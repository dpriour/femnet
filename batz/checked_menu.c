#include "batz.h"


void Checked_dessiner_contour_element(Widget widget, void *data)
	{
	int mode;
	mode = GetMenuItemChecked(w[9]);
	if (mode == 0) SetMenuItemChecked(w[9],1);
	if (mode == 1) SetMenuItemChecked(w[9],0);
	dessiner();
	}

void Checked_dessiner_contour_noeud(Widget widget, void *data)
	{
	int mode;
	mode = GetMenuItemChecked(w[90]);
	if (mode == 0) SetMenuItemChecked(w[90],1);
	if (mode == 1) SetMenuItemChecked(w[90],0);
	dessiner();
	}
void Checked_dessiner_afficher_houle(Widget widget, void *data)
	{
	int mode;
	mode = GetMenuItemChecked(w[91]);
	if (mode == 0) SetMenuItemChecked(w[91],1);
	if (mode == 1) SetMenuItemChecked(w[91],0);
	dessiner();
	}
void Checked_dessiner_contour_coulisse(Widget widget, void *data)
	{
	int mode;
	mode = GetMenuItemChecked(w[70]);
	if (mode == 0) SetMenuItemChecked(w[70],1);
	if (mode == 1) SetMenuItemChecked(w[70],0);
	dessiner();
	}

void Checked_dessiner_contour_winch(Widget widget, void *data)
	{
	int mode;
	mode = GetMenuItemChecked(w[87]);
	if (mode == 0) SetMenuItemChecked(w[87],1);
	if (mode == 1) SetMenuItemChecked(w[87],0);
	dessiner();
	}

void Checked_dessiner_contour_ball(Widget widget, void *data)
	{
	int mode;
	mode = GetMenuItemChecked(w[88]);
	if (mode == 0) 
		{
		SetMenuItemChecked(w[88],1);
		Ball.flag_dessin = 1;	
		}
	if (mode == 1) 
		{
		SetMenuItemChecked(w[88],0);
		Ball.flag_dessin = 0;	
		}
	dessiner();
	}

void Checked_dessiner_contour_triangle(Widget widget, void *data)
	{
	int mode,elem;
	mode = GetMenuItemChecked(w[10]);
	if (mode == 0) 
		{
		SetMenuItemChecked(w[10],1);
  		for (elem = 1 ; elem<= NOMBRE_SURFACES ; elem++) 
	  		{
	  		Surface[elem].flag_dessin_triangle = 1;
	  		}
		}
	if (mode == 1) 
		{
		SetMenuItemChecked(w[10],0);
  		for (elem = 1 ; elem<= NOMBRE_SURFACES ; elem++) 
	  		{
	  		Surface[elem].flag_dessin_triangle = 0;
	  		}
		}
		dessiner();
	}

void Checked_dessiner_orientation_xy(Widget widget, void *data)
	{
	int mode,elem;
	mode = GetMenuItemChecked(w[16]);
	if (mode == 0) 
		{
		SetMenuItemChecked(w[16],1);
	  	for (elem = 1 ; elem<= NOMBRE_SURFACES ; elem++) 
	  		{
	  		Surface[elem].flag_dessin_orientation_xy = 1;
	  		}
		}
	if (mode == 1) 
		{
		SetMenuItemChecked(w[16],0);
	  	for (elem = 1 ; elem<= NOMBRE_SURFACES ; elem++) 
	  		{
	  		Surface[elem].flag_dessin_orientation_xy = 0;
	  		}
		}
	dessiner();
	}

void Checked_dessiner_fils_u(Widget widget, void *data)
	{
	int mode,elem;
	mode = GetMenuItemChecked(w[11]);
	if (mode == 0) 
		{
		SetMenuItemChecked(w[11],1);
		SetMenuItemChecked(w[105],0);
	  	for (elem = 1 ; elem<= NOMBRE_SURFACES ; elem++) 
	  		{
	  		Surface[elem].flag_dessin_u = 1;
	  		}	
		}
	if (mode == 1) 
		{
		SetMenuItemChecked(w[11],0);
	  	for (elem = 1 ; elem<= NOMBRE_SURFACES ; elem++) 
	  		{
	  		Surface[elem].flag_dessin_u = 0;
	  		}	
		}
	dessiner();
	}

void Checked_dessiner_fils_v(Widget widget, void *data)
	{
	int mode,elem;
	mode = GetMenuItemChecked(w[29]);
	if (mode == 0) 
		{
		SetMenuItemChecked(w[29],1);
		SetMenuItemChecked(w[105],0);
	  	for (elem = 1 ; elem<= NOMBRE_SURFACES ; elem++) 
	  		{
	  		Surface[elem].flag_dessin_v = 1;
	  		}
		}
	if (mode == 1) 
		{
		SetMenuItemChecked(w[29],0);
	  	for (elem = 1 ; elem<= NOMBRE_SURFACES ; elem++) 
	  		{
	  		Surface[elem].flag_dessin_v = 0;
	  		}
		}
	dessiner();
	}

void Checked_dessiner_fils_u_v(Widget widget, void *data)
	{
	int mode,elem;
	mode = GetMenuItemChecked(w[105]);
	if (mode == 0) 
		{
		SetMenuItemChecked(w[105],1);
		SetMenuItemChecked(w[11],0);
		SetMenuItemChecked(w[29],0);
	  	for (elem = 1 ; elem<= NOMBRE_SURFACES ; elem++) 
	  		{
	  		Surface[elem].flag_dessin_u = 1;
	  		Surface[elem].flag_dessin_v = 1;
	  		}
		}
	if (mode == 1) 
		{
		SetMenuItemChecked(w[105],0);
	  	for (elem = 1 ; elem<= NOMBRE_SURFACES ; elem++) 
	  		{
	  		Surface[elem].flag_dessin_u = 0;
	  		Surface[elem].flag_dessin_v = 0;
	  		}
		}
	dessiner();
	}

void Checked_dessiner_surface_front(Widget widget, void *data)
	{
	int mode;
	mode = GetMenuItemChecked(w[15]);
	if (mode == 0) SetMenuItemChecked(w[15],1);
	if (mode == 1) SetMenuItemChecked(w[15],0);
	dessiner();
	}

void Checked_dessiner_axes(Widget widget, void *data)
	{
	int mode;
	mode = GetMenuItemChecked(w[17]);
	if (mode == 0) SetMenuItemChecked(w[17],1);
	if (mode == 1) SetMenuItemChecked(w[17],0);
	dessiner();
	}

void Checked_dessiner_repere(Widget widget, void *data)
	{
	int mode;
	mode = GetMenuItemChecked(w[93]);
	if (mode == 0) SetMenuItemChecked(w[93],1);
	if (mode == 1) SetMenuItemChecked(w[93],0);
	dessiner();
	}

void Checked_dessiner_quadrillage(Widget widget, void *data)
	{
	int mode;
	mode = GetMenuItemChecked(w[18]);
	if (mode == 0) SetMenuItemChecked(w[18],1);
	if (mode == 1) SetMenuItemChecked(w[18],0);
	dessiner();
	}

void Checked_dessiner_surface_libre(Widget widget, void *data)
	{
	int mode;
	mode = GetMenuItemChecked(w[14]);
	if (mode == 0) 
		{
		SetMenuItemChecked(w[14],1);
		Structure.free_surface = 1;
		}
	if (mode == 1) 
		{
		SetMenuItemChecked(w[14],0);
		Structure.free_surface = 0;
		}
	dessiner();
	}

void Checked_dessiner_ballast_altitude(Widget widget, void *data)
	{
	int mode;
	mode = GetMenuItemChecked(w[100]);
	if (mode == 0) 
		{
		SetMenuItemChecked(w[100],1);
		Structure.ballast_altitude = 1;
		}
	if (mode == 1) 
		{
		SetMenuItemChecked(w[100],0);
		Structure.ballast_altitude = 0;
		}
	dessiner();
	}


void Checked_dessiner_cube_size(Widget widget, void *data)
	{
	int mode;
	mode = GetMenuItemChecked(w[101]);
	if (mode == 0) 
		{
		SetMenuItemChecked(w[101],1);
		}
	if (mode == 1) 
		{
		SetMenuItemChecked(w[101],0);
		}
	dessiner();
	}

