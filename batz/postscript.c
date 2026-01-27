#ifndef PAS_DE_VUE

/*#include "libsx_bf.h"*/
#include <sys/time.h>
#include "batz.h"              /* where program specific stuff is defined */
#include <time.h>    // time()
/* ---
   --- Chk_ps_open : verifie si le fichier PostScript est Ouvert
   ---
*/
extern char nom_fichier[MLEN];
char *Date();

extern float libsx_point_x[];
extern float libsx_point_y[];
extern char libsx_point_horsclip[];

extern int libsx_nb_points;

/* codes PS du logo IFREMER */
short ifre[]={ 0,0,0,96,2248,96,2248,0,0,0,-11,24,10,24,28,30,28,30,22,38,22,40,28,46,30,44,36,38,36,38,30,32,30,32,42,38,42,40,48,44,50,46,56,52,58,52,68,60,70,60,82,66,84,66,96,72,98,74,110,80,112,80,118,86,120,88,130,94,132,94,138,100,140,102,144,108,148,110,152,116,154,116,160,122,162,122,168,116,170,114,176,108,176,108,182,102,182,100,184,100,194,102,196,128,196,128,190,142,188,144,182,204,180,204,174,232,174,232,168,246,168,246,160,260,158,260,146,274,144,274,134,248,132,246,126,232,126,232,120,220,120,218,124,210,124,210,120,202,118,202,112,212,112,212,118,218,118,218,106,204,104,202,100,190,98,190,104,182,104,182,98,182,98,176,98,174,104,160,104,158,98,142,98,132,96,130,92,118,90,116,84,102,84,108,82,94,14,72,14,84,70,82,70,80,64,74,62,72,36,66,36,66,30,52,28,52,22,46,22,46,16,40,16,38,10,24,10,-1,98,14,112,82,168,82,164,64,130,64,128,56,156,56,152,38,124,38,118,14,98,14,-1,158,14,172,82,214,82,222,80,226,76,230,72,232,64,230,58,228,52,224,48,218,44,222,40,224,36,224,14,202,14,202,32,198,34,196,36,184,36,180,14,158,14,-1,188,52,192,66,206,66,208,64,210,60,204,52,188,52,-9,228,14,240,82,300,82,296,64,260,64,258,56,288,56,284,40,254,40,252,32,290,32,286,14,228,14,-1,292,14,304,82,332,82,334,42,354,82,382,82,370,14,352,14,358,48,340,14,322,14,316,48,310,14,292,14,-1,374,14,386,82,446,82,442,64,406,64,404,56,434,56,430,40,400,40,398,32,436,32,432,14,374,14,-1,438,14,452,82,494,82,502,80,506,76,510,72,512,64,510,58,508,52,504,48,498,44,502,40,504,36,504,14,482,14,482,32,478,34,476,36,464,36,460,14,438,14,-1,468,52,472,66,486,66,488,64,490,60,484,52,468,52,-9,180,148,180,153,240,153,240,148,180,148,-10,160,141,160,146,240,146,240,141,160,141,-10,150,134,150,139,220,139,220,134,150,134,-10,114,127,114,132,210,132,210,127,114,127,-10,100,120,100,125,196,125,196,120,100,120,-10,92,113,92,118,174,118,174,113,92,113,-10,84,106,84,111,152,111,152,106,84,106,-10,76,99,76,104,122,104,122,99,76,99,-10,72,92,72,97,110,97,110,92,72,92,-10,70,85,70,90,94,90,94,85,70,85,-10,62,78,62,83,84,83,84,78,62,78,-10,62,71,62,76,80,76,80,71,62,71,-10,56,64,56,69,72,69,72,64,56,64,-10,56,57,56,62,66,62,66,57,56,57,-10,56,42,56,50,66,50,66,42,56,42,-10,-99};

char *LJour[]={"Mon","Mon","Tue","Tue","Wed","Web", "Thu","Thu","Fri","Fri" ,"Sat","Sat", "Sun","Sun"};

