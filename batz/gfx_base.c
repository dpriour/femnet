/*#include "batz.h"*/
#include "libsx_bf.h"

/* -----
   ----- Fonctions Graphiques 
   -----
*/
#define NB_MAX_XPOINTS 10000
float libsx_point_x[NB_MAX_XPOINTS];
float libsx_point_y[NB_MAX_XPOINTS];
char libsx_point_horsclip[NB_MAX_XPOINTS];
int libsx_nb_points;

XPoint xpoints[NB_MAX_XPOINTS];
int nb_xpoints=0;
int ClipSegment(float *,float *,float *,float *);
void Move_to (float ,float );
void Line_to (float ,float );
void Line_end ();



int ColorRGB(int r, int v, int b)
	{
	extern void ColorRGB_ps(int r, int v, int b);
	
	if (flag_ps == TRUE) ColorRGB_ps(r,v,b);
	return(GetRGBColor(r,v,b));
	}
	

void Color(int c)
	{
	extern void Color_ps(int c);
	
	if (flag_ps == TRUE) Color_ps(c);
	SetColor(c);		
	}

void Line(float xx1,float yy1,float xx2, float yy2)
	{
	Move_to(xx1,yy1); Line_to(xx2,yy2); Line_end();
	/*
	float fxx1,fyy1;
	float fxx2,fyy2;
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
 	        (int)       		(  RESOLUTION_X_FEN * xx1 )/RESOLUTION_X+dx,
		(int) RESOLUTION_Y_FEN -(( RESOLUTION_Y_FEN * yy1 )/RESOLUTION_Y+dy),
		(int) 	                (  RESOLUTION_X_FEN * xx2 )/RESOLUTION_X+dx,
		(int) RESOLUTION_Y_FEN -(( RESOLUTION_Y_FEN * yy2 )/RESOLUTION_Y+dy)
		);

	if (flag_ps == TRUE) Line_ps(xx1,yy1,xx2,yy2);
	*/
	}

void Move_to (float x,float y)
	{
	libsx_point_x[0]=x;
	libsx_point_y[0]=y;
	libsx_nb_points = 1;
	/*
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
	*/
	}

void Line_to (float x,float y)
	{
	libsx_point_x[libsx_nb_points]=x;
	libsx_point_y[libsx_nb_points]=y;
	libsx_nb_points ++;
	libsx_point_x[libsx_nb_points]=x;
	libsx_point_y[libsx_nb_points]=y;
	libsx_nb_points ++;

	/*
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
	*/
	}

void Line_end ()
	{
	int i;
	float dx,dy,x,y;
	int c,ct;
	extern void Line_end_ps ();
	
	libsx_nb_points--;
	ct=1;
	for (i=0;i<libsx_nb_points;i+=2)
		{
		
		c = ClipSegment(&libsx_point_x[i],&libsx_point_y[i],&libsx_point_x[i+1],&libsx_point_y[i+1]);
		if ( c < 0 ) 	{libsx_point_horsclip[i] = -1; libsx_point_horsclip[i+1] = -1;}
		else		{libsx_point_horsclip[i] =  0; libsx_point_horsclip[i+1] =  0; ct=0;}
		}
	if (ct==1) {libsx_nb_points=0;return;}
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
	nb_xpoints=0;
	x=9e30;y=x;
	for (i=0;i<libsx_nb_points;i++)
		{
		if ((x!=libsx_point_x[i] || y!=libsx_point_y[i]) && libsx_point_horsclip[i]==0) {x=libsx_point_x[i] ;y=libsx_point_y[i];} 
		else continue;
		xpoints[nb_xpoints].x = (int)(                   ( RESOLUTION_X_FEN * x )/RESOLUTION_X+dx);
		xpoints[nb_xpoints].y = (int)(RESOLUTION_Y_FEN -(( RESOLUTION_Y_FEN * y )/RESOLUTION_Y+dy));
		if (nb_xpoints < NB_MAX_XPOINTS) nb_xpoints++;
		}

  	DrawPolyline(xpoints, nb_xpoints);             
	if (flag_ps == TRUE && ct==0) Line_end_ps();
	}

