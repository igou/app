***UIO***


    uio的/dev/uioX节点是userspace uio创建的，pci_uio.c ->pci_get_uio_dev（）->pci_mknod_uio_dev
    内核驱动会在/sys下建立uioX