/* debut modifdp du 4 mars 2010*/
void Checked_solidity_ratio(Widget widget, void *data)
	{
	int mode;
	mode = GetMenuItemChecked(w[94]);
	if (mode == 0) 
		{
		SetMenuItemChecked(w[20],0);
		SetMenuItemChecked(w[94],1);
		SetMenuItemChecked(w[102],0);
		SetMenuItemChecked(w[95],0);
		SetMenuItemChecked(w[21],0);
		SetMenuItemChecked(w[22],0);
		SetMenuItemChecked(w[23],0);
		SetMenuItemChecked(w[84],0);
		SetMenuItemChecked(w[24],0);
		SetMenuItemChecked(w[25],0);
		SetMenuItemChecked(w[27],0);
		SetMenuItemChecked(w[56],0);
		SetMenuItemChecked(w[57],0);
		SetMenuItemChecked(w[72],0);
		SetMenuItemChecked(w[58],0);
		SetMenuItemChecked(w[59],0);
		SetMenuItemChecked(w[60],0);
		SetMenuItemChecked(w[61],0);
		SetMenuItemChecked(w[62],0);
		SetMenuItemChecked(w[73],0);
		SetMenuItemChecked(w[63],0);
		SetMenuItemChecked(w[64],0);
		SetMenuItemChecked(w[65],0);
		SetMenuItemChecked(w[66],0);
		SetMenuItemChecked(w[67],0);
		SetMenuItemChecked(w[68],0);
		SetMenuItemChecked(w[69],0);
		SetMenuItemChecked(w[82],0);
		}
	if (mode == 1) SetMenuItemChecked(w[94],0);
	dessiner();
	}
	
void Checked_max_exit_size(Widget widget, void *data)
	{
	int mode;
	mode = GetMenuItemChecked(w[102]);
	if (mode == 0) 
		{
		SetMenuItemChecked(w[20],0);
		SetMenuItemChecked(w[94],0);
		SetMenuItemChecked(w[102],1);
		SetMenuItemChecked(w[95],0);
		SetMenuItemChecked(w[21],0);
		SetMenuItemChecked(w[22],0);
		SetMenuItemChecked(w[23],0);
		SetMenuItemChecked(w[84],0);
		SetMenuItemChecked(w[24],0);
		SetMenuItemChecked(w[25],0);
		SetMenuItemChecked(w[27],0);
		SetMenuItemChecked(w[56],0);
		SetMenuItemChecked(w[57],0);
		SetMenuItemChecked(w[72],0);
		SetMenuItemChecked(w[58],0);
		SetMenuItemChecked(w[59],0);
		SetMenuItemChecked(w[60],0);
		SetMenuItemChecked(w[61],0);
		SetMenuItemChecked(w[62],0);
		SetMenuItemChecked(w[73],0);
		SetMenuItemChecked(w[63],0);
		SetMenuItemChecked(w[64],0);
		SetMenuItemChecked(w[65],0);
		SetMenuItemChecked(w[66],0);
		SetMenuItemChecked(w[67],0);
		SetMenuItemChecked(w[68],0);
		SetMenuItemChecked(w[69],0);
		SetMenuItemChecked(w[82],0);
		}
	if (mode == 1) SetMenuItemChecked(w[102],0);
	dessiner();
	}
	
void Checked_flow_orientation(Widget widget, void *data)
	{
	int mode;
	mode = GetMenuItemChecked(w[95]);
	if (mode == 0) 
		{
		SetMenuItemChecked(w[20],0);
		SetMenuItemChecked(w[94],0);
		SetMenuItemChecked(w[102],0);
		SetMenuItemChecked(w[95],1);
		SetMenuItemChecked(w[21],0);
		SetMenuItemChecked(w[22],0);
		SetMenuItemChecked(w[23],0);
		SetMenuItemChecked(w[84],0);
		SetMenuItemChecked(w[24],0);
		SetMenuItemChecked(w[25],0);
		SetMenuItemChecked(w[27],0);
		SetMenuItemChecked(w[56],0);
		SetMenuItemChecked(w[57],0);
		SetMenuItemChecked(w[72],0);
		SetMenuItemChecked(w[58],0);
		SetMenuItemChecked(w[59],0);
		SetMenuItemChecked(w[60],0);
		SetMenuItemChecked(w[61],0);
		SetMenuItemChecked(w[62],0);
		SetMenuItemChecked(w[73],0);
		SetMenuItemChecked(w[63],0);
		SetMenuItemChecked(w[64],0);
		SetMenuItemChecked(w[65],0);
		SetMenuItemChecked(w[66],0);
		SetMenuItemChecked(w[67],0);
		SetMenuItemChecked(w[68],0);
		SetMenuItemChecked(w[69],0);
		SetMenuItemChecked(w[82],0);
		}
	if (mode == 1) SetMenuItemChecked(w[95],0);
	dessiner();
	}
	
void Checked_angle_fils(Widget widget, void *data)
	{
	int mode;
	mode = GetMenuItemChecked(w[20]);
	if (mode == 0) 
		{
		SetMenuItemChecked(w[20],1);
		SetMenuItemChecked(w[94],0);
		SetMenuItemChecked(w[102],0);
		SetMenuItemChecked(w[95],0);
		SetMenuItemChecked(w[21],0);
		SetMenuItemChecked(w[22],0);
		SetMenuItemChecked(w[23],0);
		SetMenuItemChecked(w[84],0);
		SetMenuItemChecked(w[24],0);
		SetMenuItemChecked(w[25],0);
		SetMenuItemChecked(w[27],0);
		SetMenuItemChecked(w[56],0);
		SetMenuItemChecked(w[57],0);
		SetMenuItemChecked(w[72],0);
		SetMenuItemChecked(w[58],0);
		SetMenuItemChecked(w[59],0);
		SetMenuItemChecked(w[60],0);
		SetMenuItemChecked(w[61],0);
		SetMenuItemChecked(w[62],0);
		SetMenuItemChecked(w[73],0);
		SetMenuItemChecked(w[63],0);
		SetMenuItemChecked(w[64],0);
		SetMenuItemChecked(w[65],0);
		SetMenuItemChecked(w[66],0);
		SetMenuItemChecked(w[67],0);
		SetMenuItemChecked(w[68],0);
		SetMenuItemChecked(w[69],0);
		SetMenuItemChecked(w[82],0);
		}
	if (mode == 1) SetMenuItemChecked(w[20],0);
		SetMenuItemChecked(w[94],0);
		SetMenuItemChecked(w[95],0);
	dessiner();
	}
	
void Checked_orientation_volume(Widget widget, void *data)
	{
	int mode;
	mode = GetMenuItemChecked(w[21]);
	if (mode == 0) 
		{
		SetMenuItemChecked(w[20],0);
		SetMenuItemChecked(w[94],0);
		SetMenuItemChecked(w[102],0);
		SetMenuItemChecked(w[95],0);
		SetMenuItemChecked(w[21],1);
		SetMenuItemChecked(w[22],0);
		SetMenuItemChecked(w[23],0);
		SetMenuItemChecked(w[84],0);
		SetMenuItemChecked(w[24],0);
		SetMenuItemChecked(w[25],0);
		SetMenuItemChecked(w[27],0);
		SetMenuItemChecked(w[56],0);
		SetMenuItemChecked(w[57],0);
		SetMenuItemChecked(w[72],0);
		SetMenuItemChecked(w[58],0);
		SetMenuItemChecked(w[59],0);
		SetMenuItemChecked(w[60],0);
		SetMenuItemChecked(w[61],0);
		SetMenuItemChecked(w[62],0);
		SetMenuItemChecked(w[73],0);
		SetMenuItemChecked(w[63],0);
		SetMenuItemChecked(w[64],0);
		SetMenuItemChecked(w[65],0);
		SetMenuItemChecked(w[66],0);
		SetMenuItemChecked(w[67],0);
		SetMenuItemChecked(w[68],0);
		SetMenuItemChecked(w[69],0);
		SetMenuItemChecked(w[82],0);
		}
	if (mode == 1) SetMenuItemChecked(w[21],0);
	dessiner();
	}
	
