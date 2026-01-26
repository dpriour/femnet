#define PRINCIPAL 0
#include "4c19.h"
//writes blockMeshDict and snappyHexMeshDict files
void meshOF()
	{
    char tonom[1000];
  	int j,k,pa;
    double ux,uy,uz,vx,vy,vz,dx,dy,dz;

  	FILE *f3;
//writes blockMeshDict file///////////////////////////////////////////////////////////////////////////////////////
        /* last modified K. Breddermann 16.06.2022 */

            strcpy(tonom,Structure.pathOFc);
            strcat(tonom,"system/blockMeshDict");
          	printf(" \n");
          	//printf("%s %s \n","fichier ",tonom);
        if(Structure.rigOF == 1)
            {
            printf("rig is taken into account\n");        
        /// identify max and min extend of rig + body to calculate fluid volume extend//////// 
        /// ux: max extend in x-direction, vx: min extend in x-direction
            ux= Noeud[1].x;
            vx= Noeud[1].x;
            uy= Noeud[1].y;
            vy= Noeud[1].y;
            uz= Noeud[1].z;
            vz= Noeud[1].z;   
            for (j = 1 ; j<= NOMBRE_NOEUDS ; j++) 
	          	    	{  
                        if(Noeud[j].x >= ux) ux= Noeud[j].x;
                        if(Noeud[j].x <= vx) vx= Noeud[j].x;
                        if(Noeud[j].y >= uy) uy= Noeud[j].y;
                        if(Noeud[j].y <= vy) vy= Noeud[j].y;
                        if(Noeud[j].z >= uz) uz= Noeud[j].z;
                        if(Noeud[j].z <= vz) vz= Noeud[j].z; 
                        }            
            printf("%lf %lf %lf %lf %lf %lf\n",ux,vx,uy,vy,uz,vz);
            }
            else{
            //printf("no rig is taken into account\n");
       /// identify max and min extend of rig + body to calculate fluid volume extend//////// 
            ux=Noeud[Surface[1].extremite[1]].x;
            vx=Noeud[Surface[1].extremite[1]].x;
            uy=Noeud[Surface[1].extremite[1]].y;
            vy=Noeud[Surface[1].extremite[1]].y;
            uz=Noeud[Surface[1].extremite[1]].z;
            vz=Noeud[Surface[1].extremite[1]].z;    
            for (k = 1 ; k<= 3 ; k++){            
            for (j = 1 ; j<= NOMBRE_SURFACES ; j++) 
	          	    	{                             
                            if(Noeud[Surface[j].extremite[k]].x>=ux) ux=Noeud[Surface[j].extremite[k]].x;
                            if(Noeud[Surface[j].extremite[k]].x<=vx) vx=Noeud[Surface[j].extremite[k]].x;
                            if(Noeud[Surface[j].extremite[k]].y>=uy) uy=Noeud[Surface[j].extremite[k]].y;
                            if(Noeud[Surface[j].extremite[k]].y<=vy) vy=Noeud[Surface[j].extremite[k]].y;
                            if(Noeud[Surface[j].extremite[k]].z>=uz) uz=Noeud[Surface[j].extremite[k]].z;
                            if(Noeud[Surface[j].extremite[k]].z<=vz) vz=Noeud[Surface[j].extremite[k]].z;
                            
                         }
                   }    
            printf("%lf %lf %lf %lf %lf %lf\n",ux,vx,uy,vy,uz,vz);
            }
          /// define CFD fluid domain size  
            dx=ux-vx;
            dy=uy-vy;
            dz=uz-vz;

            ux=ux+8*dx;
            vx=vx-3*dx;
            if(-0.0001<=uy && uy<=0.0001){uy=0;}  //take symmetry plane into account - if any
            else{uy=uy+2*dy;}
            if(-0.0001<=vy && vy<=0.0001){vy=0;}  //take symmetry plane into account - if any
            else{vy=vy-2*dy;}
            if(vz-6*dz>=-1*Houle.depth && Houle.depth>=8){vz=vz-6*dz;}
            else{vz=-1*(Houle.depth+0.1);} //Houle.depth+0.1 because due to the bottom stiffness there is a penetration of the structure into the bottom allowed          
            if(uz+6*dz<=0 && uz+dx<=0){uz=uz+6*dz;}
            else{uz=0;}
    
            printf("%.1lf %.1lf %.1lf %.1lf %.1lf %.1lf\n",ux,vx,uy,vy,uz,vz);        
    
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
	        fprintf(f3,"    object      blockMeshDict;\n");
	        fprintf(f3,"}\n");
	        fprintf(f3,"// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //\n");
	        fprintf(f3,"\n");
	        fprintf(f3,"scale 1;\n");
	        fprintf(f3,"\n");
	        fprintf(f3,"// block size\n");
	        fprintf(f3,"// water flows along x and the domain is symmetric about y and z\n");
	        fprintf(f3,"xmin   %.1lf;\n",vx);
	        fprintf(f3,"xmax   %.1lf;\n",ux);
	        fprintf(f3,"ymin   %.1lf;\n",vy);
	        fprintf(f3,"ymax    %.1lf;\n",uy);
	        fprintf(f3,"zmin   %.1lf;\n",vz);
	        fprintf(f3,"zmax    %.1lf;\n",uz);
	        fprintf(f3,"\n");
	        fprintf(f3,"vertices\n");
	        fprintf(f3,"(\n");
	        fprintf(f3,"    ($xmin $ymin $zmin) // 0\n");
	        fprintf(f3,"    ($xmax $ymin $zmin) // 1\n");
	        fprintf(f3,"    ($xmax $ymax $zmin) // 2\n");
	        fprintf(f3,"    ($xmin $ymax $zmin) // 3\n");
	        fprintf(f3,"    ($xmin $ymin $zmax) // 4\n");
	        fprintf(f3,"    ($xmax $ymin $zmax) // 5\n");
	        fprintf(f3,"    ($xmax $ymax $zmax) // 6\n");
	        fprintf(f3,"    ($xmin $ymax $zmax) // 7\n");
	        fprintf(f3,");\n");
	        fprintf(f3,"\n");
	        fprintf(f3,"// number of cells (cell size 0.10 m)\n");
	        fprintf(f3,"xcells  130;\n");
	        fprintf(f3,"ycells   36;\n");
	        fprintf(f3,"zcells   54;\n");
	        fprintf(f3,"\n");
	        fprintf(f3,"blocks\n");
	        fprintf(f3,"(\n");
	        fprintf(f3,"    hex (0 1 2 3 4 5 6 7) ($xcells $ycells $zcells) simpleGrading (1 1 1)\n");
	        fprintf(f3,"\n");
	        fprintf(f3,");\n");
	        fprintf(f3,"\n");
	        fprintf(f3,"edges\n");
	        fprintf(f3,"(\n");
	        fprintf(f3,");\n");
	        fprintf(f3,"\n");
	        fprintf(f3,"boundary\n");
	        fprintf(f3,"(\n");
	        fprintf(f3,"    inlet\n");
	        fprintf(f3,"    {\n");
	        fprintf(f3,"        type patch;\n");
	        fprintf(f3,"        faces\n");
	        fprintf(f3,"        (\n");
	        fprintf(f3,"            (0 4 7 3)\n");
	        fprintf(f3,"        );\n");
	        fprintf(f3,"    }\n");
	        fprintf(f3,"\n");
	        fprintf(f3,"    outlet\n");
	        fprintf(f3,"    {\n");
	        fprintf(f3,"       type patch;\n");
	        fprintf(f3,"        faces\n");
	        fprintf(f3,"        (\n");
	        fprintf(f3,"            (2 6 5 1)\n");
	        fprintf(f3,"        );\n");
	        fprintf(f3,"    }\n");
	        fprintf(f3,"\n");
	        fprintf(f3,"    top\n");
	        fprintf(f3,"    {\n");
	        fprintf(f3,"        type wall;\n");
	        fprintf(f3,"        faces\n");
	        fprintf(f3,"        (\n");
	        fprintf(f3,"            (4 5 6 7)   \n");         
	        fprintf(f3,"        );\n");
	        fprintf(f3,"    }\n");
	        fprintf(f3,"\n");
	        fprintf(f3,"    bottom\n");
	        fprintf(f3,"    {\n");
	        fprintf(f3,"        type wall;\n");
	        fprintf(f3,"        faces\n");
	        fprintf(f3,"        (\n");
	        fprintf(f3,"            (0 3 2 1)\n");
	        fprintf(f3,"        );\n");
	        fprintf(f3,"    }\n");
	        fprintf(f3,"\n");
	        fprintf(f3,"    frontAndBack\n");
	        fprintf(f3,"    {\n");
	        fprintf(f3,"        type wall;\n");
	        fprintf(f3,"        faces\n");
	        fprintf(f3,"        (\n");
	        fprintf(f3,"            (1 5 4 0)\n");
	        fprintf(f3,"            (3 7 6 2)\n");
	        fprintf(f3,"        );\n");
	        fprintf(f3,"    }\n");
	        fprintf(f3,");\n");
	        fprintf(f3,"\n");
	        fprintf(f3,"mergePatchPairs\n");
	        fprintf(f3,"(\n");
	        fprintf(f3,");\n");
	        fprintf(f3,"\n");
	        fprintf(f3,"// ************************************************************************* //\n");

            fclose(f3);
           	printf("blockMeshDict %s written\n",tonom);
//blockMeshDict file////////////////////////////////////////////////////////////////////////////////////
//
//SnappyHexMeshDict file///////////////////////////////////////////////////////////////////////////////////////
        /* modified K. Breddermann 04.05.2022 */
            memset(tonom,0,strlen(tonom)); //clear tonom
            strcpy(tonom,Structure.pathOFc);
            strcat(tonom,"system/snappyHexMeshDict");
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
	        fprintf(f3,"    object      snappyHexMeshDict;\n");
	        fprintf(f3,"}\n");
	        fprintf(f3,"// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //\n");
	        fprintf(f3,"\n");
	        fprintf(f3,"castellatedMesh true;\n");
	        fprintf(f3,"snap            true;\n");
	        fprintf(f3,"addLayers       false; // param_meshRefinementLevel ? true : false\n");
	        fprintf(f3,"\n");
	        fprintf(f3,"geometry\n");
	        fprintf(f3,"{\n");
	        for (pa = 1 ; pa<= Structure.NbTypesurf ; pa++)
                {	
	        fprintf(f3,"    panel%d.stl\n",pa);
	        fprintf(f3,"    {\n");
	        fprintf(f3,"    type triSurfaceMesh;\n");
	        fprintf(f3,"    name porous_pa%d;\n",pa);
	        fprintf(f3,"    }\n");
	        }
	        fprintf(f3,"};\n");
	        fprintf(f3,"\n");
	        fprintf(f3,"// Settings for the castellatedMesh generation.\n");
	        fprintf(f3,"castellatedMeshControls\n");
	        fprintf(f3,"{\n");
	        fprintf(f3,"\n");
	        fprintf(f3,"    // Refinement parameters\n");
	        fprintf(f3,"    // ~~~~~~~~~~~~~~~~~~~~~\n");
	        fprintf(f3,"\n");
	        fprintf(f3,"    maxLocalCells 3000000;\n");
	        fprintf(f3,"\n");
	        fprintf(f3,"    maxGlobalCells 26000000;\n");
	        fprintf(f3,"\n");
	        fprintf(f3,"    minRefinementCells 10;\n");
	        fprintf(f3,"\n");
	        fprintf(f3,"    maxLoadUnbalance 0.10;\n");
	        fprintf(f3,"\n");
	        fprintf(f3,"    nCellsBetweenLevels 3;\n");
	        fprintf(f3,"\n");
	        fprintf(f3,"    // Explicit feature edge refinement\n");
	        fprintf(f3,"    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	        fprintf(f3,"\n");
	        fprintf(f3,"    features\n");
	        fprintf(f3,"    (\n");
	        fprintf(f3,"    );\n");
	        fprintf(f3,"\n");
	        fprintf(f3,"    // Surface based refinement\n");
	        fprintf(f3,"    // ~~~~~~~~~~~~~~~~~~~~~~~~\n");
	        fprintf(f3,"    refinementSurfaces\n");
	        fprintf(f3,"    {\n");
	        for (pa = 1 ; pa<= Structure.NbTypesurf ; pa++)
                {
	        fprintf(f3,"       porous_pa%d\n",pa);
	        fprintf(f3,"       {\n");
	        fprintf(f3,"          level (3 3);\n");
	        fprintf(f3,"	  faceType internal;\n");
	        fprintf(f3,"          //cellzone net;\n");
	        fprintf(f3,"          faceZone porous_pa%d;\n",pa);
	        fprintf(f3,"       }\n");
	        }
	        fprintf(f3,"    }\n");
	        fprintf(f3,"\n");
	        fprintf(f3,"    // Resolve sharp angles\n");
	        fprintf(f3,"    resolveFeatureAngle 30;\n");
	        fprintf(f3,"\n");
	        fprintf(f3,"    // Region-wise refinement\n");
	        fprintf(f3,"    // ~~~~~~~~~~~~~~~~~~~~~~\n");
	        fprintf(f3,"    refinementRegions\n");
	        fprintf(f3,"    {\n");
	        for (pa = 1 ; pa<= Structure.NbTypesurf ; pa++)
                {
	        fprintf(f3,"       porous_pa%d\n",pa);
	        fprintf(f3,"       {\n");
	        fprintf(f3,"          mode distance;\n");
	        fprintf(f3,"          levels ((0.3 2) (0.6 1));\n");
	        fprintf(f3,"       }\n");
	        }
	        fprintf(f3,"    }\n");
	        fprintf(f3,"\n");
	        fprintf(f3,"    // Mesh selection\n");
	        fprintf(f3,"    // ~~~~~~~~~~~~~~\n");
	        fprintf(f3,"\n");
	        fprintf(f3,"    locationInMesh (-1.0001 1.0001 -0.60001);\n");
	        fprintf(f3,"\n");
	        fprintf(f3,"    allowFreeStandingZoneFaces true;\n");
	        fprintf(f3,"}\n");
	        fprintf(f3,"\n");
	        fprintf(f3,"// Settings for the snapping.\n");
	        fprintf(f3,"snapControls\n");
	        fprintf(f3,"{\n");
	        fprintf(f3,"\n");
	        fprintf(f3,"    nSmoothPatch 4;\n");
	        fprintf(f3,"\n");
	        fprintf(f3,"    tolerance 1.5;\n");
	        fprintf(f3,"\n");
	        fprintf(f3,"    nSolveIter 50;\n");
	        fprintf(f3,"\n");
	        fprintf(f3,"    nRelaxIter 5;\n");
	        fprintf(f3,"\n");
	        fprintf(f3,"    // Feature snapping\n");
	        fprintf(f3,"\n");
	        fprintf(f3,"        nFeatureSnapIter 10;\n");
	        fprintf(f3,"\n");
	        fprintf(f3,"        implicitFeatureSnap true;\n");
	        fprintf(f3,"\n");
	        fprintf(f3,"        explicitFeatureSnap true;\n");
	        fprintf(f3,"\n");
	        fprintf(f3,"        multiRegionFeatureSnap false;\n");
	        fprintf(f3,"}\n");
	        fprintf(f3,"\n");
	        fprintf(f3,"// Settings for the layer addition.\n");
	        fprintf(f3,"addLayersControls\n");
	        fprintf(f3,"{\n");
	        fprintf(f3,"    relativeSizes true;\n");
	        fprintf(f3,"\n");
	        fprintf(f3,"    layers\n");
	        fprintf(f3,"    {\n");
	        fprintf(f3,"\n");
	        fprintf(f3,"    }\n");
	        fprintf(f3,"\n");
	        fprintf(f3,"    // Expansion factor for layer mesh\n");
	        fprintf(f3,"    expansionRatio 1.0;\n");
	        fprintf(f3,"\n");
	        fprintf(f3,"    finalLayerThickness 0.01;\n");
	        fprintf(f3,"\n");
	        fprintf(f3,"    minThickness 0.01;\n");
	        fprintf(f3,"\n");
	        fprintf(f3,"    nGrow 0;\n");
	        fprintf(f3,"\n");
	        fprintf(f3,"    // Advanced settings\n");
	        fprintf(f3,"\n");
	        fprintf(f3,"    featureAngle 60;\n");
	        fprintf(f3,"\n");
	        fprintf(f3,"    slipFeatureAngle 30;\n");
	        fprintf(f3,"\n");
	        fprintf(f3,"    nRelaxIter 3;\n");
	        fprintf(f3,"\n");
	        fprintf(f3,"    nSmoothSurfaceNormals 1;\n");
	        fprintf(f3,"\n");
	        fprintf(f3,"    nSmoothNormals 3;\n");
	        fprintf(f3,"\n");
	        fprintf(f3,"    nSmoothThickness 10;\n");
	        fprintf(f3,"\n");
	        fprintf(f3,"    maxFaceThicknessRatio 0.5;\n");
	        fprintf(f3,"\n");
	        fprintf(f3,"    maxThicknessToMedialRatio 0.3;\n");
	        fprintf(f3,"\n");
	        fprintf(f3,"    minMedianAxisAngle 90;\n");
	        fprintf(f3,"\n");
	        fprintf(f3,"    nBufferCellsNoExtrude 0;\n");
	        fprintf(f3,"\n");
	        fprintf(f3,"    nLayerIter 10;\n");
	        fprintf(f3,"}\n");
	        fprintf(f3,"\n");
	        fprintf(f3,"// Generic mesh quality settings. At any undoable phase these determine\n");
	        fprintf(f3,"// where to undo.\n");
	        fprintf(f3,"meshQualityControls\n");
	        fprintf(f3,"{\n");
	        fprintf(f3,"    #include \"meshQualityDict\"\n");
	        fprintf(f3,"     maxNonOrtho         69;\n");
	        fprintf(f3,"     maxBoundarySkewness 20;\n");
	        fprintf(f3,"     maxInternalSkewness 5;\n");
	        fprintf(f3,"     maxConcave          80;\n");
	        fprintf(f3,"\n");
	        fprintf(f3,"    // Advanced\n");
	        fprintf(f3,"\n");
	        fprintf(f3,"    //- Number of error distribution iterations\n");
	        fprintf(f3,"    nSmoothScale 4;\n");
	        fprintf(f3,"    //- Amount to scale back displacement at error points\n");
	        fprintf(f3,"    errorReduction 0.75;\n");
	        fprintf(f3,"}\n");
	        fprintf(f3,"\n");
	        fprintf(f3,"\n");
	        fprintf(f3,"// Advanced\n");
	        fprintf(f3,"\n");
	        fprintf(f3,"// Write flags\n");
	        fprintf(f3,"writeFlags\n");
	        fprintf(f3,"(\n");
	        fprintf(f3,"    scalarLevels\n");
	        fprintf(f3,"    layerSets\n");
	        fprintf(f3,"    layerFields     // write volScalarField for layer coverage\n");
	        fprintf(f3,");\n");
	        fprintf(f3,"\n");
	        fprintf(f3,"\n");
	        fprintf(f3,"// Merge tolerance. Is fraction of overall bounding box of initial mesh.\n");
	        fprintf(f3,"// Note: the write tolerance needs to be higher than this.\n");
	        fprintf(f3,"mergeTolerance 1e-6;\n");
	        fprintf(f3,"\n");
	        fprintf(f3,"\n");
	        fprintf(f3,"// ************************************************************************* //\n");

            fclose(f3);
           	printf("snappyHexMeshDict %s written\n",tonom);
}
//snappyHexMeshDict file////////////////////////////////////////////////////////////////////////////////////
