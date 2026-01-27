/*
 * A simple form-fillout function that lets you pass an array of
 * Tag's that describe a form and it will pop up a window and let
 * a user fill out a form that describes the values you'd like.
 *
 * The main function is GetValues_2().  See the demo program in this
 * same directory (main.c, in the function edit()) for a more
 * detailed example.
 *
 * Written by Allen Martin, (amartin@cs.wpi.edu).
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "libsx.h"
#include "batz.h"

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

typedef struct 
	{
	Widget window;
	int cancelled;
	Widget *w;
	TagList *tags;
	} MReqData;



/* protos */
static void mreq_ok(Widget w, MReqData *mdata);
static void mreq_cancel(Widget w, MReqData *mdata);
     
int GetValues_2(TagList *tags)
{
  MReqData mdata;
  int num_tags=0, num_widg=0, num_labels=0;
  int i, w, l;
  Widget *label_w, ok_w, cancel_w;
  char string[256], window_name[256]="Requestor";
  int maxwidth = 0, widest_label = -1;
  
  /* first count the number of tag items and required widgets */
  for(; tags[num_tags].tag != TAG_DONE; num_tags++)
    {
      if(tags[num_tags].tag == TAG_LABEL)
	{
	  num_labels++;
	  continue;
	}
      else if(tags[num_tags].tag == TAG_WINDOW_LABEL)
	{
	  if(!tags[num_tags].label)
	    {
	      fprintf(stderr, "Invalid window name passed to GetValues_2()\n");
	      return(TRUE);
	    }

	  strcpy(window_name, tags[num_tags].label);
	  continue;
	}
      
      /* determine the widest label */
      if(strlen(tags[num_tags].label) > maxwidth)
	{
	  maxwidth = strlen(tags[num_tags].label);
	  widest_label = num_labels;
	}

      num_labels++;
      num_widg++;
    }
      
  /* allocate mem for the widgets */
  if(!(mdata.w = (Widget *)malloc(num_widg * sizeof(Widget))))
    return(TRUE);
  if(!(label_w = (Widget *)malloc(num_labels * sizeof(Widget))))
    {
      free(mdata.w);
      return(TRUE);
    }
  
  mdata.window = MakeWindow(window_name, SAME_DISPLAY, EXCLUSIVE_WINDOW);
  mdata.tags = tags;

  /* create the label widgets first */
  for(i=0, l=0; i<num_tags; i++)
    {
      if(tags[i].tag == TAG_WINDOW_LABEL)
	continue;
      
      label_w[l] = MakeLabel(tags[i].label);
      if(l)
	SetWidgetPos(label_w[l], PLACE_UNDER, label_w[l-1], NO_CARE, NULL);
      l++;
    }
  
  for(i=0, w=0, l=0; i<num_tags; i++)
    {
      switch(tags[i].tag)
	{
	case TAG_STRING:
	  if(tags[i].init)
	    mdata.w[w]=MakeStringEntry((char *)tags[i].data, 250, NULL, NULL);
	  else
	    mdata.w[w] = MakeStringEntry(NULL, 250, NULL, NULL);
	  
	  if(l)
	    SetWidgetPos(mdata.w[w], PLACE_UNDER, label_w[l-1],
			 PLACE_RIGHT, label_w[widest_label]);
	  else
	    SetWidgetPos(mdata.w[w], PLACE_RIGHT, label_w[widest_label],
			 NO_CARE, NULL);

	  l++;
	  w++;
	  break;

	case TAG_INT:
	  if(tags[i].init)
	    {
	      sprintf(string, "%d", *((int *)tags[i].data));
	      mdata.w[w] = MakeStringEntry(string, 250, NULL, NULL);
	    }
	  else
	    mdata.w[w] = MakeStringEntry(NULL, 250, NULL, NULL);
	  
	  if(l)
	    SetWidgetPos(mdata.w[w], PLACE_UNDER, label_w[l-1],
			 PLACE_RIGHT, label_w[widest_label]);
	  else
	    SetWidgetPos(mdata.w[w], PLACE_RIGHT, label_w[widest_label],
			 NO_CARE, NULL);

	  l++;
	  w++;
	  break;

	case TAG_FLOAT:
	  if(tags[i].init)
	    {
	      sprintf(string, "%f", *((float *)tags[i].data));
	      mdata.w[w] = MakeStringEntry(string, 250, NULL, NULL);
	    }
	  else
	    mdata.w[w] = MakeStringEntry(NULL, 250, NULL, NULL);
	  
	  if(l)
	    SetWidgetPos(mdata.w[w], PLACE_UNDER, label_w[l-1],
			 PLACE_RIGHT, label_w[widest_label]);
	  else
	    SetWidgetPos(mdata.w[w], PLACE_RIGHT, label_w[widest_label],
			 NO_CARE, NULL);

	  w++;
	  l++;
	  break;

	case TAG_LABEL:
	  l++;
	  break;
	case TAG_WINDOW_LABEL:
	  break;
	  
	default:
	  fprintf(stderr, "GetValues_2() : Invalid tag item %d\n", tags[i].tag);
	}
    }
  
  ok_w = MakeButton("Ok", (void *)mreq_ok, &mdata);
  SetWidgetPos(ok_w, PLACE_UNDER, label_w[num_labels-1], NO_CARE, NULL);

  cancel_w = MakeButton("Cancel", (void *)mreq_cancel, &mdata);
  SetWidgetPos(cancel_w, PLACE_UNDER, label_w[num_labels-1],
	       PLACE_RIGHT, ok_w);

  ShowDisplay();
  MainLoop();
  
  SetCurrentWindow(ORIGINAL_WINDOW);

  /* check for cancel */
  if(mdata.cancelled)
    return(TRUE);

  free(mdata.w);
  free(label_w);
  
  return(FALSE);
}

