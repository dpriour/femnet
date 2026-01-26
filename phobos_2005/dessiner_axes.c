#define PRINCIPAL 0
#include "phobos.h"

void dessiner_axes()
	{
	int pt,nb_pt,expx,nbbasex,nbticks;
	float x1,x2,y1,y2,Xmin,Xmax,Ymin,Ymax,basex;
  	char chaine[17];
	/*int Clip3(float *xx1,float *yy1,float *xx2,float *yy2);*/
	
	/*extremites des axes*/
	if (1.0+2.0*marge == 0.0){printf("1.0+2.0*marge = 0.0   \n");exit(0);}
	Xmin = ((1.0+marge)*binx + marge*baxx) / (1.0+2.0*marge);
	Xmax = ((1.0+marge)*baxx + marge*binx) / (1.0+2.0*marge);
	Ymin = ((1.0+marge)*biny + marge*baxy) / (1.0+2.0*marge);
	Ymax = ((1.0+marge)*baxy + marge*biny) / (1.0+2.0*marge);
	
	/*printf("Xmin %8.2f Ymin %8.2f   ",Xmin,Ymin);
	printf("Xmax %8.2f Ymax %8.2f \n",Xmax,Ymax);
 	printf("binx %8.2f biny %8.2f   ",binx,biny);
	printf("baxx %8.2f baxy %8.2f \n",baxx,baxy);
 	printf("cinx %8.2f ciny %8.2f   ",cinx,ciny);
	printf("caxx %8.2f caxy %8.2f \n",caxx,caxy);*/
 	
	/*calcul des ticks X*/
	/*expx = puissance de dix de la longueur de l axe*/
	expx = (int) floor(log10(Xmax-Xmin));
	/*basex = distance de base entre les Ticks*/
	basex = (float) pow(10.0,(double)expx);
	if (basex == 0.0){printf("basex = 0.0   \n");exit(0);}
	/*nbbasex = nb de ticks sur l axe*/
	nbbasex = (int) ((Xmax-Xmin) / basex);
	
	/*recalcul de basex et de nbbasex*/
	if ((nbbasex>=2) && (nbbasex<4)) 	basex = basex / 2.0;
	if ( nbbasex<2) 			basex = basex / 5.0;
	if (basex == 0.0){printf("basex = 0.0   \n");exit(0);}
	nbbasex = (int) ((Xmax-Xmin) / basex);
	
	/*printf("Xmin = %8.2f  Xmax = %8.2f  ",Xmin,Xmax);
	printf("expx = %4d  ",expx);
	printf("basex = %8.2f  ",basex);
	printf("nbbasex = %4d  \n",nbbasex);*/
	
	/*trace des ticks selon l axe X*/
	Color(BLACK);
	for (nbticks=0;nbticks<=nbbasex;nbticks++)
		{
		x1 = (floor(Xmin/basex)*basex + nbticks * basex - binx) / (baxx - binx);
		x2 = (floor(Xmin/basex)*basex + nbticks * basex - binx) / (baxx - binx);
		y1 = (Ymin - biny) / (baxy - biny);
		y2 = (Ymin + (baxy - biny) * marge * 0.25 - biny) / (baxy - biny);
		nb_pt = Clip3(&x1,&y1,&x2,&y2);
		if (nb_pt = 2)	Line(x1,y1,x2,y2);
    		sprintf(chaine,"%5.2f",floor(Xmin/basex)*basex + nbticks * basex);
		y1 = (Ymin - (baxy - biny) * marge * 0.5 - biny) / (baxy - biny);
    		if (nbticks!=nbbasex) Text(x1,y1,chaine);
		}
	if (Structure.orientation == 1)	Text(x1,y1,"Y");
	if (Structure.orientation == 2)	Text(x1,y1,"Z");
	if (Structure.orientation == 3)	Text(x1,y1,"X");
	
	
	/*calcul des ticks Y*/
	expx = (int) floor(log10(Ymax-Ymin));
	basex = (float) pow(10.0,(double)expx);
	if (basex == 0.0){printf("basex = 0.0   \n");exit(0);}
	nbbasex = (int) ((Ymax-Ymin) / basex);
	
	/*printf("Xmax-Xmin = %8.2f  ",Ymax-Ymin);
	printf("expx = %4d  ",expx);
	printf("basex = %8.2f  ",basex);
	printf("nbbasex = %4d  ",nbbasex);*/

	if ((nbbasex>=2) && (nbbasex<4)) 	basex = basex / 2.0;
	if ( nbbasex<2) 			basex = basex / 5.0;
	if (basex == 0.0){printf("basex = 0.0   \n");exit(0);}
	nbbasex = (int) ((Ymax-Ymin) / basex);
	
	/*printf("basex = %8.2f  ",basex);
	printf("nbbasex = %4d  \n",nbbasex);*/
	
	/*trace des ticks selon l axe Y*/
	Color(BLACK);
	for (nbticks=1;nbticks<=nbbasex;nbticks++)
		{ 
		x1 = (Xmin - binx) / (baxx - binx);
		x2 = (Xmin + (baxx - binx) * marge * 0.25 - binx) / (baxx - binx);
		y1 = (Ymin + nbticks * basex - biny) / (baxy - biny);
		y2 = (Ymin + nbticks * basex - biny) / (baxy - biny);
		y1 = (floor(Ymin/basex)*basex + nbticks * basex - biny) / (baxy - biny);
		y2 = (floor(Ymin/basex)*basex + nbticks * basex - biny) / (baxy - biny);
		nb_pt = Clip3(&x1,&y1,&x2,&y2);
		if (nb_pt = 2)	Line(x1,y1,x2,y2);
    		sprintf(chaine,"%5.2f",nbticks * basex);
    		sprintf(chaine,"%5.2f",(float) (floor(Ymin/basex)*basex + nbticks * basex));
		x1 = (Xmin - (baxx - binx) * marge * 0.9 - binx) / (baxx - binx);
    		if (nbticks!=nbbasex) Text(x1,y1,chaine);
		}
	if (Structure.orientation == 1)	Text(x1,y1,"Z");
	if (Structure.orientation == 2)	Text(x1,y1,"X");
	if (Structure.orientation == 3)	Text(x1,y1,"Y");
	
	
	/*trace des axes*/
	Color(BLACK);
	x1 = (Xmin - binx) / (baxx - binx);
	y1 = (Ymin - biny) / (baxy - biny);
	x2 = (Xmax - binx) / (baxx - binx);
	y2 = (Ymin - biny) / (baxy - biny);
	nb_pt = Clip3(&x1,&y1,&x2,&y2);
	if (nb_pt = 2)	Line(x1,y1,x2,y2);
	x1 = (Xmin - binx) / (baxx - binx);
	y1 = (Ymin - biny) / (baxy - biny);
	x2 = (Xmin - binx) / (baxx - binx);
	y2 = (Ymax - biny) / (baxy - biny);
	nb_pt = Clip3(&x1,&y1,&x2,&y2);
	if (nb_pt = 2)	Line(x1,y1,x2,y2);
	
	}

