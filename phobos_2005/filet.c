#define PRINCIPAL 0
#include "phobos.h"

void filet_contour()
	{
	/*defini les triangles poses sur le contour, 
	calcule les coordonnees en nb de mailles des sommets des triangles, 
	calcule */
	int pa,col,mode,no,np,intersection;
	REAL x0,y0,x1,y1,x2,y2,x3,y3,x4,y4,X2,Y2,X4,Y4;
	
	if (Structure.graphic == 1)
		{
		/*faire le chargement du fichier si ce n est pas fait*/
		mode = GetMenuItemChecked(w[1]);
		if (mode == 0) charger_phobos();
		}
	intersection = 0; /*no intersection a priori*/
	for (pa=1;pa<=Structure.NbTypesurf;pa++)
		{ 
		//printf("pa %d\n",pa);
		if (panneau[pa].flag_filet_contour == 0)
			{
			/*verification of the nodes of the contour*/
			for (no=1;no<=panneau[pa].nb_noeud_contour-2;no++)
				{
				/*first segment*/
				x1 = noeud[panneau[pa].noeud_contour[no+0]].u;	y1 = noeud[panneau[pa].noeud_contour[no+0]].v;
				x2 = noeud[panneau[pa].noeud_contour[no+1]].u;	y2 = noeud[panneau[pa].noeud_contour[no+1]].v;
				if ((no==1) && (panneau[pa].nb_noeud_contour>3))
					{
					/*dont verify the first segment with the last*/
					for (np=no+2;np<=panneau[pa].nb_noeud_contour-1;np++)
						{
						/*second segment*/
						x3 = noeud[panneau[pa].noeud_contour[np+0]].u;	y3 = noeud[panneau[pa].noeud_contour[np+0]].v;
						x4 = noeud[panneau[pa].noeud_contour[np+1]].u;	y4 = noeud[panneau[pa].noeud_contour[np+1]].v;
						X2 = x2-x1;	Y2 = y2-y1;
						X4 = x4-x3;	Y4 = y4-y3;
						if ((Y2*X4 - Y4*X2) != 0.0)
							{
							/*coordinates of the intersection of the first segement with the second segment*/
							y0 = (Y4*Y2*x1 - Y2*Y4*x3 - Y4*X2*y1 + Y2*X4*y3) / (Y2*X4 - Y4*X2);
							x0 = (Y2*x1*X4 - X2*Y4*x3 + X2*X4*y3 - X2*y1*X4) / (Y2*X4 - Y4*X2);
							if ((x1<x0) && (x2>x0) && (x3<x0) && (x4>x0)) intersection = 1;
							if ((x1<x0) && (x2>x0) && (x3>x0) && (x4<x0)) intersection = 1;
							if ((x1>x0) && (x2<x0) && (x3<x0) && (x4>x0)) intersection = 1;
							if ((x1>x0) && (x2<x0) && (x3>x0) && (x4<x0)) intersection = 1;
							if ((y1<y0) && (y2>y0) && (y3<y0) && (y4>y0)) intersection = 1;
							if ((y1<y0) && (y2>y0) && (y3>y0) && (y4<y0)) intersection = 1;
							if ((y1>y0) && (y2<y0) && (y3<y0) && (y4>y0)) intersection = 1;
							if ((y1>y0) && (y2<y0) && (y3>y0) && (y4<y0)) intersection = 1;

							if (intersection == 1)
								{
								printf("intersection of contour sides of panel %d: the modification is not valid \n",pa);
								/*printf("pt0 %f %f  \n", x0,y0);
								printf("pt1 %f %f  \n", x1,y1);
								printf("pt2 %f %f  \n", x2,y2);
								printf("pt3 %f %f  \n", x3,y3);
								printf("pt4 %f %f  \n", x4,y4);*/
								exit(0);
								}							
							}
						}
					}
				if ((no>1) && (panneau[pa].nb_noeud_contour>3))
					{
					/*verify up to the last*/
					for (np=no+2;np<=panneau[pa].nb_noeud_contour;np++)
						{
						/*second segment*/
						x3 = noeud[panneau[pa].noeud_contour[np+0]].u;	y3 = noeud[panneau[pa].noeud_contour[np+0]].v;
						if (np != panneau[pa].nb_noeud_contour)
							{
							x4 = noeud[panneau[pa].noeud_contour[np+1]].u;	y4 = noeud[panneau[pa].noeud_contour[np+1]].v;
							}
						if (np == panneau[pa].nb_noeud_contour)
							{
							x4 = noeud[panneau[pa].noeud_contour[1]].u;	y4 = noeud[panneau[pa].noeud_contour[1]].v;
							}
						X2 = x2-x1;	Y2 = y2-y1;
						X4 = x4-x3;	Y4 = y4-y3;
						if ((Y2*X4 - Y4*X2) != 0.0)
							{
							/*coordinates of the intersection of the first segement with the second segment*/
							y0 = (Y4*Y2*x1 - Y2*Y4*x3 - Y4*X2*y1 + Y2*X4*y3) / (Y2*X4 - Y4*X2);
							x0 = (Y2*x1*X4 - X2*Y4*x3 + X2*X4*y3 - X2*y1*X4) / (Y2*X4 - Y4*X2);
							if ((x1<x0) && (x2>x0) && (x3<x0) && (x4>x0)) intersection = 1;
							if ((x1<x0) && (x2>x0) && (x3>x0) && (x4<x0)) intersection = 1;
							if ((x1>x0) && (x2<x0) && (x3<x0) && (x4>x0)) intersection = 1;
							if ((x1>x0) && (x2<x0) && (x3>x0) && (x4<x0)) intersection = 1;
							if ((y1<y0) && (y2>y0) && (y3<y0) && (y4>y0)) intersection = 1;
							if ((y1<y0) && (y2>y0) && (y3>y0) && (y4<y0)) intersection = 1;
							if ((y1>y0) && (y2<y0) && (y3<y0) && (y4>y0)) intersection = 1;
							if ((y1>y0) && (y2<y0) && (y3>y0) && (y4<y0)) intersection = 1;

							if (intersection == 1)
								{
								printf("intersection of contour sides of panel %d: the modification is not valid \n",pa);
								/*printf("pt0 %f %f  \n", x0,y0);
								printf("pt1 %f %f  \n", x1,y1);
								printf("pt2 %f %f  \n", x2,y2);
								printf("pt3 %f %f  \n", x3,y3);
								printf("pt4 %f %f  \n", x4,y4);*/
								exit(0);
								}							
							}
						}
					}
				}
			if (intersection == 0) triangulation_contour(pa);
			}
		}
	for (pa=1;pa<=Structure.NbTypesurf_hexa;pa++)
		{ 
		if (pan_hexa[pa].flag_filet_contour == 0)
			{
			triangul_hexa_contour(pa);
			}
		}

	if (intersection == 0) fils_contour_calculer();
	if (Structure.graphic == 1)
		{
		SetMenuItemChecked(w[5],1);
		}
	}


