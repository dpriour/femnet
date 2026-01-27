#define PRINCIPAL 0
#include "phobos.h"

	
int verification_ropes_around_panel2(int pa)
	{
	int no,deb_panel,fin_panel,trouve,trouve_total,link1,link2,li,obj;
	int obj1,obj2;
	
	//////////////////beginning of verification that there are ropes all around this panel of netting//////////////////////////////////////////////
	trouve_total = 0;	//there are cables all around the panel	
	for (no=1;no<=panneau[pa].nb_noeud_contour;no++)
		{
		//beginning of verification that there are ropes all around this panel of netting
		deb_panel = no;
		if (no == panneau[pa].nb_noeud_contour)	fin_panel = 1;
		else					fin_panel = no+1;
		//printf("deb_panel %d fin_panel %d  ",deb_panel,fin_panel);	
		trouve = 0;	//there is no cable linked to this side of the panel	
		link1 = 0;	
		link2 = 0;	
		for (li=1;li<=Structure.nb_liaison;li++)
			{
			for (obj=1;obj<=Lien[li].nb_liaison;obj++)
				{
				//printf("li %d obj %d type %c struct %d extre %d\n",li,obj,Lien[li].type[obj],Lien[li].structure[obj],Lien[li].extremite[obj] );			
				if ((Lien[li].type[obj] == 'p') && (Lien[li].structure[obj] == pa) && (Lien[li].extremite[obj] == deb_panel))	link1 = li;
				}
			}
		for (li=1;li<=Structure.nb_liaison;li++)
			{
			for (obj=1;obj<=Lien[li].nb_liaison;obj++)
				{
				//printf("li %d obj %d type %c struct %d extre %d\n",li,obj,Lien[li].type[obj],Lien[li].structure[obj],Lien[li].extremite[obj] );			
				if ((Lien[li].type[obj] == 'p') && (Lien[li].structure[obj] == pa) && (Lien[li].extremite[obj] == fin_panel))	link2 = li;
				}
			}
		//printf("link1 %4d link2 %4d  ",link1,link2);			
		for (obj1=1;obj1<=Lien[link1].nb_liaison;obj1++)
			{
			if (Lien[link1].type[obj1] == 'e')
				{
				//printf("typ1 %c struct %4d extr %4d \n",Lien[link1].type[obj1],Lien[link1].structure[obj1],Lien[link1].extremite[obj1]);			
				for (obj2=1;obj2<=Lien[link2].nb_liaison;obj2++)
					{
					if (Lien[link2].type[obj2] == 'e')
						{
						//printf("typ2 %c struct %4d extr %4d \n",Lien[link2].type[obj2],Lien[link2].structure[obj2],Lien[link2].extremite[obj2]);			
						if ((Lien[link1].structure[obj1] == Lien[link2].structure[obj2]) && (Lien[link1].extremite[obj1] != Lien[link2].extremite[obj2]))
							{
							trouve = Lien[link1].structure[obj1];
							//printf("trouvf %d\n",trouve);			
							}
						}
					}
				}
			}			
		//printf("linked cable %d\n",trouve);	
		if (trouve == 0)	trouve_total = no;	
		}
	return trouve_total;
	////////////////////////end of verification that there are ropes all around this panel of netting/////////////////////////////////////
	}

void create_side2cable(int pa)
	{
	int no,el,corner1,corner2,sens;
	
	
	for (el=1;el<=Structure.NbTypeelem;el++)
		{
		sens = 0;
		//int sewn_diamond_panel2cable2(int cable, int panel, int *corner1, int *corner2)
		//return 1 if the cable n° cable is sewn to the diamond panel n° panel. 
		//corner1 is linked to extremity 1 of the cable.
		//corner2 is linked to extremity 2 of the cable.
		if (sewn_diamond_panel2cable2(el, pa, &corner1, &corner2))
			{
			if (corner1 == panneau[pa].nb_noeud_contour)
				{
				if (corner2 == 1)	sens = 1;
				else			sens = -1;
				}
			else
				{
				if (corner2 == corner1+1)	sens = 1;
				else				sens = -1;
				}
			if (sens == 0)
				{
				printf("pb at create_side2cable between panel %d and cable %d corner1 %d corner2 %d\n", pa,el,corner1,corner2);
				exit(0);
				}
			else
				{
				if (sens == 1)
					{
					element[el].cable2side = corner1;
					panneau[pa].side2cable[corner1] = el;
					//printf("panel %d and cable %d corner1 %d corner2 %d\n", pa,el,corner1,corner2);
					}
				else
					{
					element[el].cable2side = -corner2;
					panneau[pa].side2cable[corner2] = -el;
					//printf("panem %d and cable %d corner1 %d corner2 %d\n", pa,el,corner1,corner2);
					}
				}		
			}
		}
	}




