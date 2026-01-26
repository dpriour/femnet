#define PRINCIPAL 0
#include "phobos.h"

/*Visualisation************************************************************/

void Checked_dessiner_contour_hexa()
	{
	int mode;
	mode = GetMenuItemChecked(w[73]);
	if (mode == 0) SetMenuItemChecked(w[73],1);
	if (mode == 1) SetMenuItemChecked(w[73],0);
	dessiner();
	}

void Checked_dessiner_contour_panneau()
	{
	int mode;
	mode = GetMenuItemChecked(w[6]);
	if (mode == 0) SetMenuItemChecked(w[6],1);
	if (mode == 1) SetMenuItemChecked(w[6],0);
	dessiner();
	}

void Checked_dessiner_contour_panel_cutting()
	{
	int mode;
	mode = GetMenuItemChecked(w[94]);
	if (mode == 0) SetMenuItemChecked(w[94],1);
	if (mode == 1) SetMenuItemChecked(w[94],0);
	dessiner();
	}

void Checked_dessiner_contour_element()
	{
	int mode;
	mode = GetMenuItemChecked(w[9]);
	if (mode == 0) SetMenuItemChecked(w[9],1);
	if (mode == 1) SetMenuItemChecked(w[9],0);
	dessiner();
	}

void Checked_dessiner_contour_winch()
	{
	int mode;
	mode = GetMenuItemChecked(w[87]);
	if (mode == 0) SetMenuItemChecked(w[87],1);
	if (mode == 1) SetMenuItemChecked(w[87],0);
	dessiner();
	}

void Checked_dessiner_contour_coulisse()
	{
	int mode;
	mode = GetMenuItemChecked(w[69]);
	if (mode == 0) SetMenuItemChecked(w[69],1);
	if (mode == 1) SetMenuItemChecked(w[69],0);
	dessiner();
	}

void Checked_dessiner_contour_balls()
	{
	int mode;
	mode = GetMenuItemChecked(w[89]);
	if (mode == 0) SetMenuItemChecked(w[89],1);
	if (mode == 1) SetMenuItemChecked(w[89],0);
	dessiner();
	}

void Checked_dessiner_liaison()
	{
	int mode;
	mode = GetMenuItemChecked(w[10]);
	if (mode == 0) SetMenuItemChecked(w[10],1);
	if (mode == 1) SetMenuItemChecked(w[10],0);
	dessiner();
	}

void Checked_angle_flexion_cable()
	{
	int mode;
	mode = GetMenuItemChecked(w[100]);
	if (mode == 0) SetMenuItemChecked(w[100],1);
	if (mode == 1) SetMenuItemChecked(w[100],0);
	dessiner();
	}

void Checked_dessiner_lie()
	{
	int mode;
	mode = GetMenuItemChecked(w[15]);
	if (mode == 0) SetMenuItemChecked(w[15],1);
	if (mode == 1) SetMenuItemChecked(w[15],0);
	dessiner();
	}
	
void Checked_filet_contour()
	{
	int mode;
	mode = GetMenuItemChecked(w[19]);
	if (mode == 0) SetMenuItemChecked(w[19],1);
	if (mode == 1) SetMenuItemChecked(w[19],0);
	dessiner();
	}
	
void Checked_filet_interne()
	{
	int mode;
	mode = GetMenuItemChecked(w[20]);
	if (mode == 0) SetMenuItemChecked(w[20],1);
	if (mode == 1) SetMenuItemChecked(w[20],0);
	dessiner();
	}
	
void Checked_internal_bar()
	{
	int mode;
	mode = GetMenuItemChecked(w[95]);
	if (mode == 0) SetMenuItemChecked(w[95],1);
	if (mode == 1) SetMenuItemChecked(w[95],0);
	dessiner();
	}
	
void Checked_orientation_uv()
	{
	int mode;
	mode = GetMenuItemChecked(w[32]);
	if (mode == 0) 
		{
		SetMenuItemChecked(w[32],1);
		SetMenuItemChecked(w[33],0);
		SetMenuItemChecked(w[34],0);
		}
	if (mode == 1) SetMenuItemChecked(w[32],0);
	dessiner();
	}
	
void Checked_orientation_UV()
	{
	int mode;
	mode = GetMenuItemChecked(w[33]);
	if (mode == 0) 
		{
		SetMenuItemChecked(w[33],1);
		SetMenuItemChecked(w[32],0);
		SetMenuItemChecked(w[34],0);
		}
	if (mode == 1) SetMenuItemChecked(w[33],0);
	dessiner();
	}
	
void Checked_orientation_xy()
	{
	int mode;
	mode = GetMenuItemChecked(w[34]);
	if (mode == 0) 
		{
		SetMenuItemChecked(w[34],1);
		SetMenuItemChecked(w[32],0);
		SetMenuItemChecked(w[33],0);
		}
	if (mode == 1) SetMenuItemChecked(w[34],0);
	dessiner();
	}

	
void Checked_fils_contour()
	{
	int mode;
	mode = GetMenuItemChecked(w[29]);
	if (mode == 0) SetMenuItemChecked(w[29],1);
	if (mode == 1) SetMenuItemChecked(w[29],0);
	dessiner();
	}
	
void Checked_UV_Vectors()
	{
	int mode;
	mode = GetMenuItemChecked(w[91]);
	if (mode == 0) SetMenuItemChecked(w[91],1);
	if (mode == 1) SetMenuItemChecked(w[91],0);
	dessiner();
	}
	
void Checked_axe_T90()
	{
	int mode;
	mode = GetMenuItemChecked(w[90]);
	if (mode == 0) SetMenuItemChecked(w[90],1);
	if (mode == 1) SetMenuItemChecked(w[90],0);
	dessiner();
	}
	
void Checked_dessiner_axes()
	{
	int mode;
	mode = GetMenuItemChecked(w[75]);
	if (mode == 0) SetMenuItemChecked(w[75],1);
	if (mode == 1) SetMenuItemChecked(w[75],0);
	dessiner();
	}
	
/*Affichage***********************************************************/
void Checked_numerotation_globale()
	{
	int mode;
	mode = GetMenuItemChecked(w[83]);
	if (mode == 0) 
		{
		SetMenuItemChecked(w[83],1);
		SetMenuItemChecked(w[74],0);
		SetMenuItemChecked(w[11],0);
		SetMenuItemChecked(w[12],0);
		SetMenuItemChecked(w[70],0);
		SetMenuItemChecked(w[8],0);
		SetMenuItemChecked(w[13],0);
		SetMenuItemChecked(w[28],0);
		SetMenuItemChecked(w[37],0);
		SetMenuItemChecked(w[56],0);
		SetMenuItemChecked(w[57],0);
		SetMenuItemChecked(w[58],0);
		SetMenuItemChecked(w[60],0);
		}
	if (mode == 1) SetMenuItemChecked(w[83],0);
	dessiner();
	}
	

void Checked_numerotation_hexa()
	{
	int mode;
	mode = GetMenuItemChecked(w[74]);
	if (mode == 0) SetMenuItemChecked(w[74],1);
	if (mode == 1) SetMenuItemChecked(w[74],0);
	dessiner();
	}

void Checked_numerotation_panneau()
	{
	int mode;
	mode = GetMenuItemChecked(w[11]);
	if (mode == 0) SetMenuItemChecked(w[11],1);
	if (mode == 1) SetMenuItemChecked(w[11],0);
	dessiner();
	}

void Checked_numerotation_element()
	{
	int mode;
	mode = GetMenuItemChecked(w[12]);
	if (mode == 0) SetMenuItemChecked(w[12],1);
	if (mode == 1) SetMenuItemChecked(w[12],0);
	dessiner();
	}