void triangulation_contour(int pa)
	{
	/*defini les triangles poses sur le contour*/
	int deb,no;
	//printf("  panneau[pa].nb_noeud_contour : %8d  \n", panneau[pa].nb_noeud_contour );/**/
	in.numberofpoints = panneau[pa].nb_noeud_contour;
	in.numberofpointattributes = 0;
  	in.pointlist = (REAL *) malloc( in.numberofpoints * 2 * sizeof(REAL));
	if ( in.pointlist   == NULL)
		{
		printf(" in.pointlist  = NULL  \n" );
		exit(0);
		}
	in.numberofsegments = panneau[pa].nb_noeud_contour;
  	in.segmentlist = (int *) malloc( in.numberofsegments * 2 * sizeof(int));
	if ( in.segmentlist   == NULL)
		{
		printf(" in.segmentlist  = NULL  \n" );
		exit(0);
		}
  	in.segmentmarkerlist = (int *) malloc( in.numberofsegments * sizeof(int));
	if ( in.segmentmarkerlist   == NULL)
		{
		printf(" in.segmenmarkertlist  = NULL  \n" );
		exit(0);
		}
	for (no=1;no<=panneau[pa].nb_noeud_contour;no++)
		{ 
		deb = panneau[pa].noeud_contour[no];
		in.pointlist[2*no-2] = noeud[deb].u;
		in.pointlist[2*no-1] = noeud[deb].v;
		in.segmentlist[2*no-2] = no;
		if ( no == panneau[pa].nb_noeud_contour) in.segmentlist[2*no-1] = 1;
		if ( no != panneau[pa].nb_noeud_contour) in.segmentlist[2*no-1] = no+1;
		in.segmentmarkerlist[no-1] = 0;
		/*printf("no %d deb  %8d   ",no,deb);/**/
		/*printf("in.pointlist[2*%d-2]  %lf  in.pointlist[2*%d-1]  %lf  \n",no,in.pointlist[2*no-2],no,in.pointlist[2*no-1]  );/**/
		}
  	in.pointattributelist 	= (REAL *) NULL;
	in.pointmarkerlist 	= (int 	*) NULL;
	in.numberofholes = 0;
  	in.numberofregions = 0;
  	in.regionlist 		= (REAL *) NULL;
  	in.regionlist = (REAL *) NULL;
	
	out.pointlist 		= (REAL 	*) NULL;
	out.pointmarkerlist 	= (int 		*) NULL;
	out.trianglelist 	= (int 		*) NULL;
	out.numberofsegments = panneau[pa].nb_noeud_contour;
  	out.segmentlist = (int *) malloc(out.numberofsegments * 2 * sizeof(int));
	if ( out.segmentlist   == NULL)
		{
		printf(" out.segmentlist  = NULL  \n" );
		exit(0);
		}
	out.segmentmarkerlist 	= (int 		*) NULL;
	for (no=1;no<=panneau[pa].nb_noeud_contour;no++)
		{ 
		if ( no != 1) out.segmentlist[2*no-2] = no-1;
		if ( no == 1) out.segmentlist[2*no-2] = panneau[pa].nb_noeud_contour;
		out.segmentlist[2*no-1] = no;
		}

		
		
	triangulate("pQ",&in,&out,&vorout);
	/*Q pour quiet : sans commentaire*/
	
	
	panneau[pa].nb_triangle_contour = out.numberoftriangles;
	if (panneau[pa].nb_triangle_contour >= NBMAXNOEUDCONTOUR)
		{
		printf(" NBMAXNOEUDCONTOUR trop petit %4d < %4d \n",NBMAXNOEUDCONTOUR,panneau[pa].nb_triangle_contour );
		exit(0);
		}
	for (deb=1;deb<=out.numberoftriangles;deb++)
		{ 
		for (no=1;no<=out.numberofcorners;no++)
			{ 
			panneau[pa].triangle_contour[deb][no] = out.trianglelist[out.numberofcorners*deb-out.numberofcorners+no-1];
			/*numero du sommet no dans la numerotation locale*/
			}
		}
	
	if ( in.pointlist 		!= NULL) 	free(in.pointlist);
  	if ( in.pointattributelist 	!= NULL) 	free(in.pointattributelist);
  	if ( in.pointmarkerlist 	!= NULL) 	free(in.pointmarkerlist);
  	if ( in.trianglelist 		!= NULL) 	free(in.trianglelist);
  	if ( in.triangleattributelist 	!= NULL) 	free(in.triangleattributelist);
  	if ( in.neighborlist 		!= NULL) 	free(in.neighborlist);
  	if ( in.segmentlist 		!= NULL) 	free(in.segmentlist);
  	if ( in.segmentmarkerlist 	!= NULL) 	free(in.segmentmarkerlist);
  	if ( in.holelist 		!= NULL) 	free(in.holelist);
  	if ( in.regionlist 		!= NULL) 	free(in.regionlist);
  	if ( in.edgelist 		!= NULL) 	free(in.edgelist);
  	if ( in.edgemarkerlist 		!= NULL) 	free(in.edgemarkerlist);
  	if ( in.normlist 		!= NULL) 	free(in.normlist);
	if ( out.pointlist 		!= NULL) 	free(out.pointlist);
  	if ( out.pointattributelist 	!= NULL) 	free(out.pointattributelist);
  	if ( out.pointmarkerlist 	!= NULL) 	free(out.pointmarkerlist);
  	if ( out.trianglelist 		!= NULL) 	free(out.trianglelist);
  	if ( out.triangleattributelist 	!= NULL) 	free(out.triangleattributelist);
  	if ( out.neighborlist 		!= NULL) 	free(out.neighborlist);
  	if ( out.segmentlist 		!= NULL) 	free(out.segmentlist);
  	if ( out.segmentmarkerlist 	!= NULL) 	free(out.segmentmarkerlist);
  	if ( out.holelist 		!= NULL) 	free(out.holelist);
  	if ( out.regionlist 		!= NULL) 	free(out.regionlist);
  	if ( out.edgelist 		!= NULL) 	free(out.edgelist);
  	if ( out.edgemarkerlist 	!= NULL) 	free(out.edgemarkerlist);
  	if ( out.normlist 		!= NULL) 	free(out.normlist);
	if ( vorout.pointlist 			!= NULL) 	free(vorout.pointlist);
  	if ( vorout.pointattributelist 		!= NULL) 	free(vorout.pointattributelist);
  	if ( vorout.pointmarkerlist 		!= NULL) 	free(vorout.pointmarkerlist);
  	if ( vorout.trianglelist 		!= NULL) 	free(vorout.trianglelist);
  	if ( vorout.triangleattributelist 	!= NULL) 	free(vorout.triangleattributelist);
  	if ( vorout.neighborlist 		!= NULL) 	free(vorout.neighborlist);
  	if ( vorout.segmentlist 		!= NULL) 	free(vorout.segmentlist);
  	if ( vorout.segmentmarkerlist 		!= NULL) 	free(vorout.segmentmarkerlist);
  	if ( vorout.holelist 			!= NULL) 	free(vorout.holelist);
  	if ( vorout.regionlist 			!= NULL) 	free(vorout.regionlist);
  	if ( vorout.edgelist 			!= NULL) 	free(vorout.edgelist);
  	if ( vorout.edgemarkerlist 		!= NULL) 	free(vorout.edgemarkerlist);
  	if ( vorout.normlist 			!= NULL) 	free(vorout.normlist);
	panneau[pa].flag_filet_contour = 1;
	}
	
