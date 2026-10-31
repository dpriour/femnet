#define PRINCIPAL 0
#include "4c19.h"
//files for porousBaffle application in OpenFOAM
void porousBaffleOF()
	{
    char    tonom[1000];
  	int     j,pa;

    FILE *f3;
//createBafflesDict file///////////////////////////////////////////////////////////////////////////////////////
        /* modified K. Breddermann 05.05.2022 */
            strcpy(tonom,Structure.pathOFc);
            strcat(tonom,"system/createBafflesDict");
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
	        fprintf(f3,"    object      createBafflesDict;\n");
	        fprintf(f3,"}\n");
	        fprintf(f3,"// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //\n");
	        fprintf(f3,"\n");
	        fprintf(f3,"// Whether to convert internal faces only (so leave boundary faces intact).\n");
	        fprintf(f3,"// This is only relevant if your face selection type can pick up boundary\n");
	        fprintf(f3,"// faces.\n");
	        fprintf(f3,"internalFacesOnly true;\n");
	        fprintf(f3,"\n");
	        fprintf(f3,"\n");
	        fprintf(f3,"// Baffles to create.\n");
	        fprintf(f3,"baffles\n");
	        fprintf(f3,"{\n");
	        fprintf(f3,"    cyclicFaces\n");
	        fprintf(f3,"    {\n");
	        fprintf(f3,"        //- Select faces and orientation through a searchableSurface\n");
	        fprintf(f3,"        type        faceZone;\n");
	        fprintf(f3,"        zoneName    porous_pa1;\n");
	        fprintf(f3,"\n");
	        fprintf(f3,"        patches\n");
	        fprintf(f3,"        {\n");
	        fprintf(f3,"            master\n");
	        fprintf(f3,"            {\n");
	        fprintf(f3,"                //- Master side patch\n");
	        fprintf(f3,"\n");
	        fprintf(f3,"                name            porous_pa1_half0;\n");
	        fprintf(f3,"                type            cyclic;\n");
	        fprintf(f3,"                neighbourPatch  porous_pa1_half1;\n");
	        fprintf(f3,"\n");
	        fprintf(f3,"                //- Optional override of added patchfields. If not specified\n");
	        fprintf(f3,"                //  any added patchfields are of type calculated.\n");
	        fprintf(f3,"                patchFields\n");
	        fprintf(f3,"                {\n");
	        fprintf(f3,"                    p\n");
	        fprintf(f3,"                    {\n");
	        fprintf(f3,"                        type            porousBafflePressure;\n");
	        fprintf(f3,"                        patchType       cyclic;\n");
	        fprintf(f3,"                        D               2;\n");
	        fprintf(f3,"                        I               1;\n");
	        fprintf(f3,"                        length          0.025;\n");
	        fprintf(f3,"                        uniformJump     true;\n");
	        fprintf(f3,"                        jump            uniform 0;\n");
	        fprintf(f3,"                        value           uniform 0;\n");
	        fprintf(f3,"                    }\n");
	        fprintf(f3,"                }\n");
	        fprintf(f3,"            }\n");
	        fprintf(f3,"            slave\n");
	        fprintf(f3,"            {\n");
	        fprintf(f3,"                //- Slave side patch\n");
	        fprintf(f3,"\n");
	        fprintf(f3,"                name            porous_pa1_half1;\n");
	        fprintf(f3,"                type            cyclic;\n");
	        fprintf(f3,"                neighbourPatch  porous_pa1_half0;\n");
	        fprintf(f3,"\n");
	        fprintf(f3,"                patchFields\n");
	        fprintf(f3,"                {\n");
	        fprintf(f3,"                    ${...master.patchFields}\n");
	        fprintf(f3,"                }\n");
	        fprintf(f3,"            }\n");
	        fprintf(f3,"        }\n");
	        fprintf(f3,"    }\n");
	        fprintf(f3,"}\n");
	        fprintf(f3,"\n");
	        fprintf(f3,"\n");
	        fprintf(f3,"// ************************************************************************* //\n");

            fclose(f3);
           	printf("createBafflesDict %s written\n",tonom);
}
//createBafflesDict file////////////////////////////////////////////////////////////////////////////////////

