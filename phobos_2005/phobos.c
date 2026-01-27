#define PRINCIPAL 1
#include "phobos.h"              /* where program specific stuff is defined */


/*void init_display(int argc, char **argv, MyProgram *me);*/

void main(int argc, char **argv)
	{
	MyProgram mydata;
 	/*char nomfichier1[200],nomfichier2[200];*/
	printf("argc : %d\n", argc);
	Structure.graphic = argc;
	
	if (argc == 1)
		{
		Flag_Fichier_charge = 0;
		Flag_Mesh = 0;
		init_display(argc, argv, &mydata);  /* setup the display */
		MainLoop();                         /* go right into the main loop */
  		}
	if ((argc == 2) || (argc == 3))
		{
		strcpy(Structure.nomfichier1,argv[1]);
    		printf("%s 				%s\n","fichier1 ",Structure.nomfichier1);
  		charger(Structure.nomfichier1);                  		/*lecture des donnees initiales don*/
		filet_contour();
		maillage();
		filet_interne();
		numerotation_globale();
		numerotation_balls();
		nb_maille_total();
		creer_fichier_phobos();
  		}
	if (argc == 3)
		{
		strcpy(Structure.nomfichier2,argv[2]);
    		printf("%s 				%s\n","fichier2 ",Structure.nomfichier2);
		charger_mdgsta();
		creer_fichier_sta();
  		}
	}




