#define PRINCIPAL 1
#include <locale.h>            /* <--- INDISPENSABLE pour setlocale */
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
    		setlocale(LC_NUMERIC, "C");
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
    		setlocale(LC_NUMERIC, "C");
		}
	}