static void mreq_ok(Widget w, MReqData *mdata)
	{
	int widg_num;
	TagList *tagptr;
	char *cptr;
	/* extract the info from the widgets */
	for(widg_num=0, tagptr=mdata->tags; tagptr->tag != TAG_DONE; tagptr++)
		{
		switch(tagptr->tag)
			{
			case TAG_STRING:
			cptr = GetStringEntry(mdata->w[widg_num++]);
			strcpy(tagptr->data, cptr);
			break;
			case TAG_INT:
			cptr = GetStringEntry(mdata->w[widg_num++]);
			*((int *)tagptr->data) = atoi(cptr);
			break;
			case TAG_FLOAT:
			cptr = GetStringEntry(mdata->w[widg_num++]);
			*((float *)tagptr->data) = atof(cptr);
			break;
			case TAG_WINDOW_LABEL:
			case TAG_LABEL:
			break;
			default:
			fprintf(stderr, "GetValues_2() : Invalid tag item %d\n", tagptr->tag);
			}
		}
	mdata->cancelled = FALSE;
	SetCurrentWindow(mdata->window);
	CloseWindow();
	}


static void mreq_cancel(Widget w, MReqData *mdata)
	{
  	mdata->cancelled = TRUE;
  	SetCurrentWindow(mdata->window);
  	CloseWindow();
	}



void edit(Widget w, void *data)
	{





  
  	TagList tags[] = 
  		{
    		{TAG_INT,    "periode fils:",      &periode_fils ,  TAG_INIT}, 
    		{TAG_DONE,   NULL,           NULL,     TAG_NOINIT}
  		};

   	if (periode_fils <= 0) periode_fils = 1;
    	if(GetValues_2(tags))
    		printf("Cancelled\n");
  	else
    		{
      		printf("periode fils: %d\n", periode_fils); 
		initialisation_nb_ufils();
		initialisation_nb_vfils();
		fils_contour_calculer();
    		}
   	if (periode_fils <= 0) periode_fils = 1;
	}

void edit_echelle(Widget w, void *data)
	{
  	TagList tags[] = 
  		{
    		{TAG_FLOAT,	"echelle verticale:",	&bcartmax ,  	TAG_INIT}, 
    		{TAG_DONE,	NULL,           	NULL,     		TAG_NOINIT}
  		};

	CLASS float binx,baxx,biny,baxy,binz,baxz,bcartmax; /*valeursmaximales des coordonnees avec rotation avec zoom*/

    	if(GetValues_2(tags))
    		printf("Cancelled\n");
  	else
    		{
      		printf("echelle verticale  : %f\n", bcartmax); 
    		}
	
	baxy = biny + bcartmax;
	baxx = binx + (baxy - biny) * RESOLUTION_X_FEN / RESOLUTION_Y_FEN;


	}

void edit_coupe(Widget w, void *data)
	{





  
  	TagList tags[] = 
  		{
    		{TAG_FLOAT,	"profondeur de coupe:",	&profondeur_coupe ,  	TAG_INIT}, 
    		{TAG_DONE,	NULL,           	NULL,     		TAG_NOINIT}
  		};


    	if(GetValues_2(tags))
    		printf("Cancelled\n");
  	else
    		{
      		printf("profondeur de coupe  : %f\n", profondeur_coupe); 
    		}
   	if (profondeur_coupe < 0.0) profondeur_coupe = 0.0;
   	if (profondeur_coupe > 1.0) profondeur_coupe = 1.0;
    	profondeur_coupe_float = cinz + profondeur_coupe * (caxz-cinz);
      	/*printf("minimum de coupe  : %f	", cinz); 
      	printf("maximum de coupe  : %f", caxz); 
      	printf("profondeur_coupe_float  : %f\n", profondeur_coupe_float);*/ 
	}