void triangul_hexa_contour(int pa)
	{
	/*defini les triangles poses sur le contour*/
	int deb,no;
	/*printf("  pan_hexa[pa].nb_noeud_contour : %8d  \n", pan_hexa[pa].nb_noeud_contour );*/
	in.numberofpoints = pan_hexa[pa].nb_noeud_contour;
	in.numberofpointattributes = 0;
  	in.pointlist = (REAL *) malloc( in.numberofpoints * 2 * sizeof(REAL));
	if ( in.pointlist   == NULL)
		{
		printf(" in.pointlist  = NULL  \n" );
		exit(0);
		}
	in.numberofsegments = pan_hexa[pa].nb_noeud_contour;
  	in.segmentlist = (int *) malloc( in.numberofsegments * 2 * sizeof(int));
	if ( in.segmentlist   == NULL)
		{
		printf(" in.segmentlist  = NULL  \n" );
		exit(0);
		}
  	in.segmentmarkerlist = (int *) malloc( in.numberofsegments * sizeof(int));
	if ( in.segmentmarkerlist   == NULL)
		{
		printf(" in.segmenmarkertlist  = NULL  \n" );
		exit(0);
		}
	for (no=1;no<=pan_hexa[pa].nb_noeud_contour;no++)
		{ 
		deb = pan_hexa[pa].noeud_contour[no];
		in.pointlist[2*no-2] = noeud[deb].u;
		in.pointlist[2*no-1] = noeud[deb].v;
		in.segmentlist[2*no-2] = no;
		if ( no == pan_hexa[pa].nb_noeud_contour) in.segmentlist[2*no-1] = 1;
		if ( no != pan_hexa[pa].nb_noeud_contour) in.segmentlist[2*no-1] = no+1;
		in.segmentmarkerlist[no-1] = 0;
		}
  	in.pointattributelist 	= (REAL *) NULL;
	in.pointmarkerlist 	= (int 	*) NULL;
	in.numberofholes = 0;
  	in.numberofregions = 0;
  	in.regionlist 		= (REAL *) NULL;
  	in.regionlist = (REAL *) NULL;
	
	out.pointlist 		= (REAL 	*) NULL;
	out.pointmarkerlist 	= (int 		*) NULL;
	out.trianglelist 	= (int 		*) NULL;
	out.numberofsegments = pan_hexa[pa].nb_noeud_contour;
  	out.segmentlist = (int *) malloc(out.numberofsegments * 2 * sizeof(int));
	if ( out.segmentlist   == NULL)
		{
		printf(" out.segmentlist  = NULL  \n" );
		exit(0);
		}
	out.segmentmarkerlist 	= (int 		*) NULL;
	for (no=1;no<=pan_hexa[pa].nb_noeud_contour;no++)
		{ 
		if ( no != 1) out.segmentlist[2*no-2] = no-1;
		if ( no == 1) out.segmentlist[2*no-2] = pan_hexa[pa].nb_noeud_contour;
		out.segmentlist[2*no-1] = no;
		}
		
		
	triangulate("pQ",&in,&out,&vorout);
	/*Q pour quiet : sans commentaire*/
	
	
	pan_hexa[pa].nb_tri_hexa_contour = out.numberoftriangles;
	if (pan_hexa[pa].nb_tri_hexa_contour >= NBMAXNOEUDCONTOUR)
		{
		printf(" NBMAXNOEUDCONTOUR trop petit %4d < %4d \n",NBMAXNOEUDCONTOUR,pan_hexa[pa].nb_tri_hexa_contour );
		exit(0);
		}
	for (deb=1;deb<=out.numberoftriangles;deb++)
		{ 
		for (no=1;no<=out.numberofcorners;no++)
			{ 
			pan_hexa[pa].tri_hexa_contour[deb][no] = out.trianglelist[out.numberofcorners*deb-out.numberofcorners+no-1];
			/*numero du sommet no dans la numerotation locale*/
			}
		}
	
	if ( in.pointlist 		!= NULL) 	free(in.pointlist);
  	if ( in.pointattributelist 	!= NULL) 	free(in.pointattributelist);
  	if ( in.pointmarkerlist 	!= NULL) 	free(in.pointmarkerlist);
  	if ( in.trianglelist 		!= NULL) 	free(in.trianglelist);
  	if ( in.triangleattributelist 	!= NULL) 	free(in.triangleattributelist);
  	if ( in.neighborlist 		!= NULL) 	free(in.neighborlist);
  	if ( in.segmentlist 		!= NULL) 	free(in.segmentlist);
  	if ( in.segmentmarkerlist 	!= NULL) 	free(in.segmentmarkerlist);
  	if ( in.holelist 		!= NULL) 	free(in.holelist);
  	if ( in.regionlist 		!= NULL) 	free(in.regionlist);
  	if ( in.edgelist 		!= NULL) 	free(in.edgelist);
  	if ( in.edgemarkerlist 		!= NULL) 	free(in.edgemarkerlist);
  	if ( in.normlist 		!= NULL) 	free(in.normlist);
	if ( out.pointlist 		!= NULL) 	free(out.pointlist);
  	if ( out.pointattributelist 	!= NULL) 	free(out.pointattributelist);
  	if ( out.pointmarkerlist 	!= NULL) 	free(out.pointmarkerlist);
  	if ( out.trianglelist 		!= NULL) 	free(out.trianglelist);
  	if ( out.triangleattributelist 	!= NULL) 	free(out.triangleattributelist);
  	if ( out.neighborlist 		!= NULL) 	free(out.neighborlist);
  	if ( out.segmentlist 		!= NULL) 	free(out.segmentlist);
  	if ( out.segmentmarkerlist 	!= NULL) 	free(out.segmentmarkerlist);
  	if ( out.holelist 		!= NULL) 	free(out.holelist);
  	if ( out.regionlist 		!= NULL) 	free(out.regionlist);
  	if ( out.edgelist 		!= NULL) 	free(out.edgelist);
  	if ( out.edgemarkerlist 	!= NULL) 	free(out.edgemarkerlist);
  	if ( out.normlist 		!= NULL) 	free(out.normlist);
	if ( vorout.pointlist 			!= NULL) 	free(vorout.pointlist);
  	if ( vorout.pointattributelist 		!= NULL) 	free(vorout.pointattributelist);
  	if ( vorout.pointmarkerlist 		!= NULL) 	free(vorout.pointmarkerlist);
  	if ( vorout.trianglelist 		!= NULL) 	free(vorout.trianglelist);
  	if ( vorout.triangleattributelist 	!= NULL) 	free(vorout.triangleattributelist);
  	if ( vorout.neighborlist 		!= NULL) 	free(vorout.neighborlist);
  	if ( vorout.segmentlist 		!= NULL) 	free(vorout.segmentlist);
  	if ( vorout.segmentmarkerlist 		!= NULL) 	free(vorout.segmentmarkerlist);
  	if ( vorout.holelist 			!= NULL) 	free(vorout.holelist);
  	if ( vorout.regionlist 			!= NULL) 	free(vorout.regionlist);
  	if ( vorout.edgelist 			!= NULL) 	free(vorout.edgelist);
  	if ( vorout.edgemarkerlist 		!= NULL) 	free(vorout.edgemarkerlist);
  	if ( vorout.normlist 			!= NULL) 	free(vorout.normlist);
	pan_hexa[pa].flag_filet_contour = 1;
	}
	
