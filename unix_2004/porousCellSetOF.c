#define PRINCIPAL 0
#include "4c19.h"
//writes stl and panel stl files
void porousCellSetOF()
	{
    char    tonom[1000];
  	int     j,pa;

    FILE *f3;
//topoSetDict file///////////////////////////////////////////////////////////////////////////////////////
        /* modified K. Breddermann 04.05.2022 */
            strcpy(tonom,Structure.pathOFc);
            strcat(tonom,"system/topoSetDict");
            /*j=strlen(tonom);
            while ((tonom[j])!='.' && j>0) j--;
            if (tonom[j]=='.') tonom[j]=0;
          	strcat(tonom,".stl");*/
          	printf(" \n");
          	//printf("%s %s \n","fichier ",tonom);
          	f3 = fopen(tonom,"w");
            if (f3 < 0)
                {   
                printf("\n");
                printf("Could not open the file %s.\n",tonom);
                }
	        fprintf(f3,"/*--------------------------------*- C++ -*----------------------------------*\\\n");   
	        fprintf(f3,"| =========                 |                                                 |\n");
	        fprintf(f3,"| \\\\      /  F ield         | OpenFOAM add-on for FEMNET                      |\n");
	        fprintf(f3,"|  \\\\    /   O peration     | OpenFOAM version:  v2012                        |\n");
	        fprintf(f3,"|   \\\\  /    A nd           | Web:      www.lmt.uni-rostock.de                |\n");
	        fprintf(f3,"|    \\\\/     M anipulation  |                                                 |\n");
	        fprintf(f3,"\\*---------------------------------------------------------------------------*/\n");
	        fprintf(f3,"FoamFile\n");
	        fprintf(f3,"{\n");
	        fprintf(f3,"    version     2.0;\n");
	        fprintf(f3,"    format      ascii;\n");
	        fprintf(f3,"    class       dictionary;\n");
	        fprintf(f3,"    object      topoSetDict;\n");
	        fprintf(f3,"}\n");
	        fprintf(f3,"// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //\n");
	        fprintf(f3,"\n");
	        fprintf(f3,"actions\n");
	        fprintf(f3,"(\n");
	        for (pa = 1 ; pa<= Structure.NbTypesurf ; pa++)
                {
	        fprintf(f3,"    {\n");
	        fprintf(f3,"        name    panel%d;\n",pa);
	        fprintf(f3,"        type    cellSet;\n");
	        fprintf(f3,"        action  new;\n");
	        fprintf(f3,"        source  surfaceToCell;\n");
	        fprintf(f3,"        sourceInfo\n");
	        fprintf(f3,"        {\n");
	        fprintf(f3,"            file \"constant/triSurface/panel%d.stl\";\n",pa);
	        fprintf(f3,"            useSurfaceOrientation false;  // use closed surface inside/outside\n");
	        fprintf(f3,"                                      // test (ignores includeCut,\n");
	        fprintf(f3,"                                    // outsidePoints)\n");
	        fprintf(f3,"            outsidePoints   ((0.662356 -0.319976 -0.0494499));    // definition of outside 1 -0.6 -0.6\n");
	        fprintf(f3,"            includeCut      true;              // cells cut by surface\n");
	        fprintf(f3,"            includeInside   false;              // cells not on outside of surf\n");
	        fprintf(f3,"            includeOutside  false;              // cells on outside of surf\n");
	        fprintf(f3,"            nearDistance    0.025;                 // cells with centre near surf\n");
	        fprintf(f3,"                                            // (set to -1 if not used)\n");
	        fprintf(f3,"            curvature       -100;\n"); 
	        fprintf(f3,"        }\n");
	        fprintf(f3,"    }\n");
	        fprintf(f3,"    {\n");
	        fprintf(f3,"        name    porous_pa%d;\n",pa);
	        fprintf(f3,"        type    cellZoneSet;\n");
	        fprintf(f3,"        action  new;\n");
	        fprintf(f3,"        source  setToCellZone;\n");
	        fprintf(f3,"        sourceInfo\n");
	        fprintf(f3,"        {\n");
	        fprintf(f3,"            set panel%d;           // name of cellSet\n",pa);
	        fprintf(f3,"        }\n");
	        fprintf(f3,"   }\n");
	        }
	        fprintf(f3,");\n");
	        fprintf(f3,"\n");
	        fprintf(f3,"// ************************************************************************* //\n");
            fclose(f3);
           	printf("topoSetDict %s written\n",tonom);
//topoSetDict file////////////////////////////////////////////////////////////////////////////////////
//
//create fvOptions file//////////////////////////////////////////////////////////////////////////////////////
/* modified K. Breddermann 09.05.2022 */
            memset(tonom,0,strlen(tonom));            
            strcpy(tonom,Structure.pathOFc);
            strcat(tonom,"constant/fvOptions");
            /*j=strlen(tonom);
            while ((tonom[j])!='.' && j>0) j--;
            if (tonom[j]=='.') tonom[j]=0;
          	strcat(tonom,".stl");*/
          	printf(" \n");
          	//printf("%s %s \n","fichier ",tonom);

          	f3 = fopen(tonom,"w");
            if (f3 < 0)
                {   
                printf("\n");
                printf("Could not open the file %s.\n",tonom);
                }
	        fprintf(f3,"/*--------------------------------*- C++ -*----------------------------------*\\\n");   
	        fprintf(f3,"| =========                 |                                                 |\n");
	        fprintf(f3,"| \\\\      /  F ield         | OpenFOAM add-on for FEMNET                      |\n");
	        fprintf(f3,"|  \\\\    /   O peration     | OpenFOAM version:  v2012                        |\n");
	        fprintf(f3,"|   \\\\  /    A nd           | Web:      www.lmt.uni-rostock.de                |\n");
	        fprintf(f3,"|    \\\\/     M anipulation  |                                                 |\n");
	        fprintf(f3,"\\*---------------------------------------------------------------------------*/\n");
	        fprintf(f3,"FoamFile\n");
	        fprintf(f3,"{\n");
	        fprintf(f3,"    version     2.0;\n");
	        fprintf(f3,"    format      ascii;\n");
	        fprintf(f3,"    class       dictionary;\n");
	        fprintf(f3,"    location    \"constant\";\n");
	        fprintf(f3,"    object      fvOptions;\n");
	        fprintf(f3,"}\n");
	        fprintf(f3,"// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //\n");
	        fprintf(f3,"\n");
	        for (pa = 1 ; pa<= Structure.NbTypesurf ; pa++)
                {
	        fprintf(f3,"porosity%d\n",pa);
	        fprintf(f3,"{\n");
	        fprintf(f3,"    type            explicitPorositySource;\n");
	        fprintf(f3,"\n");
	        fprintf(f3,"    explicitPorositySourceCoeffs\n");
	        fprintf(f3,"    {\n");
	        fprintf(f3,"        selectionMode   cellZone;\n");
	        fprintf(f3,"\n");
	        fprintf(f3,"        cellZone        porous_pa%d;\n",pa);
	        fprintf(f3,"\n");
	        fprintf(f3,"        type            DarcyForchheimer;\n");
	        fprintf(f3,"\n");
	        fprintf(f3,"        // D 100;  // Very little blockage\n");
	        fprintf(f3,"        // D 200;  // Some blockage but steady flow\n");
	        fprintf(f3,"        // D 500;  // Slight waviness in the far wake\n");
	        fprintf(f3,"        D 1000; // Fully shedding behavior\n");
	        fprintf(f3,"\n");
	        fprintf(f3,"        d   ($D $D $D);\n");
	        fprintf(f3,"        f   (0 0 0);\n");
	        fprintf(f3,"\n");
	        fprintf(f3,"        coordinateSystem\n");
	        fprintf(f3,"        {\n");
	        fprintf(f3,"            origin  (0 0 0);\n");
	        fprintf(f3,"\n");
	        fprintf(f3,"            rotation\n");
	        fprintf(f3,"            {\n");
	        fprintf(f3,"                type    none;\n");
	        fprintf(f3,"            }\n");
	        fprintf(f3,"        }\n");
	        fprintf(f3,"    }\n");
	        fprintf(f3,"}\n");
	        }
	        fprintf(f3,"// ************************************************************************* //\n");

            fclose(f3);
           	printf("fvOptions %s written\n",tonom);
}
//fvOptions file////////////////////////////////////////////////////////////////////////////////////
