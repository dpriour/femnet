#define PRINCIPAL 0
#include "phobos.h"

void meshing_netting_2_ropes3(int pa)
	{
	int el,co,zu,zv,no,period1,period2;
	int int_min_U,int_min_V,int_max_U,int_max_V;
	int trouve,tri1,tri2,extremity1_node,extremity2_node;
	double min_U,min_V,max_U,max_V,decal_u,decal_v,extremity1_u,extremity1_v,extremity2_u,extremity2_v;	
	double cut_alpha[100],cut_beta[100];	
	int cut_side[100],cut_code[100],cut_triangle[100],code,nb_cut;
	double side1_u,side1_v,side2_u,side2_v,dalpha,dbeta,ptu,ptv;
	int same_side,close_node1,close_node2,close_side1,close_side2,sommet1,sommet2,sommet3;
	double corner1_u,corner1_v,corner2_u,corner2_v;
	int corner1,corner2,ele,sens;


	/*
	CREE DES ELEMENTS BARRES LES POINTS A L INTERIEUR DU PANNEAU PA, EN SE BASANT SUR LES FILS
	*/
	//printf("netting2ropes panel %d\n",pa);
	//printf("type_maillage %d\n",panneau[pa].type_maillage);
	//printf("netting_2_ropes_period %d\n",panneau[pa].netting_2_ropes_period);
	//printf("netting_2_ropes_gap_U %6.2lf	",panneau[pa].netting_2_ropes_gap_U);
	//printf("netting_2_ropes_gap_V %6.2lf\n",panneau[pa].netting_2_ropes_gap_V);
	//printf("netting_2_ropes_accuracy %6.2lf\n",panneau[pa].netting_2_ropes_accuracy);
	//printf("netting_2_ropes_bar_nb %d\n",panneau[pa].netting_2_ropes_bar_nb);
	
	Structure.nb_node_panel2ropes = panneau[pa].nb_noeud_contour;
	node_panel2ropes.U 		= (double *) malloc((1 + Structure.nb_node_panel2ropes) * sizeof(double));
	node_panel2ropes.V 		= (double *) malloc((1 + Structure.nb_node_panel2ropes) * sizeof(double));
	node_panel2ropes.numero_total 	= (int *) malloc((1 + Structure.nb_node_panel2ropes) * sizeof(int));
	node_panel2ropes.side 		= (int *) malloc((1 + Structure.nb_node_panel2ropes) * sizeof(int));
	node_panel2ropes.cable 		= (int *) malloc((1 + Structure.nb_node_panel2ropes) * sizeof(int));
	node_panel2ropes.sens 		= (int *) malloc((1 + Structure.nb_node_panel2ropes) * sizeof(int));
	node_panel2ropes.prop_cable 	= (double *) malloc((1 + Structure.nb_node_panel2ropes) * sizeof(double));
	panneau[pa].side2cable 		= (int *) malloc((1 + panneau[pa].nb_noeud_contour) * sizeof(int));
	
	trouve = verification_ropes_around_panel2(pa);
	if (trouve != 0)
		{
		printf("When input netting2ropes is used, the panel must be surrounded by ropes. No cable allong side %4d\n",trouve);
		//printf("The side between corners %d and %d of panel %d must have a cable linked\n",deb_panel,fin_panel,pa);			
		exit(0);
		}	
		
	create_side2cable(pa);	
	//for (el=1;el<=Structure.NbTypeelem;el++)		printf("element %d sewn to %d\n",el,element[el].cable2side);
	//for (co=1;co<=panneau[pa].nb_noeud_contour;co++)	printf("side %d sewn to %d\n",co,panneau[pa].side2cable[co]);

	first_node_created(pa);
	//for (co=1;co<=Structure.nb_node_panel2ropes;co++)	printf("nb_node_panel2ropes.U[%d] %6.1lf V %6.1lf total %3d side %2d cable %2d sens %2d Prop %4.1lf\n",co,node_panel2ropes.U[co],node_panel2ropes.V[co],node_panel2ropes.numero_total[co],node_panel2ropes.side[co],node_panel2ropes.cable[co],node_panel2ropes.sens[co],node_panel2ropes.prop_cable[co]);

	min_U = noeud[panneau[pa].noeud_contour[1]].u;	min_V = noeud[panneau[pa].noeud_contour[1]].v;
	max_U = noeud[panneau[pa].noeud_contour[1]].u;	max_V = noeud[panneau[pa].noeud_contour[1]].v;
	for (co=1;co<=panneau[pa].nb_noeud_contour;co++)
		{
		if (noeud[panneau[pa].noeud_contour[co]].u > max_U) max_U = noeud[panneau[pa].noeud_contour[co]].u;
		if (noeud[panneau[pa].noeud_contour[co]].u < min_U) min_U = noeud[panneau[pa].noeud_contour[co]].u;
		if (noeud[panneau[pa].noeud_contour[co]].v > max_V) max_V = noeud[panneau[pa].noeud_contour[co]].v;
		if (noeud[panneau[pa].noeud_contour[co]].v < min_V) min_V = noeud[panneau[pa].noeud_contour[co]].v;
		}
	//printf("min_U %6.2lf max_U %6.2lf\n",min_U,max_U);
	//printf("min_V %6.2lf max_V %6.2lf\n",min_V,max_V);
	min_U = min_U - panneau[pa].netting_2_ropes_period;
	max_U = max_U + panneau[pa].netting_2_ropes_period;
	min_V = min_V - panneau[pa].netting_2_ropes_period;
	max_V = max_V + panneau[pa].netting_2_ropes_period;
	int_min_U = (int) min_U;	int_max_U = (int) max_U;
	int_min_V = (int) min_V;	int_max_V = (int) max_V;
	//printf("int_min_U %4d int_max_U %4d\n",int_min_U,int_max_U);			
	//printf("int_min_V %4d int_max_V %4d\n",int_min_V,int_max_V);
	period2 = (int) panneau[pa].netting_2_ropes_period / panneau[pa].netting_2_ropes_bar_nb;
	period1 = period2 * panneau[pa].netting_2_ropes_bar_nb;
	//printf("period1 %4d period2 %4d\n",period1,period2);			
	////////////////////beginning of the loop on u	/////////////////////////////////////////////////////////////////////
	for (zu=int_min_U;zu<=int_max_U;zu+= period1)
		{
		for (zv=int_min_V;zv<=int_max_V;zv+=period2)
			{
			/*AB twine, CD panel side, intersection of twine with panel side is M, such AM = alpha AB and CM = beta CD*/
			decal_u = panneau[pa].netting_2_ropes_gap_U * panneau[pa].netting_2_ropes_period;
			decal_v = panneau[pa].netting_2_ropes_gap_V * panneau[pa].netting_2_ropes_period;
			//printf("zu %4d zv %4d\n",zu,zv);	
			//printf("decal_u %6.2lf decal_v %6.2lf\n",decal_u,decal_v);
			extremity1_u = (double) zu+decal_u;	extremity1_v = (double) zv+decal_v;	
			extremity2_u = (double) zu+decal_u;	extremity2_v = (double) zv+decal_v+period2;
			//printf("ex12uv %5.0lf %5.0lf %5.0lf %5.0lf ",extremity1_u,extremity1_v,extremity2_u,extremity2_v);	
			same_side = side_neighbor(pa,extremity1_u,extremity1_v,extremity2_u,extremity2_v);	//if the node couple is on the same side, this side is same_side
			nb_cut = number_of_cuts(pa, extremity1_u, extremity1_v, extremity2_u, extremity2_v, cut_triangle, cut_side, cut_alpha, cut_beta, cut_code);	//nb of cut the segment between the node couple cuts the sides of the panel
			close_node1 = is_node_close_another_one2(pa, extremity1_u, extremity1_v);
			close_node2 = is_node_close_another_one2(pa, extremity2_u, extremity2_v);
			close_side1 = 0;
			close_side2 = 0;
			for (co=1;co<=panneau[pa].nb_noeud_contour;co++)
				{
				if (is_node_close_side2(pa, co, extremity1_u, extremity1_v) == 1) close_side1 = co;
				if (is_node_close_side2(pa, co, extremity2_u, extremity2_v) == 1) close_side2 = co;
				}
			tri1 = interieur_panneau_filaire2(extremity1_u, extremity1_v, pa);		
			tri2 = interieur_panneau_filaire2(extremity2_u, extremity2_v, pa);
			//printf("samside %2d nb_cut %2d ",same_side,nb_cut);	
			//printf("tri1 %2d clnod1 %3d clsid1 %2d ",tri1,close_node1,close_side1);	
			///printf("tri2 %2d clnod2 %3d clsid2 %2d ",tri2,close_node2,close_side2);	
			//if (nb_cut == 1) printf("cut_side %2d ",cut_side[nb_cut]);	
			//printf("\n");	
			//nb_cut = 0
			//CASE1
			if ((same_side == 0) && (nb_cut == 0) && (tri1 != 0) && (close_node1 == 0) && (close_side1 == 0) && (tri2 != 0) && (close_node2 == 0) && (close_side2 == 0))
				{
				//same_side= 0 nb_cut=0 case1 case1
				extremity1_node = case1(pa, tri1, extremity1_u, extremity1_v);
				extremity2_node = case1(pa, tri2, extremity2_u, extremity2_v);
				bar_creation2(pa, extremity1_node, extremity2_node, 0.0);	//printf("case1 case3 extremity1_node %4d extremity2_node %4d\n",extremity1_node,extremity2_node);
				}
			if ((same_side == 0) && (nb_cut == 0) && (tri1 != 0) && (close_node1 == 0) && (close_side1 == 0) && (tri2 == 0) && (close_node2 == 0) && (close_side2 == 0))
				{
				//same_side= 0 nb_cut=0 case1 case2
				//nothing to do
				}
			if ((same_side == 0) && (nb_cut == 0) && (tri1 != 0) && (close_node1 == 0) && (close_side1 == 0) && (tri2 != 0) && (close_node2 != 0) && (close_side2 != 0))
				{
				//same_side= 0 nb_cut=0 case1 case3
				extremity1_node = case1(pa, tri1, extremity1_u, extremity1_v);
				extremity2_node = close_node2;					//printf("case1 case3 extremity1_node %4d extremity2_node %4d\n",extremity1_node,extremity2_node);			
				bar_creation2(pa, extremity1_node, extremity2_node, 0.0);
				}
			if ((same_side == 0) && (nb_cut == 0) && (tri1 != 0) && (close_node1 == 0) && (close_side1 == 0) && (tri2 == 0) && (close_node2 != 0) && (close_side2 != 0))
				{
				//same_side= 0 nb_cut=0 case1 case4
				extremity1_node = case1(pa, tri1, extremity1_u, extremity1_v);
				extremity2_node = close_node2;					//printf("case1 case4 extremity1_node %4d extremity2_node %4d\n",extremity1_node,extremity2_node);			
				bar_creation2(pa, extremity1_node, extremity2_node, 0.0);
				}
			if ((same_side == 0) && (nb_cut == 0) && (tri1 != 0) && (close_node1 == 0) && (close_side1 == 0) && (tri2 != 0) && (close_node2 == 0) && (close_side2 != 0))
				{
				//same_side= 0 nb_cut=0 case1 case5
				extremity1_node = case1(pa, tri1, extremity1_u, extremity1_v);
				ptu = extremity2_u;
				ptv = extremity2_v;
				extremity2_node = is_node_close_side(pa,  &ptu,  &ptv);		//printf("case1 case5 extremity1_node %4d extremity2_node %4d\n",extremity1_node,extremity2_node);			
				bar_creation2(pa, extremity1_node, extremity2_node, 0.0);
				}
			if ((same_side == 0) && (nb_cut == 0) && (tri1 != 0) && (close_node1 == 0) && (close_side1 == 0) && (tri2 == 0) && (close_node2 == 0) && (close_side2 != 0))
				{
				//same_side= 0 nb_cut=0 case1 case6
				extremity1_node = case1(pa, tri1, extremity1_u, extremity1_v);
				ptu = extremity2_u;
				ptv = extremity2_v;
				extremity2_node = is_node_close_side(pa,  &ptu,  &ptv);		//printf("case1 case6 extremity1_node %4d extremity2_node %4d\n",extremity1_node,extremity2_node);			
				bar_creation2(pa, extremity1_node, extremity2_node, 0.0);
				}
			if ((same_side == 0) && (nb_cut == 0) && (tri1 != 0) && (close_node1 == 0) && (close_side1 == 0) && (tri2 != 0) && (close_node2 != 0) && (close_side2 == 0))
				{
				//same_side= 0 nb_cut=0 case1 case9
				extremity1_node = case1(pa, tri1, extremity1_u, extremity1_v);
				extremity2_node = close_node2;					//printf("case1 case9 extremity1_node %4d extremity2_node %4d\n",extremity1_node,extremity2_node);			
				bar_creation2(pa, extremity1_node, extremity2_node, 0.0);
				}
			//CASE2
			if ((same_side == 0) && (nb_cut == 0) && (tri1 == 0) && (close_node1 == 0) && (close_side1 == 0) && (tri2 != 0) && (close_node2 == 0) && (close_side2 == 0))
				{
				//same_side= 0 nb_cut=0 case2 case1
				//nothing to do
				}
			if ((same_side == 0) && (nb_cut == 0) && (tri1 == 0) && (close_node1 == 0) && (close_side1 == 0) && (tri2 == 0) && (close_node2 == 0) && (close_side2 == 0))
				{
				//same_side= 0 nb_cut=0 case2 case2
				//nothing to do
				}
			if ((same_side == 0) && (nb_cut == 0) && (tri1 == 0) && (close_node1 == 0) && (close_side1 == 0) && (tri2 != 0) && (close_node2 != 0) && (close_side2 != 0))
				{
				//same_side= 0 nb_cut=0 case2 case3
				//nothing to do
				}
			if ((same_side == 0) && (nb_cut == 0) && (tri1 == 0) && (close_node1 == 0) && (close_side1 == 0) && (tri2 == 0) && (close_node2 != 0) && (close_side2 != 0))
				{
				//same_side= 0 nb_cut=0 case2 case4
				//nothing to do
				}
			if ((same_side == 0) && (nb_cut == 0) && (tri1 == 0) && (close_node1 == 0) && (close_side1 == 0) && (tri2 != 0) && (close_node2 == 0) && (close_side2 != 0))
				{
				//same_side= 0 nb_cut=0 case2 case5
				//nothing to do
				}
			if ((same_side == 0) && (nb_cut == 0) && (tri1 == 0) && (close_node1 == 0) && (close_side1 == 0) && (tri2 == 0) && (close_node2 == 0) && (close_side2 != 0))
				{
				//same_side= 0 nb_cut=0 case2 case6
				//nothing to do
				}
			if ((same_side == 0) && (nb_cut == 0) && (tri1 == 0) && (close_node1 == 0) && (close_side1 == 0) && (tri2 != 0) && (close_node2 != 0) && (close_side2 == 0))
				{
				//same_side= 0 nb_cut=0 case2 case9
				//nothing to do
				}
			//CASE3
			if ((same_side == 0) && (nb_cut == 0) && (tri1 != 0) && (close_node1 != 0) && (close_side1 != 0) && (tri2 != 0) && (close_node2 == 0) && (close_side2 == 0))
				{
				//same_side= 0 nb_cut=0 case3 case1
				extremity1_node = close_node1;								
				extremity2_node = case1(pa, tri2, extremity2_u, extremity2_v); 	//printf("case3 case1 extremity1_node %4d extremity2_node %4d\n",extremity1_node,extremity2_node);
				bar_creation2(pa, extremity1_node, extremity2_node, 0.0);
				}
			if ((same_side == 0) && (nb_cut == 0) && (tri1 != 0) && (close_node1 != 0) && (close_side1 != 0) && (tri2 == 0) && (close_node2 == 0) && (close_side2 == 0))
				{
				//same_side= 0 nb_cut=0 case3 case2
				//nothing to do
				}
			if ((same_side == 0) && (nb_cut == 0) && (tri1 != 0) && (close_node1 != 0) && (close_side1 != 0) && (tri2 != 0) && (close_node2 != 0) && (close_side2 != 0))
				{
				//same_side= 0 nb_cut=0 case3 case3
				//nothing to do
				extremity1_node = close_node1;								
				extremity2_node = close_node2;					//printf("case3 case3 extremity1_node %4d extremity2_node %4d\n",extremity1_node,extremity2_node);			
				bar_creation2(pa, extremity1_node, extremity2_node, 0.0);
				}
			if ((same_side == 0) && (nb_cut == 0) && (tri1 != 0) && (close_node1 != 0) && (close_side1 != 0) && (tri2 == 0) && (close_node2 != 0) && (close_side2 != 0))
				{
				//same_side= 0 nb_cut=0 case3 case4
				extremity1_node = close_node1;								
				extremity2_node = close_node2;					//printf("case3 case4 extremity1_node %4d extremity2_node %4d\n",extremity1_node,extremity2_node);			
				bar_creation2(pa, extremity1_node, extremity2_node, 0.0);
				}
			if ((same_side == 0) && (nb_cut == 0) && (tri1 != 0) && (close_node1 != 0) && (close_side1 != 0) && (tri2 != 0) && (close_node2 == 0) && (close_side2 != 0))
				{
				//same_side= 0 nb_cut=0 case3 case5
				extremity1_node = close_node1;								
				ptu = extremity2_u;
				ptv = extremity2_v;
				extremity2_node = is_node_close_side(pa,  &ptu,  &ptv);		//printf("case3 case5 extremity1_node %4d extremity2_node %4d\n",extremity1_node,extremity2_node);			
				bar_creation2(pa, extremity1_node, extremity2_node, 0.0);
				}
			if ((same_side == 0) && (nb_cut == 0) && (tri1 != 0) && (close_node1 != 0) && (close_side1 != 0) && (tri2 == 0) && (close_node2 == 0) && (close_side2 != 0))
				{
				//same_side= 0 nb_cut=0 case3 case6
				extremity1_node = close_node1;								
				ptu = extremity2_u;
				ptv = extremity2_v;
				extremity2_node = is_node_close_side(pa,  &ptu,  &ptv);		//printf("case3 case6 extremity1_node %4d extremity2_node %4d\n",extremity1_node,extremity2_node);			
				bar_creation2(pa, extremity1_node, extremity2_node, 0.0);
				}
			if ((same_side == 0) && (nb_cut == 0) && (tri1 != 0) && (close_node1 != 0) && (close_side1 != 0) && (tri2 != 0) && (close_node2 != 0) && (close_side2 == 0))
				{
				//same_side= 0 nb_cut=0 case3 case9
				extremity1_node = close_node1;								
				extremity2_node = close_node2;					//printf("case3 case9 extremity1_node %4d extremity2_node %4d\n",extremity1_node,extremity2_node);			
				bar_creation2(pa, extremity1_node, extremity2_node, 0.0);
				}
			//CASE4
			if ((same_side == 0) && (nb_cut == 0) && (tri1 == 0) && (close_node1 != 0) && (close_side1 != 0) && (tri2 != 0) && (close_node2 == 0) && (close_side2 == 0))
				{
				//same_side= 0 nb_cut=0 case4 case1
				extremity1_node = close_node1;								
				extremity2_node = case1(pa, tri2, extremity2_u, extremity2_v);	//printf("case4 case1 extremity1_node %4d extremity2_node %4d\n",extremity1_node,extremity2_node);			
				bar_creation2(pa, extremity1_node, extremity2_node, 0.0);
				}
			if ((same_side == 0) && (nb_cut == 0) && (tri1 == 0) && (close_node1 != 0) && (close_side1 != 0) && (tri2 == 0) && (close_node2 == 0) && (close_side2 == 0))
				{
				//same_side= 0 nb_cut=0 case4 case2
				//nothing to do
				}
			if ((same_side == 0) && (nb_cut == 0) && (tri1 == 0) && (close_node1 != 0) && (close_side1 != 0) && (tri2 != 0) && (close_node2 != 0) && (close_side2 != 0))
				{
				//same_side= 0 nb_cut=0 case4 case3
				extremity1_node = close_node1;								
				extremity2_node = close_node2;					//printf("case4 case3 extremity1_node %4d extremity2_node %4d\n",extremity1_node,extremity2_node);			
				bar_creation2(pa, extremity1_node, extremity2_node, 0.0);
				}
			if ((same_side == 0) && (nb_cut == 0) && (tri1 == 0) && (close_node1 != 0) && (close_side1 != 0) && (tri2 == 0) && (close_node2 != 0) && (close_side2 != 0))
				{
				//same_side= 0 nb_cut=0 case4 case4
				extremity1_node = close_node1;								
				extremity2_node = close_node2;					//printf("case4 case4 extremity1_node %4d extremity2_node %4d\n",extremity1_node,extremity2_node);			
				bar_creation2(pa, extremity1_node, extremity2_node, 0.0);
				}
			if ((same_side == 0) && (nb_cut == 0) && (tri1 == 0) && (close_node1 != 0) && (close_side1 != 0) && (tri2 != 0) && (close_node2 == 0) && (close_side2 != 0))
				{
				//same_side= 0 nb_cut=0 case4 case5
				extremity1_node = close_node1;								
				ptu = extremity2_u;
				ptv = extremity2_v;
				extremity2_node = is_node_close_side(pa,  &ptu,  &ptv);		//printf("case4 case5 extremity1_node %4d extremity2_node %4d\n",extremity1_node,extremity2_node);			
				bar_creation2(pa, extremity1_node, extremity2_node, 0.0);
				}
			if ((same_side == 0) && (nb_cut == 0) && (tri1 == 0) && (close_node1 != 0) && (close_side1 != 0) && (tri2 == 0) && (close_node2 == 0) && (close_side2 != 0))
				{
				//same_side= 0 nb_cut=0 case4 case6
				extremity1_node = close_node1;								
				ptu = extremity2_u;
				ptv = extremity2_v;
				extremity2_node = is_node_close_side(pa,  &ptu,  &ptv);		//printf("case4 case6 extremity1_node %4d extremity2_node %4d\n",extremity1_node,extremity2_node);			
				bar_creation2(pa, extremity1_node, extremity2_node, 0.0);
				}
			if ((same_side == 0) && (nb_cut == 0) && (tri1 == 0) && (close_node1 != 0) && (close_side1 != 0) && (tri2 != 0) && (close_node2 != 0) && (close_side2 == 0))
				{
				//same_side= 0 nb_cut=0 case4 case9
				extremity1_node = close_node1;								
				extremity2_node = close_node2;					//printf("case4 case9 extremity1_node %4d extremity2_node %4d\n",extremity1_node,extremity2_node);			
				bar_creation2(pa, extremity1_node, extremity2_node, 0.0);
				}
			//CASE5
			if ((same_side == 0) && (nb_cut == 0) && (tri1 != 0) && (close_node1 == 0) && (close_side1 != 0) && (tri2 != 0) && (close_node2 == 0) && (close_side2 == 0))
				{
				//same_side= 0 nb_cut=0 case5 case1
				ptu = extremity1_u;
				ptv = extremity1_v;
				extremity1_node = is_node_close_side(pa,  &ptu,  &ptv);					
				extremity2_node = case1(pa, tri2, extremity2_u, extremity2_v);	//printf("case5 case1 extremity1_node %4d extremity2_node %4d\n",extremity1_node,extremity2_node);			
				bar_creation2(pa, extremity1_node, extremity2_node, 0.0);
				}
			if ((same_side == 0) && (nb_cut == 0) && (tri1 != 0) && (close_node1 == 0) && (close_side1 != 0) && (tri2 == 0) && (close_node2 == 0) && (close_side2 == 0))
				{
				//same_side= 0 nb_cut=0 case5 case2
				//nothing to do
				}
			if ((same_side == 0) && (nb_cut == 0) && (tri1 != 0) && (close_node1 == 0) && (close_side1 != 0) && (tri2 != 0) && (close_node2 != 0) && (close_side2 != 0))
				{
				//same_side= 0 nb_cut=0 case5 case3
				ptu = extremity1_u;
				ptv = extremity1_v;
				extremity1_node = is_node_close_side(pa,  &ptu,  &ptv);					
				extremity2_node = close_node2;					//printf("case5 case3 extremity1_node %4d extremity2_node %4d\n",extremity1_node,extremity2_node);			
				bar_creation2(pa, extremity1_node, extremity2_node, 0.0);
				}
			if ((same_side == 0) && (nb_cut == 0) && (tri1 != 0) && (close_node1 == 0) && (close_side1 != 0) && (tri2 == 0) && (close_node2 != 0) && (close_side2 != 0))
				{
				//same_side= 0 nb_cut=0 case5 case4
				ptu = extremity1_u;
				ptv = extremity1_v;
				extremity1_node = is_node_close_side(pa,  &ptu,  &ptv);					
				extremity2_node = close_node2;					//printf("case5 case4 extremity1_node %4d extremity2_node %4d\n",extremity1_node,extremity2_node);			
				bar_creation2(pa, extremity1_node, extremity2_node, 0.0);
				}
			if ((same_side == 0) && (nb_cut == 0) && (tri1 != 0) && (close_node1 == 0) && (close_side1 != 0) && (tri2 != 0) && (close_node2 == 0) && (close_side2 != 0))
				{
				//same_side= 0 nb_cut=0 case5 case5
				ptu = extremity1_u;
				ptv = extremity1_v;
				extremity1_node = is_node_close_side(pa,  &ptu,  &ptv);					
				ptu = extremity2_u;
				ptv = extremity2_v;
				extremity2_node = is_node_close_side(pa,  &ptu,  &ptv);		//printf("case5 case5 extremity1_node %4d extremity2_node %4d\n",extremity1_node,extremity2_node);			
				bar_creation2(pa, extremity1_node, extremity2_node, 0.0);
				}
			if ((same_side == 0) && (nb_cut == 0) && (tri1 != 0) && (close_node1 == 0) && (close_side1 != 0) && (tri2 == 0) && (close_node2 == 0) && (close_side2 != 0))
				{
				//same_side= 0 nb_cut=0 case5 case6
				ptu = extremity1_u;
				ptv = extremity1_v;
				extremity1_node = is_node_close_side(pa,  &ptu,  &ptv);					
				ptu = extremity2_u;
				ptv = extremity2_v;
				extremity2_node = is_node_close_side(pa,  &ptu,  &ptv);		//printf("case5 case6 extremity1_node %4d extremity2_node %4d\n",extremity1_node,extremity2_node);			
				bar_creation2(pa, extremity1_node, extremity2_node, 0.0);
				}
			if ((same_side == 0) && (nb_cut == 0) && (tri1 != 0) && (close_node1 == 0) && (close_side1 != 0) && (tri2 != 0) && (close_node2 != 0) && (close_side2 == 0))
				{
				//same_side= 0 nb_cut=0 case5 case9
				ptu = extremity1_u;
				ptv = extremity1_v;
				extremity1_node = is_node_close_side(pa,  &ptu,  &ptv);					
				extremity2_node = close_node2;					//printf("case5 case9 extremity1_node %4d extremity2_node %4d\n",extremity1_node,extremity2_node);			
				bar_creation2(pa, extremity1_node, extremity2_node, 0.0);
				}
				
			//CASE6
			if ((same_side == 0) && (nb_cut == 0) && (tri1 == 0) && (close_node1 == 0) && (close_side1 != 0) && (tri2 != 0) && (close_node2 == 0) && (close_side2 == 0))
				{
				//same_side= 0 nb_cut=0 case6 case1
				ptu = extremity1_u;
				ptv = extremity1_v;
				extremity1_node = is_node_close_side(pa,  &ptu,  &ptv);					
				extremity2_node = case1(pa, tri2, extremity2_u, extremity2_v);	//printf("case6 case1 extremity1_node %4d extremity2_node %4d\n",extremity1_node,extremity2_node);
				bar_creation2(pa, extremity1_node, extremity2_node, 0.0);
				}
			if ((same_side == 0) && (nb_cut == 0) && (tri1 == 0) && (close_node1 == 0) && (close_side1 != 0) && (tri2 == 0) && (close_node2 == 0) && (close_side2 == 0))
				{
				//same_side= 0 nb_cut=0 case6 case2
				//nothing to do
				}
			if ((same_side == 0) && (nb_cut == 0) && (tri1 == 0) && (close_node1 == 0) && (close_side1 != 0) && (tri2 != 0) && (close_node2 != 0) && (close_side2 != 0))
				{
				//same_side= 0 nb_cut=0 case6 case3
				ptu = extremity1_u;
				ptv = extremity1_v;
				extremity1_node = is_node_close_side(pa,  &ptu,  &ptv);					
				extremity2_node = close_node2;					//printf("case6 case3 extremity1_node %4d extremity2_node %4d\n",extremity1_node,extremity2_node);			
				bar_creation2(pa, extremity1_node, extremity2_node, 0.0);
				}
			if ((same_side == 0) && (nb_cut == 0) && (tri1 == 0) && (close_node1 == 0) && (close_side1 != 0) && (tri2 == 0) && (close_node2 != 0) && (close_side2 != 0))
				{
				//same_side= 0 nb_cut=0 case6 case4
				ptu = extremity1_u;
				ptv = extremity1_v;
				extremity1_node = is_node_close_side(pa,  &ptu,  &ptv);					
				extremity2_node = close_node2;					//printf("case6 case4 extremity1_node %4d extremity2_node %4d\n",extremity1_node,extremity2_node);			
				bar_creation2(pa, extremity1_node, extremity2_node, 0.0);
				}
			if ((same_side == 0) && (nb_cut == 0) && (tri1 == 0) && (close_node1 == 0) && (close_side1 != 0) && (tri2 != 0) && (close_node2 == 0) && (close_side2 != 0))
				{
				//same_side= 0 nb_cut=0 case6 case5
				ptu = extremity1_u;
				ptv = extremity1_v;
				extremity1_node = is_node_close_side(pa,  &ptu,  &ptv);					
				ptu = extremity2_u;
				ptv = extremity2_v;
				extremity2_node = is_node_close_side(pa,  &ptu,  &ptv);		//printf("case6 case5 extremity1_node %4d extremity2_node %4d\n",extremity1_node,extremity2_node);			
				bar_creation2(pa, extremity1_node, extremity2_node, 0.0);
				}
			if ((same_side == 0) && (nb_cut == 0) && (tri1 == 0) && (close_node1 == 0) && (close_side1 != 0) && (tri2 == 0) && (close_node2 == 0) && (close_side2 != 0))
				{
				//same_side= 0 nb_cut=0 case6 case6
				ptu = extremity1_u;
				ptv = extremity1_v;
				extremity1_node = is_node_close_side(pa,  &ptu,  &ptv);					
				ptu = extremity2_u;
				ptv = extremity2_v;
				extremity2_node = is_node_close_side(pa,  &ptu,  &ptv);		//printf("case6 case6 extremity1_node %4d extremity2_node %4d\n",extremity1_node,extremity2_node);			
				bar_creation2(pa, extremity1_node, extremity2_node, 0.0);
				}
			if ((same_side == 0) && (nb_cut == 0) && (tri1 == 0) && (close_node1 == 0) && (close_side1 != 0) && (tri2 != 0) && (close_node2 != 0) && (close_side2 == 0))
				{
				//same_side= 0 nb_cut=0 case6 case9
				ptu = extremity1_u;
				ptv = extremity1_v;
				extremity1_node = is_node_close_side(pa,  &ptu,  &ptv);					
				extremity2_node = close_node2;					//printf("case6 case9 extremity1_node %4d extremity2_node %4d\n",extremity1_node,extremity2_node);			
				bar_creation2(pa, extremity1_node, extremity2_node, 0.0);
				}
			//CASE9
			if ((same_side == 0) && (nb_cut == 0) && (tri1 != 0) && (close_node1 != 0) && (close_side1 == 0) && (tri2 != 0) && (close_node2 == 0) && (close_side2 == 0))
				{
				//same_side= 0 nb_cut=0 case9 case1
				extremity1_node = close_node1;										
				extremity2_node = case1(pa, tri2, extremity2_u, extremity2_v);	//printf("case9 case1 extremity1_node %4d extremity2_node %4d\n",extremity1_node,extremity2_node);
				bar_creation2(pa, extremity1_node, extremity2_node, 0.0);
				}
			if ((same_side == 0) && (nb_cut == 0) && (tri1 != 0) && (close_node1 != 0) && (close_side1 == 0) && (tri2 == 0) && (close_node2 == 0) && (close_side2 == 0))
				{
				//same_side= 0 nb_cut=0 case9 case2
				//nothing to do
				}
			if ((same_side == 0) && (nb_cut == 0) && (tri1 != 0) && (close_node1 != 0) && (close_side1 == 0) && (tri2 != 0) && (close_node2 != 0) && (close_side2 != 0))
				{
				//same_side= 0 nb_cut=0 case9 case3
				extremity1_node = close_node1;								
				extremity2_node = close_node2;					//printf("case9 case3 extremity1_node %4d extremity2_node %4d\n",extremity1_node,extremity2_node);			
				bar_creation2(pa, extremity1_node, extremity2_node, 0.0);
				}
			if ((same_side == 0) && (nb_cut == 0) && (tri1 != 0) && (close_node1 != 0) && (close_side1 == 0) && (tri2 == 0) && (close_node2 != 0) && (close_side2 != 0))
				{
				//same_side= 0 nb_cut=0 case9 case4
				extremity1_node = close_node1;					
				extremity2_node = close_node2;					//printf("case9 case4 extremity1_node %4d extremity2_node %4d\n",extremity1_node,extremity2_node);			
				bar_creation2(pa, extremity1_node, extremity2_node, 0.0);
				}
			if ((same_side == 0) && (nb_cut == 0) && (tri1 != 0) && (close_node1 != 0) && (close_side1 == 0) && (tri2 != 0) && (close_node2 == 0) && (close_side2 != 0))
				{
				//same_side= 0 nb_cut=0 case9 case5
				extremity1_node = close_node1;								
				ptu = extremity2_u;
				ptv = extremity2_v;
				extremity2_node = is_node_close_side(pa,  &ptu,  &ptv);		//printf("case9 case5 extremity1_node %4d extremity2_node %4d\n",extremity1_node,extremity2_node);			
				bar_creation2(pa, extremity1_node, extremity2_node, 0.0);
				}
			if ((same_side == 0) && (nb_cut == 0) && (tri1 != 0) && (close_node1 != 0) && (close_side1 == 0) && (tri2 == 0) && (close_node2 == 0) && (close_side2 != 0))
				{
				//same_side= 0 nb_cut=0 case9 case6
				extremity1_node = close_node1;							
				ptu = extremity2_u;
				ptv = extremity2_v;
				extremity2_node = is_node_close_side(pa,  &ptu,  &ptv);		//printf("case9 case6 extremity1_node %4d extremity2_node %4d\n",extremity1_node,extremity2_node);			
				bar_creation2(pa, extremity1_node, extremity2_node, 0.0);
				}
			if ((same_side == 0) && (nb_cut == 0) && (tri1 != 0) && (close_node1 != 0) && (close_side1 == 0) && (tri2 != 0) && (close_node2 != 0) && (close_side2 == 0))
				{
				//same_side= 0 nb_cut=0 case9 case9
				extremity1_node = close_node1;								
				extremity2_node = close_node2;					//printf("case9 case9 extremity1_node %4d extremity2_node %4d\n",extremity1_node,extremity2_node);			
				bar_creation2(pa, extremity1_node, extremity2_node, 0.0);
				}


			//nb_cut = 1
			//CASE1
			if ((same_side == 0) && (nb_cut == 1) && (tri1 != 0) && (close_node1 == 0) && (close_side1 == 0) && (tri2 != 0) && (close_node2 == 0) && (close_side2 == 0))
				{
				//same_side= 0 nb_cut=1 case1 case1
				//nothing to do
				}
			if ((same_side == 0) && (nb_cut == 1) && (tri1 != 0) && (close_node1 == 0) && (close_side1 == 0) && (tri2 == 0) && (close_node2 == 0) && (close_side2 == 0))
				{
				//same_side= 0 nb_cut=1 case1 case2
				extremity1_node = case1(pa, tri1, extremity1_u, extremity1_v);	
				extremity2_node = case2(pa, cut_side[nb_cut], cut_beta[nb_cut], &extremity2_u, &extremity2_v);	//printf("base1 case2 extremity1_node %4d extremity2_node %4d\n",extremity1_node,extremity2_node);
				bar_creation2(pa, extremity1_node, extremity2_node, 1.0-cut_alpha[nb_cut]);				
				}
			if ((same_side == 0) && (nb_cut == 1) && (tri1 != 0) && (close_node1 == 0) && (close_side1 == 0) && (tri2 != 0) && (close_node2 != 0) && (close_side2 != 0))
				{
				//same_side= 0 nb_cut=1 case1 case3
				//nothing to do
				}
			if ((same_side == 0) && (nb_cut == 1) && (tri1 != 0) && (close_node1 == 0) && (close_side1 == 0) && (tri2 == 0) && (close_node2 != 0) && (close_side2 != 0))
				{
				//same_side= 0 nb_cut=1 case1 case4
				//nothing to do
				}
			if ((same_side == 0) && (nb_cut == 1) && (tri1 != 0) && (close_node1 == 0) && (close_side1 == 0) && (tri2 != 0) && (close_node2 == 0) && (close_side2 != 0))
				{
				//same_side= 0 nb_cut=1 case1 case5
				//nothing to do
				}
			if ((same_side == 0) && (nb_cut == 1) && (tri1 != 0) && (close_node1 == 0) && (close_side1 == 0) && (tri2 == 0) && (close_node2 == 0) && (close_side2 != 0))
				{
				//same_side= 0 nb_cut=1 case1 case6
				//nothing to do
				}
			if ((same_side == 0) && (nb_cut == 1) && (tri1 != 0) && (close_node1 == 0) && (close_side1 == 0) && (tri2 != 0) && (close_node2 != 0) && (close_side2 == 0))
				{
				//same_side= 0 nb_cut=1 case1 case9
				//nothing to do
				}
			//CASE2
			if ((same_side == 0) && (nb_cut == 1) && (tri1 == 0) && (close_node1 == 0) && (close_side1 == 0) && (tri2 != 0) && (close_node2 == 0) && (close_side2 == 0))
				{
				//same_side= 0 nb_cut=1 case2 case1
				extremity1_node = case2(pa, cut_side[nb_cut], cut_beta[nb_cut], &extremity1_u, &extremity1_v);	
				extremity2_node = case1(pa, tri2, extremity2_u, extremity2_v);	
				bar_creation2(pa, extremity1_node, extremity2_node, cut_alpha[nb_cut]);				//printf("base2 case1 extremity1_node %4d extremity2_node %4d\n",extremity1_node,extremity2_node);		
				}
			if ((same_side == 0) && (nb_cut == 1) && (tri1 == 0) && (close_node1 == 0) && (close_side1 == 0) && (tri2 == 0) && (close_node2 == 0) && (close_side2 == 0))
				{
				//same_side= 0 nb_cut=1 case2 case2
				//nothing to do
				}
			if ((same_side == 0) && (nb_cut == 1) && (tri1 == 0) && (close_node1 == 0) && (close_side1 == 0) && (tri2 != 0) && (close_node2 != 0) && (close_side2 != 0) && (is_node_close_side2(pa, cut_side[nb_cut], extremity2_u, extremity2_v) != 1))
				{
				//same_side= 0 nb_cut=1 case2 case3
				extremity1_node = case2(pa, cut_side[nb_cut], cut_beta[nb_cut], &extremity1_u, &extremity1_v);
				extremity2_node = close_node2;									//printf("base2 case3 extremity1_node %4d extremity2_node %4d\n",extremity1_node,extremity2_node);			
				bar_creation2(pa, extremity1_node, extremity2_node, cut_alpha[nb_cut]);				
				}
			if ((same_side == 0) && (nb_cut == 1) && (tri1 == 0) && (close_node1 == 0) && (close_side1 == 0) && (tri2 == 0) && (close_node2 != 0) && (close_side2 != 0))
				{
				//same_side= 0 nb_cut=1 case2 case4
				extremity1_node = case2(pa, cut_side[nb_cut], cut_beta[nb_cut], &extremity1_u, &extremity1_v);
				extremity2_node = close_node2;									//printf("base2 case4 extremity1_node %4d extremity2_node %4d\n",extremity1_node,extremity2_node);			
				bar_creation2(pa, extremity1_node, extremity2_node, cut_alpha[nb_cut]);				
				}
			if ((same_side == 0) && (nb_cut == 1) && (tri1 == 0) && (close_node1 == 0) && (close_side1 == 0) && (tri2 != 0) && (close_node2 == 0) && (close_side2 != 0) && (is_node_close_side2(pa, cut_side[nb_cut], extremity2_u, extremity2_v) != 1))
				{
				//same_side= 0 nb_cut=1 case2 case5
				extremity1_node = case2(pa, cut_side[nb_cut], cut_beta[nb_cut], &extremity1_u, &extremity1_v);
				ptu = extremity2_u;
				ptv = extremity2_v;
				extremity2_node = is_node_close_side(pa,  &ptu,  &ptv);						//printf("base2 case5 extremity1_node %4d extremity2_node %4d\n",extremity1_node,extremity2_node);			
				bar_creation2(pa, extremity1_node, extremity2_node, cut_alpha[nb_cut]);				
				}
			if ((same_side == 0) && (nb_cut == 1) && (tri1 == 0) && (close_node1 == 0) && (close_side1 == 0) && (tri2 == 0) && (close_node2 == 0) && (close_side2 != 0))
				{
				//same_side= 0 nb_cut=1 case2 case6
				extremity1_node = case2(pa, cut_side[nb_cut], cut_beta[nb_cut], &extremity1_u, &extremity1_v);
				ptu = extremity2_u;
				ptv = extremity2_v;
				extremity2_node = is_node_close_side(pa,  &ptu,  &ptv);						//printf("base2 case6 extremity1_node %4d extremity2_node %4d\n",extremity1_node,extremity2_node);			
				bar_creation2(pa, extremity1_node, extremity2_node, cut_alpha[nb_cut]);				
				}
			if ((same_side == 0) && (nb_cut == 1) && (tri1 == 0) && (close_node1 == 0) && (close_side1 == 0) && (tri2 != 0) && (close_node2 != 0) && (close_side2 == 0))
				{
				//same_side= 0 nb_cut=1 case2 case9
				extremity1_node = case2(pa, cut_side[nb_cut], cut_beta[nb_cut], &extremity1_u, &extremity1_v);
				extremity2_node = close_node2;									//printf("base9 case9 extremity1_node %4d extremity2_node %4d\n",extremity1_node,extremity2_node);			
				bar_creation2(pa, extremity1_node, extremity2_node, cut_alpha[nb_cut]);				
				}
			//CASE3
			if ((same_side == 0) && (nb_cut == 1) && (tri1 != 0) && (close_node1 != 0) && (close_side1 != 0) && (tri2 != 0) && (close_node2 == 0) && (close_side2 == 0))
				{
				//same_side= 0 nb_cut=1 case3 case1
				//nothing to do
				}
			if ((same_side == 0) && (nb_cut == 1) && (tri1 != 0) && (close_node1 != 0) && (close_side1 != 0) && (tri2 == 0) && (close_node2 == 0) && (close_side2 == 0) && (is_node_close_side2(pa, cut_side[nb_cut], extremity1_u, extremity1_v) != 1))
				{			
				//same_side= 0 nb_cut=1 case3 case2
				extremity1_node = close_node1;									
				extremity2_node = case2(pa, cut_side[nb_cut], cut_beta[nb_cut], &extremity2_u, &extremity2_v);	//printf("base3 case2 extremity1_node %4d extremity2_node %4d\n",extremity1_node,extremity2_node);
				bar_creation2(pa, extremity1_node, extremity2_node, 1.0-cut_alpha[nb_cut]);				
				}
			if ((same_side == 0) && (nb_cut == 1) && (tri1 != 0) && (close_node1 != 0) && (close_side1 != 0) && (tri2 != 0) && (close_node2 != 0) && (close_side2 != 0))
				{
				//same_side= 0 nb_cut=1 case3 case3
				//nothing to do
				}
			if ((same_side == 0) && (nb_cut == 1) && (tri1 != 0) && (close_node1 != 0) && (close_side1 != 0) && (tri2 == 0) && (close_node2 != 0) && (close_side2 != 0))
				{
				//same_side= 0 nb_cut=1 case3 case4
				extremity1_node = close_node1;									
				extremity2_node = close_node2;									//printf("base3 case4 extremity1_node %4d extremity2_node %4d\n",extremity1_node,extremity2_node);			
				bar_creation2(pa, extremity1_node, extremity2_node, 0.0);				
				}
			if ((same_side == 0) && (nb_cut == 1) && (tri1 != 0) && (close_node1 != 0) && (close_side1 != 0) && (tri2 != 0) && (close_node2 == 0) && (close_side2 != 0))
				{
				//same_side= 0 nb_cut=1 case3 case5
				//nothing to do
				}
			if ((same_side == 0) && (nb_cut == 1) && (tri1 != 0) && (close_node1 != 0) && (close_side1 != 0) && (tri2 == 0) && (close_node2 == 0) && (close_side2 != 0))
				{
				//same_side= 0 nb_cut=1 case3 case6
				extremity1_node = close_node1;								
				ptu = extremity2_u;
				ptv = extremity2_v;
				extremity2_node = is_node_close_side(pa,  &ptu,  &ptv);						//printf("base3 case6 extremity1_node %4d extremity2_node %4d\n",extremity1_node,extremity2_node);			
				bar_creation2(pa, extremity1_node, extremity2_node, 0.0);				
				}
			if ((same_side == 0) && (nb_cut == 1) && (tri1 != 0) && (close_node1 != 0) && (close_side1 != 0) && (tri2 != 0) && (close_node2 != 0) && (close_side2 == 0))
				{
				//same_side= 0 nb_cut=1 case3 case9
				//nothing to do
				}
			//CASE4
			if ((same_side == 0) && (nb_cut == 1) && (tri1 == 0) && (close_node1 != 0) && (close_side1 != 0) && (tri2 != 0) && (close_node2 == 0) && (close_side2 == 0))
				{
				//same_side= 0 nb_cut=1 case4 case1
				extremity1_node = close_node1;								
				extremity2_node = case1(pa, tri2, extremity2_u, extremity2_v);					//printf("base4 case1 extremity1_node %4d extremity2_node %4d\n",extremity1_node,extremity2_node);
				bar_creation2(pa, extremity1_node, extremity2_node, 0.0);				
				}
			if ((same_side == 0) && (nb_cut == 1) && (tri1 == 0) && (close_node1 != 0) && (close_side1 != 0) && (tri2 == 0) && (close_node2 == 0) && (close_side2 == 0))
				{
				//same_side= 0 nb_cut=1 case4 case2
				//nothing to do
				}
			if ((same_side == 0) && (nb_cut == 1) && (tri1 == 0) && (close_node1 != 0) && (close_side1 != 0) && (tri2 != 0) && (close_node2 != 0) && (close_side2 != 0))
				{
				//same_side= 0 nb_cut=1 case4 case3
				extremity1_node = close_node1;								
				extremity2_node = close_node2;									//printf("base4 case3 extremity1_node %4d extremity2_node %4d\n",extremity1_node,extremity2_node);			
				bar_creation2(pa, extremity1_node, extremity2_node, 0.0);				
				}
			if ((same_side == 0) && (nb_cut == 1) && (tri1 == 0) && (close_node1 != 0) && (close_side1 != 0) && (tri2 == 0) && (close_node2 != 0) && (close_side2 != 0))
				{
				//same_side= 0 nb_cut=1 case4 case4
				//nothing to do
				}
			if ((same_side == 0) && (nb_cut == 1) && (tri1 == 0) && (close_node1 != 0) && (close_side1 != 0) && (tri2 != 0) && (close_node2 == 0) && (close_side2 != 0))
				{
				//same_side= 0 nb_cut=1 case4 case5
				extremity1_node = close_node1;								
				ptu = extremity2_u;
				ptv = extremity2_v;
				extremity2_node = is_node_close_side(pa,  &ptu,  &ptv);						//printf("base2 case5 extremity1_node %4d extremity2_node %4d\n",extremity1_node,extremity2_node);			
				bar_creation2(pa, extremity1_node, extremity2_node, 0.0);				
				}
			if ((same_side == 0) && (nb_cut == 1) && (tri1 == 0) && (close_node1 != 0) && (close_side1 != 0) && (tri2 == 0) && (close_node2 == 0) && (close_side2 != 0))
				{
				//same_side= 0 nb_cut=1 case4 case6
				//nothing to do
				}
			if ((same_side == 0) && (nb_cut == 1) && (tri1 == 0) && (close_node1 != 0) && (close_side1 != 0) && (tri2 != 0) && (close_node2 != 0) && (close_side2 == 0))
				{
				//same_side= 0 nb_cut=1 case4 case9
				extremity1_node = close_node1;								
				extremity2_node = close_node2;									//printf("base9 case9 extremity1_node %4d extremity2_node %4d\n",extremity1_node,extremity2_node);			
				bar_creation2(pa, extremity1_node, extremity2_node, 0.0);				
				}
			//CASE5
			if ((same_side == 0) && (nb_cut == 1) && (tri1 != 0) && (close_node1 == 0) && (close_side1 != 0) && (tri2 != 0) && (close_node2 == 0) && (close_side2 == 0))
				{
				//same_side= 0 nb_cut=1 case5 case1
				//nothing to do
				}
			if ((same_side == 0) && (nb_cut == 1) && (tri1 != 0) && (close_node1 == 0) && (close_side1 != 0) && (tri2 == 0) && (close_node2 == 0) && (close_side2 == 0) && (is_node_close_side2(pa, cut_side[nb_cut], extremity1_u, extremity1_v) != 1))
				{
				//same_side= 0 nb_cut=1 case5 case2
				ptu = extremity1_u;
				ptv = extremity1_v;
				extremity1_node = is_node_close_side(pa,  &ptu,  &ptv);					
				extremity2_node = case2(pa, cut_side[nb_cut], cut_beta[nb_cut], &extremity2_u, &extremity2_v);	//printf("base5 case2 extremity1_node %4d extremity2_node %4d\n",extremity1_node,extremity2_node);
				bar_creation2(pa, extremity1_node, extremity2_node, 1.0-cut_alpha[nb_cut]);				
				}
			if ((same_side == 0) && (nb_cut == 1) && (tri1 != 0) && (close_node1 == 0) && (close_side1 != 0) && (tri2 != 0) && (close_node2 != 0) && (close_side2 != 0))
				{
				//same_side= 0 nb_cut=1 case5 case3
				//nothing to do
				}
			if ((same_side == 0) && (nb_cut == 1) && (tri1 != 0) && (close_node1 == 0) && (close_side1 != 0) && (tri2 == 0) && (close_node2 != 0) && (close_side2 != 0))
				{
				//same_side= 0 nb_cut=1 case5 case4
				ptu = extremity1_u;
				ptv = extremity1_v;
				extremity1_node = is_node_close_side(pa,  &ptu,  &ptv);					
				extremity2_node = close_node2;									//printf("base4 case3 extremity1_node %4d extremity2_node %4d\n",extremity1_node,extremity2_node);			
				bar_creation2(pa, extremity1_node, extremity2_node, 0.0);				
				}
			if ((same_side == 0) && (nb_cut == 1) && (tri1 != 0) && (close_node1 == 0) && (close_side1 != 0) && (tri2 != 0) && (close_node2 == 0) && (close_side2 != 0))
				{
				//same_side= 0 nb_cut=1 case5 case5
				//nothing to do
				}
			if ((same_side == 0) && (nb_cut == 1) && (tri1 != 0) && (close_node1 == 0) && (close_side1 != 0) && (tri2 == 0) && (close_node2 == 0) && (close_side2 != 0))
				{
				//same_side= 0 nb_cut=1 case5 case6
				ptu = extremity1_u;
				ptv = extremity1_v;
				extremity1_node = is_node_close_side(pa,  &ptu,  &ptv);						
				ptu = extremity2_u;
				ptv = extremity2_v;
				extremity2_node = is_node_close_side(pa,  &ptu,  &ptv);						//printf("base5 case6 extremity1_node %4d extremity2_node %4d\n",extremity1_node,extremity2_node);			
				}
			if ((same_side == 0) && (nb_cut == 1) && (tri1 != 0) && (close_node1 == 0) && (close_side1 != 0) && (tri2 != 0) && (close_node2 != 0) && (close_side2 == 0))
				{
				//same_side= 0 nb_cut=1 case5 case9
				//nothing to do
				}
				
			//CASE6
			if ((same_side == 0) && (nb_cut == 1) && (tri1 == 0) && (close_node1 == 0) && (close_side1 != 0) && (tri2 != 0) && (close_node2 == 0) && (close_side2 == 0))
				{
				//same_side= 0 nb_cut=1 case6 case1
				ptu = extremity1_u;
				ptv = extremity1_v;
				extremity1_node = is_node_close_side(pa,  &ptu,  &ptv);						
				extremity2_node = case1(pa, tri2, extremity2_u, extremity2_v);					//printf("base6 case1 extremity1_node %4d extremity2_node %4d\n",extremity1_node,extremity2_node);
				bar_creation2(pa, extremity1_node, extremity2_node, 0.0);				
				}
			if ((same_side == 0) && (nb_cut == 1) && (tri1 == 0) && (close_node1 == 0) && (close_side1 != 0) && (tri2 == 0) && (close_node2 == 0) && (close_side2 == 0))
				{
				//same_side= 0 nb_cut=1 case6 case2
				//nothing to do
				}
			if ((same_side == 0) && (nb_cut == 1) && (tri1 == 0) && (close_node1 == 0) && (close_side1 != 0) && (tri2 != 0) && (close_node2 != 0) && (close_side2 != 0))
				{
				//same_side= 0 nb_cut=1 case6 case3
				ptu = extremity1_u;
				ptv = extremity1_v;
				extremity1_node = is_node_close_side(pa,  &ptu,  &ptv);						
				extremity2_node = close_node2;									//printf("base6 case3 extremity1_node %4d extremity2_node %4d\n",extremity1_node,extremity2_node);			
				bar_creation2(pa, extremity1_node, extremity2_node, 0.0);				
				}
			if ((same_side == 0) && (nb_cut == 1) && (tri1 == 0) && (close_node1 == 0) && (close_side1 != 0) && (tri2 == 0) && (close_node2 != 0) && (close_side2 != 0))
				{
				//same_side= 0 nb_cut=1 case6 case4
				//nothing to do
				}
			if ((same_side == 0) && (nb_cut == 1) && (tri1 == 0) && (close_node1 == 0) && (close_side1 != 0) && (tri2 != 0) && (close_node2 == 0) && (close_side2 != 0))
				{
				//same_side= 0 nb_cut=1 case6 case5
				ptu = extremity1_u;
				ptv = extremity1_v;
				extremity1_node = is_node_close_side(pa,  &ptu,  &ptv);						
				ptu = extremity2_u;
				ptv = extremity2_v;
				extremity2_node = is_node_close_side(pa,  &ptu,  &ptv);						//printf("base6 case5 extremity1_node %4d extremity2_node %4d\n",extremity1_node,extremity2_node);			
				bar_creation2(pa, extremity1_node, extremity2_node, 0.0);				
				}
			if ((same_side == 0) && (nb_cut == 1) && (tri1 == 0) && (close_node1 == 0) && (close_side1 != 0) && (tri2 == 0) && (close_node2 == 0) && (close_side2 != 0))
				{
				//same_side= 0 nb_cut=1 case6 case6
				//nothing to do
				}
			if ((same_side == 0) && (nb_cut == 1) && (tri1 == 0) && (close_node1 == 0) && (close_side1 != 0) && (tri2 != 0) && (close_node2 != 0) && (close_side2 == 0))
				{
				//same_side= 0 nb_cut=1 case6 case9
				ptu = extremity1_u;
				ptv = extremity1_v;
				extremity1_node = is_node_close_side(pa,  &ptu,  &ptv);						
				extremity2_node = close_node2;									//printf("base6 case9 extremity1_node %4d extremity2_node %4d\n",extremity1_node,extremity2_node);			
				bar_creation2(pa, extremity1_node, extremity2_node, 0.0);				
				}
			//CASE9
			if ((same_side == 0) && (nb_cut == 1) && (tri1 != 0) && (close_node1 != 0) && (close_side1 == 0) && (tri2 != 0) && (close_node2 == 0) && (close_side2 == 0))
				{
				//same_side= 0 nb_cut=1 case9 case1
				//nothing to do
				}
			if ((same_side == 0) && (nb_cut == 1) && (tri1 != 0) && (close_node1 != 0) && (close_side1 == 0) && (tri2 == 0) && (close_node2 == 0) && (close_side2 == 0))
				{
				//same_side= 0 nb_cut=1 case9 case2
				extremity1_node = close_node1;									
				extremity2_node = case2(pa, cut_side[nb_cut], cut_beta[nb_cut], &extremity2_u, &extremity2_v);	//printf("base9 case2 extremity1_node %4d extremity2_node %4d\n",extremity1_node,extremity2_node);
				bar_creation2(pa, extremity1_node, extremity2_node, 1.0-cut_alpha[nb_cut]);				
				}
			if ((same_side == 0) && (nb_cut == 1) && (tri1 != 0) && (close_node1 != 0) && (close_side1 == 0) && (tri2 != 0) && (close_node2 != 0) && (close_side2 != 0))
				{
				//same_side= 0 nb_cut=1 case9 case3
				//nothing to do
				}
			if ((same_side == 0) && (nb_cut == 1) && (tri1 != 0) && (close_node1 != 0) && (close_side1 == 0) && (tri2 == 0) && (close_node2 != 0) && (close_side2 != 0))
				{
				//same_side= 0 nb_cut=1 case9 case4
				extremity1_node = close_node1;									
				extremity2_node = close_node2;									//printf("base9 case4 extremity1_node %4d extremity2_node %4d\n",extremity1_node,extremity2_node);			
				bar_creation2(pa, extremity1_node, extremity2_node, 0.0);				
				}
			if ((same_side == 0) && (nb_cut == 1) && (tri1 != 0) && (close_node1 != 0) && (close_side1 == 0) && (tri2 != 0) && (close_node2 == 0) && (close_side2 != 0))
				{
				//same_side= 0 nb_cut=1 case9 case5
				//nothing to do
				}
			if ((same_side == 0) && (nb_cut == 1) && (tri1 != 0) && (close_node1 != 0) && (close_side1 == 0) && (tri2 == 0) && (close_node2 == 0) && (close_side2 != 0))
				{
				//same_side= 0 nb_cut=1 case9 case6
				extremity1_node = close_node1;									
				ptu = extremity2_u;
				ptv = extremity2_v;
				extremity2_node = is_node_close_side(pa,  &ptu,  &ptv);						//printf("base6 case5 extremity1_node %4d extremity2_node %4d\n",extremity1_node,extremity2_node);			
				bar_creation2(pa, extremity1_node, extremity2_node, 0.0);				
				}
			if ((same_side == 0) && (nb_cut == 1) && (tri1 != 0) && (close_node1 != 0) && (close_side1 == 0) && (tri2 != 0) && (close_node2 != 0) && (close_side2 == 0))
				{
				//same_side= 0 nb_cut=1 case9 case9
				//nothing to do
				}
			}
		}
	////////////////////end of the loop on u	/////////////////////////////////////////////////////////////////////


	////////////////////beginning of the loop on v	/////////////////////////////////////////////////////////////////////
	for (zv=int_min_V;zv<=int_max_V;zv+= period1)
		{
		for (zu=int_min_U;zu<=int_max_U;zu+=period2)
			{
			/*AB twine, CD panel side, intersection of twine with panel side is M, such AM = alpha AB and CM = beta CD*/
			decal_u = panneau[pa].netting_2_ropes_gap_U * panneau[pa].netting_2_ropes_period;
			decal_v = panneau[pa].netting_2_ropes_gap_V * panneau[pa].netting_2_ropes_period;
			//printf("zu %4d zv %4d\n",zu,zv);	
			//printf("decal_u %6.2lf decal_v %6.2lf\n",decal_u,decal_v);
			extremity1_u = (double) zu+decal_u;		extremity1_v = (double) zv+decal_v;	
			extremity2_u = (double) zu+decal_u+period2;	extremity2_v = (double) zv+decal_v;
			//printf("ex12uv %5.0lf %5.0lf %5.0lf %5.0lf ",extremity1_u,extremity1_v,extremity2_u,extremity2_v);	
			same_side = side_neighbor(pa,extremity1_u,extremity1_v,extremity2_u,extremity2_v);	//if the node couple is on the same side, this side is same_side
			nb_cut = number_of_cuts(pa, extremity1_u, extremity1_v, extremity2_u, extremity2_v, cut_triangle, cut_side, cut_alpha, cut_beta, cut_code);	//nb of cut the segment between the node couple cuts the sides of the panel
			close_node1 = is_node_close_another_one2(pa, extremity1_u, extremity1_v);
			close_node2 = is_node_close_another_one2(pa, extremity2_u, extremity2_v);
			close_side1 = 0;
			close_side2 = 0;
			for (co=1;co<=panneau[pa].nb_noeud_contour;co++)
				{
				if (is_node_close_side2(pa, co, extremity1_u, extremity1_v) == 1) close_side1 = co;
				if (is_node_close_side2(pa, co, extremity2_u, extremity2_v) == 1) close_side2 = co;
				}
			tri1 = interieur_panneau_filaire2(extremity1_u, extremity1_v, pa);		
			tri2 = interieur_panneau_filaire2(extremity2_u, extremity2_v, pa);
			//printf("samside %2d nb_cut %2d ",same_side,nb_cut);	
			//printf("tri1 %2d clnod1 %3d clsid1 %2d ",tri1,close_node1,close_side1);	
			//printf("tri2 %2d clnod2 %3d clsid2 %2d ",tri2,close_node2,close_side2);	
			//if (nb_cut == 1) printf("cut_side %2d ",cut_side[nb_cut]);	
			//printf("\n");	
			//nb_cut = 0
			//CASE1
			if ((same_side == 0) && (nb_cut == 0) && (tri1 != 0) && (close_node1 == 0) && (close_side1 == 0) && (tri2 != 0) && (close_node2 == 0) && (close_side2 == 0))
				{
				//same_side= 0 nb_cut=0 case1 case1
				extremity1_node = case1(pa, tri1, extremity1_u, extremity1_v);
				extremity2_node = case1(pa, tri2, extremity2_u, extremity2_v);
				bar_creation2(pa, extremity1_node, extremity2_node, 0.0);	//printf("case1 case3 extremity1_node %4d extremity2_node %4d\n",extremity1_node,extremity2_node);
				}
			if ((same_side == 0) && (nb_cut == 0) && (tri1 != 0) && (close_node1 == 0) && (close_side1 == 0) && (tri2 == 0) && (close_node2 == 0) && (close_side2 == 0))
				{
				//same_side= 0 nb_cut=0 case1 case2
				//nothing to do
				}
			if ((same_side == 0) && (nb_cut == 0) && (tri1 != 0) && (close_node1 == 0) && (close_side1 == 0) && (tri2 != 0) && (close_node2 != 0) && (close_side2 != 0))
				{
				//same_side= 0 nb_cut=0 case1 case3
				extremity1_node = case1(pa, tri1, extremity1_u, extremity1_v);
				extremity2_node = close_node2;					//printf("case1 case3 extremity1_node %4d extremity2_node %4d\n",extremity1_node,extremity2_node);			
				bar_creation2(pa, extremity1_node, extremity2_node, 0.0);
				}
			if ((same_side == 0) && (nb_cut == 0) && (tri1 != 0) && (close_node1 == 0) && (close_side1 == 0) && (tri2 == 0) && (close_node2 != 0) && (close_side2 != 0))
				{
				//same_side= 0 nb_cut=0 case1 case4
				extremity1_node = case1(pa, tri1, extremity1_u, extremity1_v);
				extremity2_node = close_node2;					//printf("case1 case4 extremity1_node %4d extremity2_node %4d\n",extremity1_node,extremity2_node);			
				bar_creation2(pa, extremity1_node, extremity2_node, 0.0);
				}
			if ((same_side == 0) && (nb_cut == 0) && (tri1 != 0) && (close_node1 == 0) && (close_side1 == 0) && (tri2 != 0) && (close_node2 == 0) && (close_side2 != 0))
				{
				//same_side= 0 nb_cut=0 case1 case5
				extremity1_node = case1(pa, tri1, extremity1_u, extremity1_v);
				ptu = extremity2_u;
				ptv = extremity2_v;
				extremity2_node = is_node_close_side(pa,  &ptu,  &ptv);		//printf("case1 case5 extremity1_node %4d extremity2_node %4d\n",extremity1_node,extremity2_node);			
				bar_creation2(pa, extremity1_node, extremity2_node, 0.0);
				}
			if ((same_side == 0) && (nb_cut == 0) && (tri1 != 0) && (close_node1 == 0) && (close_side1 == 0) && (tri2 == 0) && (close_node2 == 0) && (close_side2 != 0))
				{
				//same_side= 0 nb_cut=0 case1 case6
				extremity1_node = case1(pa, tri1, extremity1_u, extremity1_v);
				ptu = extremity2_u;
				ptv = extremity2_v;
				extremity2_node = is_node_close_side(pa,  &ptu,  &ptv);		//printf("case1 case6 extremity1_node %4d extremity2_node %4d\n",extremity1_node,extremity2_node);			
				bar_creation2(pa, extremity1_node, extremity2_node, 0.0);
				}
			if ((same_side == 0) && (nb_cut == 0) && (tri1 != 0) && (close_node1 == 0) && (close_side1 == 0) && (tri2 != 0) && (close_node2 != 0) && (close_side2 == 0))
				{
				//same_side= 0 nb_cut=0 case1 case9
				extremity1_node = case1(pa, tri1, extremity1_u, extremity1_v);
				extremity2_node = close_node2;					//printf("case1 case9 extremity1_node %4d extremity2_node %4d\n",extremity1_node,extremity2_node);			
				bar_creation2(pa, extremity1_node, extremity2_node, 0.0);
				}
			//CASE2
			if ((same_side == 0) && (nb_cut == 0) && (tri1 == 0) && (close_node1 == 0) && (close_side1 == 0) && (tri2 != 0) && (close_node2 == 0) && (close_side2 == 0))
				{
				//same_side= 0 nb_cut=0 case2 case1
				//nothing to do
				}
			if ((same_side == 0) && (nb_cut == 0) && (tri1 == 0) && (close_node1 == 0) && (close_side1 == 0) && (tri2 == 0) && (close_node2 == 0) && (close_side2 == 0))
				{
				//same_side= 0 nb_cut=0 case2 case2
				//nothing to do
				}
			if ((same_side == 0) && (nb_cut == 0) && (tri1 == 0) && (close_node1 == 0) && (close_side1 == 0) && (tri2 != 0) && (close_node2 != 0) && (close_side2 != 0))
				{
				//same_side= 0 nb_cut=0 case2 case3
				//nothing to do
				}
			if ((same_side == 0) && (nb_cut == 0) && (tri1 == 0) && (close_node1 == 0) && (close_side1 == 0) && (tri2 == 0) && (close_node2 != 0) && (close_side2 != 0))
				{
				//same_side= 0 nb_cut=0 case2 case4
				//nothing to do
				}
			if ((same_side == 0) && (nb_cut == 0) && (tri1 == 0) && (close_node1 == 0) && (close_side1 == 0) && (tri2 != 0) && (close_node2 == 0) && (close_side2 != 0))
				{
				//same_side= 0 nb_cut=0 case2 case5
				//nothing to do
				}
			if ((same_side == 0) && (nb_cut == 0) && (tri1 == 0) && (close_node1 == 0) && (close_side1 == 0) && (tri2 == 0) && (close_node2 == 0) && (close_side2 != 0))
				{
				//same_side= 0 nb_cut=0 case2 case6
				//nothing to do
				}
			if ((same_side == 0) && (nb_cut == 0) && (tri1 == 0) && (close_node1 == 0) && (close_side1 == 0) && (tri2 != 0) && (close_node2 != 0) && (close_side2 == 0))
				{
				//same_side= 0 nb_cut=0 case2 case9
				//nothing to do
				}
			//CASE3
			if ((same_side == 0) && (nb_cut == 0) && (tri1 != 0) && (close_node1 != 0) && (close_side1 != 0) && (tri2 != 0) && (close_node2 == 0) && (close_side2 == 0))
				{
				//same_side= 0 nb_cut=0 case3 case1
				extremity1_node = close_node1;								
				extremity2_node = case1(pa, tri2, extremity2_u, extremity2_v); 	//printf("case3 case1 extremity1_node %4d extremity2_node %4d\n",extremity1_node,extremity2_node);
				bar_creation2(pa, extremity1_node, extremity2_node, 0.0);
				}
			if ((same_side == 0) && (nb_cut == 0) && (tri1 != 0) && (close_node1 != 0) && (close_side1 != 0) && (tri2 == 0) && (close_node2 == 0) && (close_side2 == 0))
				{
				//same_side= 0 nb_cut=0 case3 case2
				//nothing to do
				}
			if ((same_side == 0) && (nb_cut == 0) && (tri1 != 0) && (close_node1 != 0) && (close_side1 != 0) && (tri2 != 0) && (close_node2 != 0) && (close_side2 != 0))
				{
				//same_side= 0 nb_cut=0 case3 case3
				//nothing to do
				extremity1_node = close_node1;								
				extremity2_node = close_node2;					//printf("case3 case3 extremity1_node %4d extremity2_node %4d\n",extremity1_node,extremity2_node);			
				bar_creation2(pa, extremity1_node, extremity2_node, 0.0);
				}
			if ((same_side == 0) && (nb_cut == 0) && (tri1 != 0) && (close_node1 != 0) && (close_side1 != 0) && (tri2 == 0) && (close_node2 != 0) && (close_side2 != 0))
				{
				//same_side= 0 nb_cut=0 case3 case4
				extremity1_node = close_node1;								
				extremity2_node = close_node2;					//printf("case3 case4 extremity1_node %4d extremity2_node %4d\n",extremity1_node,extremity2_node);			
				bar_creation2(pa, extremity1_node, extremity2_node, 0.0);
				}
			if ((same_side == 0) && (nb_cut == 0) && (tri1 != 0) && (close_node1 != 0) && (close_side1 != 0) && (tri2 != 0) && (close_node2 == 0) && (close_side2 != 0))
				{
				//same_side= 0 nb_cut=0 case3 case5
				extremity1_node = close_node1;								
				ptu = extremity2_u;
				ptv = extremity2_v;
				extremity2_node = is_node_close_side(pa,  &ptu,  &ptv);		//printf("case3 case5 extremity1_node %4d extremity2_node %4d\n",extremity1_node,extremity2_node);			
				bar_creation2(pa, extremity1_node, extremity2_node, 0.0);
				}
			if ((same_side == 0) && (nb_cut == 0) && (tri1 != 0) && (close_node1 != 0) && (close_side1 != 0) && (tri2 == 0) && (close_node2 == 0) && (close_side2 != 0))
				{
				//same_side= 0 nb_cut=0 case3 case6
				extremity1_node = close_node1;								
				ptu = extremity2_u;
				ptv = extremity2_v;
				extremity2_node = is_node_close_side(pa,  &ptu,  &ptv);		//printf("case3 case6 extremity1_node %4d extremity2_node %4d\n",extremity1_node,extremity2_node);			
				bar_creation2(pa, extremity1_node, extremity2_node, 0.0);
				}
			if ((same_side == 0) && (nb_cut == 0) && (tri1 != 0) && (close_node1 != 0) && (close_side1 != 0) && (tri2 != 0) && (close_node2 != 0) && (close_side2 == 0))
				{
				//same_side= 0 nb_cut=0 case3 case9
				extremity1_node = close_node1;								
				extremity2_node = close_node2;					//printf("case3 case9 extremity1_node %4d extremity2_node %4d\n",extremity1_node,extremity2_node);			
				bar_creation2(pa, extremity1_node, extremity2_node, 0.0);
				}
			//CASE4
			if ((same_side == 0) && (nb_cut == 0) && (tri1 == 0) && (close_node1 != 0) && (close_side1 != 0) && (tri2 != 0) && (close_node2 == 0) && (close_side2 == 0))
				{
				//same_side= 0 nb_cut=0 case4 case1
				extremity1_node = close_node1;								
				extremity2_node = case1(pa, tri2, extremity2_u, extremity2_v);	//printf("case4 case1 extremity1_node %4d extremity2_node %4d\n",extremity1_node,extremity2_node);			
				bar_creation2(pa, extremity1_node, extremity2_node, 0.0);
				}
			if ((same_side == 0) && (nb_cut == 0) && (tri1 == 0) && (close_node1 != 0) && (close_side1 != 0) && (tri2 == 0) && (close_node2 == 0) && (close_side2 == 0))
				{
				//same_side= 0 nb_cut=0 case4 case2
				//nothing to do
				}
			if ((same_side == 0) && (nb_cut == 0) && (tri1 == 0) && (close_node1 != 0) && (close_side1 != 0) && (tri2 != 0) && (close_node2 != 0) && (close_side2 != 0))
				{
				//same_side= 0 nb_cut=0 case4 case3
				extremity1_node = close_node1;								
				extremity2_node = close_node2;					//printf("case4 case3 extremity1_node %4d extremity2_node %4d\n",extremity1_node,extremity2_node);			
				bar_creation2(pa, extremity1_node, extremity2_node, 0.0);
				}
			if ((same_side == 0) && (nb_cut == 0) && (tri1 == 0) && (close_node1 != 0) && (close_side1 != 0) && (tri2 == 0) && (close_node2 != 0) && (close_side2 != 0))
				{
				//same_side= 0 nb_cut=0 case4 case4
				extremity1_node = close_node1;								
				extremity2_node = close_node2;					//printf("case4 case4 extremity1_node %4d extremity2_node %4d\n",extremity1_node,extremity2_node);			
				bar_creation2(pa, extremity1_node, extremity2_node, 0.0);
				}
			if ((same_side == 0) && (nb_cut == 0) && (tri1 == 0) && (close_node1 != 0) && (close_side1 != 0) && (tri2 != 0) && (close_node2 == 0) && (close_side2 != 0))
				{
				//same_side= 0 nb_cut=0 case4 case5
				extremity1_node = close_node1;								
				ptu = extremity2_u;
				ptv = extremity2_v;
				extremity2_node = is_node_close_side(pa,  &ptu,  &ptv);		//printf("case4 case5 extremity1_node %4d extremity2_node %4d\n",extremity1_node,extremity2_node);			
				bar_creation2(pa, extremity1_node, extremity2_node, 0.0);
				}
			if ((same_side == 0) && (nb_cut == 0) && (tri1 == 0) && (close_node1 != 0) && (close_side1 != 0) && (tri2 == 0) && (close_node2 == 0) && (close_side2 != 0))
				{
				//same_side= 0 nb_cut=0 case4 case6
				extremity1_node = close_node1;								
				ptu = extremity2_u;
				ptv = extremity2_v;
				extremity2_node = is_node_close_side(pa,  &ptu,  &ptv);		//printf("case4 case6 extremity1_node %4d extremity2_node %4d\n",extremity1_node,extremity2_node);			
				bar_creation2(pa, extremity1_node, extremity2_node, 0.0);
				}
			if ((same_side == 0) && (nb_cut == 0) && (tri1 == 0) && (close_node1 != 0) && (close_side1 != 0) && (tri2 != 0) && (close_node2 != 0) && (close_side2 == 0))
				{
				//same_side= 0 nb_cut=0 case4 case9
				extremity1_node = close_node1;								
				extremity2_node = close_node2;					//printf("case4 case9 extremity1_node %4d extremity2_node %4d\n",extremity1_node,extremity2_node);			
				bar_creation2(pa, extremity1_node, extremity2_node, 0.0);
				}
			//CASE5
			if ((same_side == 0) && (nb_cut == 0) && (tri1 != 0) && (close_node1 == 0) && (close_side1 != 0) && (tri2 != 0) && (close_node2 == 0) && (close_side2 == 0))
				{
				//same_side= 0 nb_cut=0 case5 case1
				ptu = extremity1_u;
				ptv = extremity1_v;
				extremity1_node = is_node_close_side(pa,  &ptu,  &ptv);					
				extremity2_node = case1(pa, tri2, extremity2_u, extremity2_v);	//printf("case5 case1 extremity1_node %4d extremity2_node %4d\n",extremity1_node,extremity2_node);			
				bar_creation2(pa, extremity1_node, extremity2_node, 0.0);
				}
			if ((same_side == 0) && (nb_cut == 0) && (tri1 != 0) && (close_node1 == 0) && (close_side1 != 0) && (tri2 == 0) && (close_node2 == 0) && (close_side2 == 0))
				{
				//same_side= 0 nb_cut=0 case5 case2
				//nothing to do
				}
			if ((same_side == 0) && (nb_cut == 0) && (tri1 != 0) && (close_node1 == 0) && (close_side1 != 0) && (tri2 != 0) && (close_node2 != 0) && (close_side2 != 0))
				{
				//same_side= 0 nb_cut=0 case5 case3
				ptu = extremity1_u;
				ptv = extremity1_v;
				extremity1_node = is_node_close_side(pa,  &ptu,  &ptv);					
				extremity2_node = close_node2;					//printf("case5 case3 extremity1_node %4d extremity2_node %4d\n",extremity1_node,extremity2_node);			
				bar_creation2(pa, extremity1_node, extremity2_node, 0.0);
				}
			if ((same_side == 0) && (nb_cut == 0) && (tri1 != 0) && (close_node1 == 0) && (close_side1 != 0) && (tri2 == 0) && (close_node2 != 0) && (close_side2 != 0))
				{
				//same_side= 0 nb_cut=0 case5 case4
				ptu = extremity1_u;
				ptv = extremity1_v;
				extremity1_node = is_node_close_side(pa,  &ptu,  &ptv);					
				extremity2_node = close_node2;					//printf("case5 case4 extremity1_node %4d extremity2_node %4d\n",extremity1_node,extremity2_node);			
				bar_creation2(pa, extremity1_node, extremity2_node, 0.0);
				}
			if ((same_side == 0) && (nb_cut == 0) && (tri1 != 0) && (close_node1 == 0) && (close_side1 != 0) && (tri2 != 0) && (close_node2 == 0) && (close_side2 != 0))
				{
				//same_side= 0 nb_cut=0 case5 case5
				ptu = extremity1_u;
				ptv = extremity1_v;
				extremity1_node = is_node_close_side(pa,  &ptu,  &ptv);					
				ptu = extremity2_u;
				ptv = extremity2_v;
				extremity2_node = is_node_close_side(pa,  &ptu,  &ptv);		//printf("case5 case5 extremity1_node %4d extremity2_node %4d\n",extremity1_node,extremity2_node);			
				bar_creation2(pa, extremity1_node, extremity2_node, 0.0);
				}
			if ((same_side == 0) && (nb_cut == 0) && (tri1 != 0) && (close_node1 == 0) && (close_side1 != 0) && (tri2 == 0) && (close_node2 == 0) && (close_side2 != 0))
				{
				//same_side= 0 nb_cut=0 case5 case6
				ptu = extremity1_u;
				ptv = extremity1_v;
				extremity1_node = is_node_close_side(pa,  &ptu,  &ptv);					
				ptu = extremity2_u;
				ptv = extremity2_v;
				extremity2_node = is_node_close_side(pa,  &ptu,  &ptv);		//printf("case5 case6 extremity1_node %4d extremity2_node %4d\n",extremity1_node,extremity2_node);			
				bar_creation2(pa, extremity1_node, extremity2_node, 0.0);
				}
			if ((same_side == 0) && (nb_cut == 0) && (tri1 != 0) && (close_node1 == 0) && (close_side1 != 0) && (tri2 != 0) && (close_node2 != 0) && (close_side2 == 0))
				{
				//same_side= 0 nb_cut=0 case5 case9
				ptu = extremity1_u;
				ptv = extremity1_v;
				extremity1_node = is_node_close_side(pa,  &ptu,  &ptv);					
				extremity2_node = close_node2;					//printf("case5 case9 extremity1_node %4d extremity2_node %4d\n",extremity1_node,extremity2_node);			
				bar_creation2(pa, extremity1_node, extremity2_node, 0.0);
				}
				
			//CASE6
			if ((same_side == 0) && (nb_cut == 0) && (tri1 == 0) && (close_node1 == 0) && (close_side1 != 0) && (tri2 != 0) && (close_node2 == 0) && (close_side2 == 0))
				{
				//same_side= 0 nb_cut=0 case6 case1
				ptu = extremity1_u;
				ptv = extremity1_v;
				extremity1_node = is_node_close_side(pa,  &ptu,  &ptv);					
				extremity2_node = case1(pa, tri2, extremity2_u, extremity2_v);	//printf("case6 case1 extremity1_node %4d extremity2_node %4d\n",extremity1_node,extremity2_node);
				bar_creation2(pa, extremity1_node, extremity2_node, 0.0);
				}
			if ((same_side == 0) && (nb_cut == 0) && (tri1 == 0) && (close_node1 == 0) && (close_side1 != 0) && (tri2 == 0) && (close_node2 == 0) && (close_side2 == 0))
				{
				//same_side= 0 nb_cut=0 case6 case2
				//nothing to do
				}
			if ((same_side == 0) && (nb_cut == 0) && (tri1 == 0) && (close_node1 == 0) && (close_side1 != 0) && (tri2 != 0) && (close_node2 != 0) && (close_side2 != 0))
				{
				//same_side= 0 nb_cut=0 case6 case3
				ptu = extremity1_u;
				ptv = extremity1_v;
				extremity1_node = is_node_close_side(pa,  &ptu,  &ptv);					
				extremity2_node = close_node2;					//printf("case6 case3 extremity1_node %4d extremity2_node %4d\n",extremity1_node,extremity2_node);			
				bar_creation2(pa, extremity1_node, extremity2_node, 0.0);
				}
			if ((same_side == 0) && (nb_cut == 0) && (tri1 == 0) && (close_node1 == 0) && (close_side1 != 0) && (tri2 == 0) && (close_node2 != 0) && (close_side2 != 0))
				{
				//same_side= 0 nb_cut=0 case6 case4
				ptu = extremity1_u;
				ptv = extremity1_v;
				extremity1_node = is_node_close_side(pa,  &ptu,  &ptv);					
				extremity2_node = close_node2;					//printf("case6 case4 extremity1_node %4d extremity2_node %4d\n",extremity1_node,extremity2_node);			
				bar_creation2(pa, extremity1_node, extremity2_node, 0.0);
				}
			if ((same_side == 0) && (nb_cut == 0) && (tri1 == 0) && (close_node1 == 0) && (close_side1 != 0) && (tri2 != 0) && (close_node2 == 0) && (close_side2 != 0))
				{
				//same_side= 0 nb_cut=0 case6 case5
				ptu = extremity1_u;
				ptv = extremity1_v;
				extremity1_node = is_node_close_side(pa,  &ptu,  &ptv);					
				ptu = extremity2_u;
				ptv = extremity2_v;
				extremity2_node = is_node_close_side(pa,  &ptu,  &ptv);		//printf("case6 case5 extremity1_node %4d extremity2_node %4d\n",extremity1_node,extremity2_node);			
				bar_creation2(pa, extremity1_node, extremity2_node, 0.0);
				}
			if ((same_side == 0) && (nb_cut == 0) && (tri1 == 0) && (close_node1 == 0) && (close_side1 != 0) && (tri2 == 0) && (close_node2 == 0) && (close_side2 != 0))
				{
				//same_side= 0 nb_cut=0 case6 case6
				ptu = extremity1_u;
				ptv = extremity1_v;
				extremity1_node = is_node_close_side(pa,  &ptu,  &ptv);					
				ptu = extremity2_u;
				ptv = extremity2_v;
				extremity2_node = is_node_close_side(pa,  &ptu,  &ptv);		//printf("case6 case6 extremity1_node %4d extremity2_node %4d\n",extremity1_node,extremity2_node);			
				bar_creation2(pa, extremity1_node, extremity2_node, 0.0);
				}
			if ((same_side == 0) && (nb_cut == 0) && (tri1 == 0) && (close_node1 == 0) && (close_side1 != 0) && (tri2 != 0) && (close_node2 != 0) && (close_side2 == 0))
				{
				//same_side= 0 nb_cut=0 case6 case9
				ptu = extremity1_u;
				ptv = extremity1_v;
				extremity1_node = is_node_close_side(pa,  &ptu,  &ptv);					
				extremity2_node = close_node2;					//printf("case6 case9 extremity1_node %4d extremity2_node %4d\n",extremity1_node,extremity2_node);			
				bar_creation2(pa, extremity1_node, extremity2_node, 0.0);
				}
			//CASE9
			if ((same_side == 0) && (nb_cut == 0) && (tri1 != 0) && (close_node1 != 0) && (close_side1 == 0) && (tri2 != 0) && (close_node2 == 0) && (close_side2 == 0))
				{
				//same_side= 0 nb_cut=0 case9 case1
				extremity1_node = close_node1;										
				extremity2_node = case1(pa, tri2, extremity2_u, extremity2_v);	//printf("case9 case1 extremity1_node %4d extremity2_node %4d\n",extremity1_node,extremity2_node);
				bar_creation2(pa, extremity1_node, extremity2_node, 0.0);
				}
			if ((same_side == 0) && (nb_cut == 0) && (tri1 != 0) && (close_node1 != 0) && (close_side1 == 0) && (tri2 == 0) && (close_node2 == 0) && (close_side2 == 0))
				{
				//same_side= 0 nb_cut=0 case9 case2
				//nothing to do
				}
			if ((same_side == 0) && (nb_cut == 0) && (tri1 != 0) && (close_node1 != 0) && (close_side1 == 0) && (tri2 != 0) && (close_node2 != 0) && (close_side2 != 0))
				{
				//same_side= 0 nb_cut=0 case9 case3
				extremity1_node = close_node1;								
				extremity2_node = close_node2;					//printf("case9 case3 extremity1_node %4d extremity2_node %4d\n",extremity1_node,extremity2_node);			
				bar_creation2(pa, extremity1_node, extremity2_node, 0.0);
				}
			if ((same_side == 0) && (nb_cut == 0) && (tri1 != 0) && (close_node1 != 0) && (close_side1 == 0) && (tri2 == 0) && (close_node2 != 0) && (close_side2 != 0))
				{
				//same_side= 0 nb_cut=0 case9 case4
				extremity1_node = close_node1;					
				extremity2_node = close_node2;					//printf("case9 case4 extremity1_node %4d extremity2_node %4d\n",extremity1_node,extremity2_node);			
				bar_creation2(pa, extremity1_node, extremity2_node, 0.0);
				}
			if ((same_side == 0) && (nb_cut == 0) && (tri1 != 0) && (close_node1 != 0) && (close_side1 == 0) && (tri2 != 0) && (close_node2 == 0) && (close_side2 != 0))
				{
				//same_side= 0 nb_cut=0 case9 case5
				extremity1_node = close_node1;								
				ptu = extremity2_u;
				ptv = extremity2_v;
				extremity2_node = is_node_close_side(pa,  &ptu,  &ptv);		//printf("case9 case5 extremity1_node %4d extremity2_node %4d\n",extremity1_node,extremity2_node);			
				bar_creation2(pa, extremity1_node, extremity2_node, 0.0);
				}
			if ((same_side == 0) && (nb_cut == 0) && (tri1 != 0) && (close_node1 != 0) && (close_side1 == 0) && (tri2 == 0) && (close_node2 == 0) && (close_side2 != 0))
				{
				//same_side= 0 nb_cut=0 case9 case6
				extremity1_node = close_node1;							
				ptu = extremity2_u;
				ptv = extremity2_v;
				extremity2_node = is_node_close_side(pa,  &ptu,  &ptv);		//printf("case9 case6 extremity1_node %4d extremity2_node %4d\n",extremity1_node,extremity2_node);			
				bar_creation2(pa, extremity1_node, extremity2_node, 0.0);
				}
			if ((same_side == 0) && (nb_cut == 0) && (tri1 != 0) && (close_node1 != 0) && (close_side1 == 0) && (tri2 != 0) && (close_node2 != 0) && (close_side2 == 0))
				{
				//same_side= 0 nb_cut=0 case9 case9
				extremity1_node = close_node1;								
				extremity2_node = close_node2;					//printf("case9 case9 extremity1_node %4d extremity2_node %4d\n",extremity1_node,extremity2_node);			
				bar_creation2(pa, extremity1_node, extremity2_node, 0.0);
				}


			//nb_cut = 1
			//CASE1
			if ((same_side == 0) && (nb_cut == 1) && (tri1 != 0) && (close_node1 == 0) && (close_side1 == 0) && (tri2 != 0) && (close_node2 == 0) && (close_side2 == 0))
				{
				//same_side= 0 nb_cut=1 case1 case1
				//nothing to do
				}
			if ((same_side == 0) && (nb_cut == 1) && (tri1 != 0) && (close_node1 == 0) && (close_side1 == 0) && (tri2 == 0) && (close_node2 == 0) && (close_side2 == 0))
				{
				//same_side= 0 nb_cut=1 case1 case2
				extremity1_node = case1(pa, tri1, extremity1_u, extremity1_v);	
				extremity2_node = case2(pa, cut_side[nb_cut], cut_beta[nb_cut], &extremity2_u, &extremity2_v);	//printf("base1 case2 extremity1_node %4d extremity2_node %4d\n",extremity1_node,extremity2_node);
				bar_creation2(pa, extremity1_node, extremity2_node, 1.0-cut_alpha[nb_cut]);				
				}
			if ((same_side == 0) && (nb_cut == 1) && (tri1 != 0) && (close_node1 == 0) && (close_side1 == 0) && (tri2 != 0) && (close_node2 != 0) && (close_side2 != 0))
				{
				//same_side= 0 nb_cut=1 case1 case3
				//nothing to do
				}
			if ((same_side == 0) && (nb_cut == 1) && (tri1 != 0) && (close_node1 == 0) && (close_side1 == 0) && (tri2 == 0) && (close_node2 != 0) && (close_side2 != 0))
				{
				//same_side= 0 nb_cut=1 case1 case4
				//nothing to do
				}
			if ((same_side == 0) && (nb_cut == 1) && (tri1 != 0) && (close_node1 == 0) && (close_side1 == 0) && (tri2 != 0) && (close_node2 == 0) && (close_side2 != 0))
				{
				//same_side= 0 nb_cut=1 case1 case5
				//nothing to do
				}
			if ((same_side == 0) && (nb_cut == 1) && (tri1 != 0) && (close_node1 == 0) && (close_side1 == 0) && (tri2 == 0) && (close_node2 == 0) && (close_side2 != 0))
				{
				//same_side= 0 nb_cut=1 case1 case6
				//nothing to do
				}
			if ((same_side == 0) && (nb_cut == 1) && (tri1 != 0) && (close_node1 == 0) && (close_side1 == 0) && (tri2 != 0) && (close_node2 != 0) && (close_side2 == 0))
				{
				//same_side= 0 nb_cut=1 case1 case9
				//nothing to do
				}
			//CASE2
			if ((same_side == 0) && (nb_cut == 1) && (tri1 == 0) && (close_node1 == 0) && (close_side1 == 0) && (tri2 != 0) && (close_node2 == 0) && (close_side2 == 0))
				{
				//same_side= 0 nb_cut=1 case2 case1
				extremity1_node = case2(pa, cut_side[nb_cut], cut_beta[nb_cut], &extremity1_u, &extremity1_v);	
				extremity2_node = case1(pa, tri2, extremity2_u, extremity2_v);	
				bar_creation2(pa, extremity1_node, extremity2_node, cut_alpha[nb_cut]);				//printf("base2 case1 extremity1_node %4d extremity2_node %4d\n",extremity1_node,extremity2_node);		
				}
			if ((same_side == 0) && (nb_cut == 1) && (tri1 == 0) && (close_node1 == 0) && (close_side1 == 0) && (tri2 == 0) && (close_node2 == 0) && (close_side2 == 0))
				{
				//same_side= 0 nb_cut=1 case2 case2
				//nothing to do
				}
			if ((same_side == 0) && (nb_cut == 1) && (tri1 == 0) && (close_node1 == 0) && (close_side1 == 0) && (tri2 != 0) && (close_node2 != 0) && (close_side2 != 0) && (is_node_close_side2(pa, cut_side[nb_cut], extremity2_u, extremity2_v) != 1))
				{
				//same_side= 0 nb_cut=1 case2 case3
				extremity1_node = case2(pa, cut_side[nb_cut], cut_beta[nb_cut], &extremity1_u, &extremity1_v);
				extremity2_node = close_node2;									//printf("base2 case3 extremity1_node %4d extremity2_node %4d\n",extremity1_node,extremity2_node);			
				bar_creation2(pa, extremity1_node, extremity2_node, cut_alpha[nb_cut]);				
				}
			if ((same_side == 0) && (nb_cut == 1) && (tri1 == 0) && (close_node1 == 0) && (close_side1 == 0) && (tri2 == 0) && (close_node2 != 0) && (close_side2 != 0))
				{
				//same_side= 0 nb_cut=1 case2 case4
				extremity1_node = case2(pa, cut_side[nb_cut], cut_beta[nb_cut], &extremity1_u, &extremity1_v);
				extremity2_node = close_node2;									//printf("base2 case4 extremity1_node %4d extremity2_node %4d\n",extremity1_node,extremity2_node);			
				bar_creation2(pa, extremity1_node, extremity2_node, cut_alpha[nb_cut]);				
				}
			if ((same_side == 0) && (nb_cut == 1) && (tri1 == 0) && (close_node1 == 0) && (close_side1 == 0) && (tri2 != 0) && (close_node2 == 0) && (close_side2 != 0) && (is_node_close_side2(pa, cut_side[nb_cut], extremity2_u, extremity2_v) != 1))
				{
				//same_side= 0 nb_cut=1 case2 case5
				extremity1_node = case2(pa, cut_side[nb_cut], cut_beta[nb_cut], &extremity1_u, &extremity1_v);
				ptu = extremity2_u;
				ptv = extremity2_v;
				extremity2_node = is_node_close_side(pa,  &ptu,  &ptv);						//printf("base2 case5 extremity1_node %4d extremity2_node %4d\n",extremity1_node,extremity2_node);			
				bar_creation2(pa, extremity1_node, extremity2_node, cut_alpha[nb_cut]);				
				}
			if ((same_side == 0) && (nb_cut == 1) && (tri1 == 0) && (close_node1 == 0) && (close_side1 == 0) && (tri2 == 0) && (close_node2 == 0) && (close_side2 != 0))
				{
				//same_side= 0 nb_cut=1 case2 case6
				extremity1_node = case2(pa, cut_side[nb_cut], cut_beta[nb_cut], &extremity1_u, &extremity1_v);
				ptu = extremity2_u;
				ptv = extremity2_v;
				extremity2_node = is_node_close_side(pa,  &ptu,  &ptv);						//printf("base2 case6 extremity1_node %4d extremity2_node %4d\n",extremity1_node,extremity2_node);			
				bar_creation2(pa, extremity1_node, extremity2_node, cut_alpha[nb_cut]);				
				}
			if ((same_side == 0) && (nb_cut == 1) && (tri1 == 0) && (close_node1 == 0) && (close_side1 == 0) && (tri2 != 0) && (close_node2 != 0) && (close_side2 == 0))
				{
				//same_side= 0 nb_cut=1 case2 case9
				extremity1_node = case2(pa, cut_side[nb_cut], cut_beta[nb_cut], &extremity1_u, &extremity1_v);
				extremity2_node = close_node2;									//printf("base9 case9 extremity1_node %4d extremity2_node %4d\n",extremity1_node,extremity2_node);			
				bar_creation2(pa, extremity1_node, extremity2_node, cut_alpha[nb_cut]);				
				}
			//CASE3
			if ((same_side == 0) && (nb_cut == 1) && (tri1 != 0) && (close_node1 != 0) && (close_side1 != 0) && (tri2 != 0) && (close_node2 == 0) && (close_side2 == 0))
				{
				//same_side= 0 nb_cut=1 case3 case1
				//nothing to do
				}
			if ((same_side == 0) && (nb_cut == 1) && (tri1 != 0) && (close_node1 != 0) && (close_side1 != 0) && (tri2 == 0) && (close_node2 == 0) && (close_side2 == 0) && (is_node_close_side2(pa, cut_side[nb_cut], extremity1_u, extremity1_v) != 1))
				{
				//same_side= 0 nb_cut=1 case3 case2
				extremity1_node = close_node1;									
				extremity2_node = case2(pa, cut_side[nb_cut], cut_beta[nb_cut], &extremity2_u, &extremity2_v);	//printf("base3 case2 extremity1_node %4d extremity2_node %4d\n",extremity1_node,extremity2_node);
				bar_creation2(pa, extremity1_node, extremity2_node, 1.0-cut_alpha[nb_cut]);				
				}
			if ((same_side == 0) && (nb_cut == 1) && (tri1 != 0) && (close_node1 != 0) && (close_side1 != 0) && (tri2 != 0) && (close_node2 != 0) && (close_side2 != 0))
				{
				//same_side= 0 nb_cut=1 case3 case3
				//nothing to do
				}
			if ((same_side == 0) && (nb_cut == 1) && (tri1 != 0) && (close_node1 != 0) && (close_side1 != 0) && (tri2 == 0) && (close_node2 != 0) && (close_side2 != 0))
				{
				//same_side= 0 nb_cut=1 case3 case4
				extremity1_node = close_node1;									
				extremity2_node = close_node2;									//printf("base3 case4 extremity1_node %4d extremity2_node %4d\n",extremity1_node,extremity2_node);			
				bar_creation2(pa, extremity1_node, extremity2_node, 0.0);				
				}
			if ((same_side == 0) && (nb_cut == 1) && (tri1 != 0) && (close_node1 != 0) && (close_side1 != 0) && (tri2 != 0) && (close_node2 == 0) && (close_side2 != 0))
				{
				//same_side= 0 nb_cut=1 case3 case5
				//nothing to do
				}
			if ((same_side == 0) && (nb_cut == 1) && (tri1 != 0) && (close_node1 != 0) && (close_side1 != 0) && (tri2 == 0) && (close_node2 == 0) && (close_side2 != 0))
				{
				//same_side= 0 nb_cut=1 case3 case6
				extremity1_node = close_node1;								
				ptu = extremity2_u;
				ptv = extremity2_v;
				extremity2_node = is_node_close_side(pa,  &ptu,  &ptv);						//printf("base3 case6 extremity1_node %4d extremity2_node %4d\n",extremity1_node,extremity2_node);			
				bar_creation2(pa, extremity1_node, extremity2_node, 0.0);				
				}
			if ((same_side == 0) && (nb_cut == 1) && (tri1 != 0) && (close_node1 != 0) && (close_side1 != 0) && (tri2 != 0) && (close_node2 != 0) && (close_side2 == 0))
				{
				//same_side= 0 nb_cut=1 case3 case9
				//nothing to do
				}
			//CASE4
			if ((same_side == 0) && (nb_cut == 1) && (tri1 == 0) && (close_node1 != 0) && (close_side1 != 0) && (tri2 != 0) && (close_node2 == 0) && (close_side2 == 0))
				{
				//same_side= 0 nb_cut=1 case4 case1
				extremity1_node = close_node1;								
				extremity2_node = case1(pa, tri2, extremity2_u, extremity2_v);					//printf("base4 case1 extremity1_node %4d extremity2_node %4d\n",extremity1_node,extremity2_node);
				bar_creation2(pa, extremity1_node, extremity2_node, 0.0);				
				}
			if ((same_side == 0) && (nb_cut == 1) && (tri1 == 0) && (close_node1 != 0) && (close_side1 != 0) && (tri2 == 0) && (close_node2 == 0) && (close_side2 == 0))
				{
				//same_side= 0 nb_cut=1 case4 case2
				//nothing to do
				}
			if ((same_side == 0) && (nb_cut == 1) && (tri1 == 0) && (close_node1 != 0) && (close_side1 != 0) && (tri2 != 0) && (close_node2 != 0) && (close_side2 != 0))
				{
				//same_side= 0 nb_cut=1 case4 case3
				extremity1_node = close_node1;								
				extremity2_node = close_node2;									//printf("base4 case3 extremity1_node %4d extremity2_node %4d\n",extremity1_node,extremity2_node);			
				bar_creation2(pa, extremity1_node, extremity2_node, 0.0);				
				}
			if ((same_side == 0) && (nb_cut == 1) && (tri1 == 0) && (close_node1 != 0) && (close_side1 != 0) && (tri2 == 0) && (close_node2 != 0) && (close_side2 != 0))
				{
				//same_side= 0 nb_cut=1 case4 case4
				//nothing to do
				}
			if ((same_side == 0) && (nb_cut == 1) && (tri1 == 0) && (close_node1 != 0) && (close_side1 != 0) && (tri2 != 0) && (close_node2 == 0) && (close_side2 != 0))
				{
				//same_side= 0 nb_cut=1 case4 case5
				extremity1_node = close_node1;								
				ptu = extremity2_u;
				ptv = extremity2_v;
				extremity2_node = is_node_close_side(pa,  &ptu,  &ptv);						//printf("base2 case5 extremity1_node %4d extremity2_node %4d\n",extremity1_node,extremity2_node);			
				bar_creation2(pa, extremity1_node, extremity2_node, 0.0);				
				}
			if ((same_side == 0) && (nb_cut == 1) && (tri1 == 0) && (close_node1 != 0) && (close_side1 != 0) && (tri2 == 0) && (close_node2 == 0) && (close_side2 != 0))
				{
				//same_side= 0 nb_cut=1 case4 case6
				//nothing to do
				}
			if ((same_side == 0) && (nb_cut == 1) && (tri1 == 0) && (close_node1 != 0) && (close_side1 != 0) && (tri2 != 0) && (close_node2 != 0) && (close_side2 == 0))
				{
				//same_side= 0 nb_cut=1 case4 case9
				extremity1_node = close_node1;								
				extremity2_node = close_node2;									//printf("base9 case9 extremity1_node %4d extremity2_node %4d\n",extremity1_node,extremity2_node);			
				bar_creation2(pa, extremity1_node, extremity2_node, 0.0);				
				}
			//CASE5
			if ((same_side == 0) && (nb_cut == 1) && (tri1 != 0) && (close_node1 == 0) && (close_side1 != 0) && (tri2 != 0) && (close_node2 == 0) && (close_side2 == 0))
				{
				//same_side= 0 nb_cut=1 case5 case1
				//nothing to do
				}
			if ((same_side == 0) && (nb_cut == 1) && (tri1 != 0) && (close_node1 == 0) && (close_side1 != 0) && (tri2 == 0) && (close_node2 == 0) && (close_side2 == 0) && (is_node_close_side2(pa, cut_side[nb_cut], extremity1_u, extremity1_v) != 1))
				{
				//same_side= 0 nb_cut=1 case5 case2
				ptu = extremity1_u;
				ptv = extremity1_v;
				extremity1_node = is_node_close_side(pa,  &ptu,  &ptv);					
				extremity2_node = case2(pa, cut_side[nb_cut], cut_beta[nb_cut], &extremity2_u, &extremity2_v);	//printf("base5 case2 extremity1_node %4d extremity2_node %4d\n",extremity1_node,extremity2_node);
				bar_creation2(pa, extremity1_node, extremity2_node, 1.0-cut_alpha[nb_cut]);				
				}
			if ((same_side == 0) && (nb_cut == 1) && (tri1 != 0) && (close_node1 == 0) && (close_side1 != 0) && (tri2 != 0) && (close_node2 != 0) && (close_side2 != 0))
				{
				//same_side= 0 nb_cut=1 case5 case3
				//nothing to do
				}
			if ((same_side == 0) && (nb_cut == 1) && (tri1 != 0) && (close_node1 == 0) && (close_side1 != 0) && (tri2 == 0) && (close_node2 != 0) && (close_side2 != 0))
				{
				//same_side= 0 nb_cut=1 case5 case4
				ptu = extremity1_u;
				ptv = extremity1_v;
				extremity1_node = is_node_close_side(pa,  &ptu,  &ptv);					
				extremity2_node = close_node2;									//printf("base4 case3 extremity1_node %4d extremity2_node %4d\n",extremity1_node,extremity2_node);			
				bar_creation2(pa, extremity1_node, extremity2_node, 0.0);				
				}
			if ((same_side == 0) && (nb_cut == 1) && (tri1 != 0) && (close_node1 == 0) && (close_side1 != 0) && (tri2 != 0) && (close_node2 == 0) && (close_side2 != 0))
				{
				//same_side= 0 nb_cut=1 case5 case5
				//nothing to do
				}
			if ((same_side == 0) && (nb_cut == 1) && (tri1 != 0) && (close_node1 == 0) && (close_side1 != 0) && (tri2 == 0) && (close_node2 == 0) && (close_side2 != 0))
				{
				//same_side= 0 nb_cut=1 case5 case6
				ptu = extremity1_u;
				ptv = extremity1_v;
				extremity1_node = is_node_close_side(pa,  &ptu,  &ptv);						
				ptu = extremity2_u;
				ptv = extremity2_v;
				extremity2_node = is_node_close_side(pa,  &ptu,  &ptv);						//printf("base5 case6 extremity1_node %4d extremity2_node %4d\n",extremity1_node,extremity2_node);			
				}
			if ((same_side == 0) && (nb_cut == 1) && (tri1 != 0) && (close_node1 == 0) && (close_side1 != 0) && (tri2 != 0) && (close_node2 != 0) && (close_side2 == 0))
				{
				//same_side= 0 nb_cut=1 case5 case9
				//nothing to do
				}
				
			//CASE6
			if ((same_side == 0) && (nb_cut == 1) && (tri1 == 0) && (close_node1 == 0) && (close_side1 != 0) && (tri2 != 0) && (close_node2 == 0) && (close_side2 == 0))
				{
				//same_side= 0 nb_cut=1 case6 case1
				ptu = extremity1_u;
				ptv = extremity1_v;
				extremity1_node = is_node_close_side(pa,  &ptu,  &ptv);						
				extremity2_node = case1(pa, tri2, extremity2_u, extremity2_v);					//printf("base6 case1 extremity1_node %4d extremity2_node %4d\n",extremity1_node,extremity2_node);
				bar_creation2(pa, extremity1_node, extremity2_node, 0.0);				
				}
			if ((same_side == 0) && (nb_cut == 1) && (tri1 == 0) && (close_node1 == 0) && (close_side1 != 0) && (tri2 == 0) && (close_node2 == 0) && (close_side2 == 0))
				{
				//same_side= 0 nb_cut=1 case6 case2
				//nothing to do
				}
			if ((same_side == 0) && (nb_cut == 1) && (tri1 == 0) && (close_node1 == 0) && (close_side1 != 0) && (tri2 != 0) && (close_node2 != 0) && (close_side2 != 0))
				{
				//same_side= 0 nb_cut=1 case6 case3
				ptu = extremity1_u;
				ptv = extremity1_v;
				extremity1_node = is_node_close_side(pa,  &ptu,  &ptv);						
				extremity2_node = close_node2;									//printf("base6 case3 extremity1_node %4d extremity2_node %4d\n",extremity1_node,extremity2_node);			
				bar_creation2(pa, extremity1_node, extremity2_node, 0.0);				
				}
			if ((same_side == 0) && (nb_cut == 1) && (tri1 == 0) && (close_node1 == 0) && (close_side1 != 0) && (tri2 == 0) && (close_node2 != 0) && (close_side2 != 0))
				{
				//same_side= 0 nb_cut=1 case6 case4
				//nothing to do
				}
			if ((same_side == 0) && (nb_cut == 1) && (tri1 == 0) && (close_node1 == 0) && (close_side1 != 0) && (tri2 != 0) && (close_node2 == 0) && (close_side2 != 0))
				{
				//same_side= 0 nb_cut=1 case6 case5
				ptu = extremity1_u;
				ptv = extremity1_v;
				extremity1_node = is_node_close_side(pa,  &ptu,  &ptv);						
				ptu = extremity2_u;
				ptv = extremity2_v;
				extremity2_node = is_node_close_side(pa,  &ptu,  &ptv);						//printf("base6 case5 extremity1_node %4d extremity2_node %4d\n",extremity1_node,extremity2_node);			
				bar_creation2(pa, extremity1_node, extremity2_node, 0.0);				
				}
			if ((same_side == 0) && (nb_cut == 1) && (tri1 == 0) && (close_node1 == 0) && (close_side1 != 0) && (tri2 == 0) && (close_node2 == 0) && (close_side2 != 0))
				{
				//same_side= 0 nb_cut=1 case6 case6
				//nothing to do
				}
			if ((same_side == 0) && (nb_cut == 1) && (tri1 == 0) && (close_node1 == 0) && (close_side1 != 0) && (tri2 != 0) && (close_node2 != 0) && (close_side2 == 0))
				{
				//same_side= 0 nb_cut=1 case6 case9
				ptu = extremity1_u;
				ptv = extremity1_v;
				extremity1_node = is_node_close_side(pa,  &ptu,  &ptv);						
				extremity2_node = close_node2;									//printf("base6 case9 extremity1_node %4d extremity2_node %4d\n",extremity1_node,extremity2_node);			
				bar_creation2(pa, extremity1_node, extremity2_node, 0.0);				
				}
			//CASE9
			if ((same_side == 0) && (nb_cut == 1) && (tri1 != 0) && (close_node1 != 0) && (close_side1 == 0) && (tri2 != 0) && (close_node2 == 0) && (close_side2 == 0))
				{
				//same_side= 0 nb_cut=1 case9 case1
				//nothing to do
				}
			if ((same_side == 0) && (nb_cut == 1) && (tri1 != 0) && (close_node1 != 0) && (close_side1 == 0) && (tri2 == 0) && (close_node2 == 0) && (close_side2 == 0))
				{
				//same_side= 0 nb_cut=1 case9 case2
				extremity1_node = close_node1;									
				extremity2_node = case2(pa, cut_side[nb_cut], cut_beta[nb_cut], &extremity2_u, &extremity2_v);	//printf("base9 case2 extremity1_node %4d extremity2_node %4d\n",extremity1_node,extremity2_node);
				bar_creation2(pa, extremity1_node, extremity2_node, 1.0-cut_alpha[nb_cut]);				
				}
			if ((same_side == 0) && (nb_cut == 1) && (tri1 != 0) && (close_node1 != 0) && (close_side1 == 0) && (tri2 != 0) && (close_node2 != 0) && (close_side2 != 0))
				{
				//same_side= 0 nb_cut=1 case9 case3
				//nothing to do
				}
			if ((same_side == 0) && (nb_cut == 1) && (tri1 != 0) && (close_node1 != 0) && (close_side1 == 0) && (tri2 == 0) && (close_node2 != 0) && (close_side2 != 0))
				{
				//same_side= 0 nb_cut=1 case9 case4
				extremity1_node = close_node1;									
				extremity2_node = close_node2;									//printf("base9 case4 extremity1_node %4d extremity2_node %4d\n",extremity1_node,extremity2_node);			
				bar_creation2(pa, extremity1_node, extremity2_node, 0.0);				
				}
			if ((same_side == 0) && (nb_cut == 1) && (tri1 != 0) && (close_node1 != 0) && (close_side1 == 0) && (tri2 != 0) && (close_node2 == 0) && (close_side2 != 0))
				{
				//same_side= 0 nb_cut=1 case9 case5
				//nothing to do
				}
			if ((same_side == 0) && (nb_cut == 1) && (tri1 != 0) && (close_node1 != 0) && (close_side1 == 0) && (tri2 == 0) && (close_node2 == 0) && (close_side2 != 0))
				{
				//same_side= 0 nb_cut=1 case9 case6
				extremity1_node = close_node1;									
				ptu = extremity2_u;
				ptv = extremity2_v;
				extremity2_node = is_node_close_side(pa,  &ptu,  &ptv);						//printf("base6 case5 extremity1_node %4d extremity2_node %4d\n",extremity1_node,extremity2_node);			
				bar_creation2(pa, extremity1_node, extremity2_node, 0.0);				
				}
			if ((same_side == 0) && (nb_cut == 1) && (tri1 != 0) && (close_node1 != 0) && (close_side1 == 0) && (tri2 != 0) && (close_node2 != 0) && (close_side2 == 0))
				{
				//same_side= 0 nb_cut=1 case9 case9
				//nothing to do
				}
			}
		}
	////////////////////end of the loop on u	/////////////////////////////////////////////////////////////////////



	sorting_node_per_element_around_panel(pa);
	bar_creation_per_element_around_panel(pa);
	}