void first_node_created(int pa)
	{
	int no,co,sewn,deb,fin,trouve,el;
	double corner1_u,corner1_v,corner2_u,corner2_v;
	
	////////////////////////beginning of the list of nodes already created around the panel pa/////////////////////////////////////////
	Structure.nb_node_panel2ropes = 0;
	//list of nodes a the panel pa/////////////////////////////////////////
	for (co=1;co<=panneau[pa].nb_noeud_contour;co++)
		{
		Structure.nb_node_panel2ropes++;
		node_panel2ropes.U[Structure.nb_node_panel2ropes] = noeud[panneau[pa].noeud_contour[co]].u;
		node_panel2ropes.V[Structure.nb_node_panel2ropes] = noeud[panneau[pa].noeud_contour[co]].v;
		el = panneau[pa].side2cable[co];
		if (el > 0) 	node_panel2ropes.numero_total[Structure.nb_node_panel2ropes] = element[ el].extremite[1];
		else  		node_panel2ropes.numero_total[Structure.nb_node_panel2ropes] = element[-el].extremite[2];
		node_panel2ropes.side[Structure.nb_node_panel2ropes] = co;
		if (el > 0) 	node_panel2ropes.cable[Structure.nb_node_panel2ropes] = el;
		else	 	node_panel2ropes.cable[Structure.nb_node_panel2ropes] = -el;
		if (el > 0) 	node_panel2ropes.sens[Structure.nb_node_panel2ropes] =  1;
		else	 	
			{
			node_panel2ropes.sens[Structure.nb_node_panel2ropes] = -1;
			//printf("node_panel2ropes.sens[%d] =  %d\n",Structure.nb_node_panel2ropes ,node_panel2ropes.sens[Structure.nb_node_panel2ropes] );
			}
		if (el > 0)	node_panel2ropes.prop_cable[Structure.nb_node_panel2ropes] = 0.0;
		else		node_panel2ropes.prop_cable[Structure.nb_node_panel2ropes] = 1.0;
		}
	//////////////////////////////////////end of list of nodes already created around the panel pa/////////////////////////////////////////
	}
		
int is_node_close_side(int pan, double *extrem_u, double *extrem_v)
	{
	int no,co,deb_panel,fin_panel,corner1,corner2,extrem_node,sens;
	double node_u,node_v,side1_u,side1_v,side2_u,side2_v,dalpha,dbeta,dalpha_ok;
	
	extrem_node = 0;
	//printf("pan %3d *extrem_u %6.2lf *extrem_v %6.2lf\n",pan,*extrem_u,*extrem_v);	
	for (co=1;co<=panneau[pan].nb_noeud_contour;co++)
		{
		deb_panel = co;
		if (co == panneau[pan].nb_noeud_contour)	fin_panel = 1;
		else						fin_panel = co+1;
		side1_u = noeud[panneau[pan].noeud_contour[deb_panel]].u;
		side1_v = noeud[panneau[pan].noeud_contour[deb_panel]].v;
		side2_u = noeud[panneau[pan].noeud_contour[fin_panel]].u;
		side2_v = noeud[panneau[pan].noeud_contour[fin_panel]].v;
		//printf("deb_panel %d fin_panel %d\n",deb_panel,fin_panel);	
		//printf("panneau[pan].noeud_contour[deb_panel] %d panneau[pan].noeud_contour[fin_panel] %d\n",panneau[pan].noeud_contour[deb_panel],panneau[pan].noeud_contour[fin_panel]);	
		//printf("side1_u %6.2lf side1_v %6.2lf side2_u %6.2lf side2_v %6.2lf\n",side1_u,side1_v,side2_u,side2_v);	
		distance_segment_point(side1_u, side1_v, side2_u, side2_v, *extrem_u, *extrem_v,&dalpha,&dbeta);
		//printf("*extrem_u %6.2lf *extrem_v %6.2lf side %d dalpha %6.2lf dbeta %6.2lf\n",*extrem_u,*extrem_v,co,dalpha,dbeta);	
		if ((fabs(dbeta) <= panneau[pan].netting_2_ropes_accuracy) && (dalpha >= 0.0) && (dalpha <= 1.0))
			{
			//printf("*extrem_u %6.2lf *extrem_v %6.2lf dalpha %6.2lf dbeta %6.2lf side %d\n",*extrem_u,*extrem_v,dalpha,dbeta,co);	
			if (co != panneau[pan].nb_noeud_contour)
				{
				corner1 = co;
				corner2 = co + 1;
				}
			else
				{
				corner1 = co;
				corner2 = 1;
				}
			no = panneau[pan].side2cable[co];
			if (no > 0) 	sens =  1;
			else		sens = -1;
			*extrem_u = side1_u + dalpha * (side2_u-side1_u);
			*extrem_v = side1_v + dalpha * (side2_v-side1_v);
			Structure.nb_total++;
			//printf("Structure.nb_totaa %d extrem_u %6.2lf extrem_v %6.2lf dalpha %6.2lf dbeta %6.2lf\n",Structure.nb_total,*extrem_u,*extrem_v,dalpha,dbeta);	
			extrem_node = Structure.nb_total;
			Structure.nb_node_panel2ropes++;
			node_panel2ropes.U 		= (double *) realloc(node_panel2ropes.U, (1 + Structure.nb_node_panel2ropes) * sizeof(double));
			node_panel2ropes.V 		= (double *) realloc(node_panel2ropes.V, (1 + Structure.nb_node_panel2ropes) * sizeof(double));
			node_panel2ropes.numero_total 	= (int *) realloc(node_panel2ropes.numero_total, (1 + Structure.nb_node_panel2ropes) * sizeof(int));
			node_panel2ropes.side 		= (int *) realloc(node_panel2ropes.side, (1 + Structure.nb_node_panel2ropes) * sizeof(int));
			node_panel2ropes.cable 		= (int *) realloc(node_panel2ropes.cable, (1 + Structure.nb_node_panel2ropes) * sizeof(int));
			node_panel2ropes.sens 		= (int *) realloc(node_panel2ropes.sens, (1 + Structure.nb_node_panel2ropes) * sizeof(int));
			node_panel2ropes.prop_cable 	= (double *) realloc(node_panel2ropes.prop_cable, (1 + Structure.nb_node_panel2ropes) * sizeof(double));
			node_panel2ropes.U[Structure.nb_node_panel2ropes] = *extrem_u;
			node_panel2ropes.V[Structure.nb_node_panel2ropes] = *extrem_v;
			node_panel2ropes.numero_total[Structure.nb_node_panel2ropes] = Structure.nb_total;
			node_panel2ropes.side[Structure.nb_node_panel2ropes] = co;
			node_panel2ropes.cable[Structure.nb_node_panel2ropes] = no*sens;
			node_panel2ropes.sens[Structure.nb_node_panel2ropes] = 1;
			if (no>0) 	node_panel2ropes.prop_cable[Structure.nb_node_panel2ropes] =     dalpha;
			else 		node_panel2ropes.prop_cable[Structure.nb_node_panel2ropes] = 1.0-dalpha;
			
			//cable no is sewn to the side cut by the twine
			element[no*sens].nb_nodes++;
			element[no*sens].noeud = (int *) realloc(element[no*sens].noeud, (1+ element[no*sens].nb_nodes) * sizeof(int));
			element[no*sens].prop = (double *) realloc(element[no*sens].prop, (1+ element[no*sens].nb_nodes) * sizeof(double));
			element[no*sens].noeud[element[no*sens].nb_nodes] = Structure.nb_total;
			if (no>0)	element[no*sens].prop[element[no*sens].nb_nodes] =     dalpha;	
			else		element[no*sens].prop[element[no*sens].nb_nodes] = 1.0-dalpha;	
			//printf("element[%d].nb_nodes %2d ",no,element[no*sens].nb_nodes);	
			//printf("element[%d].noeud %2d ",no,element[no*sens].noeud[element[no*sens].nb_nodes]);	
			//printf("element[%d].prop %6.2lf \n",no,element[no*sens].prop[element[no*sens].nb_nodes]);	

			if (no>0)	dalpha_ok =       dalpha;
			else		dalpha_ok = 1.0 - dalpha;
			noeud[Structure.nb_total].x = noeud[element[no*sens].extremite[1]].x + dalpha_ok * (noeud[element[no*sens].extremite[2]].x-noeud[element[no*sens].extremite[1]].x);
			noeud[Structure.nb_total].y = noeud[element[no*sens].extremite[1]].y + dalpha_ok * (noeud[element[no*sens].extremite[2]].y-noeud[element[no*sens].extremite[1]].y);
			noeud[Structure.nb_total].z = noeud[element[no*sens].extremite[1]].z + dalpha_ok * (noeud[element[no*sens].extremite[2]].z-noeud[element[no*sens].extremite[1]].z);
			noeud[Structure.nb_total].type = element[no*sens].type_noeud;
			noeud[Structure.nb_total].u = *extrem_u;
			noeud[Structure.nb_total].v = *extrem_v;

			//printf("anoeud[%d].xyz %6.2lf %6.2lf %6.2lf \n",Structure.nb_total,noeud[Structure.nb_total].x,noeud[Structure.nb_total].y,noeud[Structure.nb_total].z);	
			//printf("extrem_u %6.2lf *extrem_v %6.2lf \n",*extrem_u,*extrem_v);	
			}
		}
	return extrem_node;
	}


