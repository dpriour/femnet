#include "4c19.h"

void energy_bottom2()
	{
  	int zl,zc,zg,zh,zi;
  	int min_nbx,max_nbx,min_nby,max_nby;
  	int nb_segment_plus_x,nb_segment_moin_x,nb_segment_plus_y,nb_segment_moin_y;
  	double Cox1,Coy1,Coz1,Cox2,Coy2,Coz2,Dox1,Doy1,Doz1,Dox2,Doy2,Doz2;
  	double longueur_totale,longueur_coupee;
	double minx,maxx,miny,maxy,xplus,xmoins,yplus,ymoins;
	double x1,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12,x13,x14,x15,x16,x17,x18,x19,x20,x21,x22,x23,x24,x25,x26,x27,x28,x29,x30,x31,x32,x33,x34,x35,x36,x37,x38,x39,x40,x41,x42,x43,x44,x45,x46,x47,x48;
	double y1,y2,y3,y4,y5,y6,y7,y8,y9,y10,y11,y12,y13,y14,y15,y16,y17,y18,y19,y20,y21,y22,y23,y24,y25,y26,y27,y28,y29,y30,y31,y32,y33,y34,y35,y36,y37,y38,y39,y40,y41,y42,y43,y44,y45,y46,y47,y48;
	double z1,z2,z3,z4,z5,z6,z7,z8,z9,z10,z11,z12,z13,z14,z15,z16,z17,z18,z19,z20,z21,z22,z23,z24,z25,z26,z27,z28,z29,z30,z31,z32,z33,z34,z35,z36,z37,z38,z39,z40,z41,z42,z43,z44,z45,z46,z47,z48;
	double effort_H,deplacement,nrj;
		
  	for (zg = 1 ; zg<= NOMBRE_NOEUDS ; zg++) 
  		{
  		x1 = wf1[3*zg-2];	y1 = wf1[3*zg-1];	z1 = wf1[3*zg-0];
  		x2 = wf[3*zg-2];	y2 = wf[3*zg-1];	z2 = wf[3*zg-0];
		if ((whs[3*zg-0] == 1) && (z1 < wh[3*zg-0]) && (z2 < wh[3*zg-0]))
			{
			//the node is always in contact with bottom
			effort_H = (wh[3*zg-0] - z2) * Bottom.raideur * Bottom.coef_frottement;
			deplacement = sqrt((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1));		//total displacement
			nrj = effort_H * deplacement;					//total energy
			
	  		minx = x1;	if (minx > x2)	minx = x2;
	  		maxx = x1;	if (maxx < x2)	maxx = x2;
	  		minz = y1;	if (miny > y2)	miny = y2;
	  		maxz = y1;	if (maxy < y2)	maxy = y2;
			
	  		min_nbx = (int)floor(minx/Energy_bottom.step);
	  		max_nbx = (int)floor(maxx/Energy_bottom.step);
	  		min_nby = (int)floor(miny/Energy_bottom.step);
	  		max_nby = (int)floor(maxy/Energy_bottom.step);
			
			longueur_totale = deplacement;

			if ((nrj >0.0) && (longueur_totale > 0.0))
				{
				//exit(0);
				for (zl = min_nbx; zl<= max_nbx; zl++)
					{
					for (zc = min_nby; zc<= max_nby; zc++)
						{
						xplus = zl * Energy_bottom.step; 
						yplus = zc * Energy_bottom.step;
						xmoins = xplus + Energy_bottom.step;
						ymoins = yplus + Energy_bottom.step;
						
//printf("xplus %lf xmoins %lf yplus %lf ymoins %lf \n",xplus,xmoins,yplus,ymoins);
				
						nb_segment_plus_x =  cut_segment_plus_x(xplus, x1, y1, x2, y2, &x4 ,&y4, &x5 ,&y5);
//printf("anb %d x1 %lf x2 %lf y1 %lf y2 %lf \n",nb_segment_plus_x,x4,x5,y4,y5);
						if (nb_segment_plus_x == 1)
							{
							nb_segment_plus_y =  cut_segment_plus_y(yplus, y4, x4, y5, x5, &y10 ,&x10, &y11 ,&x11);
//printf("bnb %d x1 %lf x2 %lf y1 %lf y2 %lf \n",nb_segment_plus_y,x10,x11,y10,y11);
							if (nb_segment_plus_y == 1)
								{
								nb_segment_moin_x =  cut_segment_moin_x(xmoins, x10, y10, x11, y11, &x16 ,&y16, &x17 ,&y17);
//printf("cnb %d x1 %lf x2 %lf y1 %lf y2 %lf \n",nb_segment_moin_x,x16,x17,y16,y17);
								if (nb_segment_moin_x == 1)
									{
									nb_segment_moin_y =  cut_segment_moin_y(ymoins, y16, x16, y17, x17, &y22 ,&x22, &y23 ,&x23);
//printf("dnb %d x1 %lf x2 %lf y1 %lf y2 %lf \n",nb_segment_moin_y,x22,x23,y22,y23);
									if (nb_segment_moin_y == 1)
										{
										longueur_coupee = sqrt((x23-x22)*(x23-x22) + (z23-z22)*(z23-z22));
//printf("xplus %lf x1 %lf x2 %lf yplus %lf y1 %lf y2 %lf \n",xplus,x1,x2,yplus,y1,y2);
//printf("zg %d longueur_totale %lf longueur_coupee %lf nrj %lf \n",zg,longueur_totale,longueur_coupee,nrj);
//printf("zl %d zc %d longueur_coupee %lf \n",zl,zc,longueur_coupee);
										if ((nrj >0.0) && (longueur_coupee > 0.0))
											{
											zh = 0;
									   		do
										   		{
										   		zh++;
										   		}
									  		while ((zh <= Energy_bottom.nb_square) && ((zl != Energy_bottom.nbx[zh]) || (zc != Energy_bottom.nby[zh])));
									  		
									  		if (zh > Energy_bottom.nb_square)
									  			{
											 	Energy_bottom.nb_square++;

												Energy_bottom.nrj = (double *) realloc(Energy_bottom.nrj, (1 + Energy_bottom.nb_square) * sizeof(double));
												Energy_bottom.nbx = (int *) realloc(Energy_bottom.nbx, (1 + Energy_bottom.nb_square) * sizeof(int));
												Energy_bottom.nby = (int *) realloc(Energy_bottom.nby, (1 + Energy_bottom.nb_square) * sizeof(int));

												Energy_bottom.nbx[Energy_bottom.nb_square] = zl;
												Energy_bottom.nby[Energy_bottom.nb_square] = zc;
												Energy_bottom.nrj[Energy_bottom.nb_square] = longueur_coupee/longueur_totale*nrj;
												//printf("nb_square %d\n",Energy_bottom.nb_square);
												/*
												if (Energy_bottom.nb_square >48) 
													{
													for (zi = 1; zi<= Energy_bottom.nb_square; zi++)
														{
														printf("nbx %d ",Energy_bottom.nbx[zi]);
														printf("nby %d ",Energy_bottom.nby[zi]);
														printf("nrj %lf \n",Energy_bottom.nrj[zi]);

														}
													exit(0);
													}*/
									  			}
									  		else
									  			{
												Energy_bottom.nbx[zh] = zl;
												Energy_bottom.nby[zh] = zc;
												Energy_bottom.nrj[zh] += longueur_coupee/longueur_totale*nrj;
												//printf("mb_square %d\n",Energy_bottom.nb_square);
									  			}
									  			
									  			
									  			
											}
										
										}
									}
								}
							}
						}
					}
				}
  			}
  		}
  	}

