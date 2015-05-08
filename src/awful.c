#include "awful.h"

void awful_put_logo(u16 x, u16 y)
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
	// line 12
	y++;
	lp(x,y,7);
	lp(x+2,y,7);

	lp(x+5,y,7);
	lp(x+12,y,7);
	lp(x+15,y,7);
	lp(x+22,y,7);
	// line 13
	y++;
	lp(x,y,7);
	lp(x+2,y,7);

	lp(x+5,y,8);
	lp(x+6,y,5);
	lp(x+7,y,5);
	lp(x+8,y,5);
	lp(x+9,y,5);
	lp(x+10,y,6);
	lp(x+12,y,7);
	lp(x+15,y,7);
	lp(x+17,y,4);
	lp(x+18,y,5);
	lp(x+19,y,5);
	lp(x+20,y,6);
	lp(x+22,y,7);
	// line 14
	y++;
	lp(x,y,7);
	lp(x+2,y,7);

	lp(x+10,y,7);
	lp(x+12,y,7);
	lp(x+15,y,7);
	lp(x+17,y,7);
	lp(x+20,y,7);
	lp(x+22,y,7);
	// line 15
	y++;
	lp(x,y,7);
	lp(x+2,y,7);

	lp(x+5,y,4);
	lp(x+6,y,5);
	lp(x+7,y,6);
	lp(x+10,y,7);
	lp(x+12,y,7);
	lp(x+15,y,8);
	lp(x+16,y,5);
	lp(x+17,y,9);
	lp(x+20,y,7);
	lp(x+22,y,7);
	// line 16
	y++;
	lp(x,y,7);
	lp(x+2,y,7);

	lp(x+5,y,7);
	lp(x+7,y,8);
	lp(x+8,y,5);
	lp(x+9,y,5);
	lp(x+10,y,9);
	lp(x+12,y,7);
	lp(x+20,y,7);
	lp(x+22,y,7);
	// line 17
	y++;
	lp(x,y,7);
	lp(x+2,y,7);

	lp(x+5,y,7);
	lp(x+12,y,7);
	lp(x+20,y,7);
	lp(x+22,y,7);
	// line 18
	y++;
	lp(x,y,7);
	lp(x+2,y,7);

	lp(x+5,y,8);
	lp(x+6,y,5);
	lp(x+7,y,5);
	lp(x+8,y,5);
	lp(x+9,y,5);
	lp(x+10,y,5);
	lp(x+11,y,5);
	lp(x+12,y,9);
	lp(x+15,y,4);
	lp(x+16,y,5);
	lp(x+17,y,6);
	lp(x+20,y,7);
	lp(x+22,y,7);
	
	
	// line 19
	y++;
	lp(x,y,7);
	lp(x+2,y,7);
	lp(x+15,y,7);
	lp(x+17,y,7);
	lp(x+20,y,7);
	lp(x+22,y,7);
	// line 19
	y++;
	lp(x,y,7);
	lp(x+2,y,7);
	lp(x+15,y,7);
	lp(x+17,y,7);
	lp(x+20,y,7);
	lp(x+22,y,7);


	// line 20
	y++;
	lp(x,y,7);
	lp(x+2,y,8);
	for (int i = 3; i < 15; i++)
	{
		lp(x+i,y,5);
	}
	lp(x+15,y,9);
	lp(x+17,y,7);
	lp(x+20,y,7);
	lp(x+22,y,7);
	
	

	// line 21
	y++;
	lp(x,y,7);
	lp(x+17,y,7);
	lp(x+20,y,7);
	lp(x+22,y,7);
	
	
	// Line 22
	
	y++;
	lp(x,y,8); // corner TL
	for (u16 i = 1; i < 17; i++)
	{
		lp(x + i,y,5);
	}
	lp(x + 17,y,9);
	lp(x + 20,y,8);
	lp(x + 21,y,5);
	lp(x + 22,y,9);



}