int number_of_cuts(int pan, double extrem1_u, double extrem1_v, double extrem2_u, double extrem2_v, int *cut_t, int *cut_s, double *cut_a, double *cut_b, int *cut_c)
	{
	int nb_cutt,deb_panel,fin_panel,no,code,tri1,tri2;
	double side1_u,side1_v,side2_u,side2_v,dalpha,dbeta;
	tri1     = interieur_panneau_filaire2(extrem1_u, extrem1_v,  pan);		
	tri2     = interieur_panneau_filaire2(extrem2_u, extrem2_v,  pan);		
	//////////////////////////////beginning of calculation of the number of cuts (nb_cutt) of this numerical twine (extrem1_u,extrem1_v to extrem2_u,extrem2_v) with sides of the panel pa	
	nb_cutt = 0; //up to now the twine zu-zv (AB) has no intersection with panel side
	for (no=1;no<=panneau[pan].nb_noeud_contour;no++)
		{
		deb_panel = no;
		if (no == panneau[pan].nb_noeud_contour) 	fin_panel = 1;
		else						fin_panel = no+1;
		side1_u = noeud[panneau[pan].noeud_contour[deb_panel]].u;
		side1_v = noeud[panneau[pan].noeud_contour[deb_panel]].v;
		side2_u = noeud[panneau[pan].noeud_contour[fin_panel]].u;
		side2_v = noeud[panneau[pan].noeud_contour[fin_panel]].v;
		code =  intersection_segment2(extrem1_u,extrem1_v,extrem2_u,extrem2_v,side1_u,side1_v,side2_u,side2_v,&dalpha,&dbeta);
	  	/*calcule l intersection M de 2 segments A (extrem1_u,extrem1_v) a B (extrem2_u,extrem2_v) 
	  	et de  C (side1_u,side1_v) a D (side2_u,side2_v)
	  	et renvoie un code selon l intersection
	  	code = 1  si les 2 segments ne sont pas parallèles
	  	code = 2  si les 2 segments sont parallèles
	  	si les 2  segments ne sont pas parallèles, AM = dalpha AB et CM = dbeta CD
	  	si les 2 segments sont parallèles AC = dalpha AB + dbeta N. Avec N = AB ^ k. k étant le vecteur (0 0 1)
	  	*/
		//printf("code inside %4d	triangles %4d %4d ",code,tri1,tri2);	
		//printf("a1= %lf; b1= %lf; a2= %lf; b2= %lf;\n",extrem1_u,extrem1_v,extrem2_u,extrem2_v);	
		//printf("x1= %lf; y1= %lf; x2= %lf; y2= %lf;\n",side1_u,side1_v,side2_u,side2_v);	
		//printf("alpha %lf beta %lf\n",dalpha,dbeta);	
		if (code == 1)
			{
			//AB (twine) and CD (panel side) not parallel
			if ((dalpha < 1.0) && (dalpha >= 0.0) && (dbeta < 1.0) && (dbeta >= 0.0) && (tri1*tri2 == 0) && (tri1+tri2 > 0))
				{
				//twine cuts a panel side. The intersection is in the twine and in the panel side
				nb_cutt++;
				cut_t[nb_cutt] = tri1;
				cut_s[nb_cutt] = no;
				cut_c[nb_cutt] = code;
				cut_a[nb_cutt] = dalpha;
				cut_b[nb_cutt] = dbeta;
				//printf("tri1 %2d tri2 %2d ",tri1, tri2);	
				//printf("cut_t %2d cut_s %2d cut_c %2d cut_a %4.2lf cut_b %4.2lf\n",cut_t[nb_cutt], cut_s[nb_cutt], cut_c[nb_cutt], cut_a[nb_cutt], cut_b[nb_cutt]);
				//printf("a1= %lf; b1= %lf; a2= %lf; b2= %lf;\n",extrem1_u,extrem1_v,extrem2_u,extrem2_v);	
				//printf("x1= %lf; y1= %lf; x2= %lf; y2= %lf;\n",side1_u,side1_v,side2_u,side2_v);	
				}
			}
		}
	/////////////////////////end of calculation of the number of cuts (nb_cutt) of this numerical twine (extrem1_u,extrem1_v to extrem2_u,extrem2_v) with sides of the panel pa	
	return nb_cutt;
	}


	
