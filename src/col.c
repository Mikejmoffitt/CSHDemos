#include "col.h"

void col_init(void)
{
	VDP_doVRamDMA((u32)gfx_font,COL_FONT_VRAM_OFFSET*32,16 * 256);

	VDP_setHorizontalScroll(PLAN_B,4);
}

void col_puts40(u16 x, u16 y, char *s)
{
	u16 orig_x = x;
	while(*s)
	{
		if (*s == '\n')
		{	
			y++;
			x = orig_x;
		}
		else if (*s == '\t')
		{
			x = x + 4;
		}
		else
		{
			VDP_setTileMapXY(
				VDP_PLAN_B,
				TILE_ATTR_FULL(0,0,0,0,
				(*s + (COL_FONT_VRAM_OFFSET))),
				x,y);	
			x++;
		}
		s++;
	}
}

void col_puts(u16 x, u16 y, char *s)
{
	u16 max = 80;
	u16 orig_x = x;
	register u32 flip = x % 2;
	while(*s)
	{
		max--;
		if (max == 0)
		{
			return;
		}
		if (*s == '\n')
		{	
			flip = orig_x % 2;
			y++;
			x = orig_x;
		}
		else if (*s == '\t')
		{
			x = x + 4;
		}
		else
		{
			VDP_setTileMapXY(
				(flip) ? VDP_PLAN_B : VDP_PLAN_A,
				TILE_ATTR_FULL(0,0,0,0,
				(*s + COL_FONT_SEL + (COL_FONT_VRAM_OFFSET))),
				x >> 1,y);	
			x++;
			flip = (flip) ? 0 : 1;
		}
		s++;
	}
}

/* vim: set noet: */
