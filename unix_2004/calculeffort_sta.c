#include "4c19.h"

void calculeffort_sta(int notria,double VV[4],double UV[4])

	{
	int i;
	double modVV,modUV,modne,acos_theta;
	double prodsc,temp1,temp2,temp3;
	double f,k,theta,sign,length;
	double ne[4],te[4],N[4],T[4];

	/*initialisation*/
	for( i =  1 ; i <= 9 ; i++)
	     {
	      ETu_ou_v[i]=0.0;
	      ENu_ou_v[i]=0.0; 
	     }  

	/* les normes de VV et de UV */
	modVV = sqrt(VV[1]*VV[1]+VV[2]*VV[2]+VV[3]*VV[3]);
	modUV = sqrt(UV[1]*UV[1]+UV[2]*UV[2]+UV[3]*UV[3]);

	/*les intermediaires */
	prodsc = UV[1]*VV[1]+UV[2]*VV[2]+UV[3]*VV[3];
	temp1 = -VV[1]*(UV[2]*UV[2]+UV[3]*UV[3])+UV[1]*(UV[2]*VV[2]+UV[3]*VV[3]);
	temp2 =  VV[2]*(UV[3]*UV[3]+UV[1]*UV[1])-UV[2]*(UV[3]*VV[3]+UV[1]*VV[1]);
	temp3 =  VV[3]*(UV[1]*UV[1]+UV[2]*UV[2])-UV[3]*(UV[1]*VV[1]+UV[2]*VV[2]);

	/*l'angle theta entre UV et VV */
	if ((modVV == 0.0) || (modUV == 0.0))
		{
		theta = 0.0;
		}
	else
		{
		acos_theta = prodsc/modUV/modVV;
		if (acos_theta >  1.0) acos_theta =  1.0;
		if (acos_theta < -1.0) acos_theta = -1.0;
		//theta = acos(prodsc/modUV/modVV);
		theta = acos(acos_theta);
		}

	/* les directions des efforts */
	modne = sin(theta);

	if ((modVV == 0.0) || (modUV == 0.0) || (modne == 0.0))
		{
		ne[1] = 0.0;
		ne[2] = 0.0;
		ne[3] = 0.0;
		}
	else
		{
		ne[1] = -temp1/(modUV*modUV)/modVV/modne;
		ne[2] =  temp2/(modUV*modUV)/modVV/modne;
		ne[3] =  temp3/(modUV*modUV)/modVV/modne;
		}
	if ((theta <= PI/2) && (theta >= -PI/2))
		{
		sign = 1.0;
		}
	else
		{
		sign = -1.0;
		}
		
	if (modUV == 0.0)
		{
		te[1] = 0.0;
		te[2] = 0.0;
		te[3] = 0.0;
		}
	else
		{
		te[1] = sign*UV[1]/modUV;
		te[2] = sign*UV[2]/modUV;
		te[3] = sign*UV[3]/modUV;
		}

	/* les vecteurs efforts */
	f = Surface[notria].ftangent;
	
	length = Surface[notria].lgrepos - panneau[Surface[notria].type].largeurnoeud;	/*length of twine affected by the curent*/
	
	k =0.5*RHO*Surface[notria].cdnormal*Surface[notria].diametrehydro*length*modVV*modVV;

	T[1] = f*k*cos(theta)*cos(theta)*te[1];
	T[2] = f*k*cos(theta)*cos(theta)*te[2];
	T[3] = f*k*cos(theta)*cos(theta)*te[3];

	N[1] = k*sin(theta)*sin(theta)*ne[1];
	N[2] = k*sin(theta)*sin(theta)*ne[2];
	N[3] = k*sin(theta)*sin(theta)*ne[3];

  	/* Effort tangent et effort normal applique sur le sommet 1 du triangle,
     	pour les fils de directions u ou v */
     
     	ETu_ou_v[1] = T[1]*Surface[notria].nb_cote_u_ou_v/3.0;
     	ETu_ou_v[2] = T[2]*Surface[notria].nb_cote_u_ou_v/3.0;
     	ETu_ou_v[3] = T[3]*Surface[notria].nb_cote_u_ou_v/3.0;
  
     	ENu_ou_v[1] = N[1]*Surface[notria].nb_cote_u_ou_v/3.0;
     	ENu_ou_v[2] = N[2]*Surface[notria].nb_cote_u_ou_v/3.0;
     	ENu_ou_v[3] = N[3]*Surface[notria].nb_cote_u_ou_v/3.0;

  	/* Effort tangent et effort normal applique sur le sommet 2 du triangle,
     	pour les fils de directions u ou v */
    
     	ETu_ou_v[4] = T[1]*Surface[notria].nb_cote_u_ou_v/3.0;
     	ETu_ou_v[5] = T[2]*Surface[notria].nb_cote_u_ou_v/3.0;
     	ETu_ou_v[6] = T[3]*Surface[notria].nb_cote_u_ou_v/3.0;
  
     	ENu_ou_v[4] = N[1]*Surface[notria].nb_cote_u_ou_v/3.0;
     	ENu_ou_v[5] = N[2]*Surface[notria].nb_cote_u_ou_v/3.0;
     	ENu_ou_v[6] = N[3]*Surface[notria].nb_cote_u_ou_v/3.0;


  	/* Effort tangent et effort normal applique sur le sommet 3 du triangle,
     	pour les fils de directions u ou v  */
    
     	ETu_ou_v[7] = T[1]*Surface[notria].nb_cote_u_ou_v/3.0;
     	ETu_ou_v[8] = T[2]*Surface[notria].nb_cote_u_ou_v/3.0;
     	ETu_ou_v[9] = T[3]*Surface[notria].nb_cote_u_ou_v/3.0;
  
     	ENu_ou_v[7] = N[1]*Surface[notria].nb_cote_u_ou_v/3.0;
     	ENu_ou_v[8] = N[2]*Surface[notria].nb_cote_u_ou_v/3.0;
     	ENu_ou_v[9] = N[3]*Surface[notria].nb_cote_u_ou_v/3.0;
	} 
