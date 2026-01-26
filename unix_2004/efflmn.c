#define PRINCIPAL 0
#include "4c19.h"

void efflmn(int elem,double *VV,double *LMN,double longueur_repos)
	{
  	/* 
  	Calcul des vecteurs effort tangent et effort normal pour la direction LMN dans le triangle numero elem
     	Resultat dans l'espace. 
     	*/
     
  	/* LMN : Composantes selon X, Y et Z du vecteur LMN */  
  	/* VV : Composantes selon X, Y et Z du vecteur VV */
    
   	double theta1,R,Tx,Ty,Ny,Nx;

	/*printf(" Debut \n");  	
	printf(" VV = ");  	imprvectreel(3, VV);
 	printf(" LMN = ");  	imprvectreel(3, LMN);*/
 
	/* printf("calcul de alpha1 et beta1\n");  */
  	/* calcul des 2 angles de rotation alpha1/Z beta1/Y , pour travailler dans le plan contenant VV et LMN */
     	rota1(VV,LMN);
	/*printf(" alpha1 = %lf  beta1= %lf \n",alpha1,beta1);  */
    

  	/* Rotations de alpha1 et de beta1 des vecteurs VV et LMN  */   
     	base1(alpha1,3,beta1,2,3,VV);
     	base1(alpha1,3,beta1,2,3,LMN); 
  
  	/* Definition et rotation d'un angle alpha2 autour de Z pour avoir V parallele a l'axe des X et V positif */
     	if (VV[2] < 0.0) alpha2 =   acos(VV[1]/sqrt(VV[1]*VV[1] +VV[2]*VV[2]));   
     	if (VV[2] > 0.0) alpha2 = - acos(VV[1]/sqrt(VV[1]*VV[1] +VV[2]*VV[2]));
     	if (VV[2] == 0.0 && VV[1] >= 0.0) alpha2 = 0.0;
     	if (VV[2] == 0.0 && VV[1] <  0.0) alpha2 = PI;
    
	/*printf(" alpha2 = %lf   \n",alpha2/PI*180);  */
   
  	/* Rotations de alpha2 des vecteurs LMN, VV.
     	On travaille alors dans le plan defini X et Y, VV etant parallele a X */
     	base1(alpha2,3,0.0,3,3,LMN);
     	base1(alpha2,3,0.0,3,3,VV);
     	
 	/*printf(" VV = ");  	imprvectreel(3, VV);
 	printf(" LMN = ");  	imprvectreel(3, LMN);*/
  
  	/* Definition de l'angle theta1, entre la direction du vecteur VV et le vecteur LMN. */
     	if(LMN[1] != 0.0) theta1 =  atan(LMN[2]/LMN[1]);
     	if(LMN[1] == 0.0) theta1 = PI/4;
     	
	/*printf(" theta1 = %lf   \n",theta1/PI*180);  */
  
  	/* Definition des efforts, tangent et normal, pour un seul cote de maille, projetees sur X et Y,
     	appelees respectivement Tx, Ty, Nx, Ny */  
  
  	/* R = constante*/
  	/*ici on prend en compte l allongement des fils*/
	/* R = 0.5*RHO*Surf_Hexa[elem].cdnormal*Surf_Hexa[elem].diametrehydro*sqrt(longueur_repos/sqrt(LMN[1]*LMN[1]+LMN[2]*LMN[2])/2)*Courant.vitesse*Courant.vitesse*sqrt(LMN[1]*LMN[1]+LMN[2]*LMN[2])/2
   	;*/
  	/*ici on ne prend pas en compte l allongement des fils*/
     	R = 0.5*RHO*Surf_Hexa[elem].cdnormal*Surf_Hexa[elem].diametrehydro*Courant.vitesse*Courant.vitesse*longueur_repos ; 
     	
     	
/*****************************************************************************************************************************
ERREUR : on ne tient compte que du diametre des fils l !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!     	
*****************************************************************************************************************************/
     	
     	
     	
     	
     	R = 0.5*RHO*Surf_Hexa[elem].cdnormal*Surf_Hexa[elem].diam_hydro_l*Courant.vitesse*Courant.vitesse*longueur_repos ;  
	/*printf(" R = %lf   \n",R);  */
  
  	/* Calcul des directions des efforts, donnees dans les vecteurs ne et te*/
     	compos(VV,LMN);
 	/*imprvectreel(3, te);
 	imprvectreel(3, ne);*/
     
	/*printf("ftangent  = %lf   \n",Surf_Hexa[elem].ftangent);  */
     	Tx = R*Surf_Hexa[elem].ftangent*cos(theta1)*cos(theta1) * te[1];
     	Ty = R*Surf_Hexa[elem].ftangent*cos(theta1)*cos(theta1) * te[2];
     	Nx = R*sin(theta1)*sin(theta1) * ne[1];
     	Ny = R*sin(theta1)*sin(theta1) * ne[2];
  
  	/* Effort tangent et effort nomal applique sur le sommet 1 du triangle,
     	pour les fils de directions l, m ou n */
     
     	ETlmn[1] = Tx*Surf_Hexa[elem].nb_cote_l_m_ou_n/3.0;
     	ETlmn[2] = Ty*Surf_Hexa[elem].nb_cote_l_m_ou_n/3.0;
     	ETlmn[3] = 0.0;
  
     	ENlmn[1] = Nx*Surf_Hexa[elem].nb_cote_l_m_ou_n/3.0;
     	ENlmn[2] = Ny*Surf_Hexa[elem].nb_cote_l_m_ou_n/3.0;
     	ENlmn[3] = 0.0;

  	/* Effort tangent et effort nomal applique sur le sommet 2 du triangle,
     	pour les fils de directions l, m ou n */
    
     	ETlmn[4] = Tx*Surf_Hexa[elem].nb_cote_l_m_ou_n/3.0;
     	ETlmn[5] = Ty*Surf_Hexa[elem].nb_cote_l_m_ou_n/3.0;
     	ETlmn[6] = 0.0;

     	ENlmn[4] = Nx*Surf_Hexa[elem].nb_cote_l_m_ou_n/3.0;
     	ENlmn[5] = Ny*Surf_Hexa[elem].nb_cote_l_m_ou_n/3.0;
     	ENlmn[6] = 0.0;

 

  	/* Effort tangent et effort nomal applique sur le sommet 3 du triangle,
     	pour les fils de directions l, m ou n  */
    
     	ETlmn[7] = Tx*Surf_Hexa[elem].nb_cote_l_m_ou_n/3.0;
     	ETlmn[8] = Ty*Surf_Hexa[elem].nb_cote_l_m_ou_n/3.0;
     	ETlmn[9] = 0.0;
  
     	ENlmn[7] = Nx*Surf_Hexa[elem].nb_cote_l_m_ou_n/3.0;
     	ENlmn[8] = Ny*Surf_Hexa[elem].nb_cote_l_m_ou_n/3.0;
     	ENlmn[9] = 0.0;

 
  	/* On replace les efforts, ainsi que VV dans l'espace par des rotations opposees */
  
     	base1(-alpha2,3,0.0,3,9,ETlmn);
     	base1(-alpha2,3,0.0,3,9,ENlmn);
     	base1(-alpha2,3,0.0,3,3,VV);
     	base1(-beta1,2,-alpha1,3,9,ETlmn);
     	base1(-beta1,2,-alpha1,3,9,ENlmn);
     	base1(-beta1,2,-alpha1,3,3,VV);
}    