void Checked_numerotation_coulisse()
	{
	int mode;
	mode = GetMenuItemChecked(w[70]);
	if (mode == 0) SetMenuItemChecked(w[70],1);
	if (mode == 1) SetMenuItemChecked(w[70],0);
	dessiner();
	}

void Checked_numerotation_barre()
	{
	int mode;
	mode = GetMenuItemChecked(w[8]);
	if (mode == 0) SetMenuItemChecked(w[8],1);
	if (mode == 1) SetMenuItemChecked(w[8],0);
	dessiner();
	}

void Checked_order_liaison()
	{
	int mode;
	mode = GetMenuItemChecked(w[13]);
	if (mode == 0) 
		{
		SetMenuItemChecked(w[13],1);
		SetMenuItemChecked(w[103],0);
		}
	if (mode == 1) SetMenuItemChecked(w[13],0);
	dessiner();
	}
	
void Checked_numerotation_liaison()
	{
	int mode;
	mode = GetMenuItemChecked(w[103]);
	if (mode == 0) 
		{
		SetMenuItemChecked(w[103],1);
		SetMenuItemChecked(w[13],0);
		}
	if (mode == 1) SetMenuItemChecked(w[103],0);
	dessiner();
	}
	
void Checked_ordre_maillage()
	{
	int mode;
	mode = GetMenuItemChecked(w[85]);
	if (mode == 0) SetMenuItemChecked(w[85],1);
	if (mode == 1) SetMenuItemChecked(w[85],0);
	dessiner();
	}
	
void Checked_numerotation_triangle_contour()
	{
	int mode;
	mode = GetMenuItemChecked(w[28]);
	if (mode == 0) 
		{
		SetMenuItemChecked(w[28],1);
		}
	if (mode == 1) SetMenuItemChecked(w[28],0);
	dessiner();
	}

void Checked_numerotation_triangle_interieur()
	{
	int mode;
	mode = GetMenuItemChecked(w[37]);
	if (mode == 0) 
		{
		SetMenuItemChecked(w[37],1);
		}
	if (mode == 1) SetMenuItemChecked(w[37],0);
	dessiner();
	}
	
void Checked_courant()
	{
	int mode;
	mode = GetMenuItemChecked(w[56]);
	if (mode == 0) 
		{
		SetMenuItemChecked(w[56],1);
		}
	if (mode == 1) SetMenuItemChecked(w[56],0);
	dessiner();
	}
	
void Checked_prise()
	{
	int mode;
	mode = GetMenuItemChecked(w[57]);
	if (mode == 0) 
		{
		SetMenuItemChecked(w[57],1);
		}
	if (mode == 1) SetMenuItemChecked(w[57],0);
	dessiner();
	}

void Checked_frottement_fond()
	{
	int mode;
	mode = GetMenuItemChecked(w[58]);
	if (mode == 0) 
		{
		SetMenuItemChecked(w[58],1);
		}
	if (mode == 1) SetMenuItemChecked(w[58],0);
	dessiner();
	}

void Checked_surface_fils()
	{
	int mode;
	mode = GetMenuItemChecked(w[60]);
	if (mode == 0) 
		{
		SetMenuItemChecked(w[60],1);
		}
	if (mode == 1) SetMenuItemChecked(w[60],0);
	dessiner();
	}
	

/*Info Noeud*************************************************************/
void Checked_numerotation_total()
	{
	int mode;
	mode = GetMenuItemChecked(w[14]);
	if (mode == 0) 
		{
		SetMenuItemChecked(w[14],1);
		SetMenuItemChecked(w[23],0);
		SetMenuItemChecked(w[17],0);
		SetMenuItemChecked(w[18],0);
		SetMenuItemChecked(w[21],0);
		SetMenuItemChecked(w[24],0);
		SetMenuItemChecked(w[48],0);
		SetMenuItemChecked(w[49],0);
		SetMenuItemChecked(w[50],0);
		SetMenuItemChecked(w[51],0);
		SetMenuItemChecked(w[52],0);
		SetMenuItemChecked(w[53],0);
		SetMenuItemChecked(w[54],0);
		SetMenuItemChecked(w[55],0);
		SetMenuItemChecked(w[61],0);
		SetMenuItemChecked(w[62],0);
		}
	if (mode == 1) SetMenuItemChecked(w[14],0);
	dessiner();
	}

void Checked_numerotation_global()
	{
	int mode;
	mode = GetMenuItemChecked(w[23]);
	if (mode == 0) 
		{
		SetMenuItemChecked(w[14],0);
		SetMenuItemChecked(w[23],1);
		SetMenuItemChecked(w[17],0);
		SetMenuItemChecked(w[18],0);
		SetMenuItemChecked(w[21],0);
		SetMenuItemChecked(w[24],0);
		SetMenuItemChecked(w[48],0);
		SetMenuItemChecked(w[49],0);
		SetMenuItemChecked(w[50],0);
		SetMenuItemChecked(w[51],0);
		SetMenuItemChecked(w[52],0);
		SetMenuItemChecked(w[53],0);
		SetMenuItemChecked(w[54],0);
		SetMenuItemChecked(w[55],0);
		SetMenuItemChecked(w[61],0);
		SetMenuItemChecked(w[62],0);
		}
	if (mode == 1) SetMenuItemChecked(w[23],0);
	dessiner();
	}

void Checked_numerotation_local()
	{
	int mode;
	mode = GetMenuItemChecked(w[17]);
	if (mode == 0) 
		{
		SetMenuItemChecked(w[14],0);
		SetMenuItemChecked(w[23],0);
		SetMenuItemChecked(w[17],1);
		SetMenuItemChecked(w[18],0);
		SetMenuItemChecked(w[21],0);
		SetMenuItemChecked(w[24],0);
		SetMenuItemChecked(w[48],0);
		SetMenuItemChecked(w[49],0);
		SetMenuItemChecked(w[50],0);
		SetMenuItemChecked(w[51],0);
		SetMenuItemChecked(w[52],0);
		SetMenuItemChecked(w[53],0);
		SetMenuItemChecked(w[54],0);
		SetMenuItemChecked(w[55],0);
		SetMenuItemChecked(w[61],0);
		SetMenuItemChecked(w[62],0);
		}
	if (mode == 1) SetMenuItemChecked(w[17],0);
	dessiner();
	}
void Checked_numerotation_coin()
	{
	int mode;
	mode = GetMenuItemChecked(w[18]);
	if (mode == 0) 
		{
		SetMenuItemChecked(w[14],0);
		SetMenuItemChecked(w[23],0);
		SetMenuItemChecked(w[17],0);
		SetMenuItemChecked(w[18],1);
		SetMenuItemChecked(w[21],0);
		SetMenuItemChecked(w[24],0);
		SetMenuItemChecked(w[48],0);
		SetMenuItemChecked(w[49],0);
		SetMenuItemChecked(w[50],0);
		SetMenuItemChecked(w[51],0);
		SetMenuItemChecked(w[52],0);
		SetMenuItemChecked(w[53],0);
		SetMenuItemChecked(w[54],0);
		SetMenuItemChecked(w[55],0);
		SetMenuItemChecked(w[61],0);
		SetMenuItemChecked(w[62],0);
		}
	if (mode == 1) SetMenuItemChecked(w[18],0);
	dessiner();
	}