int side_neighbor(int pan, double pt1x, double pt1y, double pt2x, double pt2y)
	{
	//return the side of the panel from which the 2 points (pt1 and pt2) are on or close, if they are close, otherwise 0.
	int no,neighbor,close1,close2;
	neighbor = 0;
	for (no=1;no<=panneau[pan].nb_noeud_contour;no++)
		{
		close1 =  is_node_close_side2(pan, no, pt1x, pt1y);
		close2 =  is_node_close_side2(pan, no, pt2x, pt2y);
		//printf("no %d close1 %d close2 %d\n",no,close1,close2);	
		if ((close1 != 0) && (close2 != 0))
			{
			neighbor = no;
			}
		}
	return neighbor;
	}

int is_node_close_side2(int pan, int side, double ptu, double ptv)
	{
	//return 1 if the point (pt) is close (distance < accuracy) the side of the panel pan or on the side. Otherwide 0
	int no,deb_panel,fin_panel,corner1,corner2,close_side,sens,triangle;
	double node_u,node_v,side1_u,side1_v,side2_u,side2_v,dalpha,dbeta,dalpha_ok,side_length;
	
	close_side = 0;
	deb_panel = side;
	if (side == panneau[pan].nb_noeud_contour)	fin_panel = 1;
	else						fin_panel = side+1;
	side1_u = noeud[panneau[pan].noeud_contour[deb_panel]].u;
	side1_v = noeud[panneau[pan].noeud_contour[deb_panel]].v;
	side2_u = noeud[panneau[pan].noeud_contour[fin_panel]].u;
	side2_v = noeud[panneau[pan].noeud_contour[fin_panel]].v;
	side_length = sqrt((side2_u-side1_u)*(side2_u-side1_u)+(side2_v-side1_v)*(side2_v-side1_v));
	//printf("deb_panel %d fin_panel %d\n",deb_panel,fin_panel);	
	//printf("panneau[pan].noeud_contour[deb_panel] %d panneau[pan].noeud_contour[fin_panel] %d\n",panneau[pan].noeud_contour[deb_panel],panneau[pan].noeud_contour[fin_panel]);	
	//printf("side1_u %6.2lf side1_v %6.2lf side2_u %6.2lf side2_v %6.2lf\n",side1_u,side1_v,side2_u,side2_v);	
	distance_segment_point(side1_u, side1_v, side2_u, side2_v, ptu, ptv,&dalpha,&dbeta);
	//printf("ptu %6.2lf ptv %6.2lf side %d dalpha %6.2lf dbeta %6.2lf side_length %6.2lf\n",ptu,ptv,side,dalpha,dbeta,side_length);	
	if ((fabs(dbeta) <= panneau[pan].netting_2_ropes_accuracy) && (dalpha*side_length >= 0.0-panneau[pan].netting_2_ropes_accuracy) && (dalpha*side_length <= side_length+panneau[pan].netting_2_ropes_accuracy))
		{
		close_side = 1;
		}
	return close_side;
	}
	