void fils_contour_calculer()
	{
	int s,sommet1,sommet2,sommet3,ind,pa;
	float U1,U2,U3,V1,V2,V3,n1,n2,n3,m1,m2,m3,nh,Uh,Ui;
	float ve1[4],ve2[4],ve3[4],u12[4],u23[4],u31[4],v12[4],v23[4],v31[4],vh[4],uh1[4],uh2[4];
	
   	if (periode_fils <= 0) periode_fils = 1;
	
	for (pa=1;pa<=Structure.NbTypesurf;pa++)
		{
		if((panneau[pa].flag_filet_contour == 1) && (panneau[pa].flag_dessin != 0))
			{
			/*printf("fils_contour_calculer pa  : %8d \n",pa);*/
			for (s=1;s<=panneau[pa].nb_triangle_contour;s++)
				{
				sommet1 = panneau[pa].noeud_contour[panneau[pa].triangle_contour[s][1]];
				sommet2 = panneau[pa].noeud_contour[panneau[pa].triangle_contour[s][2]];
				sommet3 = panneau[pa].noeud_contour[panneau[pa].triangle_contour[s][3]];
	
				/*printf(" triangle  : %8d \n",s);
				printf(" sommets  : %8d %8d %8d \n",sommet1,sommet2,sommet3);*/
		
				U1 = noeud[sommet1].V + noeud[sommet1].U; V1 = noeud[sommet1].V - noeud[sommet1].U;
				U2 = noeud[sommet2].V + noeud[sommet2].U; V2 = noeud[sommet2].V - noeud[sommet2].U;
				U3 = noeud[sommet3].V + noeud[sommet3].U; V3 = noeud[sommet3].V - noeud[sommet3].U;

				U1 = (float) U1 / periode_fils;		V1 = (float) V1 / periode_fils;
				U2 = (float) U2 / periode_fils;		V2 = (float) V2 / periode_fils;
				U3 = (float) U3 / periode_fils;		V3 = (float) V3 / periode_fils;

				ve1[1] = noeud[sommet1].x; ve1[2] = noeud[sommet1].y; ve1[3] = noeud[sommet1].z;
				ve2[1] = noeud[sommet2].x; ve2[2] = noeud[sommet2].y; ve2[3] = noeud[sommet2].z;
				ve3[1] = noeud[sommet3].x; ve3[2] = noeud[sommet3].y; ve3[3] = noeud[sommet3].z;

				n1 = fabs(U3-U2); /*U twine nb cutting edge 1*/
				n2 = fabs(U1-U3);
				n3 = fabs(U2-U1);

				m1 = fabs(V3-V2);
				m2 = fabs(V1-V3);
				m3 = fabs(V2-V1);

				if (n3 != 0) 
					{
					u12[1] = (ve2[1]-ve1[1]) / n3; 
					u12[2] = (ve2[2]-ve1[2]) / n3; 
					u12[3] = (ve2[3]-ve1[3]) / n3; 
					}
				else 
					{
					u12[1] = 0.0;
					u12[2] = 0.0;
					u12[3] = 0.0;
					}
				if (m3 != 0) 
					{
					v12[1] = (ve2[1]-ve1[1]) / m3; 
					v12[2] = (ve2[2]-ve1[2]) / m3; 
					v12[3] = (ve2[3]-ve1[3]) / m3; 
					}
				else 
					{
					v12[1] = 0.0;
					v12[2] = 0.0;
					v12[3] = 0.0;
					}
				
				if (n2 != 0) 
					{
					u31[1] = (ve1[1]-ve3[1]) / n2; 
					u31[2] = (ve1[2]-ve3[2]) / n2; 
					u31[3] = (ve1[3]-ve3[3]) / n2; 
					}
				else 
					{
					u31[1] = 0.0;
					u31[2] = 0.0;
					u31[3] = 0.0;
					}
				if (m2 != 0) 
					{
					v31[1] = (ve1[1]-ve3[1]) / m2; 
					v31[2] = (ve1[2]-ve3[2]) / m2; 
					v31[3] = (ve1[3]-ve3[3]) / m2; 
					}
				else 
					{
					v31[1] = 0.0;
					v31[2] = 0.0;
					v31[3] = 0.0;
					}
			
				if (n1 != 0) 
					{
					u23[1] = (ve3[1]-ve2[1]) / n1; 
					u23[2] = (ve3[2]-ve2[2]) / n1; 
					u23[3] = (ve3[3]-ve2[3]) / n1; 
					}
				else 
					{
					u23[1] = 0.0;
					u23[2] = 0.0;
					u23[3] = 0.0;
					}
				if (m1 != 0) 
					{
					v23[1] = (ve3[1]-ve2[1]) / m1; 
					v23[2] = (ve3[2]-ve2[2]) / m1; 
					v23[3] = (ve3[3]-ve2[3]) / m1; 
					}
				else 
					{
					v23[1] = 0.0;
					v23[2] = 0.0;
					v23[3] = 0.0;
					}
		
				if ((n1>=n2) && (n1>=n3)) ind = 1;
				if ((n2>=n3) && (n2>=n1)) ind = 2;
				if ((n3>=n1) && (n3>=n2)) ind = 3;
				
				if (ind == 1)
					{
		  			vh [1] =  ve2[1]; vh [2] =  ve2[2]; vh [3] =  ve2[3]; 
  					uh1[1] =  u23[1]; uh1[2] =  u23[2]; uh1[3] =  u23[3]; 
  					uh2[1] = -u12[1]; uh2[2] = -u12[2]; uh2[3] = -u12[3];
  					nh = n3;  
		  			Uh = U2; Ui = U3;  
  					hachu3(vh,uh1,uh2,nh,Uh,Ui);
  					vh [1] =  ve3[1]; vh [2] =  ve3[2]; vh [3] =  ve3[3]; 
  					uh1[1] = -u23[1]; uh1[2] = -u23[2]; uh1[3] = -u23[3]; 
	  				uh2[1] =  u31[1]; uh2[2] =  u31[2]; uh2[3] =  u31[3];
	  				nh = n2;  
  					Uh = U3; Ui = U2;  
  					hachu3(vh,uh1,uh2,nh,Uh,Ui);
	  				}
				if (ind == 2)
					{
  					vh [1] =  ve1[1]; vh [2] =  ve1[2]; vh [3] =  ve1[3]; 
	  				uh1[1] = -u31[1]; uh1[2] = -u31[2]; uh1[3] = -u31[3]; 
  					uh2[1] =  u12[1]; uh2[2] =  u12[2]; uh2[3] =  u12[3];
	  				nh = n3;  
  					Uh = U1; Ui = U3;  
	  				hachu3(vh,uh1,uh2,nh,Uh,Ui);
  					vh [1] =  ve3[1]; vh [2] =  ve3[2]; vh [3] =  ve3[3]; 
	  				uh1[1] =  u31[1]; uh1[2] =  u31[2]; uh1[3] =  u31[3]; 
  					uh2[1] = -u23[1]; uh2[2] = -u23[2]; uh2[3] = -u23[3];
	  				nh = n1;  
  					Uh = U3; Ui = U1;  
  					hachu3(vh,uh1,uh2,nh,Uh,Ui);
	  				}
				if (ind == 3)
					{
  					vh [1] =  ve1[1]; vh [2] =  ve1[2]; vh [3] =  ve1[3]; 
  					uh1[1] = -u31[1]; uh1[2] = -u31[2]; uh1[3] = -u31[3]; 
		  			uh2[1] =  u12[1]; uh2[2] =  u12[2]; uh2[3] =  u12[3];
  					nh = n2;  
  					Uh = U1; Ui = U2;  
  					hachu3(vh,uh1,uh2,nh,Uh,Ui);
	  				vh [1] =  ve2[1]; vh [2] =  ve2[2]; vh [3] =  ve2[3]; 
	  				uh1[1] = -u12[1]; uh1[2] = -u12[2]; uh1[3] = -u12[3]; 
  					uh2[1] =  u23[1]; uh2[2] =  u23[2]; uh2[3] =  u23[3];
  					nh = n1;  
	  				Uh = U2; Ui = U1;  
  					hachu3(vh,uh1,uh2,nh,Uh,Ui);
	  				}

				if ((m1>=m2) && (m1>=m3)) ind = 1;
				if ((m2>=m3) && (m2>=m1)) ind = 2;
				if ((m3>=m1) && (m3>=m2)) ind = 3;
				
				if (ind == 1)
					{
		  			vh [1] =  ve2[1]; vh [2] =  ve2[2]; vh [3] =  ve2[3]; 
  					uh1[1] =  v23[1]; uh1[2] =  v23[2]; uh1[3] =  v23[3]; 
  					uh2[1] = -v12[1]; uh2[2] = -v12[2]; uh2[3] = -v12[3];
  					nh = m3;  
	  				Uh = V2; Ui = V3;  
	  				hachu3(vh,uh1,uh2,nh,Uh,Ui);
  					vh [1] =  ve3[1]; vh [2] =  ve3[2]; vh [3] =  ve3[3]; 
  					uh1[1] = -v23[1]; uh1[2] = -v23[2]; uh1[3] = -v23[3]; 
	  				uh2[1] =  v31[1]; uh2[2] =  v31[2]; uh2[3] =  v31[3];
  					nh = m2;  
	  				Uh = V3; Ui = V2;  
  					hachu3(vh,uh1,uh2,nh,Uh,Ui);
	  				}
				if (ind == 2)
					{
  					vh [1] =  ve1[1]; vh [2] =  ve1[2]; vh [3] =  ve1[3]; 
	  				uh1[1] = -v31[1]; uh1[2] = -v31[2]; uh1[3] = -v31[3]; 
  					uh2[1] =  v12[1]; uh2[2] =  v12[2]; uh2[3] =  v12[3];
  					nh = m3;  
	  				Uh = V1; Ui = V3;  
		  			hachu3(vh,uh1,uh2,nh,Uh,Ui);
  					vh [1] =  ve3[1]; vh [2] =  ve3[2]; vh [3] =  ve3[3]; 
  					uh1[1] =  v31[1]; uh1[2] =  v31[2]; uh1[3] =  v31[3]; 
  					uh2[1] = -v23[1]; uh2[2] = -v23[2]; uh2[3] = -v23[3];
		  			nh = m1;  
  					Uh = V3; Ui = V1;  
  					hachu3(vh,uh1,uh2,nh,Uh,Ui);
  					}
				if (ind == 3)
					{
  					vh [1] =  ve1[1]; vh [2] =  ve1[2]; vh [3] =  ve1[3]; 
  					uh1[1] = -v31[1]; uh1[2] = -v31[2]; uh1[3] = -v31[3]; 
  					uh2[1] =  v12[1]; uh2[2] =  v12[2]; uh2[3] =  v12[3];
		  			nh = m2;  
  					Uh = V1; Ui = V2;  
  					hachu3(vh,uh1,uh2,nh,Uh,Ui);
	  				vh [1] =  ve2[1]; vh [2] =  ve2[2]; vh [3] =  ve2[3]; 
	  				uh1[1] = -v12[1]; uh1[2] = -v12[2]; uh1[3] = -v12[3]; 
  					uh2[1] =  v23[1]; uh2[2] =  v23[2]; uh2[3] =  v23[3];
  					nh = m1;  
	  				Uh = V2; Ui = V1;  
	  				hachu3(vh,uh1,uh2,nh,Uh,Ui);
  					}
				}
			}
		}
	}
	