char *LMois[]={"Jan","Jan","Feb","Feb","Mar","Mar","Apr","Apr","May","May","Jun","Jun", "Jul","Jul","Aug","Aug","Sep","Sep","Oct","Oct","Nov","Nov","Dec","Dec"};


void Chk_ps_open()
	{
	char nom_fichier_ps[MLEN];
	int l = strlen(nom_fichier);
	int te;
	if (fic_ps != NULL) return;

	/* Ouvre le fichier et prepare l'entete */

	
	if (l<3 || nom_fichier[l-3] !='.' )
		sprintf(nom_fichier_ps,"%s.ps",nom_fichier);
	else
		strcpy(nom_fichier_ps,nom_fichier);
	if (strcmp(nom_fichier_ps,".ps")==0)
		sprintf(nom_fichier_ps,"postscript.ps");

	printf("nom_fichier_ps : %s\n",nom_fichier_ps);	
	fic_ps = fopen(nom_fichier_ps,"w");

	if (fic_ps == NULL)
		{
		fprintf(stderr,"Impossible de creer le fichier PostScript !\n");
		return;
		}

	fprintf(fic_ps,"%%!PS\n");
	fprintf(fic_ps,"/dictlocal 12 dict def \n");
	fprintf(fic_ps,"/Reencode { \n");
	fprintf(fic_ps,"dictlocal begin \n");	
	fprintf(fic_ps,"/Nvvect exch def \n");
	fprintf(fic_ps,"/Nomnvpolice exch def \n");
	fprintf(fic_ps,"/Nompolicedebase exch def \n");
	fprintf(fic_ps,"/Policedebasedict Nompolicedebase findfont def \n");
	fprintf(fic_ps,"/nouveaudict Policedebasedict maxlength dict def \n");
	fprintf(fic_ps,"Policedebasedict { \n");
	fprintf(fic_ps,"exch dup /FID ne { \n");
	fprintf(fic_ps,"dup /Encoding eq { \n");
	fprintf(fic_ps,"exch dup length array copy \n");
	fprintf(fic_ps,"nouveaudict 3 1 roll put } { \n");
	fprintf(fic_ps,"exch nouveaudict 3 1 roll put } \n");
	fprintf(fic_ps,"ifelse } { pop pop } ifelse } forall \n");
	fprintf(fic_ps,"nouveaudict /FontName Nomnvpolice put \n");
	fprintf(fic_ps,"Nvvect aload pop Nvvect length 2 idiv { \n");
	fprintf(fic_ps,"nouveaudict /Encoding get 3 1 roll put } \n");
	fprintf(fic_ps,"repeat Nomnvpolice nouveaudict definefont pop end} \n");
	fprintf(fic_ps,"def /francvect [ \n");
	fprintf(fic_ps,"244/ocircumflex \n");
	fprintf(fic_ps,"232/egrave \n");
	fprintf(fic_ps,"233/eacute \n");
	fprintf(fic_ps,"234/ecircumflex \n");
	fprintf(fic_ps,"224/agrave \n");
	fprintf(fic_ps,"231/ccedilla \n");
	fprintf(fic_ps,"238/icircumflex \n");
	fprintf(fic_ps,"249/ugrave \n");
	fprintf(fic_ps,"226/acircumflex \n");
	fprintf(fic_ps,"235/edieresis \n");
	fprintf(fic_ps,"239/idieresis \n");
	fprintf(fic_ps,"]def \n");
	fprintf(fic_ps,"/%s\n",NOM_POLICE_PS);
	fprintf(fic_ps,"/%s-fr francvect Reencode \n",NOM_POLICE_PS);
	fprintf(fic_ps,"/%s-fr findfont \n",NOM_POLICE_PS);
	fprintf(fic_ps," %d scalefont setfont\n",hauteur_police_ps);
	fprintf(fic_ps," %f setlinewidth\n",epaisseur_trait_ps);
	if (mode_portrait == FALSE)
		{
		fprintf(fic_ps,"  %f  0 translate stroke \n",RESOLUTION_X_PS+2*MARGE_X_PS);
		fprintf(fic_ps," 90 rotate stroke\n");
		}
	if (mode_portrait == TRUE)
		{
		fprintf(fic_ps,"  %f  0 translate stroke \n",                2*MARGE_X_PS);
		fprintf(fic_ps," 00 rotate stroke\n");
		}
		
		
	fprintf(fic_ps," [] 0 setdash\n");

	fprintf(fic_ps,"%% macro rectangle plein  \n");
	fprintf(fic_ps,"/boite{\n");
	fprintf(fic_ps,"	/Dimy exch def		%% recherche larg y dans pile\n");
	fprintf(fic_ps,"	/Dimx exch def		%% recherche larg x dans pile\n");
	fprintf(fic_ps,"	0    Dimy rlineto	%% trace \n");
	fprintf(fic_ps,"	Dimx 0    rlineto\n");
	fprintf(fic_ps,"	0    Dimy neg rlineto\n");
	fprintf(fic_ps,"	closepath		%% ferme la boite\n");
	fprintf(fic_ps,"	fill			%% remplissage\n");
	fprintf(fic_ps,"	stroke			%% affichage\n");
	fprintf(fic_ps,"	} def\n");

	fprintf(fic_ps,"\n\n\n\n");		
		{
		int zi,zj,zk,x,y;

		zi=0;zj=0;zk=0;
		/* lecture des codes de ifre[]
		-99 : fin
		-g :  fin d'une region, g= niveau de gris
		x y : position x,y
		*/
		fprintf(fic_ps,"%d %d translate\n",10,25);
		fprintf(fic_ps,"0.15 0.15 scale\n");
		fprintf(fic_ps,"newpath\n");

/*		do
			{
			c=ifre[zi];
			if (c!=-99)
				{
				if (c<0)
					{
					fprintf(fic_ps,"closepath\n");
					if (c==-11)
						fprintf(fic_ps,"%f setgray\n", 1.); 
					else 
						fprintf(fic_ps,"%f setgray\n", -(float)(c)*.1);
					fprintf(fic_ps,"fill newpath\n");
					zj=0;zk=0;
					}
				else
					{
					if (zj==0)
						{
						x=c;
						zj=1;
						}
					
					else 
						{
						y=c;
						zj=0;
						if (zk==0)
							{
							fprintf (fic_ps,"%d %d moveto\n",x,y);
							zk=1;
							}
						else
							{
							fprintf (fic_ps,"%d %d lineto\n",x,y);
							}
						}
					}
				}
			zi++;
			} while (c!=-99) ;
*/
		fprintf(fic_ps,"6.66666 6.66666 scale\n");
		/*fprintf(fic_ps,".2 setgray %d %d moveto  (Date : %s  Fichier: %s) show \n",95,10,Date(),nom_fichier);*/
		/*fprintf(fic_ps,".2 setgray %d %d moveto  (%s %s %s) show \n",95,-10,Date(),nom_fichier_ps,"dpriour@gmail.com");*/
		fprintf(fic_ps,".2 setgray %d %d moveto  (%s %s) show \n",95,-10,nom_fichier_ps,"dpriour@gmail.com");
		}



	}