int is_node_close_another_one2(int pan, double ptu, double ptv)
	{
	int extrem_node,no;
	double node_u,node_v;
	
	extrem_node = 0;
	for (no=1;no<=Structure.nb_node_panel2ropes;no++)
		{
		node_u = node_panel2ropes.U[no];
		node_v = node_panel2ropes.V[no];
		if (sqrt((ptu-node_u)*(ptu-node_u)+(ptv-node_v)*(ptv-node_v)) <= panneau[pan].netting_2_ropes_accuracy)
			{
			extrem_node = node_panel2ropes.numero_total[no];	//node_total
			}
		}
	//printf("pam %3d ptu %6.2lf ptv %6.2lf extrem_node %2d\n",pan,ptu,ptv,extrem_node);	
	return extrem_node;
	}	
	
int bar_creation2(int pan, int pt1, int pt2, double cut_a)
	{
	Structure.nb_barre++;		
	barre[Structure.nb_barre].noeud[1] = pt1;
	barre[Structure.nb_barre].noeud[2] = pt2;
	barre[Structure.nb_barre].netting2ropes_panel 	= pan;
	barre[Structure.nb_barre].netting2ropes_uv	= 1;
	//barre[Structure.nb_barre].longueur_repos = (float)  panneau[pan].longueur_repos*panneau[pan].netting_2_ropes_period*(1.0-cut_a);
	barre[Structure.nb_barre].longueur_repos = (float)  panneau[pan].longueur_repos*panneau[pan].netting_2_ropes_period*(1.0-cut_a)/panneau[pan].netting_2_ropes_bar_nb;
	barre[Structure.nb_barre].pro[1] = 0.0 ;
	barre[Structure.nb_barre].pro[2] = barre[Structure.nb_barre].longueur_repos / panneau[pan].longueur_repos;
	barre[Structure.nb_barre].type = -pan;
	return Structure.nb_barre;
	}
	
int case1(int pan, int tri, double ptu, double ptv)
	{
	int sommet1,sommet2,sommet3;
	double dalpha,dbeta;
	
	Structure.nb_total++;
	//printf("case1 case1 nb_total %4d\n",Structure.nb_total);			
	tri = interieur_panneau_filaire3(ptu, ptv,  pan, &dalpha  ,&dbeta );			
	sommet1 = panneau[pan].noeud_contour[panneau[pan].triangle_contour[tri][1]];
	sommet2 = panneau[pan].noeud_contour[panneau[pan].triangle_contour[tri][2]];
	sommet3 = panneau[pan].noeud_contour[panneau[pan].triangle_contour[tri][3]];
	noeud[Structure.nb_total].x = noeud[sommet1].x + dalpha *(noeud[sommet2].x-noeud[sommet1].x) + dbeta *(noeud[sommet3].x-noeud[sommet2].x);
	noeud[Structure.nb_total].y = noeud[sommet1].y + dalpha *(noeud[sommet2].y-noeud[sommet1].y) + dbeta *(noeud[sommet3].y-noeud[sommet2].y);
	noeud[Structure.nb_total].z = noeud[sommet1].z + dalpha *(noeud[sommet2].z-noeud[sommet1].z) + dbeta *(noeud[sommet3].z-noeud[sommet2].z);	
	noeud[Structure.nb_total].type = panneau[pan].type_noeud;
	noeud[Structure.nb_total].u = ptu;
	noeud[Structure.nb_total].v = ptv;
	Structure.nb_node_panel2ropes++;
	node_panel2ropes.U 		= (double *) realloc(node_panel2ropes.U, (1 + Structure.nb_node_panel2ropes) * sizeof(double));
	node_panel2ropes.V 		= (double *) realloc(node_panel2ropes.V, (1 + Structure.nb_node_panel2ropes) * sizeof(double));
	node_panel2ropes.numero_total 	= (int *) realloc(node_panel2ropes.numero_total, (1 + Structure.nb_node_panel2ropes) * sizeof(int));
	node_panel2ropes.side 		= (int *) realloc(node_panel2ropes.side, (1 + Structure.nb_node_panel2ropes) * sizeof(int));
	node_panel2ropes.cable 		= (int *) realloc(node_panel2ropes.cable, (1 + Structure.nb_node_panel2ropes) * sizeof(int));
	node_panel2ropes.sens 		= (int *) realloc(node_panel2ropes.sens, (1 + Structure.nb_node_panel2ropes) * sizeof(int));
	node_panel2ropes.prop_cable 	= (double *) realloc(node_panel2ropes.prop_cable, (1 + Structure.nb_node_panel2ropes) * sizeof(double));
	node_panel2ropes.U[Structure.nb_node_panel2ropes] = ptu;
	node_panel2ropes.V[Structure.nb_node_panel2ropes] = ptv;
	node_panel2ropes.numero_total[Structure.nb_node_panel2ropes] = Structure.nb_total;
	node_panel2ropes.side[Structure.nb_node_panel2ropes] = 0;
	node_panel2ropes.cable[Structure.nb_node_panel2ropes] = 0;
	node_panel2ropes.sens[Structure.nb_node_panel2ropes] = 0;
	node_panel2ropes.prop_cable[Structure.nb_node_panel2ropes] = 0.0;
	return Structure.nb_total;
	}

