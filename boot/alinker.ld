SECTIONS
{
	. = 0x80000, 

	_text_boot = .;
	.text.boot : { *(.text.boot) }
	_etext_boot = .;

	_text = .;
	.text : { *(.text) }
	_etext = .;

	_rodata = .;
	.rodata : { *(.rodata) }
	_erodata = .;

	_data = .;
	.data : {
		 *(.data)
		 . = ALIGN(4096);
		 *(.data.init_task) 
	}
	. = ALIGN(4096);
	idmap_pg_dir = .;
	. += 4096;
	_edata = .;

	. = ALIGN(0x8);
	_bss = .;
	.bss : { *(.bss*) } 
	_ebss = .;

	. = ALIGN(4096);
	init_pg_dir = .;
	. += 4096;
}