void Checked_numerotation_interieur()
	{
	int mode;
	mode = GetMenuItemChecked(w[21]);
	if (mode == 0) 
		{
		SetMenuItemChecked(w[14],0);
		SetMenuItemChecked(w[23],0);
		SetMenuItemChecked(w[17],0);
		SetMenuItemChecked(w[18],0);
		SetMenuItemChecked(w[21],1);
		SetMenuItemChecked(w[24],0);
		SetMenuItemChecked(w[48],0);
		SetMenuItemChecked(w[49],0);
		SetMenuItemChecked(w[50],0);
		SetMenuItemChecked(w[51],0);
		SetMenuItemChecked(w[52],0);
		SetMenuItemChecked(w[53],0);
		SetMenuItemChecked(w[54],0);
		SetMenuItemChecked(w[55],0);
		SetMenuItemChecked(w[61],0);
		SetMenuItemChecked(w[62],0);
		}
	if (mode == 1) SetMenuItemChecked(w[21],0);
	dessiner();
	}

void Checked_numerotation_type()
	{
	int mode;
	mode = GetMenuItemChecked(w[24]);
	if (mode == 0) 
		{
		SetMenuItemChecked(w[14],0);
		SetMenuItemChecked(w[23],0);
		SetMenuItemChecked(w[17],0);
		SetMenuItemChecked(w[18],0);
		SetMenuItemChecked(w[21],0);
		SetMenuItemChecked(w[24],1);
		SetMenuItemChecked(w[48],0);
		SetMenuItemChecked(w[49],0);
		SetMenuItemChecked(w[50],0);
		SetMenuItemChecked(w[51],0);
		SetMenuItemChecked(w[52],0);
		SetMenuItemChecked(w[53],0);
		SetMenuItemChecked(w[54],0);
		SetMenuItemChecked(w[55],0);
		SetMenuItemChecked(w[61],0);
		SetMenuItemChecked(w[62],0);
		}
	if (mode == 1) SetMenuItemChecked(w[24],0);
	dessiner();
	}

void Checked_valeur_masse()
	{
	int mode;
	mode = GetMenuItemChecked(w[48]);
	if (mode == 0) 
		{
		SetMenuItemChecked(w[14],0);
		SetMenuItemChecked(w[23],0);
		SetMenuItemChecked(w[17],0);
		SetMenuItemChecked(w[18],0);
		SetMenuItemChecked(w[21],0);
		SetMenuItemChecked(w[24],0);
		SetMenuItemChecked(w[48],1);
		SetMenuItemChecked(w[49],0);
		SetMenuItemChecked(w[50],0);
		SetMenuItemChecked(w[51],0);
		SetMenuItemChecked(w[52],0);
		SetMenuItemChecked(w[53],0);
		SetMenuItemChecked(w[54],0);
		SetMenuItemChecked(w[55],0);
		SetMenuItemChecked(w[61],0);
		SetMenuItemChecked(w[62],0);
		}
	if (mode == 1) SetMenuItemChecked(w[48],0);
	dessiner();
	}

void Checked_valeur_longueur()
	{
	int mode;
	mode = GetMenuItemChecked(w[49]);
	if (mode == 0) 
		{
		SetMenuItemChecked(w[14],0);
		SetMenuItemChecked(w[23],0);
		SetMenuItemChecked(w[17],0);
		SetMenuItemChecked(w[18],0);
		SetMenuItemChecked(w[21],0);
		SetMenuItemChecked(w[24],0);
		SetMenuItemChecked(w[48],0);
		SetMenuItemChecked(w[49],1);
		SetMenuItemChecked(w[50],0);
		SetMenuItemChecked(w[51],0);
		SetMenuItemChecked(w[52],0);
		SetMenuItemChecked(w[53],0);
		SetMenuItemChecked(w[54],0);
		SetMenuItemChecked(w[55],0);
		SetMenuItemChecked(w[61],0);
		SetMenuItemChecked(w[62],0);
		}
	if (mode == 1) SetMenuItemChecked(w[49],0);
	dessiner();
	}

void Checked_valeur_cd()
	{
	int mode;
	mode = GetMenuItemChecked(w[50]);
	if (mode == 0) 
		{
		SetMenuItemChecked(w[14],0);
		SetMenuItemChecked(w[23],0);
		SetMenuItemChecked(w[17],0);
		SetMenuItemChecked(w[18],0);
		SetMenuItemChecked(w[21],0);
		SetMenuItemChecked(w[24],0);
		SetMenuItemChecked(w[48],0);
		SetMenuItemChecked(w[49],0);
		SetMenuItemChecked(w[50],1);
		SetMenuItemChecked(w[51],0);
		SetMenuItemChecked(w[52],0);
		SetMenuItemChecked(w[53],0);
		SetMenuItemChecked(w[54],0);
		SetMenuItemChecked(w[55],0);
		SetMenuItemChecked(w[61],0);
		SetMenuItemChecked(w[62],0);
		}
	if (mode == 1) SetMenuItemChecked(w[50],0);
	dessiner();
	}

void Checked_valeur_effort_exterieur()
	{
	int mode;
	mode = GetMenuItemChecked(w[51]);
	if (mode == 0) 
		{
		SetMenuItemChecked(w[14],0);
		SetMenuItemChecked(w[23],0);
		SetMenuItemChecked(w[17],0);
		SetMenuItemChecked(w[18],0);
		SetMenuItemChecked(w[21],0);
		SetMenuItemChecked(w[24],0);
		SetMenuItemChecked(w[48],0);
		SetMenuItemChecked(w[49],0);
		SetMenuItemChecked(w[50],0);
		SetMenuItemChecked(w[51],1);
		SetMenuItemChecked(w[52],0);
		SetMenuItemChecked(w[53],0);
		SetMenuItemChecked(w[54],0);
		SetMenuItemChecked(w[55],0);
		SetMenuItemChecked(w[61],0);
		SetMenuItemChecked(w[62],0);
		}
	if (mode == 1) SetMenuItemChecked(w[51],0);
	dessiner();
	}

void Checked_valeur_fixation()
	{
	int mode;
	mode = GetMenuItemChecked(w[52]);
	if (mode == 0) 
		{
		SetMenuItemChecked(w[14],0);
		SetMenuItemChecked(w[23],0);
		SetMenuItemChecked(w[17],0);
		SetMenuItemChecked(w[18],0);
		SetMenuItemChecked(w[21],0);
		SetMenuItemChecked(w[24],0);
		SetMenuItemChecked(w[48],0);
		SetMenuItemChecked(w[49],0);
		SetMenuItemChecked(w[50],0);
		SetMenuItemChecked(w[51],0);
		SetMenuItemChecked(w[52],2);
		SetMenuItemChecked(w[53],0);
		SetMenuItemChecked(w[54],0);
		SetMenuItemChecked(w[55],0);
		SetMenuItemChecked(w[61],0);
		SetMenuItemChecked(w[62],0);
		}
	if (mode == 1) SetMenuItemChecked(w[52],0);
	dessiner();
	}

void Checked_valeur_limite()
	{
	int mode;
	mode = GetMenuItemChecked(w[53]);
	if (mode == 0) 
		{
		SetMenuItemChecked(w[14],0);
		SetMenuItemChecked(w[23],0);
		SetMenuItemChecked(w[17],0);
		SetMenuItemChecked(w[18],0);
		SetMenuItemChecked(w[21],0);
		SetMenuItemChecked(w[24],0);
		SetMenuItemChecked(w[48],0);
		SetMenuItemChecked(w[49],0);
		SetMenuItemChecked(w[50],0);
		SetMenuItemChecked(w[51],0);
		SetMenuItemChecked(w[52],0);
		SetMenuItemChecked(w[53],1);
		SetMenuItemChecked(w[54],0);
		SetMenuItemChecked(w[55],0);
		SetMenuItemChecked(w[61],0);
		SetMenuItemChecked(w[62],0);
		}
	if (mode == 1) SetMenuItemChecked(w[53],0);
	dessiner();
	}

