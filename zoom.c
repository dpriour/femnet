#define PRINCIPAL 0
#include "phobos.h"              /* where program specific stuff is defined */

int button_downx,button_downy,button_number,motion_x,motion_y;

void add_link()
	{
   	SetMouseMotionCB(w[4], motion);
	printf("mouse at (%d,%d)\n", motion_x,motion_y);
	}

void motion(Widget w, int x, int y, void *data)
	{
	int pa,no,deb,x1,y1,x2,y2,xt,yt;
	int pa1,no1,pa2,no2;
  	static int oldx = 0, oldy = 0;
  	float dist1,dist2,distt;
  	char str[1];

  	oldx = x;
  	oldy = y;
	motion_x = x;
	motion_y = y;
	
	if (Structure.NbTypesurf != 0)
		{
		deb = panneau[1].noeud_contour[1];
		}
	if (Structure.NbTypeelem != 0)
		{
		//deb = element[1].extremite[1];
		}

	xt = (int) ((noeud[deb].x - binx) / (baxx - binx) * RESOLUTION_X_FEN);
	yt = (int) ((noeud[deb].y - baxy) / (biny - baxy) * RESOLUTION_Y_FEN);
	distt = (float) sqrt((x-xt)*(x-xt)+(y-yt)*(y-yt));
	dist1 = distt;
	x1 = xt;
	y1 = yt;
	str[0] = 'p';
	pa1 = pa;
	no1 = no;
	//printf("mouse at (%d,%d) deb %d x1,y1, (%d,%d) dist1 %f x,y %f,%f\n", x,y,deb,x1,y1,dist1,noeud[deb].x,noeud[deb].y);
	//printf("binx baxx %f,%f\n",binx,baxx);
	//printf("biny baxy %f,%f\n",biny,baxy);
	
	for (pa=1;pa<=Structure.NbTypesurf;pa++)
		{ 
		if ((panneau[pa].flag_dessin != 0) && (plan.do_it != 1))
			{
			for (no=1;no<=panneau[pa].nb_noeud_contour;no++)
				{ 
				deb = panneau[pa].noeud_contour[no];
				xt = (int) ((noeud[deb].x - binx) / (baxx - binx) * RESOLUTION_X_FEN);
				yt = (int) ((noeud[deb].y - baxy) / (biny - baxy) * RESOLUTION_Y_FEN);
				distt = (float) sqrt((x-xt)*(x-xt)+(y-yt)*(y-yt));
				if (distt < dist1)
					{
					Color(WHITE);
					DrawBox(x1-5,y1-5,10,10);
					dist1 = distt;
					x1 = xt;
					y1 = yt;
					str[0] = 'p';
					pa1 = pa;
					no1 = no;
					Color(BLACK);
					DrawBox(x1-5,y1-5,10,10);
					printf("pa no (%4d,%4d) deb %4d dist1 %f\n", pa,no,deb,dist1);
					}
				}
			}
		}

	
	
	
	
	
	//Color(BLACK);
	//DrawBox(x,y,10,10);
	
	//dessiner();

	//Color(WHITE);
	//DrawBox(x,y,10,10);
	}

void button_down(Widget w, int which_button, int x, int y, void *data)
{
	MyProgram *me = (MyProgram *)data;
	button_downx = x;
	button_downy = y;
	button_number = which_button;
  	/* SetMouseMotionCB(w, motion);*/
	/*printf("You clicked button %d at (%d,%d)", which_button, x,y); */ 
}

void button_up(Widget w, int which_button, int x, int y, void *data)
{
	MyProgram *me = (MyProgram *)data;
	float caxx,caxy,cinx,ciny,CX,CY;
	
	/*printf("You released button %d at (%d,%d)\n", which_button, x,y); */
	
	caxx = baxx;
	caxy = baxy;
	cinx = binx;
	ciny = biny;
	
	CX = cinx + (float) (x           ) / RESOLUTION_X_FEN  * (caxx - cinx);
	CY = caxy + (float) (y           ) / RESOLUTION_Y_FEN  * (ciny - caxy);
	
	printf("You released button %d at (%f,%f)\n", which_button, CX,CY); /* */
	
	
	if (which_button == 1)
		{
		/*bouton gauche actionne : zoom autour du segment clique*/
		if (x < button_downx) 
			{
			binx = cinx + (float) (x           ) / RESOLUTION_X_FEN  * (caxx - cinx);
			baxx = cinx + (float) (button_downx) / RESOLUTION_X_FEN  * (caxx - cinx);
			}
		if (x > button_downx) 
			{
			binx = cinx + (float) (button_downx) / RESOLUTION_X_FEN  * (caxx - cinx);
			baxx = cinx + (float) (x           ) / RESOLUTION_X_FEN  * (caxx - cinx);
			}
		if (y > button_downy) 
			{
			biny = caxy + (float) (y           ) / RESOLUTION_Y_FEN  * (ciny - caxy);
			baxy = caxy + (float) (button_downy) / RESOLUTION_Y_FEN  * (ciny - caxy);
			}
		if (y < button_downy) 
			{
			biny = caxy + (float) (button_downy) / RESOLUTION_Y_FEN  * (ciny - caxy);
			baxy = caxy + (float) (y           ) / RESOLUTION_Y_FEN  * (ciny - caxy);
			}
		if (x == button_downx || y == button_downy) 
			{
			binx = minx - 0.05 * (maxx - minx);
			biny = miny - 0.05 * (maxy - miny);
			baxx = maxx + 0.05 * (maxx - minx);
			baxy = maxy + 0.05 * (maxy - miny);
			}
		if ((baxx - binx) > (baxy - biny)) bcartmax = baxx - binx;
		if ((baxy - biny) > (baxx - binx)) bcartmax = baxy - biny;
		}
		
	if (which_button == 3)
		{
		/*bouton droit actionne : deplacement de la figure du segment clique*/
		binx = binx + (float) (button_downx - x) / RESOLUTION_X_FEN  * (caxx - cinx);
		baxx = baxx + (float) (button_downx - x) / RESOLUTION_X_FEN  * (caxx - cinx);
		biny = biny + (float) (button_downy - y) / RESOLUTION_Y_FEN  * (ciny - caxy);
		baxy = baxy + (float) (button_downy - y) / RESOLUTION_Y_FEN  * (ciny - caxy);
		}
	
	dessiner();
	button_number = 0;
}

