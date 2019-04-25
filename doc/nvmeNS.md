NVMe
    
identify command
    
    identify controller data -->  01h
multi namespace
    
    5.11
    CNS要支持10h-13h
    返回的数据结构长度为4096字节


**kernel**
    
    nvme_identify_ctrl() identify controller 01h  --一般nvme_scan_work()时发送
    nvme_identify_ns_list() identify ns list 02h
    nvme_identify_ns() identify ns   00h
    struct nvme_id_ns {
	__le64			nsze;   namespace size
	__le64			ncap;    为0表示namespace id is inactive，This field indicates the maximum number of logical blocks
        that may be allocated in the namespace at any point in time
	__le64			nuse;
	__u8			nsfeat;
	__u8			nlbaf;
	__u8			flbas;  formatted lba size
	__u8			mc;     Metadata Capabilities
	__u8			dpc;    End-to-end Data Protection Capabilities
	__u8			dps;    End-to-end Data Protection Type Settings
	__u8			nmic;   Namespace Multi-path I/O and Namespace Sharing Capabilities
	__u8			rescap;
	__u8			fpi;
	__u8			rsvd33;
	__le16			nawun;    Namespace Atomic Write Unit Normal
	__le16			nawupf;
	__le16			nacwu;
	__le16			nabsn;
	__le16			nabo;
	__le16			nabspf;
	__u16			rsvd46;
	__le64			nvmcap[2];
	__u8			rsvd64[40];
	__u8			nguid[16];
	__u8			eui64[8];
	struct nvme_lbaf	lbaf[16]; LBA Format Support
	__u8			rsvd192[192];
	__u8			vs[3712];
    }




***

**NVMe Reservation command**
[http://www.ssdfans.com/blog/2018/06/21/%e8%9b%8b%e8%9b%8b%e8%af%bb%e5%89%a9%e7%9a%84nvme%e4%b9%8b%e4%b8%80%ef%bc%9anvme-reservation/](http://www.ssdfans.com/blog/2018/06/21/%e8%9b%8b%e8%9b%8b%e8%af%bb%e5%89%a9%e7%9a%84nvme%e4%b9%8b%e4%b8%80%ef%bc%9anvme-reservation/)

    属于 IO command
    Reservation操作的对象是Namespace，而不是SSD
    
***Asynchronous Namespace Access (ANA)***
    
    
    kernel abbr