void Checked_volume_elementaire(Widget widget, void *data)
	{
	int mode;
	mode = GetMenuItemChecked(w[22]);
	if (mode == 0) 
		{
		SetMenuItemChecked(w[20],0);
		SetMenuItemChecked(w[94],0);
		SetMenuItemChecked(w[102],0);
		SetMenuItemChecked(w[95],0);
		SetMenuItemChecked(w[21],0);
		SetMenuItemChecked(w[22],1);
		SetMenuItemChecked(w[23],0);
		SetMenuItemChecked(w[84],0);
		SetMenuItemChecked(w[24],0);
		SetMenuItemChecked(w[25],0);
		SetMenuItemChecked(w[27],0);
		SetMenuItemChecked(w[56],0);
		SetMenuItemChecked(w[57],0);
		SetMenuItemChecked(w[72],0);
		SetMenuItemChecked(w[58],0);
		SetMenuItemChecked(w[59],0);
		SetMenuItemChecked(w[60],0);
		SetMenuItemChecked(w[61],0);
		SetMenuItemChecked(w[62],0);
		SetMenuItemChecked(w[73],0);
		SetMenuItemChecked(w[63],0);
		SetMenuItemChecked(w[64],0);
		SetMenuItemChecked(w[65],0);
		SetMenuItemChecked(w[66],0);
		SetMenuItemChecked(w[67],0);
		SetMenuItemChecked(w[68],0);
		SetMenuItemChecked(w[69],0);
		SetMenuItemChecked(w[82],0);
		}
	if (mode == 1) SetMenuItemChecked(w[22],0);
	dessiner();
	}
	
void Checked_surface_elementaire(Widget widget, void *data)
	{
	int mode;
	mode = GetMenuItemChecked(w[23]);
	if (mode == 0) 
		{
		SetMenuItemChecked(w[20],0);
		SetMenuItemChecked(w[94],0);
		SetMenuItemChecked(w[102],0);
		SetMenuItemChecked(w[95],0);
		SetMenuItemChecked(w[21],0);
		SetMenuItemChecked(w[22],0);
		SetMenuItemChecked(w[23],1);
		SetMenuItemChecked(w[84],0);
		SetMenuItemChecked(w[24],0);
		SetMenuItemChecked(w[25],0);
		SetMenuItemChecked(w[27],0);
		SetMenuItemChecked(w[56],0);
		SetMenuItemChecked(w[57],0);
		SetMenuItemChecked(w[72],0);
		SetMenuItemChecked(w[58],0);
		SetMenuItemChecked(w[59],0);
		SetMenuItemChecked(w[60],0);
		SetMenuItemChecked(w[61],0);
		SetMenuItemChecked(w[62],0);
		SetMenuItemChecked(w[73],0);
		SetMenuItemChecked(w[63],0);
		SetMenuItemChecked(w[64],0);
		SetMenuItemChecked(w[65],0);
		SetMenuItemChecked(w[66],0);
		SetMenuItemChecked(w[67],0);
		SetMenuItemChecked(w[68],0);
		SetMenuItemChecked(w[69],0);
		SetMenuItemChecked(w[82],0);
		}
	if (mode == 1) SetMenuItemChecked(w[23],0);
	dessiner();
	}
	
void Checked_defaut_discretisation(Widget widget, void *data)
	{
	int mode;
	mode = GetMenuItemChecked(w[84]);
	if (mode == 0) 
		{
		SetMenuItemChecked(w[20],0);
		SetMenuItemChecked(w[94],0);
		SetMenuItemChecked(w[102],0);
		SetMenuItemChecked(w[95],0);
		SetMenuItemChecked(w[21],0);
		SetMenuItemChecked(w[22],0);
		SetMenuItemChecked(w[23],0);
		SetMenuItemChecked(w[84],0);
		SetMenuItemChecked(w[84],1);
		SetMenuItemChecked(w[24],0);
		SetMenuItemChecked(w[25],0);
		SetMenuItemChecked(w[27],0);
		SetMenuItemChecked(w[56],0);
		SetMenuItemChecked(w[57],0);
		SetMenuItemChecked(w[72],0);
		SetMenuItemChecked(w[58],0);
		SetMenuItemChecked(w[59],0);
		SetMenuItemChecked(w[60],0);
		SetMenuItemChecked(w[61],0);
		SetMenuItemChecked(w[62],0);
		SetMenuItemChecked(w[73],0);
		SetMenuItemChecked(w[63],0);
		SetMenuItemChecked(w[64],0);
		SetMenuItemChecked(w[65],0);
		SetMenuItemChecked(w[66],0);
		SetMenuItemChecked(w[67],0);
		SetMenuItemChecked(w[68],0);
		SetMenuItemChecked(w[69],0);
		SetMenuItemChecked(w[82],0);
		}
	if (mode == 1) SetMenuItemChecked(w[84],0);
	dessiner();
	}
	
void Checked_profondeur_barycentre(Widget widget, void *data)
	{
	int mode;
	mode = GetMenuItemChecked(w[24]);
	if (mode == 0) 
		{
		SetMenuItemChecked(w[20],0);
		SetMenuItemChecked(w[94],0);
		SetMenuItemChecked(w[102],0);
		SetMenuItemChecked(w[95],0);
		SetMenuItemChecked(w[21],0);
		SetMenuItemChecked(w[22],0);
		SetMenuItemChecked(w[23],0);
		SetMenuItemChecked(w[84],0);
		SetMenuItemChecked(w[24],1);
		SetMenuItemChecked(w[25],0);
		SetMenuItemChecked(w[27],0);
		SetMenuItemChecked(w[56],0);
		SetMenuItemChecked(w[57],0);
		SetMenuItemChecked(w[72],0);
		SetMenuItemChecked(w[58],0);
		SetMenuItemChecked(w[59],0);
		SetMenuItemChecked(w[60],0);
		SetMenuItemChecked(w[61],0);
		SetMenuItemChecked(w[62],0);
		SetMenuItemChecked(w[73],0);
		SetMenuItemChecked(w[63],0);
		SetMenuItemChecked(w[64],0);
		SetMenuItemChecked(w[65],0);
		SetMenuItemChecked(w[66],0);
		SetMenuItemChecked(w[67],0);
		SetMenuItemChecked(w[68],0);
		SetMenuItemChecked(w[69],0);
		SetMenuItemChecked(w[82],0);
		}
	if (mode == 1) SetMenuItemChecked(w[24],0);
	dessiner();
	}
	
void Checked_numero_element(Widget widget, void *data)
	{
	int mode;
	mode = GetMenuItemChecked(w[25]);
	if (mode == 0) 
		{
		SetMenuItemChecked(w[20],0);
		SetMenuItemChecked(w[94],0);
		SetMenuItemChecked(w[102],0);
		SetMenuItemChecked(w[95],0);
		SetMenuItemChecked(w[21],0);
		SetMenuItemChecked(w[22],0);
		SetMenuItemChecked(w[23],0);
		SetMenuItemChecked(w[84],0);
		SetMenuItemChecked(w[24],0);
		SetMenuItemChecked(w[25],1);
		SetMenuItemChecked(w[27],0);
		SetMenuItemChecked(w[28],0);
		SetMenuItemChecked(w[56],0);
		SetMenuItemChecked(w[57],0);
		SetMenuItemChecked(w[72],0);
		SetMenuItemChecked(w[58],0);
		SetMenuItemChecked(w[59],0);
		SetMenuItemChecked(w[60],0);
		SetMenuItemChecked(w[61],0);
		SetMenuItemChecked(w[62],0);
		SetMenuItemChecked(w[73],0);
		SetMenuItemChecked(w[63],0);
		SetMenuItemChecked(w[64],0);
		SetMenuItemChecked(w[65],0);
		SetMenuItemChecked(w[66],0);
		SetMenuItemChecked(w[67],0);
		SetMenuItemChecked(w[68],0);
		SetMenuItemChecked(w[69],0);
		SetMenuItemChecked(w[82],0);
		}
	if (mode == 1) SetMenuItemChecked(w[25],0);
	dessiner();
	}
	
