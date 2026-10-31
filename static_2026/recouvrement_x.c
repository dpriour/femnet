#define PRINCIPAL 0
#include "4c19.h"

int recouvrement_x(int element1, int element2, double *min, double *max, double *mean)
	{
  	int trouve,zi,zj,ex;
  	double x1,y1,x21,y21,x22,y22,xp,yp;
  	
  	trouve = 0;
  	*min = 0.0;
  	*max = 0.0;
  	*mean = 0.0;
  	
  	for (zi = 1 ; zi<= NOMBRE_ELEMENTS ; zi++)
  		{
	  	if (Element[zi].type == element1)
	  		{
		  	for (ex = 1 ; ex<= 2 ; ex++)
		  		{
		  		/*for each extremity*/
		  		x1 = wf[yb(zi,3*ex-2)];		/*x coordinate of the 1st barre extremity 1*/
		  		y1 = wf[yb(zi,3*ex-1)];		/*y coordinate of the 1st barre extremity 1*/
			  	for (zj = 1 ; zj<= NOMBRE_ELEMENTS ; zj++)
			  		{
				  	if (Element[zj].type == element2)
				  		{
				  		x21 = wf[yb(zj,1)];		/*x coordinate of the 2d barre extremity 1*/
				  		y21 = wf[yb(zj,2)];		/*y coordinate of the 2d barre extremity 1*/
				  		x22 = wf[yb(zj,4)];		/*x coordinate of the 2d barre extremity 2*/
				  		y22 = wf[yb(zj,5)];		/*y coordinate of the 2d barre extremity 2*/
				  		if ((y1>=y21) && (y1<y22))
				  			{
				  			/*point 1 is in front of 2d barre*/
				  			yp = y1;
				  			xp = x21 + (x22-x21)*(yp-y21)/(y22-y21);
				  			if (trouve == 0)
				  				{
				  				*min = xp-x1;
				  				*max = xp-x1;
				  				*mean = xp-x1;
								/*printf("\na 1 %lf %lf 21 %lf %lf 22 %lf %lf p %lf %lf min %lf max %lf mean %lf\n",x1,y1,x21,y21,x22,y22,xp,yp,*min,*max,*mean);*/
								/*printf("\na ex %d trouve %d zi %d zj %d y1 %lf y21 %lf y22 %lf\n",ex,trouve,zi,zj,y1,y21,y22);*/
				  				}
				  			else
				  				{
				  				if (*min > xp-x1) *min = xp-x1;
				  				if (*max < xp-x1) *max = xp-x1;
				  				*mean = (*mean*trouve+(xp-x1))/(trouve+1);
								/*printf("\nb 1 %lf %lf 21 %lf %lf 22 %lf %lf p %lf %lf min %lf max %lf mean %lf\n",x1,y1,x21,y21,x22,y22,xp,yp,*min,*max,*mean);*/
								/*printf("\nb ex %d trouve %d zi %d zj %d y1 %lf y21 %lf y22 %lf\n",ex,trouve,zi,zj,y1,y21,y22);*/
				  				}
				  			trouve++;
				  			}
				  		if ((y1<y21) && (y1>=y22))
				  			{
				  			/*point 1 is in front of 2d barre*/
				  			yp = y1;
				  			xp = x21 + (x22-x21)*(yp-y21)/(y22-y21);
				  			if (trouve == 0)
				  				{
				  				*min = xp-x1;
				  				*max = xp-x1;
				  				*mean = xp-x1;
								/*printf("\nc 1 %lf %lf 21 %lf %lf 22 %lf %lf p %lf %lf min %lf max %lf mean %lf\n",x1,y1,x21,y21,x22,y22,xp,yp,*min,*max,*mean);*/
								/*printf("\nc ex %d trouve %d zi %d zj %d y1 %lf y21 %lf y22 %lf\n",ex,trouve,zi,zj,y1,y21,y22);*/
				  				}
				  			else
				  				{
				  				if (*min > xp-x1) *min = xp-x1;
				  				if (*max < xp-x1) *max = xp-x1;
				  				*mean = (*mean*trouve+(xp-x1))/(trouve+1);
								/*printf("\nd 1 %lf %lf 21 %lf %lf 22 %lf %lf p %lf %lf min %lf max %lf mean %lf\n",x1,y1,x21,y21,x22,y22,xp,yp,*min,*max,*mean);*/
								/*printf("\nd ex %d trouve %d zi %d zj %d y1 %lf y21 %lf y22 %lf\n",ex,trouve,zi,zj,y1,y21,y22);*/
				  				}
				  			trouve++;
				  			}
				  		}		  		
			  		}
		  		}
	  		}
	  	if (Element[zi].type == element2)
	  		{
		  	for (ex = 1 ; ex<= 2 ; ex++)
		  		{
		  		/*for each extremity*/
		  		x1 = -wf[yb(zi,3*ex-2)];		/*x coordinate of the 1st barre extremity 1*/
		  		y1 = -wf[yb(zi,3*ex-1)];		/*y coordinate of the 1st barre extremity 1*/
			  	for (zj = 1 ; zj<= NOMBRE_ELEMENTS ; zj++)
			  		{
				  	if (Element[zj].type == element1)
				  		{
				  		x21 = -wf[yb(zj,1)];		/*x coordinate of the 2d barre extremity 1*/
				  		y21 = -wf[yb(zj,2)];		/*y coordinate of the 2d barre extremity 1*/
				  		x22 = -wf[yb(zj,4)];		/*x coordinate of the 2d barre extremity 2*/
				  		y22 = -wf[yb(zj,5)];		/*y coordinate of the 2d barre extremity 2*/
				  		if ((y1>=y21) && (y1<y22))
				  			{
				  			/*point 1 is in front of 2d barre*/
				  			yp = y1;
				  			xp = x21 + (x22-x21)*(yp-y21)/(y22-y21);
				  			if (trouve == 0)
				  				{
				  				*min = xp-x1;
				  				*max = xp-x1;
				  				*mean = xp-x1;
								/*printf("\ne 1 %lf %lf 21 %lf %lf 22 %lf %lf p %lf %lf min %lf max %lf mean %lf\n",x1,y1,x21,y21,x22,y22,xp,yp,*min,*max,*mean);*/
								/*printf("\ne ex %d trouve %d zi %d zj %d y1 %lf y21 %lf y22 %lf\n",ex,trouve,zi,zj,y1,y21,y22);*/
				  				}
				  			else
				  				{
				  				if (*min > xp-x1) *min = xp-x1;
				  				if (*max < xp-x1) *max = xp-x1;
				  				*mean = (*mean*trouve+(xp-x1))/(trouve+1);
								/*printf("\nf 1 %lf %lf 21 %lf %lf 22 %lf %lf p %lf %lf min %lf max %lf mean %lf\n",x1,y1,x21,y21,x22,y22,xp,yp,*min,*max,*mean);*/
								/*printf("\nf ex %d trouve %d zi %d zj %d y1 %lf y21 %lf y22 %lf\n",ex,trouve,zi,zj,y1,y21,y22);*/
				  				}
				  			trouve++;
				  			}
				  		if ((y1<y21) && (y1>=y22))
				  			{
				  			/*point 1 is in front of 2d barre*/
				  			yp = y1;
				  			xp = x21 + (x22-x21)*(yp-y21)/(y22-y21);
				  			if (trouve == 0)
				  				{
				  				*min = xp-x1;
				  				*max = xp-x1;
				  				*mean = xp-x1;
								/*printf("\ng 1 %lf %lf 21 %lf %lf 22 %lf %lf p %lf %lf min %lf max %lf mean %lf\n",x1,y1,x21,y21,x22,y22,xp,yp,*min,*max,*mean);*/
								/*printf("\ng ex %d trouve %d zi %d zj %d y1 %lf y21 %lf y22 %lf\n",ex,trouve,zi,zj,y1,y21,y22);*/
				  				}
				  			else
				  				{
				  				if (*min > xp-x1) *min = xp-x1;
				  				if (*max < xp-x1) *max = xp-x1;
				  				*mean = (*mean*trouve+(xp-x1))/(trouve+1);
								/*printf("\nh 1 %lf %lf 21 %lf %lf 22 %lf %lf p %lf %lf min %lf max %lf mean %lf\n",x1,y1,x21,y21,x22,y22,xp,yp,*min,*max,*mean);*/
								/*printf("\nh ex %d trouve %d zi %d zj %d y1 %lf y21 %lf y22 %lf\n",ex,trouve,zi,zj,y1,y21,y22);*/
				  				}
				  			trouve++;
				  			}
				  		}		  		
			  		}
		  		}
	  		}
	  	}
  	
  	
  	
	return trouve;	
	}