void Chk_ps_close()
	{
	if (fic_ps != NULL)
		{
		fprintf(fic_ps," showpage\n");
		fclose(fic_ps);
		}
	fic_ps = NULL;

	}

void Text_ps(float x,float y, char *s)
	{
	float fx,fy;
	char buf[1024];
	int i,j;
	char c;
	float dx,dy,rx,ry;

	if (flag_delta_carac == TRUE)
		{
		dx =  (float)(largeur_police_ps*delta_caract_x/2);
		dy =  (float)(hauteur_police_ps*delta_caract_y/2);
		}
	else
		{
		dx = 0;
		dy = 0;
		}		

	/* recodage de la chaine en Postscript */
	j=0;
	for (i=0;i<=strlen(s);i++)
		{
		c = *(s+i);
		if (c == '(' || c==')' || c=='\\')
			{
			buf[j++] = '\\';
			}
		buf[j++] = c;
		}

	Chk_ps_open();
	rx= RESOLUTION_X_PS;
	ry= RESOLUTION_Y_PS;
	if (flag_ortho_norm == TRUE)
		{
		if(mode_portrait == FALSE) ry = ry /  ((RESOLUTION_Y-axe_y1)/RESOLUTION_Y+1.);
		}

	if (mode_portrait == TRUE)
		{
		fx = ( rx * x )/RESOLUTION_X+dx+MARGE_X_PS;
		fy = ( ry * y )/RESOLUTION_Y+dy+MARGE_Y_PS;
		}
	else
		{
		fx = ( ry * x )/RESOLUTION_Y+dx+MARGE_Y_PS;
		fy = ( rx * y )/RESOLUTION_X+dy+MARGE_X_PS;
		}


	fprintf(fic_ps,"%f %f moveto(%s)show\n",fx,fy,buf);
	delta_caract_x=0;
	delta_caract_y=0;
	}
