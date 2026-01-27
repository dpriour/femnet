#define PRINCIPAL 1
#include "batz.h"              /* where program specific stuff is defined */

void init_display(int argc, char **argv, MyProgram *me);

int main(int argc, char **argv)
	{
	int no;
	MyProgram mydata;
	Structure.graphic = argc;
	printf("Structure.graphic : %d\n", argc);
	
	if (argc == 1)
		{
		Flag_Fichier_initial_charge = 0;
		Flag_Fichier_final_charge = 0;
		clip.gauche = 	0.0 + marge/2.0;
		clip.bas = 	0.0 + marge/2.0;
		clip.droite = 	1.0 - marge/2.0;
		clip.haut = 	1.0 - marge/2.0;
		flag_clip = 	1;
		mode_portrait = TRUE;
		init_display(argc, argv, &mydata);  /* setup the display */

		MainLoop();                        /* go right into the main loop */
		return 1;
  		}
	if (argc == 2)
		{
		strcpy(Structure.nomfichier1,argv[1]);
    		printf("%s 				%s\n","fichier1 ",Structure.nomfichier1);
		Flag_Fichier_initial_charge = 0;
		Flag_Fichier_final_charge = 0;
		clip.gauche = 	0.0 + marge/2.0;
		clip.bas = 	0.0 + marge/2.0;
		clip.droite = 	1.0 - marge/2.0;
		clip.haut = 	1.0 - marge/2.0;
		flag_clip = 	1;
		mode_portrait = TRUE;
		init_display_text(argc, argv, &mydata);  	/* setup the display */
		RESOLUTION_X_FEN = X_SIZE ;
		RESOLUTION_Y_FEN = Y_SIZE;
		charger_final();/**/

		angle_x = 270.0;		angle_y = 0.0;		
		rotation();
		printf("binx = %8.2f; biny = %8.2f; ",binx,biny);	printf("baxx = %8.2f; baxy = %8.2f; \n",baxx,baxy); 
		binx =  -260.29; biny =  -352.06; baxx =   516.03; baxy =   645.35; 
		rotation_fils();
		tri();
		Genere_ps();
		}
	}




