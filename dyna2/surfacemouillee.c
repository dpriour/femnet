#include "4c19.h"

void surfacemouillee(int notria,double S1)
{

/*calcul de la surface mouillee de chaque element triangulaire modelisant le
filet relativement à la surface libre au REPOS*/

double xp1,yp1,xp2,yp2;
double S;

if (wf[yc(notria,3)] >= 0.0 && wf[yc(notria,6)] >= 0.0 && wf[yc(notria,9)] >= 0.0)
	{
	SM = 0.0;
	}
	
if (wf[yc(notria,3)] < 0.0 && wf[yc(notria,6)] < 0.0 && wf[yc(notria,9)] < 0.0)
	{
	SM = S1;
	}
	
if (wf[yc(notria,3)] >= 0.0 && wf[yc(notria,6)] < 0.0 && wf[yc(notria,9)] < 0.0)
	{
	/*On calcule les coordonnees des deux points d'intersection entre le
	triangle ABC (sommet 1,sommet 2,sommet 3)et la surface libre 
	d'apres le theoreme de thales*/
	/*coordonnees de P1*/
	xp1 = (wf[yc(notria,4)]*wf[yc(notria,3)]-wf[yc(notria,1)]*wf[yc(notria,6)])/(wf[yc(notria,3)]-wf[yc(notria,6)]);
	yp1 = (wf[yc(notria,5)]*wf[yc(notria,3)]-wf[yc(notria,2)]*wf[yc(notria,6)])/(wf[yc(notria,3)]-wf[yc(notria,6)]);
	/*coordonnees de P2*/
	xp2 = (wf[yc(notria,7)]*wf[yc(notria,3)]-wf[yc(notria,1)]*wf[yc(notria,9)])/(wf[yc(notria,3)]-wf[yc(notria,9)]);
	yp2 = (wf[yc(notria,8)]*wf[yc(notria,3)]-wf[yc(notria,2)]*wf[yc(notria,9)])/(wf[yc(notria,3)]-wf[yc(notria,9)]);
	/*surface du triangle AP1P2*/
	S = 0.5*sqrt(pow(wf[yc(notria,3)]*(yp2-yp1),2.0)
	+pow(wf[yc(notria,3)]*(xp1-xp2),2.0)
	+pow((xp1-wf[yc(notria,1)])*(yp2-wf[yc(notria,2)])-(yp1-wf[yc(notria,2)])*(xp2-wf[yc(notria,1)]),2.0));
	
	/*surface mouillee*/
	SM = S1 - S;
	}
	
if (wf[yc(notria,3)] < 0.0 && wf[yc(notria,6)] >= 0.0 && wf[yc(notria,9)] < 0.0)
	{
	/*On calcule les coordonnees des deux points d'intersection entre le
	triangle ABC (sommet 1,sommet 2,sommet 3)et la surface libre 
	d'apres le theoreme de thales*/
	/*coordonnees de P1*/
	xp1 = (wf[yc(notria,7)]*wf[yc(notria,6)]-wf[yc(notria,4)]*wf[yc(notria,9)])/(wf[yc(notria,6)]-wf[yc(notria,9)]);
	yp1 = (wf[yc(notria,8)]*wf[yc(notria,6)]-wf[yc(notria,5)]*wf[yc(notria,9)])/(wf[yc(notria,6)]-wf[yc(notria,9)]);
	/*coordonnees de P2*/
	xp2 = (wf[yc(notria,1)]*wf[yc(notria,6)]-wf[yc(notria,4)]*wf[yc(notria,3)])/(wf[yc(notria,6)]-wf[yc(notria,3)]);
	yp2 = (wf[yc(notria,2)]*wf[yc(notria,6)]-wf[yc(notria,5)]*wf[yc(notria,3)])/(wf[yc(notria,6)]-wf[yc(notria,3)]);
	/*surface du triangle BP1P2*/
	S = 0.5*sqrt(pow(wf[yc(notria,6)]*(yp2-yp1),2.0)
	+pow(wf[yc(notria,6)]*(xp1-xp2),2.0)
	+pow((xp1-wf[yc(notria,4)])*(yp2-wf[yc(notria,5)])-(yp1-wf[yc(notria,5)])*(xp2-wf[yc(notria,4)]),2.0));
	
	/*surface mouillee*/
	SM = S1 - S;
	}
	
if (wf[yc(notria,3)] < 0.0 && wf[yc(notria,6)] < 0.0 && wf[yc(notria,9)] >= 0.0)
	{
	/*On calcule les coordonnees des deux points d'intersection entre le
	triangle ABC (sommet 1,sommet 2,sommet 3)et la surface libre 
	d'apres le theoreme de thales*/
	/*coordonnees de P1*/
	xp1 = (wf[yc(notria,1)]*wf[yc(notria,9)]-wf[yc(notria,7)]*wf[yc(notria,3)])/(wf[yc(notria,9)]-wf[yc(notria,3)]);
	yp1 = (wf[yc(notria,2)]*wf[yc(notria,9)]-wf[yc(notria,8)]*wf[yc(notria,3)])/(wf[yc(notria,9)]-wf[yc(notria,3)]);
	/*coordonnees de P2*/
	xp2 = (wf[yc(notria,4)]*wf[yc(notria,9)]-wf[yc(notria,7)]*wf[yc(notria,6)])/(wf[yc(notria,9)]-wf[yc(notria,6)]);
	yp2 = (wf[yc(notria,5)]*wf[yc(notria,9)]-wf[yc(notria,8)]*wf[yc(notria,6)])/(wf[yc(notria,9)]-wf[yc(notria,6)]);
	/*surface du triangle CP1P2*/
	S = 0.5*sqrt(pow(wf[yc(notria,9)]*(yp2-yp1),2.0)
	+pow(wf[yc(notria,9)]*(xp1-xp2),2.0)
	+pow((xp1-wf[yc(notria,7)])*(yp2-wf[yc(notria,8)])-(yp1-wf[yc(notria,8)])*(xp2-wf[yc(notria,7)]),2.0));
	
	/*surface mouillee*/
	SM = S1 - S;
	}
	
if (wf[yc(notria,3)] < 0.0 && wf[yc(notria,6)] >= 0.0 && wf[yc(notria,9)] >= 0.0)
	{
	/*On calcule les coordonnees des deux points d'intersection entre le
	triangle ABC (sommet 1,sommet 2,sommet 3)et la surface libre 
	d'apres le theoreme de thales*/
	/*coordonnees de P1*/
	xp1 = (wf[yc(notria,1)]*wf[yc(notria,9)]-wf[yc(notria,7)]*wf[yc(notria,3)])/(wf[yc(notria,9)]-wf[yc(notria,3)]);
	yp1 = (wf[yc(notria,2)]*wf[yc(notria,9)]-wf[yc(notria,8)]*wf[yc(notria,3)])/(wf[yc(notria,9)]-wf[yc(notria,3)]);
	/*coordonnees de P2*/
	xp2 = (wf[yc(notria,1)]*wf[yc(notria,6)]-wf[yc(notria,4)]*wf[yc(notria,3)])/(wf[yc(notria,6)]-wf[yc(notria,3)]);
	yp2 = (wf[yc(notria,2)]*wf[yc(notria,6)]-wf[yc(notria,5)]*wf[yc(notria,3)])/(wf[yc(notria,6)]-wf[yc(notria,3)]);
	/*surface mouillee = surface du triangle AP1P2*/
	SM = 0.5*sqrt(pow(wf[yc(notria,3)]*(yp1-yp2),2.0)
	+pow(wf[yc(notria,3)]*(xp2-xp1),2.0)
	+pow((xp2-wf[yc(notria,1)])*(yp1-wf[yc(notria,2)])-(yp2-wf[yc(notria,2)])*(xp1-wf[yc(notria,1)]),2.0));
	}

if (wf[yc(notria,3)] >= 0.0 && wf[yc(notria,6)] < 0.0 && wf[yc(notria,9)] >= 0.0)
	{
	/*On calcule les coordonnees des deux points d'intersection entre le
	triangle ABC (sommet 1,sommet 2,sommet 3)et la surface libre 
	d'apres le theoreme de thales*/
	/*coordonnees de P1*/
	xp1 = (wf[yc(notria,4)]*wf[yc(notria,3)]-wf[yc(notria,1)]*wf[yc(notria,6)])/(wf[yc(notria,3)]-wf[yc(notria,6)]);
	yp1 = (wf[yc(notria,5)]*wf[yc(notria,3)]-wf[yc(notria,2)]*wf[yc(notria,6)])/(wf[yc(notria,3)]-wf[yc(notria,6)]);
	/*coordonnees de P2*/
	xp2 = (wf[yc(notria,4)]*wf[yc(notria,9)]-wf[yc(notria,7)]*wf[yc(notria,6)])/(wf[yc(notria,9)]-wf[yc(notria,6)]);
	yp2 = (wf[yc(notria,5)]*wf[yc(notria,9)]-wf[yc(notria,8)]*wf[yc(notria,6)])/(wf[yc(notria,9)]-wf[yc(notria,6)]);
	/*surface mouillee = surface du triangle BP1P2*/
	SM = 0.5*sqrt(pow(wf[yc(notria,6)]*(yp1-yp2),2.0)
	+pow(wf[yc(notria,6)]*(xp2-xp1),2.0)
	+pow((xp2-wf[yc(notria,4)])*(yp1-wf[yc(notria,5)])-(yp2-wf[yc(notria,5)])*(xp1-wf[yc(notria,4)]),2.0));
	}
	
if (wf[yc(notria,3)] >= 0.0 && wf[yc(notria,6)] >= 0.0 && wf[yc(notria,9)] < 0.0)
	{
	/*On calcule les coordonnees des deux points d'intersection entre le
	triangle ABC (sommet 1,sommet 2,sommet 3)et la surface libre 
	d'apres le theoreme de thales*/
	/*coordonnees de P1*/
	xp1 = (wf[yc(notria,7)]*wf[yc(notria,6)]-wf[yc(notria,4)]*wf[yc(notria,9)])/(wf[yc(notria,6)]-wf[yc(notria,9)]);
	yp1 = (wf[yc(notria,8)]*wf[yc(notria,6)]-wf[yc(notria,5)]*wf[yc(notria,9)])/(wf[yc(notria,6)]-wf[yc(notria,9)]);
	/*coordonnees de P2*/
	xp2 = (wf[yc(notria,7)]*wf[yc(notria,3)]-wf[yc(notria,1)]*wf[yc(notria,9)])/(wf[yc(notria,3)]-wf[yc(notria,9)]);
	yp2 = (wf[yc(notria,8)]*wf[yc(notria,3)]-wf[yc(notria,2)]*wf[yc(notria,9)])/(wf[yc(notria,3)]-wf[yc(notria,9)]);
	/*surface mouillee = surface du triangle CP1P2*/
	SM = 0.5*sqrt(pow(wf[yc(notria,9)]*(yp1-yp2),2.0)
	+pow(wf[yc(notria,9)]*(xp2-xp1),2.0)
	+pow((xp2-wf[yc(notria,7)])*(yp1-wf[yc(notria,8)])-(yp2-wf[yc(notria,8)])*(xp1-wf[yc(notria,7)]),2.0));
	}
if (SM > S1)
	{
	SM = S1;
	}
}



