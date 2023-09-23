OUTPUT_ARCH("riscv")
ENTRY(_entry)

SECTIONS
{

  . = 0x80000000;

  .text : {
    *(.text .text.*)
    . = ALIGN(4K);
    PROVIDE(etext = .);
  }

  .rodata : {
    . = ALIGN(4K);
    *(.srodata .srodata.*) /* do not need to distinguish this from .rodata */
    . = ALIGN(4K);
    *(.rodata .rodata.*)
  }

  .data : {
    . = ALIGN(4K);
    *(.sdata .sdata.*) /* do not need to distinguish this from .data */
    . = ALIGN(4K);
    *(.data .data.*)
  }

  .bss : {
    . = ALIGN(4K);
    *(.sbss .sbss.*) /* do not need to distinguish this from .bss */
    . = ALIGN(4K);
    *(.bss .bss.*)
  }
  . = ALIGN(4K);
  PROVIDE(end = .);
}