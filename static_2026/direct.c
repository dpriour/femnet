#define PRINCIPAL 0
#include "4c19.h"

void direct()

{
  /* 
  Verification de l'orientation des triangles . Apres rotations, les triangles seront
   dans le sens direct, ainsi que le repere (0,u,v). 
   */
  
  int elem,zh,zi,zj;
  double A,B,C,D,S,u2,u3,v2,v3,nx,ny,mx,my;
  double U2,U3,V2,V3,Ux,Uy,Vx,Vy;
  
  for ( elem = 1 ; elem <= NOMBRE_SURFACES ; elem++ )
  {
    /*numeros des coordonnees selon x des sommets du triangle*/
    zh = yc(elem,1);  zi = yc(elem,4);  zj = yc(elem,7);
    rotation3(zh,zi,zj); /* On travaille dans le plan XOY apres ces rotations*/
/*if (elem == 256) 
	{
	printf("zh : %d zi : %d zj : %d \n",zh,zi,zj);
	exit(0);
	}*/
    /* u2 : coordonnee du noeud 2 en nb maille selon les fils de direction u*/ 
    u2 = Surface[elem].lon[3]+Surface[elem].lon[4]-Surface[elem].lon[2]-Surface[elem].lon[1];  
    /* u3 : coordonnee du noeud 3 en nb maille selon les fils de direction u */
    u3 = Surface[elem].lon[5]+Surface[elem].lon[6]-Surface[elem].lon[2]-Surface[elem].lon[1]; 
    /* v2 : coordonnee du noeud 2 en nb maille selon les fils de direction v*/
    v2 = -Surface[elem].lon[3]+Surface[elem].lon[4]-Surface[elem].lon[2]+Surface[elem].lon[1];
    /* v3 : coordonnee du noeud 3 en nb maille selon les fils de direction v*/
    v3 = -Surface[elem].lon[5]+Surface[elem].lon[6]-Surface[elem].lon[2]+Surface[elem].lon[1]; 
   
   /* (Xi,Yi) coordonnes cartesiennes dans le plan XOY du sommet i du triangle elem*/
    A = v2*(X1-X3) + v3*(X2-X1); 
    B = v2*(Y3-Y1) + v3*(Y1-Y2);
    C = u2*(X1-X3) + u3*(X2-X1);
    D = u2*(Y3-Y1) + u3*(Y1-Y2); 
    S = u2*v3 - u3*v2;
   /*printf("S : %lf \n",S);
   if (elem == 39) exit(0);*/
    
    /* nx : Coordonnees selon x d'un cote de maille (selon u )*/
    /* ny : Coordonnees selon y d'un cote de maille (selon u )*/
    /* mx : Coordonnees selon x d'un cote de maille (selon v )*/
    /* my : Coordonnees selon y d'un cote de maille (selon v )*/

    if (S == 0.0)
    {
   	printf("Erreur de coordonnees filaires sur l element : %d \n",elem);
	exit(0);
    }
    
    nx = A/S;
    ny = -B/S;
    mx = -C/S;
    my = D/S;
  
  /* Changement afin de rendre le repere forme par les fils u et v direct*/
    if (nx*my - ny*mx < 0.0)
    {
      Surface[elem].lon[1] = - Surface[elem].lon[1];
      Surface[elem].lon[3] = - Surface[elem].lon[3];
      Surface[elem].lon[5] = - Surface[elem].lon[5];
    }
  }
 
  for ( elem = 1 ; elem <= NOMBRE_SURF_HEXA ; elem++ )
  {
    /*numeros des coordonnees selon x des sommets du triangle*/
    zh = yc_hexa(elem,1);  zi = yc_hexa(elem,4);  zj = yc_hexa(elem,7);
    rotation3(zh,zi,zj); /* On travaille dans le plan XOY apres ces rotations*/
    /* U2 : coordonnee du noeud 2 en nb maille selon les fils de direction u*/ 
    U2 = Surf_Hexa[elem].lon[3]+Surf_Hexa[elem].lon[4]-Surf_Hexa[elem].lon[2]-Surf_Hexa[elem].lon[1];  
    /* U3 : coordonnee du noeud 3 en nb maille selon les fils de direction u */
    U3 = Surf_Hexa[elem].lon[5]+Surf_Hexa[elem].lon[6]-Surf_Hexa[elem].lon[2]-Surf_Hexa[elem].lon[1]; 
    /* V2 : coordonnee du noeud 2 en nb maille selon les fils de direction v*/
    V2 = -Surf_Hexa[elem].lon[3]+Surf_Hexa[elem].lon[4]-Surf_Hexa[elem].lon[2]+Surf_Hexa[elem].lon[1];
    /* V3 : coordonnee du noeud 3 en nb maille selon les fils de direction v*/
    V3 = -Surf_Hexa[elem].lon[5]+Surf_Hexa[elem].lon[6]-Surf_Hexa[elem].lon[2]+Surf_Hexa[elem].lon[1]; 
    
   
   /* (Xi,Yi) coordonnes cartesiennes dans le plan XOY du sommet i du triangle elem*/
    A = V2*(X1-X3) + V3*(X2-X1); 
    B = V2*(Y3-Y1) + V3*(Y1-Y2);
    C = U2*(X1-X3) + U3*(X2-X1);
    D = U2*(Y3-Y1) + U3*(Y1-Y2); 
    S = U2*V3 - U3*V2;
   /*printf("S : %lf \n",S);*/
    
    /* Ux : Coordonnees selon x d'un cote de maille (selon U )*/
    /* Uy : Coordonnees selon y d'un cote de maille (selon U )*/
    /* Vx : Coordonnees selon x d'un cote de maille (selon V )*/
    /* Vy : Coordonnees selon y d'un cote de maille (selon V )*/

    if (S == 0.0)
    {
   	printf("Erreur de coordonnees filaires sur l element : %d \n",elem);
	exit(0);
    }
    
    Ux = A/S;
    Uy = -B/S;
    Vx = -C/S;
    Vy = D/S;
  
  /* Changement afin de rendre le repere forme par les fils u et v direct*/
    if (Ux*Vy - Uy*Vx < 0.0)
    {
      Surf_Hexa[elem].lon[1] = - Surf_Hexa[elem].lon[1];
      Surf_Hexa[elem].lon[3] = - Surf_Hexa[elem].lon[3];
      Surf_Hexa[elem].lon[5] = - Surf_Hexa[elem].lon[5];
    }
  }
}  
    
