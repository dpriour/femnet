#include "4c19.h"	
	
void filethydro4_sta_zhan()

{

/*efforts de trainee hydrodynamique agissant sur les fils du filet en tenant
compte de la proportion de la surface mouillee par rapport a la surface totale.
prend en compte la ponderation liee a la surface libre*/
  
int zi,zl;
double ba[4],Vw[4],nt[4];
  
for (zi = 1 ; zi <= NOMBRE_SURFACES ; zi++)
	{
	Vw[1] = Courant.vitesse*cos(Courant.direction*PI/180.0) * panneau[Surface[zi].type].current_reduction;
	Vw[2] = Courant.vitesse*sin(Courant.direction*PI/180.0) * panneau[Surface[zi].type].current_reduction;
	Vw[3] = 0.0                                             * panneau[Surface[zi].type].current_reduction;
	//twine u
	ba[1] = Surface[zi].nx;
	ba[2] = Surface[zi].ny;
	ba[3] = Surface[zi].nz;
	calculeffort_Zhan(zi,Vw,ba);
	calculeffort_Zhan(zi,Vw,ba);
	calculeffort_Zhan(zi,Vw,ba);
	//twine v
	ba[1] = Surface[zi].mx;
	ba[2] = Surface[zi].my;
	ba[3] = Surface[zi].mz;
	calculeffort_Zhan(zi,Vw,ba);
	calculeffort_Zhan(zi,Vw,ba);
	calculeffort_Zhan(zi,Vw,ba);
	}
}