void Checked_valeur_sens_limite()
	{
	int mode;
	mode = GetMenuItemChecked(w[54]);
	if (mode == 0) 
		{
		SetMenuItemChecked(w[14],0);
		SetMenuItemChecked(w[23],0);
		SetMenuItemChecked(w[17],0);
		SetMenuItemChecked(w[18],0);
		SetMenuItemChecked(w[21],0);
		SetMenuItemChecked(w[24],0);
		SetMenuItemChecked(w[48],0);
		SetMenuItemChecked(w[49],0);
		SetMenuItemChecked(w[50],0);
		SetMenuItemChecked(w[51],0);
		SetMenuItemChecked(w[52],0);
		SetMenuItemChecked(w[53],0);
		SetMenuItemChecked(w[54],1);
		SetMenuItemChecked(w[55],0);
		SetMenuItemChecked(w[61],0);
		SetMenuItemChecked(w[62],0);
		}
	if (mode == 1) SetMenuItemChecked(w[54],0);
	dessiner();
	}

void Checked_valeur_symetrie()
	{
	int mode;
	mode = GetMenuItemChecked(w[55]);
	if (mode == 0) 
		{
		SetMenuItemChecked(w[14],0);
		SetMenuItemChecked(w[23],0);
		SetMenuItemChecked(w[17],0);
		SetMenuItemChecked(w[18],0);
		SetMenuItemChecked(w[21],0);
		SetMenuItemChecked(w[24],0);
		SetMenuItemChecked(w[48],0);
		SetMenuItemChecked(w[49],0);
		SetMenuItemChecked(w[50],0);
		SetMenuItemChecked(w[51],0);
		SetMenuItemChecked(w[52],0);
		SetMenuItemChecked(w[53],0);
		SetMenuItemChecked(w[54],0);
		SetMenuItemChecked(w[55],1);
		SetMenuItemChecked(w[61],0);
		SetMenuItemChecked(w[62],0);
		}
	if (mode == 1) SetMenuItemChecked(w[55],0);
	dessiner();
	}

void Checked_nb_mailles()
	{
	int mode;
	mode = GetMenuItemChecked(w[61]);
	if (mode == 0) 
		{
		SetMenuItemChecked(w[14],0);
		SetMenuItemChecked(w[23],0);
		SetMenuItemChecked(w[17],0);
		SetMenuItemChecked(w[18],0);
		SetMenuItemChecked(w[21],0);
		SetMenuItemChecked(w[24],0);
		SetMenuItemChecked(w[48],0);
		SetMenuItemChecked(w[49],0);
		SetMenuItemChecked(w[50],0);
		SetMenuItemChecked(w[51],0);
		SetMenuItemChecked(w[52],0);
		SetMenuItemChecked(w[53],0);
		SetMenuItemChecked(w[54],0);
		SetMenuItemChecked(w[55],0);
		SetMenuItemChecked(w[61],1);
		SetMenuItemChecked(w[62],0);
		}
	if (mode == 1) SetMenuItemChecked(w[61],0);
	dessiner();
	}

void Checked_nb_cotes_mailles()
	{
	int mode;
	mode = GetMenuItemChecked(w[62]);
	if (mode == 0) 
		{
		SetMenuItemChecked(w[14],0);
		SetMenuItemChecked(w[23],0);
		SetMenuItemChecked(w[17],0);
		SetMenuItemChecked(w[18],0);
		SetMenuItemChecked(w[21],0);
		SetMenuItemChecked(w[24],0);
		SetMenuItemChecked(w[48],0);
		SetMenuItemChecked(w[49],0);
		SetMenuItemChecked(w[50],0);
		SetMenuItemChecked(w[51],0);
		SetMenuItemChecked(w[52],0);
		SetMenuItemChecked(w[53],0);
		SetMenuItemChecked(w[54],0);
		SetMenuItemChecked(w[55],0);
		SetMenuItemChecked(w[61],0);
		SetMenuItemChecked(w[62],1);
		}
	if (mode == 1) SetMenuItemChecked(w[62],0);
	dessiner();
	}


void Checked_longueur_cotes()
	{
	int mode;
	mode = GetMenuItemChecked(w[63]);
	if (mode == 0) 
		{
		SetMenuItemChecked(w[63],1);
		}
	if (mode == 1) SetMenuItemChecked(w[63],0);
	dessiner();
	}




void Checked_panel_cutting()
	{
	int mode;
	mode = GetMenuItemChecked(w[93]);
	if (mode == 0) 
		{
		SetMenuItemChecked(w[63],0);
		SetMenuItemChecked(w[93],1);
		}
	if (mode == 1) SetMenuItemChecked(w[93],0);
	dessiner();
	}



/*info element***************************************************************/
void Checked_raideur_traction()
	{
	int mode;
	mode = GetMenuItemChecked(w[39]);
	if (mode == 0) 
		{
		SetMenuItemChecked(w[39],1);
		SetMenuItemChecked(w[81],0);
		SetMenuItemChecked(w[82],0);
		SetMenuItemChecked(w[84],0);
		SetMenuItemChecked(w[86],0);
		SetMenuItemChecked(w[40],0);
		SetMenuItemChecked(w[76],0);
		SetMenuItemChecked(w[102],0);

		SetMenuItemChecked(w[41],0);
		SetMenuItemChecked(w[96],0);
		SetMenuItemChecked(w[42],0);
		SetMenuItemChecked(w[43],0);
		SetMenuItemChecked(w[77],0);
		SetMenuItemChecked(w[44],0);
		SetMenuItemChecked(w[45],0);
		SetMenuItemChecked(w[92],0);
		SetMenuItemChecked(w[46],0);
		SetMenuItemChecked(w[26],0);
		SetMenuItemChecked(w[64],0);
		SetMenuItemChecked(w[65],0);
		SetMenuItemChecked(w[66],0);
		SetMenuItemChecked(w[67],0);
		SetMenuItemChecked(w[68],0);
		SetMenuItemChecked(w[99],0);
		}
	if (mode == 1) SetMenuItemChecked(w[39],0);
	dessiner();
	}

void Checked_raideur_compression()
	{
	int mode;
	mode = GetMenuItemChecked(w[40]);
	if (mode == 0) 
		{
		SetMenuItemChecked(w[39],0);
		SetMenuItemChecked(w[81],0);
		SetMenuItemChecked(w[82],0);
		SetMenuItemChecked(w[84],0);
		SetMenuItemChecked(w[86],0);
		SetMenuItemChecked(w[40],1);
		SetMenuItemChecked(w[76],0);
		SetMenuItemChecked(w[102],0);

		SetMenuItemChecked(w[41],0);
		SetMenuItemChecked(w[96],0);
		SetMenuItemChecked(w[42],0);
		SetMenuItemChecked(w[43],0);
		SetMenuItemChecked(w[77],0);
		SetMenuItemChecked(w[44],0);
		SetMenuItemChecked(w[45],0);
		SetMenuItemChecked(w[92],0);
		SetMenuItemChecked(w[46],0);
		SetMenuItemChecked(w[26],0);
		SetMenuItemChecked(w[64],0);
		SetMenuItemChecked(w[65],0);
		SetMenuItemChecked(w[66],0);
		SetMenuItemChecked(w[67],0);
		SetMenuItemChecked(w[68],0);
		SetMenuItemChecked(w[99],0);
		}
	if (mode == 1) SetMenuItemChecked(w[40],0);
	dessiner();
	}

