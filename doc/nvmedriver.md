***Keith Busch->nvme driver development history ppt***

**[https://www.wesrch.com/electronics/paper-details/pdf-EL1SE1SBQTYBV-linux-nvm-express#page23](https://www.wesrch.com/electronics/paper-details/pdf-EL1SE1SBQTYBV-linux-nvm-express#page23 "Keith Busch- nvme driver development history ppt")**


***flash ppt***
    
 **[https://www.wesrch.com/presentations?display=all&org=Flash+Memory+Summit](https://www.wesrch.com/presentations?display=all&org=Flash+Memory+Summit "more meaningful flash ppt")**

**blk\_rq\_map\_user()和blk\_rq\_map\_kern()**
    
    blk_rq_map_user函数是用于user发送来的cmd,建立user buffer与bio的联系，处理bio_vec,最后加入request;
    blk_rq_map_kern函数是处理kernel发送的命令建立bio和pages,bio与request联系
blk_rq\_map\_user():[https://blog.csdn.net/fudan_abc/article/details/2034264](https://blog.csdn.net/fudan_abc/article/details/2034264 "blk_rq_map_user")
blk\_rq\_map\_kern():[https://blog.csdn.net/fudan_abc/article/details/2037612](https://blog.csdn.net/fudan_abc/article/details/2037612 "blk_rq_map_kern")


    

    struct nvme_ctrl {

	enum nvme_ctrl_state state;
	spinlock_t lock;
	const struct nvme_ctrl_ops *ops;
	struct request_queue *admin_q;
	struct request_queue *connect_q;
	struct device *dev;
	struct kref kref;
	int instance;
	struct blk_mq_tag_set *tagset;
	struct list_head namespaces;
	struct mutex namespaces_mutex;
	struct device *device;	/* char device */
	struct list_head node;
	struct ida ns_ida;

	char name[12];
	char serial[20];
	char model[40];
	char firmware_rev[8];
	u16 cntlid;

	u32 ctrl_config;

	u32 page_size;   **nvme_enable_ctrl()中设置，目前为4k**
	u32 max_hw_sectors;
	u32 stripe_size;
	u16 oncs;
	u16 vid;
	atomic_t abort_limit;
	u8 event_limit;
	u8 vwc;
	u32 vs;
	u32 sgls;
	u16 kas;
	unsigned int kato;
	bool subsystem;
	unsigned long quirks;
	struct work_struct scan_work;
	struct work_struct async_event_work;
	struct delayed_work ka_work;

	/* fabrics only */
	u16 sqsize;
	u32 ioccsz;
	u32 iorcsz;
	u16 icdoff;
	u16 maxcmd;
	struct nvmf_ctrl_options *opts;};
*** 
**nvme\_init\_iod**

    初始化iod，里面包括sg等信息，如果sg不够，就要重新分配

**/*
 * max size of iod being embedded in the request payload
 * request后面会带payload的一些空间，这是固定的长度。如果超过了这个限制，就会另行分配iod->sg = kmalloc,否则就
 * 用iod->inline_sg
 */**

    #define nvme_int_pages		2
    #define nvme_int_bytes(dev)	(nvme_int_pages * (dev)->ctrl.page_size)

    static unsigned int nvme_cmd_size(struct nvme_dev *dev)
    {
     //request后面预留的空间
    | nvme_iod |sizeof(__le64 *) * nvme_npages(size, dev)|nvme_int_pages * struct scatterlist|
    	return sizeof(struct nvme_iod) +
    		nvme_iod_alloc_size(dev, nvme_int_bytes(dev), nvme_int_pages);
    }
**1 个 sg里有page地址和相对应的连续物理地址**

    static __le64 **iod_list(struct request *req)
    {
    	struct nvme_iod *iod = blk_mq_rq_to_pdu(req);
    	return (__le64 **)(iod->sg + req->nr_phys_segments);// 移动sg
    }
***

**nvme\_map\_data()**
**一个sg对应一个连续的物理地址，但prp对于物理地址又有要求，所以需要再次处理转换nvme_setup_prps(),**
**即物理地址跨了cc.mps(memory page size，page_size为4k来源于此)，就要用prp2 或者 prp list**

    static int nvme_map_data(struct nvme_dev *dev, struct request *req,
		unsigned size, struct nvme_command *cmnd)
    {
	struct nvme_iod *iod = blk_mq_rq_to_pdu(req);
	struct request_queue *q = req->q;
	enum dma_data_direction dma_dir = rq_data_dir(req) ?
			dma_to_device : dma_from_device;
	int ret = blk_mq_rq_queue_error;

	sg_init_table(iod->sg, req->nr_phys_segments);
    **bios to sg**
	iod->nents = blk_rq_map_sg(q, req, iod->sg);
	if (!iod->nents)
		goto out;

	ret = blk_mq_rq_queue_busy;
    **返回sg的物理地址**
	if (!dma_map_sg(dev->dev, iod->sg, iod->nents, dma_dir))
		goto out;

	if (!nvme_setup_prps(dev, req, size))
		goto out_unmap;

	ret = blk_mq_rq_queue_error;
	if (blk_integrity_rq(req)) {
		if (blk_rq_count_integrity_sg(q, req->bio) != 1)
			goto out_unmap;

		sg_init_table(&iod->meta_sg, 1);
		if (blk_rq_map_integrity_sg(q, req->bio, &iod->meta_sg) != 1)
			goto out_unmap;

		if (rq_data_dir(req))
			nvme_dif_remap(req, nvme_dif_prep);

		if (!dma_map_sg(dev->dev, &iod->meta_sg, 1, dma_dir))
			goto out_unmap;
	}

	cmnd->rw.dptr.prp1 = cpu_to_le64(sg_dma_address(iod->sg));
	cmnd->rw.dptr.prp2 = cpu_to_le64(iod->first_dma);
	if (blk_integrity_rq(req))
		cmnd->rw.metadata = cpu_to_le64(sg_dma_address(&iod->meta_sg));
	return blk_mq_rq_queue_ok;

    out_unmap:
	   dma_unmap_sg(dev->dev, iod->sg, iod->nents, dma_dir);
    out:
	   return ret;
    } 
*** 
*** 
![seg and page](http://oliveryang.net/media/images/2016/page_segment_block_sector.png)

**有个概念->max_segments的计算结果是表明一个request中最多能有多少个bio_vec，具体例子参见函数 nvme\_set\_queue\_limits()【max\_hw\_sectors可能来自nvme identity返回的mdts，SMI返回的max data transfer size为128K】**

![bio + bio_vec + page](http://oliveryang.net/media/images/2016/bio_page.png)

**bio_vec and bio**

    struct bio_vec { // 表示一个segment，一个seg在一page内
    	struct page	*bv_page;
    	unsigned int	bv_len;
    	unsigned int	bv_offset;
    };
        下面只是截取了bio的部分成员
    struct bio {
    	struct bio		*bi_next;	/* request queue link */
    	struct block_device	*bi_bdev;
    	struct bvec_iter	bi_iter;
    	/* Number of segments in this BIO after
    	 * physical address coalescing is performed.
    	 */
    	unsigned int		bi_phys_segments;
    	struct bio_vec		*bi_io_vec;	/* the actual vec list */
    	struct bio_set		*bi_pool;
    	/*
    	 * We can inline a number of vecs at the end of the bio, to avoid
    	 * double allocations for a small number of bio_vecs. This member
    	 * MUST obviously be kept at the very end of the bio.
    	 */
    	struct bio_vec		bi_inline_vecs[0];
}

    request[ bio    ... bio]
    bio    [ bi_vec ...  bi_vec] //每个bi_vec对应一页
    **下面讲到的__blk_segment_map_sg()就是来处理最小单位 bi_vec的**

**blk\_rq\_map\_sg 函数**

该函数解析来自[https://blog.csdn.net/lpstc123/article/details/44983707](https://blog.csdn.net/lpstc123/article/details/44983707)

主要流程:

- 1.调用* \_\_blk\_bios\_map\_sg函数*  根据这个request对象中隐含的bios链表中的bio来设置sglist。该函数会返回sglist中设置了的表项的数目，并且传递给它的参数sg会被设置为指向最后一个设置了的表项。
- 2.有的设备存在“excess dma”的问题，如果是这样的话必须在散列表后面追加一个“抽干缓冲区”，用于存放那些无意义的数据。
- 3.调用sg\_mark\_end函数设置scatterlist的末尾表项的结束标志，最后返回scatterlist中设置了的表项的数目。

**step 1. \_\_blk\_bios\_map\_sg函数**
    
    主要函数部分
    for_each_bio(bio) // 不止处理传入的bio，还会处理该struct request的后续bio
		bio_for_each_segment(bvec, bio, iter) 
			__blk_segment_map_sg(q, &bvec, sglist, &bvprv, sg,
					     &nsegs, &cluster);// 处理bio中的bi_io_vec的合并

    此函数负责从bio构建出一个scatterlist，因为一个request可以对应多个bio，所以这里处理的不仅仅是传入的bio，
    还会继续它的下一个bio直到末尾。
    sglist：表示我们要设置的那张scatterlist。
    sg：当这个函数执行完成之后，sg就是指向了最后一个有用scatterlist表项。它返回scatterlist中实际设置了多少
    个项。
    主要流程:
    - 1.如果bio设置了req_write_same标志，表示多次读写同一个块，那么只需要设置一个scatterlist表项（因为如果
    - 这个bio后面还跟随了其他bios，那么肯定也是写同一个位置的，这是merge操作决定的）并返回1。
    - 2.对这个bio链中的每个bio的每个segment调用__blk_segment_map_sg函数*，逐段的设置scatterlist。
    - 3.返回nsegs(scatterlist中使用了的表项数目)

**step 2. \_\_blk\_segment\_map\_sg函数**

    bvec：当前要“转换”（根据bio_vec设置scatterlist表项）的bio_vec
    sglist：表示我们要设置的那张聚散列表
    bvprv：用来保存前一个segment
    sg：用于存储前一个聚散表表项
    nsegs：用来存储目前设置了多少个表项
    
    主要流程:
    - 1.如果 *sg 不为空(只有第一次才可能为空)，说明前面存在scatterlist表项，尝试bvec能否和前一个合并：
        - a.合并之后的大小不能超过request_queue的limits限制的最大段大小
        - b.两者所描述的physical address必须能够衔接起来
        - c.合并后的段的地址必须符合limits中段界限要求。(假设一个设备dma有4MB的限制，mask就设为0x3FFFFF,可以解释宏BIOVEC_SEG_BOUNDARY()的原理，只要4MB以上的为都相等那么就符合要求，而且在调用该宏之前，前后bi_vec的phy地址连续的条件已经满足了)
         - 只有上面的三个条件都满足才能认为是可以合并的，此时只需修改 *sg 中的长度即可，然后跳至第4步；
         -  否则的则需要使用一个新段。
    - 2.如果 *sg 为空，说明这是第一次进来设置sglist，那么就将它赋值为sglist；否则的话，将它赋值为下一       
        -  个表项。这时，sg的作用有了改变，它现在指向这个bvec要使用的scatterlist表项。  
    - 3.调用sg_set_page函数设置该表项(这里只设置虚拟page地址，dma地址应该在其他函数设置，如nvme的dma_map_sg())，并递加nsegs的值。   
    - 4.最后将bvprv设置为这个bvec(这样下次进入这个函数时bvprv就成了指向前一个段的指针)
 （segment boundary检查的解释[https://stackoverflow.com/questions/14200095/whats-the-usage-of-blk-queue-segment-boundary](https://stackoverflow.com/questions/14200095/whats-the-usage-of-blk-queue-segment-boundary "segment")）
 
 
 
**nvme\_setup\_prps()**         sg填充好后，就要setup prps了
    
    一个sg对应一个连续的物理地址，但prp对于物理地址又有要求，所以需要再次处理转换nvme_setup_prps(),即物理地址跨了cc.mps(memory page size，page_size为4k来
    源于此)，就要用prp2 或者 prp list
    
    
***
***
***nvme Initialization 7.6.1***
    
    RDY由controller设置
    host等RDY变为0，controller设置CC.EN为1，controller将RDY置为1，表明可以处理command了
**nvme\_wait\_ready()**
        
    host要等CSTS.RDY to become 'status'

****
    
    static int nvme_configure_admin_queue(struct nvme_dev *dev)
    {
	
	dev->subsystem = readl(dev->bar + NVME_REG_VS) >= NVME_VS(1, 1) ?
						NVME_CAP_NSSRC(cap) : 0;
    // host将CC.EN清为0，且等RDY为0
    //2. The host waits for the controller to indicate that any previous reset is complete by waiting for
    CSTS.RDY to become ‘0.’
	result = nvme_disable_ctrl(&dev->ctrl, cap);
    // 3 4 5 6由下面语句和nvme_enable_ctrl()完成
    //3. The Admin Queue should be configured. The Admin Queue is configured by setting the Admin
    Queue Attributes (AQA), Admin Submission Queue Base Address (ASQ), and Admin Completion
    Queue Base Address (ACQ) to appropriate values.
    //4. The controller settings should be configured. Specifically:
    a. The arbitration mechanism should be selected in CC.AMS.
    b. The memory page size should be initialized in CC.MPS.
    c. The I/O Command Set that is to be used should be selected in CC.CSS.
	writel(aqa, dev->bar + NVME_REG_AQA);
    //5. The controller should be enabled by setting CC.EN to ‘1’.
    //6. The host should wait for the controller to indicate it is ready to process commands. The controller
    is ready to process commands when CSTS.RDY is set to ‘1’.
	lo_hi_writeq(nvmeq->sq_dma_addr, dev->bar + NVME_REG_ASQ);
	lo_hi_writeq(nvmeq->cq_dma_addr, dev->bar + NVME_REG_ACQ);
	result = nvme_enable_ctrl(&dev->ctrl, cap);
    }
    //7. The host should determine the configuration of the controller by issuing the Identify command,
    specifying the Controller data structure. The host should then determine the configuration of
    each namespace by issuing the Identify command for each namespace, specifying the
    Namespace data structure
    nvme_init_identify()
    //8. The host should determine the number of I/O Submission Queues and I/O Completion Queues
    supported using the Set Features command with the Number of Queues feature identifier. After
    determining the number of I/O Queues, the MSI and/or MSI-X registers should be configured.
    //9. The host should allocate the appropriate number of I/O Completion Queues based on the number
    required for the system configuration and the number supported by the controller. The I/O
    Completion Queues are allocated using the Create I/O Completion Queue command.
    //10. The host should allocate the appropriate number of I/O Submission Queues based on the number
    required for the system configuration and the number supported by the controller. The I/O
    Submission Queues are allocated using the Create I/O Submission Queue command.
    nvme_setup_io_queues()  // 会发送set features,然后先create io completion queue，再create io submission queue
    //11. If the host desires asynchronous notification of optional events, the host should issue a Set
    Features command specifying the events to enable. If the host desires asynchronous notification
    of events, the host should submit an appropriate number of Asynchronous Event Request
    commands. This step may be done at any point after the controller signals it is ready (i.e.,
    CSTS.RDY is set to ‘1’).
    nvme_queue_async_events()


**nvme\_shutdown\_ctrl()**
    
    The host 设置 Shutdown Notification (CC.SHN)为01b to indicate a normal
    shutdown operation. The controller 设置Shutdown Status (CSTS.SHST) 
    为10b指示shutdown processing完成






***
***
***
**Controller Level Reset**

    1.NVM Subsystem Reset
    2.Conventional Reset (PCI Express Hot, Warm, or Cold reset)
    3.PCI Express transaction layer Data Link Down status
    4.Function Level Reset (PCI reset)
    5.Controller Reset (CC.EN transitions from ‘1’ to ‘0’)
    
    除了Controller Reset，都会导致与host失去通信
    
    Controller Reset时，AQA ASQ ACQ不会reset


**nvme\_alloc\_admin\_tags() nvme\_dev\_add()**

    其中会设置admin timeout，ADMIN_TIMEOUT目前是60s
    NVME_IO_TIMEOUT为30s
    blk_mq_init_allocated_queue()该函数会将该timeout设置到request_queue的rq_timeout
    blk_mq_start_request()中的blk_add_timer()则会取request_queue的该值作为每个request的timeout时间
    


**NVMe abort command**
    
    是一个尽力而为的command，因为被abort的命令可以已经执行了或正在执行。
    completion的DWORD 0的bit 0指示abort是否成功。 0 成功 1 失败
    completing aborted command with status: 来自nvme_complete_rq()
    nvme nvme0: I/O 168 QID 1 timeout, reset controller这是由于该command已经被abort一次
    但abort还没有返回驱动或者是由于该command为 admin command timeout，所以reset controller
    来自于nvme_timeout()




*** typedef int vector[10] typedef数组类型***

    定义含有10个元素的数组类型vector，
  
    vector v1,v2;
    定义了vector类型的两个对象v1和v2，每个对象都是vector类型的一个数组，每个数组
    由10个整型元素所组成。



***Linux interrupt review***

**[http://www.wowotech.net/irq_subsystem/irq-domain.html](http://www.wowotech.net/irq_subsystem/irq-domain.html)**    

    
    irq number,irq chip,irq domain    

    关于HW interrupt ID映射到IRQ number上 这事，在过去系统只有一个interrupt controller
    的时候还是很简单的，中断控制器上实际的HW interrupt line的编号可以直接变成IRQ number。
    例如我们大家都熟悉的SOC内嵌的interrupt controller，这种controller多半有中断状态寄存
    器，这个寄存器可能有64个bit（也可能更多），每个bit就是一个IRQ number，可以直接进行映
    射。这时候，GPIO的中断在中断控制器的状态寄存器中只有一个bit，因此所有的GPIO中断只有一
    个IRQ number，在该通用GPIO中断的irq handler中进行deduplex，将各个具体的GPIO中断映射
    到其相应的IRQ number上。如果你是一个足够老的工程师，应该是经历过这个阶段的。
        随着linux kernel的发展，将interrupt controller抽象成irqchip这个概念越来越流行，
    甚至GPIO controller也可以被看出一个interrupt controller chip，这样，系统中至少有两
    个中断控制器了，一个传统意义的中断控制器，一个是GPIO controller type的中断控制器。随
    着系统复杂度加大，外设中断数据增加，实际上系统可以需要多个中断控制器进行级联，面对这样
    的趋势，linux kernel工程师如何应对？答案就是irq domain这个概念。
        我们听说过很多的domain，power domain，clock domain等等，所谓domain，就是领域，
    范围的意思，也就是说，任何的定义出了这个范围就没有意义了。系统中所有的interrupt 
    controller会形成树状结构，对于每个interrupt controller都可以连接若干个外设的中断请
    求（我们称之interrupt source），interrupt controller会对连接其上的interrupt source
    （根据其在Interrupt controller中物理特性）进行编号（也就是HW interrupt ID了）。但这
    个编号仅仅限制在本interrupt controller范围内。 