#include "batz.h"              /* where program specific stuff is defined */

int button_downx,button_downy,button_number;

void button_down(Widget ww, int which_button, int x, int y, void *data)
	{
	/*MotionCB      motion;*/
	
	MyProgram *me = (MyProgram *)data;
	button_downx = x;
	button_downy = y;
	button_number = which_button;
	/*printf("You clicked button %d at (%d,%d)", which_button, x,y); */
  	/*SetMouseMotionCB(ww, motion);*/
	}

void button_up(Widget ww, int which_button, int x, int y, void *data)
	{
	MyProgram *me = (MyProgram *)data;
	float daxx,daxy,dinx,diny;
	
	/*printf("You released button %d at (%d,%d)\n", which_button, x,y);*/
	
	daxx = baxx;
	daxy = baxy;
	dinx = binx;
	diny = biny;
	
	if (which_button == 1)
		{
		/*bouton gauche actionne : zoom sur le rectangle autour de la diagonale cliquee*/
		
		/*cas ou le rectangle a une surface non nulle*/
		if (x < button_downx) 
			{
			binx = dinx + (float) (x           ) / RESOLUTION_X_FEN  * (daxx - dinx);
			baxx = dinx + (float) (button_downx) / RESOLUTION_X_FEN  * (daxx - dinx);
			}
		if (x > button_downx) 
			{
			binx = dinx + (float) (button_downx) / RESOLUTION_X_FEN  * (daxx - dinx);
			baxx = dinx + (float) (x           ) / RESOLUTION_X_FEN  * (daxx - dinx);
			}
		if (y > button_downy) 
			{
			biny = daxy + (float) (y           ) / RESOLUTION_Y_FEN  * (diny - daxy);
			baxy = daxy + (float) (button_downy) / RESOLUTION_Y_FEN  * (diny - daxy);
			}
		if (y < button_downy) 
			{
			biny = daxy + (float) (button_downy) / RESOLUTION_Y_FEN  * (diny - daxy);
			baxy = daxy + (float) (y           ) / RESOLUTION_Y_FEN  * (diny - daxy);
			}
		/*consevation de la meme echelle en x et en y*/
		if (((baxx - binx)*RESOLUTION_Y_FEN)>((baxy - biny)*RESOLUTION_X_FEN))
			{
			baxy = biny + (baxx - binx) * RESOLUTION_Y_FEN / RESOLUTION_X_FEN;
			}
		else
			{
			baxx = binx + (baxy - biny) * RESOLUTION_X_FEN / RESOLUTION_Y_FEN;
			}
			
			
		/*cas ou le rectangle a une surface  nulle*/
		if (x == button_downx || y == button_downy) 
			{
			binx = cinx - marge * (caxx - cinx);
			biny = ciny - marge * (caxy - ciny);
			baxx = caxx + marge * (caxx - cinx);
			baxy = caxy + marge * (caxy - ciny);
			}
			
		if (ARTICLE_HEXA_2001 == 1)
			{
			/*binx = cinx - 0.1 * (caxx - cinx);
			biny = ciny - 0.1 * (caxy - ciny);
			baxx = caxx + 0.8 * (caxx - cinx);
			baxy = caxy + 0.8 * (caxy - ciny);*/
			}


		if ((baxx - binx) > (baxy - biny)) bcartmax = baxx - binx;
		if ((baxy - biny) > (baxx - binx)) bcartmax = baxy - biny;
		printf("binx %8.2f biny %8.2f ",binx,biny);
		printf("baxx %8.2f baxy %8.2f \n",baxx,baxy); 
		/*printf("RESOLUTION_X_FEN %8.2f RESOLUTION_Y_FEN %8.2f \n",RESOLUTION_X_FEN,RESOLUTION_Y_FEN);*/
		}
	if (which_button == 3)
		{
		/*bouton droit actionne : deplacement de la figure du segment clique*/
		binx = binx + (float) (button_downx - x) / RESOLUTION_X_FEN  * (daxx - dinx);
		baxx = baxx + (float) (button_downx - x) / RESOLUTION_X_FEN  * (daxx - dinx);
		biny = biny + (float) (button_downy - y) / RESOLUTION_Y_FEN  * (diny - daxy);
		baxy = baxy + (float) (button_downy - y) / RESOLUTION_Y_FEN  * (diny - daxy);
		printf("binx %8.2f biny %8.2f ",binx,biny);
		printf("baxx %8.2f baxy %8.2f \n",baxx,baxy); 
		/*printf("RESOLUTION_X_FEN %8.2f RESOLUTION_Y_FEN %8.2f \n",RESOLUTION_X_FEN,RESOLUTION_Y_FEN);*/
		}
	
	if (baxx - binx == 0.0) { printf("baxx - binx = 0.0   \n"); exit(0); }
	if (baxy - biny == 0.0) { printf("baxx - binx = 0.0   \n"); exit(0); }
  	SetMouseMotionCB(ww, NULL);
	dessiner();
	}