void calculeffort_Zhan(int notria,double VV[4],double UV[4])
/*from Analytical and experimental investigation of drag on nets of fish cages
Zhan and al, 2005, Aquacultural engineering*/

	{
	int i,pa;
	double modne,deltal,dd,temp1;
	double Rne[4],Rte[4],mod_Rne,mod_Rte,temp[4];
	double ii[4],uv[4],vv[4],VN[4],VT[4],vn[4],vt[4],mod_VN,mod_VT,mod_VV,mod_UV;
	double c1,c2,c3,c4,c5,Sn;
	
	/*VV : current			vv : normalized current*/
	/*UV : twine			uv : normalized twine*/
	/*VN : normal current		vn : normalized normal current*/
	/*VT : tangent current		vt : normalized tangent current*/
	
	Sn = Solidity_diamond(notria);				/*solidity of the triangular element*/
	
	deltal = Surface[notria].lgrepos;		/*bar length*/
	dd = Surface[notria].diametrehydro;		/*twine diameter*/
	c1 =  0.137;
	c2 =  1.002;
	c3 =  2.230;
	c4 = -0.211;
	c5 =  0.947;
	
	ii[1] = 1.0;	ii[2] = 0.0;	ii[3] = 0.0;
	produit_vect3(VV, UV, temp);						/*temp is normal to VV (current) and UV (twine)*/
	produit_vect3(UV, temp, VN);						/*VN along the component of VV (current) normal to the twine*/
	temp1 = sqrt(produit_scal(VN,VN));					/*temp1 module of VN*/
	if (temp1 != 0.0) 
		{
		produit_scal_vect(1/temp1, VN, vn);		/*vn*/		/*vn normalized component of VV (current) normal to the twine*/
		mod_VN = produit_scal(VV,vn);			/*mod_VN*/	/*mod_VN is the amplitude of the component of VV (current) normal to the twine */
		}
	else
		{
		vn[1] = 1.0;	vn[2] = 0.0;	vn[3] = 0.0;	/*vn*/		/*vn is something*/
		mod_VN = 0.0;					/*mod_VN*/	/*mod_VN is the amplitude of the component of VV (current) normal to the twine */
		}
	produit_scal_vect(mod_VN, vn, VN);			/*VN*/		/*VN component of VV (current) normal to the twine*/
	mod_VV = sqrt(produit_scal(VV,VV));					/*mod_VV module of VV*/
	if (mod_VV != 0.0) 
		{
		produit_scal_vect(1/mod_VV, VV, vv);		/*vv*/		/*current normalized*/
		}
	else
		{
		vv[1] = 1.0;	vv[2] = 0.0;	vv[3] = 0.0;	/*vv*/		/*vv is something*/
		}
	produit_scal_vect(-1.0, VN, temp);					/*temp is now the opprosite of the previous one VN*/
	add_vect(temp, VV, VT);					/*VT*/		/*VT component of VV (current) parralel to the twine*/
	mod_VT = sqrt(produit_scal(VT,VT));			/*mod_VT*/	/*mod_VT module of VT*/
	if (mod_VT != 0.0) 
		{
		produit_scal_vect(1/mod_VT, VT, vt);		/*vt*/		/*vt normalized component of VV (current) parrallel to the twine*/
		}
	else
		{
		vt[1] = 1.0;	vt[2] = 0.0;	vt[3] = 0.0;	/*vt*/		/*vt is something*/
		}
	//Only 1/3 is calculated because this function is used by dyna2 which calculates by vertex
	mod_Rne = 0.5 * RHO * deltal * dd * mod_VN * (mod_VN + c1 + c2 * mod_VN * Sn + c3 * mod_VN * Sn * Sn) / 3.0;
	produit_scal_vect(mod_Rne, vn, Rne);					/*Rne normal force to one twine*/
	
	mod_Rte = 0.5 * RHO * deltal * dd * mod_VT * (mod_VT + c4 + c5 * mod_VT * Sn) / 3.0;
	produit_scal_vect(mod_Rte, vt, Rte);					/*Rte tangent force to one twine*/
	
  	/* tangent and normal force on vertex 1 for twines u and v */
     
	wasurf[yc(notria,1)] += (Rte[1]+Rne[1]) * Surface[notria].pondFS[1] * Surface[notria].nb_cote_u_ou_v / 3.0;		//1/3 de la trainee de tous les fils u
	wasurf[yc(notria,2)] += (Rte[2]+Rne[2]) * Surface[notria].pondFS[1] * Surface[notria].nb_cote_u_ou_v / 3.0;		//1/3 de la trainee de tous les fils u
	wasurf[yc(notria,3)] += (Rte[3]+Rne[3]) * Surface[notria].pondFS[1] * Surface[notria].nb_cote_u_ou_v / 3.0;		//1/3 de la trainee de tous les fils u
	Structure.surface_drag += (Rte[1]+Rne[1]) * Surface[notria].pondFS[1] * Surface[notria].nb_cote_u_ou_v / 3.0;
	if (Sortie_texte.panel_drag == 1)
		{
	  	pa = Surface[notria].type;	/*panel*/
	    	panneau[pa].drag += (Rte[1]+Rne[1]) * Surface[notria].pondFS[1] * Surface[notria].nb_cote_u_ou_v / 3.0;
	    	Surface[notria].panel_drag += (Rte[1]+Rne[1]) * Surface[notria].pondFS[1] * Surface[notria].nb_cote_u_ou_v / 3.0;
		}
     	
  	/* tangent and normal force on vertex 2 for twines u and v */
    
	wasurf[yc(notria,4)] += (Rte[1]+Rne[1]) * Surface[notria].pondFS[2] * Surface[notria].nb_cote_u_ou_v / 3.0;		//1/3 de la trainee de tous les fils u
	wasurf[yc(notria,5)] += (Rte[2]+Rne[2]) * Surface[notria].pondFS[2] * Surface[notria].nb_cote_u_ou_v / 3.0;		//1/3 de la trainee de tous les fils u
	wasurf[yc(notria,6)] += (Rte[3]+Rne[3]) * Surface[notria].pondFS[2] * Surface[notria].nb_cote_u_ou_v / 3.0;		//1/3 de la trainee de tous les fils u
	Structure.surface_drag += (Rte[1]+Rne[1]) * Surface[notria].pondFS[2] * Surface[notria].nb_cote_u_ou_v / 3.0;
	if (Sortie_texte.panel_drag == 1)
		{
	  	pa = Surface[notria].type;	/*panel*/
	    	panneau[pa].drag += (Rte[1]+Rne[1]) * Surface[notria].pondFS[2] * Surface[notria].nb_cote_u_ou_v / 3.0;
	    	Surface[notria].panel_drag += (Rte[1]+Rne[1]) * Surface[notria].pondFS[2] * Surface[notria].nb_cote_u_ou_v / 3.0;
		}
     	
  	/* tangent and normal force on vertex 3 for twines u and v */
    
	wasurf[yc(notria,7)] += (Rte[1]+Rne[1]) * Surface[notria].pondFS[3] * Surface[notria].nb_cote_u_ou_v / 3.0;		//1/3 de la trainee de tous les fils u
	wasurf[yc(notria,8)] += (Rte[2]+Rne[2]) * Surface[notria].pondFS[3] * Surface[notria].nb_cote_u_ou_v / 3.0;		//1/3 de la trainee de tous les fils u
	wasurf[yc(notria,9)] += (Rte[3]+Rne[3]) * Surface[notria].pondFS[3] * Surface[notria].nb_cote_u_ou_v / 3.0;		//1/3 de la trainee de tous les fils u
	Structure.surface_drag += (Rte[1]+Rne[1]) * Surface[notria].pondFS[3] * Surface[notria].nb_cote_u_ou_v / 3.0;
	if (Sortie_texte.panel_drag == 1)
		{
	  	pa = Surface[notria].type;	/*panel*/
	    	panneau[pa].drag += (Rte[1]+Rne[1]) * Surface[notria].pondFS[3] * Surface[notria].nb_cote_u_ou_v / 3.0;
	    	Surface[notria].panel_drag += (Rte[1]+Rne[1]) * Surface[notria].pondFS[3] * Surface[notria].nb_cote_u_ou_v / 3.0;
		}
	} 
	
double Solidity_diamond(int notria)
/*calculation of the solidity ratio of the triangular element in case of diamond meshes*/

	{
	double Vn[4],Vm[4],normal[4];
	double mesh_surface,twine_surface,Sn;
	
	Vn[1] = (float) Surface[notria].nx;	Vn[2] = (float) Surface[notria].ny;	Vn[3] = (float) Surface[notria].nz; /*u twine vector*/
	Vm[1] = (float) Surface[notria].mx;	Vm[2] = (float) Surface[notria].my;	Vm[3] = (float) Surface[notria].mz; /*v twine vector*/
	produit_vect3(Vn, Vm, normal);
	mesh_surface = 2.0 * sqrt(produit_scal(normal,normal));	/*surface of one mesh*/
	twine_surface = 4.0 * Surface[notria].diametrehydro * Surface[notria].lgrepos - Surface[notria].diametrehydro * Surface[notria].diametrehydro;	/*surface of twine in one mesh*/
	Sn = twine_surface / mesh_surface;
	if (Sn > 1.0) Sn = 1.0;
	if (Sn < 0.0) Sn = 0.0;
	
	return Sn;
	
	} 
	
	
	