void axe_T90_calculer()
	{
	int s,sommet1,sommet2,sommet3,ind,pa;
	float U1,U2,U3,V1,V2,V3,n1,n2,n3,m1,m2,m3,nh,Uh,Ui;
	float ve1[4],ve2[4],ve3[4],u12[4],u23[4],u31[4],v12[4],v23[4],v31[4],vh[4],uh1[4],uh2[4];
	
   	if (periode_fils <= 0) periode_fils = 1;
	
	for (pa=1;pa<=Structure.NbTypesurf;pa++)
		{
		if(panneau[pa].flag_filet_contour == 1)
			{
			for (s=1;s<=panneau[pa].nb_triangle_contour;s++)
				{
				sommet1 = panneau[pa].noeud_contour[panneau[pa].triangle_contour[s][1]];
				sommet2 = panneau[pa].noeud_contour[panneau[pa].triangle_contour[s][2]];
				sommet3 = panneau[pa].noeud_contour[panneau[pa].triangle_contour[s][3]];
	
				/*printf(" triangle  : %8d \n",s);
				printf(" sommets  : %8d %8d %8d \n",sommet1,sommet2,sommet3);*/
				
				/*
				U1 = noeud[sommet1].V + noeud[sommet1].U; 	V1 = noeud[sommet1].V - noeud[sommet1].U;
				U2 = noeud[sommet2].V + noeud[sommet2].U; 	V2 = noeud[sommet2].V - noeud[sommet2].U;
				U3 = noeud[sommet3].V + noeud[sommet3].U; 	V3 = noeud[sommet3].V - noeud[sommet3].U;
				*/

				U1 = noeud[sommet1].U; 				V1 = noeud[sommet1].V;
				U2 = noeud[sommet2].U; 				V2 = noeud[sommet2].V;
				U3 = noeud[sommet3].U; 				V3 = noeud[sommet3].V;

				U1 = (float) U1 / periode_fils;		V1 = (float) V1 / periode_fils;
				U2 = (float) U2 / periode_fils;		V2 = (float) V2 / periode_fils;
				U3 = (float) U3 / periode_fils;		V3 = (float) V3 / periode_fils;

				ve1[1] = noeud[sommet1].x; ve1[2] = noeud[sommet1].y; ve1[3] = noeud[sommet1].z;
				ve2[1] = noeud[sommet2].x; ve2[2] = noeud[sommet2].y; ve2[3] = noeud[sommet2].z;
				ve3[1] = noeud[sommet3].x; ve3[2] = noeud[sommet3].y; ve3[3] = noeud[sommet3].z;

				n1 = fabs(U3-U2); /*U twine nb cutting edge 1*/
				n2 = fabs(U1-U3);
				n3 = fabs(U2-U1);

				m1 = fabs(V3-V2);
				m2 = fabs(V1-V3);
				m3 = fabs(V2-V1);

				if (n3 != 0) 
					{
					u12[1] = (ve2[1]-ve1[1]) / n3; 
					u12[2] = (ve2[2]-ve1[2]) / n3; 
					u12[3] = (ve2[3]-ve1[3]) / n3; 
					}
				else 
					{
					u12[1] = 0.0;
					u12[2] = 0.0;
					u12[3] = 0.0;
					}
				if (m3 != 0) 
					{
					v12[1] = (ve2[1]-ve1[1]) / m3; 
					v12[2] = (ve2[2]-ve1[2]) / m3; 
					v12[3] = (ve2[3]-ve1[3]) / m3; 
					}
				else 
					{
					v12[1] = 0.0;
					v12[2] = 0.0;
					v12[3] = 0.0;
					}
				
				if (n2 != 0) 
					{
					u31[1] = (ve1[1]-ve3[1]) / n2; 
					u31[2] = (ve1[2]-ve3[2]) / n2; 
					u31[3] = (ve1[3]-ve3[3]) / n2; 
					}
				else 
					{
					u31[1] = 0.0;
					u31[2] = 0.0;
					u31[3] = 0.0;
					}
				if (m2 != 0) 
					{
					v31[1] = (ve1[1]-ve3[1]) / m2; 
					v31[2] = (ve1[2]-ve3[2]) / m2; 
					v31[3] = (ve1[3]-ve3[3]) / m2; 
					}
				else 
					{
					v31[1] = 0.0;
					v31[2] = 0.0;
					v31[3] = 0.0;
					}
			
				if (n1 != 0) 
					{
					u23[1] = (ve3[1]-ve2[1]) / n1; 
					u23[2] = (ve3[2]-ve2[2]) / n1; 
					u23[3] = (ve3[3]-ve2[3]) / n1; 
					}
				else 
					{
					u23[1] = 0.0;
					u23[2] = 0.0;
					u23[3] = 0.0;
					}
				if (m1 != 0) 
					{
					v23[1] = (ve3[1]-ve2[1]) / m1; 
					v23[2] = (ve3[2]-ve2[2]) / m1; 
					v23[3] = (ve3[3]-ve2[3]) / m1; 
					}
				else 
					{
					v23[1] = 0.0;
					v23[2] = 0.0;
					v23[3] = 0.0;
					}
		
				if ((n1>=n2) && (n1>=n3)) ind = 1;
				if ((n2>=n3) && (n2>=n1)) ind = 2;
				if ((n3>=n1) && (n3>=n2)) ind = 3;
				
				if (ind == 1)
					{
		  			vh [1] =  ve2[1]; vh [2] =  ve2[2]; vh [3] =  ve2[3]; 
  					uh1[1] =  u23[1]; uh1[2] =  u23[2]; uh1[3] =  u23[3]; 
  					uh2[1] = -u12[1]; uh2[2] = -u12[2]; uh2[3] = -u12[3];
  					nh = n3;  
		  			Uh = U2; Ui = U3;  
  					hachu4(vh,uh1,uh2,nh,Uh,Ui);
  					vh [1] =  ve3[1]; vh [2] =  ve3[2]; vh [3] =  ve3[3]; 
  					uh1[1] = -u23[1]; uh1[2] = -u23[2]; uh1[3] = -u23[3]; 
	  				uh2[1] =  u31[1]; uh2[2] =  u31[2]; uh2[3] =  u31[3];
	  				nh = n2;  
  					Uh = U3; Ui = U2;  
  					hachu4(vh,uh1,uh2,nh,Uh,Ui);
	  				}
				if (ind == 2)
					{
  					vh [1] =  ve1[1]; vh [2] =  ve1[2]; vh [3] =  ve1[3]; 
	  				uh1[1] = -u31[1]; uh1[2] = -u31[2]; uh1[3] = -u31[3]; 
  					uh2[1] =  u12[1]; uh2[2] =  u12[2]; uh2[3] =  u12[3];
	  				nh = n3;  
  					Uh = U1; Ui = U3;  
	  				hachu4(vh,uh1,uh2,nh,Uh,Ui);
  					vh [1] =  ve3[1]; vh [2] =  ve3[2]; vh [3] =  ve3[3]; 
	  				uh1[1] =  u31[1]; uh1[2] =  u31[2]; uh1[3] =  u31[3]; 
  					uh2[1] = -u23[1]; uh2[2] = -u23[2]; uh2[3] = -u23[3];
	  				nh = n1;  
  					Uh = U3; Ui = U1;  
  					hachu4(vh,uh1,uh2,nh,Uh,Ui);
	  				}
				if (ind == 3)
					{
  					vh [1] =  ve1[1]; vh [2] =  ve1[2]; vh [3] =  ve1[3]; 
  					uh1[1] = -u31[1]; uh1[2] = -u31[2]; uh1[3] = -u31[3]; 
		  			uh2[1] =  u12[1]; uh2[2] =  u12[2]; uh2[3] =  u12[3];
  					nh = n2;  
  					Uh = U1; Ui = U2;  
  					hachu4(vh,uh1,uh2,nh,Uh,Ui);
	  				vh [1] =  ve2[1]; vh [2] =  ve2[2]; vh [3] =  ve2[3]; 
	  				uh1[1] = -u12[1]; uh1[2] = -u12[2]; uh1[3] = -u12[3]; 
  					uh2[1] =  u23[1]; uh2[2] =  u23[2]; uh2[3] =  u23[3];
  					nh = n1;  
	  				Uh = U2; Ui = U1;  
  					hachu4(vh,uh1,uh2,nh,Uh,Ui);
	  				}

				/*
				if ((m1>=m2) && (m1>=m3)) ind = 1;
				if ((m2>=m3) && (m2>=m1)) ind = 2;
				if ((m3>=m1) && (m3>=m2)) ind = 3;
				
				if (ind == 1)
					{
		  			vh [1] =  ve2[1]; vh [2] =  ve2[2]; vh [3] =  ve2[3]; 
  					uh1[1] =  v23[1]; uh1[2] =  v23[2]; uh1[3] =  v23[3]; 
  					uh2[1] = -v12[1]; uh2[2] = -v12[2]; uh2[3] = -v12[3];
  					nh = m3;  
	  				Uh = V2; Ui = V3;  
	  				hachu4(vh,uh1,uh2,nh,Uh,Ui);
  					vh [1] =  ve3[1]; vh [2] =  ve3[2]; vh [3] =  ve3[3]; 
  					uh1[1] = -v23[1]; uh1[2] = -v23[2]; uh1[3] = -v23[3]; 
	  				uh2[1] =  v31[1]; uh2[2] =  v31[2]; uh2[3] =  v31[3];
  					nh = m2;  
	  				Uh = V3; Ui = V2;  
  					hachu4(vh,uh1,uh2,nh,Uh,Ui);
	  				}
				if (ind == 2)
					{
  					vh [1] =  ve1[1]; vh [2] =  ve1[2]; vh [3] =  ve1[3]; 
	  				uh1[1] = -v31[1]; uh1[2] = -v31[2]; uh1[3] = -v31[3]; 
  					uh2[1] =  v12[1]; uh2[2] =  v12[2]; uh2[3] =  v12[3];
  					nh = m3;  
	  				Uh = V1; Ui = V3;  
		  			hachu4(vh,uh1,uh2,nh,Uh,Ui);
  					vh [1] =  ve3[1]; vh [2] =  ve3[2]; vh [3] =  ve3[3]; 
  					uh1[1] =  v31[1]; uh1[2] =  v31[2]; uh1[3] =  v31[3]; 
  					uh2[1] = -v23[1]; uh2[2] = -v23[2]; uh2[3] = -v23[3];
		  			nh = m1;  
  					Uh = V3; Ui = V1;  
  					hachu4(vh,uh1,uh2,nh,Uh,Ui);
  					}
				if (ind == 3)
					{
  					vh [1] =  ve1[1]; vh [2] =  ve1[2]; vh [3] =  ve1[3]; 
  					uh1[1] = -v31[1]; uh1[2] = -v31[2]; uh1[3] = -v31[3]; 
  					uh2[1] =  v12[1]; uh2[2] =  v12[2]; uh2[3] =  v12[3];
		  			nh = m2;  
  					Uh = V1; Ui = V2;  
  					hachu4(vh,uh1,uh2,nh,Uh,Ui);
	  				vh [1] =  ve2[1]; vh [2] =  ve2[2]; vh [3] =  ve2[3]; 
	  				uh1[1] = -v12[1]; uh1[2] = -v12[2]; uh1[3] = -v12[3]; 
  					uh2[1] =  v23[1]; uh2[2] =  v23[2]; uh2[3] =  v23[3];
  					nh = m1;  
	  				Uh = V2; Ui = V1;  
	  				hachu4(vh,uh1,uh2,nh,Uh,Ui);
  					}
  				*/
				}
			}
		}
	}
	

