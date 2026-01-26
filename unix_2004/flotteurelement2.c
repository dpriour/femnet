#define PRINCIPAL 0
#include "4c19.h"
//#define DEBUG

/* Prise en compte des efforts de flottabilite des elements, (on utilise pour ce calcul la longueur au repos de l element),
   par rapport a la cote 0, ainsi que des raideurs de flottabilite*/

void flotteurelement2()
{
	int    zi,no3,no6,cable;
	double f,lmouillee,dx,dy,dz,d1,d2,d3,d4,d5,d6,CC;
	  
	for (zi = 1 ; zi<= NOMBRE_ELEMENTS ; zi++) 
  	{
  		cable = Element[zi].type;
		if (TypeElement[cable].noeud_trainee == 1) //volume des barres reporté dans des cubes centrés sur les 2 extremités de la barre
		{
			//printf("zi %d lcube %lf pond %lf %lf avant  %lf %lf ",zi,Element[zi].lcube,Element[zi].pondFS[1],Element[zi].pondFS[2],waelem[no3],waelem[no6]);
			//extremite 1
	    		no3 = yb(zi,3); 	/*numero de la coordonnee selon z de l extremite  1 de l element*/
			waelem[no3]      += RHO * G * Element[zi].lcube * Element[zi].lcube * Element[zi].lcube * Element[zi].pondFS[1];
			if ((Element[zi].pondFS[1] > 0.0) && (Element[zi].pondFS[1] < 1.0))
				{
				ze[no3][eca] += RHO * G * Element[zi].lcube * Element[zi].lcube;
				}
			//extremite 2
	    		no6 = yb(zi,6); 	/*numero de la coordonnee selon z de l extremite  2 de l element*/
			waelem[no6]      += RHO * G * Element[zi].lcube * Element[zi].lcube * Element[zi].lcube * Element[zi].pondFS[2];
			if ((Element[zi].pondFS[2] > 0.0) && (Element[zi].pondFS[2] < 1.0))
				{
				ze[no6][eca] += RHO * G * Element[zi].lcube * Element[zi].lcube;
				}
			//printf("apres %lf %lf\n",waelem[no3],waelem[no6]);
		}

		if (TypeElement[cable].noeud_trainee != 1) //volume des barres reporté sur toute la longueur de la barre
		{
	    		no3 = yb(zi,3); 	/*numero de la coordonnee selon z de l extremite  1 de l element*/
	    		no6 = yb(zi,6); 	/*numero de la coordonnee selon z de l extremite  2 de l element*/

	    		dx = wf[yb(zi,4)]-wf[yb(zi,1)];
	    		dy = wf[yb(zi,5)]-wf[yb(zi,2)];
	    		dz = wf[yb(zi,6)]-wf[yb(zi,3)]; 
	    		CC = PI * Element[zi].diametrehydro * Element[zi].diametrehydro / 4.0 * RHO * G;

	    		if ((wf[no3] < 0.0) && (wf[no6] > 0.0))
	    		{
	     			/* element flottant no3 dans l eau no6 hors d eau*/
	      			lmouillee = Element[zi].lgrepos / (wf[no3] - wf[no6]) * wf[no3];
				/*printf("lm = %12.4lf ",lmouillee);*/
	      
	      			/*f : flottabilite de l element*/
	      			f = lmouillee * CC;
	      			/*printf("f = %12.4lf\n",f);*/
	      			
	      			waelem[no3] += f - f * lmouillee / 2.0 / Element[zi].lgrepos;
	      			waelem[no6] +=     f * lmouillee / 2.0 / Element[zi].lgrepos;
	     			 /*printf("fz2 = %12.4lf\n",f * lmouillee / 2.0 / Element[zi].lgrepos);*/
	      			/*di : derivee de lmouillee */
	      			d1=wf[no3]*dx/dz/Element[zi].lgrepos;
	      			d2=wf[no3]*dy/dz/Element[zi].lgrepos;
	      			d3=(wf[no3]/Element[zi].lgrepos)-Element[zi].lgrepos*(1/dz + wf[no3]/dz/dz);
	      			d4= -d1;
	      			d5= -d2;
	      			d6= wf[no3] *(Element[zi].lgrepos/dz/dz - 1/Element[zi].lgrepos);

				if (Structure.type_solver == 1)
				{
		      			ze[no3][eca        -2] += CC*d1*lmouillee/Element[zi].lgrepos -CC*d1 +CC*lmouillee*lmouillee*dx/2/Element[zi].lgrepos/Element[zi].lgrepos/Element[zi].lgrepos;
		      			ze[no3][eca        -1] += CC*d2*lmouillee/Element[zi].lgrepos -CC*d2 +CC*lmouillee*lmouillee*dy/2/Element[zi].lgrepos/Element[zi].lgrepos/Element[zi].lgrepos;
		      			ze[no3][eca          ] += CC*d3*lmouillee/Element[zi].lgrepos -CC*d3 +CC*lmouillee*lmouillee*dz/2/Element[zi].lgrepos/Element[zi].lgrepos/Element[zi].lgrepos;
		      			ze[no3][eca+no6-no3-2] += CC*d4*lmouillee/Element[zi].lgrepos -CC*d4 -CC*lmouillee*lmouillee*dx/2/Element[zi].lgrepos/Element[zi].lgrepos/Element[zi].lgrepos;
		      			ze[no3][eca+no6-no3-1] += CC*d5*lmouillee/Element[zi].lgrepos -CC*d5 -CC*lmouillee*lmouillee*dy/2/Element[zi].lgrepos/Element[zi].lgrepos/Element[zi].lgrepos;
		      			ze[no3][eca+no6-no3  ] += CC*d6*lmouillee/Element[zi].lgrepos -CC*d6 -CC*lmouillee*lmouillee*dz/2/Element[zi].lgrepos/Element[zi].lgrepos/Element[zi].lgrepos;
		     
		      			ze[no6][eca+no3-no6-2] += -CC*lmouillee*( d1 + lmouillee*dx/Element[zi].lgrepos/Element[zi].lgrepos)/2/Element[zi].lgrepos;
		      			ze[no6][eca+no3-no6-1] += -CC*lmouillee*( d2 + lmouillee*dy/Element[zi].lgrepos/Element[zi].lgrepos)/2/Element[zi].lgrepos;
		      			ze[no6][eca+no3-no6  ] += -CC*lmouillee*( d3 + lmouillee*dz/Element[zi].lgrepos/Element[zi].lgrepos)/2/Element[zi].lgrepos;
		      			ze[no6][eca        -2] +=  CC*lmouillee*(-d4 + lmouillee*dx/Element[zi].lgrepos/Element[zi].lgrepos)/2/Element[zi].lgrepos;
		      			ze[no6][eca        -1] +=  CC*lmouillee*(-d5 + lmouillee*dy/Element[zi].lgrepos/Element[zi].lgrepos)/2/Element[zi].lgrepos;
		      			ze[no6][eca          ] +=  CC*lmouillee*(-d6 + lmouillee*dz/Element[zi].lgrepos/Element[zi].lgrepos)/2/Element[zi].lgrepos;   
				}
				else if (Structure.type_solver == 2)
				{
					affectation_pardiso(CC*d1*lmouillee/Element[zi].lgrepos -CC*d1 +CC*lmouillee*lmouillee*dx/2/Element[zi].lgrepos/Element[zi].lgrepos/Element[zi].lgrepos, no3, no3-2);
					affectation_pardiso(CC*d2*lmouillee/Element[zi].lgrepos -CC*d2 +CC*lmouillee*lmouillee*dy/2/Element[zi].lgrepos/Element[zi].lgrepos/Element[zi].lgrepos, no3, no3-1);
					affectation_pardiso(CC*d3*lmouillee/Element[zi].lgrepos -CC*d3 +CC*lmouillee*lmouillee*dz/2/Element[zi].lgrepos/Element[zi].lgrepos/Element[zi].lgrepos, no3, no3);
					affectation_pardiso(CC*d4*lmouillee/Element[zi].lgrepos -CC*d4 -CC*lmouillee*lmouillee*dx/2/Element[zi].lgrepos/Element[zi].lgrepos/Element[zi].lgrepos, no3, no6-2);
					affectation_pardiso(CC*d5*lmouillee/Element[zi].lgrepos -CC*d5 -CC*lmouillee*lmouillee*dy/2/Element[zi].lgrepos/Element[zi].lgrepos/Element[zi].lgrepos, no3, no6-1);
					affectation_pardiso(CC*d6*lmouillee/Element[zi].lgrepos -CC*d6 -CC*lmouillee*lmouillee*dz/2/Element[zi].lgrepos/Element[zi].lgrepos/Element[zi].lgrepos, no3, no6);

					affectation_pardiso(-CC*lmouillee*(d1 + lmouillee*dx/Element[zi].lgrepos/Element[zi].lgrepos)/2/Element[zi].lgrepos, no6, no3-2);
					affectation_pardiso(-CC*lmouillee*(d2 + lmouillee*dy/Element[zi].lgrepos/Element[zi].lgrepos)/2/Element[zi].lgrepos, no6, no3-1);
					affectation_pardiso(-CC*lmouillee*(d3 + lmouillee*dz/Element[zi].lgrepos/Element[zi].lgrepos)/2/Element[zi].lgrepos, no6, no3);
					affectation_pardiso(CC*lmouillee*(-d4 + lmouillee*dx/Element[zi].lgrepos/Element[zi].lgrepos)/2/Element[zi].lgrepos, no6, no6-2);
					affectation_pardiso(CC*lmouillee*(-d5 + lmouillee*dy/Element[zi].lgrepos/Element[zi].lgrepos)/2/Element[zi].lgrepos, no6, no6-1);
					affectation_pardiso(CC*lmouillee*(-d6 + lmouillee*dz/Element[zi].lgrepos/Element[zi].lgrepos)/2/Element[zi].lgrepos, no6, no6);

				}

	   		}
	   
	    		if ((wf[no3] > 0.0) && (wf[no6] < 0.0))
	    		{
	      			/* element flottant no6 dans l eau no3 hors d eau*/
	      			lmouillee = Element[zi].lgrepos / (wf[no6] - wf[no3]) * wf[no6];
				/*printf("lm = %12.4lf ",lmouillee);*/
	      			f = lmouillee * CC;
	      			waelem[no3] +=     f * lmouillee / 2.0 / Element[zi].lgrepos;
	      			waelem[no6] += f - f * lmouillee / 2.0 / Element[zi].lgrepos;
	      			d1 = -wf[no6]*dx/dz/Element[zi].lgrepos;
	      			d2 = -wf[no6]*dy/dz/Element[zi].lgrepos;
	      			d3 = -wf[no6]*(1/Element[zi].lgrepos - Element[zi].lgrepos/dz/dz);
	      			d4 = -d1;
	      			d5 = -d5;
	      			d6 = Element[zi].lgrepos/dz + wf[no6]/Element[zi].lgrepos - wf[no6]*Element[zi].lgrepos/dz/dz;
	      
				if (Structure.type_solver == 1)
				{
		      			ze[no3][eca-2        ] += -CC*lmouillee*(d1 + lmouillee*dx/Element[zi].lgrepos/Element[zi].lgrepos)/2/Element[zi].lgrepos;
		      			ze[no3][eca-1        ] += -CC*lmouillee*(d2 + lmouillee*dy/Element[zi].lgrepos/Element[zi].lgrepos)/2/Element[zi].lgrepos;
		      			ze[no3][eca          ] += -CC*lmouillee*(d3 + lmouillee*dz/Element[zi].lgrepos/Element[zi].lgrepos)/2/Element[zi].lgrepos;
		      			ze[no3][eca+no6-no3-2] += CC*lmouillee*(-d4 + lmouillee*dx/Element[zi].lgrepos/Element[zi].lgrepos)/2/Element[zi].lgrepos;
		      			ze[no3][eca+no6-no3-1] += CC*lmouillee*(-d5 + lmouillee*dy/Element[zi].lgrepos/Element[zi].lgrepos)/2/Element[zi].lgrepos;
		      			ze[no3][eca+no6-no3  ] += CC*lmouillee*(-d6 + lmouillee*dz/Element[zi].lgrepos/Element[zi].lgrepos)/2/Element[zi].lgrepos;   

		      			ze[no6][eca+no3-no6-2] += CC*d1*lmouillee/Element[zi].lgrepos -CC*d1 +CC*lmouillee*lmouillee*dx/2/Element[zi].lgrepos/Element[zi].lgrepos/Element[zi].lgrepos;
		      			ze[no6][eca+no3-no6-1] += CC*d2*lmouillee/Element[zi].lgrepos -CC*d2 +CC*lmouillee*lmouillee*dy/2/Element[zi].lgrepos/Element[zi].lgrepos/Element[zi].lgrepos;
		      			ze[no6][eca+no3-no6  ] += CC*d3*lmouillee/Element[zi].lgrepos -CC*d3 +CC*lmouillee*lmouillee*dz/2/Element[zi].lgrepos/Element[zi].lgrepos/Element[zi].lgrepos;
		      			ze[no6][eca-2        ] += CC*d4*lmouillee/Element[zi].lgrepos -CC*d4 -CC*lmouillee*lmouillee*dx/2/Element[zi].lgrepos/Element[zi].lgrepos/Element[zi].lgrepos;
		      			ze[no6][eca-1        ] += CC*d5*lmouillee/Element[zi].lgrepos -CC*d5 -CC*lmouillee*lmouillee*dy/2/Element[zi].lgrepos/Element[zi].lgrepos/Element[zi].lgrepos;
		      			ze[no6][eca          ] += CC*d6*lmouillee/Element[zi].lgrepos -CC*d6 -CC*lmouillee*lmouillee*dz/2/Element[zi].lgrepos/Element[zi].lgrepos/Element[zi].lgrepos;
				}
				else if (Structure.type_solver == 2)
				{
					affectation_pardiso(-CC*lmouillee*(d1 + lmouillee*dx/Element[zi].lgrepos/Element[zi].lgrepos)/2/Element[zi].lgrepos, no3, no3-2);
					affectation_pardiso(-CC*lmouillee*(d2 + lmouillee*dy/Element[zi].lgrepos/Element[zi].lgrepos)/2/Element[zi].lgrepos, no3, no3-1);
					affectation_pardiso(-CC*lmouillee*(d3 + lmouillee*dz/Element[zi].lgrepos/Element[zi].lgrepos)/2/Element[zi].lgrepos, no3, no3);
					affectation_pardiso(CC*lmouillee*(-d4 + lmouillee*dx/Element[zi].lgrepos/Element[zi].lgrepos)/2/Element[zi].lgrepos, no3, no6-2);
					affectation_pardiso(CC*lmouillee*(-d5 + lmouillee*dy/Element[zi].lgrepos/Element[zi].lgrepos)/2/Element[zi].lgrepos, no3, no6-1);
					affectation_pardiso(CC*lmouillee*(-d6 + lmouillee*dz/Element[zi].lgrepos/Element[zi].lgrepos)/2/Element[zi].lgrepos, no3, no6);

					affectation_pardiso(CC*d1*lmouillee/Element[zi].lgrepos -CC*d1 +CC*lmouillee*lmouillee*dx/2/Element[zi].lgrepos/Element[zi].lgrepos/Element[zi].lgrepos, no6, no3-2);
					affectation_pardiso(CC*d2*lmouillee/Element[zi].lgrepos -CC*d2 +CC*lmouillee*lmouillee*dy/2/Element[zi].lgrepos/Element[zi].lgrepos/Element[zi].lgrepos, no6, no3-1);
					affectation_pardiso(CC*d3*lmouillee/Element[zi].lgrepos -CC*d3 +CC*lmouillee*lmouillee*dz/2/Element[zi].lgrepos/Element[zi].lgrepos/Element[zi].lgrepos, no6, no3);
					affectation_pardiso(CC*d4*lmouillee/Element[zi].lgrepos -CC*d4 -CC*lmouillee*lmouillee*dx/2/Element[zi].lgrepos/Element[zi].lgrepos/Element[zi].lgrepos, no6, no6-2);
					affectation_pardiso(CC*d5*lmouillee/Element[zi].lgrepos -CC*d5 -CC*lmouillee*lmouillee*dy/2/Element[zi].lgrepos/Element[zi].lgrepos/Element[zi].lgrepos, no6, no6-1);
					affectation_pardiso(CC*d6*lmouillee/Element[zi].lgrepos -CC*d6 -CC*lmouillee*lmouillee*dz/2/Element[zi].lgrepos/Element[zi].lgrepos/Element[zi].lgrepos, no6, no6);

				}
	    		}
	    
	    		if ((wf[no3] <= 0.0) && (wf[no6] <= 0.0))
	    		{
	      			/* element inonde */
	      			f = Element[zi].lgrepos * CC;
	      			waelem[no3] += f / 2.0;
	      			waelem[no6] += f / 2.0;
	       		}
	    
	    		if ((wf[no3] >= 0.0) && (wf[no6] >= 0.0))
	    		{
	     			/* element exonde */
	    		}
  		}
	}
}