void Checked_raideur_ouverture()
	{
	int mode;
	mode = GetMenuItemChecked(w[76]);
	if (mode == 0) 
		{
		SetMenuItemChecked(w[39],0);
		SetMenuItemChecked(w[81],0);
		SetMenuItemChecked(w[82],0);
		SetMenuItemChecked(w[84],0);
		SetMenuItemChecked(w[86],0);
		SetMenuItemChecked(w[40],0);
		SetMenuItemChecked(w[76],1);
		SetMenuItemChecked(w[41],0);
		SetMenuItemChecked(w[96],0);
		SetMenuItemChecked(w[42],0);
		SetMenuItemChecked(w[43],0);
		SetMenuItemChecked(w[77],0);
		SetMenuItemChecked(w[44],0);
		SetMenuItemChecked(w[45],0);
		SetMenuItemChecked(w[92],0);
		SetMenuItemChecked(w[46],0);
		SetMenuItemChecked(w[26],0);
		SetMenuItemChecked(w[64],0);
		SetMenuItemChecked(w[65],0);
		SetMenuItemChecked(w[66],0);
		SetMenuItemChecked(w[67],0);
		SetMenuItemChecked(w[68],0);
		SetMenuItemChecked(w[99],0);
		}
	if (mode == 1) SetMenuItemChecked(w[76],0);
	dessiner();
	}

void Checked_twines_nb()
	{
	int mode;
	mode = GetMenuItemChecked(w[102]);
	if (mode == 0) 
		{
		SetMenuItemChecked(w[39],0);
		SetMenuItemChecked(w[81],0);
		SetMenuItemChecked(w[82],0);
		SetMenuItemChecked(w[84],0);
		SetMenuItemChecked(w[86],0);
		SetMenuItemChecked(w[40],0);
		SetMenuItemChecked(w[76],0);
		SetMenuItemChecked(w[102],1);
		SetMenuItemChecked(w[41],0);
		SetMenuItemChecked(w[96],0);
		SetMenuItemChecked(w[42],0);
		SetMenuItemChecked(w[43],0);
		SetMenuItemChecked(w[77],0);
		SetMenuItemChecked(w[44],0);
		SetMenuItemChecked(w[45],0);
		SetMenuItemChecked(w[92],0);
		SetMenuItemChecked(w[46],0);
		SetMenuItemChecked(w[26],0);
		SetMenuItemChecked(w[64],0);
		SetMenuItemChecked(w[65],0);
		SetMenuItemChecked(w[66],0);
		SetMenuItemChecked(w[67],0);
		SetMenuItemChecked(w[68],0);
		SetMenuItemChecked(w[99],0);
		}
	if (mode == 1) SetMenuItemChecked(w[102],0);
	dessiner();
	}

void Checked_longueur_repos()
	{
	int mode;
	mode = GetMenuItemChecked(w[41]);
	if (mode == 0) 
		{
		SetMenuItemChecked(w[39],0);
		SetMenuItemChecked(w[81],0);
		SetMenuItemChecked(w[82],0);
		SetMenuItemChecked(w[84],0);
		SetMenuItemChecked(w[86],0);
		SetMenuItemChecked(w[40],0);
		SetMenuItemChecked(w[76],0);
		SetMenuItemChecked(w[102],0);

		SetMenuItemChecked(w[41],1);
		SetMenuItemChecked(w[96],0);
		SetMenuItemChecked(w[42],0);
		SetMenuItemChecked(w[43],0);
		SetMenuItemChecked(w[77],0);
		SetMenuItemChecked(w[44],0);
		SetMenuItemChecked(w[45],0);
		SetMenuItemChecked(w[92],0);
		SetMenuItemChecked(w[46],0);
		SetMenuItemChecked(w[26],0);
		SetMenuItemChecked(w[64],0);
		SetMenuItemChecked(w[65],0);
		SetMenuItemChecked(w[66],0);
		SetMenuItemChecked(w[67],0);
		SetMenuItemChecked(w[68],0);
		SetMenuItemChecked(w[99],0);
		}
	if (mode == 1) SetMenuItemChecked(w[41],0);
	dessiner();
	}
	
void Checked_bar_length()
	{
	int mode;
	mode = GetMenuItemChecked(w[96]);
	if (mode == 0) 
		{
		SetMenuItemChecked(w[39],0);
		SetMenuItemChecked(w[81],0);
		SetMenuItemChecked(w[82],0);
		SetMenuItemChecked(w[84],0);
		SetMenuItemChecked(w[86],0);
		SetMenuItemChecked(w[40],0);
		SetMenuItemChecked(w[76],0);
		SetMenuItemChecked(w[102],0);

		SetMenuItemChecked(w[41],0);
		SetMenuItemChecked(w[96],1);
		SetMenuItemChecked(w[42],0);
		SetMenuItemChecked(w[43],0);
		SetMenuItemChecked(w[77],0);
		SetMenuItemChecked(w[44],0);
		SetMenuItemChecked(w[45],0);
		SetMenuItemChecked(w[92],0);
		SetMenuItemChecked(w[46],0);
		SetMenuItemChecked(w[26],0);
		SetMenuItemChecked(w[64],0);
		SetMenuItemChecked(w[65],0);
		SetMenuItemChecked(w[66],0);
		SetMenuItemChecked(w[67],0);
		SetMenuItemChecked(w[68],0);
		SetMenuItemChecked(w[99],0);
		}
	if (mode == 1) SetMenuItemChecked(w[96],0);
	dessiner();
	}
	
void Checked_longueur_tendue()
	{
	int mode;
	mode = GetMenuItemChecked(w[81]);
	if (mode == 0) 
		{
	        SetMenuItemChecked(w[39],0);
		SetMenuItemChecked(w[40],0);
		SetMenuItemChecked(w[76],0);
		SetMenuItemChecked(w[102],0);

		SetMenuItemChecked(w[41],0);
		SetMenuItemChecked(w[96],0);
		SetMenuItemChecked(w[81],1);
		SetMenuItemChecked(w[82],0);
		SetMenuItemChecked(w[84],0);
		SetMenuItemChecked(w[86],0);
		SetMenuItemChecked(w[42],0);
		SetMenuItemChecked(w[43],0);
		SetMenuItemChecked(w[77],0);
		SetMenuItemChecked(w[44],0);
		SetMenuItemChecked(w[45],0);
		SetMenuItemChecked(w[92],0);
		SetMenuItemChecked(w[46],0);
		SetMenuItemChecked(w[26],0);
		SetMenuItemChecked(w[64],0);
		SetMenuItemChecked(w[65],0);
		SetMenuItemChecked(w[66],0);
		SetMenuItemChecked(w[67],0);
		SetMenuItemChecked(w[68],0);
		SetMenuItemChecked(w[99],0);
		}
	if (mode == 1) SetMenuItemChecked(w[81],0);
	dessiner();
	}
	
