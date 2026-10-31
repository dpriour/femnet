#include "batz.h"

void commentaire()
	{
	/*ecrit les commentaires*/
	
	int pa,no;


	float xx1,yy1;
	char chaine[155];
	
	Color(BLUE);
	  	
	yy1 = (float) (0.95); 	
  	for( pa = 1 ; pa <= Sortie_texte.nb_distance ; pa++ )
  		{
		yy1 += (float) (-0.02); 	/*decalage de 1 puisque c est un element*/
		xx1 = (float) (0.5);
		/*sprintf(chaine,"%s %.3g",Sortie_texte.comment_distance[pa].texte,Sortie_texte.valeur_distance[pa]);
    		Text(xx1,yy1,chaine);*/
		/*sprintf(chaine,"%s",Sortie_texte.comment_distance[pa].texte);
    		Text(xx1,yy1,chaine);*/
    		
		no = 0;
		while ((Sortie_texte.comment_distance[pa].texte[no] !=':') && (no<155))
			{
			no++;
			xx1 = (float) (0.5 + 0.008 * no);
			if (Sortie_texte.comment_distance[pa].texte[no] != '\t') sprintf(chaine,"%c",Sortie_texte.comment_distance[pa].texte[no]);
			if (Sortie_texte.comment_distance[pa].texte[no] == '\t') sprintf(chaine,"%s"," ");
    			Text(xx1,yy1,chaine);
			}
		xx1 = (float) (0.95);
		sprintf(chaine,"%.3g",Sortie_texte.valeur_distance[pa]);
    		Text(xx1,yy1,chaine);
  		}
  		
  	for( pa = 1 ; pa <= Sortie_texte.nb_effort ; pa++ )
  		{
		yy1 += (float) (-0.02); 	/*decalage de 1 puisque c est un element*/
		no = 0;
		while ((Sortie_texte.comment_effort[pa].texte[no] !=':') && (no<155))
			{
			no++;
			xx1 = (float) (0.5 + 0.008 * no);
			if (Sortie_texte.comment_effort[pa].texte[no] != '\t') sprintf(chaine,"%c",Sortie_texte.comment_effort[pa].texte[no]);
			if (Sortie_texte.comment_effort[pa].texte[no] == '\t') sprintf(chaine,"%s"," ");
    			Text(xx1,yy1,chaine);
			}
		xx1 = (float) (0.95);
		sprintf(chaine,"%.3g",Sortie_texte.valeur_effort[pa]);
    		Text(xx1,yy1,chaine);
  		}
  		
  	for( pa = 1 ; pa <= Sortie_texte.nb_tension_element ; pa++ )
  		{
		yy1 += (float) (-0.02); 	/*decalage de 1 puisque c est un element*/
		no = 0;
		while ((Sortie_texte.comment_tension_element[pa].texte[no] !=':') && (no<155))
			{
			no++;
			xx1 = (float) (0.5 + 0.008 * no);
			if (Sortie_texte.comment_tension_element[pa].texte[no] != '\t') sprintf(chaine,"%c",Sortie_texte.comment_tension_element[pa].texte[no]);
			if (Sortie_texte.comment_tension_element[pa].texte[no] == '\t') sprintf(chaine,"%s"," ");
    			Text(xx1,yy1,chaine);
			}
		xx1 = (float) (0.95);
		sprintf(chaine,"%.3g",Sortie_texte.valeur_tension[pa]);
    		Text(xx1,yy1,chaine);
  		}
  		
  	for( pa = 1 ; pa <= Sortie_texte.nb_tension_coulisse ; pa++ )
  		{
		yy1 += (float) (-0.02); 	/*decalage de 1 puisque c est un element*/
		no = 0;
		while ((Sortie_texte.comment_tension_coulisse[pa].texte[no] !=':') && (no<155))
			{
			no++;
			xx1 = (float) (0.5 + 0.008 * no);
			if (Sortie_texte.comment_tension_coulisse[pa].texte[no] != '\t') sprintf(chaine,"%c",Sortie_texte.comment_tension_coulisse[pa].texte[no]);
			if (Sortie_texte.comment_tension_coulisse[pa].texte[no] == '\t') sprintf(chaine,"%s"," ");
    			Text(xx1,yy1,chaine);
			}
		xx1 = (float) (0.95);
		sprintf(chaine,"%.3g",Sortie_texte.valeur_tension_coulisse[pa]);
    		Text(xx1,yy1,chaine);
  		}
  		
  	for( pa = 1 ; pa <= Sortie_texte.nb_position ; pa++ )
  		{
		yy1 += (float) (-0.02); 	/*decalage de 1 puisque c est un element*/
		no = 0;
		while ((Sortie_texte.comment_position[pa].texte[no] !=':') && (no<155))
			{
			no++;
			xx1 = (float) (0.5 + 0.008 * no);
			if (Sortie_texte.comment_position[pa].texte[no] != '\t') sprintf(chaine,"%c",Sortie_texte.comment_position[pa].texte[no]);
			if (Sortie_texte.comment_position[pa].texte[no] == '\t') sprintf(chaine,"%s"," ");
    			Text(xx1,yy1,chaine);
			}
		xx1 = (float) (0.95);
		sprintf(chaine,"%.3g",Sortie_texte.valeur_position[pa]);
    		Text(xx1,yy1,chaine);
  		}
  		
  	if(Sortie_texte.bottom_drag == 1)
  		{
		xx1 = (float) (0.5);
		yy1 += (float) (-0.02); 	/*decalage de 1 puisque c est un element*/
		Text(xx1,yy1," bottom drag   (N):");
		xx1 = (float) (0.95);
		sprintf(chaine,"%.3g",Sortie_texte.valeur_bottom_drag);
    		Text(xx1,yy1,chaine);
  		}
  		
  	if(Sortie_texte.catch_drag == 1)
  		{
		xx1 = (float) (0.5);
		yy1 += (float) (-0.02); 	/*decalage de 1 puisque c est un element*/
		Text(xx1,yy1," catch drag   (N):");
		xx1 = (float) (0.95);
		sprintf(chaine,"%.3g",Sortie_texte.valeur_catch_drag);
    		Text(xx1,yy1,chaine);
  		}
  		
  	if(Sortie_texte.element_drag == 1)
  		{
		xx1 = (float) (0.5);
		yy1 += (float) (-0.02); 	/*decalage de 1 puisque c est un element*/
		Text(xx1,yy1," cable drag   (N):");
		xx1 = (float) (0.95);
		sprintf(chaine,"%.3g",Sortie_texte.valeur_element_drag);
    		Text(xx1,yy1,chaine);
  		}
  		
  	if(Sortie_texte.surface_drag == 1)
  		{
		xx1 = (float) (0.5);
		yy1 += (float) (-0.02); 	/*decalage de 1 puisque c est un element*/
		Text(xx1,yy1," netting drag   (N):");
		xx1 = (float) (0.95);
		sprintf(chaine,"%.3g",Sortie_texte.valeur_surface_drag);
    		Text(xx1,yy1,chaine);
  		}
  		
  	if(Sortie_texte.node_drag == 1)
  		{
		xx1 = (float) (0.5);
		yy1 += (float) (-0.02); 	/*decalage de 1 puisque c est un element*/
		Text(xx1,yy1," node drag   (N):");
		xx1 = (float) (0.95);
		sprintf(chaine,"%.3g",Sortie_texte.valeur_node_drag);
    		Text(xx1,yy1,chaine);
  		}
  		
  	if(Sortie_texte.effort_structure == 1)
  		{
		xx1 = (float) (0.5);
		yy1 += (float) (-0.02); 	/*decalage de 1 puisque c est un element*/
		Text(xx1,yy1," forces X Y Z (N):");
		xx1 = (float) (0.75);
		sprintf(chaine,"%.3g",Sortie_texte.valeur_effort_structure[1]);
    		Text(xx1,yy1,chaine);
		xx1 = (float) (0.85);
		sprintf(chaine,"%.3g",Sortie_texte.valeur_effort_structure[2]);
    		Text(xx1,yy1,chaine);
		xx1 = (float) (0.95);
		sprintf(chaine,"%.3g",Sortie_texte.valeur_effort_structure[3]);
    		Text(xx1,yy1,chaine);
		/*printf("Sortie_texte.valeur_effort_structure %lf %lf %lf \n",Sortie_texte.valeur_effort_structure[1],Sortie_texte.valeur_effort_structure[2],Sortie_texte.valeur_effort_structure[3]);*/
  		}
  		
  	if(Sortie_texte.diametre_prise == 1)
  		{
		xx1 = (float) (0.5);
		yy1 += (float) (-0.02); 	/*decalage de 1 puisque c est un element*/
		Text(xx1,yy1," maximal catch diameter   (m):");
		xx1 = (float) (0.95);
		sprintf(chaine,"%.3g",Sortie_texte.valeur_diametre_prise);
    		Text(xx1,yy1,chaine);
  		}
  		
  	if(Sortie_texte.epaisseur_prise == 1)
  		{
		xx1 = (float) (0.5);
		yy1 += (float) (-0.02); 	/*decalage de 1 puisque c est un element*/
		Text(xx1,yy1," catch thickness   (m):");
		xx1 = (float) (0.95);
		sprintf(chaine,"%.3g",Sortie_texte.valeur_epaisseur_prise);
    		Text(xx1,yy1,chaine);
  		}
  		
  	if(Sortie_texte.volume_capture == 1)
  		{
		xx1 = (float) (0.5);
		yy1 += (float) (-0.02); 	/*decalage de 1 puisque c est un element*/
		Text(xx1,yy1," catch volume   (m3):");
		xx1 = (float) (0.95);
		sprintf(chaine,"%.3g",Sortie_texte.valeur_volume_capture);
    		Text(xx1,yy1,chaine);
  		}
  		
  	if(Sortie_texte.vitesse_courant == 1)
  		{
		xx1 = (float) (0.5);
		yy1 += (float) (-0.02); 	/*decalage de 1 puisque c est un element*/
		Text(xx1,yy1," current amplitude   (m/s):");
		xx1 = (float) (0.95);
		sprintf(chaine,"%.3g",Sortie_texte.valeur_vitesse_courant);
    		Text(xx1,yy1,chaine);
  		}
  		
  	if(Sortie_texte.surface_filtree == 1)
  		{
		xx1 = (float) (0.5);
		yy1 += (float) (-0.02); 	/*decalage de 1 puisque c est un element*/
		Text(xx1,yy1," filtered surface   (m2):");
		xx1 = (float) (0.95);
		sprintf(chaine,"%.3g",Sortie_texte.valeur_surface_filtree);
    		Text(xx1,yy1,chaine);
  		}  		
	}
	
