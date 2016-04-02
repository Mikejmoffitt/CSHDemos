#include <genesis.h>
#include "music.h"
#include "col.h"
#include "mpad.h"
#include "sprites.h"
#include "awful.h"

u16 hint_val = 3;
u16 col = 0;
u16 col_off = 0;
u16 phrase_num = 0;
u16 scroll_off = 0;
s16 dscroll = 0;
u16 term_pos = 0;
u16 term_scrolling = 0;
volatile u16 vbl_wait;

// Rainbow cycling palette
#define PAL_LEN (54 - 16)
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


void term_print(const char *s, u16 frames)
{
	col_puts(0,term_pos++ % 32, s);
	if (term_pos >= 28)
	{
		VDP_setVerticalScroll(PLAN_A, (term_pos - 28) << 3);
		VDP_setVerticalScroll(PLAN_B, (term_pos - 28) << 3);
		col_puts(0, term_pos % 32, "                                                                                ");
	}

	while (frames--)
	{	
		while (vbl_wait)
		{	
			__asm__("nop");
		}
		vbl_wait = 1;
	}
}

void bios_boot_demo(void)
{
	VDP_clearPlan(VDP_PLAN_A, 0);
	VDP_clearPlan(VDP_PLAN_B, 0);
	VDP_setHInterrupt(0);
	term_print("  ___   ___  ___   ___     ___   ___       ___  ___     ___", 1);
	term_print(" |___  |__  |  _  |___|   |  _  |__  |\\ | |__  |___  | |___ ", 1);
	term_print("  ___| |___ |___| |   |   |___| |___ | \\| |___  ___| |  ___|", 1);
	term_print("", 20);
	term_print(" Entry Vector 0x202", 2);
	term_print(" CSHBIOS(C)2016 Computer Science House", 2);
	term_print(" MD-VA6 BOOT ROM Revision 3", 30);
	term_print("", 0);
	term_print(" CPU1 : Motorola 68000 7.6MHz", 2);
	term_print("   Speed : 7.61 MHz", 2);
	term_print("", 0);
	term_print(" CPU2 : Zilog Z80 3.8MHz", 2);
	term_print("   Speed : 3.80 MHz", 60);
	term_print("", 0);

	term_print(" Press DEL to run Setup", 0);
	term_print(" Press <F8> for BBS POPUP", 170);
	term_print("", 0);

	term_print(" SRAM Asynchronous 2 x 65256 (64k x 8), single channel, parallel", 16);
	term_print("  Checking SRAM...", 60);
	term_print(" 8K  OK", 7);
	term_print(" 16K OK", 7);
	term_print(" 24K OK", 7);
	term_print(" 32K OK", 7);
	term_print(" 40K OK", 7);
	term_print(" 48K OK", 7);
	term_print(" 56K OK", 7);
	term_print(" 64K OK", 60);
	term_print("", 0);

	term_print(" VDP : Sega 315-5313 (Yamaha YM7101)", 2);
	term_print("   Speed: 56MHz", 2);
	term_print("   VRAM: 64K Serial Out Parallel Load DRAM", 2);
	term_print("   CRAM: 64 x 9", 2);
	term_print("   TMSS Enabled", 1);
	term_print("", 60);
	term_print(" 0xC00000 : Data Port", 20);
	term_print(" 0xC00004 : Control Port", 20);
	term_print(" 0xC00008 : H/V counter", 20);
	term_print(" 0xC00011 : SN76489", 20);
	term_print(" 0xC0001C : Debug Register", 70);
	term_print("", 0);
	term_print(" Starting demo...", 120);
}


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

_voidCallback *h_int_scroll(void)
{
	if (scroll_off > 200)
	{
		VDP_setPaletteColor(14, 0);
	}
	scroll_off += dscroll;
	VDP_setVerticalScroll(PLAN_A, scroll_off);
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
	"                       Microsoft wouldn't do that...                    ",
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

void startup_stretch(void)
{
	SYS_setHIntCallback((_voidCallback *)h_int_scroll);
	VDP_setHIntCounter(3);
	VDP_setHInterrupt(1);


	u16 counter = 240;
	while (counter--)
	{
		while (vbl_wait)
		{	
			__asm__("nop");
		}
		VDP_setHInterrupt(0);
		VDP_setPaletteColor(14,palette[counter % 32]);
		vbl_wait = 1;
		counter--;
		scroll_off = 0;
		dscroll = counter / 4;
		VDP_setHInterrupt(1);
	}
	VDP_setHInterrupt(0);
}



int main(void)
{
	music_init();
	music_play(3);
	u16 delay_mod = 4;
	u16 col_inc_cnt = 0;
	setup();
reset_demo:
	sprites_dma_simple();
	term_pos = 0;
	VDP_setHInterrupt(0);

	VDP_clearPlan(VDP_PLAN_A, 0);
	VDP_clearPlan(VDP_PLAN_B, 0);
	// Greyscale palette for text
	VDP_setPaletteColor(0,0x000);
	VDP_setPaletteColor(1,0x444);
	VDP_setPaletteColor(2,0x888);
	VDP_setPaletteColor(3,0xEEE);

	bios_boot_demo();
	VDP_clearPlan(VDP_PLAN_A, 0);
	VDP_clearPlan(VDP_PLAN_B, 0);


	awful_put_logo(8, 2);
	startup_stretch();

	VDP_setVerticalScroll(PLAN_A, 252);
	VDP_setVerticalScroll(PLAN_B, 252);

	VDP_setHIntCounter(hint_val);
	SYS_setHIntCallback((_voidCallback *)h_int);
	volatile u8 p1 = pad_read(0);
	sprites_init();

	col_puts40(8,0,"Computer Science House");

	// Initialize background stars
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
				goto reset_demo;
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