#ifdef KK
void Line_ps(float xx1,float yy1,float xx2,float yy2)
	{
	float fx1,fy1;
	float fx2,fy2;
	float dx,dy,rx,ry;

	if (flag_delta_carac == TRUE)
		{
		dx = (float)(largeur_police_ps*delta_caract_x/2);
		dy = (float)(hauteur_police_ps*delta_caract_y/2);
		}
	else
		{
		dx=0;
		dy=0;
		}

	Chk_ps_open();
	rx= RESOLUTION_X_PS;
	ry= RESOLUTION_Y_PS;
	if (flag_ortho_norm== TRUE)
		{
		if(mode_portrait == FALSE) ry = ry /  ((RESOLUTION_Y-axe_y1)/RESOLUTION_Y+1.);
		
		}

	if (mode_portrait == TRUE)
		{
		fx1 = ( rx * xx1 )/RESOLUTION_X+MARGE_X_PS+dx;
		fy1 = ( ry * yy1 )/RESOLUTION_Y+MARGE_Y_PS+dy;
		fx2 = ( rx * xx2 )/RESOLUTION_X+MARGE_X_PS+dx;
		fy2 = ( ry * yy2 )/RESOLUTION_Y+MARGE_Y_PS+dy;
		}
	else
		{
		fx1 = ( ry * xx1 )/RESOLUTION_Y+MARGE_Y_PS+dx;
		fy1 = ( rx * yy1 )/RESOLUTION_X+MARGE_X_PS+dy;
		fx2 = ( ry * xx2 )/RESOLUTION_Y+MARGE_Y_PS+dx;
		fy2 = ( rx * yy2 )/RESOLUTION_X+MARGE_X_PS+dy;
		}

	fprintf(fic_ps,"%.4f %.4f moveto %.4f %.4f  lineto stroke \n",fx1,fy1,fx2,fy2);
	}

void Move_to_ps (float x1,float y1)
	{
	float fx1,fy1;
	float dx,dy,rx,ry;

	if (flag_delta_carac == TRUE)
		{
		dx = (float)(largeur_police_ps*delta_caract_x/2);
		dy = (float)(hauteur_police_ps*delta_caract_y/2);
		}
	else
		{
		dx=0;
		dy=0;
		}
	Chk_ps_open();
	rx= RESOLUTION_X_PS;
	ry= RESOLUTION_Y_PS;
	if (flag_ortho_norm== TRUE)
		{
		if(mode_portrait == FALSE) ry = ry /  ((RESOLUTION_Y-axe_y1)/RESOLUTION_Y+1.);
		
		}

	if (mode_portrait == TRUE)
		{
		fx1 = ( rx * x1 )/RESOLUTION_X+MARGE_X_PS+dx;
		fy1 = ( ry * y1 )/RESOLUTION_Y+MARGE_Y_PS+dy;
		}
	else
		{
		fx1 = ( ry * x1 )/RESOLUTION_Y+MARGE_Y_PS+dx;
		fy1 = ( rx * y1 )/RESOLUTION_X+MARGE_X_PS+dy;
		}
	fprintf(fic_ps,"%.4f %.4f moveto \n",fx1,fy1);
	}

