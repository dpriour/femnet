#define PRINCIPAL 0
#include "4c19.h"

void libere_memoire_dyna()
	{
	/* libere la memoire alloue par malloc */
	if (Energy_bottom.nbx	!= NULL)        free(Energy_bottom.nbx);
	if (Energy_bottom.nby	!= NULL)        free(Energy_bottom.nby);
	if (Energy_bottom.nrj	!= NULL)        free(Energy_bottom.nrj);
	}



