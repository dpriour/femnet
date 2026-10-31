#include "4c19.h"

void actualiser_position(nomfichier)
char *nomfichier;
	{
  	int zi,zg,no3,no6,type,j,itmp,temp_int,pa,temp2_int, node,ecart,coordinate;
  	double vx,vy,vz,tmp_d2;
  	double alpha,R11,R12,R13,R21,R22,R23,R31,R32,R33,co,si;
  	double uu[4],vv[4],ww[4],tt[4],ntt,ss[4],radius,distance_linear;
 	char tonom[200];
	FILE *f3;
	
  	/* lorsque la position d equilibre dynamique a ete trouvee mise a jour des valeurs a t-1*/
 	/* wf1 : vecteur contenant les coordonnes des noeuds au temps t-1*/
 	/* mvb1 : vecteur contenant les vitesses des coordonnes des noeuds au temps t-1*/
   	for (zi = 1 ; zi<= 3*NOMBRE_NOEUDS; zi++) 
  		{
    		wf1[zi]  = wf[zi];
    		mvb1[zi] = mvb[zi];
  		}


   	if(Structure.speed_type_node == 1)
   		{
	  	//in case of modification of typenodespeed cf input speed_type_node node_type begining_times end_times beginning_vx end_vx beginning_vy end_vy beginning_vz end_vz 	
	  	if (Structure.nb_speed_type_node> 0)
	  		{
		   	for (zi = 1 ; zi<= NOMBRE_NOEUDS; zi++) 
		  		{
		  		type = Noeud[zi].type;
		  		if (TypeNoeud[type].beg_times > TypeNoeud[type].end_times)
		  			{
		    			printf("in speed_type_node begining times %lf must be < end times %lf\n",TypeNoeud[type].beg_times,TypeNoeud[type].end_times) ;
		    			exit(0);		
		  			}
		  		if (TypeNoeud[type].beg_times < TypeNoeud[type].end_times)
		  			{
			  		if ((times >=TypeNoeud[type].beg_times) && (times <=TypeNoeud[type].end_times))
			  			{
			  			vx = TypeNoeud[type].beg_vx + (times - TypeNoeud[type].beg_times) * (TypeNoeud[type].end_vx - TypeNoeud[type].beg_vx) / (TypeNoeud[type].end_times - TypeNoeud[type].beg_times);
		    				mvb[3*zi-2] = vx; 			
			    			wf[3*zi-2]  = wf1[3*zi-2] + mvb[3*zi-2] * Pascalcul;		//new position of the coordinate
				    		wl[3*zi-2] = 0;						//the coordinate is fixed
			  			vy = TypeNoeud[type].beg_vy + (times - TypeNoeud[type].beg_times) * (TypeNoeud[type].end_vy - TypeNoeud[type].beg_vy) / (TypeNoeud[type].end_times - TypeNoeud[type].beg_times);
		    				mvb[3*zi-1] = vy; 			
			    			wf[3*zi-1]  = wf1[3*zi-1] + mvb[3*zi-1] * Pascalcul;		//new position of the coordinate
				    		wl[3*zi-1] = 0;						//the coordinate is fixed
			  			vz = TypeNoeud[type].beg_vz + (times - TypeNoeud[type].beg_times) * (TypeNoeud[type].end_vz - TypeNoeud[type].beg_vz) / (TypeNoeud[type].end_times - TypeNoeud[type].beg_times);
		    				mvb[3*zi-0] = vz;
			    			wf[3*zi-0]  = wf1[3*zi-0] + mvb[3*zi-0] * Pascalcul;		//new position of the coordinate
				    		wl[3*zi-0] = 0;						//the coordinate is fixed
		    				//printf("vx %10.2lf vy %10.2lf vz %10.2lf\n",vx,vy,vz) ;			
		    				}
	    				}
		  		}
	  		}
  		}

   	if(Structure.speed_type_node == 2)
   		{
	  	//in case of modification of typenodespeed cf input speed_type_node2 node_type nb_times times1 timesi speedx1 speedxi speedy1 speedyi speedz1 speedzi  	
	   	for (zi = 1 ; zi<= NOMBRE_NOEUDS; zi++) 
	  		{
		  	type = Noeud[zi].type;
	  		if (TypeNoeud[type].nb_times >= 2)
	  			{
	      			for (zg=1;zg<=TypeNoeud[type].nb_times-1;zg++)
					{
					if ((times >= TypeNoeud[type].times[zg]) && (times <= TypeNoeud[type].times[zg+1]))
						{
						vx = TypeNoeud[type].speedx[zg]+ (TypeNoeud[type].speedx[zg+1]-TypeNoeud[type].speedx[zg])*(times-TypeNoeud[type].times[zg])/(TypeNoeud[type].times[zg+1]-TypeNoeud[type].times[zg]);
    						wf[3*zi-2]  = wf1[3*zi-2] + vx * Pascalcul;	//new position of the coordinate
		    				mvb[3*zi-2] = vx; 			
			    			//wf[3*zi-2]  = wf1[3*zi-2] + mvb[3*zi-2] * Pascalcul;		//new position of the coordinate
				    		wl[3*zi-2] = 0;						//the coordinate is fixed
						vy = TypeNoeud[type].speedy[zg]+ (TypeNoeud[type].speedy[zg+1]-TypeNoeud[type].speedy[zg])*(times-TypeNoeud[type].times[zg])/(TypeNoeud[type].times[zg+1]-TypeNoeud[type].times[zg]);
    						wf[3*zi-1]  = wf1[3*zi-1] + vy * Pascalcul;	//new position of the coordinate
		    				mvb[3*zi-1] = vy; 			
			    			//wf[3*zi-1]  = wf1[3*zi-1] + mvb[3*zi-1] * Pascalcul;		//new position of the coordinate
				    		wl[3*zi-1] = 0;						//the coordinate is fixed
						vz = TypeNoeud[type].speedz[zg]+ (TypeNoeud[type].speedz[zg+1]-TypeNoeud[type].speedz[zg])*(times-TypeNoeud[type].times[zg])/(TypeNoeud[type].times[zg+1]-TypeNoeud[type].times[zg]);
    						wf[3*zi-0]  = wf1[3*zi-0] + vz * Pascalcul;	//new position of the coordinate
		    				mvb[3*zi-0] = vz; 			
			    			//wf[3*zi-0]  = wf1[3*zi-0] + mvb[3*zi-0] * Pascalcul;		//new position of the coordinate
				    		wl[3*zi-0] = 0;						//the coordinate is fixed
		    				//printf("zi %d vx %10.2lf vy %10.2lf vz %10.2lf wf %10.2lf\n",zi,vx,vy,vz,wf[3*zi-2]) ;
		    				//exit(0);
		    				}
					}
				}
	  		}
  		}


   	if(Structure.speed_type_node == 4)
   		{
  		//in case the speed of few coordinates are given in *.fos
		strcpy(tonom,nomfichier);
		j=strlen(tonom);
		while ((tonom[j])!='.' && j>0) j--;
		if (tonom[j]=='.') tonom[j]=0;
	  	strcat(tonom,".fos");
		//printf("At each time step the file %s is read. This file give the speed of coordinates\n",tonom);
	  	f3 = fopen(tonom,"r");
		itmp = fscanf(f3,"%d",&temp_int);
		//printf("nb of coordinates %d\n",temp_int);
   		//exit(0);
		for (pa=1;pa<=temp_int;pa++)	
			{	
			itmp = fscanf(f3,"%d",&temp2_int);
			itmp = fscanf(f3,"%lf",&tmp_d2);
			
			/*
			if coordinate is 1 node is 1
			node = (int) floor((temp2_int + 2)/3); // node number
			ecart = 3*node - temp2_int;		//2 if along x, 1 if aloing y and 0 if along z
			coordinate  = 3*fixa[node] - ecart;	//coordinate number
			
			wf[3*fixa[int1]-3+int2]);
			
			*/
			node = (int) floor((temp2_int + 2)/3); // node number
			ecart = 3*node - temp2_int;		//2 if along x, 1 if along y and 0 if along z
			coordinate  = 3*fixa[node] - ecart;	//coordinate number
			//printf("node %d ecart %d coordinate %d speed %lf m/s\n",node, ecart, coordinate,tmp_d2);
			
    			wf[coordinate]  = wf1[coordinate] + tmp_d2 * Pascalcul;	//new position of the coordinate
	    		mvb[coordinate] = tmp_d2; 					//new speed of the coordinate
	    		wl[coordinate] = 0;						//the coordinate is fixed
			//printf("coordinate %d speed %lf m/s position %lf m\n",temp2_int,tmp_d2,wf[coordinate]);
			}
		fclose(f3);			
   		}
	}