void Line_to_ps (float x1,float y1)
	{
	float fx1,fy1;
	float dx,dy,rx,ry;

	if (flag_delta_carac == TRUE)
		{
		dx = (float)(largeur_police_ps*delta_caract_x/2);
		dy = (float)(hauteur_police_ps*delta_caract_y/2);
		}
	else
		{
		dx=0;
		dy=0;
		}
	Chk_ps_open();
	rx= RESOLUTION_X_PS;
	ry= RESOLUTION_Y_PS;
	if (flag_ortho_norm== TRUE)
		{
		if(mode_portrait == FALSE) ry = ry /  ((RESOLUTION_Y-axe_y1)/RESOLUTION_Y+1.);
		
		}

	if (mode_portrait == TRUE)
		{
		fx1 = ( rx * x1 )/RESOLUTION_X+MARGE_X_PS+dx;
		fy1 = ( ry * y1 )/RESOLUTION_Y+MARGE_Y_PS+dy;
		}
	else
		{
		fx1 = ( ry * x1 )/RESOLUTION_Y+MARGE_Y_PS+dx;
		fy1 = ( rx * y1 )/RESOLUTION_X+MARGE_X_PS+dy;
		}

	fprintf(fic_ps,"%.4f %.4f lineto \n",fx1,fy1);
	}
#endif

void Line_end_ps ()
	{

	float fx1,fy1;
	float dx,dy,rx,ry;
	int i,j;
	if (flag_delta_carac == TRUE)
		{
		dx = (float)(largeur_police_ps*delta_caract_x/2);
		dy = (float)(hauteur_police_ps*delta_caract_y/2);
		}
	else
		{
		dx=0;
		dy=0;
		}
	Chk_ps_open();
	rx= RESOLUTION_X_PS;
	ry= RESOLUTION_Y_PS;
	if (flag_ortho_norm== TRUE)
		{
		if(mode_portrait == FALSE) ry = ry /  ((RESOLUTION_Y-axe_y1)/RESOLUTION_Y+1.);
		
		}
	j=0;
	for (i=0;i<libsx_nb_points;i++)
		{
		if (mode_portrait == TRUE)
			{
			fx1 = ( rx * libsx_point_x[i] )/RESOLUTION_X+MARGE_X_PS+dx;
			fy1 = ( ry * libsx_point_y[i] )/RESOLUTION_Y+MARGE_Y_PS+dy;
			}
		else
			{
			fx1 = ( ry * libsx_point_x[i] )/RESOLUTION_Y+MARGE_Y_PS+dx;
			fy1 = ( rx * libsx_point_y[i] )/RESOLUTION_X+MARGE_X_PS+dy;
			}
		if( (int) libsx_point_horsclip[i] == -1) continue;

		if (j==0)
			fprintf(fic_ps,"\n%.4f %.4f moveto ",fx1,fy1);
		else
			fprintf(fic_ps,"%.4f %.4f lineto ",fx1,fy1);
		j++;
		}
	fprintf(fic_ps,"stroke\n");
	}
	
