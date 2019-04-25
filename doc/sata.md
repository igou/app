***FPDMA***    

    first part dma是可以让drive发起dma的机制
    device发起一个DMA setup FIS(frame information structure)给host控制器，该FIS指定了
    TAG。host根据tag，加载PRD table指针到DMA engine。这意味着drive可以重新排序command，
    根据其需求发起要传哪个buffer。
    tag#        FPDMA Vector Table
     0          PRD table 0
     1          PRD table 1
     ...
     32         PRD table 32
        PRD table x填入DMA Engine

***NCQ 分两类command***

    

    Race-Free Status Return: 无竞争状态返回机制，允许任何指令任何时间报告执行状态，此外，
        多个命令执行完毕信息可以打包一起回传。

    Interrupt Aggregation: 在DMA传输模式下，硬盘通知传输结束，会引起一个中断（Interrupt），
        造成延迟。所以，SATA spec提供中断聚集机制。如果硬盘同时间内完成多组命令，这些命令完成
        所引起的中断就可以聚集在一起，大幅减少中断的数目，这对于降低中断延迟有极大的贡献。
    
    First-Party DMA(FPDMA): SATA允许硬盘端通过DMA setup FIS直接对Host控制器送出数据传
    输请求，DMA引擎就可以直接进行资料传输，这个过程中并不需要Host端软件的介入。

    Status Return:host有个32-bit的SActive寄存器记录每个tag的状态，如果bit为1，表明command
    是outstanding(在drive中还没处理或者即将发送到drive)。SActive(completion机制)->host 
    set，device clear(clear bit通过发送Set Device Bits FIS),host和device不需要同步
**Read  FPDMA Queued Command**


    command 60h,FUA bit ,TAG

    TAG:NCQ有个tag，其值位于0到31之间，如果drive支持少于32个，那么久限制最大的tag。使用32个
    tag值，可以使用一个32-bit的值报告所有command的状态
    One interesting field is the TAG field in the Sector Count register.  Each queued
    command issued has a tag associated with it.  The tag is a shorthand mechanism 
    used between the host and the device to identify a particular outstanding command.
    Tag values can be between 0 and 31, although the drive can report support for 
    a queue depth less than 32.  In this case, tag values are limited to the maximum 
    tag value the drive supports.  Having tag values limited to be between 0 and 31 
    has some nice advantages, including that status for all commands can be reported 
    in one 32-bit value.  Each outstanding command must have a unique tag value                                                        

**Write FPDMA Queued Command**
    
    command 61h,FUA bit ,TAG