void  hachu3(float vh[],float uh1[],float uh2[],float nh,float Uh,float Ui)
	{
	/*
	vh est le sommet a partir duquel on calcule les fils
	uh1 est le premier vecteur de separation des fils sur le premier cote
	uh2 est le second  vecteur de separation des fils sur le second  cote
	nh nb of twines cuuting the edge
	Uh Ui coordinates in meshes nb of the vertexes
	*/
	float debut;
	int ind,nb,col;
	if (Ui > Uh)
		{
		debut = (float) (ceil ((double) Uh) - Uh); 
		}
	else 
		{
		debut = (float) (Uh - floor ((double) Uh));
		}
	nb = (int) (floor(nh-debut+1));
	/*printf(" vh  : %8.2f %8.2f %8.2f\n",vh [1],vh [2],vh [3]);
	printf(" uh1 : %8.2f %8.2f %8.2f\n",uh1[1],uh1[2],uh1[3]);
	printf(" uh2 : %8.2f %8.2f %8.2f\n",uh2[1],uh2[2],uh2[3]);
	printf(" nh  : %8.2f debut  : %8.2f Uh  : %8.2f Ui  : %8.2f nb  : %d\n",nh,debut,Uh,Ui,nb);*/
	for (ind=1;ind<=nb;ind++)
		{
		Structure.nb_fils++;
		/**********************************************/
		h1x = (float *) realloc(h1x, (1+ Structure.nb_fils) * sizeof(float));
		if (h1x    == NULL)
			{
			printf("h1x  2 = NULL  \n" );
			exit(0);
			}
		/**********************************************/
		h1y = (float *) realloc(h1y, (1+ Structure.nb_fils) * sizeof(float));
		if (h1y    == NULL)
			{
			printf("h1y  2 = NULL  \n" );
			exit(0);
			}
		/**********************************************/
		h2x = (float *) realloc(h2x, (1+ Structure.nb_fils) * sizeof(float));
		if (h2x    == NULL)
			{
			printf("h2x  2 = NULL  \n" );
			exit(0);
			}
		/**********************************************/
		h2y = (float *) realloc(h2y, (1+ Structure.nb_fils) * sizeof(float));
		if (h2y    == NULL)
			{
			printf("h2y  2 = NULL  \n" );
			exit(0);
			}
		/**********************************************/
		h1x[Structure.nb_fils] = vh[1]+debut*uh1[1] + (ind-1) * uh1[1]; /*coordonnee selon x de l extremite 1 du fil*/
		h2x[Structure.nb_fils] = vh[1]+debut*uh2[1] + (ind-1) * uh2[1]; /*coordonnee selon x de l extremite 2 du fil*/
		h1y[Structure.nb_fils] = vh[2]+debut*uh1[2] + (ind-1) * uh1[2]; /*coordonnee selon x de l extremite 1 du fil*/
		h2y[Structure.nb_fils] = vh[2]+debut*uh2[2] + (ind-1) * uh2[2]; /*coordonnee selon x de l extremite 2 du fil*/
		/*printf(" h1  : %8.2f %8.2f  ",h1x[Structure.nb_fils],h1y[Structure.nb_fils]);
		printf(" h2  : %8.2f %8.2f\n",h2x[Structure.nb_fils],h2y[Structure.nb_fils]);*/
		}
	}
	