void Checked_type_element(Widget widget, void *data)
	{
	int mode;
	mode = GetMenuItemChecked(w[27]);
	if (mode == 0) 
		{
		SetMenuItemChecked(w[20],0);
		SetMenuItemChecked(w[94],0);
		SetMenuItemChecked(w[102],0);
		SetMenuItemChecked(w[95],0);
		SetMenuItemChecked(w[21],0);
		SetMenuItemChecked(w[22],0);
		SetMenuItemChecked(w[23],0);
		SetMenuItemChecked(w[84],0);
		SetMenuItemChecked(w[24],0);
		SetMenuItemChecked(w[25],0);
		SetMenuItemChecked(w[27],1);
		SetMenuItemChecked(w[56],0);
		SetMenuItemChecked(w[57],0);
		SetMenuItemChecked(w[72],0);
		SetMenuItemChecked(w[58],0);
		SetMenuItemChecked(w[59],0);
		SetMenuItemChecked(w[60],0);
		SetMenuItemChecked(w[61],0);
		SetMenuItemChecked(w[62],0);
		SetMenuItemChecked(w[73],0);
		SetMenuItemChecked(w[63],0);
		SetMenuItemChecked(w[64],0);
		SetMenuItemChecked(w[65],0);
		SetMenuItemChecked(w[66],0);
		SetMenuItemChecked(w[67],0);
		SetMenuItemChecked(w[68],0);
		SetMenuItemChecked(w[69],0);
		SetMenuItemChecked(w[82],0);
		}
	if (mode == 1) SetMenuItemChecked(w[27],0);
	dessiner();
	}
	
void Checked_commentaire(Widget widget, void *data)
	{
	int mode;
	mode = GetMenuItemChecked(w[71]);
	if (mode == 0) 
		{
		SetMenuItemChecked(w[71],1);
		}
	if (mode == 1) SetMenuItemChecked(w[71],0);
	dessiner();
	}
	
void Checked_animation(Widget widget, void *data)
	{
	int mode;
	mode = GetMenuItemChecked(w[77]);
	if (mode == 0) 
		{
		SetMenuItemChecked(w[77],1);
		}
	if (mode == 1) SetMenuItemChecked(w[77],0);
	/* debut modifdp du 26 mars 2010*/
	/*animation();*/
	animation2(0);
	//anim_rotation2(0);
	/* fin modifdp du 26 mars 2010*/
	}
	
void Checked_animation_video(Widget widget, void *data)
	{
	int mode;
	mode = GetMenuItemChecked(w[92]);
	if (mode == 0) 
		{
		SetMenuItemChecked(w[92],1);
		}
	if (mode == 1) SetMenuItemChecked(w[92],0);
	/* debut modifdp du 26 mars 2010*/
	/*animation_video();*/
	animation2(1);
	//anim_rotation2(1);
	/* fin modifdp du 26 mars 2010*/
	}

void Checked_animation_eigenvalue(Widget widget, void *data)
	{
	int mode;
	mode = GetMenuItemChecked(w[104]);
	if (mode == 0) 
		{
		SetMenuItemChecked(w[104],1);
		}
	if (mode == 1) SetMenuItemChecked(w[104],0);
	animation_eigenvalue(0);
	}

void Checked_symmetry_no_symmetry(Widget widget, void *data)
	{
	int mode;
	mode = GetMenuItemChecked(w[103]);
	if (mode == 0) 
		{
		SetMenuItemChecked(w[103],1);
		}
	if (mode == 1) SetMenuItemChecked(w[103],0);
	printf("Structure.symetry %d\n",Structure.symetry);
	printf("mode %d\n",mode); 
	if (mode == 0)	
		{
		if (Structure.symetry == 0)
			{
			//nothing to do
			}
		if ((Structure.symetry == 1) || (Structure.symetry == 2) || (Structure.symetry == 4))
			{
			NOMBRE_ELEMENTS  = (int) NOMBRE_ELEMENTS / 2;
			NOMBRE_SURFACES  = (int)NOMBRE_SURFACES / 2;
		  	NOMBRE_SURF_HEXA = (int)NOMBRE_SURF_HEXA / 2;
			NOMBRE_NOEUDS    = (int)NOMBRE_NOEUDS / 2;
			}
		}
	if (mode == 1)	
		{
		if (Structure.symetry == 0)
			{
			//nothing to do
			}
		if ((Structure.symetry == 1) || (Structure.symetry == 2) || (Structure.symetry == 4))
			{
			NOMBRE_ELEMENTS  = 2 * NOMBRE_ELEMENTS;
			NOMBRE_SURFACES  = 2 * NOMBRE_SURFACES;
		  	NOMBRE_SURF_HEXA = 2 * NOMBRE_SURF_HEXA;
			NOMBRE_NOEUDS    = 2 * NOMBRE_NOEUDS;
			}
		}
	dessiner();
	}

void Checked_efforts_externes(Widget widget, void *data)
	{
	int mode;
	mode = GetMenuItemChecked(w[74]);
	if (mode == 0) 
		{
		SetMenuItemChecked(w[74],1);
		}
	if (mode == 1) SetMenuItemChecked(w[74],0);
	dessiner();
	}
	
void Checked_eigen_values(Widget widget, void *data)
	{
	int mode;
	mode = GetMenuItemChecked(w[97]);
	if (mode == 0) 
		{
		SetMenuItemChecked(w[97],1);
		}
	if (mode == 1) SetMenuItemChecked(w[97],0);
	dessiner();
	}
	
void Checked_immersion(Widget widget, void *data)
	{
	int mode;
	mode = GetMenuItemChecked(w[86]);
	if (mode == 0) 
		{
		SetMenuItemChecked(w[86],1);
		}
	if (mode == 1) SetMenuItemChecked(w[86],0);
	dessiner();
	}
	
void Checked_trajectoire(Widget widget, void *data)
	{
	int mode;
	mode = GetMenuItemChecked(w[85]);
	if (mode == 0) 
		{
		SetMenuItemChecked(w[85],1);
		}
	if (mode == 1) SetMenuItemChecked(w[85],0);
	dessiner();
	}
	
void Checked_deplacement(Widget widget, void *data)
	{
	int mode;
	mode = GetMenuItemChecked(w[83]);
	if (mode == 0) 
		{
		SetMenuItemChecked(w[83],1);
		}
	if (mode == 1) SetMenuItemChecked(w[83],0);
	dessiner();
	}
	
void Checked_raideur_traction(Widget widget, void *data)
	{
	int mode;
	mode = GetMenuItemChecked(w[56]);
	if (mode == 0) 
		{
		SetMenuItemChecked(w[20],0);
		SetMenuItemChecked(w[94],0);
		SetMenuItemChecked(w[102],0);
		SetMenuItemChecked(w[95],0);
		SetMenuItemChecked(w[21],0);
		SetMenuItemChecked(w[22],0);
		SetMenuItemChecked(w[23],0);
		SetMenuItemChecked(w[84],0);
		SetMenuItemChecked(w[24],0);
		SetMenuItemChecked(w[25],0);
		SetMenuItemChecked(w[27],0);
		SetMenuItemChecked(w[56],1);
		SetMenuItemChecked(w[57],0);
		SetMenuItemChecked(w[72],0);
		SetMenuItemChecked(w[58],0);
		SetMenuItemChecked(w[59],0);
		SetMenuItemChecked(w[60],0);
		SetMenuItemChecked(w[61],0);
		SetMenuItemChecked(w[62],0);
		SetMenuItemChecked(w[73],0);
		SetMenuItemChecked(w[63],0);
		SetMenuItemChecked(w[64],0);
		SetMenuItemChecked(w[65],0);
		SetMenuItemChecked(w[66],0);
		SetMenuItemChecked(w[67],0);
		SetMenuItemChecked(w[68],0);
		SetMenuItemChecked(w[69],0);
		SetMenuItemChecked(w[82],0);
		}
	if (mode == 1) SetMenuItemChecked(w[56],0);
	dessiner();
	}
	
void Checked_raideur_compression(Widget widget, void *data)
	{
	int mode;
	mode = GetMenuItemChecked(w[57]);
	if (mode == 0) 
		{
		SetMenuItemChecked(w[20],0);
		SetMenuItemChecked(w[94],0);
		SetMenuItemChecked(w[102],0);
		SetMenuItemChecked(w[95],0);
		SetMenuItemChecked(w[21],0);
		SetMenuItemChecked(w[22],0);
		SetMenuItemChecked(w[23],0);
		SetMenuItemChecked(w[84],0);
		SetMenuItemChecked(w[24],0);
		SetMenuItemChecked(w[25],0);
		SetMenuItemChecked(w[27],0);
		SetMenuItemChecked(w[56],0);
		SetMenuItemChecked(w[57],7);
		SetMenuItemChecked(w[72],0);
		SetMenuItemChecked(w[58],0);
		SetMenuItemChecked(w[59],0);
		SetMenuItemChecked(w[60],0);
		SetMenuItemChecked(w[61],0);
		SetMenuItemChecked(w[62],0);
		SetMenuItemChecked(w[73],0);
		SetMenuItemChecked(w[63],0);
		SetMenuItemChecked(w[64],0);
		SetMenuItemChecked(w[65],0);
		SetMenuItemChecked(w[66],0);
		SetMenuItemChecked(w[67],0);
		SetMenuItemChecked(w[68],0);
		SetMenuItemChecked(w[69],0);
		SetMenuItemChecked(w[82],0);
		}
	if (mode == 1) SetMenuItemChecked(w[57],0);
	dessiner();
	}
	