void Surface_end_ps ()
	{
	float fx1,fy1;
	float dx,dy,rx,ry;
	int i;
	if (flag_delta_carac == TRUE)
		{
		dx = (float)(largeur_police_ps*delta_caract_x/2);
		dy = (float)(hauteur_police_ps*delta_caract_y/2);
		}
	else
		{
		dx=0;
		dy=0;
		}
	Chk_ps_open();
	rx= RESOLUTION_X_PS;
	ry= RESOLUTION_Y_PS;
	if (flag_ortho_norm== TRUE)
		{
		if(mode_portrait == FALSE) ry = ry /  ((RESOLUTION_Y-axe_y1)/RESOLUTION_Y+1.);
		
		}
	for (i=0;i<libsx_nb_points;i++)
		{
		if (mode_portrait == TRUE)
			{
			fx1 = ( rx * libsx_point_x[i] )/RESOLUTION_X+MARGE_X_PS+dx;
			fy1 = ( ry * libsx_point_y[i] )/RESOLUTION_Y+MARGE_Y_PS+dy;
			}
		else
			{
			fx1 = ( ry * libsx_point_x[i] )/RESOLUTION_Y+MARGE_Y_PS+dx;
			fy1 = ( rx * libsx_point_y[i] )/RESOLUTION_X+MARGE_X_PS+dy;
			}

		if (i==0)
			fprintf(fic_ps,"\n%.4f %.4f moveto ",fx1,fy1);
		else
			fprintf(fic_ps,"%.4f %.4f lineto ",fx1,fy1);
		}

	fprintf(fic_ps,"closepath\nfill\nstroke\n");
	}


void Circle_ps (float xx1,float yy1,float r)
	{
	float fx1,fy1;
	float dx,dy,rx,ry;

	if (flag_delta_carac == TRUE)
		{
		dx = (float)(largeur_police_ps*delta_caract_x/2);
		dy = (float)(hauteur_police_ps*delta_caract_y/2);
		}
	else
		{
		dx=0;
		dy=0;
		}
	Chk_ps_open();
	rx= RESOLUTION_X_PS;
	ry= RESOLUTION_Y_PS;
	if (flag_ortho_norm== TRUE)
		{
		if(mode_portrait == FALSE) ry = ry /  ((RESOLUTION_Y-axe_y1)/RESOLUTION_Y+1.);
		
		}

	if (mode_portrait == TRUE)
		{
		fx1 = ( rx * xx1 )/RESOLUTION_X+MARGE_X_PS+dx;
		fy1 = ( ry * yy1 )/RESOLUTION_Y+MARGE_Y_PS+dy;
		}
	else
		{
		fx1 = ( ry * xx1 )/RESOLUTION_Y+MARGE_Y_PS+dx;
		fy1 = ( rx * yy1 )/RESOLUTION_X+MARGE_X_PS+dy;
		}

	
	fprintf(fic_ps,"%.4f %.4f %f 0 360 arc stroke\n",fx1,fy1,r*2/3);
	}


void Color_ps(int c)
	{
	Chk_ps_open();
	 
	     if (c== BLACK) fprintf(fic_ps,"0 0 0 setrgbcolor\n"); 
	else if (c== BLUE)  fprintf(fic_ps,"0 0 1 setrgbcolor\n"); 
	else if (c== GREEN) fprintf(fic_ps,"0 1 0 setrgbcolor\n");
	/*else if (c== 3) fprintf(fic_ps,"0 1 1 setrgbcolor\n");*/
	else if (c== RED) fprintf(fic_ps,"1 0 0 setrgbcolor\n");
	/*else if (c== 5) fprintf(fic_ps,"1 0 1 setrgbcolor\n");*/
	else if (c== YELLOW) fprintf(fic_ps,"1 1 0 setrgbcolor\n");
	else if (c== WHITE) fprintf(fic_ps,"1 1 1 setrgbcolor\n");
	else  fprintf(fic_ps,"%f setgray\n", ((float) c)/ 256.);
				
				
		
	}
	
void ColorRGB_ps(int r, int v, int b)
	{
	Chk_ps_open();
	fprintf(fic_ps,"%f %f %f setrgbcolor\n",((float) r)/ 256.,((float) v)/
	256.,((float) b)/ 256.);
	}

void Motif_ps(char d[],int n)
	{
	int i;
	Chk_ps_open();
	fprintf(fic_ps,"[");
	if (n)
		for (i=0;i<n;i++) fprintf(fic_ps," %d",d[i]);
	else
		n=1;
	fprintf(fic_ps,"]%d setdash\n",n);
	}
	