void edit_coupe2(Widget ww, float val, void *junk)
	{
  	profondeur_coupe = val;
  	/*printf("Val de profondeur_coupe = %8.3f \n",profondeur_coupe);*/
  	
   	if (profondeur_coupe < 0.0) profondeur_coupe = 0.0;
   	if (profondeur_coupe > 1.0) profondeur_coupe = 1.0;
    	profondeur_coupe_float = cinz + profondeur_coupe * (caxz-cinz);
    	
  	dessiner();
	}

void edit_temps1(Widget ww, float val, void *junk)
	{
	int elem,pa,no;
	double elongation;
	int deb,fin;

	double valinter;
	float valinter2;

	char chaine[7];
	extern void EcritText(int icolor, double dx, double dy, char *chaine, double decalage_y);

  	temps_t = val;
  	/*printf("Val de temps_t = %8.3f ",temps_t);*/



	if (nbtemps > 0)
		{
   		if (temps_t > 1.0) temps_t = 1.0;
 	
		pa = (int) (1+ ((nbtemps-1) * temps_t));

		/*printf("Val de temps_t = %8.3f ",temps_t);
		printf("pa = %8d ",pa);
		printf("nbtemps = %8d \n",nbtemps);*/

   		if (temps_t < 0.0) temps_t = 0.0;

		valinter = temps_t *(Finstockage-Debutstockage);
		valinter2 = (float) valinter + Debutstockage;

		char text[10];
		sprintf(text,"%7.2f",valinter2);  

  		SetStringEntry(w[91], text);


	
    		for (elem=1;elem<=NOMBRE_NOEUDS;elem++)
    			{
			//printf("pa = %8d elem = %8d NOMBRE_NOEUDS = %8d \n",pa,elem,NOMBRE_NOEUDS);
			Noeud[elem].x = Noeud[elem].ex[pa];
			Noeud[elem].y = Noeud[elem].ey[pa];
			Noeud[elem].z = Noeud[elem].ez[pa];
    			}

		/* 	
		printf("temps_t_float = %f , nbtemps %d",temps_t_float, nbtemps);
		printf("x2 = %8.3f ",Noeud[2].dx[pa]);
		printf("z2 = %8.3f \n",Noeud[2].dz[pa]);
		*/

		/*
		for (elem=1;elem <= NOMBRE_ELEMENTS;elem++)
			{

			Element[elem].wt=Element[elem].dtension[pa];
			Element[elem].lgtendue=Element[elem].dlgtendue[pa];
			Element[elem].nrj=Element[elem].dnrj[pa];
			}
		*/
  		dessiner();

		/*printf("Houle %d \n",Houle.nb_point);*/
		if (Structure.free_surface == 1)
			{
			TraceSegment(WHITE, surface_libre[1][1], surface_libre[2][1], surface_libre[1][2], surface_libre[2][2]);
			TraceSegment(WHITE, surface_libre[1][2], surface_libre[2][2], surface_libre[1][3], surface_libre[2][3]);
			TraceSegment(WHITE, surface_libre[1][3], surface_libre[2][3], surface_libre[1][4], surface_libre[2][4]);
			TraceSegment(WHITE, surface_libre[1][4], surface_libre[2][4], surface_libre[1][1], surface_libre[2][1]);
			for (no=1;no<=Houle.nb_point-1;no=no+2)
				{ 
				/*trace des barres transversales*/
				deb = no;
				fin = no+1;
				TraceSegment(BLUE, Houle.U[deb][pa], Houle.V[deb][pa], Houle.U[fin][pa], Houle.V[fin][pa]);
				//TraceSegment(BLUE, Houle.U[no][pa], Houle.V[no][pa], Houle.U[no+1][pa], Houle.V[no+1][pa]);
				/*printf("Houle %lf %lf %lf \n",Houle.U[deb][pa], Houle.V[deb][pa], Houle.U[fin][pa], Houle.V[fin][pa]);*/
				}
			for (no=1;no<=Houle.nb_point-3;no=no+2)
				{ 
				/*trace des segments paralleles a la houle*/
				deb = no;
				fin = no+2;
				/*TraceSegment(RED, Houle.U[deb][pa], Houle.V[deb][pa], Houle.U[fin][pa], Houle.V[fin][pa]);*/
				/*trace des segments paralleles a la houle*/
				deb = no+1;
				fin = no+3;
				/*TraceSegment(GREEN, Houle.U[deb][pa], Houle.V[deb][pa], Houle.U[fin][pa], Houle.V[fin][pa]);*/
				}
			}
  		}
  	else
  		{
		printf("There is no dynamics: this cursor is not operant \n");
  		}
	}

