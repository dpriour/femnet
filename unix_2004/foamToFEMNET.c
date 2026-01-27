#define PRINCIPAL 0
#include "4c19.h"

/* reads OpenFOAM output, sorts data, writes *.spe file */

int foamToFEMNET(char *nomfichier)
	{
  	char tonom[1000];
	char tonom1[1000];
	char tonom2[1000];
	char *buffer;
	char t1[256];
	char t2[12];
	//char	pathOFc[44] = "/home/kbreddermann/FEMNET/OpenFOAM/OFcase/";
  	int j,k,elem,itmp;
  	double d,d1;
  	FILE *f1;
	FILE *f2;
	FILE *f3;
printf("foamToFEMNET is called\n");
/*check for and read OpenFOAM latestTime*/
	strcpy(tonom2,Structure.pathOFc);
    	strcat(tonom2,"postProcessing/surfaces/latestTimeStep.txt");
	f3 = fopen(tonom2,"r");	
	if (f3 == NULL) 
  		{
    		printf(" \n");
    		printf("%s %s %s \n","file ",tonom2," don't exist");
    		/*fclose(f1);*/
    		return 0;
  		} 
  	else
  		{
    		printf(" \n");
    		printf("%s %s %s \n","file ",tonom2," exists ");
		buffer = fgets(t2,12,f3);
		t2[strcspn(t2,"\n")]= 0;//removes '\n' added by fgets()
		}		
	fclose(f3);

	strcpy(tonom1,Structure.pathOFc);
    	strcat(tonom1,"postProcessing/surfaces/");
	strcat(tonom1, t2); /*add the lastestTime directory to path*/
	strcat(tonom1,"/U_inputFEMNET.raw");

	f2 = fopen(tonom1,"r");	
	if (f2 == NULL) 
  		{
    		printf(" \n");
    		printf("%s %s %s \n","file ",tonom1," don't exist");
    		/*fclose(f1);*/
    		return 0;
  		} 
  	else
  		{
    		printf(" \n");
    		printf("%s %s %s \n","file ",tonom1," exists ");
  	buffer = fgets(t1,256,f2);  /* t1 contains first line of file *.raw*/
  	buffer = fgets(t1,256,f2);  /* t1 contains first line of file *.raw*/
	for (elem=1;elem<=NOMBRE_NOEUDS;elem++)
    			{
			itmp = fscanf(f2,"%lf %lf %lf %lf %lf %lf ",\
			&Noeud[elem].OFx,&Noeud[elem].OFy,&Noeud[elem].OFz,&Noeud[elem].OFsx,\
			&Noeud[elem].OFsy,&Noeud[elem].OFsz);
			}
		}
	fclose(f2);
	strcpy(tonom,nomfichier);
        j=strlen(tonom);
        while ((tonom[j])!='.' && j>0) j--;
        if (tonom[j]=='.') tonom[j]=0;

  	strcat(tonom,".spe");
  	f1 = fopen(tonom,"w");
/*calculation and comparison of the squared distances between points/noueds to find the associated points/noeuds*/	  	
	for (elem=1;elem<=NOMBRE_NOEUDS;elem++)
    		{
		k=0;
		d=1; /*sets d to arbitrary distance*/
			/*search loop*/		
			for (j=1;j<=NOMBRE_NOEUDS;j++)
    			{		
			d1=(Noeud[elem].x-Noeud[j].OFx)*(Noeud[elem].x-Noeud[j].OFx)+(Noeud[elem].y-Noeud[j].OFy)*(Noeud[elem].y-Noeud[j].OFy)+(Noeud[elem].z-Noeud[j].OFz)*(Noeud[elem].z-Noeud[j].OFz);
			if (d1<=d){
			k=j;
			d=d1;
			}
			}
			fprintf(f1,"%d",elem);	
			//fprintf(f1,"%17.9lf ",Noeud[elem].x);	
			//fprintf(f1,"%17.9lf ",Noeud[elem].y);	
			//fprintf(f1,"%17.9lf ",Noeud[elem].z);
			fprintf(f1,"%17.9lf ",Noeud[k].OFsx);	
			fprintf(f1,"%17.9lf ",Noeud[k].OFsy);	
			fprintf(f1,"%17.9lf\n",Noeud[k].OFsz);    			
		}
    		/*for (elem=1;elem<=NOMBRE_NOEUDS;elem++)
    			{
			fprintf(f1,"%d   ",elem);	
			fprintf(f1,"%17.9lf   ",Noeud[elem].OFx);	
			fprintf(f1,"%17.9lf   ",Noeud[elem].OFy);	
			fprintf(f1,"%17.9lf   ",Noeud[elem].OFz);
			fprintf(f1,"%17.9lf   ",Noeud[elem].OFsx);	
			fprintf(f1,"%17.9lf   ",Noeud[elem].OFsy);	
			fprintf(f1,"%17.9lf   \n",Noeud[elem].OFsz); 			
			}*/
      
    		fclose(f1);
        printf("speed file is written\n");		
        return 1;
	}	
	

