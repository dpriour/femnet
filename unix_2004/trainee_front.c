#define PRINCIPAL 0
#include "4c19.h"
	
	
void trainee_front()
	{
  	/*calcul des efforts de trainee en amont du front*/
  	double AlbX1,AlbX2,AlbX3,AlbZ1,AlbZ2,AlbZ3,U1,V1,U2,V2,U3,V3,ZZ1,vitesseM,directionM;
  	double nbmaille,nbmaille_aval,nbmaille_amont,param1,param2,tfuv[4],V[4];
  	int elem,zh,zi,zj,zl,zk,nc,appartient,pan;

  	changement_variable_catch();		/* met l axe des X dans le sens du courant et le plan Y0Z tel que Z soit vertical ascendant*/
  	for ( elem = 1 ; elem <= NOMBRE_SURFACES ; elem++ )
  		{
  		
  		/* Definition du vecteur courant grace au fichier .mdf */
	     	V[1] = Courant.vitesse*cos(Courant.direction*PI/180.0) * panneau[Surface[elem].type].current_reduction;
	     	V[2] = Courant.vitesse*sin(Courant.direction*PI/180.0) * panneau[Surface[elem].type].current_reduction;
	     	V[3] = 0.0  					       * panneau[Surface[elem].type].current_reduction;
		if (Courant.nb_courant != 0)
			{
			zh = yc(elem,1);	zi = yc(elem,4);	zj = yc(elem,7);
			ZZ1 = (wf[zh+2] + wf[zi+2] + wf[zj+2]) /3.0;			/*mean depth of the triangular element*/
			for (zl = 1 ;zl <= Courant.nb_courant ;zl++ )
				{
				if (((ZZ1-Courant.depth1[zl])*(ZZ1-Courant.depth2[zl])) <= 0.0)
					{
					vitesseM   = Courant.courant1[zl]   +(ZZ1-Courant.depth1[zl])/(Courant.depth2[zl]-Courant.depth1[zl])*(Courant.courant2[zl]  -Courant.courant1[zl]);
					directionM = Courant.direction1[zl] +(ZZ1-Courant.depth1[zl])/(Courant.depth2[zl]-Courant.depth1[zl])*(Courant.direction2[zl]-Courant.direction1[zl]);
					V[1] = vitesseM*cos(directionM*PI/180.0) * panneau[Surface[elem].type].current_reduction;
					V[2] = vitesseM*sin(directionM*PI/180.0) * panneau[Surface[elem].type].current_reduction;
					V[3] = 0.0                               * panneau[Surface[elem].type].current_reduction;
					/*if (elem == 1298) 
						{
						printf("zl %d ",zl);
						printf("Courant.nb_courant %d ",Courant.nb_courant);
						printf("h mean %lf ",ZZ1);
						printf("depth1 %lf depth2 %lf ",Courant.depth1[zl],Courant.depth2[zl]);
						printf("courant1 %lf courant2 %lf ",Courant.courant1[zl],Courant.courant2[zl]);
						printf("vitesseM %lf directionM %lf ",vitesseM,directionM);
						printf("ZZ1 %lf  ",((wf[zh+2] + wf[zi+2] + wf[zj+2]) /3.0)+56);
						}
					*/
					}
				}
		
			}
  		
  		
  		if (Surface[elem].tarp == 0)
  			{
  		/*printf("elemee = %5d ",elem);*/
  		/*numeros des coordonnees selon x des sommets du triangle*/
  		zh = yc(elem,1);  zi = yc(elem,4);  zj = yc(elem,7);

  		/*
  		coordonnees cartesiennes et filaires du triangle
  		*/
  		AlbX1 = wfcodend[zh  ];	AlbX2 = wfcodend[zi  ];	AlbX3 = wfcodend[zj  ];
  		AlbZ1 = wfcodend[zh+2];	AlbZ2 = wfcodend[zi+2];	AlbZ3 = wfcodend[zj+2];
  		U1 = Surface[elem].lon[1] ; V1 = Surface[elem].lon[2] ;
  		U2 = Surface[elem].lon[3] ; V2 = Surface[elem].lon[4] ;
  		U3 = Surface[elem].lon[5] ; V3 = Surface[elem].lon[6] ;
   		/*ne traiter que les surfaces en partie sous la surface libre*/
   		if ((AlbZ1 <= 0.0) || (AlbZ2 <= 0.0 ) || (AlbZ3 <= 0.0 ))
		{
  		/*ne traiter que les surfaces a l avant ou en partie a l avant du front*/
  		if ((AlbX1 < Prise.front) || (AlbX2 < Prise.front) || (AlbX3 < Prise.front))
  			{
  			for ( zl = 1 ; zl <= 9 ; zl++ ) wae[zl] = 0.0;  				
			/*surfaces totalement a l avant  du front*/
  			if ((AlbX1 <= Prise.front) && (AlbX2 <= Prise.front) && (AlbX3 <= Prise.front))
  				{
  				/*printf("elem avt = %5d \n",elem);*/
   				/* Efforts aux 3 noeuds, sommets du triangle.*/
				trainee_fil( elem, V, &tfuv[0]);
				nbmaille = Surface[elem].nb_cote_u_ou_v;
   				/* Efforts aux 3 noeuds, sommets du triangle .*/
   				wae[1] = tfuv[1] / 3.0 * nbmaille;
   				wae[2] = tfuv[2] / 3.0 * nbmaille;
   				wae[3] = tfuv[3] / 3.0 * nbmaille;
   				wae[4] = tfuv[1] / 3.0 * nbmaille;
   				wae[5] = tfuv[2] / 3.0 * nbmaille;
   				wae[6] = tfuv[3] / 3.0 * nbmaille;
   				wae[7] = tfuv[1] / 3.0 * nbmaille;
   				wae[8] = tfuv[2] / 3.0 * nbmaille;
   				wae[9] = tfuv[3] / 3.0 * nbmaille;
/*if (nbiter > 274)
	{
	if ((zh == 235)  || (zi == 235)  || (zj == 235))	
		{
		printf("a elem %d ",elem);
		printf("tfuv %lf %lf %lf ",tfuv[1],tfuv[2],tfuv[3]);
		printf("nb_m %lf ",nbmaille);
		printf("tfuv*nb_m %lf ",tfuv[2]*nbmaille/3);
		printf("wae %lf %lf %lf ",wae[2],wae[5],wae[8]);
		}
	}*/
				/* Mise a jour du vecteur effort global*/
    				for ( zl = 1; zl <= 9; zl++ ) wasurf[yc(elem,zl)] += wae[zl];
				Structure.surface_drag = Structure.surface_drag + wae[1] + wae[4] + wae[7];
				pan = Surface[elem].type;
				panneau[pan].drag = panneau[pan].drag + wae[1] + wae[4] + wae[7];
				Surface[elem].panel_drag = Surface[elem].panel_drag + wae[1] + wae[4] + wae[7];
				Surface[elem].panel_dragxyz = Surface[elem].panel_dragxyz + sqrt(wae[1]*wae[1] + wae[2]*wae[2] + wae[3]*wae[3]) 
                                                                                          + sqrt(wae[4]*wae[4] + wae[5]*wae[5] + wae[6]*wae[6]) 
                                                                                          + sqrt(wae[7]*wae[7] + wae[8]*wae[8] + wae[9]*wae[9]);
  				/*printf("elem %5d pan %5d drag %lf drag %lf \n",elem,pan,Surface[elem].panel_drag,panneau[pan].drag );*/
    				}
			else if ((AlbX1 >= Prise.front) && (AlbX2 < Prise.front) && (AlbX3 < Prise.front))
  				{
  				/*surfaces partiellement a l avant  du front : point 1 en aval du front
  				inter1 (inter2) est le point intersection du front avec le cote 12 (31)*/
   				/* trainee sur un fil u et v du triangle elem.*/
				trainee_fil( elem, V, &tfuv[0]);
				/* Nombre de maille par point du triangle de sommets 1, inter1 et inter2. */
				nbmaille = Surface[elem].nb_cote_u_ou_v;
				param1 = (AlbX1-Prise.front) / (AlbX1-AlbX2) ; param2 = (AlbX1-Prise.front) / (AlbX1-AlbX3) ;
				nbmaille_aval = fabs( ( (1 - param1) * U1 + param1 * U2 - U1) * ((1 - param2) * V1 + param2 * V3 - V1)
				                    - ( (1 - param1) * V1 + param1 * V2 - V1) * ((1 - param2) * U1 + param2 * U3 - U1) );
   				/* Efforts aux 3 noeuds, sommets du triangle .*/
   				wae[1] = tfuv[1] / 3.0 * (nbmaille - nbmaille_aval * (1.0 + ((AlbX2-Prise.front)/(AlbX2-AlbX1)) + ((AlbX3-Prise.front)/(AlbX3-AlbX1))));
   				wae[2] = tfuv[2] / 3.0 * (nbmaille - nbmaille_aval * (1.0 + ((AlbX2-Prise.front)/(AlbX2-AlbX1)) + ((AlbX3-Prise.front)/(AlbX3-AlbX1))));
   				wae[3] = tfuv[3] / 3.0 * (nbmaille - nbmaille_aval * (1.0 + ((AlbX2-Prise.front)/(AlbX2-AlbX1)) + ((AlbX3-Prise.front)/(AlbX3-AlbX1))));
   				wae[4] = tfuv[1] / 3.0 * (nbmaille - nbmaille_aval * ((Prise.front-AlbX1)/(AlbX2-AlbX1)));
   				wae[5] = tfuv[2] / 3.0 * (nbmaille - nbmaille_aval * ((Prise.front-AlbX1)/(AlbX2-AlbX1)));
   				wae[6] = tfuv[3] / 3.0 * (nbmaille - nbmaille_aval * ((Prise.front-AlbX1)/(AlbX2-AlbX1)));
   				wae[7] = tfuv[1] / 3.0 * (nbmaille - nbmaille_aval * ((Prise.front-AlbX1)/(AlbX3-AlbX1)));
   				wae[8] = tfuv[2] / 3.0 * (nbmaille - nbmaille_aval * ((Prise.front-AlbX1)/(AlbX3-AlbX1)));
   				wae[9] = tfuv[3] / 3.0 * (nbmaille - nbmaille_aval * ((Prise.front-AlbX1)/(AlbX3-AlbX1)));
/*if (nbiter > 274)
	{
	if ((zh == 235)  || (zi == 235)  || (zj == 235))	
		{
		printf("b elem %d ",elem);
		printf("tfuv %lf %lf %lf ",tfuv[1],tfuv[2],tfuv[3]);
		printf("nb_m %lf ",nbmaille);
		printf("tfuv*nb_m %lf ",tfuv[2]*nbmaille/3);
		printf("wae %lf %lf %lf ",wae[2],wae[5],wae[8]);
		}
	}*/
				/* Mise a jour du vecteur effort global*/
    				for ( zl = 1; zl <= 9; zl++ ) wasurf[yc(elem,zl)] += wae[zl];
				Structure.surface_drag = Structure.surface_drag + wae[1] + wae[4] + wae[7];
				pan = Surface[elem].type;
				panneau[pan].drag = panneau[pan].drag + wae[1] + wae[4] + wae[7];
				Surface[elem].panel_drag = Surface[elem].panel_drag + wae[1] + wae[4] + wae[7];
 				Surface[elem].panel_dragxyz = Surface[elem].panel_dragxyz + sqrt(wae[1]*wae[1] + wae[2]*wae[2] + wae[3]*wae[3]) 
                                                                                          + sqrt(wae[4]*wae[4] + wae[5]*wae[5] + wae[6]*wae[6]) 
                                                                                          + sqrt(wae[7]*wae[7] + wae[8]*wae[8] + wae[9]*wae[9]);
   				}
			else if ((AlbX1 < Prise.front) && (AlbX2 >= Prise.front) && (AlbX3 < Prise.front))
  				{
  				/* surfaces partiellement a l avant  du front : point 2 en aval du front
  				inter1 (inter2) est le point intersection du front avec le cote 23 (12)
  				on calcule le volume en amont que l on retranche au volume dy cylindre de section triangulaire*/
   				/* trainee sur un fil u et v du triangle elem.*/
				trainee_fil( elem, V, &tfuv[0]);
				/* Nombre de maille du triangle de sommets 2, inter1 et inter2. */
				nbmaille = Surface[elem].nb_cote_u_ou_v;
				param1 = (AlbX2-Prise.front) / (AlbX2-AlbX3) ; param2 = (AlbX2-Prise.front) / (AlbX2-AlbX1) ;
				nbmaille_aval = fabs( ( (1 - param1) * U2 + param1 * U3 - U2) * ( (1 - param2) * V2 + param2 * V1 - V2)
				                    - ( (1 - param1) * V2 + param1 * V3 - V2) * ( (1 - param2) * U2 + param2 * U1 - U2) );
				/* Efforts aux 3 noeuds, sommets du triangle .*/
   				wae[1] = tfuv[1] / 3.0 * (nbmaille - nbmaille_aval * ((Prise.front-AlbX2)/(AlbX1-AlbX2)));
   				wae[2] = tfuv[2] / 3.0 * (nbmaille - nbmaille_aval * ((Prise.front-AlbX2)/(AlbX1-AlbX2)));
   				wae[3] = tfuv[3] / 3.0 * (nbmaille - nbmaille_aval * ((Prise.front-AlbX2)/(AlbX1-AlbX2)));
   				wae[4] = tfuv[1] / 3.0 * (nbmaille - nbmaille_aval * (1.0 + ((AlbX3-Prise.front)/(AlbX3-AlbX2)) + ((AlbX1-Prise.front)/(AlbX1-AlbX2))));
   				wae[5] = tfuv[2] / 3.0 * (nbmaille - nbmaille_aval * (1.0 + ((AlbX3-Prise.front)/(AlbX3-AlbX2)) + ((AlbX1-Prise.front)/(AlbX1-AlbX2))));
   				wae[6] = tfuv[3] / 3.0 * (nbmaille - nbmaille_aval * (1.0 + ((AlbX3-Prise.front)/(AlbX3-AlbX2)) + ((AlbX1-Prise.front)/(AlbX1-AlbX2))));
   				wae[7] = tfuv[1] / 3.0 * (nbmaille - nbmaille_aval * ((Prise.front-AlbX2)/(AlbX3-AlbX2)));
   				wae[8] = tfuv[2] / 3.0 * (nbmaille - nbmaille_aval * ((Prise.front-AlbX2)/(AlbX3-AlbX2)));
   				wae[9] = tfuv[3] / 3.0 * (nbmaille - nbmaille_aval * ((Prise.front-AlbX2)/(AlbX3-AlbX2)));
/*if (nbiter > 274)
	{
	if ((zh == 235)  || (zi == 235)  || (zj == 235))	
		{
		printf("c elem %d ",elem);
		printf("tfuv %lf %lf %lf ",tfuv[1],tfuv[2],tfuv[3]);
		printf("nb_m %lf ",nbmaille);
		printf("tfuv*nb_m %lf ",tfuv[2]*nbmaille/3);
		printf("wae %lf %lf %lf ",wae[2],wae[5],wae[8]);
		}
	}*/
				/* Mise a jour du vecteur effort global*/
    				for ( zl = 1 ; zl <= 9 ; zl++ ) wasurf[yc(elem,zl)] += wae[zl];  				
				Structure.surface_drag = Structure.surface_drag + wae[1] + wae[4] + wae[7];
				pan = Surface[elem].type;
				panneau[pan].drag = panneau[pan].drag + wae[1] + wae[4] + wae[7];
				Surface[elem].panel_drag = Surface[elem].panel_drag + wae[1] + wae[4] + wae[7];
				Surface[elem].panel_dragxyz = Surface[elem].panel_dragxyz + sqrt(wae[1]*wae[1] + wae[2]*wae[2] + wae[3]*wae[3]) 
                                                                                          + sqrt(wae[4]*wae[4] + wae[5]*wae[5] + wae[6]*wae[6]) 
                                                                                          + sqrt(wae[7]*wae[7] + wae[8]*wae[8] + wae[9]*wae[9]);
    				}
			else if ((AlbX1 < Prise.front) && (AlbX2 < Prise.front) && (AlbX3 >= Prise.front))
  				{
  				/* surfaces partiellement a l avant du front : point 3 en aval du front
  				inter1 (inter2) est le point intersection du front avec le cote 31 (23) */
   				/* trainee sur un fil u et v du triangle elem.*/
				trainee_fil( elem, V, &tfuv[0]);				
				/* Nombre de maille du triangle de sommets 3, inter1 et inter2. */
				nbmaille = Surface[elem].nb_cote_u_ou_v;
				param1 = (AlbX3-Prise.front) / (AlbX3-AlbX1) ;    param2 = (AlbX3-Prise.front) / (AlbX3-AlbX2) ;
				nbmaille_aval = fabs( ( (1 - param1) * U3 + param1 * U1 - U3) * ( (1 -param2) * V3 + param2 * V2 - V3)
				                    - ( (1 - param1) * V3 + param1 * V1 - V3) * ( (1 -param2) * U3 + param2 * U2 - U3) );
   				/* Efforts aux 3 noeuds, sommets du triangle .*/
   				wae[1] = tfuv[1] / 3.0 * (nbmaille - nbmaille_aval * ((Prise.front-AlbX3)/(AlbX1-AlbX3)));
   				wae[2] = tfuv[2] / 3.0 * (nbmaille - nbmaille_aval * ((Prise.front-AlbX3)/(AlbX1-AlbX3)));
   				wae[3] = tfuv[3] / 3.0 * (nbmaille - nbmaille_aval * ((Prise.front-AlbX3)/(AlbX1-AlbX3)));
   				wae[4] = tfuv[1] / 3.0 * (nbmaille - nbmaille_aval * ((Prise.front-AlbX3)/(AlbX2-AlbX3)));
   				wae[5] = tfuv[2] / 3.0 * (nbmaille - nbmaille_aval * ((Prise.front-AlbX3)/(AlbX2-AlbX3)));
   				wae[6] = tfuv[3] / 3.0 * (nbmaille - nbmaille_aval * ((Prise.front-AlbX3)/(AlbX2-AlbX3)));
   				wae[7] = tfuv[1] / 3.0 * (nbmaille - nbmaille_aval * (1.0 + ((AlbX1-Prise.front)/(AlbX1-AlbX3)) + ((AlbX2-Prise.front)/(AlbX2-AlbX3))));
   				wae[8] = tfuv[2] / 3.0 * (nbmaille - nbmaille_aval * (1.0 + ((AlbX1-Prise.front)/(AlbX1-AlbX3)) + ((AlbX2-Prise.front)/(AlbX2-AlbX3))));
   				wae[9] = tfuv[3] / 3.0 * (nbmaille - nbmaille_aval * (1.0 + ((AlbX1-Prise.front)/(AlbX1-AlbX3)) + ((AlbX2-Prise.front)/(AlbX2-AlbX3))));
/*if (nbiter > 274)
	{
	if ((zh == 235)  || (zi == 235)  || (zj == 235))	
		{
		printf("d elem %d ",elem);
		printf("tfuv %lf %lf %lf ",tfuv[1],tfuv[2],tfuv[3]);
		printf("nb_m %lf ",nbmaille);
		printf("tfuv*nb_m %lf ",tfuv[2]*nbmaille/3);
		printf("wae %lf %lf %lf ",wae[2],wae[5],wae[8]);
		}
	}*/
				/* Mise a jour du vecteur effort global*/
    				for ( zl = 1 ; zl <= 9 ; zl++ ) wasurf[yc(elem,zl)] += wae[zl];  				
				Structure.surface_drag = Structure.surface_drag + wae[1] + wae[4] + wae[7];
				pan = Surface[elem].type;
				panneau[pan].drag = panneau[pan].drag + wae[1] + wae[4] + wae[7];
				Surface[elem].panel_drag = Surface[elem].panel_drag + wae[1] + wae[4] + wae[7];
 				Surface[elem].panel_dragxyz = Surface[elem].panel_dragxyz + sqrt(wae[1]*wae[1] + wae[2]*wae[2] + wae[3]*wae[3]) 
                                                                                          + sqrt(wae[4]*wae[4] + wae[5]*wae[5] + wae[6]*wae[6]) 
                                                                                          + sqrt(wae[7]*wae[7] + wae[8]*wae[8] + wae[9]*wae[9]);
   				}
			else if ((AlbX1 < Prise.front) && (AlbX2 >= Prise.front) && (AlbX3 >= Prise.front))
  				{
  				/* surfaces partiellement a l arriere  du front : point 1 en amont du front
  				inter1 (inter2) est le point intersection du front avec le cote 12 (31)*/
   				/* trainee sur un fil u et v du triangle elem.*/
				trainee_fil( elem, V, &tfuv[0]);
   				/* Nombre de mailles contenues dans le triangle amont de sommets1, inter1 et inter2.*/
				nbmaille = Surface[elem].nb_cote_u_ou_v;
   				param1 = (AlbX1-Prise.front) / (AlbX1-AlbX2) ;    param2 = (AlbX1-Prise.front) / (AlbX1-AlbX3) ;
				nbmaille_amont = fabs( ( (1 - param1) * U1 + param1 * U2 - U1) * ( (1 - param2) * V1 + param2 * V3 - V1)
				                     - ( (1 - param1) * V1 + param1 * V2 - V1) * ( (1 - param2) * U1 + param2 * U3 - U1) );
   				/* Efforts aux 3 noeuds, sommets du triangle elem. */
   				wae[1] = tfuv[1] / 3.0 * (nbmaille_amont * (1.0 + ((AlbX2-Prise.front)/(AlbX2-AlbX1)) + ((AlbX3-Prise.front)/(AlbX3-AlbX1))));
   				wae[2] = tfuv[2] / 3.0 * (nbmaille_amont * (1.0 + ((AlbX2-Prise.front)/(AlbX2-AlbX1)) + ((AlbX3-Prise.front)/(AlbX3-AlbX1))));
   				wae[3] = tfuv[3] / 3.0 * (nbmaille_amont * (1.0 + ((AlbX2-Prise.front)/(AlbX2-AlbX1)) + ((AlbX3-Prise.front)/(AlbX3-AlbX1))));
   				wae[4] = tfuv[1] / 3.0 * (nbmaille_amont * ((Prise.front-AlbX1)/(AlbX2-AlbX1)));
   				wae[5] = tfuv[2] / 3.0 * (nbmaille_amont * ((Prise.front-AlbX1)/(AlbX2-AlbX1)));
   				wae[6] = tfuv[3] / 3.0 * (nbmaille_amont * ((Prise.front-AlbX1)/(AlbX2-AlbX1)));
   				wae[7] = tfuv[1] / 3.0 * (nbmaille_amont * ((Prise.front-AlbX1)/(AlbX3-AlbX1)));
   				wae[8] = tfuv[2] / 3.0 * (nbmaille_amont * ((Prise.front-AlbX1)/(AlbX3-AlbX1)));
   				wae[9] = tfuv[3] / 3.0 * (nbmaille_amont * ((Prise.front-AlbX1)/(AlbX3-AlbX1)));
/*if (nbiter > 274)
	{
	if ((zh == 235)  || (zi == 235)  || (zj == 235))	
		{
		printf("e elem %d ",elem);
		printf("tfuv %lf %lf %lf ",tfuv[1],tfuv[2],tfuv[3]);
		printf("nb_m %lf ",nbmaille);
		printf("tfuv*nb_m %lf ",tfuv[2]*nbmaille/3);
		printf("wae %lf %lf %lf ",wae[2],wae[5],wae[8]);
		}
	}*/
				/* Mise a jour du vecteur effort global */
    				for ( zl = 1 ; zl <= 9 ; zl++ ) wasurf[yc(elem,zl)] += wae[zl];  				
				Structure.surface_drag = Structure.surface_drag + wae[1] + wae[4] + wae[7];
				pan = Surface[elem].type;
				panneau[pan].drag = panneau[pan].drag + wae[1] + wae[4] + wae[7];
				Surface[elem].panel_drag = Surface[elem].panel_drag + wae[1] + wae[4] + wae[7];
 				Surface[elem].panel_dragxyz = Surface[elem].panel_dragxyz + sqrt(wae[1]*wae[1] + wae[2]*wae[2] + wae[3]*wae[3]) 
                                                                                          + sqrt(wae[4]*wae[4] + wae[5]*wae[5] + wae[6]*wae[6]) 
                                                                                          + sqrt(wae[7]*wae[7] + wae[8]*wae[8] + wae[9]*wae[9]);
   				}
    				
			else if ((AlbX1 >= Prise.front) && (AlbX2 < Prise.front) && (AlbX3 >= Prise.front))
  				{
  				/* surfaces partiellement a l arriere  du front : point 2 en amont du front
  				inter1 (inter2) est le point intersection du front avec le cote 23 (12) */
   				/* trainee sur un fil u et v du triangle elem.*/
				trainee_fil( elem, V, &tfuv[0]);
   				/* Nombre de mailles contenues dans le triangle de sommets 2, inter1 et inter2. */
				nbmaille = Surface[elem].nb_cote_u_ou_v;
				param1 = (AlbX2-Prise.front) / (AlbX2-AlbX3) ;    param2 = (AlbX2-Prise.front) / (AlbX2-AlbX1) ;
				nbmaille_amont = fabs( ( (1 - param1) * U2 + param1 * U3 - U2) * ( (1 - param2) * V2 + param2 * V1 - V2)
				                     - ( (1 - param1) * V2 + param1 * V3 - V2) * ( (1 - param2) * U2 + param2 * U1 - U2) );
   				/* Efforts aux 3 noeuds, sommets du triangle elem. */
   				wae[1] = tfuv[1] / 3.0 * (nbmaille_amont * ((Prise.front-AlbX2)/(AlbX1-AlbX2)));
   				wae[2] = tfuv[2] / 3.0 * (nbmaille_amont * ((Prise.front-AlbX2)/(AlbX1-AlbX2)));
   				wae[3] = tfuv[3] / 3.0 * (nbmaille_amont * ((Prise.front-AlbX2)/(AlbX1-AlbX2)));
   				wae[4] = tfuv[1] / 3.0 * (nbmaille_amont * (1.0 + ((AlbX3-Prise.front)/(AlbX3-AlbX2)) + ((AlbX1-Prise.front)/(AlbX1-AlbX2))));
   				wae[5] = tfuv[2] / 3.0 * (nbmaille_amont * (1.0 + ((AlbX3-Prise.front)/(AlbX3-AlbX2)) + ((AlbX1-Prise.front)/(AlbX1-AlbX2))));
   				wae[6] = tfuv[3] / 3.0 * (nbmaille_amont * (1.0 + ((AlbX3-Prise.front)/(AlbX3-AlbX2)) + ((AlbX1-Prise.front)/(AlbX1-AlbX2))));
   				wae[7] = tfuv[1] / 3.0 * (nbmaille_amont * ((Prise.front-AlbX2)/(AlbX3-AlbX2)));
   				wae[8] = tfuv[2] / 3.0 * (nbmaille_amont * ((Prise.front-AlbX2)/(AlbX3-AlbX2)));
   				wae[9] = tfuv[3] / 3.0 * (nbmaille_amont * ((Prise.front-AlbX2)/(AlbX3-AlbX2)));
/*if (nbiter > 274)
	{
	if ((zh == 235)  || (zi == 235)  || (zj == 235))	
		{
		printf("f elem %d ",elem);
		printf("tfuv %lf %lf %lf ",tfuv[1],tfuv[2],tfuv[3]);
		printf("nb_m %lf ",nbmaille);
		printf("tfuv*nb_m %lf ",tfuv[2]*nbmaille/3);
		printf("wae %lf %lf %lf ",wae[2],wae[5],wae[8]);
		}
	}*/
  				/* Mise a jour du vecteur effort global*/
    				for ( zl = 1 ; zl <= 9 ; zl++ ) wasurf[yc(elem,zl)] += wae[zl];  				
				Structure.surface_drag = Structure.surface_drag + wae[1] + wae[4] + wae[7];
				pan = Surface[elem].type;
				panneau[pan].drag = panneau[pan].drag + wae[1] + wae[4] + wae[7];
				Surface[elem].panel_drag = Surface[elem].panel_drag + wae[1] + wae[4] + wae[7];
				Surface[elem].panel_dragxyz = Surface[elem].panel_dragxyz + sqrt(wae[1]*wae[1] + wae[2]*wae[2] + wae[3]*wae[3]) 
                                                                                          + sqrt(wae[4]*wae[4] + wae[5]*wae[5] + wae[6]*wae[6]) 
                                                                                          + sqrt(wae[7]*wae[7] + wae[8]*wae[8] + wae[9]*wae[9]);
    				}
			else if ((AlbX1 >= Prise.front) && (AlbX2 >= Prise.front) && (AlbX3 < Prise.front))
  				{
  				/* surfaces partiellement a l arriere  du front : point 3 en amont du front
  				inter1 (inter2) est le point intersection du front avec le cote 31 (23) */
   				/* trainee sur un fil u et v du triangle elem.*/
				trainee_fil( elem, V, &tfuv[0]);
   				/* Nombre de mailles contenues dans le triangle de sommets 3, inter1 et inter2. */
				nbmaille = Surface[elem].nb_cote_u_ou_v;
				param1 = (AlbX3-Prise.front) / (AlbX3-AlbX1) ;    param2 = (AlbX3-Prise.front) / (AlbX3-AlbX2) ;
				nbmaille_amont = fabs( ( (1 - param1) * U3 + param1 * U1 - U3) * ( (1 - param2) * V3 + param2 * V2 - V3)
				                     - ( (1 - param1) * V3 + param1 * V1 - V3) * ( (1 - param2) * U3 + param2 * U2 - U3) );
   				/* Efforts aux 3 noeuds, sommets du triangle elem. */
   				wae[1] = tfuv[1] / 3.0 * (nbmaille_amont * ((Prise.front-AlbX3)/(AlbX1-AlbX3)));
   				wae[2] = tfuv[2] / 3.0 * (nbmaille_amont * ((Prise.front-AlbX3)/(AlbX1-AlbX3)));
   				wae[3] = tfuv[3] / 3.0 * (nbmaille_amont * ((Prise.front-AlbX3)/(AlbX1-AlbX3)));
   				wae[4] = tfuv[1] / 3.0 * (nbmaille_amont * ((Prise.front-AlbX3)/(AlbX2-AlbX3)));
   				wae[5] = tfuv[2] / 3.0 * (nbmaille_amont * ((Prise.front-AlbX3)/(AlbX2-AlbX3)));
   				wae[6] = tfuv[3] / 3.0 * (nbmaille_amont * ((Prise.front-AlbX3)/(AlbX2-AlbX3)));
   				wae[7] = tfuv[1] / 3.0 * (nbmaille_amont * (1.0 + ((AlbX1-Prise.front)/(AlbX1-AlbX3)) + ((AlbX2-Prise.front)/(AlbX2-AlbX3))));
   				wae[8] = tfuv[2] / 3.0 * (nbmaille_amont * (1.0 + ((AlbX1-Prise.front)/(AlbX1-AlbX3)) + ((AlbX2-Prise.front)/(AlbX2-AlbX3))));
   				wae[9] = tfuv[3] / 3.0 * (nbmaille_amont * (1.0 + ((AlbX1-Prise.front)/(AlbX1-AlbX3)) + ((AlbX2-Prise.front)/(AlbX2-AlbX3))));
				/* Mise a jour du vecteur effort global */
    				for ( zl = 1 ; zl <= 9 ; zl++ ) wasurf[yc(elem,zl)] += wae[zl];		
				Structure.surface_drag = Structure.surface_drag + wae[1] + wae[4] + wae[7];
				pan = Surface[elem].type;
				panneau[pan].drag = panneau[pan].drag + wae[1] + wae[4] + wae[7];
				Surface[elem].panel_drag = Surface[elem].panel_drag + wae[1] + wae[4] + wae[7];
				Surface[elem].panel_dragxyz = Surface[elem].panel_dragxyz + sqrt(wae[1]*wae[1] + wae[2]*wae[2] + wae[3]*wae[3]) 
                                                                                          + sqrt(wae[4]*wae[4] + wae[5]*wae[5] + wae[6]*wae[6]) 
                                                                                          + sqrt(wae[7]*wae[7] + wae[8]*wae[8] + wae[9]*wae[9]);
/*if (nbiter > 274)
	{
	if ((zh == 235)  || (zi == 235)  || (zj == 235))	
		{
		printf("g elem %d ",elem);
		printf("tfuv %lf %lf %lf ",tfuv[1],tfuv[2],tfuv[3]);
		printf("nb_m %lf ",nbmaille);
		printf("tfuv*nb_m %lf ",tfuv[2]*nbmaille/3);
		printf("wae %lf %lf %lf ",wae[2],wae[5],wae[8]);
		}
	}*/
    				}
  			}
  			}
		}
		
  	/*
  	for ( pan = 1 ; pan <= 14 ; pan++ )
  		{
  		printf("pan %5d drag %lf \n",pan,panneau[pan].drag);
  		}
  	*/
		
		
	}
		
  	for ( elem = 1 ; elem <= NOMBRE_SURF_HEXA ; elem++ )
  		{
  		/*numeros des coordonnees selon x des sommets du triangle*/
  		zh = yc_hexa(elem,1);  zi = yc_hexa(elem,4);  zj = yc_hexa(elem,7);
  		
  		/*
  		coordonnees cartesiennes et filaires du triangle
  		*/
  		AlbX1 = wfcodend[zh  ];	AlbX2 = wfcodend[zi  ];	AlbX3 = wfcodend[zj  ];
  		AlbZ1 = wfcodend[zh+2];	AlbZ2 = wfcodend[zi+2];	AlbZ3 = wfcodend[zj+2];
  		U1 = Surf_Hexa[elem].lon[1] ; V1 = Surf_Hexa[elem].lon[2] ;
  		U2 = Surf_Hexa[elem].lon[3] ; V2 = Surf_Hexa[elem].lon[4] ;
  		U3 = Surf_Hexa[elem].lon[5] ; V3 = Surf_Hexa[elem].lon[6] ;

   		/*
   		ne traiter que les surfaces en partie sous la surface libre
   		*/
   		if ((AlbZ1 <= 0.0) || (AlbZ2 <= 0.0 ) || (AlbZ3 <= 0.0 ))
		{
  		/*
  		ne traiter que les surfaces a l avant ou en partie a l avant du front
  		*/
  		if ((AlbX1 < Prise.front) || (AlbX2 < Prise.front) || (AlbX3 < Prise.front))
  			{
  			
  			for ( zl = 1 ; zl <= 9 ; zl++ ) wae[zl] = 0.0;  				
			
			/*surfaces totalement a l avant  du front*/
  			if ((AlbX1 <= Prise.front) && (AlbX2 <= Prise.front) && (AlbX3 <= Prise.front))
  				{  
   				/* Efforts aux 3 noeuds, sommets du triangle.*/
  				eff_hexa1(elem);

				/* Mise a jour du vecteur effort global*/
    				for (zl = 1; zl <= 9; zl++) 
    					{
    					 wasurf[yc_hexa(elem,zl)] += EN[zl];  				
    					 wasurf[yc_hexa(elem,zl)] += ET[zl];
    					}  				
				Structure.surface_drag = Structure.surface_drag + EN[1] + EN[4] + EN[7] + ET[1] + ET[4] + ET[7];
    				}
  			/* 
  			surfaces partiellement a l avant  du front : point 1 en aval du front
  			inter1 (inter2) est le point intersection du front avec le cote 12 (31) 
  			*/
			else if ((AlbX1 >= Prise.front) && (AlbX2 < Prise.front) && (AlbX3 < Prise.front))
  				{
  				/*printf("elem 1avl = %5d \n",elem);*/
   				/* Efforts  aux 3 noeuds, sommets du triangle elem.*/
  				eff_hexa1(elem);
    				for (zl = 1; zl <= 9; zl++) 
    					{
    					wae[zl]  = EN[zl];  				
    					wae[zl] += ET[zl];
    					}  				

				/* Nombre de maille par point du triangle de sommets 1, inter1 et inter2. */
				nbmaille = Surf_Hexa[elem].nb_cote_l_m_ou_n;
				param1 = (AlbX1-Prise.front) / (AlbX1-AlbX2) ; param2 = (AlbX1-Prise.front) / (AlbX1-AlbX3) ;
				Surf_Hexa[elem].nb_cote_l_m_ou_n = fabs( ( (1 - param1) * U1 + param1 * U2 - U1) * ((1 - param2) * V1 + param2 * V3 - V1)
				                                   - ( (1 - param1) * V1 + param1 * V2 - V1) * ((1 - param2) * U1 + param2 * U3 - U1) );
				eff_hexa1(elem);
				
   				/* Efforts aux 3 noeuds, sommets du triangle .*/
  					wae[3] = wae[3] - (EN[6]+ET[6]) * ((AlbX1-Prise.front)/(AlbX1-AlbX2)) - (EN[9]+ET[9]) * ((AlbX1-Prise.front)/(AlbX1-AlbX3));
  					wae[2] = wae[2] - (EN[5]+ET[5]) * ((AlbX1-Prise.front)/(AlbX1-AlbX2)) - (EN[8]+ET[8]) * ((AlbX1-Prise.front)/(AlbX1-AlbX3));
  					wae[1] = wae[1] - (EN[4]+ET[4]) * ((AlbX1-Prise.front)/(AlbX1-AlbX2)) - (EN[7]+ET[7]) * ((AlbX1-Prise.front)/(AlbX1-AlbX3));
  					wae[6] = wae[6] - (EN[6]+ET[6]) * ((AlbX1-Prise.front)/(AlbX1-AlbX2));
  					wae[5] = wae[5] - (EN[5]+ET[5]) * ((AlbX1-Prise.front)/(AlbX1-AlbX2));
  					wae[4] = wae[4] - (EN[4]+ET[4]) * ((AlbX1-Prise.front)/(AlbX1-AlbX2));
  					wae[9] = wae[9] - (EN[9]+ET[9]) * ((AlbX1-Prise.front)/(AlbX1-AlbX3));
  					wae[8] = wae[8] - (EN[8]+ET[8]) * ((AlbX1-Prise.front)/(AlbX1-AlbX3));
  					wae[7] = wae[7] - (EN[7]+ET[7]) * ((AlbX1-Prise.front)/(AlbX1-AlbX3));

				/* Mise a jour du vecteur effort global*/
    				for ( zl = 1; zl <= 9; zl++ ) wasurf[yc_hexa(elem,zl)] += wae[zl];  				
    				/* Restauration de Surf_Hexa[elem].nb_cote_l_m_ou_n. */
    				Surf_Hexa[elem].nb_cote_l_m_ou_n = nbmaille; 
				Structure.surface_drag = Structure.surface_drag + wae[1] + wae[4] + wae[7];
    				}
  			/* surfaces partiellement a l avant  du front : point 2 en aval du front
  			inter1 (inter2) est le point intersection du front avec le cote 23 (12)
  			on calcule le volume en amont que l on retranche au volume dy cylindre de section triangulaire*/
			else if ((AlbX1 < Prise.front) && (AlbX2 >= Prise.front) && (AlbX3 < Prise.front))
  				{
   				/* Efforts  aux 3 noeuds, sommets du triangle.*/
  				eff_hexa1(elem);
    				for ( zl = 1 ; zl <= 9 ; zl++ ) 
    					{
    					 wae[zl] = EN[zl];  				
    					 wae[zl] += ET[zl];
    					}  				
				
				/* Nombre de maille du triangle de sommets 2, inter1 et inter2. */
				nbmaille = Surf_Hexa[elem].nb_cote_l_m_ou_n;
				param1 = (AlbX2-Prise.front) / (AlbX2-AlbX3) ; param2 = (AlbX2-Prise.front) / (AlbX2-AlbX1) ;
				Surf_Hexa[elem].nb_cote_l_m_ou_n = fabs( ( (1 - param1) * U2 + param1 * U3 - U2) * ( (1 - param2) * V2 + param2 * V1 - V2)
				                                   - ( (1 - param1) * V2 + param1 * V3 - V2) * ( (1 - param2) * U2 + param2 * U1 - U2) );
				eff_hexa1(elem);
				
				/* Efforts aux 3 noeuds, sommets du triangle .*/
  					wae[6] = wae[6] - (EN[9]+ET[9]) * ((AlbX2-Prise.front)/(AlbX2-AlbX3)) - (EN[3]+ET[3]) * ((AlbX2-Prise.front)/(AlbX2-AlbX1));
  					wae[5] = wae[5] - (EN[8]+ET[8]) * ((AlbX2-Prise.front)/(AlbX2-AlbX3)) - (EN[2]+ET[2]) * ((AlbX2-Prise.front)/(AlbX2-AlbX1));
  					wae[4] = wae[4] - (EN[7]+ET[7]) * ((AlbX2-Prise.front)/(AlbX2-AlbX3)) - (EN[1]+ET[1]) * ((AlbX2-Prise.front)/(AlbX2-AlbX1));
  					wae[9] = wae[9] - (EN[9]+ET[9]) * ((AlbX2-Prise.front)/(AlbX2-AlbX3));
  					wae[8] = wae[8] - (EN[8]+ET[8]) * ((AlbX2-Prise.front)/(AlbX2-AlbX3));
  					wae[7] = wae[7] - (EN[7]+ET[7]) * ((AlbX2-Prise.front)/(AlbX2-AlbX3));
  					wae[3] = wae[3] - (EN[3]+ET[3]) * ((AlbX2-Prise.front)/(AlbX2-AlbX1));
  					wae[2] = wae[2] - (EN[2]+ET[2]) * ((AlbX2-Prise.front)/(AlbX2-AlbX1));
  					wae[1] = wae[1] - (EN[1]+ET[1]) * ((AlbX2-Prise.front)/(AlbX2-AlbX1));

				/* Mise a jour du vecteur effort global*/
    				for ( zl = 1 ; zl <= 9 ; zl++ ) wasurf[yc_hexa(elem,zl)] += wae[zl];  				
    				/* Restauration de Surf_Hexa[elem].nb_cote_l_m_ou_n. */
    				Surf_Hexa[elem].nb_cote_l_m_ou_n = nbmaille; 
				Structure.surface_drag = Structure.surface_drag + wae[1] + wae[4] + wae[7];
    				}
  			/* surfaces partiellement a l avant du front : point 3 en aval du front
  			inter1 (inter2) est le point intersection du front avec le cote 31 (23) */
			else if ((AlbX1 < Prise.front) && (AlbX2 < Prise.front) && (AlbX3 >= Prise.front))
  				{
   				/* Efforts  aux 3 noeuds, sommets du triangle.*/
  				eff_hexa1(elem);
    				for ( zl = 1 ; zl <= 9 ; zl++ ) 
    					{
    					 wae[zl] = EN[zl];  				
    					 wae[zl] += ET[zl];
    					}  				
				
				/* Nombre de maille du triangle de sommets 3, inter1 et inter2. */
				nbmaille = Surf_Hexa[elem].nb_cote_l_m_ou_n;
				param1 = (AlbX3-Prise.front) / (AlbX3-AlbX1) ;    param2 = (AlbX3-Prise.front) / (AlbX3-AlbX2) ;
				Surf_Hexa[elem].nb_cote_l_m_ou_n = fabs( ( (1 - param1) * U3 + param1 * U1 - U3) * ( (1 -param2) * V3 + param2 * V2 - V3)
				                                   - ( (1 - param1) * V3 + param1 * V1 - V3) * ( (1 -param2) * U3 + param2 * U2 - U3) );
				eff_hexa1(elem);

   				/* Efforts aux 3 noeuds, sommets du triangle .*/
  					wae[9] = wae[9] - (EN[3]+ET[3]) * ((AlbX3-Prise.front)/(AlbX3-AlbX1)) - (EN[6]+ET[6]) * ((AlbX3-Prise.front)/(AlbX3-AlbX2));
  					wae[8] = wae[8] - (EN[2]+ET[2]) * ((AlbX3-Prise.front)/(AlbX3-AlbX1)) - (EN[5]+ET[5]) * ((AlbX3-Prise.front)/(AlbX3-AlbX2));
  					wae[7] = wae[7] - (EN[1]+ET[1]) * ((AlbX3-Prise.front)/(AlbX3-AlbX1)) - (EN[4]+ET[4]) * ((AlbX3-Prise.front)/(AlbX3-AlbX2));
  					wae[3] = wae[3] - (EN[3]+ET[3]) * ((AlbX3-Prise.front)/(AlbX3-AlbX1));
  					wae[2] = wae[2] - (EN[2]+ET[2]) * ((AlbX3-Prise.front)/(AlbX3-AlbX1));
  					wae[1] = wae[1] - (EN[1]+ET[1]) * ((AlbX3-Prise.front)/(AlbX3-AlbX1));
  					wae[6] = wae[6] - (EN[6]+ET[6]) * ((AlbX3-Prise.front)/(AlbX3-AlbX2));
  					wae[5] = wae[5] - (EN[5]+ET[5]) * ((AlbX3-Prise.front)/(AlbX3-AlbX2));
  					wae[4] = wae[4] - (EN[4]+ET[4]) * ((AlbX3-Prise.front)/(AlbX3-AlbX2));

				/* Mise a jour du vecteur effort global*/
    				for ( zl = 1 ; zl <= 9 ; zl++ ) wasurf[yc_hexa(elem,zl)] += wae[zl];  				
    				/* Restauration de Surf_Hexa[elem].nb_cote_l_m_ou_n. */
    				Surf_Hexa[elem].nb_cote_l_m_ou_n = nbmaille; 
				Structure.surface_drag = Structure.surface_drag + wae[1] + wae[4] + wae[7];
    				}
  			/* surfaces partiellement a l arriere  du front : point 1 en amont du front
  			inter1 (inter2) est le point intersection du front avec le cote 12 (31)*/
			else if ((AlbX1 < Prise.front) && (AlbX2 >= Prise.front) && (AlbX3 >= Prise.front))
  				{
   				/* Nombre de mailles contenues dans le triangle amont de sommets1, inter1 et inter2.*/
				nbmaille = Surf_Hexa[elem].nb_cote_l_m_ou_n;
   				param1 = (AlbX1-Prise.front) / (AlbX1-AlbX2) ;    param2 = (AlbX1-Prise.front) / (AlbX1-AlbX3) ;
				Surf_Hexa[elem].nb_cote_l_m_ou_n = fabs( ( (1 - param1) * U1 + param1 * U2 - U1) * ( (1 - param2) * V1 + param2 * V3 - V1)
				                                   - ( (1 - param1) * V1 + param1 * V2 - V1) * ( (1 - param2) * U1 + param2 * U3 - U1) );
  				eff_hexa1(elem);
   				/* Efforts aux 3 noeuds, sommets du triangle amont. */
   				for( zl = 1 ; zl <= 9 ; zl++ ) 
   					{
   					 wae[zl]  = EN[zl];
   					 wae[zl] += ET[zl];
   					}
   				/* Efforts aux 3 noeuds, sommets du triangle elem. */
   					wae[3] = wae[3] +  wae[6] * ((AlbX1-Prise.front)/(AlbX1-AlbX2)) + wae[9] * ((AlbX1-Prise.front)/(AlbX1-AlbX3));
   					wae[2] = wae[2] +  wae[5] * ((AlbX1-Prise.front)/(AlbX1-AlbX2)) + wae[8] * ((AlbX1-Prise.front)/(AlbX1-AlbX3));
   					wae[1] = wae[1] +  wae[4] * ((AlbX1-Prise.front)/(AlbX1-AlbX2)) + wae[7] * ((AlbX1-Prise.front)/(AlbX1-AlbX3));
   					wae[6] = wae[6] * ((AlbX1-Prise.front)/(AlbX1-AlbX2));
   					wae[5] = wae[5] * ((AlbX1-Prise.front)/(AlbX1-AlbX2));
   					wae[4] = wae[4] * ((AlbX1-Prise.front)/(AlbX1-AlbX2));
   					wae[9] = wae[9] * ((AlbX1-Prise.front)/(AlbX1-AlbX2));
   					wae[8] = wae[8] * ((AlbX1-Prise.front)/(AlbX1-AlbX2));
   					wae[7] = wae[7] * ((AlbX1-Prise.front)/(AlbX1-AlbX2));

				/* Mise a jour du vecteur effort global */
    				for ( zl = 1 ; zl <= 9 ; zl++ ) wasurf[yc_hexa(elem,zl)] += wae[zl];  				
    				/* Restauration de Surf_Hexa[elem].nb_cote_l_m_ou_n. */
    				Surf_Hexa[elem].nb_cote_l_m_ou_n = nbmaille; 
				Structure.surface_drag = Structure.surface_drag + wae[1] + wae[4] + wae[7];
    				}
    				
  			/* surfaces partiellement a l arriere  du front : point 2 en amont du front
  			inter1 (inter2) est le point intersection du front avec le cote 23 (12) */
			else if ((AlbX1 >= Prise.front) && (AlbX2 < Prise.front) && (AlbX3 >= Prise.front))
  				{
   				/* Nombre de mailles contenues dans le triangle de sommets 2, inter1 et inter2. */
				nbmaille = Surf_Hexa[elem].nb_cote_l_m_ou_n;
				param1 = (AlbX2-Prise.front) / (AlbX2-AlbX3) ;    param2 = (AlbX2-Prise.front) / (AlbX2-AlbX1) ;
				Surf_Hexa[elem].nb_cote_l_m_ou_n = fabs( ( (1 - param1) * U2 + param1 * U3 - U2) * ( (1 - param2) * V2 + param2 * V1 - V2)
				                                   - ( (1 - param1) * V2 + param1 * V3 - V2) * ( (1 - param2) * U2 + param2 * U1 - U2) );
  				eff_hexa1(elem);
   				/* Efforts aux 3 noeuds, sommets du triangle amont. */
   				for( zl = 1 ; zl <= 9 ; zl++ ) 
   					{
   					 wae[zl] = EN[zl];
   					 wae[zl] += ET[zl];
   					}
   				/* Efforts aux 3 noeuds, sommets du triangle elem. */
   					wae[6] = wae[6] +  wae[9] * ((AlbX2-Prise.front)/(AlbX2-AlbX3)) + wae[3] * ((AlbX2-Prise.front)/(AlbX2-AlbX1));
   					wae[5] = wae[5] +  wae[8] * ((AlbX2-Prise.front)/(AlbX2-AlbX3)) + wae[2] * ((AlbX2-Prise.front)/(AlbX2-AlbX1));
   					wae[4] = wae[4] +  wae[7] * ((AlbX2-Prise.front)/(AlbX2-AlbX3)) + wae[1] * ((AlbX2-Prise.front)/(AlbX2-AlbX1));
   					wae[9] = wae[9] * ((AlbX2-Prise.front)/(AlbX2-AlbX3));
   					wae[8] = wae[8] * ((AlbX2-Prise.front)/(AlbX2-AlbX3));
   					wae[7] = wae[7] * ((AlbX2-Prise.front)/(AlbX2-AlbX3));
   					wae[3] = wae[3] * ((AlbX2-Prise.front)/(AlbX2-AlbX1));
   					wae[2] = wae[2] * ((AlbX2-Prise.front)/(AlbX2-AlbX1));
   					wae[1] = wae[1] * ((AlbX2-Prise.front)/(AlbX2-AlbX1));

  				/* Mise a jour du vecteur effort global*/
    				for ( zl = 1 ; zl <= 9 ; zl++ ) wasurf[yc_hexa(elem,zl)] += wae[zl];  				
    				
    				/* Restauration de Surf_Hexa[elem].nb_cote_l_m_ou_n. */
    				Surf_Hexa[elem].nb_cote_l_m_ou_n = nbmaille; 
				Structure.surface_drag = Structure.surface_drag + wae[1] + wae[4] + wae[7];
    				}
  			/* surfaces partiellement a l arriere  du front : point 3 en amont du front
  			inter1 (inter2) est le point intersection du front avec le cote 31 (23) */
			else if ((AlbX1 >= Prise.front) && (AlbX2 >= Prise.front) && (AlbX3 < Prise.front))
  				{
   				/* Nombre de mailles contenues dans le triangle de sommets 3, inter1 et inter2. */
				nbmaille = Surf_Hexa[elem].nb_cote_l_m_ou_n;
				param1 = (AlbX3-Prise.front) / (AlbX3-AlbX1) ;    param2 = (AlbX3-Prise.front) / (AlbX3-AlbX2) ;
				Surf_Hexa[elem].nb_cote_l_m_ou_n = fabs( ( (1 - param1) * U3 + param1 * U1 - U3) * ( (1 - param2) * V3 + param2 * V2 - V3)
				                                   - ( (1 - param1) * V3 + param1 * V1 - V3) * ( (1 - param2) * U3 + param2 * U2 - U3) );
  				eff_hexa1(elem);

   				/* Efforts aux 3 noeuds, sommets du triangle amont. */
   				for( zl = 1 ; zl <= 9 ; zl++ ) 
   					{
   					 wae[zl] = EN[zl];
   					 wae[zl] += ET[zl];
   					}
   				/* Efforts aux 3 noeuds, sommets du triangle elem. */
   					wae[9] = wae[9] +  wae[3] * ((AlbX3-Prise.front)/(AlbX3-AlbX1)) + wae[6] * ((AlbX3-Prise.front)/(AlbX3-AlbX2));
   					wae[8] = wae[8] +  wae[2] * ((AlbX3-Prise.front)/(AlbX3-AlbX1)) + wae[5] * ((AlbX3-Prise.front)/(AlbX3-AlbX2));
   					wae[7] = wae[7] +  wae[1] * ((AlbX3-Prise.front)/(AlbX3-AlbX1)) + wae[4] * ((AlbX3-Prise.front)/(AlbX3-AlbX2));
   					wae[3] = wae[3] * ((AlbX3-Prise.front)/(AlbX3-AlbX1));
   					wae[2] = wae[2] * ((AlbX3-Prise.front)/(AlbX3-AlbX1));
   					wae[1] = wae[1] * ((AlbX3-Prise.front)/(AlbX3-AlbX1));
   					wae[6] = wae[6] * ((AlbX3-Prise.front)/(AlbX3-AlbX2));
   					wae[5] = wae[5] * ((AlbX3-Prise.front)/(AlbX3-AlbX2));
   					wae[4] = wae[4] * ((AlbX3-Prise.front)/(AlbX3-AlbX2));

				/* Mise a jour du vecteur effort global */
    				for ( zl = 1 ; zl <= 9 ; zl++ ) wasurf[yc_hexa(elem,zl)] += wae[zl];		

    				/* Restauration de Surf_Hexa[elem].nb_cote_l_m_ou_n. */
    				Surf_Hexa[elem].nb_cote_l_m_ou_n = nbmaille; 
				Structure.surface_drag = Structure.surface_drag + wae[1] + wae[4] + wae[7];
    				}
			/*
			printf("EFFORTS de TRAINEE :\n ");
			for ( i = 1 ; i <= 9 ; i++ ) printf("composante %d sur noeud %d : %lf\n",i,i/3+1,wae[i]);
			*/
  			}
		}
		}
	}
