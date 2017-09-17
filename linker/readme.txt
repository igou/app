head.s and vmlinux.lds.s locate in arch/arm/kernel.
vmlinux.lds.s是链接脚本，但是以汇编文件形式存在，里面也涉及到汇编的一些语法。该文件会kbuild转换为vmlinux.lds
文件来自于3.14.2
最主要是linker的语法
SECTIONS{}语句表示输出文件的内存布局
 {
    . = 0x10000;
    .text START : AT(LOADADDR) { *(.text) }  //分号前是输出文件的段，后是输入文件的段 START可以指定run-time地址, 后面at是load地址，at不写的话就等于run-time地址。
    . = 0x8000000;
    .data : { *(.data) }
    .bss : { *(.bss) }
 }
