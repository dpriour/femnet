#define PRINCIPAL 0
#include "4c19.h"

void affectation_ze_rang(int za, int zb, double val)
	/*affectation in ze such as K[za][zb] = val;
	val = - dF_za/dX_zb*/
	{
	if (abs(zb-za) > eca)
		{
		printf("%s %d \n","Warning: DIM3 in filwin.h is too small, increase it up to",zb-za+1);
		exit(0);
		}
	ze[za][eca+zb-za] += val;
	if(rang[1][za]<zb)	rang[1][za]=zb;	//bottom limit
	if(rang[2][za]<zb)	rang[2][za]=zb;	//right  limit
	if(rang[3][za]>zb)	rang[3][za]=zb;	//top    limit
	if(rang[4][za]>zb)	rang[4][za]=zb;	//left   limit
	if(rang[1][zb]<za)	rang[1][zb]=za;
	if(rang[2][zb]<za)	rang[2][zb]=za;
	if(rang[3][zb]>za)	rang[3][zb]=za;
	if(rang[4][zb]>za)	rang[4][zb]=za;
	//exit(0);
	}