void Surface_end()
	{
	int i,ct;
	float dx,dy,x,y;
	char c;
	extern void Surface_end_ps ();

	libsx_nb_points--;
	ct=1;
	for (i=0;i<libsx_nb_points;i+=2)
		{
		c=ClipSegment(&libsx_point_x[i],&libsx_point_y[i],&libsx_point_x[i+1],&libsx_point_y[i+1]);
		if (c<0) 	{libsx_point_horsclip[i] = -1; libsx_point_horsclip[i+1] = -1;}
		else		{libsx_point_horsclip[i] =  0; libsx_point_horsclip[i+1] =  0; ct = 0;}
		}
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
	nb_xpoints=0;
	x=9e30;y=x;
	for (i=0;i<libsx_nb_points;i++)
		{
		if ((x!=libsx_point_x[i] || y!=libsx_point_y[i]) ) {x=libsx_point_x[i] ;y=libsx_point_y[i];} else continue;
		xpoints[nb_xpoints].x = (int)(                   ( RESOLUTION_X_FEN * x )/RESOLUTION_X+dx);
		xpoints[nb_xpoints].y = (int)(RESOLUTION_Y_FEN -(( RESOLUTION_Y_FEN * y )/RESOLUTION_Y+dy));
		if (nb_xpoints < NB_MAX_XPOINTS) nb_xpoints++;

		}

	DrawFilledPolygon(xpoints,nb_xpoints);
	if (flag_ps == TRUE && ct==0) Surface_end_ps();

	}

void Circle (float x,float y,float r)
	{
	float dx,dy;
	extern void Circle_ps (float x1,float y1,float r);

	if (flag_clip==1)
		{
		if (x-r<clip.gauche || x+r>clip.droite || y+r>clip.haut || y-r>clip.bas) return;
		}
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
	float dx,dy;
	extern void Text_ps(float x,float y, char *s);

	if (flag_clip==1)
		{
		
		}
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
	extern void Motif_ps(char d[],int n);

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


	/*SetDrawMotif(&ligne_motif[m][1],(int) ligne_motif[m][0]);*/

	if (flag_ps == TRUE) Motif_ps(&ligne_motif[m][1],ligne_motif[m][0]);

	}

void Size_font(int coef)
	{
	extern void Size_font_ps(int coef);
	
	if (flag_ps == TRUE) Size_font_ps(coef);
	}

void Line_larg(int n)
	{
	extern void Line_larg_ps(int n);

	SetLineWidth(n);
	if (flag_ps == TRUE) Line_larg_ps(n);
	}

void Rectangle_plein(float x,float y, float l, float h)
	{
	float dx,dy;
	extern  void Rectangle_plein_ps(float x1,float y1, float x2,float y2);
	
	if (flag_clip==1)
		{
		if (x<clip.gauche) { l=l-(clip.gauche-x);x=clip.gauche; if (l<0) return;}
		if (x>clip.droite || y>clip.haut) return;
		if (y<clip.bas) {h=h-(clip.bas-y); y=clip.bas; if (h<0) return;}
		}
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
 	        (int) (      		 (  RESOLUTION_X_FEN * x ) / RESOLUTION_X + dx  ),
		(int) (RESOLUTION_Y_FEN -(( RESOLUTION_Y_FEN * y ) / RESOLUTION_Y + dy )),
		(int) (                  (  RESOLUTION_X_FEN * l ) / RESOLUTION_X       ),
		(int) (                  (  RESOLUTION_Y_FEN * h ) / RESOLUTION_Y       )
		);
	if (flag_ps == TRUE) Rectangle_plein_ps(x,y,l,h);
	}


