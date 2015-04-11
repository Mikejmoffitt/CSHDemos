#include <genesis.h>
#include "col.h"
#include "mpad.h"

u16 col = 0;

_voidCallback *v_int(void)
{
	//VDP_setPaletteColor(0,col);	
	//col_puts(0,1,"Got int...");
	//col += 0x100;
}	

_voidCallback *h_int(void)
{
	VDP_setPaletteColor(0,col);
	col += 0x001;
	return; 
}

void setup(void)
{
	VDP_init();
	col_init();
	VDP_setHInterrupt(16);	

	SYS_setInterruptMaskLevel(0);
	SYS_setVIntCallback(v_int);
	SYS_setHIntCallback(h_int);
	SYS_enableInts();
}

int main(void)
{
	setup();
	u16 i;
	VDP_setPaletteColor(0,0x000);
	VDP_setPaletteColor(1,0x666);
	VDP_setPaletteColor(2,0xAAA);
	VDP_setPaletteColor(3,0xEEE);
	col_puts(0,0,"Test text!");
	for (;;)
	{
		VDP_waitVSync();
	}
	return 0;	
}

/* vim: set noet: */
