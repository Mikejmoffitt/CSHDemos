#include <genesis.h>
#include "col.h"
#include "mpad.h"
#include "sprites.h"
#include "awful.h"

u16 hint_val = 3;
u16 col = 0;
u16 col_off = 0;
u16 phrase_num = 0;

#define PAL_LEN (53 - 15)
const u16 palette[] = 
{
	0x00E,
	0x02E,
	0x04E,
	0x06E,
	0x08E,
	0x0AE,
	0x0CE,
	0x0EE,
	0x0EC,
	0x0EA,
	0x0E8,
	0x0E6,
	0x2E4,
	0x4E0,
	0x6E0,
	0x8E0,
	0xAE0,
	0xCE0,
	0xEE0,
	0xEC0,
	0xEA0,
	0xE80,
	0xE60,
	0xE40,
	0xE20,
	0xE00,
	0xE02,
	0xE04,
	0xE06,
	0xE08,
	0xE0A,
	0xE0C,
	0xE0E,
	0xC0E,
	0xA0E,
	0x80E,
	0x60E,
	0x40E,
	0x20E
};

volatile u16 vbl_wait;

_voidCallback *v_int(void)
{
	vbl_wait = 0;
	return NULL;
}	

_voidCallback *h_int(void)
{
	VDP_setPaletteColor(14,palette[col]);
	col++;
	while (col >= PAL_LEN)
	{
		col -= PAL_LEN;
	}
	return NULL; 
}

void setup(void)
{
	// Initialize Sega VDP
	VDP_init();

	// Configure the screen with to 40 columns
	VDP_setScreenWidth320();

	// Configure background planes to be 64 x 32 cells
	VDP_setPlanSize(64,32);

	// Initialize column text output (DMA graphic tiles)
	col_init();

	// Disable interrupts during configuration
	SYS_disableInts();

	// Allow all three interrupts
	SYS_setInterruptMaskLevel(0);

	// Set pointers to interrupt service routines
	SYS_setVIntCallback((_voidCallback *)v_int);
	SYS_setHIntCallback((_voidCallback *)h_int);

	// Now we can enable interrupts
	SYS_enableInts();

	// Configure the screen with to 40 columns
	VDP_setScreenWidth320();

	// Configure background planes to be 64 x 32 cells
	VDP_setPlanSize(64,32);

}

const char* phrases[] = 
{
	"         Getting more done after 2:00 AM than most people do all day.   ",
	"                         Social versus Technical!                       ",
	"             68K blows the '88 away! Welcome to Motorola Zone!          ",
	"                        I said hey! What's going on?!                   ",
	"      Why buy something when you can do it yourself for twice the cost? ",
	"                       We're working on drink, we swear!                ",
	"         Lean synergy-driven agile development to leverage our product. ",
	"                          Can you hear my microphone?                   ",
	"                         Microsoft wouldn't do that...                  ",
	0

};

static inline void print_phrase(u16 p)
{
	col_puts(0,26,phrases[p]);
}

#define NUM_STARS 64

typedef struct star star;
struct star
{
	u16 x;
	u16 y;
	u16 size;
	u8 speed;
	u8 offset;
};

static void process_stars(star *stars)
{
	for (int i = 0; i < NUM_STARS; i++)
	{
		stars[i].x = stars[i].x + stars[i].speed;
		if (stars[i].x >= 320)
		{
			stars[i].x = 0;
			stars[i].y = GET_HVCOUNTER%256;
		}
		sprite_put(stars[i].x, stars[i].y,  SPRITE_SIZE(1,1), stars[i].size);
	}
}

int main(void)
{
	u16 delay_mod = 4;
	u16 col_inc_cnt = 0;
	setup();
	VDP_setPaletteColor(0,0x000);
	VDP_setPaletteColor(1,0x444);
	VDP_setPaletteColor(2,0x888);
	VDP_setPaletteColor(3,0xEEE);
	VDP_setHIntCounter(hint_val);
	volatile u8 p1 = pad_read(0);
	VDP_setHInterrupt(0);
	sprites_init();

	col_puts40(8,0,"Computer Science House");

	awful_put_logo(8, 2);

	star stars[NUM_STARS];
	u16 i = 0;
	for (i = 0; i < NUM_STARS; i++)
	{
		stars[i].x = i * 5;
		stars[i].y = 128 + i * 8;
		stars[i].speed = (i % 7) + 1;
		stars[i].offset = (3 * i) % 4;
		stars[i].size = (i % 4 == 0) ? ('.' + COL_FONT_VRAM_OFFSET) : (128 + '.' + COL_FONT_VRAM_OFFSET);
	}

	print_phrase(8);
	u16 delay = 0;
	u8 dir = 0;
	VDP_setHInterrupt(1);
	for (;;)
	{
		delay++;
		if (col_inc_cnt == 0)
		{
			col_inc_cnt = hint_val;
			col_off += 0x002;
		}
		else
		{
			col_inc_cnt--;
		}
		if (delay == 512)
		{
			if (phrase_num == 8)
			{
				phrase_num = 0;
			}
			hint_val++;
			if (hint_val == 10)
			{
				hint_val = 3;
			}
			delay_mod = delay_mod >> 1;
			if (delay_mod == 0)
			{
				delay_mod = delay_mod = 4;
			}
			VDP_setHIntCounter(hint_val);
			VDP_setHInterrupt(0);
			print_phrase(phrase_num);
			VDP_setHInterrupt(1);
			phrase_num++;

			delay = 0;
		}	
		process_stars(&stars);
		while (vbl_wait)
		{	
			__asm__("nop");
		}
		VDP_setHInterrupt(0);
		VDP_setPaletteColor(14,palette[col]);
		col = col_off;
		vbl_wait = 1;
		sprites_dma_simple();
		VDP_setHInterrupt(1);
	}
	return 0;	
}

/* vim: set noet: */
