#define PRINCIPAL 1
#include "phobos.h"

int main(int argc,char **argv)
{  
    MyProgram mydata;
    Structure.graphic=argc;
    if(argc==1) {
        gtk_init(&argc,&argv);
    	setlocale(LC_NUMERIC, "C");
        //Structure.graphic=argc;
        Flag_Fichier_charge=0; Flag_Mesh=0;
        init_display(argc,argv,&mydata);
        ShowDisplay();
        MainLoop();
        return 0;
    }
    if(argc==2||argc==3) {
    	setlocale(LC_NUMERIC, "C");
        strcpy(Structure.nomfichier1,argv[1]);
        charger(Structure.nomfichier1);
        filet_contour(); maillage(); filet_interne(); numerotation_globale();
        numerotation_balls(); nb_maille_total(); creer_fichier_phobos();
    }
    if(argc==3) {
    	setlocale(LC_NUMERIC, "C");
        strcpy(Structure.nomfichier2,argv[2]);
        charger_mdgsta(); creer_fichier_sta();
    }
    return 0;
}