void  hachu4(float vh[],float uh1[],float uh2[],float nh,float Uh,float Ui)
	{
	/*
	vh est le sommet a partir duquel on calcule les fils
	uh1 est le premier vecteur de separation des fils sur le premier cote
	uh2 est le second  vecteur de separation des fils sur le second  cote
	nh nb of twines cuuting the edge
	Uh Ui coordinates in meshes nb of the vertexes
	*/
	float debut;
	int ind,nb,col;
	if (Ui > Uh)
		{
		debut = (float) (ceil ((double) Uh) - Uh); 
		}
	else 
		{
		debut = (float) (Uh - floor ((double) Uh));
		}
	nb = (int) (floor(nh-debut+1));
	/*printf(" vh  : %8.2f %8.2f %8.2f\n",vh [1],vh [2],vh [3]);
	printf(" uh1 : %8.2f %8.2f %8.2f\n",uh1[1],uh1[2],uh1[3]);
	printf(" uh2 : %8.2f %8.2f %8.2f\n",uh2[1],uh2[2],uh2[3]);
	printf(" nh  : %8.2f debut  : %8.2f Uh  : %8.2f Ui  : %8.2f nb  : %d\n",nh,debut,Uh,Ui,nb);*/
	for (ind=1;ind<=nb;ind++)
		{
		Structure.T90_nb_fils++;
		/**********************************************/
		g1x = (float *) realloc(g1x, (1+ Structure.T90_nb_fils) * sizeof(float));
		if (g1x    == NULL)
			{
			printf("g1x  2 = NULL  \n" );
			exit(0);
			}
		/**********************************************/
		g1y = (float *) realloc(g1y, (1+ Structure.T90_nb_fils) * sizeof(float));
		if (g1y    == NULL)
			{
			printf("g1y  2 = NULL  \n" );
			exit(0);
			}
		/**********************************************/
		g2x = (float *) realloc(g2x, (1+ Structure.T90_nb_fils) * sizeof(float));
		if (g2x    == NULL)
			{
			printf("g2x  2 = NULL  \n" );
			exit(0);
			}
		/**********************************************/
		g2y = (float *) realloc(g2y, (1+ Structure.T90_nb_fils) * sizeof(float));
		if (g2y    == NULL)
			{
			printf("g2y  2 = NULL  \n" );
			exit(0);
			}
		/**********************************************/
		g1x[Structure.T90_nb_fils] = vh[1]+debut*uh1[1] + (ind-1) * uh1[1]; /*coordonnee selon x de l extremite 1 du fil*/
		g2x[Structure.T90_nb_fils] = vh[1]+debut*uh2[1] + (ind-1) * uh2[1]; /*coordonnee selon x de l extremite 2 du fil*/
		g1y[Structure.T90_nb_fils] = vh[2]+debut*uh1[2] + (ind-1) * uh1[2]; /*coordonnee selon x de l extremite 1 du fil*/
		g2y[Structure.T90_nb_fils] = vh[2]+debut*uh2[2] + (ind-1) * uh2[2]; /*coordonnee selon x de l extremite 2 du fil*/
		/*printf(" h1  : %8.2f %8.2f  ",h1x[Structure.T90_nb_fils],h1y[Structure.T90_nb_fils]);
		printf(" h2  : %8.2f %8.2f\n",h2x[Structure.T90_nb_fils],g2y[Structure.T90_nb_fils]);*/
		}
	}