//int case2(int pa , int cut_side[nb_cut], double cut_beta[nb_cut], double *extrem_u, double *extrem_v)
int case2(int pan, int cut_s           , double cut_b           , double *extrem_u, double *extrem_v)
	{
	int corner1,corner2,sens,ele;
	double corner1_u,corner1_v,corner2_u,corner2_v;

	corner1 = cut_s;
	if (corner1 == panneau[pan].nb_noeud_contour)	corner2 = 1;
	else						corner2 = corner1+1;
	corner1_u = noeud[panneau[pan].noeud_contour[corner1]].u;
	corner1_v = noeud[panneau[pan].noeud_contour[corner1]].v;
	corner2_u = noeud[panneau[pan].noeud_contour[corner2]].u;
	corner2_v = noeud[panneau[pan].noeud_contour[corner2]].v;
	//begining of extrem2 outside
	*extrem_u = corner1_u + cut_b * (corner2_u-corner1_u);
	*extrem_v = corner1_v + cut_b * (corner2_v-corner1_v);
	//printf("*extrem_u %lf *extrem_v %lf \n",*extrem_u,*extrem_v);	
	Structure.nb_total++;
	//printf("base1 case2 nb_total %4d\n",Structure.nb_total);		
	//printf("Structure.nb_totab %d *extrem_u %6.2lf *extrem_v %6.2lf\n",Structure.nb_total,*extrem_u,*extrem_v);	
	Structure.nb_node_panel2ropes++;
	node_panel2ropes.U 		= (double *) realloc(node_panel2ropes.U, (1 + Structure.nb_node_panel2ropes) * sizeof(double));
	node_panel2ropes.V 		= (double *) realloc(node_panel2ropes.V, (1 + Structure.nb_node_panel2ropes) * sizeof(double));
	node_panel2ropes.numero_total 	= (int *) realloc(node_panel2ropes.numero_total, (1 + Structure.nb_node_panel2ropes) * sizeof(int));
	node_panel2ropes.side 		= (int *) realloc(node_panel2ropes.side, (1 + Structure.nb_node_panel2ropes) * sizeof(int));
	node_panel2ropes.cable 		= (int *) realloc(node_panel2ropes.cable, (1 + Structure.nb_node_panel2ropes) * sizeof(int));
	node_panel2ropes.sens 		= (int *) realloc(node_panel2ropes.sens, (1 + Structure.nb_node_panel2ropes) * sizeof(int));
	node_panel2ropes.prop_cable 	= (double *) realloc(node_panel2ropes.prop_cable, (1 + Structure.nb_node_panel2ropes) * sizeof(double));
	node_panel2ropes.U[Structure.nb_node_panel2ropes] = *extrem_u;
	node_panel2ropes.V[Structure.nb_node_panel2ropes] = *extrem_v;
	node_panel2ropes.numero_total[Structure.nb_node_panel2ropes] = Structure.nb_total;
	node_panel2ropes.side[Structure.nb_node_panel2ropes] = cut_s;
	if (panneau[pan].side2cable[cut_s] > 0) 	sens = 1;
	else						sens = -1;
	ele = sens * panneau[pan].side2cable[cut_s];
	node_panel2ropes.cable[Structure.nb_node_panel2ropes] = ele;
	node_panel2ropes.sens[Structure.nb_node_panel2ropes] = sens;
	if (sens == 1)	node_panel2ropes.prop_cable[Structure.nb_node_panel2ropes]  =       cut_b;
	else		node_panel2ropes.prop_cable[Structure.nb_node_panel2ropes]  = 1.0 - cut_b;
	//printf("eode_created_numero[%d] %d node_panel2ropesUV %lf %lf\n",Structure.nb_node_panel2ropes,node_panel2ropes.numero_total[Structure.nb_node_panel2ropes],node_panel2ropes.U[Structure.nb_node_panel2ropes],node_panel2ropes.V[Structure.nb_node_panel2ropes]);	
	//printf("*extrem_u %lf *extrem_v %lf \n",*extrem_u,*extrem_v);	
	//printf("Structure.nb_total %2d \n",Structure.nb_total);	
	//printf("Structure.nb_total %2d\n",Structure.nb_total);	
	//printf("cut_beta[nb_cut] %lf  ",cut_beta[nb_cut]);	
	//printf("corner1 %2d corner2 %2d\n",corner1,corner2);	
	element[ele].nb_nodes++;
	element[ele].noeud = (int *) realloc(element[ele].noeud, (1+ element[ele].nb_nodes) * sizeof(int));
	element[ele].prop = (double *) realloc(element[ele].prop, (1+ element[ele].nb_nodes) * sizeof(double));

	element[ele].noeud[element[ele].nb_nodes] = Structure.nb_total;
	if (sens == 1)	element[ele].prop[element[ele].nb_nodes] =       cut_b;
	else		element[ele].prop[element[ele].nb_nodes] = 1.0 - cut_b;
	//printf("panel %2d ",pa);	
	//printf("cable %2d ",ele);	
	//printf("element[%d].nb_nodes %2d ",ele,element[ele].nb_nodes);	
	//printf("element[%d].noeud %2d ",ele,element[ele].noeud[element[ele].nb_nodes]);	
	//printf("element[%d].prop %lf \n",ele,element[ele].prop[element[ele].nb_nodes]);	
	noeud[Structure.nb_total].x = noeud[element[ele].extremite[1]].x + element[ele].prop[element[ele].nb_nodes] * (noeud[element[ele].extremite[2]].x-noeud[element[ele].extremite[1]].x);
	noeud[Structure.nb_total].y = noeud[element[ele].extremite[1]].y + element[ele].prop[element[ele].nb_nodes] * (noeud[element[ele].extremite[2]].y-noeud[element[ele].extremite[1]].y);
	noeud[Structure.nb_total].z = noeud[element[ele].extremite[1]].z + element[ele].prop[element[ele].nb_nodes] * (noeud[element[ele].extremite[2]].z-noeud[element[ele].extremite[1]].z);
	noeud[Structure.nb_total].type = element[ele].type_noeud;
	//end of extrem outside
	return Structure.nb_total;
	}
	