int Clip3(float *xx1,float *yy1,float *xx2,float *yy2)
	{
	double x1,y1,x2,y2;
	
	x1 = (double) *xx1;
	y1 = (double) *yy1;
	x2 = (double) *xx2;
	y2 = (double) *yy2;
	
	if ((x1>=0.0 && x1<=1.0) && (x2>=0.0 && x2<=1.0) && (y1>=0.0 && y1<=1.0) && (y2>=0.0 && y2<=1.0))
		{
		return 2;
		}

	if ((x1<0.0 && x2<0.0) || (x1>1.0 && x2>1.0) || (y1<0.0 && y2<0.0) || (y1>1.0 && y2>1.0) ) 
		{
		return 0;
		}

	
	if (x1<0.0)
		{
		if ((x2-x1) !=0.0)
			{
			y1 = y2 - (x2-0.0) * (y2-y1)/(x2-x1);
			}
		else
			{
			y1 = y2;	
			}
		x1=0.0;	
		}
	if ((x1<0.0 && x2<0.0) || (x1>1.0 && x2>1.0) || (y1<0.0 && y2<0.0) || (y1>1.0 && y2>1.0) ) 
		{
		return 0;
		}
	if (x2<0.0)
		{
		if ((x2-x1) !=0.0)
			{
			y2 = y2 - (x2-0.0) * (y2-y1)/(x2-x1);
			}
		else
			{
			y2 = y2;	
			}
		x2=0.0;	
		}
	if ((x1<0.0 && x2<0.0) || (x1>1.0 && x2>1.0) || (y1<0.0 && y2<0.0) || (y1>1.0 && y2>1.0) ) 
		{
		return 0;
		}
	if (x1>1.0)
		{
		if ((x2-x1) !=0.0)
			{
			y1 = y2 - (x2-1.0) * (y2-y1)/(x2-x1);
			}
		else
			{
			y1 = y2;	
			}
		x1=1.0;	
		}
	if ((x1<0.0 && x2<0.0) || (x1>1.0 && x2>1.0) || (y1<0.0 && y2<0.0) || (y1>1.0 && y2>1.0) ) 
		{
		return 0;
		}
	if (x2>1.0)
		{
		if ((x2-x1) !=0.0)
			{
			y2 = y2 - (x2-1.0) * (y2-y1)/(x2-x1);
			}
		else
			{
			y2 = y2;	
			}
		x2=1.0;	
		}

	if ((x1<0.0 && x2<0.0) || (x1>1.0 && x2>1.0) || (y1<0.0 && y2<0.0) || (y1>1.0 && y2>1.0) ) 
		{
		return 0;
		}
	if (y1<0.0)
		{
		if ((y2-y1) !=0.0)
			{
			x1 = x2 - (y2-0.0) * (x2-x1)/(y2-y1);
			}
		else
			{
			x1 = x2;	
			}
		y1=0.0;	
		}

	if ((x1<0.0 && x2<0.0) || (x1>1.0 && x2>1.0) || (y1<0.0 && y2<0.0) || (y1>1.0 && y2>1.0) ) 
		{
		return 0;
		}
	if (y2<0.0)
		{
		if ((y2-y1) !=0.0)
			{
			x2 = x2 - (y2-0.0) * (x2-x1)/(y2-y1);
			}
		else
			{
			x2 = x2;	
			}
		y2=0.0;	
		}

	if ((x1<0.0 && x2<0.0) || (x1>1.0 && x2>1.0) || (y1<0.0 && y2<0.0) || (y1>1.0 && y2>1.0) ) 
		{
		return 0;
		}
	if (y1>1.0)
		{
		if ((y2-y1) !=0.0)
			{
			x1 = x2 - (y2-1.0) * (x2-x1)/(y2-y1);
			}
		else
			{
			x1 = x2;	
			}
		y1=1.0;	
		}

	if ((x1<0.0 && x2<0.0) || (x1>1.0 && x2>1.0) || (y1<0.0 && y2<0.0) || (y1>1.0 && y2>1.0) ) 
		{
		return 0;
		}
	if (y2>1.0)
		{
		if ((y2-y1) !=0.0)
			{
			x2 = x2 - (y2-1.0) * (x2-x1)/(y2-y1);
			}
		else
			{
			x2 = x2;	
			}
		y2=1.0;	
		}

	if ((x1<0.0 && x2<0.0) || (x1>1.0 && x2>1.0) || (y1<0.0 && y2<0.0) || (y1>1.0 && y2>1.0) ) 
		{
		return 0;
		}

	*xx1 = (float) x1;
	*yy1 = (float) y1;
	*xx2 = (float) x2;
	*yy2 = (float) y2;
	return 2;
	}