void Checked_raideur_ouverture(Widget widget, void *data)
	{
	int mode;
	mode = GetMenuItemChecked(w[72]);
	if (mode == 0) 
		{
		SetMenuItemChecked(w[20],0);
		SetMenuItemChecked(w[94],0);
		SetMenuItemChecked(w[102],0);
		SetMenuItemChecked(w[95],0);
		SetMenuItemChecked(w[21],0);
		SetMenuItemChecked(w[22],0);
		SetMenuItemChecked(w[23],0);
		SetMenuItemChecked(w[84],0);
		SetMenuItemChecked(w[24],0);
		SetMenuItemChecked(w[25],0);
		SetMenuItemChecked(w[27],0);
		SetMenuItemChecked(w[56],0);
		SetMenuItemChecked(w[57],0);
		SetMenuItemChecked(w[72],1);
		SetMenuItemChecked(w[58],0);
		SetMenuItemChecked(w[59],0);
		SetMenuItemChecked(w[60],0);
		SetMenuItemChecked(w[61],0);
		SetMenuItemChecked(w[62],0);
		SetMenuItemChecked(w[73],0);
		SetMenuItemChecked(w[63],0);
		SetMenuItemChecked(w[64],0);
		SetMenuItemChecked(w[65],0);
		SetMenuItemChecked(w[66],0);
		SetMenuItemChecked(w[67],0);
		SetMenuItemChecked(w[68],0);
		SetMenuItemChecked(w[69],0);
		SetMenuItemChecked(w[82],0);
		}
	if (mode == 1) SetMenuItemChecked(w[72],0);
	dessiner();
	}
	
void Checked_tension(Widget widget, void *data)
	{
	int mode;
	mode = GetMenuItemChecked(w[58]);
	if (mode == 0) 
		{
		SetMenuItemChecked(w[20],0);
		SetMenuItemChecked(w[94],0);
		SetMenuItemChecked(w[102],0);
		SetMenuItemChecked(w[95],0);
		SetMenuItemChecked(w[21],0);
		SetMenuItemChecked(w[22],0);
		SetMenuItemChecked(w[23],0);
		SetMenuItemChecked(w[84],0);
		SetMenuItemChecked(w[24],0);
		SetMenuItemChecked(w[25],0);
		SetMenuItemChecked(w[27],0);
		SetMenuItemChecked(w[56],0);
		SetMenuItemChecked(w[57],0);
		SetMenuItemChecked(w[72],0);
		SetMenuItemChecked(w[58],1);
		SetMenuItemChecked(w[59],0);
		SetMenuItemChecked(w[60],0);
		SetMenuItemChecked(w[61],0);
		SetMenuItemChecked(w[62],0);
		SetMenuItemChecked(w[73],0);
		SetMenuItemChecked(w[63],0);
		SetMenuItemChecked(w[64],0);
		SetMenuItemChecked(w[65],0);
		SetMenuItemChecked(w[66],0);
		SetMenuItemChecked(w[67],0);
		SetMenuItemChecked(w[68],0);
		SetMenuItemChecked(w[69],0);
		SetMenuItemChecked(w[82],0);
		}
	if (mode == 1) SetMenuItemChecked(w[58],0);
	dessiner();
	}
	
void Checked_nrj(Widget widget, void *data)
	{
	int mode;
	mode = GetMenuItemChecked(w[82]);
	if (mode == 0) 
		{
		SetMenuItemChecked(w[20],0);
		SetMenuItemChecked(w[94],0);
		SetMenuItemChecked(w[102],0);
		SetMenuItemChecked(w[95],0);
		SetMenuItemChecked(w[21],0);
		SetMenuItemChecked(w[22],0);
		SetMenuItemChecked(w[23],0);
		SetMenuItemChecked(w[84],0);
		SetMenuItemChecked(w[24],0);
		SetMenuItemChecked(w[25],0);
		SetMenuItemChecked(w[27],0);
		SetMenuItemChecked(w[56],0);
		SetMenuItemChecked(w[57],0);
		SetMenuItemChecked(w[72],0);
		SetMenuItemChecked(w[58],0);
		SetMenuItemChecked(w[59],0);
		SetMenuItemChecked(w[60],0);
		SetMenuItemChecked(w[61],0);
		SetMenuItemChecked(w[62],0);
		SetMenuItemChecked(w[73],0);
		SetMenuItemChecked(w[63],0);
		SetMenuItemChecked(w[64],0);
		SetMenuItemChecked(w[65],0);
		SetMenuItemChecked(w[66],0);
		SetMenuItemChecked(w[67],0);
		SetMenuItemChecked(w[68],0);
		SetMenuItemChecked(w[69],0);
		SetMenuItemChecked(w[82],1);
		}
	if (mode == 1) SetMenuItemChecked(w[82],0);
	dessiner();
	}
	
void Checked_longueur_repos(Widget widget, void *data)
	{
	int mode;
	mode = GetMenuItemChecked(w[59]);
	if (mode == 0) 
		{
		SetMenuItemChecked(w[20],0);
		SetMenuItemChecked(w[94],0);
		SetMenuItemChecked(w[102],0);
		SetMenuItemChecked(w[95],0);
		SetMenuItemChecked(w[21],0);
		SetMenuItemChecked(w[22],0);
		SetMenuItemChecked(w[23],0);
		SetMenuItemChecked(w[84],0);
		SetMenuItemChecked(w[24],0);
		SetMenuItemChecked(w[25],0);
		SetMenuItemChecked(w[27],0);
		SetMenuItemChecked(w[56],0);
		SetMenuItemChecked(w[57],0);
		SetMenuItemChecked(w[72],0);
		SetMenuItemChecked(w[58],0);
		SetMenuItemChecked(w[59],1);
		SetMenuItemChecked(w[60],0);
		SetMenuItemChecked(w[61],0);
		SetMenuItemChecked(w[62],0);
		SetMenuItemChecked(w[73],0);
		SetMenuItemChecked(w[63],0);
		SetMenuItemChecked(w[64],0);
		SetMenuItemChecked(w[65],0);
		SetMenuItemChecked(w[66],0);
		SetMenuItemChecked(w[67],0);
		SetMenuItemChecked(w[68],0);
		SetMenuItemChecked(w[69],0);
		SetMenuItemChecked(w[82],0);
		}
	if (mode == 1) SetMenuItemChecked(w[59],0);
	dessiner();
	}
	
void Checked_longueur_tendue(Widget widget, void *data)
	{
	int mode;
	mode = GetMenuItemChecked(w[60]);
	if (mode == 0) 
		{
		SetMenuItemChecked(w[20],0);
		SetMenuItemChecked(w[94],0);
		SetMenuItemChecked(w[102],0);
		SetMenuItemChecked(w[95],0);
		SetMenuItemChecked(w[21],0);
		SetMenuItemChecked(w[22],0);
		SetMenuItemChecked(w[23],0);
		SetMenuItemChecked(w[84],0);
		SetMenuItemChecked(w[24],0);
		SetMenuItemChecked(w[25],0);
		SetMenuItemChecked(w[27],0);
		SetMenuItemChecked(w[56],0);
		SetMenuItemChecked(w[57],0);
		SetMenuItemChecked(w[72],0);
		SetMenuItemChecked(w[58],0);
		SetMenuItemChecked(w[59],0);
		SetMenuItemChecked(w[60],1);
		SetMenuItemChecked(w[61],0);
		SetMenuItemChecked(w[62],0);
		SetMenuItemChecked(w[73],0);
		SetMenuItemChecked(w[63],0);
		SetMenuItemChecked(w[64],0);
		SetMenuItemChecked(w[65],0);
		SetMenuItemChecked(w[66],0);
		SetMenuItemChecked(w[67],0);
		SetMenuItemChecked(w[68],0);
		SetMenuItemChecked(w[69],0);
		SetMenuItemChecked(w[82],0);
		}
	if (mode == 1) SetMenuItemChecked(w[60],0);
	dessiner();
	}
	