void sorting_node_per_element_around_panel(int pan)
	{
	int no,np,co,cp,corner1,corner2,sewn,temp_noeud;
	double temp_prop;
	
	//beginning of sorting node in element by prop increasing
	for (np=1;np<=panneau[pan].nb_noeud_contour;np++)	
		{
		no = abs(panneau[pan].side2cable[np]);
		element[no].flag_maillage = 1;	//this cable no is treated
		//the cable no is sewn to the panel pan
		//printf("caaaaaaaaaable %4d nb_nodes %4d\n",no,element[no].nb_nodes);
		for (co=1;co<=element[no].nb_nodes-1;co++)
			{
			//printf("coooooooooooo %4d \n",co);
			temp_noeud = element[no].noeud[co];
			temp_prop = element[no].prop[co];	
			for (cp=co+1;cp<=element[no].nb_nodes;cp++)
				{
				//printf("prop[%2d] %lf prop[%2d] %lf temp %lf \n",co,element[no].prop[co],cp,element[no].prop[cp],temp_prop);
				if (element[no].prop[cp] < element[no].prop[co])
					{
					element[no].prop[co] = element[no].prop[cp];
					element[no].noeud[co] = element[no].noeud[cp];
					element[no].prop[cp] = temp_prop;
					element[no].noeud[cp] = temp_noeud;
					temp_noeud = element[no].noeud[co];
					temp_prop = element[no].prop[co];	
					}
				}	
			}
		}
	//end of sorting node in element by prop increasing

	////////////begining of the list of node and prop by element sewn
	for (np=1;np<=panneau[pan].nb_noeud_contour;np++)	
		{
		no = abs(panneau[pan].side2cable[np]);
		//the cable no is sewn to the panel pan
		//printf("cable %4d nb_nodes %4d\n",no,element[no].nb_nodes);
		for (co=1;co<=element[no].nb_nodes;co++)
			{
			//printf("	noeud[%2d] %4d ",co,element[no].noeud[co]);
			//printf("prop[%2d] %lf \n",co,element[no].prop[co]);
			}
		}
	////////////begining of the list of node and prop by element sewn
	}


