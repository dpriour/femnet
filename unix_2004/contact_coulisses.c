#define PRINCIPAL 0
#include "4c19.h"

void contact_coulisses()
{
	/* 
	Calcul des efforts en chaque noeud issus du contact entre des noeuds successifs
	si la distance entre 2 oeuds successifs est < 2 diametres de coulisse (pouquoi pas?)
	en fait on espere que cet effort va empecher certaine difficulte de convergence
	qui semble-t-il apparaisse lorsque 2 noeud consecutifs se rapprochent de trop
	par exemple de moins d un millimetre alors que le bout accroche fait une boucle
	de plus d un metre.
	
	Il faudrait sans doute en toute rigueur (quand on aura le temps) tenir compte
	du diametre du bout accroche a la coulisse et non du diametre de la coulisse
	*/
  	int zi,zj,noeud1,noeud2;
  	int co1,co2,co3,co4,co5,co6;
  	double dx,dy,dz,effort,contact,k11,k12,k13,k22,k23,k33,Dist,Diam,Raid,Dist3;
  
  	for (zi = 1 ; zi<= NOMBRE_COULISSES ; zi++)
  	{
    		for (zj = 1 ; zj<= Coulisse[zi].nb_noeud + 1; zj++) 
    		{
    			/*calcul des efforts aux noeuds*/
    			if (zj == 1) noeud1 = Coulisse[zi].extremite[1];
    			if (zj != 1) noeud1 = Coulisse[zi].noeud[zj-1];
    			if (zj != Coulisse[zi].nb_noeud + 1) noeud2 = Coulisse[zi].noeud[zj];
    			if (zj == Coulisse[zi].nb_noeud + 1) noeud2 = Coulisse[zi].extremite[2];
    			
    			/*numeros des coordonnees des 2 points noeud1 et noeud2*/
    			co1 = 3*noeud1-2;	co2 = 3*noeud1-1;	co3 = 3*noeud1-0;
    			co4 = 3*noeud2-2;	co5 = 3*noeud2-1;	co6 = 3*noeud2-0;
    			
    			dx = wf[co4]-wf[co1];	dy = wf[co5]-wf[co2];	dz = wf[co6]-wf[co3];
    			Coulisse[zi].longueur[zj] = sqrt(dx*dx + dy*dy + dz*dz);
    			
    			if (Coulisse[zi].longueur[zj] < 2.0 * Coulisse[zi].diametrehydro)
    			{
    				/*dans ce cas il y a contact entre les extremites du segment zj*/
    				Dist = Coulisse[zi].longueur[zj];
    				Dist3 = Dist*Dist*Dist;
    				Diam = Coulisse[zi].diametrehydro;
    				Raid = Coulisse[zi].raideur_traction;
    				
    				/*calcul des efforts*/
    				contact = 2.0 * Diam - Dist;
    				effort = Raid * contact / (2.0 * Diam);
     				waelem[co1] -= dx/Dist*effort;	waelem[co2] -= dy/Dist*effort;	waelem[co3] -= dz/Dist*effort;
    				waelem[co4] += dx/Dist*effort;	waelem[co5] += dy/Dist*effort;	waelem[co6] += dz/Dist*effort;
/*
printf("coulisse = %5d \n",zi);
printf("segment = %5d \n",zj);
printf("contact = %lf \n",contact);
printf("effort = %lf \n",effort);
printf("noeud1 = %lf %lf %lf \n",wf[co1],wf[co2],wf[co3]);
printf("noeud2 = %lf %lf %lf \n",wf[co4],wf[co5],wf[co6]);
printf("effort selon x au noeud1 = %lf \n",-dx/Dist*effort);
*/

				/*calcul des raideurs*/
				k11 = (-1.0/Dist+0.5/Diam+dx*dx/Dist3)*Raid;
				k22 = (-1.0/Dist+0.5/Diam+dy*dy/Dist3)*Raid;
				k33 = (-1.0/Dist+0.5/Diam+dz*dz/Dist3)*Raid;
				k12 = dx/Dist3*dy*Raid;
				k13 = dx/Dist3*dz*Raid;
				k23 = dy/Dist3*dz*Raid;
    				/*raideur[coord2][coord1] equivalent a ze[coord2][eca-coord2+coord1]*/
				if (Structure.type_solver == 1)
				{
					ze[co1][eca-co1+co1] += k11;	ze[co1][eca-co1+co2] += k12;	ze[co1][eca-co1+co3] += k13;
					ze[co1][eca-co1+co4] -= k11;	ze[co1][eca-co1+co5] -= k12;	ze[co1][eca-co1+co6] -= k13;
					
					ze[co2][eca-co2+co1] += k12;	ze[co2][eca-co2+co2] += k22;	ze[co2][eca-co2+co3] += k23;
					ze[co2][eca-co2+co4] -= k12;	ze[co2][eca-co2+co5] -= k22;	ze[co2][eca-co2+co6] -= k23;
	
					ze[co3][eca-co3+co1] += k13;	ze[co3][eca-co3+co2] += k23;	ze[co3][eca-co3+co3] += k33;
					ze[co3][eca-co3+co4] -= k13;	ze[co3][eca-co3+co5] -= k23;	ze[co3][eca-co3+co6] -= k33;
					
					ze[co4][eca-co4+co1] -= k11;	ze[co4][eca-co4+co2] -= k12;	ze[co4][eca-co4+co3] -= k13;
					ze[co4][eca-co4+co4] += k11;	ze[co4][eca-co4+co5] += k12;	ze[co4][eca-co4+co6] += k13;
						
					ze[co5][eca-co5+co1] -= k12;	ze[co5][eca-co5+co2] -= k22;	ze[co5][eca-co5+co3] -= k23;
					ze[co5][eca-co5+co4] += k12;	ze[co5][eca-co5+co5] += k22;	ze[co5][eca-co5+co6] += k23;
	
					ze[co6][eca-co6+co1] -= k13;	ze[co6][eca-co6+co2] -= k23;	ze[co6][eca-co6+co3] -= k33;
					ze[co6][eca-co6+co4] += k13;	ze[co6][eca-co6+co5] += k23;	ze[co6][eca-co6+co6] += k33;
				}
				else if (Structure.type_solver == 2)
  		    		{
					affectation_pardiso(k11, co1, co1); //ze[co1][eca-co1+co1] += k11;
					affectation_pardiso(k12, co1, co2); //ze[co1][eca-co1+co2] += k12;	
					affectation_pardiso(k13, co1, co3); //ze[co1][eca-co1+co3] += k13;

					affectation_pardiso(-k11, co1, co4); //ze[co1][eca-co1+co4] -= k11;	
					affectation_pardiso(-k12, co1, co5); //ze[co1][eca-co1+co5] -= k12;	
					affectation_pardiso(-k13, co1, co6); //ze[co1][eca-co1+co6] -= k13;

					affectation_pardiso(k12, co2, co1); //ze[co2][eca-co2+co1] += k12;	
					affectation_pardiso(k22, co2, co2); //ze[co2][eca-co2+co2] += k22;	
					affectation_pardiso(k23, co2, co3); //ze[co2][eca-co2+co3] += k23;

					affectation_pardiso(-k12, co2, co4); //ze[co2][eca-co2+co4] -= k12;	
					affectation_pardiso(-k22, co2, co5); //ze[co2][eca-co2+co5] -= k22;	
					affectation_pardiso(-k23, co2, co6); //ze[co2][eca-co2+co6] -= k23;

					affectation_pardiso(k13, co3, co1); //ze[co3][eca-co3+co1] += k13;
					affectation_pardiso(k23, co3, co2); //ze[co3][eca-co3+co2] += k23;
					affectation_pardiso(k33, co3, co3); //ze[co3][eca-co3+co3] += k33;

					affectation_pardiso(-k13, co3, co4); //ze[co3][eca-co3+co4] -= k13;
					affectation_pardiso(-k23, co3, co5); //ze[co3][eca-co3+co5] -= k23;
					affectation_pardiso(-k33, co3, co6); //ze[co3][eca-co3+co6] -= k33;

					affectation_pardiso(-k11, co4, co1); //ze[co4][eca-co4+co1] -= k11;
					affectation_pardiso(-k12, co4, co2); //ze[co4][eca-co4+co2] -= k12;
					affectation_pardiso(-k13, co4, co3); //ze[co4][eca-co4+co3] -= k13;

					affectation_pardiso(k11, co4, co4); //ze[co4][eca-co4+co4] += k11;
					affectation_pardiso(k12, co4, co5); //ze[co4][eca-co4+co5] += k12;
					affectation_pardiso(k13, co4, co6); //ze[co4][eca-co4+co6] += k13;

					affectation_pardiso(-k12, co5, co1); //ze[co5][eca-co5+co1] -= k12;
					affectation_pardiso(-k22, co5, co2); //ze[co5][eca-co5+co2] -= k22;
					affectation_pardiso(-k23, co5, co3); //ze[co5][eca-co5+co3] -= k23;

					affectation_pardiso(k12, co5, co4); //ze[co5][eca-co5+co4] += k12;
					affectation_pardiso(k22, co5, co5); //ze[co5][eca-co5+co5] += k22;
					affectation_pardiso(k23, co5, co6); //ze[co5][eca-co5+co6] += k23;		

					affectation_pardiso(-k13, co6, co1); //ze[co6][eca-co6+co1] -= k13;
					affectation_pardiso(-k23, co6, co2); //ze[co6][eca-co6+co2] -= k23;
					affectation_pardiso(-k33, co6, co3); //ze[co6][eca-co6+co3] -= k33;

					affectation_pardiso(k13, co6, co4); //ze[co6][eca-co6+co4] += k13;
					affectation_pardiso(k23, co6, co5); //ze[co6][eca-co6+co5] += k23;
					affectation_pardiso(k33, co6, co6); //ze[co6][eca-co6+co6] += k33;
 		     		}
    			}
    		}
  	}
}

