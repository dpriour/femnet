#define PRINCIPAL 0
#include "4c19.h"

int etat_convergence()
{
	/*
	estimation de l etat de la convergence et modification de la raideur
	additionnelle en consequence
	*/
	
  	int zi,zj;
  	double moyenne_RW[11],ecart_RW[11];
  	double moyenne_MW[11],ecart_MW[11];
  	double moyenne_RMEAN[11],ecart_RMEAN[11];
  	double moyenne_MMEAN[11],ecart_MMEAN[11],Numtemps_relax_sup,Numtemps_inf,Numtemps_sup;
  	double Moy1,Moy2,Moy3,Moy4,Ecar1,Ecar2,Ecar3,Ecar4;

    	Numtemps_relax_sup = 1000000000000.0;	/*valeur maximale de Numtemps_relax*/
    	Numtemps_sup = 1000000000000.0;		/*valeur maximale de Numtemps*/
    	Numtemps_inf = 0.1;			/*valeur minimale de Numtemps*/

	if (nbiter < 1000)
		{
		for ( zi = nbiter ; zi >= 2 ; zi-- )
			{
			/*
			etat_converg stocke les nbiter dernieres valeurs
			de RW MW RMEAN et MMEAN (valeurs des effort et deplacement max et moyen)
			*/
			etat_converg[zi][1] = etat_converg[zi-1][1];
			etat_converg[zi][2] = etat_converg[zi-1][2];
			etat_converg[zi][3] = etat_converg[zi-1][3];
			etat_converg[zi][4] = etat_converg[zi-1][4];
			}
		}
	else
		{
		for ( zi = 1000 ; zi >= 2 ; zi-- )
			{
			/*
			etat_converg stocke les 1000 dernieres valeurs
			de RW MW RMEAN et MMEAN (valeurs des effort et deplacement max et moyen)
			*/
			etat_converg[zi][1] = etat_converg[zi-1][1];
			etat_converg[zi][2] = etat_converg[zi-1][2];
			etat_converg[zi][3] = etat_converg[zi-1][3];
			etat_converg[zi][4] = etat_converg[zi-1][4];
			}
		}
	
	etat_converg[1][1] = RW;
	etat_converg[1][2] = MW;
	etat_converg[1][3] = RMEAN;
	etat_converg[1][4] = MMEAN;
	
	if (nbiter > 10)
	{
		/*
		chevrottement entre 2 valeurs
		Moy1  moyenne du max de deplacement sur les 7  dernieres et toutes les 2 
		Ecar1 ecart   du max de deplacement sur les 7  dernieres et toutes les 2 
		Moy2  moyenne du max de deplacement sur les 14 dernieres et toutes les 1 
		*/
		Moy1  = moyenne_convergence(2, 10, 2);
		Moy2  = moyenne_convergence(2, 20, 1);
		Ecar1 =   ecart_convergence(2, 10, 2);
		Ecar2 =   ecart_convergence(2, 20, 1);
		
		if ((fabs(Moy2-Moy1) > 2.0 * Ecar1) && (Numtemps < Numtemps_sup))
			{
			Numtemps_relax = Numtemps_relax * 1.1;
			}
		
		
		/*
		Trop grande variation : ecart est > a 4 moyenne du max
		Moy1  moyenne du max de deplacement sur les 15  dernieres et toutes les 1 
		Ecar1 ecart   du max de deplacement sur les 15  dernieres et toutes les 1 
		*/
		Moy1  = moyenne_convergence(2, 15, 1);
		Ecar1 =   ecart_convergence(2, 15, 1);
		
		if ((fabs(Moy1) < Ecar1 / 4.0) && (Numtemps < Numtemps_sup))
			{
			Numtemps_relax = Numtemps_relax * 1.1;
			}
		
		
		/*
		Trop grand deplacement : ecart est > a deplacement / 2
		Ecar1 ecart   du max de deplacement sur les 15  dernieres et toutes les 1 
		*/
		Ecar1 =   ecart_convergence(2, 15, 1);
		
		if ((Ecar1 > Deplacement / 2.0) && (Numtemps < Numtemps_sup))
			{
			Numtemps_relax = Numtemps_relax * 1.1;
			}
		
		
		/*
		convergence trop lente
		*/
		/*effort max trop stable*/
		Moy1  = moyenne_convergence(1, 20, 1);
		Ecar1 =   ecart_convergence(1, 20, 1);
		if (fabs(Moy1) > 4.0 * Ecar1)
			{
			/*deplacement max est faible relativement a deplacement*/
			Moy2  = moyenne_convergence(2, 20, 1);
			Ecar2 =   ecart_convergence(2, 20, 1);
			if (Deplacement - fabs(Moy2) > Ecar2)
				{
				/*effort moyen trop stable*/
				Moy3  = moyenne_convergence(3, 20, 1);
				Ecar3 =   ecart_convergence(3, 20, 1);
				if (fabs(Moy3) > 4.0 * Ecar3)
					{
					/*deplacement moyen trop stable*/
					Moy4  = moyenne_convergence(4, 20, 1);
					Ecar4 =   ecart_convergence(4, 20, 1);
					if (fabs(Moy4) > 4.0 * Ecar4)
						{
						/*raideur additionelle faible*/
						if (Numtemps > Numtemps_inf)
							{
							Numtemps_relax = Numtemps_relax * 0.9;
							}
						}
					}
				}
			}
	}
	/*if (Numtemps < 0.1 ) Numtemps = 0.1;*/
}


double moyenne_convergence(int variable,int nb_pris, int periode)
	{
	/*
	renvoie la moyenne de RW si variable = 1, MW si variable = 2, RMEAN si variable = 3 ou MMEAN si variable = 4
	la moyenne est calculee sur les derniere nb_pris valeurs, avec un pas de periode. Si periode = 1 l;a moyenne est calculee sur
	toutes les valeurs, si periode = 2 sur une valeurs sur deux, si periode = n sur 1/n valeurs. Periode permet alors de 
	detecter les vibrations
	*/
	int zi;
	double resultat;
	
	resultat = 0.0;
	for ( zi = 1 ; zi <= periode * nb_pris ; zi=zi+periode) resultat = resultat + etat_converg[zi][variable];
	resultat = resultat / nb_pris;
	return resultat;
	}


double ecart_convergence(int variable,int nb_pris, int periode)
	{
	/*
	renvoie l ecart type de RW si variable = 1, MW si variable = 2, RMEAN si variable = 3 ou MMEAN si variable = 4
	l ecart est calcule sur les derniere nb_pris valeurs, avec un pas de periode. Si periode = 1 l ecart est calcule sur
	toutes les valeurs, si periode = 2 sur une valeurs sur deux, si periode = n sur 1/n valeurs. Periode permet alors de 
	detecter les vibrations
	*/
	int zi;
	double resultat,moyenne;
	
	moyenne = moyenne_convergence( variable, nb_pris,  periode);
	resultat = 0.0;
	for ( zi = 1 ; zi <= periode * nb_pris ; zi=zi+periode) resultat = resultat + fabs(etat_converg[zi][variable] - moyenne);
	resultat = resultat / nb_pris;
	return resultat;
	}