void Checked_tension()
	{
	int mode;
	mode = GetMenuItemChecked(w[82]);
	if (mode == 0) 
		{
		SetMenuItemChecked(w[39],0);
		SetMenuItemChecked(w[40],0);
		SetMenuItemChecked(w[76],0);
		SetMenuItemChecked(w[102],0);

		SetMenuItemChecked(w[41],0);
		SetMenuItemChecked(w[96],0);
		SetMenuItemChecked(w[81],0);
		SetMenuItemChecked(w[82],1);
		SetMenuItemChecked(w[84],0);
		SetMenuItemChecked(w[86],0);
		SetMenuItemChecked(w[42],0);
		SetMenuItemChecked(w[43],0);
		SetMenuItemChecked(w[77],0);
		SetMenuItemChecked(w[44],0);
		SetMenuItemChecked(w[45],0);
		SetMenuItemChecked(w[92],0);
		SetMenuItemChecked(w[46],0);
		SetMenuItemChecked(w[26],0);
		SetMenuItemChecked(w[64],0);
		SetMenuItemChecked(w[65],0);
		SetMenuItemChecked(w[66],0);
		SetMenuItemChecked(w[67],0);
		SetMenuItemChecked(w[68],0);
		SetMenuItemChecked(w[99],0);
		}
	if (mode == 1) SetMenuItemChecked(w[82],0);
	dessiner();
	}
	
void Checked_nrj()
	{
	int mode;
	mode = GetMenuItemChecked(w[84]);
	if (mode == 0) 
		{
	        SetMenuItemChecked(w[39],0);
		SetMenuItemChecked(w[40],0);
		SetMenuItemChecked(w[76],0);
		SetMenuItemChecked(w[102],0);

		SetMenuItemChecked(w[41],0);
		SetMenuItemChecked(w[96],0);
		SetMenuItemChecked(w[81],0);
		SetMenuItemChecked(w[82],0);
		SetMenuItemChecked(w[84],1);
		SetMenuItemChecked(w[86],0);
		SetMenuItemChecked(w[42],0);
		SetMenuItemChecked(w[43],0);
		SetMenuItemChecked(w[77],0);
		SetMenuItemChecked(w[44],0);
		SetMenuItemChecked(w[45],0);
		SetMenuItemChecked(w[92],0);
		SetMenuItemChecked(w[46],0);
		SetMenuItemChecked(w[26],0);
		SetMenuItemChecked(w[64],0);
		SetMenuItemChecked(w[65],0);
		SetMenuItemChecked(w[66],0);
		SetMenuItemChecked(w[67],0);
		SetMenuItemChecked(w[68],0);
		SetMenuItemChecked(w[99],0);
		}
	if (mode == 1) SetMenuItemChecked(w[84],0);
	dessiner();
	}
	

void Checked_defaut_discretisation()
	{
	int mode;
	mode = GetMenuItemChecked(w[86]);
	if (mode == 0) 
		{
	        SetMenuItemChecked(w[39],0);
		SetMenuItemChecked(w[40],0);
		SetMenuItemChecked(w[76],0);
		SetMenuItemChecked(w[102],0);

		SetMenuItemChecked(w[41],0);
		SetMenuItemChecked(w[96],0);
		SetMenuItemChecked(w[81],0);
		SetMenuItemChecked(w[82],0);
		SetMenuItemChecked(w[84],0);
		SetMenuItemChecked(w[86],1);
		SetMenuItemChecked(w[42],0);
		SetMenuItemChecked(w[43],0);
		SetMenuItemChecked(w[77],0);
		SetMenuItemChecked(w[44],0);
		SetMenuItemChecked(w[45],0);
		SetMenuItemChecked(w[92],0);
		SetMenuItemChecked(w[46],0);
		SetMenuItemChecked(w[26],0);
		SetMenuItemChecked(w[64],0);
		SetMenuItemChecked(w[65],0);
		SetMenuItemChecked(w[66],0);
		SetMenuItemChecked(w[67],0);
		SetMenuItemChecked(w[68],0);
		SetMenuItemChecked(w[99],0);
		}
	if (mode == 1) SetMenuItemChecked(w[86],0);
	dessiner();
	}
	

void Checked_masse_volumique()
	{
	int mode;
	mode = GetMenuItemChecked(w[42]);
	if (mode == 0) 
		{
		SetMenuItemChecked(w[39],0);
		SetMenuItemChecked(w[81],0);
		SetMenuItemChecked(w[82],0);
		SetMenuItemChecked(w[84],0);
		SetMenuItemChecked(w[86],0);
		SetMenuItemChecked(w[40],0);
		SetMenuItemChecked(w[76],0);
		SetMenuItemChecked(w[102],0);

		SetMenuItemChecked(w[41],0);
		SetMenuItemChecked(w[96],0);
		SetMenuItemChecked(w[42],2);
		SetMenuItemChecked(w[43],0);
		SetMenuItemChecked(w[77],0);
		SetMenuItemChecked(w[44],0);
		SetMenuItemChecked(w[45],0);
		SetMenuItemChecked(w[92],0);
		SetMenuItemChecked(w[46],0);
		SetMenuItemChecked(w[26],0);
		SetMenuItemChecked(w[64],0);
		SetMenuItemChecked(w[65],0);
		SetMenuItemChecked(w[66],0);
		SetMenuItemChecked(w[67],0);
		SetMenuItemChecked(w[68],0);
		SetMenuItemChecked(w[99],0);
		}
	if (mode == 1) SetMenuItemChecked(w[42],0);
	dessiner();
	}

void Checked_diametre()
	{
	int mode;
	mode = GetMenuItemChecked(w[43]);
	if (mode == 0) 
		{
		SetMenuItemChecked(w[39],0);
		SetMenuItemChecked(w[81],0);
		SetMenuItemChecked(w[82],0);
		SetMenuItemChecked(w[84],0);
		SetMenuItemChecked(w[86],0);
		SetMenuItemChecked(w[40],0);
		SetMenuItemChecked(w[76],0);
		SetMenuItemChecked(w[102],0);

		SetMenuItemChecked(w[41],0);
		SetMenuItemChecked(w[96],0);
		SetMenuItemChecked(w[42],0);
		SetMenuItemChecked(w[43],1);
		SetMenuItemChecked(w[77],0);
		SetMenuItemChecked(w[44],0);
		SetMenuItemChecked(w[45],0);
		SetMenuItemChecked(w[92],0);
		SetMenuItemChecked(w[46],0);
		SetMenuItemChecked(w[26],0);
		SetMenuItemChecked(w[64],0);
		SetMenuItemChecked(w[65],0);
		SetMenuItemChecked(w[66],0);
		SetMenuItemChecked(w[67],0);
		SetMenuItemChecked(w[68],0);
		SetMenuItemChecked(w[99],0);
		}
	if (mode == 1) SetMenuItemChecked(w[43],0);
	dessiner();
	}

void Checked_largeur_noeud()
	{
	int mode;
	mode = GetMenuItemChecked(w[77]);
	if (mode == 0) 
		{
		SetMenuItemChecked(w[39],0);
		SetMenuItemChecked(w[81],0);
		SetMenuItemChecked(w[82],0);
		SetMenuItemChecked(w[84],0);
		SetMenuItemChecked(w[86],0);
		SetMenuItemChecked(w[40],0);
		SetMenuItemChecked(w[76],0);
		SetMenuItemChecked(w[102],0);

		SetMenuItemChecked(w[41],0);
		SetMenuItemChecked(w[96],0);
		SetMenuItemChecked(w[42],0);
		SetMenuItemChecked(w[43],0);
		SetMenuItemChecked(w[77],1);
		SetMenuItemChecked(w[44],0);
		SetMenuItemChecked(w[45],0);
		SetMenuItemChecked(w[92],0);
		SetMenuItemChecked(w[46],0);
		SetMenuItemChecked(w[26],0);
		SetMenuItemChecked(w[64],0);
		SetMenuItemChecked(w[65],0);
		SetMenuItemChecked(w[66],0);
		SetMenuItemChecked(w[67],0);
		SetMenuItemChecked(w[68],0);
		SetMenuItemChecked(w[99],0);
		}
	if (mode == 1) SetMenuItemChecked(w[77],0);
	dessiner();
	}