void Entry_Temps(Widget ww, char *string, void *junk)
	{
	/*prend la chaine de caractere dans MakeStringEntry la transforme en float
	et fait une rotation de cette valeur*/



  	double val;
  	double valinter;
	float valf;
 	void *me;
 
  	/*printf("entry = %s\n",string);*/
  	val = atof(string);
	
	valinter = val - Debutstockage;	
	

	valf = (float) valinter/(Finstockage-Debutstockage) ;
 	printf("valf = %f,\n",valf);


	edit_temps1(ww, valf, me);


	char text[10];
	sprintf(text,"%7.2f",val);  
  	SetStringEntry(w[91], text);

	}


void edit_animation(Widget w, void *data)
	{

 	TagList tags5[] = 
  		{
    		{TAG_FLOAT,	"ralenti d animation:",	&ralenti_animation ,  	TAG_FLOAT}, 
    		{TAG_DONE,	NULL,           	NULL,     		TAG_FLOAT}
  		};
    	if(GetValues_2(tags5))    		printf("Cancelled\n");
  	else					printf("ralenti_animation  : %lf\n", ralenti_animation); 
  	
	}

void edit_nb_animation(Widget w, void *data)
	{

  	TagList tags[] = 
  		{
    		{TAG_INT,	"cycles nb:",		&nb_animation ,  	TAG_INIT}, 
    		{TAG_DONE,	NULL,           	NULL,     		TAG_NOINIT}
  		};
    	if(GetValues_2(tags))    			printf("Cancelled\n");
  	else			      			printf("cycles nb  : %d\n", nb_animation); 

  	TagList tags2[] = 
  		{
    		{TAG_FLOAT,	"animation start:",	&depart_anim_sec ,  	TAG_FLOAT}, 
    		{TAG_DONE,	NULL,           	NULL,     		TAG_FLOAT}
  		};
    	if(GetValues_2(tags2))    			printf("Cancelled\n");
  	else			      			printf("animation start  : %7.2f\n", depart_anim_sec); 

  	TagList tags3[] = 
  		{
    		{TAG_FLOAT,	"animation end:",	&fin_anim_sec ,  	TAG_FLOAT}, 
    		{TAG_DONE,	NULL,           	NULL,     		TAG_FLOAT}
  		};
    	if(GetValues_2(tags3))    			printf("Cancelled\n");
  	else			      			printf("animation end  : %7.2f\n", fin_anim_sec); 

  	TagList tags4[] = 
  		{
    		{TAG_INT,	"step between images:",	&step_animation ,  	TAG_INIT}, 
    		{TAG_DONE,	NULL,           	NULL,     		TAG_NOINIT}
  		};
    	if(GetValues_2(tags4))    			printf("Cancelled\n");
  	else			      			printf("step between images  : %d\n", step_animation); 

 	TagList tags5[] = 
  		{
    		{TAG_FLOAT,	"ralenti d animation:",	&ralenti_animation ,  	TAG_FLOAT}, 
    		{TAG_DONE,	NULL,           	NULL,     		TAG_FLOAT}
  		};

	if (floor(1.0/(Passtockage*ralenti_animation)) < 1)
	{
		ralenti_animation = 1.0;
	}

    	if(GetValues_2(tags5))    		printf("Cancelled\n");
  	else					printf("ralenti_animation  : %lf\n", ralenti_animation); 
  	

	depart_anim = (1+ ((nbtemps-1) * ((depart_anim_sec - Debutstockage)/(Finstockage-Debutstockage))));
		
	fin_anim = (1+ ((nbtemps-1) * ((fin_anim_sec - Debutstockage)/(Finstockage-Debutstockage))));


	}

void edit_eigenvalues(Widget w, void *data)
	{
  	TagList tags[] = 
  		{
    		{TAG_INT,	"no eigenvector:",	&no_eigenvalue ,  	TAG_INIT}, 
    		{TAG_DONE,	NULL,           	NULL,     		TAG_NOINIT}
  		};
    	if(GetValues_2(tags))    			printf("Cancelled\n");
  	else			      			printf("no eigenvector  : %d\n", no_eigenvalue); 
	if (no_eigenvalue > Structure.eigenvalues) no_eigenvalue = Structure.eigenvalues;
  	TagList tags2[] = 
  		{
    		{TAG_FLOAT,	"scale_eigenvalue:",	&scale_eigenvalue ,  	TAG_FLOAT}, 
    		{TAG_DONE,	NULL,           	NULL,     		TAG_FLOAT}
  		};
    	if(GetValues_2(tags2))    			printf("Cancelled\n");
  	else			      			printf("scale_eigenvalue  : %7.2f\n", scale_eigenvalue); 

	}

