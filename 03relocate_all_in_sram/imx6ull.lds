SECTIONS {
    _load_addr = 0x80100000;

    . = 0x900000 ;

    . = ALIGN(4);
    .text      :
    {
      *(.text)
    }

    . = ALIGN(4);
    .rodata : { *(.rodata) }

    . = ALIGN(4);

    .data  :
    {
      data_start = . ;
      *(.data) 
      data_end = . ;
    }

    . = ALIGN(4);
    __bss_start = .;
    .bss : { *(.bss) *(.COMMON) }
    __bss_end = .;
}