void Checked_coefficient_cd()
	{
	int mode;
	mode = GetMenuItemChecked(w[44]);
	if (mode == 0) 
		{
		SetMenuItemChecked(w[39],0);
		SetMenuItemChecked(w[81],0);
		SetMenuItemChecked(w[82],0);
		SetMenuItemChecked(w[84],0);
		SetMenuItemChecked(w[86],0);
		SetMenuItemChecked(w[40],0);
		SetMenuItemChecked(w[76],0);
		SetMenuItemChecked(w[102],0);

		SetMenuItemChecked(w[41],0);
		SetMenuItemChecked(w[96],0);
		SetMenuItemChecked(w[42],0);
		SetMenuItemChecked(w[43],0);
		SetMenuItemChecked(w[77],0);
		SetMenuItemChecked(w[44],1);
		SetMenuItemChecked(w[45],0);
		SetMenuItemChecked(w[92],0);
		SetMenuItemChecked(w[46],0);
		SetMenuItemChecked(w[26],0);
		SetMenuItemChecked(w[64],0);
		SetMenuItemChecked(w[65],0);
		SetMenuItemChecked(w[66],0);
		SetMenuItemChecked(w[67],0);
		SetMenuItemChecked(w[68],0);
		SetMenuItemChecked(w[99],0);
		}
	if (mode == 1) SetMenuItemChecked(w[44],0);
	dessiner();
	}

void Checked_coefficient_f()
	{
	int mode;
	mode = GetMenuItemChecked(w[45]);
	if (mode == 0) 
		{
		SetMenuItemChecked(w[39],0);
		SetMenuItemChecked(w[81],0);
		SetMenuItemChecked(w[82],0);
		SetMenuItemChecked(w[84],0);
		SetMenuItemChecked(w[86],0);
		SetMenuItemChecked(w[40],0);
		SetMenuItemChecked(w[76],0);
		SetMenuItemChecked(w[102],0);

		SetMenuItemChecked(w[41],0);
		SetMenuItemChecked(w[96],0);
		SetMenuItemChecked(w[42],0);
		SetMenuItemChecked(w[43],0);
		SetMenuItemChecked(w[77],0);
		SetMenuItemChecked(w[44],0);
		SetMenuItemChecked(w[45],1);
		SetMenuItemChecked(w[92],0);
		SetMenuItemChecked(w[46],0);
		SetMenuItemChecked(w[26],0);
		SetMenuItemChecked(w[64],0);
		SetMenuItemChecked(w[65],0);
		SetMenuItemChecked(w[66],0);
		SetMenuItemChecked(w[67],0);
		SetMenuItemChecked(w[68],0);
		SetMenuItemChecked(w[99],0);
		}
	if (mode == 1) SetMenuItemChecked(w[45],0);
	dessiner();
	}

void Checked_panel_drag()
	{
	int mode;
	mode = GetMenuItemChecked(w[92]);
	if (mode == 0) 
		{
		SetMenuItemChecked(w[39],0);
		SetMenuItemChecked(w[81],0);
		SetMenuItemChecked(w[82],0);
		SetMenuItemChecked(w[84],0);
		SetMenuItemChecked(w[86],0);
		SetMenuItemChecked(w[40],0);
		SetMenuItemChecked(w[76],0);
		SetMenuItemChecked(w[102],0);

		SetMenuItemChecked(w[41],0);
		SetMenuItemChecked(w[96],0);
		SetMenuItemChecked(w[42],0);
		SetMenuItemChecked(w[43],0);
		SetMenuItemChecked(w[77],0);
		SetMenuItemChecked(w[44],0);
		SetMenuItemChecked(w[45],0);
		SetMenuItemChecked(w[92],1);
		SetMenuItemChecked(w[46],0);
		SetMenuItemChecked(w[26],0);
		SetMenuItemChecked(w[64],0);
		SetMenuItemChecked(w[65],0);
		SetMenuItemChecked(w[66],0);
		SetMenuItemChecked(w[67],0);
		SetMenuItemChecked(w[68],0);
		SetMenuItemChecked(w[99],0);
		}
	if (mode == 1) SetMenuItemChecked(w[92],0);
	dessiner();
	}

void Checked_longueur_maillage()
	{
	int mode;
	mode = GetMenuItemChecked(w[46]);
	if (mode == 0) 
		{
		SetMenuItemChecked(w[39],0);
		SetMenuItemChecked(w[81],0);
		SetMenuItemChecked(w[82],0);
		SetMenuItemChecked(w[84],0);
		SetMenuItemChecked(w[86],0);
		SetMenuItemChecked(w[40],0);
		SetMenuItemChecked(w[76],0);
		SetMenuItemChecked(w[102],0);

		SetMenuItemChecked(w[41],0);
		SetMenuItemChecked(w[96],0);
		SetMenuItemChecked(w[42],0);
		SetMenuItemChecked(w[43],0);
		SetMenuItemChecked(w[77],0);
		SetMenuItemChecked(w[44],0);
		SetMenuItemChecked(w[45],0);
		SetMenuItemChecked(w[92],0);
		SetMenuItemChecked(w[46],1);
		SetMenuItemChecked(w[26],0);
		SetMenuItemChecked(w[64],0);
		SetMenuItemChecked(w[65],0);
		SetMenuItemChecked(w[66],0);
		SetMenuItemChecked(w[67],0);
		SetMenuItemChecked(w[68],0);
		SetMenuItemChecked(w[99],0);
		}
	if (mode == 1) SetMenuItemChecked(w[46],0);
	dessiner();
	}

void Checked_type_maillage()
	{
	int mode;
	mode = GetMenuItemChecked(w[26]);
	if (mode == 0) 
		{
		SetMenuItemChecked(w[39],0);
		SetMenuItemChecked(w[81],0);
		SetMenuItemChecked(w[82],0);
		SetMenuItemChecked(w[84],0);
		SetMenuItemChecked(w[86],0);
		SetMenuItemChecked(w[40],0);
		SetMenuItemChecked(w[76],0);
		SetMenuItemChecked(w[102],0);

		SetMenuItemChecked(w[41],0);
		SetMenuItemChecked(w[96],0);
		SetMenuItemChecked(w[42],0);
		SetMenuItemChecked(w[43],0);
		SetMenuItemChecked(w[77],0);
		SetMenuItemChecked(w[44],0);
		SetMenuItemChecked(w[45],0);
		SetMenuItemChecked(w[92],0);
		SetMenuItemChecked(w[46],0);
		SetMenuItemChecked(w[26],1);
		SetMenuItemChecked(w[64],0);
		SetMenuItemChecked(w[65],0);
		SetMenuItemChecked(w[66],0);
		SetMenuItemChecked(w[67],0);
		SetMenuItemChecked(w[68],0);
		SetMenuItemChecked(w[99],0);
		}
	if (mode == 1) SetMenuItemChecked(w[26],0);
	dessiner();
	}