void Checked_masse_volumique(Widget widget, void *data)
	{
	int mode;
	mode = GetMenuItemChecked(w[61]);
	if (mode == 0) 
		{
		SetMenuItemChecked(w[20],0);
		SetMenuItemChecked(w[94],0);
		SetMenuItemChecked(w[102],0);
		SetMenuItemChecked(w[95],0);
		SetMenuItemChecked(w[21],0);
		SetMenuItemChecked(w[22],0);
		SetMenuItemChecked(w[23],0);
		SetMenuItemChecked(w[84],0);
		SetMenuItemChecked(w[24],0);
		SetMenuItemChecked(w[25],0);
		SetMenuItemChecked(w[27],0);
		SetMenuItemChecked(w[56],0);
		SetMenuItemChecked(w[57],0);
		SetMenuItemChecked(w[72],0);
		SetMenuItemChecked(w[58],0);
		SetMenuItemChecked(w[59],0);
		SetMenuItemChecked(w[60],0);
		SetMenuItemChecked(w[61],1);
		SetMenuItemChecked(w[62],0);
		SetMenuItemChecked(w[73],0);
		SetMenuItemChecked(w[63],0);
		SetMenuItemChecked(w[64],0);
		SetMenuItemChecked(w[65],0);
		SetMenuItemChecked(w[66],0);
		SetMenuItemChecked(w[67],0);
		SetMenuItemChecked(w[68],0);
		SetMenuItemChecked(w[69],0);
		SetMenuItemChecked(w[82],0);
		}
	if (mode == 1) SetMenuItemChecked(w[61],0);
	dessiner();
	}
	
void Checked_diametre(Widget widget, void *data)
	{
	int mode;
	mode = GetMenuItemChecked(w[62]);
	if (mode == 0) 
		{
		SetMenuItemChecked(w[20],0);
		SetMenuItemChecked(w[94],0);
		SetMenuItemChecked(w[102],0);
		SetMenuItemChecked(w[95],0);
		SetMenuItemChecked(w[21],0);
		SetMenuItemChecked(w[22],0);
		SetMenuItemChecked(w[23],0);
		SetMenuItemChecked(w[84],0);
		SetMenuItemChecked(w[24],0);
		SetMenuItemChecked(w[25],0);
		SetMenuItemChecked(w[27],0);
		SetMenuItemChecked(w[56],0);
		SetMenuItemChecked(w[57],0);
		SetMenuItemChecked(w[72],0);
		SetMenuItemChecked(w[58],0);
		SetMenuItemChecked(w[59],0);
		SetMenuItemChecked(w[60],0);
		SetMenuItemChecked(w[61],0);
		SetMenuItemChecked(w[62],1);
		SetMenuItemChecked(w[73],0);
		SetMenuItemChecked(w[63],0);
		SetMenuItemChecked(w[64],0);
		SetMenuItemChecked(w[65],0);
		SetMenuItemChecked(w[66],0);
		SetMenuItemChecked(w[67],0);
		SetMenuItemChecked(w[68],0);
		SetMenuItemChecked(w[69],0);
		SetMenuItemChecked(w[82],0);
		}
	if (mode == 1) SetMenuItemChecked(w[62],0);
	dessiner();
	}
	
void Checked_largeur_noeud(Widget widget, void *data)
	{
	int mode;
	mode = GetMenuItemChecked(w[73]);
	if (mode == 0) 
		{
		SetMenuItemChecked(w[20],0);
		SetMenuItemChecked(w[94],0);
		SetMenuItemChecked(w[102],0);
		SetMenuItemChecked(w[95],0);
		SetMenuItemChecked(w[21],0);
		SetMenuItemChecked(w[22],0);
		SetMenuItemChecked(w[23],0);
		SetMenuItemChecked(w[84],0);
		SetMenuItemChecked(w[24],0);
		SetMenuItemChecked(w[25],0);
		SetMenuItemChecked(w[27],0);
		SetMenuItemChecked(w[56],0);
		SetMenuItemChecked(w[57],0);
		SetMenuItemChecked(w[72],0);
		SetMenuItemChecked(w[58],0);
		SetMenuItemChecked(w[59],0);
		SetMenuItemChecked(w[60],0);
		SetMenuItemChecked(w[61],0);
		SetMenuItemChecked(w[62],0);
		SetMenuItemChecked(w[73],1);
		SetMenuItemChecked(w[63],0);
		SetMenuItemChecked(w[64],0);
		SetMenuItemChecked(w[65],0);
		SetMenuItemChecked(w[66],0);
		SetMenuItemChecked(w[67],0);
		SetMenuItemChecked(w[68],0);
		SetMenuItemChecked(w[69],0);
		SetMenuItemChecked(w[82],0);
		}
	if (mode == 1) SetMenuItemChecked(w[73],0);
	dessiner();
	}
	
void Checked_coefficient_cd(Widget widget, void *data)
	{
	int mode;
	mode = GetMenuItemChecked(w[63]);
	if (mode == 0) 
		{
		SetMenuItemChecked(w[20],0);
		SetMenuItemChecked(w[94],0);
		SetMenuItemChecked(w[102],0);
		SetMenuItemChecked(w[95],0);
		SetMenuItemChecked(w[21],0);
		SetMenuItemChecked(w[22],0);
		SetMenuItemChecked(w[23],0);
		SetMenuItemChecked(w[84],0);
		SetMenuItemChecked(w[24],0);
		SetMenuItemChecked(w[25],0);
		SetMenuItemChecked(w[27],0);
		SetMenuItemChecked(w[56],0);
		SetMenuItemChecked(w[57],0);
		SetMenuItemChecked(w[72],0);
		SetMenuItemChecked(w[58],0);
		SetMenuItemChecked(w[59],0);
		SetMenuItemChecked(w[60],0);
		SetMenuItemChecked(w[61],0);
		SetMenuItemChecked(w[62],0);
		SetMenuItemChecked(w[73],0);
		SetMenuItemChecked(w[63],1);
		SetMenuItemChecked(w[64],0);
		SetMenuItemChecked(w[65],0);
		SetMenuItemChecked(w[66],0);
		SetMenuItemChecked(w[67],0);
		SetMenuItemChecked(w[68],0);
		SetMenuItemChecked(w[69],0);
		SetMenuItemChecked(w[82],0);
		}
	if (mode == 1) SetMenuItemChecked(w[63],0);
	dessiner();
	}
	
void Checked_coefficient_f(Widget widget, void *data)
	{
	int mode;
	mode = GetMenuItemChecked(w[64]);
	if (mode == 0) 
		{
		SetMenuItemChecked(w[20],0);
		SetMenuItemChecked(w[94],0);
		SetMenuItemChecked(w[102],0);
		SetMenuItemChecked(w[95],0);
		SetMenuItemChecked(w[21],0);
		SetMenuItemChecked(w[22],0);
		SetMenuItemChecked(w[23],0);
		SetMenuItemChecked(w[84],0);
		SetMenuItemChecked(w[24],0);
		SetMenuItemChecked(w[25],0);
		SetMenuItemChecked(w[27],0);
		SetMenuItemChecked(w[56],0);
		SetMenuItemChecked(w[57],0);
		SetMenuItemChecked(w[72],0);
		SetMenuItemChecked(w[58],0);
		SetMenuItemChecked(w[59],0);
		SetMenuItemChecked(w[60],0);
		SetMenuItemChecked(w[61],0);
		SetMenuItemChecked(w[62],0);
		SetMenuItemChecked(w[73],0);
		SetMenuItemChecked(w[63],0);
		SetMenuItemChecked(w[64],1);
		SetMenuItemChecked(w[65],0);
		SetMenuItemChecked(w[66],0);
		SetMenuItemChecked(w[67],0);
		SetMenuItemChecked(w[68],0);
		SetMenuItemChecked(w[69],0);
		SetMenuItemChecked(w[82],0);
		}
	if (mode == 1) SetMenuItemChecked(w[64],0);
	dessiner();
	}
	
