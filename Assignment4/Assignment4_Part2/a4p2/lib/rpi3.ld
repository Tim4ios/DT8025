/*
    Part of the Real-Time Embedded Systems course at Halmstad University
    Copyright (c) 2016, Sebastian Kunze <sebastian.kunze@hh.se>
    All rights reserved.
*/

/* Linker script for LM3S811 */
EXTERN (Vector_Table)
EXTERN (Default_Handler)
ENTRY  (Entry)

SECTIONS {
	/* main code */
	. = 0x8000;
	.text : {
		*(.startup)
		*(.text*)
		. = ALIGN(4);
		*(.rodata*)
	}

	/* static constructors/destructors */
	.preinit_array : {
		. = ALIGN(4);
		PROVIDE_HIDDEN (__preinit_array_start = .);
		KEEP (*(.preinit_array))
		PROVIDE_HIDDEN (__preinit_array_end = .);
	}
	.init_array : {
		. = ALIGN(4);
		PROVIDE_HIDDEN (__init_array_start = .);
		KEEP (*(SORT(.init_array.*)))
		KEEP (*(.init_array))
		PROVIDE_HIDDEN (__init_array_end = .);
	}
	.fini_array : {
		. = ALIGN(4);
		PROVIDE_HIDDEN (__fini_array_start = .);
		KEEP (*(.fini_array))
		KEEP (*(SORT(.fini_array.*)))
		PROVIDE_HIDDEN (__fini_array_end = .);
	}
	. = ALIGN(4);
	_etext = .;

	/* main data */
	.data : {
		PROVIDE_HIDDEN (_data = LOADADDR(.data));
		PROVIDE_HIDDEN (_sdata = .);
		*(.data*)
		. = ALIGN(4);
		PROVIDE_HIDDEN (_edata = .);
	}

	/* fastcall */
	.fast : {
		PROVIDE_HIDDEN (_fast = LOADADDR(.fast));
		PROVIDE_HIDDEN (_sfast = .);
		*(.fast)
		. = ALIGN(4);
		PROVIDE_HIDDEN (_efast = .);
	}

	/* zero-initialized data */
	.bss (NOLOAD) : {
		PROVIDE_HIDDEN (_sbss = .);
		*(.bss*)
		*(COMMON)
		. = ALIGN(4);
		PROVIDE_HIDDEN (_ebss = .);
	}

	/* Might be needed for C++ exceptions */
	/DISCARD/ : { *(.eh_frame) }

	. = ALIGN(4);
	_end = .;

	. = 0x4000000;	/* 64 MB */
	_heap_end = .;
}