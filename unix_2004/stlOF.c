#define PRINCIPAL 0
#include "4c19.h"
//writes stl and panel stl files
void stlOF()
	{
    char    tonom[1000];
  	int     j,pa,zi,zj,nb_tri;
    double  ux,uy,uz,vx,vy,vz,n1,n2,n3;
    char	panelid[21];

    FILE *f3;
//stl file//////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /* modified K. Breddermann 04.05.2022 */
            strcpy(tonom,Structure.pathOFc);
            strcat(tonom,"constant/triSurface/netbody.stl");
        /*    strcpy(tonom,nomfichier);
            j=strlen(tonom);
            while ((tonom[j])!='.' && j>0) j--;
            if (tonom[j]=='.') tonom[j]=0;
          	strcat(tonom,".stl");*/
          	printf(" \n");
          	printf("%s %s \n","fichier ",tonom);
exit(0);
          	f3 = fopen(tonom,"w");
            if (f3 < 0)
                {   
                printf("\n");
                printf("Could not open the file %s.\n",tonom);
                }
            zi=1;
            nb_tri=0;
            for (pa = 1 ; pa<= Structure.NbTypesurf ; pa++)
                {            
                for (j = 1 ; j<= NOMBRE_SURFACES ; j++) 
	          	    	{  
                        if(Surface[j].type == pa) nb_tri= nb_tri+1;               
                        }                
                        fprintf(f3,"solid panel%d\n",pa);
                        for (j = zi ; j<=nb_tri ; j++) 
	          	    	    {                    
                            ux=wf[3*Surface[j].extremite[2]-2]-wf[3*Surface[j].extremite[1]-2];
                            uy=wf[3*Surface[j].extremite[2]-1]-wf[3*Surface[j].extremite[1]-1];
                            uz=wf[3*Surface[j].extremite[2]-0]-wf[3*Surface[j].extremite[1]-0];
                            vx=wf[3*Surface[j].extremite[3]-2]-wf[3*Surface[j].extremite[1]-2];
                            vy=wf[3*Surface[j].extremite[3]-1]-wf[3*Surface[j].extremite[1]-1];
                            vz=wf[3*Surface[j].extremite[3]-0]-wf[3*Surface[j].extremite[1]-0];
                            n1=(uy*vz-uz*vy)/sqrt((uy*vz-uz*vy)*(uy*vz-uz*vy)+(uz*vx-ux*vz)*(uz*vx-ux*vz)+(ux*vy-uy*vx)*(ux*vy-uy*vx));
                            n2=(uz*vx-ux*vz)/sqrt((uy*vz-uz*vy)*(uy*vz-uz*vy)+(uz*vx-ux*vz)*(uz*vx-ux*vz)+(ux*vy-uy*vx)*(ux*vy-uy*vx));
                            n3=(ux*vy-uy*vx)/sqrt((uy*vz-uz*vy)*(uy*vz-uz*vy)+(uz*vx-ux*vz)*(uz*vx-ux*vz)+(ux*vy-uy*vx)*(ux*vy-uy*vx));   		
                            fprintf(f3,"  facet normal  %.7E  %.7E  %.7E\n", n1,n2,n3);
                            fprintf(f3,"    outer loop\n");
                            fprintf(f3,"      vertex  %.7E  %.7E  %.7E\n",wf[3*Surface[j].extremite[1]-2], wf[3*Surface[j].extremite[1]-1], wf[3*Surface[j].extremite[1]-0]);
	            		    fprintf(f3,"      vertex  %.7E  %.7E  %.7E\n",wf[3*Surface[j].extremite[2]-2], wf[3*Surface[j].extremite[2]-1], wf[3*Surface[j].extremite[2]-0]);
                            fprintf(f3,"      vertex  %.7E  %.7E  %.7E\n",wf[3*Surface[j].extremite[3]-2], wf[3*Surface[j].extremite[3]-1], wf[3*Surface[j].extremite[3]-0]);
                            fprintf(f3,"    endloop\n  endfacet\n");
	          		        }
                        zi=nb_tri+1;
                        fprintf (f3,"endsolid panel%d\n",pa);
                } 
            fclose(f3);
           	printf("stl-file %s written\n",tonom);
//stl file////////////////////////////////////////////////////////////////////////////////////////////////// 
//
//panel stl file ////////////////////////////////////////////////////////////////////////////////////////////
        /* modified K. Breddermann 04.05.2022 */
            memset(tonom,0,strlen(tonom)); //clear tonom            
            strcpy(tonom,Structure.pathOFc);
            strcat(tonom,"constant/triSurface/");
            /*j=strlen(tonom);
            while ((tonom[j])!='.' && j>0) j--;
            if (tonom[j]=='.') tonom[j]=0;
          	strcat(tonom,".stl");*/
            zi=1;
            nb_tri=0;
            for (pa = 1 ; pa<= Structure.NbTypesurf ; pa++)
                {            
                for (j = 1 ; j<= NOMBRE_SURFACES ; j++) 
	          	    	{  
                        if(Surface[j].type == pa) nb_tri= nb_tri+1;               
                        }                
		        zj=strlen(tonom);
           		 while ((tonom[zj])!='/' && zj>0) zj--;
           		 if (tonom[zj]=='/') tonom[zj+1]=0;		
		        panelid[0] = 0;		
		        sprintf(panelid, "panel%d.stl",pa);
		        strcat(tonom,panelid);
		        //printf("%s %s \n","fichier ",tonom);                	
		        f3 = fopen(tonom,"w");
            		if (f3 < 0)
             		   {   
               		   printf("\n");
                	   printf("Could not open the file %s.\n",tonom);
               		   }
		        fprintf(f3,"solid panel%d\n",pa);
                        for (j = zi ; j<=nb_tri ; j++) 
	          	    	    {                    
                            ux=wf[3*Surface[j].extremite[2]-2]-wf[3*Surface[j].extremite[1]-2];
                            uy=wf[3*Surface[j].extremite[2]-1]-wf[3*Surface[j].extremite[1]-1];
                            uz=wf[3*Surface[j].extremite[2]-0]-wf[3*Surface[j].extremite[1]-0];
                            vx=wf[3*Surface[j].extremite[3]-2]-wf[3*Surface[j].extremite[1]-2];
                            vy=wf[3*Surface[j].extremite[3]-1]-wf[3*Surface[j].extremite[1]-1];
                            vz=wf[3*Surface[j].extremite[3]-0]-wf[3*Surface[j].extremite[1]-0];
                            n1=(uy*vz-uz*vy)/sqrt((uy*vz-uz*vy)*(uy*vz-uz*vy)+(uz*vx-ux*vz)*(uz*vx-ux*vz)+(ux*vy-uy*vx)*(ux*vy-uy*vx));
                            n2=(uz*vx-ux*vz)/sqrt((uy*vz-uz*vy)*(uy*vz-uz*vy)+(uz*vx-ux*vz)*(uz*vx-ux*vz)+(ux*vy-uy*vx)*(ux*vy-uy*vx));
                            n3=(ux*vy-uy*vx)/sqrt((uy*vz-uz*vy)*(uy*vz-uz*vy)+(uz*vx-ux*vz)*(uz*vx-ux*vz)+(ux*vy-uy*vx)*(ux*vy-uy*vx));   		
                            fprintf(f3,"  facet normal  %.7E  %.7E  %.7E\n", n1,n2,n3);
                            fprintf(f3,"    outer loop\n");
                            fprintf(f3,"      vertex  %.7E  %.7E  %.7E\n",wf[3*Surface[j].extremite[1]-2], wf[3*Surface[j].extremite[1]-1], wf[3*Surface[j].extremite[1]-0]);
	            		    fprintf(f3,"      vertex  %.7E  %.7E  %.7E\n",wf[3*Surface[j].extremite[2]-2], wf[3*Surface[j].extremite[2]-1], wf[3*Surface[j].extremite[2]-0]);
                            fprintf(f3,"      vertex  %.7E  %.7E  %.7E\n",wf[3*Surface[j].extremite[3]-2], wf[3*Surface[j].extremite[3]-1], wf[3*Surface[j].extremite[3]-0]);
                            fprintf(f3,"    endloop\n  endfacet\n");
	          		        }
                        zi=nb_tri+1;
                        fprintf (f3,"endsolid panel%d\n",pa);
               		fclose(f3);
	         } 
           	printf("panel stl-files written\n");
}
//panel stl file ////////////////////////////////////////////////////////////////////////////////////////////
