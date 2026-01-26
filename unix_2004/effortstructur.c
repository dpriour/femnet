#define PRINCIPAL 0
#include "4c19.h"

void effortstructur()

/* on somme les efforts aux frontieres de la structue selon X, Y et Z. 
sur les coordonnees fixes et on les stocke dans wa[1], wa[2] et wa[3], */
   
{
    int i;
     
     for ( i = 1 ; i <= 3 ; i++ )
     { 
        /*mise a zero des efforts selon X Y et Z*/
        wa[i] = 0.0;		          
     } 
     
     for ( i = 1 ; i <= NOMBRE_NOEUDS ; i++ )
     { 
     /*effort selon X */
       if ( (wl[3*i-2] != 99) && (Noeud[i].symx == 0) )
       {
        wa[1] += wasurf[3*i-2];		          
        wa[1] += waelem[3*i-2];
        wa[1] += wanoeud[3*i-2];
       	//printf("i %4d wasurf %lf waelem %lf wanoeud %lf wa %lf   \n",i,wasurf[3*i-2],waelem[3*i-2],wanoeud[3*i-2],wa[1]);/**/
       }
     /*effort selon Y */
       if ( (wl[3*i-1] != 99) && (Noeud[i].symy == 0)  )
       {
        wa[2] += wasurf[3*i-1];		          
        wa[2] += waelem[3*i-1];
        wa[2] += wanoeud[3*i-1];
       }
     /*effort selon Z */
       if ( (wl[3*i-0] != 99) && (Noeud[i].symz == 0)  )
       {
        wa[3] += wasurf[3*i-0];		          
        wa[3] += waelem[3*i-0];
        wa[3] += wanoeud[3*i-0];
       }
     }  
  }    
