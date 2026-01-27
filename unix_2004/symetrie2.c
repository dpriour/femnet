#define PRINCIPAL 0
#include "4c19.h"

void symetrie2()
{

	/* 
	On verifie, noeud par noeud, s'ils sont sur un plan de symetrie (XOY, ou XOZ, ou YOZ).
	Dans ce cas, on modifie la matrice de raideur et les efforts. 
	*/
   
    	int zi,zl,i;
     	double interm;
     
     
     	for ( i = 1 ; i <= NOMBRE_NOEUDS ; i++ )
	{ 
      		/* Symetrie par rapport au plan YOZ. Modification des efforts */   
       		if ( Noeud[i].symx == 1 )
		{
        		wanoeud[3*i-2] = 0.0 ;   
        		wasurf[3*i-2 ] = 0.0 ;		          waelem[3*i-2 ] = 0.0 ;
        		wasurf[3*i-1 ] = 2.0*wasurf[3*i-1] ;  	  waelem[3*i-1 ] = 2.0*waelem[3*i-1] ;
        		wasurf[3*i   ] = 2.0*wasurf[3*i  ] ; 	  waelem[3*i   ] = 2.0*waelem[3*i  ] ;		
		} 
       
     		/* Symetrie par rapport au plan XOZ. Modification des efforts */        
      		if ( Noeud[i].symy == 1 )
		{  
         		wanoeud[3*i-1] = 0.0;
         		wasurf[3*i-1 ] = 0.0;			  waelem[3*i-1] = 0.0;
         		wasurf[3*i-2 ] = 2.0*wasurf[3*i-2];	  waelem[3*i-2] = 2.0*waelem[3*i-2];
         		wasurf[3*i   ] = 2.0*wasurf[3*i  ];	  waelem[3*i  ] = 2.0*waelem[3*i  ];		 
		}
      
     		/* Symetrie par rapport au plan XOY. Modification des efforts */   
        	if ( Noeud[i].symz == 1 )
		{ 
         		wanoeud[3*i  ] = 0.0;
        		wasurf[ 3*i  ] = 0.0;			waelem[3*i  ] = 0.0;
         		wasurf[ 3*i-2] = 2.0*wasurf[3*i-2];	waelem[3*i-2] = 2.0*waelem[3*i-2];
         		wasurf[ 3*i-1] = 2.0*wasurf[3*i-1];	waelem[3*i-1] = 2.0*waelem[3*i-1];
		}
      
	}  

  	/* Parcours de tous les noeuds et calcul du vecteur effort total */
     	for ( i = 1 ; i <= NOMBRE_NOEUDS ; i++ )
	{
        	wa[3*i-2] = wasurf[3*i-2] + waelem[3*i-2] + wanoeud[3*i-2];
        	wa[3*i-1] = wasurf[3*i-1] + waelem[3*i-1] + wanoeud[3*i-1];
        	wa[3*i-0] = wasurf[3*i-0] + waelem[3*i-0] + wanoeud[3*i-0];
	}   
       
       
           
      	for ( i = 1 ; i <= NOMBRE_NOEUDS ; i++ )
	{
		interm = 0.0;
  		/* Symetrie par rapport au plan YOZ . Modification de la matrice de raideur */   
       		if ( Noeud[i].symx == 1 )
       		{
        		wl[3*i-2] = 0.0;         /* On fixe le deplacement du noeud i, sur l'axe des X a 0. */ 
			if (Structure.type_solver == 1)
			{
				/*on multiplie par 2 les lignes selon y et z*/    
        			for ( zl = rang[4][3*i-1] ; zl <= rang[2][3*i-1] ; zl++) ze[3*i-1][zl+eca-3*i+1] = 2.0*ze[3*i-1][zl+eca-3*i+1] ;
        			for ( zl = rang[4][3*i  ] ; zl <= rang[2][3*i  ] ; zl++) ze[3*i  ][zl+eca-3*i  ] = 2.0*ze[3*i  ][zl+eca-3*i  ] ;        
        			interm = ze[3*i-2][eca];
        			/*la ligne et la collonne selon x est mise a zero sauf le terme kij qui est multiplie par 2*/
        			for ( zl = rang[4][3*i-2] ; zl <= rang[2][3*i-2] ; zl++)  ze[3*i-2][zl+eca-3*i+2] = 0.0;    
        			for ( zi = rang[3][3*i-2] ; zi <= rang[1][3*i-2] ; zi++)  ze[zi   ][3*i-2+eca-zi] = 0.0;
        			ze[3*i-2][eca] = 2.0*interm;
       			}
			else if (Structure.type_solver == 2)
			{
				//on multiplie par 2 les lignes selon y et z  
        			for ( zl = rang[4][3*i-1] ; zl <= rang[2][3*i-1] ; zl++)
				{
					trouve_valeur(3*i-1, zl);
					//modif_pardiso(2.0*valeur, 3*i-1, zl);
				}
        			for ( zl = rang[4][3*i  ] ; zl <= rang[2][3*i  ] ; zl++)
				{
					trouve_valeur(3*i, zl);
					//modif_pardiso(2.0*valeur, 3*i, zl);
				}
				trouve_valeur(3*i-2,3*i-2);
        			interm = valeur;
        			//la ligne et la collonne selon x est mise a zero sauf le terme kij qui est multiplie par 2
        			for ( zl = rang[4][3*i-2] ; zl <= rang[2][3*i-2] ; zl++)
				{
					//modif_pardiso(0.0, 3*i-2, zl);
				}
        			for ( zi = rang[3][3*i-2] ; zi <= rang[1][3*i-2] ; zi++)
				{
					//modif_pardiso(0.0, zi, 3*i-2);
				} 
				//affectation_pardiso(2.0*interm, 3*i-2, 3*i-2);
			}
		}
       
  		/* Symetrie par rapport au plan XOZ . Modification de la matrice de raideur*/        
      		if ( Noeud[i].symy == 1 )
		{  
         		wl[3*i-1] = 0.0;          /* On fixe le deplacement du noeud i, sur l'axe des Y a 0. */
			if (Structure.type_solver == 1)
			{
        	 		for ( zl = rang[4][3*i-2] ; zl <= rang[2][3*i-2] ; zl++) ze[3*i-2][zl+eca-3*i+2] = 2.0*ze[3*i-2][zl+eca-3*i+2] ;
        	 		for ( zl = rang[4][3*i  ] ; zl <= rang[2][3*i  ] ; zl++) ze[3*i  ][zl+eca-3*i  ] = 2.0*ze[3*i  ][zl+eca-3*i  ] ;   
        	 		interm = ze[3*i-1][eca];       
        	 		for ( zl = rang[4][3*i-1] ; zl <= rang[2][3*i-1] ; zl++)   ze[3*i-1][zl+eca-3*i+1] = 0.0;       
        	 		for ( zi = rang[3][3*i-1] ; zi <= rang[1][3*i-1] ; zi++)   ze[zi   ][3*i-1+eca-zi] = 0.0;           
        	 		ze[3*i-1][eca] = 2.0*interm;
       			}
			else if (Structure.type_solver == 2)
			{
        			for ( zl = rang[4][3*i-2] ; zl <= rang[2][3*i-2] ; zl++)
				{
					trouve_valeur(3*i-2, zl);
					//modif_pardiso(2.0*valeur, 3*i-2, zl);
				}
        			for ( zl = rang[4][3*i  ] ; zl <= rang[2][3*i  ] ; zl++)
				{
					trouve_valeur(3*i, zl);
					//modif_pardiso(2.0*valeur, 3*i, zl);
				}
				trouve_valeur(3*i-1,3*i-1);
        			interm = valeur;

        			for ( zl = rang[4][3*i-1] ; zl <= rang[2][3*i-1] ; zl++)
				{
					//modif_pardiso(0.0, 3*i-1, zl);
				}
        			for ( zi = rang[3][3*i-1] ; zi <= rang[1][3*i-1] ; zi++)
				{
					//modif_pardiso(0.0, zi, 3*i-1);
				}
				//affectation_pardiso(2.0*interm, 3*i-1, 3*i-1);
			}
		}
              
  		/* Symetrie par rapport au plan XOY. Modification de la matrice de raideur */   
       		if ( Noeud[i].symz == 1 )
		{ 
         		wl[3*i  ] = 0.0;              /* On fixe le deplacement du noeud i, sur l'axe des Z a 0. */
			if (Structure.type_solver == 1)
			{
 	        		for ( zl = rang[4][3*i-2] ; zl <= rang[2][3*i-2]; zl++) ze[3*i-2][zl+eca-3*i+2] = 2.0*ze[3*i-2][zl+eca-3*i+2] ;
        	 		for ( zl = rang[4][3*i-1] ; zl <= rang[2][3*i-1]; zl++) ze[3*i-1][zl+eca-3*i+1] = 2.0*ze[3*i-1][zl+eca-3*i+1] ;
        	 		interm = ze[3*i  ][eca];       
        	 		for ( zl = rang[4][3*i  ] ; zl <=rang[2][3*i  ] ; zl++)   ze[3*i  ][zl+eca-3*i  ] = 0.0;              
        	 		for ( zi = rang[3][3*i  ] ; zi <=rang[1][3*i  ] ; zi++)   ze[zi   ][3*i+eca-zi  ] = 0.0;           
        	 		ze[3*i  ][eca] = 2.0*interm;
       			}
			else if (Structure.type_solver == 2)
			{ 
        			for ( zl = rang[4][3*i-2] ; zl <= rang[2][3*i-2] ; zl++)
				{
					trouve_valeur(3*i-2, zl);
					//modif_pardiso(2.0*valeur, 3*i-2, zl);
				}
        			for ( zl = rang[4][3*i-1  ] ; zl <= rang[2][3*i-1  ] ; zl++)
				{
					trouve_valeur(3*i-1, zl);
					//modif_pardiso(2.0*valeur, 3*i-1, zl);
				}
				trouve_valeur(3*i,3*i);
        			interm = valeur;

        			for ( zl = rang[4][3*i] ; zl <= rang[2][3*i] ; zl++)
				{
					//modif_pardiso(0.0, 3*i, zl);
				}
        			for ( zi = rang[3][3*i] ; zi <= rang[1][3*i] ; zi++)
				{
					//modif_pardiso(0.0, zi, 3*i);
				} 
				//affectation_pardiso(2.0*interm, 3*i, 3*i);
			}
		}
	} 
}

 