double surfacemouillee2(int notria,double S1)
{

/*calcul de la surface mouillee de chaque element triangulaire modelisant le
filet relativement à la surface libre au REPOS*/

double xp1,yp1,xp2,yp2;
double S,SMo;

if (wf[yc(notria,3)] >= 0.0 && wf[yc(notria,6)] >= 0.0 && wf[yc(notria,9)] >= 0.0)
	{
	SMo = 0.0;
	}
	
if (wf[yc(notria,3)] < 0.0 && wf[yc(notria,6)] < 0.0 && wf[yc(notria,9)] < 0.0)
	{
	SMo = S1;
	}
	
if (wf[yc(notria,3)] >= 0.0 && wf[yc(notria,6)] < 0.0 && wf[yc(notria,9)] < 0.0)
	{
	/*On calcule les coordonnees des deux points d'intersection entre le
	triangle ABC (sommet 1,sommet 2,sommet 3)et la surface libre 
	d'apres le theoreme de thales*/
	/*coordonnees de P1*/
	xp1 = (wf[yc(notria,4)]*wf[yc(notria,3)]-wf[yc(notria,1)]*wf[yc(notria,6)])/(wf[yc(notria,3)]-wf[yc(notria,6)]);
	yp1 = (wf[yc(notria,5)]*wf[yc(notria,3)]-wf[yc(notria,2)]*wf[yc(notria,6)])/(wf[yc(notria,3)]-wf[yc(notria,6)]);
	/*coordonnees de P2*/
	xp2 = (wf[yc(notria,7)]*wf[yc(notria,3)]-wf[yc(notria,1)]*wf[yc(notria,9)])/(wf[yc(notria,3)]-wf[yc(notria,9)]);
	yp2 = (wf[yc(notria,8)]*wf[yc(notria,3)]-wf[yc(notria,2)]*wf[yc(notria,9)])/(wf[yc(notria,3)]-wf[yc(notria,9)]);
	/*surface du triangle AP1P2*/
	S = 0.5*sqrt(pow(wf[yc(notria,3)]*(yp2-yp1),2.0)
	+pow(wf[yc(notria,3)]*(xp1-xp2),2.0)
	+pow((xp1-wf[yc(notria,1)])*(yp2-wf[yc(notria,2)])-(yp1-wf[yc(notria,2)])*(xp2-wf[yc(notria,1)]),2.0));
	
	/*surface mouillee*/
	SMo = S1 - S;
	}
	
if (wf[yc(notria,3)] < 0.0 && wf[yc(notria,6)] >= 0.0 && wf[yc(notria,9)] < 0.0)
	{
	/*On calcule les coordonnees des deux points d'intersection entre le
	triangle ABC (sommet 1,sommet 2,sommet 3)et la surface libre 
	d'apres le theoreme de thales*/
	/*coordonnees de P1*/
	xp1 = (wf[yc(notria,7)]*wf[yc(notria,6)]-wf[yc(notria,4)]*wf[yc(notria,9)])/(wf[yc(notria,6)]-wf[yc(notria,9)]);
	yp1 = (wf[yc(notria,8)]*wf[yc(notria,6)]-wf[yc(notria,5)]*wf[yc(notria,9)])/(wf[yc(notria,6)]-wf[yc(notria,9)]);
	/*coordonnees de P2*/
	xp2 = (wf[yc(notria,1)]*wf[yc(notria,6)]-wf[yc(notria,4)]*wf[yc(notria,3)])/(wf[yc(notria,6)]-wf[yc(notria,3)]);
	yp2 = (wf[yc(notria,2)]*wf[yc(notria,6)]-wf[yc(notria,5)]*wf[yc(notria,3)])/(wf[yc(notria,6)]-wf[yc(notria,3)]);
	/*surface du triangle BP1P2*/
	S = 0.5*sqrt(pow(wf[yc(notria,6)]*(yp2-yp1),2.0)
	+pow(wf[yc(notria,6)]*(xp1-xp2),2.0)
	+pow((xp1-wf[yc(notria,4)])*(yp2-wf[yc(notria,5)])-(yp1-wf[yc(notria,5)])*(xp2-wf[yc(notria,4)]),2.0));
	
	/*surface mouillee*/
	SMo = S1 - S;
	}
	
if (wf[yc(notria,3)] < 0.0 && wf[yc(notria,6)] < 0.0 && wf[yc(notria,9)] >= 0.0)
	{
	/*On calcule les coordonnees des deux points d'intersection entre le
	triangle ABC (sommet 1,sommet 2,sommet 3)et la surface libre 
	d'apres le theoreme de thales*/
	/*coordonnees de P1*/
	xp1 = (wf[yc(notria,1)]*wf[yc(notria,9)]-wf[yc(notria,7)]*wf[yc(notria,3)])/(wf[yc(notria,9)]-wf[yc(notria,3)]);
	yp1 = (wf[yc(notria,2)]*wf[yc(notria,9)]-wf[yc(notria,8)]*wf[yc(notria,3)])/(wf[yc(notria,9)]-wf[yc(notria,3)]);
	/*coordonnees de P2*/
	xp2 = (wf[yc(notria,4)]*wf[yc(notria,9)]-wf[yc(notria,7)]*wf[yc(notria,6)])/(wf[yc(notria,9)]-wf[yc(notria,6)]);
	yp2 = (wf[yc(notria,5)]*wf[yc(notria,9)]-wf[yc(notria,8)]*wf[yc(notria,6)])/(wf[yc(notria,9)]-wf[yc(notria,6)]);
	/*surface du triangle CP1P2*/
	S = 0.5*sqrt(pow(wf[yc(notria,9)]*(yp2-yp1),2.0)
	+pow(wf[yc(notria,9)]*(xp1-xp2),2.0)
	+pow((xp1-wf[yc(notria,7)])*(yp2-wf[yc(notria,8)])-(yp1-wf[yc(notria,8)])*(xp2-wf[yc(notria,7)]),2.0));
	
	/*surface mouillee*/
	SMo = S1 - S;
	}
	
if (wf[yc(notria,3)] < 0.0 && wf[yc(notria,6)] >= 0.0 && wf[yc(notria,9)] >= 0.0)
	{
	/*On calcule les coordonnees des deux points d'intersection entre le
	triangle ABC (sommet 1,sommet 2,sommet 3)et la surface libre 
	d'apres le theoreme de thales*/
	/*coordonnees de P1*/
	xp1 = (wf[yc(notria,1)]*wf[yc(notria,9)]-wf[yc(notria,7)]*wf[yc(notria,3)])/(wf[yc(notria,9)]-wf[yc(notria,3)]);
	yp1 = (wf[yc(notria,2)]*wf[yc(notria,9)]-wf[yc(notria,8)]*wf[yc(notria,3)])/(wf[yc(notria,9)]-wf[yc(notria,3)]);
	/*coordonnees de P2*/
	xp2 = (wf[yc(notria,1)]*wf[yc(notria,6)]-wf[yc(notria,4)]*wf[yc(notria,3)])/(wf[yc(notria,6)]-wf[yc(notria,3)]);
	yp2 = (wf[yc(notria,2)]*wf[yc(notria,6)]-wf[yc(notria,5)]*wf[yc(notria,3)])/(wf[yc(notria,6)]-wf[yc(notria,3)]);
	/*surface mouillee = surface du triangle AP1P2*/
	SMo = 0.5*sqrt(pow(wf[yc(notria,3)]*(yp1-yp2),2.0)
	+pow(wf[yc(notria,3)]*(xp2-xp1),2.0)
	+pow((xp2-wf[yc(notria,1)])*(yp1-wf[yc(notria,2)])-(yp2-wf[yc(notria,2)])*(xp1-wf[yc(notria,1)]),2.0));
	}

if (wf[yc(notria,3)] >= 0.0 && wf[yc(notria,6)] < 0.0 && wf[yc(notria,9)] >= 0.0)
	{
	/*On calcule les coordonnees des deux points d'intersection entre le
	triangle ABC (sommet 1,sommet 2,sommet 3)et la surface libre 
	d'apres le theoreme de thales*/
	/*coordonnees de P1*/
	xp1 = (wf[yc(notria,4)]*wf[yc(notria,3)]-wf[yc(notria,1)]*wf[yc(notria,6)])/(wf[yc(notria,3)]-wf[yc(notria,6)]);
	yp1 = (wf[yc(notria,5)]*wf[yc(notria,3)]-wf[yc(notria,2)]*wf[yc(notria,6)])/(wf[yc(notria,3)]-wf[yc(notria,6)]);
	/*coordonnees de P2*/
	xp2 = (wf[yc(notria,4)]*wf[yc(notria,9)]-wf[yc(notria,7)]*wf[yc(notria,6)])/(wf[yc(notria,9)]-wf[yc(notria,6)]);
	yp2 = (wf[yc(notria,5)]*wf[yc(notria,9)]-wf[yc(notria,8)]*wf[yc(notria,6)])/(wf[yc(notria,9)]-wf[yc(notria,6)]);
	/*surface mouillee = surface du triangle BP1P2*/
	SMo = 0.5*sqrt(pow(wf[yc(notria,6)]*(yp1-yp2),2.0)
	+pow(wf[yc(notria,6)]*(xp2-xp1),2.0)
	+pow((xp2-wf[yc(notria,4)])*(yp1-wf[yc(notria,5)])-(yp2-wf[yc(notria,5)])*(xp1-wf[yc(notria,4)]),2.0));
	}
	
if (wf[yc(notria,3)] >= 0.0 && wf[yc(notria,6)] >= 0.0 && wf[yc(notria,9)] < 0.0)
	{
	/*On calcule les coordonnees des deux points d'intersection entre le
	triangle ABC (sommet 1,sommet 2,sommet 3)et la surface libre 
	d'apres le theoreme de thales*/
	/*coordonnees de P1*/
	xp1 = (wf[yc(notria,7)]*wf[yc(notria,6)]-wf[yc(notria,4)]*wf[yc(notria,9)])/(wf[yc(notria,6)]-wf[yc(notria,9)]);
	yp1 = (wf[yc(notria,8)]*wf[yc(notria,6)]-wf[yc(notria,5)]*wf[yc(notria,9)])/(wf[yc(notria,6)]-wf[yc(notria,9)]);
	/*coordonnees de P2*/
	xp2 = (wf[yc(notria,7)]*wf[yc(notria,3)]-wf[yc(notria,1)]*wf[yc(notria,9)])/(wf[yc(notria,3)]-wf[yc(notria,9)]);
	yp2 = (wf[yc(notria,8)]*wf[yc(notria,3)]-wf[yc(notria,2)]*wf[yc(notria,9)])/(wf[yc(notria,3)]-wf[yc(notria,9)]);
	/*surface mouillee = surface du triangle CP1P2*/
	SMo = 0.5*sqrt(pow(wf[yc(notria,9)]*(yp1-yp2),2.0)
	+pow(wf[yc(notria,9)]*(xp2-xp1),2.0)
	+pow((xp2-wf[yc(notria,7)])*(yp1-wf[yc(notria,8)])-(yp2-wf[yc(notria,8)])*(xp1-wf[yc(notria,7)]),2.0));
	}
return SMo;
}
