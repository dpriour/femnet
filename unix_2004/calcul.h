typedef double Scalaire;
typedef Scalaire Vecteur[3];
typedef Scalaire Derivee_Scalaire[9];
typedef Vecteur* Derivee_Vecteur[9];
typedef Scalaire Derivee_Seconde_Scalaire[9][9];
typedef Vecteur* Derivee_Seconde_Vecteur[9][9];
enum Coordonnee {COORD_X=0, COORD_Y=1, COORD_Z=2};
const char* nom_coordonnee[9] = {"x1", "y1", "z1", "x2", "y2", "z2", "x3", "y3", "z3"};

__inline__ Vecteur* nouveauVecteur(void);
void nettoyerVecteurs(void);
Vecteur *vecteur(Scalaire x, Scalaire y, Scalaire z);
Vecteur *produitVectoriel(Vecteur *v1, Vecteur *v2);
Scalaire produitScalaire(Vecteur *v1, Vecteur *v2);
Vecteur *sommeVecteurs(Vecteur *v1, Vecteur *v2);
Vecteur *soustractionVecteurs(Vecteur *v1, Vecteur *v2);
Vecteur *multiplicationVecteurScalaire(Vecteur *v, Scalaire s);
Scalaire normeVecteur(Vecteur *v);
void symetriserDeriveeSecondeVecteur(Derivee_Seconde_Vecteur *d2v);
void symetriserDeriveeSecondeScalaire(Derivee_Seconde_Scalaire *d2s);
void printScalaire(Scalaire s);
void printVecteur(Vecteur *v);
void printDeriveeScalaire(Derivee_Scalaire *d);
void printDeriveeSecondeScalaire(Derivee_Seconde_Scalaire *d2);
void printDeriveeVecteur(Derivee_Vecteur *dv);
void printDeriveeSecondeVecteur(Derivee_Seconde_Vecteur *d2v);

#define MAX_VECTEURS	20
Vecteur liste_vecteurs[MAX_VECTEURS];
int nombre_vecteurs = 0;

Vecteur *nouveauVecteur(void){
	return &(liste_vecteurs[nombre_vecteurs++]);
}

void nettoyerVecteurs(void){
	nombre_vecteurs = 0;
}

Vecteur *vecteur(Scalaire x, Scalaire y, Scalaire z){
	Vecteur *v = nouveauVecteur();
	(*v)[COORD_X] = x;
	(*v)[COORD_Y] = y;
	(*v)[COORD_Z] = z;
	return v;
}

Vecteur *produitVectoriel(Vecteur *v1, Vecteur *v2){
	Vecteur *v = nouveauVecteur();
	(*v)[COORD_X] = ((*v2)[COORD_Z])*((*v1)[COORD_Y])-((*v2)[COORD_Y])*((*v1)[COORD_Z]);
	(*v)[COORD_Y] = ((*v2)[COORD_X])*((*v1)[COORD_Z])-((*v2)[COORD_Z])*((*v1)[COORD_X]);
	(*v)[COORD_Z] = ((*v1)[COORD_X])*((*v2)[COORD_Y])-((*v2)[COORD_X])*((*v1)[COORD_Y]);
	return v;
}

Scalaire produitScalaire(Vecteur *v1, Vecteur *v2){
	int c;
	Scalaire somme = 0;
	for (c=0; c<3; c++) somme += ((*v1)[c])*((*v2)[c]);
	return somme;
}

Vecteur *sommeVecteurs(Vecteur *v1, Vecteur *v2){
	int c;
	Vecteur *v = nouveauVecteur();
	for (c=0; c<3; c++) (*v)[c] = ((*v1)[c])+((*v2)[c]);
	return v;
}

Vecteur *soustractionVecteurs(Vecteur *v1, Vecteur *v2){
	int c;
	Vecteur *v = nouveauVecteur();
	for (c=0; c<3; c++) (*v)[c] = ((*v1)[c])-((*v2)[c]);
	return v;
}

Vecteur *multiplicationVecteurScalaire(Vecteur *v, Scalaire s){
	int c;
	Vecteur *v2 = nouveauVecteur();
	for (c=0; c<3; c++) (*v2)[c] = s*((*v)[c]);
	return v2;
}

Scalaire normeVecteur(Vecteur *v){
	return sqrt(produitScalaire(v, v));
}

void symetriserDeriveeSecondeVecteur(Derivee_Seconde_Vecteur *d2v){
	int i, j;
	for (i=0; i<9; i++) for (j=i+1; j<9; j++) (*d2v)[j][i] = (*d2v)[i][j];
}

void symetriserDeriveeSecondeScalaire(Derivee_Seconde_Scalaire *d2s){
	int i, j;
	for (i=0; i<9; i++) for (j=i+1; j<9; j++) (*d2s)[j][i] = (*d2s)[i][j];
}

void printScalaire(Scalaire s){
	printf("%lf\n", s);
}

void printVecteur(Vecteur *v){
	printf("[%lf ; %lf ; %lf]\n", (*v)[COORD_X], (*v)[COORD_Y], (*v)[COORD_Z]);
}

void printDeriveeScalaire(Derivee_Scalaire *d){
	int i;
	for (i=0; i<9; i++) printf("%s : %lf%s", nom_coordonnee[i], ((*d)[i]), i<8?"\t":"\n");
}

void printDeriveeSecondeScalaire(Derivee_Seconde_Scalaire *d2){
	int i, j;
	printf("Derivee seconde scalaire ###############################\n");
	for (i=0; i<9; i++) for (j=0; j<9; j++) printf("(%s,%s) : %lf%s", nom_coordonnee[i], nom_coordonnee[j], ((*d2)[i][j]), j<8?"\t":"\n");
	printf("########################################################\n");
}

void printDeriveeVecteur(Derivee_Vecteur *dv){
	int i;
	printf("Derivee vecteur ########################################\n");
	for (i=0; i<9; i++){
		printf("%s : ", nom_coordonnee[i]);
		printVecteur((*dv)[i]);
	}
	printf("########################################################\n");
}

void printDeriveeSecondeVecteur(Derivee_Seconde_Vecteur *d2v){
	int i, j;
	printf("Derivee seconde vecteur ################################\n");
	for (i=0; i<9; i++){
		for (j=0; j<9; j++){
			printf("(%s, %s) : ", nom_coordonnee[i], nom_coordonnee[j]);
			printVecteur(((*d2v)[i][j]));
		}
	}
	printf("########################################################\n");
}

