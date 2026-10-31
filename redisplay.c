#define PRINCIPAL 0
#include "phobos.h"

void redisplay(Widget w, int new_width, int new_height, void *data)
	{
	MyProgram *me = data;
	RESOLUTION_X_FEN = (float)new_width ;
	RESOLUTION_Y_FEN = (float)new_height ;
	dessiner();
	}












