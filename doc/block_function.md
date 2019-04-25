**blk\_rq\_bio\_prep()**
    
    将request与bio联系起来
**blk\_mq\_map\_request()**

    __blk_mq_alloc_request()申请request，如果没有request时，会run_hw_queue执行之前的request，释放出request
**generic\_make\_request()**

    /*
	 * We only want one ->make_request_fn to be active at a time, else
	 * stack usage with stacked devices could be a problem.  So use
	 * current->bio_list to keep a list of requests submited by a
	 * make_request_fn function.  current->bio_list is also used as a
	 * flag to say if generic_make_request is currently active in this
	 * task or not.  If it is NULL, then no make_request is active.  If
	 * it is non-NULL, then a make_request is active, and new requests
	 * should be added at the tail
	 */
    这里还跟进程有关，有防止递归的手段
**generic\_file\_direct\_write()**

**bio\_add\_page()**
    
    attempt to add page to bio

**submit\_bio()**
    
    /**
    * submit_bio - submit a bio to the block device layer for I/O
    * @bio: The &struct bio which describes the I/O
    * submit_bio() is very similar in purpose to generic_make_request(), and
    * uses that function to do most of the work. Both are fairly rough
    * interfaces; @bio must be presetup and ready for I/O.
    */
    
**blk\_mq\_make\_request()**

    mq所用的请求request函数
    Multiple hardware queue variant. This will not use per-process plugs,
    but will attempt to bypass the hctx queueing if we can go straight to
    hardware for SYNC IO.

    static blk_qc_t blk_mq_make_request(struct request_queue *q, struct bio *bio)
    {
	const int is_sync = rw_is_sync(bio_op(bio), bio->bi_opf);
	const int is_flush_fua = bio->bi_opf & (REQ_PREFLUSH | REQ_FUA);
	struct blk_map_ctx data;
	struct request *rq;
	unsigned int request_count = 0;
	struct blk_plug *plug;
	struct request *same_queue_rq = NULL;
	blk_qc_t cookie;

	blk_queue_bounce(q, &bio);

	if (bio_integrity_enabled(bio) && bio_integrity_prep(bio)) {
		bio_io_error(bio);
		return BLK_QC_T_NONE;
	}

	blk_queue_split(q, &bio, q->bio_split);

	if (!is_flush_fua && !blk_queue_nomerges(q) &&
	    blk_attempt_plug_merge(q, bio, &request_count, &same_queue_rq))
		return BLK_QC_T_NONE;

	rq = blk_mq_map_request(q, bio, &data);
	if (unlikely(!rq))
		return BLK_QC_T_NONE;

	cookie = blk_tag_to_qc_t(rq->tag, data.hctx->queue_num);

	if (unlikely(is_flush_fua)) {
		blk_mq_bio_to_request(rq, bio);
		blk_insert_flush(rq);
		goto run_queue;
	}

	plug = current->plug; // 当前进程的plug
	**/*
	 * If the driver supports defer issued based on 'last', then
	 * queue it up like normal since we can potentially save some
	 * CPU this way.
	 */**
	if (((plug && !blk_queue_nomerges(q)) || is_sync) &&
	    !(data.hctx->flags & BLK_MQ_F_DEFER_ISSUE)) {
		struct request *old_rq = NULL;

		blk_mq_bio_to_request(rq, bio);

		/*
		 * We do limited pluging. If the bio can be merged, do that.
		 * Otherwise the existing request in the plug list will be
		 * issued. So the plug list will have one request at most
		 */
		if (plug) {
			/*
			 * The plug list might get flushed before this. If that
			 * happens, same_queue_rq is invalid and plug list is
			 * empty
			 */
			if (same_queue_rq && !list_empty(&plug->mq_list)) {
				old_rq = same_queue_rq;
				list_del_init(&old_rq->queuelist);
			}
			list_add_tail(&rq->queuelist, &plug->mq_list);
		} else /* is_sync */
			old_rq = rq;
		blk_mq_put_ctx(data.ctx);
		if (!old_rq)
			goto done;
		if (!blk_mq_direct_issue_request(old_rq, &cookie))
			goto done;
		blk_mq_insert_request(old_rq, false, true, true);
		goto done;
	}

	if (!blk_mq_merge_queue_io(data.hctx, data.ctx, rq, bio)) {
		/*
		 * For a SYNC request, send it to the hardware immediately. For
		 * an ASYNC request, just ensure that we run it later on. The
		 * latter allows for merging opportunities and more efficient
		 * dispatching.
		 */
    run_queue:    //sync或者fua直接run_hw_queu
		blk_mq_run_hw_queue(data.hctx, !is_sync || is_flush_fua);
	}
	blk_mq_put_ctx(data.ctx);
    done:
	return cookie;
    }


***
**blk-sysfs.c**
    
    这里显示/sys/block/'disk'的信息
    struct kobj_type blk_queue_ktype = {
	.sysfs_ops	= &queue_sysfs_ops,
	.default_attrs	= default_attrs,
	.release	= blk_release_queue,
    };
    比如 nvme下的max_segments就是来自于nvme_set_queue_limits()函数
    blk_queue_logical_block_size()设置block_size


**nvme\_revalidate\_disk()**
    
    namespace的相关信息



**缩写**

    内核块设备中的bt前缀是block tag

***blk-mq***

**picture from [https://blog.csdn.net/zhufengtianya/article/details/43266415](https://blog.csdn.net/zhufengtianya/article/details/43266415 "blk-mq picture")**
    

    process                 o   o   o   o   o
                            ↓   ↓   ↓   ↓   ↓
    soft-ctx(per-cpu)       x   x   x   x   x
                             ↘↙ ↘↙ ↘ ↙ ↘↙
    hard-ctx                  y   y   y    y
                              ↓   ↓   ↓    ↓
    hardware                  z   z   z    z

    Multi-queue应运而生。其主要思想在于将单个请求队列上的资源竞争分散至多队列上。该多队列
    主要分为以下两种：软件队列以及硬件分配队列。
    软件队列：软件队列原则上可为每个核或者每个socket配置一个处理队列。假设一个NUMA系统有
    4个sockets，每个socket有6个核，那么最少可配置4个软件队列，最多配置24个软件队列。在对
    应的每个软件队列中可进行请求调度，添加标记以及计数等功能。在此基础上，每个socket或者核
    直接将请求发送至其对应的软件队列中， 从而可避免单请求队列造成的锁竞争问题。

    硬件队列：硬件队列主要负责与底层设备驱动的匹配，即存在多少个设备驱动，则配置对应数量的
    硬件队列。其将负责将来自软件队列的请求发送至驱动层。
    
    当请求加入到硬件队列后，其会被打上一个唯一标签，该标签会随后传入驱动层，主要用于判断此
    请求是否已被处理完成。