void Checked_section_element()
	{
	int mode;
	mode = GetMenuItemChecked(w[64]);
	if (mode == 0) 
		{
		SetMenuItemChecked(w[39],0);
		SetMenuItemChecked(w[81],0);
		SetMenuItemChecked(w[82],0);
		SetMenuItemChecked(w[84],0);
		SetMenuItemChecked(w[86],0);
		SetMenuItemChecked(w[40],0);
		SetMenuItemChecked(w[76],0);
		SetMenuItemChecked(w[102],0);

		SetMenuItemChecked(w[41],0);
		SetMenuItemChecked(w[96],0);
		SetMenuItemChecked(w[42],0);
		SetMenuItemChecked(w[43],0);
		SetMenuItemChecked(w[77],0);
		SetMenuItemChecked(w[44],0);
		SetMenuItemChecked(w[45],0);
		SetMenuItemChecked(w[92],0);
		SetMenuItemChecked(w[46],0);
		SetMenuItemChecked(w[26],0);
		SetMenuItemChecked(w[64],1);
		SetMenuItemChecked(w[65],0);
		SetMenuItemChecked(w[66],0);
		SetMenuItemChecked(w[67],0);
		SetMenuItemChecked(w[68],0);
		SetMenuItemChecked(w[99],0);
		}
	if (mode == 1) SetMenuItemChecked(w[64],0);
	dessiner();
	}

	
void Checked_volume_element()
	{
	int mode;
	mode = GetMenuItemChecked(w[65]);
	if (mode == 0) 
		{
		SetMenuItemChecked(w[39],0);
		SetMenuItemChecked(w[81],0);
		SetMenuItemChecked(w[82],0);
		SetMenuItemChecked(w[84],0);
		SetMenuItemChecked(w[86],0);
		SetMenuItemChecked(w[40],0);
		SetMenuItemChecked(w[76],0);
		SetMenuItemChecked(w[102],0);

		SetMenuItemChecked(w[41],0);
		SetMenuItemChecked(w[96],0);
		SetMenuItemChecked(w[42],0);
		SetMenuItemChecked(w[43],0);
		SetMenuItemChecked(w[77],0);
		SetMenuItemChecked(w[44],0);
		SetMenuItemChecked(w[45],0);
		SetMenuItemChecked(w[92],0);
		SetMenuItemChecked(w[46],0);
		SetMenuItemChecked(w[26],0);
		SetMenuItemChecked(w[64],0);
		SetMenuItemChecked(w[65],1);
		SetMenuItemChecked(w[66],0);
		SetMenuItemChecked(w[67],0);
		SetMenuItemChecked(w[68],0);
		SetMenuItemChecked(w[99],0);
		}
	if (mode == 1) SetMenuItemChecked(w[65],0);
	dessiner();
	}

	
void Checked_masse_element()
	{
	int mode;
	mode = GetMenuItemChecked(w[66]);
	if (mode == 0) 
		{
		SetMenuItemChecked(w[39],0);
		SetMenuItemChecked(w[81],0);
		SetMenuItemChecked(w[82],0);
		SetMenuItemChecked(w[84],0);
		SetMenuItemChecked(w[86],0);
		SetMenuItemChecked(w[40],0);
		SetMenuItemChecked(w[76],0);
		SetMenuItemChecked(w[102],0);

		SetMenuItemChecked(w[41],0);
		SetMenuItemChecked(w[96],0);
		SetMenuItemChecked(w[42],0);
		SetMenuItemChecked(w[43],0);
		SetMenuItemChecked(w[77],0);
		SetMenuItemChecked(w[44],0);
		SetMenuItemChecked(w[45],0);
		SetMenuItemChecked(w[92],0);
		SetMenuItemChecked(w[46],0);
		SetMenuItemChecked(w[26],0);
		SetMenuItemChecked(w[64],0);
		SetMenuItemChecked(w[65],0);
		SetMenuItemChecked(w[66],1);
		SetMenuItemChecked(w[67],0);
		SetMenuItemChecked(w[68],0);
		SetMenuItemChecked(w[99],0);
		}
	if (mode == 1) SetMenuItemChecked(w[66],0);
	dessiner();
	}

	
void Checked_masse_lineique()
	{
	int mode;
	mode = GetMenuItemChecked(w[67]);
	if (mode == 0) 
		{
		SetMenuItemChecked(w[39],0);
		SetMenuItemChecked(w[81],0);
		SetMenuItemChecked(w[82],0);
		SetMenuItemChecked(w[84],0);	
		SetMenuItemChecked(w[40],0);
		SetMenuItemChecked(w[76],0);
		SetMenuItemChecked(w[102],0);

		SetMenuItemChecked(w[41],0);
		SetMenuItemChecked(w[96],0);
		SetMenuItemChecked(w[42],0);
		SetMenuItemChecked(w[43],0);
		SetMenuItemChecked(w[77],0);
		SetMenuItemChecked(w[44],0);
		SetMenuItemChecked(w[45],0);
		SetMenuItemChecked(w[92],0);
		SetMenuItemChecked(w[46],0);
		SetMenuItemChecked(w[26],0);
		SetMenuItemChecked(w[64],0);
		SetMenuItemChecked(w[65],0);
		SetMenuItemChecked(w[66],0);
		SetMenuItemChecked(w[67],1);
		SetMenuItemChecked(w[68],0);
		SetMenuItemChecked(w[99],0);
		}
	if (mode == 1) SetMenuItemChecked(w[67],0);
	dessiner();
	}

	
void Checked_flottabilite()
	{
	int mode;
	mode = GetMenuItemChecked(w[68]);
	if (mode == 0) 
		{
		SetMenuItemChecked(w[39],0);
		SetMenuItemChecked(w[81],0);
		SetMenuItemChecked(w[82],0);
		SetMenuItemChecked(w[84],0);
		SetMenuItemChecked(w[86],0);
		SetMenuItemChecked(w[40],0);
		SetMenuItemChecked(w[76],0);
		SetMenuItemChecked(w[102],0);

		SetMenuItemChecked(w[41],0);
		SetMenuItemChecked(w[96],0);
		SetMenuItemChecked(w[42],0);
		SetMenuItemChecked(w[43],0);
		SetMenuItemChecked(w[77],0);
		SetMenuItemChecked(w[44],0);
		SetMenuItemChecked(w[45],0);
		SetMenuItemChecked(w[92],0);
		SetMenuItemChecked(w[46],0);
		SetMenuItemChecked(w[26],0);
		SetMenuItemChecked(w[64],0);
		SetMenuItemChecked(w[65],0);
		SetMenuItemChecked(w[66],0);
		SetMenuItemChecked(w[67],0);
		SetMenuItemChecked(w[68],1);
		SetMenuItemChecked(w[99],0);
		}
	if (mode == 1) SetMenuItemChecked(w[68],0);
	dessiner();
	}
	
	
void Checked_EI_flexion_cable()
	{
	int mode;
	mode = GetMenuItemChecked(w[99]);
	if (mode == 0) 
		{
		SetMenuItemChecked(w[39],0);
		SetMenuItemChecked(w[81],0);
		SetMenuItemChecked(w[82],0);
		SetMenuItemChecked(w[84],0);
		SetMenuItemChecked(w[86],0);
		SetMenuItemChecked(w[40],0);
		SetMenuItemChecked(w[76],0);
		SetMenuItemChecked(w[102],0);

		SetMenuItemChecked(w[41],0);
		SetMenuItemChecked(w[96],0);
		SetMenuItemChecked(w[42],0);
		SetMenuItemChecked(w[43],0);
		SetMenuItemChecked(w[77],0);
		SetMenuItemChecked(w[44],0);
		SetMenuItemChecked(w[45],0);
		SetMenuItemChecked(w[92],0);
		SetMenuItemChecked(w[46],0);
		SetMenuItemChecked(w[26],0);
		SetMenuItemChecked(w[64],0);
		SetMenuItemChecked(w[65],0);
		SetMenuItemChecked(w[66],0);
		SetMenuItemChecked(w[67],0);
		SetMenuItemChecked(w[68],0);
		SetMenuItemChecked(w[99],1);
		}
	if (mode == 1) SetMenuItemChecked(w[99],0);
	dessiner();
	}
	
	
	
