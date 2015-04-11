#include <genesis.h>
#include <stdio.h>
#include "col.h"
#include "mpad.h"

u16 hint_val = 1;
u16 col = 0;
u16 col_off = 0;


void lp(u16 x, u16 y, u16 val)
{
	val += 128;
	VDP_setTileMapXY(
				VDP_PLAN_A,
				TILE_ATTR_FULL(0,0,0,0,
				val + (COL_FONT_VRAM_OFFSET/32)),x,y);
}

void putCSHLogo(u16 x, u16 y)
{
	// top line
	lp(x,y,4); // corner TL
	for (u16 i = 1; i < 17; i++)
	{
		lp(x + i,y,5);
	}
	lp(x + 17,y,6);
	lp(x + 20,y,4);
	lp(x + 21,y,5);
	lp(x + 22,y,6);
	// line 2
	y++;
	lp(x,y,7);
	lp(x+17,y,7);
	lp(x+20,y,7);
	lp(x+22,y,7);
	// line 3
	y++;
	lp(x,y,7);
	lp(x+2,y,4);
	for (int i = 3; i < 15; i++)
	{
		lp(x+i,y,5);
	}
	lp(x+15,y,6);
	lp(x+17,y,7);
	lp(x+20,y,7);
	lp(x+22,y,7);
	// line 4
	y++;
	lp(x,y,7);
	lp(x+2,y,7);
	lp(x+15,y,7);
	lp(x+17,y,7);
	lp(x+20,y,7);
	lp(x+22,y,7);
	// line 5
	y++;
	lp(x,y,7);
	lp(x+2,y,7);
	lp(x+15,y,7);
	lp(x+17,y,7);
	lp(x+20,y,7);
	lp(x+22,y,7);
	// line 6
	y++;
	lp(x,y,7);
	lp(x+2,y,7);
	lp(x+5,y,4);
	for (int i = 6; i < 12; i++)
	{
		lp(x+i,y,5);
	}
	lp(x+12,y,6);
	lp(x+15,y,8);
	lp(x+16,y,5);
	lp(x+17,y,9);
	lp(x+20,y,7);
	lp(x+22,y,7);
	// line 7
	y++;
	lp(x,y,7);
	lp(x+2,y,7);
	lp(x+5,y,7);
	lp(x+12,y,7);
	lp(x+20,y,7);
	lp(x+22,y,7);
	// line 8
	y++;
	lp(x,y,7);
	lp(x+2,y,7);
	lp(x+5,y,7);
	lp(x+7,y,4);
	lp(x+8,y,5);
	lp(x+9,y,5);
	lp(x+10,y,6);

	lp(x+12,y,7);
	lp(x+20,y,7);
	lp(x+22,y,7);
	// line 9
	y++;
	lp(x,y,7);
	lp(x+2,y,7);
	lp(x+5,y,7);
	lp(x+7,y,7);
	lp(x+10,y,8);
	lp(x+11,y,5);
	lp(x+12,y,9);

	lp(x+15,y,4);
	lp(x+16,y,5);
	lp(x+17,y,6);
	
	lp(x+20,y,7);
	lp(x+22,y,7);
	// line 10
	y++;
	lp(x,y,7);
	lp(x+2,y,7);
	lp(x+5,y,7);
	lp(x+7,y,7);

	lp(x+15,y,7);
	lp(x+17,y,7);

	lp(x+20,y,7);
	lp(x+22,y,7);
	// line 11
	y++;
	lp(x,y,7);
	lp(x+2,y,7);
	lp(x+5,y,7);
	lp(x+7,y,8);
	lp(x+8,y,5);
	lp(x+9,y,5);
	lp(x+10,y,5);
	lp(x+11,y,5);
	lp(x+12,y,6);

	lp(x+15,y,7);
	lp(x+17,y,8);
	lp(x+18,y,5);
	lp(x+19,y,5);
	lp(x+20,y,9);
	lp(x+22,y,7);


}

_voidCallback *v_int(void)
{
	//VDP_setPaletteColor(0,col);	
	//col_puts(0,1,"Got int...");
	col = col_off;
	return;
}	

_voidCallback *h_int(void)
{
	VDP_setPaletteColor(14,col);
	col += 0x002;
	return; 
}

void setup(void)
{
	VDP_init();
	col_init();

	SYS_disableInts();
	SYS_setInterruptMaskLevel(0);
	SYS_setVIntCallback(v_int);
	VDP_setHInterrupt(0);
	SYS_setHIntCallback(h_int);
	SYS_enableInts();
	VDP_setScreenWidth256();
	VDP_setPlanSize(32,32);
}

int main(void)
{
	u16 assholes = 0;
	setup();
	VDP_setPaletteColor(0,0x000);
	VDP_setPaletteColor(1,0x666);
	VDP_setPaletteColor(2,0xAAA);
	VDP_setPaletteColor(3,0xEEE);
	VDP_setHIntCounter(hint_val);
	volatile u8 p1 = pad_read(0);
	col_puts(2,2,"Welcome to Computer Science House!");
	
	putCSHLogo(4, 2);

	VDP_setHInterrupt(1);
	u16 delay = 0;
	u8 dir = 0;
	for (;;)
	{
		VDP_setHInterrupt(1);
		VDP_waitVSync();
		VDP_setHInterrupt(0);
		delay++;
		if (delay == 512)
		{
			hint_val++;
			VDP_setHIntCounter(hint_val);

		delay = 0;
		}		
		if (delay % 2 == 0)
		{
			col_off += 0x002;
		}
	}
	return 0;	
}

/* vim: set noet: */