#include "col.h"

void col_init(void)
{
	VDP_doVRamDMA(gfx_font,COL_FONT_VRAM_OFFSET,16 * 256);

	VDP_setHorizontalScroll(PLAN_B,4);
}

void col_puts(u8 x, u8 y, char *s)
{
	u8 orig_x = x;
	while(*s)
	{
		if (*s == '\n')
		{
			y++;
			x = orig_x;
		}
		else
		{
			VDP_setTileMapXY(
				VDP_PLAN_A,
				TILE_ATTR_FULL(0,0,0,0,
				(*s + COL_FONT_SEL + (COL_FONT_VRAM_OFFSET/32))),
				x,y);
		}
		s++;
		if (*s == '\n')
		{
			y++;
			x = orig_x;
			s++;
		}
		else if (*s)
		{
			VDP_setTileMapXY(
				VDP_PLAN_B,
				TILE_ATTR_FULL(0,0,0,0,
				(*s + COL_FONT_SEL + (COL_FONT_VRAM_OFFSET/32))),
				x,y);
			s++;
			x++;
		}
	}
}

/* vim: set noet: */
