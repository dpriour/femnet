#include "4c19.h"


void flotteurelement_dyna2()
{
	/* 
	Prise en compte des efforts de flottabilite des elements, (on utilise pour ce calcul la longueur au repos de l element),
	par rapport a la cote 0, ainsi que des raideurs de flottabilite
	Prise en compte de l'imersion dans la houle
	*/
	
  	int    zi,no3,no6,nd1,nd2;
  	double f,lmouillee,dx,dy,dz,d1,d2,d3,d4,d5,d6,CC,pp,qq;
  	double volum_elem,masse_elem,lonx,lony,lonz;
  
   	for (zi = 1 ; zi<= NOMBRE_ELEMENTS; zi++) 
  	{
		if (TypeElement[Element[zi].type].noeud_trainee == 1) //volume element rapporté aux 2 extremités
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

		if (TypeElement[Element[zi].type].noeud_trainee != 1)  //volume element rapporté sur toute la longueur de l element
		{
			nd1 = (int) rint(yb(zi,3)/3); 	/*numero du noeud de l extremite  1 de l element*/
			nd2 = (int) rint(yb(zi,6)/3); 	/*numero du noeud de l extremite  2 de l element*/

			no3 = yb(zi,3); 	/*numero de la coordonnee selon z de l extremite  1 de l element*/
			no6 = yb(zi,6); 	/*numero de la coordonnee selon z de l extremite  2 de l element*/

			dx = wf[yb(zi,4)]-wf[yb(zi,1)];
			dy = wf[yb(zi,5)]-wf[yb(zi,2)];
			dz = wf[yb(zi,6)]-wf[yb(zi,3)]; 
	    		CC = PI * Element[zi].diametrehydro * Element[zi].diametrehydro / 4.0 * RHO * G;

			pp = Element[zi].mass * G;

			qq = pp / 2.0 / Element[zi].lgrepos;

			if ((Noeud[nd1].imersion <= 0.0) && (Noeud[nd2].imersion > 0.0))
			{
     			/* element flottant nd2 dans l eau nd1 hors d eau*/
				/* element flottant nd1 dans l eau nd2 hors d eau*/
				lmouillee = Element[zi].lgwet; 
				/*f : flottabilite de l element*/
				f = lmouillee * pp;     			
				waelem[no3] += f - f * lmouillee / 2.0 / Element[zi].lgrepos;
				waelem[no6] +=     f * lmouillee / 2.0 / Element[zi].lgrepos;
				/*di : derivee de lgwet par xi*/
				d3 = - Element[zi].lgrepos * Noeud[nd2].imersion / (Noeud[nd1].imersion - Noeud[nd2].imersion) * (Noeud[nd1].imersion - Noeud[nd2].imersion);
				d6 =   Element[zi].lgrepos * Noeud[nd1].imersion / (Noeud[nd1].imersion - Noeud[nd2].imersion) * (Noeud[nd1].imersion - Noeud[nd2].imersion);
	    			if (Structure.type_solver == 1)
				{
      					ze[no3][eca          ] += (2.0 *qq * Element[zi].lgwet - pp) * d3;
     					ze[no3][eca+no6-no3  ] += (2.0 *qq * Element[zi].lgwet - pp) * d6;
      					ze[no6][eca+no3-no6  ] += -2.0 *qq * Element[zi].lgwet       * d3;
      					ze[no6][eca          ] += -2.0 *qq * Element[zi].lgwet       * d6;
		  		}
				else if (Structure.type_solver == 2)
      				{
					//affectation_pardiso((2.0 *qq * Element[zi].lgwet - pp) * d3, no3, no3);
					//affectation_pardiso((2.0 *qq * Element[zi].lgwet - pp) * d6, no3, no6);
					//affectation_pardiso(-2.0 *qq * Element[zi].lgwet * d3, no6, no3);
					//affectation_pardiso(-2.0 *qq * Element[zi].lgwet * d6, no6, no6);
      				}
       			}

	    		if ((Noeud[nd1].imersion > 0.0) && (Noeud[nd2].imersion <= 0.0))
	    		{
	     			/* element flottant nd2 dans l eau nd1 hors d eau*/
	      			lmouillee = Element[zi].lgwet;
	     			/*f : flottabilite de l element*/
	      			f = lmouillee * pp;
	      			waelem[no3] +=     f * lmouillee / 2.0 / Element[zi].lgrepos;
	      			waelem[no6] += f - f * lmouillee / 2.0 / Element[zi].lgrepos;

	      			/*di : derivee de lgwet par xi*/
	      			d3 =   Element[zi].lgrepos * Noeud[nd2].imersion / (Noeud[nd1].imersion - Noeud[nd2].imersion) * (Noeud[nd1].imersion - Noeud[nd2].imersion);
	      			d6 = - Element[zi].lgrepos * Noeud[nd1].imersion / (Noeud[nd1].imersion - Noeud[nd2].imersion) * (Noeud[nd1].imersion - Noeud[nd2].imersion);

	    			if (Structure.type_solver == 1)
				{
		    			ze[no3][eca          ] += -2.0 *qq * Element[zi].lgwet       * d3;
		      			ze[no3][eca+no6-no3  ] += -2.0 *qq * Element[zi].lgwet       * d6;
		      			ze[no6][eca+no3-no6  ] += (2.0 *qq * Element[zi].lgwet - pp) * d3;
		      			ze[no6][eca          ] += (2.0 *qq * Element[zi].lgwet - pp) * d6; 
		  		}
				else if (Structure.type_solver == 2)
				{
					//affectation_pardiso(-2.0 *qq * Element[zi].lgwet       * d3, no3, no3);
					//affectation_pardiso(-2.0 *qq * Element[zi].lgwet       * d6, no3, no6);
					//affectation_pardiso((2.0 *qq * Element[zi].lgwet - pp) * d3, no6, no3);
					//affectation_pardiso((2.0 *qq * Element[zi].lgwet - pp) * d6, no6, no6);
				}
	      		}
	    		if ((Noeud[nd1].imersion < 0.0) && (Noeud[nd2].imersion < 0.0))
	    		{
	     			/* element inonde*/
	      			f = Element[zi].lgwet * pp;
	      			waelem[no3] += f / 2.0;
	      			waelem[no6] += f / 2.0;
	      		}
	    		if ((Noeud[nd1].imersion >= 0.0) && (Noeud[nd2].imersion >= 0.0))
	    		{
	     			/* element exonde*/
	      		}

		}
  	}
}
