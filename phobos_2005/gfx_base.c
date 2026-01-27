#define PRINCIPAL 0
#ifndef PAS_DE_VUE

/*#include "libsx_bf.h"*/
#include "phobos.h"

/* -----
   ----- Fonctions Graphiques 
   -----
*/
void Line_larg_ps(int n);
int ColorRGB(int r, int v, int b);
void ColorRGB_ps(int r, int v, int b);
void Color(int c);
void Color_ps(int c);
void Line(float x1,float y1,float x2, float y2);
void Line_ps(float x1,float y1,float x2,float y2);
void Move_to (float x,float y);
void Move_to_ps (float x1,float y1);
void Line_to (float x,float y);
void Line_to_ps (float x1,float y1);
void Line_end ();
void Line_end_ps ();
void Surface_end();
void Surface_end_ps ();
void Circle (float x,float y,float r);
void Circle_ps (float x1,float y1,float r);
void Text(float x,float y,char *str);
void Text_ps(float x,float y, char *s);
void Motif(int m);
void Motif_ps(char d[],int n);
void Size_font(int coef);
void Size_font_ps(int coef);
void Rectangle_plein(float x,float y, float l, float h);
void Rectangle_plein_ps(float x1,float y1, float x2,float y2);


#define NB_MAX_XPOINTS 10000
XPoint xpoints[NB_MAX_XPOINTS];
int nb_xpoints=0;

int ColorRGB(int r, int v, int b)
	{
	if (flag_ps == TRUE) ColorRGB_ps(r,v,b);
	return(GetRGBColor(r,v,b));
	}
	

void Color(int c)
	{
	if (flag_ps == TRUE) Color_ps(c);
	SetColor(c);		
	}

void Line(float x1,float y1,float x2, float y2)
	{
	float fx1,fy1;
	float fx2,fy2;
	float dx,dy;
	
	if (flag_delta_carac == TRUE)
		{
		dx =  (float)(taille_police_x*delta_caract_x/2);
		dy =  (float)(taille_police_y*delta_caract_y/2);
		}
	else
		{
		dx=0;
		dy=0;
		}

	DrawLine(
 	        (int)       		(  RESOLUTION_X_FEN * x1 )/RESOLUTION_X+dx,
		(int) RESOLUTION_Y_FEN -(( RESOLUTION_Y_FEN * y1 )/RESOLUTION_Y+dy),
		(int) 	                (  RESOLUTION_X_FEN * x2 )/RESOLUTION_X+dx,
		(int) RESOLUTION_Y_FEN -(( RESOLUTION_Y_FEN * y2 )/RESOLUTION_Y+dy)
		);

	if (flag_ps == TRUE) Line_ps(x1,y1,x2,y2);
	}

void Move_to (float x,float y)
	{
	float dx,dy;


	if (flag_delta_carac == TRUE)
		{
		dx = (float)(taille_police_x*delta_caract_x/2);
		dy = (float)(taille_police_y*delta_caract_y/2);
		}
	else
		{
		dx=0;
		dy=0;
		}
	nb_xpoints=1;

	xpoints[0].x = (int)( 	                ( RESOLUTION_X_FEN * x )/RESOLUTION_X+dx);
	xpoints[0].y = (int)(RESOLUTION_Y_FEN -(( RESOLUTION_Y_FEN * y )/RESOLUTION_Y+dy));
	if (flag_ps == TRUE) Move_to_ps(x,y);

	}

void Line_to (float x,float y)
	{
	float dx,dy;

	if (flag_ps == TRUE) Line_to_ps(x,y);

	if (flag_delta_carac == TRUE)
		{
		dx =(float)(taille_police_x*delta_caract_x/2);
		dy =(float)(taille_police_y*delta_caract_y/2);
		}
	else
		{
		dx=0;
		dy=0;
		}
	
	xpoints[nb_xpoints].x = (int)(                   ( RESOLUTION_X_FEN * x )/RESOLUTION_X+dx);
	xpoints[nb_xpoints].y = (int)(RESOLUTION_Y_FEN -(( RESOLUTION_Y_FEN * y )/RESOLUTION_Y+dy));
	if (nb_xpoints < NB_MAX_XPOINTS) nb_xpoints++;
	}

void Line_end ()
	{
  	DrawPolyline(xpoints, nb_xpoints);             
	if (flag_ps == TRUE) Line_end_ps();
	}
	
void Surface_end()
	{
	DrawFilledPolygon(xpoints,nb_xpoints);
	if (flag_ps == TRUE) Surface_end_ps();
	}