void Checked_section_element(Widget widget, void *data)
	{
	int mode;
	mode = GetMenuItemChecked(w[65]);
	if (mode == 0) 
		{
		SetMenuItemChecked(w[20],0);
		SetMenuItemChecked(w[94],0);
		SetMenuItemChecked(w[102],0);
		SetMenuItemChecked(w[95],0);
		SetMenuItemChecked(w[21],0);
		SetMenuItemChecked(w[22],0);
		SetMenuItemChecked(w[23],0);
		SetMenuItemChecked(w[84],0);
		SetMenuItemChecked(w[24],0);
		SetMenuItemChecked(w[25],0);
		SetMenuItemChecked(w[27],0);
		SetMenuItemChecked(w[56],0);
		SetMenuItemChecked(w[57],0);
		SetMenuItemChecked(w[72],0);
		SetMenuItemChecked(w[58],0);
		SetMenuItemChecked(w[59],0);
		SetMenuItemChecked(w[60],0);
		SetMenuItemChecked(w[61],0);
		SetMenuItemChecked(w[62],0);
		SetMenuItemChecked(w[73],0);
		SetMenuItemChecked(w[63],0);
		SetMenuItemChecked(w[64],0);
		SetMenuItemChecked(w[65],1);
		SetMenuItemChecked(w[66],0);
		SetMenuItemChecked(w[67],0);
		SetMenuItemChecked(w[68],0);
		SetMenuItemChecked(w[69],0);
		SetMenuItemChecked(w[82],0);
		}
	if (mode == 1) SetMenuItemChecked(w[65],0);
	dessiner();
	}
	
void Checked_volume_element(Widget widget, void *data)
	{
	int mode;
	mode = GetMenuItemChecked(w[66]);
	if (mode == 0) 
		{
		SetMenuItemChecked(w[20],0);
		SetMenuItemChecked(w[94],0);
		SetMenuItemChecked(w[102],0);
		SetMenuItemChecked(w[95],0);
		SetMenuItemChecked(w[21],0);
		SetMenuItemChecked(w[22],0);
		SetMenuItemChecked(w[23],0);
		SetMenuItemChecked(w[84],0);
		SetMenuItemChecked(w[24],0);
		SetMenuItemChecked(w[25],0);
		SetMenuItemChecked(w[27],0);
		SetMenuItemChecked(w[56],0);
		SetMenuItemChecked(w[57],0);
		SetMenuItemChecked(w[72],0);
		SetMenuItemChecked(w[58],0);
		SetMenuItemChecked(w[59],0);
		SetMenuItemChecked(w[60],0);
		SetMenuItemChecked(w[61],0);
		SetMenuItemChecked(w[62],0);
		SetMenuItemChecked(w[73],0);
		SetMenuItemChecked(w[63],0);
		SetMenuItemChecked(w[64],0);
		SetMenuItemChecked(w[65],0);
		SetMenuItemChecked(w[66],1);
		SetMenuItemChecked(w[67],0);
		SetMenuItemChecked(w[68],0);
		SetMenuItemChecked(w[69],0);
		SetMenuItemChecked(w[82],0);
		}
	if (mode == 1) SetMenuItemChecked(w[66],0);
	dessiner();
	}
	
void Checked_masse_element(Widget widget, void *data)
	{
	int mode;
	mode = GetMenuItemChecked(w[67]);
	if (mode == 0) 
		{
		SetMenuItemChecked(w[20],0);
		SetMenuItemChecked(w[94],0);
		SetMenuItemChecked(w[102],0);
		SetMenuItemChecked(w[95],0);
		SetMenuItemChecked(w[21],0);
		SetMenuItemChecked(w[22],0);
		SetMenuItemChecked(w[23],0);
		SetMenuItemChecked(w[84],0);
		SetMenuItemChecked(w[24],0);
		SetMenuItemChecked(w[25],0);
		SetMenuItemChecked(w[27],0);
		SetMenuItemChecked(w[56],0);
		SetMenuItemChecked(w[57],0);
		SetMenuItemChecked(w[72],0);
		SetMenuItemChecked(w[58],0);
		SetMenuItemChecked(w[59],0);
		SetMenuItemChecked(w[60],0);
		SetMenuItemChecked(w[61],0);
		SetMenuItemChecked(w[62],0);
		SetMenuItemChecked(w[73],0);
		SetMenuItemChecked(w[63],0);
		SetMenuItemChecked(w[64],0);
		SetMenuItemChecked(w[65],0);
		SetMenuItemChecked(w[66],0);
		SetMenuItemChecked(w[67],1);
		SetMenuItemChecked(w[68],0);
		SetMenuItemChecked(w[69],0);
		SetMenuItemChecked(w[82],0);
		}
	if (mode == 1) SetMenuItemChecked(w[67],0);
	dessiner();
	}
	
void Checked_masse_lineique(Widget widget, void *data)
	{
	int mode;
	mode = GetMenuItemChecked(w[68]);
	if (mode == 0) 
		{
		SetMenuItemChecked(w[20],0);
		SetMenuItemChecked(w[94],0);
		SetMenuItemChecked(w[102],0);
		SetMenuItemChecked(w[95],0);
		SetMenuItemChecked(w[21],0);
		SetMenuItemChecked(w[22],0);
		SetMenuItemChecked(w[23],0);
		SetMenuItemChecked(w[84],0);
		SetMenuItemChecked(w[24],0);
		SetMenuItemChecked(w[25],0);
		SetMenuItemChecked(w[27],0);
		SetMenuItemChecked(w[56],0);
		SetMenuItemChecked(w[57],0);
		SetMenuItemChecked(w[72],0);
		SetMenuItemChecked(w[58],0);
		SetMenuItemChecked(w[59],0);
		SetMenuItemChecked(w[60],0);
		SetMenuItemChecked(w[61],0);
		SetMenuItemChecked(w[62],0);
		SetMenuItemChecked(w[73],0);
		SetMenuItemChecked(w[63],0);
		SetMenuItemChecked(w[64],0);
		SetMenuItemChecked(w[65],0);
		SetMenuItemChecked(w[66],0);
		SetMenuItemChecked(w[67],0);
		SetMenuItemChecked(w[68],1);
		SetMenuItemChecked(w[69],0);
		SetMenuItemChecked(w[82],0);
		}
	if (mode == 1) SetMenuItemChecked(w[68],0);
	dessiner();
	}
	

void Checked_flottabilite(Widget widget, void *data)
	{
	int mode;
	mode = GetMenuItemChecked(w[69]);
	if (mode == 0) 
		{
		SetMenuItemChecked(w[20],0);
		SetMenuItemChecked(w[94],0);
		SetMenuItemChecked(w[102],0);
		SetMenuItemChecked(w[95],0);
		SetMenuItemChecked(w[21],0);
		SetMenuItemChecked(w[22],0);
		SetMenuItemChecked(w[23],0);
		SetMenuItemChecked(w[84],0);
		SetMenuItemChecked(w[24],0);
		SetMenuItemChecked(w[25],0);
		SetMenuItemChecked(w[27],0);
		SetMenuItemChecked(w[56],0);
		SetMenuItemChecked(w[57],0);
		SetMenuItemChecked(w[72],0);
		SetMenuItemChecked(w[58],0);
		SetMenuItemChecked(w[59],0);
		SetMenuItemChecked(w[60],0);
		SetMenuItemChecked(w[61],0);
		SetMenuItemChecked(w[62],0);
		SetMenuItemChecked(w[73],0);
		SetMenuItemChecked(w[63],0);
		SetMenuItemChecked(w[64],0);
		SetMenuItemChecked(w[65],0);
		SetMenuItemChecked(w[66],0);
		SetMenuItemChecked(w[67],0);
		SetMenuItemChecked(w[68],0);
		SetMenuItemChecked(w[69],1);
		SetMenuItemChecked(w[82],0);
		}
	if (mode == 1) SetMenuItemChecked(w[69],0);
	dessiner();
	}
/* fin modifdp du 4 mars 2010*/
	

void Checked_type_noeud(Widget widget, void *data)
	{
	int mode;
	mode = GetMenuItemChecked(w[28]);
	if (mode == 0) 
		{
		SetMenuItemChecked(w[28],1);
		SetMenuItemChecked(w[32],0);
		SetMenuItemChecked(w[33],0);
		SetMenuItemChecked(w[35],0);
		SetMenuItemChecked(w[38],0);
		SetMenuItemChecked(w[41],0);
		SetMenuItemChecked(w[44],0);
		SetMenuItemChecked(w[47],0);
		SetMenuItemChecked(w[50],0);
		SetMenuItemChecked(w[53],0);
		SetMenuItemChecked(w[80],0);
		}
	if (mode == 1) SetMenuItemChecked(w[28],0);
	dessiner();
	}
	
