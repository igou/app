BME 和 MSE 要先为1，该两个属于PCI reg

BME 
    
    Enables the controller to act as a master for data transfers
MSE 
    
    Controls access to the controller’s register memory
    space.

READ SQ
    
    控制器发送一个 pci express read从host 中fetch cmd entries



CMB
    
    使用controller的memory，比如 SQ放在controller的内存中等，see doc 4.7