***pci surprise removal***
    
    
    detail see https://unix.stackexchange.com/questions/73908/how-to-reset-cycle-power-to-a-pcie-device

    Potential Method #1
    
    I think you can do it with these commands:
    
    disable
    
    echo 0 > /sys/bus/pci/slots/$NUMBER/power
    
    enable
    
    echo 1 > /sys/bus/pci/slots/$NUMBER/power
    
    Where $NUMBER is the number of the PCI slot.
    
    lspci -vv may help to identify the device. This is not very well documented...
    Potential Method #2
    
    I came across this thread on U&L, similar issue: there are some answers to that question that say you can reset with this command:
    
    echo "1" > /sys/bus/pci/devices/$NUMBER/reset
    
    However, I would read the answers there! There are conditions around doing it this way! Specifically I would read this answer!
    Potential Method #3
    
    There is a Unix command, setpci, that may give you a method for resetting a device in the PCI bus.
    
    I did not see any specific examples with this command so you'll have to google for examples and look through the man page. I would tread lightly with this command until you're confident in it's use. From what I've read about it, it's manipulating the hardware directly and so there are always risks in doing it yourself vs. using a tool that is exposing this type of functionality!
    
    introduce new command setpci



**lspci pci show up**

    
 
    https://superuser.com/questions/1375202/how-to-understand-lspci-tree-format
    I use a Dell G3 3579 to run the lspci -tvv command.

    Here is the output:

    -[0000:00]-+-00.0  Intel Corporation 8th Gen Core Processor Host Bridge/DRAM Registers
           +-01.0-[01]----00.0  NVIDIA Corporation GP106M [GeForce GTX 1060 Mobile]
           +-02.0  Intel Corporation Device 3e9b
           +-04.0  Intel Corporation Xeon E3-1200 v5/E3-1500 v5/6th Gen Core Processor Thermal Subsystem        
           +-08.0  Intel Corporation Xeon E3-1200 v5/v6 / E3-1500 v5 / 6th/7th Gen Core Processor Gaussian Mixture Model
           +-12.0  Intel Corporation Cannon Lake PCH Thermal Controller
           +-14.0  Intel Corporation Cannon Lake PCH USB 3.1 xHCI Host Controller
           +-14.2  Intel Corporation Cannon Lake PCH Shared SRAM
           +-14.3  Intel Corporation Wireless-AC 9560 [Jefferson Peak]
           +-15.0  Intel Corporation Device a368
           +-15.1  Intel Corporation Device a369
           +-16.0  Intel Corporation Cannon Lake PCH HECI Controller
           +-17.0  Intel Corporation 82801 Mobile SATA Controller [RAID mode]
           +-1b.0-[02-3a]--
           +-1d.0-[3b]----00.0  Realtek Semiconductor Co., Ltd. RTL8111/8168/8411 PCI Express Gigabit Ethernet Controller
           +-1f.0  Intel Corporation Device a30d
           +-1f.3  Intel Corporation Cannon Lake PCH cAVS
           +-1f.4  Intel Corporation Cannon Lake PCH SMBus Controller
           \-1f.5  Intel Corporation Cannon Lake PCH SPI Controller

    I know that the GPU is directly connect to the CPU through the PCIE and intel use PCH to connect other devices.

    Here are the questions:
    Q1: Why the tree output shows that all the devices connect to the same PCI bus(bus 00)?
    Q2: What does +-1b.0-[02-3a]-- mean?
    Q3: How do I know which device is connect to CPU's PCI-E or PCH's PCI-E bus?
    A:
    Q:Why the tree output shows that all the devices connect to the same PCI bus(bus 00)?
    Because that's how PCIe structure works: All devices are connected to a single root node. (Though you can have 
    several PCIe domains, but that complicates things).
    For Intel, all external PCIe lanes, no matter if they originate from the CPU or the PCH, are behind PCIe bridges 
    (and therefore get new PCIe bus numbers). The devices in the PCH southbridge itself show up as direct descendants 
    of the PCIe root.
    Remember that the CPU and PCH are closely coupled through a proprietary high-speed bus, which is transparent to 
    the PCIe protocol. That's why the PCIe layout doesn't match the physical layout.

    Q:What does +-1b.0-[02-3a]-- mean?
    1b.0 is a slot and function number of the PCIe root hub. In this case, it contains a PCIe bridge. The busses behind 
        this bridge would be numbered 02 to 3a, even though there are currently no devices attached to them.
    In a similar way, your GPU is behind the bridge 01.0, and your LAN controller behind the bridge 1d.0, which may be an internal bridge.
    Q:How do I know which device is connect to CPU's PCI-E or PCH's PCI-E bus?

    Typically they would show up behind different PCIe bridges. Details depend on the Intel CPU architecture. No, I don't know what bridges
     that would be for your particular architecture, but possibly one can find out with Intel datasheets and/or by observing existing systems.