void Checked_numero_noeud(Widget widget, void *data)
	{
	int mode;
	mode = GetMenuItemChecked(w[33]);
	if (mode == 0) 
		{
		SetMenuItemChecked(w[28],0);
		SetMenuItemChecked(w[32],0);
		SetMenuItemChecked(w[33],1);
		SetMenuItemChecked(w[35],0);
		SetMenuItemChecked(w[38],0);
		SetMenuItemChecked(w[41],0);
		SetMenuItemChecked(w[44],0);
		SetMenuItemChecked(w[47],0);
		SetMenuItemChecked(w[50],0);
		SetMenuItemChecked(w[53],0);
		SetMenuItemChecked(w[80],0);
		}
	if (mode == 1) SetMenuItemChecked(w[33],0);
	dessiner();
	}
	
void Checked_masse_noeud(Widget widget, void *data)
	{
	int mode;
	mode = GetMenuItemChecked(w[32]);
	if (mode == 0) 
		{
		SetMenuItemChecked(w[28],0);
		SetMenuItemChecked(w[32],1);
		SetMenuItemChecked(w[33],0);
		SetMenuItemChecked(w[35],0);
		SetMenuItemChecked(w[38],0);
		SetMenuItemChecked(w[41],0);
		SetMenuItemChecked(w[44],0);
		SetMenuItemChecked(w[47],0);
		SetMenuItemChecked(w[50],0);
		SetMenuItemChecked(w[53],0);
		SetMenuItemChecked(w[80],0);
		}
	if (mode == 1) SetMenuItemChecked(w[32],0);
	dessiner();
	}
	
	
void Checked_longueur_noeud(Widget widget, void *data)
	{
	int mode;
	mode = GetMenuItemChecked(w[35]);
	if (mode == 0) 
		{
		SetMenuItemChecked(w[28],0);
		SetMenuItemChecked(w[32],0);
		SetMenuItemChecked(w[33],0);
		SetMenuItemChecked(w[35],1);
		SetMenuItemChecked(w[38],0);
		SetMenuItemChecked(w[41],0);
		SetMenuItemChecked(w[44],0);
		SetMenuItemChecked(w[47],0);
		SetMenuItemChecked(w[50],0);
		SetMenuItemChecked(w[53],0);
		SetMenuItemChecked(w[80],0);
		}
	if (mode == 1) SetMenuItemChecked(w[35],0);
	dessiner();
	}
	
	
void Checked_cd_noeud(Widget widget, void *data)
	{
	int mode;
	mode = GetMenuItemChecked(w[38]);
	if (mode == 0) 
		{
		SetMenuItemChecked(w[28],0);
		SetMenuItemChecked(w[32],0);
		SetMenuItemChecked(w[33],0);
		SetMenuItemChecked(w[35],0);
		SetMenuItemChecked(w[38],1);
		SetMenuItemChecked(w[41],0);
		SetMenuItemChecked(w[44],0);
		SetMenuItemChecked(w[47],0);
		SetMenuItemChecked(w[50],0);
		SetMenuItemChecked(w[53],0);
		SetMenuItemChecked(w[80],0);
		}
	if (mode == 1) SetMenuItemChecked(w[38],0);
	dessiner();
	}
	
	
void Checked_effort_noeud(Widget widget, void *data)
	{
	int mode;
	mode = GetMenuItemChecked(w[41]);
	if (mode == 0) 
		{
		SetMenuItemChecked(w[28],0);
		SetMenuItemChecked(w[32],0);
		SetMenuItemChecked(w[33],0);
		SetMenuItemChecked(w[35],0);
		SetMenuItemChecked(w[38],0);
		SetMenuItemChecked(w[41],1);
		SetMenuItemChecked(w[44],0);
		SetMenuItemChecked(w[47],0);
		SetMenuItemChecked(w[50],0);
		SetMenuItemChecked(w[53],0);
		SetMenuItemChecked(w[80],0);
		}
	if (mode == 1) SetMenuItemChecked(w[41],0);
	dessiner();
	}
	
	
void Checked_limite_noeud(Widget widget, void *data)
	{
	int mode;
	mode = GetMenuItemChecked(w[44]);
	if (mode == 0) 
		{
		SetMenuItemChecked(w[28],0);
		SetMenuItemChecked(w[32],0);
		SetMenuItemChecked(w[33],0);
		SetMenuItemChecked(w[35],0);
		SetMenuItemChecked(w[38],0);
		SetMenuItemChecked(w[41],0);
		SetMenuItemChecked(w[44],1);
		SetMenuItemChecked(w[47],0);
		SetMenuItemChecked(w[50],0);
		SetMenuItemChecked(w[53],0);
		SetMenuItemChecked(w[80],0);
		}
	if (mode == 1) SetMenuItemChecked(w[44],0);
	dessiner();
	}
	
	
void Checked_sens_limite_noeud(Widget widget, void *data)
	{
	int mode;
	mode = GetMenuItemChecked(w[47]);
	if (mode == 0) 
		{
		SetMenuItemChecked(w[28],0);
		SetMenuItemChecked(w[32],0);
		SetMenuItemChecked(w[33],0);
		SetMenuItemChecked(w[35],0);
		SetMenuItemChecked(w[38],0);
		SetMenuItemChecked(w[41],0);
		SetMenuItemChecked(w[44],0);
		SetMenuItemChecked(w[47],1);
		SetMenuItemChecked(w[50],0);
		SetMenuItemChecked(w[53],0);
		SetMenuItemChecked(w[80],0);
		}
	if (mode == 1) SetMenuItemChecked(w[47],0);
	dessiner();
	}
	
	
void Checked_deplacement_noeud(Widget widget, void *data)
	{
	int mode;
	mode = GetMenuItemChecked(w[50]);
	if (mode == 0) 
		{
		SetMenuItemChecked(w[28],0);
		SetMenuItemChecked(w[32],0);
		SetMenuItemChecked(w[33],0);
		SetMenuItemChecked(w[35],0);
		SetMenuItemChecked(w[38],0);
		SetMenuItemChecked(w[41],0);
		SetMenuItemChecked(w[44],0);
		SetMenuItemChecked(w[47],0);
		SetMenuItemChecked(w[50],1);
		SetMenuItemChecked(w[53],0);
		SetMenuItemChecked(w[80],0);
		}
	if (mode == 1) SetMenuItemChecked(w[50],0);
	dessiner();
	}
	
	

void Checked_symmetrie_noeud(Widget widget, void *data)
	{
	int mode;
	mode = GetMenuItemChecked(w[53]);
	if (mode == 0) 
		{
		SetMenuItemChecked(w[28],0);
		SetMenuItemChecked(w[32],0);
		SetMenuItemChecked(w[33],0);
		SetMenuItemChecked(w[35],0);
		SetMenuItemChecked(w[38],0);
		SetMenuItemChecked(w[41],0);
		SetMenuItemChecked(w[44],0);
		SetMenuItemChecked(w[47],0);
		SetMenuItemChecked(w[50],0);
		SetMenuItemChecked(w[53],1);
		SetMenuItemChecked(w[80],0);
		}
	if (mode == 1) SetMenuItemChecked(w[53],0);
	dessiner();
	}


void Checked_nb_mailles(Widget widget, void *data)
	{
	int mode;
	mode = GetMenuItemChecked(w[80]);
	if (mode == 0) 
		{
		SetMenuItemChecked(w[28],0);
		SetMenuItemChecked(w[32],0);
		SetMenuItemChecked(w[33],0);
		SetMenuItemChecked(w[35],0);
		SetMenuItemChecked(w[38],0);
		SetMenuItemChecked(w[41],0);
		SetMenuItemChecked(w[44],0);
		SetMenuItemChecked(w[47],0);
		SetMenuItemChecked(w[50],0);
		SetMenuItemChecked(w[53],0);
		SetMenuItemChecked(w[80],1);
		}
	if (mode == 1) SetMenuItemChecked(w[80],0);
	dessiner();
	}