int ClipSegment(float *XX1,float *YY1,float *XX2,float *YY2)
	{
	float a,b,xx1,yy1,xx2,yy2;
	if (flag_clip==0) return(0);
	xx1=*XX1; xx2=*XX2; yy1=*YY1; yy2=*YY2;

	if ((xx1<clip.gauche && xx2<clip.gauche) || (yy1<clip.bas && yy2<clip.bas) || (xx1>clip.droite && xx2>clip.droite) || (yy1>clip.haut && yy2>clip.haut))
		{
		if (xx1<clip.gauche) { *XX1 =  clip.gauche;  }
		if (xx2<clip.gauche) { *XX2 =  clip.gauche;  }
		if (xx1>clip.droite ) { *XX1 =  clip.droite;  }
		if (xx2>clip.droite ) { *XX2 =  clip.droite;  }
		if (yy1<clip.bas ) { *YY1 =  clip.bas; }
		if (yy2<clip.bas ) { *YY2 =  clip.bas; }
		if (yy1>clip.haut ) { *YY1 =  clip.haut;  }
		if (yy2>clip.haut ) { *YY2 =  clip.haut;  }
	 	return(-1);
		}
	
	if (xx1<clip.gauche)

		{
		a = xx2-xx1;
		if (a!=0)
			{
			a = (yy2-yy1)/a;
			b = yy2-a*xx2;
			yy1=a*clip.gauche+b;
			if ((yy1>clip.haut && yy2>clip.haut) || (yy1<clip.bas && yy2<clip.bas))
				{
				if (yy1<clip.bas ) { *YY1 =  clip.bas; }
				if (yy2<clip.bas ) { *YY2 =  clip.bas; }
				if (yy1>clip.haut ) { *YY1 =  clip.haut;  }
				if (yy2>clip.haut ) { *YY2 =  clip.haut;  }
				*XX1=clip.gauche;
	 			return(-1);
				}
			}
		xx1=clip.gauche;	
		}
	if (xx2<clip.gauche)
		{
		a = xx2-xx1;
		if (a!=0)
			{
			a = (yy2-yy1)/a;
			b = yy2-a*xx2;
			yy2=a*clip.gauche+b;
			if ((yy1>clip.haut && yy2>clip.haut) || (yy1<clip.bas && yy2<clip.bas))
				{
				if (yy1<clip.bas ) { *YY1 =  clip.bas; }
				if (yy2<clip.bas ) { *YY2 =  clip.bas; }
				if (yy1>clip.haut ) { *YY1 =  clip.haut;  }
				if (yy2>clip.haut ) { *YY2 =  clip.haut;  }
				*XX2=clip.gauche;
	 			return(-1);
				}

			}
		xx2=clip.gauche;	
		}
	
	if (xx1>clip.droite)
		{
		a = xx2-xx1;
		if (a!=0)
			{
			a = (yy2-yy1)/a;
			b = yy2-a*xx2;
			yy1=a*clip.droite+b;
			if ((yy1>clip.haut && yy2>clip.haut) || (yy1<clip.bas && yy2<clip.bas))
				{
				if (yy1<clip.bas ) { *YY1 =  clip.bas; }
				if (yy2<clip.bas ) { *YY2 =  clip.bas; }
				if (yy1>clip.haut ) { *YY1 =  clip.haut;  }
				if (yy2>clip.haut ) { *YY2 =  clip.haut;  }
				*XX1=clip.droite;
	 			return(-1);
				}

			}
		xx1=clip.droite;	
		}
	if (xx2>clip.droite)
		{
		a = xx2-xx1;
		if (a!=0)
			{
			a = (yy2-yy1)/a;
			b = yy2-a*xx2;
			yy2=a*clip.droite+b;
			if ((yy1>clip.haut && yy2>clip.haut) || (yy1<clip.bas && yy2<clip.bas))
				{
				if (yy1<clip.bas ) { *YY1 =  clip.bas; }
				if (yy2<clip.bas ) { *YY2 =  clip.bas; }
				if (yy1>clip.haut ) { *YY1 =  clip.haut;  }
				if (yy2>clip.haut ) { *YY2 =  clip.haut;  }
				*XX2=clip.droite;
	 			return(-1);
				}

			}
		xx2=clip.droite;	
		}

	if (yy1>clip.haut)
		{
		a = xx2-xx1;
		if (a!=0.) 
			{
			a = (yy2-yy1)/a;
			b = yy2-a*xx2;
			xx1=(-b+clip.haut)/a;
			if ((xx1<clip.gauche && xx2<clip.gauche)  || (xx1>clip.droite && xx2>clip.droite))
				{
				if (xx1<clip.gauche) { *XX1 =  clip.gauche;  }
				if (xx2<clip.gauche) { *XX2 =  clip.gauche;  }
				if (xx1>clip.droite ) { *XX1 =  clip.droite;  }
				if (xx2>clip.droite ) { *XX2 =  clip.droite;  }
				*YY1=clip.haut;
				return(-1);
				}
			}
		yy1=clip.haut;	
		}

	if (yy2>clip.haut)
		{
		a = xx2-xx1;
		if (a!=0.)
			{
			a = (yy2-yy1)/a;
			b = yy2-a*xx2;
			xx2=(-b+clip.haut)/a;
			if ((xx1<clip.gauche && xx2<clip.gauche)  || (xx1>clip.droite && xx2>clip.droite))
				{
				if (xx1<clip.gauche) { *XX1 =  clip.gauche;  }
				if (xx2<clip.gauche) { *XX2 =  clip.gauche;  }
				if (xx1>clip.droite ) { *XX1 =  clip.droite;  }
				if (xx2>clip.droite ) { *XX2 =  clip.droite;  }
				*YY2=clip.haut;
				return(-1);
				}

			}
		yy2=clip.haut;	
		}

	if (yy1<clip.bas)
		{
		a = xx2-xx1;
		if (a!=0.F)
			{
			a = (yy2-yy1)/a;
			b = yy2-a*xx2;
			xx1=(-b+clip.bas)/a;
			if ((xx1<clip.gauche && xx2<clip.gauche)  || (xx1>clip.droite && xx2>clip.droite))
				{
				if (xx1<clip.gauche) { *XX1 =  clip.gauche;  }
				if (xx2<clip.gauche) { *XX2 =  clip.gauche;  }
				if (xx1>clip.droite ) { *XX1 =  clip.droite;  }
				if (xx2>clip.droite ) { *XX2 =  clip.droite;  }
				*YY1=clip.bas;
				return(-1);
				}

			}
		yy1=clip.bas;	
		}

	if (yy2<clip.bas)
		{
		a = xx2-xx1;
		if (a!=0)
			{
			a = (yy2-yy1)/a;
			b = yy2-a*xx2;
			xx2=(-b+clip.bas)/a;
			if ((xx1<clip.gauche && xx2<clip.gauche)  || (xx1>clip.droite && xx2>clip.droite))
				{
				if (xx1<clip.gauche) { *XX1 =  clip.gauche;  }
				if (xx2<clip.gauche) { *XX2 =  clip.gauche;  }
				if (xx1>clip.droite ) { *XX1 =  clip.droite;  }
				if (xx2>clip.droite ) { *XX2 =  clip.droite;  }
				*YY2=clip.bas;
				return(-1);
				}

			}
		yy2=clip.bas;	
		}
	*XX1=xx1; *XX2=xx2; *YY1=yy1; *YY2=yy2;
	return(0);

	}

