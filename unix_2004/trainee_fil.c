#define PRINCIPAL 0
#include "4c19.h"

void trainee_fil(int elem, double *VV, double *tfuv)
	{

  	/* 
  	Calcul des vecteurs effort tangent et effort normal pour un fil u de direction N et un fil v de direction M 
  	du triangle numero elem. On prend en compte la longueur du fil son diametre et les coefficients de trainee.
     	Resultat dans l'espace.
     	le resultat est dans les vecteurs tfuv. 
     	tfuv[1] = trainee d un fil u et d un fil v selon x 
     	tfuv[2] = trainee d un fil u et d un fil v selon y
     	tfuv[3] = trainee d un fil u et d un fil v selon z
     	*/
     
  	/* NM : Composantes selon X, Y et Z du vecteur NM placees dans NM[1] NM[2] et NM[3]*/  
  	/* VV : Composantes selon X, Y et Z du vecteur VV placees dans VV[1] VV[2] et VV[3] */
    
   	double theta1,R,Tx,Ty,Ny,Nx,NM[4],modV;
   	
   	/*module vitesse*/
   	modV = sqrt(produit_scal(VV,VV));

   	
   	/*fil u*/
   	NM[1] = Surface[elem].nx;    NM[2] = Surface[elem].ny;  NM[3] = Surface[elem].nz;

	/* printf("calcul de alpha1 et beta1\n");  */
  	/* calcul des 2 angles de rotation alpha1/Z beta1/Y , pour travailler dans le plan contenant VV et NM */
     	rota1(VV,NM);    

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
     	
  	/* Definition de l'angle theta1, entre la direction du vecteur VV et le vecteur NM. */
     	if(NM[1] != 0.0) theta1 =  atan(NM[2]/NM[1]);
     	if(NM[1] == 0.0) theta1 = PI/4;
     	
  	/* Definition des efforts, tangent et normal, pour un seul cote de maille, projetees sur X et Y,
     	appelees respectivement Tx, Ty, Nx, Ny */  
  
  	/* R = constante*/

  	/*ici on prend en compte l allongement des fils*/
	/* R = 0.5*RHO*Surface[elem].cdnormal*Surface[elem].diametrehydro*sqrt(Surface[elem].lgrepos/sqrt(NM[1]*NM[1]+NM[2]*NM[2])/2)*modV*modV*sqrt(NM[1]*NM[1]+NM[2]*NM[2])/2;*/

  	/*ici on ne prend pas en compte l allongement des fils*/
     	R = 0.5*RHO*Surface[elem].cdnormal*Surface[elem].diametrehydro*modV*modV*Surface[elem].lgrepos ;  
	/*printf(" R = %lf   \n",R);  */
  
  	/* Calcul des directions des efforts, donnees dans les vecteurs ne et te*/
     	compos(VV,NM);
     
	/*printf("ftangent  = %lf   \n",Surface[elem].ftangent);  */
     	Tx = R*Surface[elem].ftangent*cos(theta1)*cos(theta1) * te[1];
     	Ty = R*Surface[elem].ftangent*cos(theta1)*cos(theta1) * te[2];
     	Nx = R*sin(theta1)*sin(theta1) * ne[1];
     	Ny = R*sin(theta1)*sin(theta1) * ne[2];
  
  	/* Effort tangent et effort nomal applique sur le sommet 1 du triangle,
     	pour les fils de directions u ou v */
     
     	tfuv[1] = Tx  + Nx;
     	tfuv[2] = Ty  + Ny;
     	tfuv[3] = 0.0;
  

 


   	/*fil v*/
   	NM[1] = Surface[elem].mx;    NM[2] = Surface[elem].my;  NM[3] = Surface[elem].mz;

	/* printf("calcul de alpha1 et beta1\n");  */
  	/* calcul des 2 angles de rotation alpha1/Z beta1/Y , pour travailler dans le plan contenant VV et NM */
     	rota1(VV,NM);    

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
     	
  	/* Definition de l'angle theta1, entre la direction du vecteur VV et le vecteur NM. */
     	if(NM[1] != 0.0) theta1 =  atan(NM[2]/NM[1]);
     	if(NM[1] == 0.0) theta1 = PI/4;
     	
  	/* Definition des efforts, tangent et normal, pour un seul cote de maille, projetees sur X et Y,
     	appelees respectivement Tx, Ty, Nx, Ny */  
  
  	/* R = constante*/

  	/*ici on prend en compte l allongement des fils*/
	/* R = 0.5*RHO*Surface[elem].cdnormal*Surface[elem].diametrehydro*sqrt(Surface[elem].lgrepos/sqrt(NM[1]*NM[1]+NM[2]*NM[2])/2)*modV*modV*sqrt(NM[1]*NM[1]+NM[2]*NM[2])/2;*/

  	/*ici on ne prend pas en compte l allongement des fils*/
     	R = 0.5*RHO*Surface[elem].cdnormal*Surface[elem].diametrehydro*modV*modV*Surface[elem].lgrepos ;  
	/*printf(" R = %lf   \n",R);  */
  
  	/* Calcul des directions des efforts, donnees dans les vecteurs ne et te*/
     	compos(VV,NM);
     
	/*printf("ftangent  = %lf   \n",Surface[elem].ftangent);  */
     	Tx = R*Surface[elem].ftangent*cos(theta1)*cos(theta1) * te[1];
     	Ty = R*Surface[elem].ftangent*cos(theta1)*cos(theta1) * te[2];
     	Nx = R*sin(theta1)*sin(theta1) * ne[1];
     	Ny = R*sin(theta1)*sin(theta1) * ne[2];
  
  	/* Effort tangent et effort nomal applique sur le sommet 1 du triangle,
     	pour les fils de directions u ou v */
     
     	tfuv[1] += Tx  + Nx;
     	tfuv[2] += Ty  + Ny;
     	tfuv[3] += 0.0;
  

 


  	/* On replace les efforts, ainsi que VV dans l'espace par des rotations opposees */
  
     	base1(-alpha2,3,0.0,3,3,tfuv);
     	base1(-alpha2,3,0.0,3,3,VV);
     	base1(-beta1,2,-alpha1,3,3,tfuv);
     	base1(-beta1,2,-alpha1,3,3,VV);
}    
