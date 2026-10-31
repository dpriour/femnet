#include "batz.h"

void redisplay(Widget ww, int new_width, int new_height, void *data)
	{
	MyProgram *me = data;
	RESOLUTION_X_FEN = (float)new_width ;
	RESOLUTION_Y_FEN = (float)new_height;
	if (RESOLUTION_X_FEN == 0.0) { printf("RESOLUTION_X_FEN = 0.0   \n"); exit(0); }
	if (RESOLUTION_Y_FEN == 0.0) { printf("RESOLUTION_Y_FEN = 0.0   \n"); exit(0); }
	if (((baxx - binx)*RESOLUTION_Y_FEN)>((baxy - biny)*RESOLUTION_X_FEN))
		{
		baxy = biny + (baxx - binx) * RESOLUTION_Y_FEN / RESOLUTION_X_FEN;
		}
	else
		{
		baxx = binx + (baxy - biny) * RESOLUTION_X_FEN / RESOLUTION_Y_FEN;
		}
	dessiner();
	}