void Circle (float x,float y,float r)
	{
	float dx,dy;

	if (flag_delta_carac == TRUE)
		{
		dx =  (float)(taille_police_x*delta_caract_x/2);
		dy =  (float)(taille_police_y*delta_caract_y/2);
		}
	else
		{
		dx=0;
		dy=0;
		}


	DrawArc(
		 (int)(	                   ( RESOLUTION_X_FEN * x )/RESOLUTION_X+dx),
		 (int)(RESOLUTION_Y_FEN - (( RESOLUTION_Y_FEN * y )/RESOLUTION_Y+dy)),
		 (int)r,(int)r,0,360);
	if (flag_ps == TRUE) Circle_ps(x,y,r);
	}

void Text(float x,float y,char *str)
	{
	float fx,fy;
	float dx,dy;

	if (flag_delta_carac == TRUE)
		{
		dx =  (float)(taille_police_x*delta_caract_x/2);
		dy =  (float)(taille_police_y*delta_caract_y/2);
		}
	else
		{
		dx=0;
		dy=0;
		}
	
	if (flag_ps == TRUE) Text_ps(x,y,str) ; 

  	DrawText(str, 
		(int)(                    ( RESOLUTION_X_FEN * x )/RESOLUTION_X+dx),
		(int)(RESOLUTION_Y_FEN - (( RESOLUTION_Y_FEN * y )/RESOLUTION_Y+dy)) 
		);
	}

void Motif(int m)
	{
	static char first = TRUE;

	if (first == TRUE)
		{
		first = FALSE;
		ligne_motif[0][0] = 0;ligne_motif[0][1] = 1;ligne_motif[0][2] = 1;
		ligne_motif[1][0] = 2;ligne_motif[1][1] = 5;ligne_motif[1][2] = 5;
		ligne_motif[2][0] = 2;ligne_motif[2][1] = 2;ligne_motif[2][2] = 2;
		ligne_motif[3][0] = 4;ligne_motif[3][1] = 5;ligne_motif[3][2] = 5; ligne_motif[3][3] = 2;ligne_motif[3][4] = 2;
		ligne_motif[4][0] = 4;ligne_motif[4][1] = 5;ligne_motif[4][2] = 2; ligne_motif[4][3] = 2;ligne_motif[4][4] = 5; 
		ligne_motif[5][0] = 4;ligne_motif[5][1] = 5;ligne_motif[5][2] = 1; ligne_motif[5][3] = 5;ligne_motif[5][4] = 5; 
		ligne_motif[6][0] = 4;ligne_motif[6][1] = 5;ligne_motif[6][2] = 5; ligne_motif[6][3] = 1;ligne_motif[6][4] = 5; 
		ligne_motif[7][0] = 4;ligne_motif[7][1] = 8;ligne_motif[7][2] = 4; ligne_motif[7][3] = 8;ligne_motif[7][4] = 4; 
		ligne_motif[8][0] = 4;ligne_motif[8][1] = 8;ligne_motif[8][2] = 8; ligne_motif[8][3] = 4;ligne_motif[8][4] = 4; 
		ligne_motif[9][0] = 4;ligne_motif[9][1] = 8;ligne_motif[9][2] = 2; ligne_motif[9][3] = 8;ligne_motif[9][4] = 8; 

		}


	/*SetDrawMotif(&ligne_motif[m][1],ligne_motif[m][0]);*/

	if (flag_ps == TRUE) Motif_ps(&ligne_motif[m][1],ligne_motif[m][0]);

	}

void Size_font(int coef)
	{
	if (flag_ps == TRUE) Size_font_ps(coef);
	}

void Line_larg(int n)
	{
	SetLineWidth(n);
	if (flag_ps == TRUE) Line_larg_ps(n);
	}

void Rectangle_plein(float x,float y, float l, float h)
	{

	float dx,dy;

	if (flag_delta_carac == TRUE)
		{
		dx =  (float)(taille_police_x*delta_caract_x/2);
		dy =  (float)(taille_police_y*delta_caract_y/2);
		}
	else
		{
		dx=0;
		dy=0;
		}

	DrawFilledBox(
 	        (int)       		(  RESOLUTION_X_FEN * x )/RESOLUTION_X+dx,
		(int) RESOLUTION_Y_FEN -(( RESOLUTION_Y_FEN * y )/RESOLUTION_Y+dy),
		(int) 	                (  RESOLUTION_X_FEN * l )/RESOLUTION_X,
		(int)                   (( RESOLUTION_Y_FEN * h )/RESOLUTION_Y)
		);

	if (flag_ps == TRUE) Rectangle_plein_ps(x,y,l,h);


	}

#endif