void bar_creation_per_element_around_panel(int pan)
	{
	int no,np,co,cp,corner1,corner2,sewn,temp_noeud,node_prop1,node_prop2,trouve_barre;
	double temp_prop,prop1,prop2;
	
////////////////////////////////beginning of bar creation in element
	for (np=1;np<=panneau[pan].nb_noeud_contour;np++)	
		{
		no = abs(panneau[pan].side2cable[np]);
		//the cable no is sewn to the panel pan
		//printf("cablf %4d nb_node %4d\n",no,element[no].nb_nodes);	
		//printf("extremite %4d  %4d\n",element[no].extremite[1],element[no].extremite[2]);	
		//printf("element length %6.2f ",element[no].lgrepos);
		for (co=1;co<=element[no].nb_nodes+1;co++)
			{
			//printf("bar %4d \n",co);	
			if (element[no].nb_nodes != 0)
				{
				if (co == 1)
					{
					prop1 = 0.0;				node_prop1 = element[no].extremite[1];
					prop2 = element[no].prop[co];		node_prop2 = element[no].noeud[co];
					//printf("	node_prop1 %4d prop1 %lf\n",node_prop1,prop1);	
					//printf("	node_prop2 %4d prop2 %lf\n",node_prop2,prop2);	
					}
				if ((co != 1) && (co != element[no].nb_nodes+1))
					{
					prop1 = element[no].prop[co-1];		node_prop1 = element[no].noeud[co-1];
					prop2 = element[no].prop[co];		node_prop2 = element[no].noeud[co];
					//printf("	node_prop1 %4d prop1 %lf\n",node_prop1,prop1);	
					//printf("	node_prop2 %4d prop2 %lf\n",node_prop2,prop2);	
					}
				if (co == element[no].nb_nodes+1)
					{
					prop1 = element[no].prop[co-1];		node_prop1 = element[no].noeud[co-1];
					prop2 = 1.0;				node_prop2 = element[no].extremite[2];
					//printf("	node_prop1 %4d prop1 %lf\n",node_prop1,prop1);	
					//printf("	node_prop2 %4d prop2 %lf\n",node_prop2,prop2);	
					}
				for (cp=1;cp<=Structure.nb_barre;cp++)
					{
					trouve_barre = 0;
					if ((barre[cp].type == no) && (barre[cp].noeud[1] == node_prop1) && (barre[cp].noeud[2] != node_prop2))
						{
						trouve_barre = cp;
						barre[cp].noeud[2] = node_prop2;
						barre[cp].longueur_repos = (float) ((prop2-prop1) * element[no].lgrepos);
						barre[cp].pro[1] = (float) prop1;
						barre[cp].pro[2] = (float) prop2;
						barre[cp].type = no;
						//printf("length %d %6.2f \n",Structure.nb_barre,barre[Structure.nb_barre].longueur_repos);
						//printf("	node_prop1 %4d prop1 %lf\n",node_prop1,prop1);	
						//printf("	node_prop2 %4d prop2 %lf\n",node_prop2,prop2);	
						//printf("element length %6.2f ",element[no].lgrepos);
						}
					}
				//printf("	trouve_barre %4d\n",trouve_barre);	
				if (trouve_barre == 0)
					{
					Structure.nb_barre++;
					barre[Structure.nb_barre].noeud[1] = node_prop1;
					//printf("barrh %d extremity 1 %d\n",Structure.nb_barre,node_prop1);	
					barre[Structure.nb_barre].noeud[2] = node_prop2;
					barre[Structure.nb_barre].netting2ropes_panel 	= pan;
					barre[Structure.nb_barre].netting2ropes_uv	= 1;
					barre[Structure.nb_barre].longueur_repos = (float)  ((prop2-prop1) * element[no].lgrepos);
					barre[Structure.nb_barre].pro[1] = (float) prop1;
					barre[Structure.nb_barre].pro[2] = (float) prop2;
					barre[Structure.nb_barre].type = no;
					//printf("lengti %d %6.2f \n",Structure.nb_barre,barre[Structure.nb_barre].longueur_repos);
					//printf("	node_prop1 %4d prop1 %lf\n",node_prop1,prop1);	
					//printf("	node_prop2 %4d prop2 %lf\n",node_prop2,prop2);	
					//printf("element length %6.2f ",element[no].lgrepos);
					}
					
				}
			else
				{
				prop1 = 0.0;	node_prop1 = element[no].extremite[1];
				prop2 = 1.0;	node_prop2 = element[no].extremite[2];
				for (cp=1;cp<=Structure.nb_barre;cp++)
					{
					trouve_barre = 0;
					if ((barre[cp].type == no) && (barre[cp].noeud[1] == node_prop1) && (barre[cp].noeud[2] != node_prop2))
						{
						trouve_barre = cp;
						barre[cp].noeud[2] = node_prop2;
						barre[cp].longueur_repos = (float) ((prop2-prop1) * element[no].lgrepos);
						barre[cp].pro[1] = (float) prop1;
						barre[cp].pro[2] = (float) prop2;
						barre[cp].type = no;
						//printf("lengtj %d %6.2f \n",Structure.nb_barre,barre[Structure.nb_barre].longueur_repos);
						//printf("	node_prop1 %4d prop1 %lf\n",node_prop1,prop1);	
						//printf("	node_prop2 %4d prop2 %lf\n",node_prop2,prop2);	
						//printf("element length %6.2f ",element[no].lgrepos);
						}
					}
				//printf("	trouve_barre %4d\n",trouve_barre);	
				if (trouve_barre == 0)
					{
					Structure.nb_barre++;
					barre[Structure.nb_barre].noeud[1] = node_prop1;
					//printf("barri %d extremity 1 %d\n",Structure.nb_barre,node_prop1);	
					barre[Structure.nb_barre].noeud[2] = node_prop2;
					barre[Structure.nb_barre].netting2ropes_panel 	= pan;
					barre[Structure.nb_barre].netting2ropes_uv	= 1;
					barre[Structure.nb_barre].longueur_repos = (float)  ((prop2-prop1) * element[no].lgrepos);
					barre[Structure.nb_barre].pro[1] = (float) prop1;
					barre[Structure.nb_barre].pro[2] = (float) prop2;
					barre[Structure.nb_barre].type = no;
					//printf("lengtk %d %6.2f \n",Structure.nb_barre,barre[Structure.nb_barre].longueur_repos);
					//printf("	node_prop1 %4d prop1 %lf\n",node_prop1,prop1);	
					//printf("	node_prop2 %4d prop2 %lf\n",node_prop2,prop2);	
					//printf("element length %6.2f ",element[no].lgrepos);
					}
				}
			}
		
		/*for (co=1;co<=Structure.nb_barre;co++)
			{
			if (barre[co].type == no)
				{
				//this barre co is in the element no
				printf("bar %4d ",co);	
				printf("cable %4d ",barre[co].type);	
				printf("extremiy %4d %4d\n",barre[co].noeud[1] ,barre[co].noeud[2] );	
				}
			}
		*/		
		}
////////////////////////////////end of bar creation

	/*
	for (no=1;no<=Structure.nb_barre;no++)
		{
		printf("bar %4d ",no);	
		printf("cable %4d ",barre[no].type);	
		printf("lengtl %6.2f ",barre[no].longueur_repos);
		printf("extremiy %4d %4d\n",barre[no].noeud[1] ,barre[no].noeud[2] );	
		}
	*/
	}

