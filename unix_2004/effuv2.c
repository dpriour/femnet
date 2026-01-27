#define PRINCIPAL 0
#include "4c19.h"

void effuv(int elem, double *VV, double *NM)
	{
  	/* 
  	Calcul des vecteurs effort tangent et effort normal pour l ensemble des fils (ou cote de maille) de direction NM 
  	du triangle numero elem. On prend en compte la longueur du fil son diametre et les coefficients de trainee.
     	Resultat dans l'espace.
     	le resultat est dans les vecteurs ENuv et ETuv. 
     	ENuv pour l effort normal et ETuv pour l effort tangentiel.
     	la taille de ces vecteurs est 9 : 
     	ENuv[1] = effort selon x sur le sommet 1 de l effort normal
     	ENuv[2] = effort selon y sur le sommet 1 de l effort normal
     	ENuv[3] = effort selon z sur le sommet 1 de l effort normal
     	ENuv[4] = effort selon x sur le sommet 2 de l effort normal
     	ENuv[5] = effort selon y sur le sommet 2 de l effort normal
     	ENuv[6] = effort selon z sur le sommet 2 de l effort normal
     	ENuv[7] = effort selon x sur le sommet 3 de l effort normal
     	ENuv[8] = effort selon y sur le sommet 3 de l effort normal
     	ENuv[9] = effort selon z sur le sommet 3 de l effort normal

     	ETuv[1] = effort selon x sur le sommet 1 de l effort tangentiel
     	ETuv[2] = effort selon y sur le sommet 1 de l effort tangentiel
     	ETuv[3] = effort selon z sur le sommet 1 de l effort tangentiel
     	ETuv[4] = effort selon x sur le sommet 2 de l effort tangentiel
     	ETuv[5] = effort selon y sur le sommet 2 de l effort tangentiel
     	ETuv[6] = effort selon z sur le sommet 2 de l effort tangentiel
     	ETuv[7] = effort selon x sur le sommet 3 de l effort tangentiel
     	ETuv[8] = effort selon y sur le sommet 3 de l effort tangentiel
     	ETuv[9] = effort selon z sur le sommet 3 de l effort tangentiel

     	de la meme facon que le poids d un triangle est reparti uniformement entre les 3 sommets ici on a:
     	ENuv[1] = ENuv[4] = ENuv[7]
     	ENuv[2] = ENuv[5] = ENuv[8]
     	ENuv[3] = ENuv[6] = ENuv[9] idem pour ETuv

     	*/
     
  	/* NM : Composantes selon X, Y et Z du vecteur NM placees dans NM[1] NM[2] et NM[3]*/  
  	/* VV : Composantes selon X, Y et Z du vecteur VV placees dans VV[1] VV[2] et VV[3] */
    
   	double theta1,R,Tx,Ty,Ny,Nx;

if(elem == 1)
	{
	printf(" Debut \n");  	
	printf(" VV = ");  	imprvectreel(3, VV);
 	printf(" NM = ");  	imprvectreel(3, NM);
 	}
 
	/* printf("calcul de alpha1 et beta1\n");  */
  	/* calcul des 2 angles de rotation alpha1/Z beta1/Y , pour travailler dans le plan contenant VV et NM */
     	rota1(VV,NM);
/*if(elem == 1) printf(" alpha1 = %lf  beta1= %lf \n",alpha1,beta1); */
    

  	/* Rotations de alpha1 et de beta1 des vecteurs VV et NM  */   
     	base1(alpha1,3,beta1,2,3,VV);
     	base1(alpha1,3,beta1,2,3,NM); 
  
  	/* Definition et rotation d'un angle alpha2 autour de Z pour avoir V parallele a l'axe des X et V positif */
     	if (VV[2] < 0.0) alpha2 =   acos(VV[1]/sqrt(VV[1]*VV[1] +VV[2]*VV[2]));   
     	if (VV[2] > 0.0) alpha2 = - acos(VV[1]/sqrt(VV[1]*VV[1] +VV[2]*VV[2]));
     	if (VV[2] == 0.0 && VV[1] >= 0.0) alpha2 = 0.0;
     	if (VV[2] == 0.0 && VV[1] <  0.0) alpha2 = PI;
    
	/*printf(" alpha2 = %lf   \n",alpha2/PI*180);  */
   
  	/* Rotations de alpha2 des vecteurs NM, VV.
     	On travaille alors dans le plan defini X et Y, VV etant parallele a X */
     	base1(alpha2,3,0.0,3,3,NM);
     	base1(alpha2,3,0.0,3,3,VV);
     	
/*if(elem == 1)
	{
 	printf(" VV = ");  	imprvectreel(3, VV);
 	printf(" NM = ");  	imprvectreel(3, NM);
 	}*/
  
  	/* Definition de l'angle theta1, entre la direction du vecteur VV et le vecteur NM. */
     	if(NM[1] != 0.0) theta1 =  atan(NM[2]/NM[1]);
     	if(NM[1] == 0.0) theta1 = PI/4;
     	
	/*printf(" theta1 = %lf   \n",theta1/PI*180);  */
  
  	/* Definition des efforts, tangent et normal, pour un seul cote de maille, projetees sur X et Y,
     	appelees respectivement Tx, Ty, Nx, Ny */  
  
  	/* R = constante*/

  	/*ici on prend en compte l allongement des fils*/
	/* R = 0.5*RHO*Surface[elem].cdnormal*Surface[elem].diametrehydro*sqrt(Surface[elem].lgrepos/sqrt(NM[1]*NM[1]+NM[2]*NM[2])/2)*Courant.vitesse*Courant.vitesse*sqrt(NM[1]*NM[1]+NM[2]*NM[2])/2;*/

  	/*ici on ne prend pas en compte l allongement des fils*/
     	R = 0.5*RHO*Surface[elem].cdnormal*Surface[elem].diametrehydro*Courant.vitesse*Courant.vitesse*Surface[elem].lgrepos ;  
	/*printf(" R = %lf   \n",R);  */
  
  	/* Calcul des directions des efforts, donnees dans les vecteurs ne et te*/
     	compos(VV,NM);
if(elem == 1)
	{
 	imprvectreel(3, te);
 	imprvectreel(3, ne);
	printf("Surface[elem].nb_cote_u_ou_v  = %lf   \n",Surface[elem].nb_cote_u_ou_v);
	printf(" R = %lf   \n",R);
	printf(" Surface[elem].cdnormal = %lf   \n",Surface[elem].cdnormal);
	printf(" Surface[elem].diametrehydro = %lf   \n",Surface[elem].diametrehydro);
	printf(" Courant.vitesse = %lf   \n",Courant.vitesse);
	printf(" Surface[elem].lgrepos = %lf   \n",Surface[elem].lgrepos);
 	}
     
	/*printf("ftangent  = %lf   \n",Surface[elem].ftangent);  */
     	Tx = R*Surface[elem].ftangent*cos(theta1)*cos(theta1) * te[1];
     	Ty = R*Surface[elem].ftangent*cos(theta1)*cos(theta1) * te[2];
     	Nx = R*sin(theta1)*sin(theta1) * ne[1];
     	Ny = R*sin(theta1)*sin(theta1) * ne[2];
  
  	/* Effort tangent et effort nomal applique sur le sommet 1 du triangle,
     	pour les fils de directions u ou v */
     
     	ETuv[1] = Tx*Surface[elem].nb_cote_u_ou_v/3.0;
     	ETuv[2] = Ty*Surface[elem].nb_cote_u_ou_v/3.0;
     	ETuv[3] = 0.0;
  
     	ENuv[1] = Nx*Surface[elem].nb_cote_u_ou_v/3.0;
     	ENuv[2] = Ny*Surface[elem].nb_cote_u_ou_v/3.0;
     	ENuv[3] = 0.0;

  	/* Effort tangent et effort nomal applique sur le sommet 2 du triangle,
     	pour les fils de directions u ou v */
    
     	ETuv[4] = Tx*Surface[elem].nb_cote_u_ou_v/3.0;
     	ETuv[5] = Ty*Surface[elem].nb_cote_u_ou_v/3.0;
     	ETuv[6] = 0.0;

     	ENuv[4] = Nx*Surface[elem].nb_cote_u_ou_v/3.0;
     	ENuv[5] = Ny*Surface[elem].nb_cote_u_ou_v/3.0;
     	ENuv[6] = 0.0;

 

  	/* Effort tangent et effort nomal applique sur le sommet 3 du triangle,
     	pour les fils de directions u ou v  */
    
     	ETuv[7] = Tx*Surface[elem].nb_cote_u_ou_v/3.0;
     	ETuv[8] = Ty*Surface[elem].nb_cote_u_ou_v/3.0;
     	ETuv[9] = 0.0;
  
     	ENuv[7] = Nx*Surface[elem].nb_cote_u_ou_v/3.0;
     	ENuv[8] = Ny*Surface[elem].nb_cote_u_ou_v/3.0;
     	ENuv[9] = 0.0;

  	/* On replace les efforts, ainsi que VV dans l'espace par des rotations opposees */
  
     	base1(-alpha2,3,0.0,3,9,ETuv);
     	base1(-alpha2,3,0.0,3,9,ENuv);
     	base1(-alpha2,3,0.0,3,3,VV);
     	base1(-beta1,2,-alpha1,3,9,ETuv);
     	base1(-beta1,2,-alpha1,3,9,ENuv);
     	base1(-beta1,2,-alpha1,3,3,VV);
if(elem == 1)
	{
	printf("ENuv et  ETuv  \n");
 	imprvectreel(3, ENuv);
 	imprvectreel(3, ETuv);
 	}
 
}    