void Size_font_ps(int coef)
	{
	fprintf(fic_ps,"/%s-fr findfont %d scalefont setfont\n",NOM_POLICE_PS,hauteur_police_ps+coef);
	}

void Line_larg_ps(int n)
	{
	fprintf(fic_ps,"%f setlinewidth \n", 0.1+0.2*((float)(n-1)));
	}

void Rectangle_plein_ps(float xx1,float yy1, float xx2,float yy2)
	{
	float fx1,fy1;
	float fx2,fy2;
	float dx,dy,rx,ry;

	if (flag_delta_carac == TRUE)
		{
		dx = (float)(largeur_police_ps*delta_caract_x/2);
		dy = (float)(hauteur_police_ps*delta_caract_y/2);
		}
	else
		{
		dx=0;
		dy=0;
		}

	Chk_ps_open();
	rx= RESOLUTION_X_PS;
	ry= RESOLUTION_Y_PS;
	if (flag_ortho_norm== TRUE)
		{
		if(mode_portrait == FALSE) ry = ry /  ((RESOLUTION_Y-axe_y1)/RESOLUTION_Y+1.);
		
		}

	if (mode_portrait == TRUE)
		{
		fx1 = ( rx * xx1 )/RESOLUTION_X+MARGE_X_PS+dx;
		fy1 = ( ry * yy1 )/RESOLUTION_Y+MARGE_Y_PS+dy;
		fx2 = ( rx * xx2 )/RESOLUTION_X+MARGE_X_PS+dx;
		fy2 = ( ry * yy2 )/RESOLUTION_Y+MARGE_Y_PS+dy;
		}
	else
		{
		fx1 = ( ry * xx1 )/RESOLUTION_Y+MARGE_Y_PS+dx;
		fy1 = ( rx * yy1 )/RESOLUTION_X+MARGE_X_PS+dy;
		fx2 = ( ry * xx2 )/RESOLUTION_Y+MARGE_Y_PS+dx;
		fy2 = ( rx * yy2 )/RESOLUTION_X+MARGE_X_PS+dy;
		}

	fprintf(fic_ps,"%.4f %.4f moveto %.4f %.4f boite \n",fx1,fy1,fx2,fy2);
	}



char *Date()
	{
     	struct timeval tp;
     	struct timezone tzp;
	static char date[80];
	char joursem[10];
	int jour;
	char mois[16];
	char heure[16];
	int an;
	static char first=1;
	
	int i,j;

	if (first==1)
		{
		for (i=0;i<14;i++)
			for (j=0;j<9;j++) 
				if (*(LJour[i]+j)==' ') *(LJour[i]+j)=0;
		for (i=0;i<24;i++)
			for (j=0;j<9;j++) 
				if (*(LMois[i]+j)==' ') *(LMois[i]+j)=0;
		
		gettimeofday(&tp,&tzp); /* recherche la date du jour */
		strcpy(date,ctime(&tp.tv_sec));
		//ctime_r(&tp.tv_sec, date);		
		i=0;
		sscanf (date,"%s",joursem);i=i+strlen(joursem)+1;
		sscanf (&date[i],"%s",mois);i=i+strlen(mois)+1;
		sscanf(&date[i],"%d",&jour);i=i+2; if( jour>9) i++;
		sscanf(&date[i],"%s",heure);i+=strlen(heure)+1;
		sscanf(&date[i],"%d",&an);

		for (i=0;i<7;i++)
			{
			if (strcmp( (LJour[i*2]),joursem)==0)  {strcpy(joursem,(LJour[i*2+1]));break;}
			}
		for (i=0;i<12;i++)
			{
			if (strcmp( (LMois[i*2]),mois)==0)  {strcpy(mois,(LMois[i*2+1]));break;}
			}
		/*sprintf(date,"%s %d %s %d %s",joursem,jour,mois,an,heure);*/
		sprintf(date,"%d %s %d %s",jour,mois,an,heure);
		first=0;
		}
	return(date);

	}
#endif