***https://blog.csdn.net/zhongyhc/article/details/38781695 pci总线分配的好文章***

***PCIe cfg***
    
    pcie Bridge type 1 header   BAR有0-1
    pcie end point type 0 header BAR有0-5


***pci int***
 
    >>1, 2, 3, and 4 that map to legacy interrupt Messages for INTA, INTB, INTC, and INTD   

    Interrupt Pin Register (Offset 3Dh)
    The Interrupt Pin register is a read-only register that identifies the legacy interrupt Message(s) the
    15 Function uses (see Section 6.1 for further details). Valid values are 1, 2, 3, and 4 that map to legacy
    interrupt Messages for INTA, INTB, INTC, and INTD respectively. A value of 00h indicates that
    the Function uses no legacy interrupt Message(s).

***pin A routed to IRQ 16***

  [https://stackoverflow.com/questions/15510810/linux-pci-device-driver-bus-v-kernel-irq](https://stackoverflow.com/questions/15510810/linux-pci-device-driver-bus-v-kernel-irq "IRQ")
  
    以SMI NVMe为例
    lspci -b -vv 看到的IRQ是bus-centric view，该值也跟controller pci+0x3c的值一样(0xB)
                 为物理pin
    lspci -vv 看到的IRQ则是kernel的view，IRQ为其他值(eg. 16)，该值为virtual pin，device和
               CPU之间隔着PIC

    
    CPU's IRQ pin, almost always, isn't connected directly to a peripheral device,
     but via an programmable interrupt controller(PIC, e.g. Intel 8259A). This helps handling large device fan-out and also heterogeneous interrupt format (pin based v.s. message based as in PCIe).
    If you run a recent version of lspci, it would print information like
    Interrupt: pin A routed to IRQ 26
    Here, pin A as 11 in OP, is the physical pin. This is something saved by the PCI device and used by the hardware to exchange between interrupts controller. From LDP:
    The PCI set up code writes the pin number of the interrupt controller into the PCI configuration header for each device. It determines the interrupt pin (or IRQ) number using its knowledge of the PCI interrupt routing topology together with the devices PCI slot number and which PCI interrupt pin that it is using. The interrupt pin that a device uses is fixed and is kept in a field in the PCI configuration header for this device. It writes this information into the interrupt line field that is reserved for this purpose. When the device driver runs, it reads this information and uses it to request control of the interrupt from the Linux kernel.
    IRQ 26 as 19 in OP is something that kernel code and CPU deal with. According to Linux Documentation/IRQ.txt:
    An IRQ number is a kernel identifier used to talk about a hardware interrupt source. Typically this is an index into the global irq_desc array, but except for what linux/interrupt.h implements the details are architecture specific.
    So the PCI first receives interrupts from device, translate interrupt source to a IRQ number and informs the CPU. CPU use IRQ number to look into Interrupt Descriptor Table(IDT) and find the correct software handler.

***pci capability***
    
 [https://blog.csdn.net/juana1/article/details/6746011](https://blog.csdn.net/juana1/article/details/6746011 "pci MSI capability configuration")
 
    Start End Symbol Name
    00h 03h ID Identifiers
    04h 05h CMD Command Register
    06h 07h STS Device Status
    08h 08h RID Revision ID
    09h 0Bh CC Class Codes
    0Ch 0Ch CLS Cache Line Size
    0Dh 0Dh MLT Master Latency Timer
    0Eh 0Eh HTYPE Header Type
    0Fh 0Fh BIST Built In Self Test (Optional)
    10h 13h MLBAR
    (BAR0) Memory Register Base Address, lower 32-bits <BAR0>
    14h 17h MUBAR
    (BAR1) Memory Register Base Address, upper 32-bits <BAR1>
    18h 1Bh IDBAR
    (BAR2)
    Index/Data Pair Register Base Address <BAR2>
    (Optional)
    1Ch 1Fh BAR3 Reserved <BAR3>
    20h 23h BAR4 Vendor Specific
    24h 27h BAR5 Vendor Specific
    28h 2Bh CCPTR CardBus CIS Pointer
    2Ch 2Fh SS Subsystem Identifiers
    30h 33h EROM Expansion ROM Base Address (Optional)
    34h 34h CAP Capabilities Pointer   capability list由此开始，每个capability都有个ID，然后每个capability还有个next指针
    35h 3Bh R Reserved
    3Ch 3Dh INTR Interrupt Information
    3Eh 3Eh MGNT Minimum Grant (Optional)
    3Fh 3Fh MLAT Maximum Latency (Optional)

***pci function description***
    
    
   ***pci_msi_vec_count***
        
    
        /**
     * pci_msi_vec_count - Return the number of MSI vectors a device can send
     * @dev: device to report about
     *
     * This function returns the number of MSI vectors a device requested via
     * Multiple Message Capable register. It returns a negative errno if the
     * device is not capable sending MSI interrupts. Otherwise, the call succeeds
     * and returns a power of two, up to a maximum of 2^5 (32), according to the
     * MSI specification.
     **/
    是从MSI capability + 2h 去读取MMC Multiple Message Capable (MMC): Indicates the number of messages the controller
    wants to assert.

#define __const_hweight8(w)	
        统计1的个数的一个方式	
	 ((unsigned int)			\
	 ((!!((w) & (1ULL << 0))) +	\
	  (!!((w) & (1ULL << 1))) +	\
	  (!!((w) & (1ULL << 2))) +	\
	  (!!((w) & (1ULL << 3))) +	\
	  (!!((w) & (1ULL << 4))) +	\
	  (!!((w) & (1ULL << 5))) +	\
	  (!!((w) & (1ULL << 6))) +	\
	  (!!((w) & (1ULL << 7))))



***pci port service driver***
    
 ***aer driver (aerdriver)***

     see Documentation/PCI/pcieaer-howto.txt
    Correctable errors不需要软件介入，由硬件检错和纠错
    uncorrectable errors -> non-fatal errors and fatal errors.
        Non-fatal errors cause the particular transaction to be unreliable,
            but the PCI Express link itself is fully functional.
        Fatal errors, on the other hand, cause the link to be unreliable.
     fatal error发生时，就要调用reset_link()

    hp driver  aerdriver
    VC(virtual channel) driver



***/proc/iomem***
    
    /proc/iomem里的地址是物理地址
    eg.
    通过insert_resource将resource注册到资源tree中
    insert_resource(&iomem_resource, &code_resource);
    insert_resource(&iomem_resource, &data_resource);
    insert_resource(&iomem_resource, &bss_resource); 
    而X86上物理内存的探测需要给BIOS发送0x15中断
***BIOS AND EFI***
    
    
    传统BIOS会提供e820 table提供内存布局，EFI也会提供一种内存map格式，对于efi启动方式，
    realmode下，则可能是arch/x86/boot/compressed/eboot.c里，exit_boot时，调用efi提供
    的system table->get_memory_map，获取到内存布局信息。
    setup_arch内存初始化

***内核独立module编译***
    
    
    拉取源码，make make modules_install，然后会生成/lib/modules/kernelxxx/build
    然后module编译 -C 到/lib/modules/kernelxxx/build
     /lib/modules/**/build file is a symlink to your kernel source
