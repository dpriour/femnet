#define PRINCIPAL 0
#include "4c19.h"

void compos(double *V,double *u)

/* procedure qui permet de definir les directions des composantes selon X et Y des efforts normaux, et  
   tangents Ces directions sont donnees dans les vecteurs ne et te. Le vecteur u donne les composantes du fil (u[1] u[2] et u[3]),
   le vecteur V les composantes du courant : V[1] V[2] et V[3].
   Puisque nous sommes dans le plan, les troisieme composantes de V et de u sont nulles. 
   De plus V est parallele a l'axe des X, donc v[2] = 0.*/
   
{
   int sgn,i;
   double v[4],s[4],amplitude;
  
  /* Mise a zero de ne et de te : */
    for (i=1 ; i<=3; i++)
    {
      te[i] = 0.0;
      ne[i] = 0.0;
    }  
     
   /* Nomalisalisation du vecteur V, sauvegarde dans v */
   if(V[1] != 0.0)
   {
     v[1] = V[1]/sqrt(V[1]*V[1]);
     v[2] = 0.0 ; 
     v[3] = 0.0 ;
   }
     /* Cas ou la vitesse du courant est nulle */
   if(V[1]==0) 
   {
     v[1] = 0.0;
     v[2] = 0.0;
     v[3] = 0.0;
   }    
   
   /* Nomalisalisation du vecteur u, sauvegarde dans u */
   amplitude = sqrt((u[1]*u[1]) + (u[2]*u[2]));
   if(amplitude != 0.0)
   {
     u[1] = u[1] / amplitude;
     u[2] = u[2] / amplitude; 
     u[3] = 0.0;
   }
   if(amplitude == 0.0)
   {
     u[1] = 1.0;
     u[2] = 0.0; 
     u[3] = 0.0 ;
   }
   
   /* Direction du fil donne par sgn */
   if (u[1] >= 0.0) sgn =  1;
   if (u[1] <  0.0) sgn = -1;
     
   te[1]=sgn * u[1];
   te[2]=sgn * u[2];
   
   
   /* produit vectoriel norme de v par te, le vecteur s est donc suivant l'axe Z : */
   s[1]= 0.0 ;
   s[2]= 0.0 ;
   if (v[1]*te[2] >= 0.0)
   	{
   	s[3]=   1.0;
   	}
   if (v[1]*te[2] <  0.0)
   	{
   	s[3]= - 1.0;
   	}
   
   /*produit vectoriel de te par s : on obtient alors le vecteur ne, c'est a dire les composantes X, Y, Z
    du vecteur normal a te(dirige de la meme facon que l'effort de portance) */
    
   ne[1] =  te[2] * s[3];
   ne[2] = -te[1] * s[3];
   
     if((((te[1]*te[1]) + (te[2]*te[2])) > 1.001) || (((te[1]*te[1]) + (te[2]*te[2])) < 0.999))
     	{
  	printf(" te %12.4lf %12.4lf \n",te[1],te[2] );
  	printf(" ne %12.4lf %12.4lf \n",ne[1],ne[2] );
  	printf(" u  %12.4lf %12.4lf %12.4lf \n",u[1],u[2],u[3] );
  	printf(" v  %12.4lf %12.4lf %12.4lf \n",v[1],v[2],v[3] );
  	printf(" Erreur dans compos.c");
  	exit(0);
     	}
     if((((ne[1]*ne[1]) + (ne[2]*ne[2])) > 1.001) || (((ne[1]*ne[1]) + (ne[2]*ne[2])) < 0.999))
     	{
  	printf(" te %12.4lf %12.4lf \n",te[1],te[2] );
  	printf(" ne %12.4lf %12.4lf \n",ne[1],ne[2] );
  	printf(" u  %12.4lf %12.4lf %12.4lf \n",u[1],u[2],u[3] );
  	printf(" v  %12.4lf %12.4lf %12.4lf \n",v[1],v[2],v[3] );
  	printf(" Erreur dans compos.c");
  	exit(0);
     	}
}   
   
