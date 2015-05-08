#include <genesis.h>
#include "col.h"
#include "mpad.h"
#include "sprites.h"
#include "awful.h"

u16 hint_val = 1;
u16 col = 0;
u16 col_off = 0;
u16 phrase_num = 0;

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
	SYS_setVIntCallback(v_int);
	SYS_setHIntCallback(h_int);

	// Now we can enable interrupts
	SYS_enableInts();

	// Configure the screen with to 40 columns
	VDP_setScreenWidth320();

	// Configure background planes to be 64 x 32 cells
	VDP_setPlanSize(64,32);

}

const char* phrases[] = 
{
	"test1",
	"test2",
	"test3"
};

void print_phrase(u16 p)
{
	col_puts(0,26,"                                                                                        ");
	switch(p)
	{
		case 0:
			col_puts(0,26,"         Getting more done after 2:00 AM than most people do all day.");
			break;
		case 1:
			col_puts(0,26,"                         Social versus Technical!  ");
			break;
		case 2:
			col_puts(0,26,"             68K blows the '88 away! Welcome to Motorola Zone!     ");
			break;
		case 3:
			col_puts(0,26,"                        I said hey! What's going on?!       ");
			break;
		case 4:
			col_puts(0,26,"      Why buy something when you can do it yourself for twice the cost? ");
			break;
		case 5:
			col_puts(0,26,"                       We're working on drink, we swear!   ");
			break;
		case 6:
			col_puts(0,26,"         Lean synergy-driven agile development to leverage our product.  ");
			break;
		case 7:
			col_puts(0,26,"                          Can you hear my microphone? ");
			break;
		case 8:
			col_puts(0,26,"                         Microsoft wouldn't do that... ");
			break;

	}
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

int main(void)
{
	u16 assholes = 0;
	u16 delay_mod = 4;
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
		VDP_waitVSync();
		VDP_setHInterrupt(0);
		sprites_dma(NUM_STARS + 1);
		VDP_setHInterrupt(1);
		delay++;

		/*
		if (delay % 128 == 0)
		{
			delay_mod = delay_mod >> 1;
			if (delay_mod == 1)
			{

				delay_mod = 32;
			}
		}
		*/
		if (delay == 2048)
		{
			if (phrase_num == 8)
			{
				phrase_num = 0;
			}
			hint_val++;
			if (hint_val == 12)
			{
				hint_val = 2;
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
		if (delay % delay_mod == 0)
		{
			col_off += 0x002;
		}


		for (i = 0; i < NUM_STARS; i++)
		{
			stars[i].x = stars[i].x + stars[i].speed;
			if (stars[i].x >= 320)
			{
				stars[i].x = 0;
				stars[i].y = stars[i].y + stars[i].offset;
			}
			if (stars[i].y > 256)
			{
				stars[i].y-=256;
			}
			sprite_set(i, stars[i].x, stars[i].y,  SPRITE_SIZE(1,1), stars[i].size,i + 1);
		}

	}
	return 0;	
}

/* vim: set noet: */