#ifdef KK

void ClipArea()
	{
	/*modifie les coordonnees de surface passe figx et figy
	np =  nb de point des surfaces  MARCHE MAL*/


	 long int i,j,k;
	 int clipclip;
	float b,h,d,g;
	float figx[30],figy[30],areax[30],areay[30];
	int np;
	
	b=clip.bas;
	h=clip.haut;
	d=clip.droite;
	g=clip.gauche;
	np = libsx_nb_points;
	for (i=0;i<np;i++){figx[i]=libsx_point_x[i];figy[i]=libsx_point_y[i];}


	figx[np]=figx[0];
	figy[np]=figy[0];

/*clip haut */
	j=0;
	k=0;
	if (figy[0]<h)  clipclip=1; else clipclip=0;
	do 
		{
		j++;
		if (figy[j]<h)
			{ 
			if (clipclip==0) 
				{
				areax[k] = ( (figx[j]-figx[j-1]) * (h-figy[j]) / (figy[j]-figy[j-1]) ) + figx[j];
				areay[k]=h;
				k++;
				clipclip=1;
				}
			}
  		else if (clipclip==1)
			{
  			if (figy[j]>h)
				{
				areax[k]= ( (figx[j]-figx[j-1]) * (h-figy[j]) / (figy[j]-figy[j-1])) + figx[j];
				areay[k]= h;
				k++;
				areax[k]=figx[j];areay[k]=figy[j];k++;
				clipclip=0;
				}
			}
  		else
			{
 	 		areax[k]=figx[j];
			areay[k]=figy[j];
			k++;
			}
		} 
		while (j<np);
	for (i=0;i<=k;i++) {figx[i]=areax[i];figy[i]=areay[i];}
 	figx[k]=figx[0]; figy[k]=figy[0]; np=k;
 /* clip bas */

	j=0;
	k=0;
	if (figy[0]>b)  clipclip=1; else clipclip=0;
	do 
		{
		j++;
		if (figy[j]>b)
			{ 
			if (clipclip==0) 
				{
				areax[k] = ( (figx[j]-figx[j-1]) * (b-figy[j]) / (figy[j]-figy[j-1]) ) + figx[j];
				areay[k]=b;
				k++;
				clipclip=1;
				}
			}
  		else if (clipclip==1)
			{
			if (figy[j]<b)
				{
				areax[k]= ( (figx[j]-figx[j-1]) * (b-figy[j]) / (figy[j]-figy[j-1])) + figx[j];
				areay[k]= b;
				k++;
				areax[k]=figx[j];areay[k]=figy[j];k++;
				clipclip=0;
				}
			}
		else
			{
			areax[k]=figx[j];
			areay[k]=figy[j];
			k++;
			}
		} 
		while (j<np);

	for (i=0;i<=k;i++) {figx[i]=areax[i];figy[i]=areay[i];}
	figx[k]=figx[0]; figy[k]=figy[0]; np=k;

/* clip gauche */
	j=0;
	k=0;
	if (figx[0]<g)  clipclip=1; else clipclip=0;
	do 
		{
		j++;
		if (figx[j]<g)
			{ 
			if (clipclip==0) 
				{
				areay[k] = ( (figy[j]-figy[j-1]) * (g-figx[j]) / (figx[j]-figx[j-1]) ) + figy[j];
				areax[k]=g;
				k++;
				clipclip=1;
				}
			}
		else if (clipclip==1)
			{
  			if (figx[j]>g)
				{
				areay[k]= ( (figy[j]-figy[j-1]) * (g-figx[j]) / (figx[j]-figx[j-1])) + figy[j];
				areax[k]= g;
				k++;
				areax[k]=figx[j];areay[k]=figy[j];k++;
				clipclip=0;
				}
			}
		else
			{
			areax[k]=figx[j];areay[k]=figy[j];k++;
			}
		} 
		while (j<np);

	for (i=0;i<=k;i++) {figx[i]=areax[i];figy[i]=areay[i];}
	figx[k]=figx[0];figy[k]=figy[0];np=k;

/* clip droit */
	j=0;
	k=0;

	if (figx[0]>d)  clipclip=1; else clipclip=0;
	do 
		{ 
		j++;
		if (figx[j]>d)
			{ 
			if (clipclip==0) 
				{
				areay[k] =  (figy[j]-figy[j-1]) * (d-figx[j]) / (figx[j]-figx[j-1])  + figy[j];
				areax[k]=d;
				k++;
				clipclip=1;
				}
			}
		else 	
			{
			if (clipclip==1)
				{
  				if (figx[j]<d)
					{
					areay[k]=  (figy[j]-figy[j-1]) * (d-figx[j]) / (figx[j]-figx[j-1]) + figy[j];
					areax[k]= d;
					k++;
					areax[k]=figx[j];areay[k]=figy[j];k++;
					clipclip=0;
					}
				}
  			else
				{
				areax[k]=figx[j];areay[k]=figy[j];k++;
				}
			}
		} 
		while (j<np);
	for (i=0;i<=k;i++) {figx[i]=areax[i]; figy[i]=areay[i];}
	figx[k]=figx[0]; figy[k]=figy[0]; np=k;


	 libsx_nb_points=np;
	for (i=0;i<np;i++){libsx_point_x[i]=figx[i];libsx_point_y[i]=figy[i];}


	}
#endif

void TraceClip()
	{
	char flg=flag_clip;
	flag_clip = 0;
	Move_to(clip.gauche,clip.haut);
	Line_to(clip.gauche,clip.bas);
	Line_to(clip.droite,clip.bas);
	Line_to(clip.droite,clip.haut);
	Line_to(clip.gauche,clip.haut);
	Line_end();
	flag_clip=flg;
	}
