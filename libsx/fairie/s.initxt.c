h60231
s 00257/00000/00000
d D 1.1 95/10/17 12:16:32 molagnon 1 0
c date and time created 95/10/17 12:16:32 by molagnon
e
u
U
f e 0
t
T
I 1
#include "../include/faixvt.h"

initxt_ (char *Pzlwin, char *Pzlicn, char *Pzlfon, int *Pkmrg, float *Pxmrg, float *Pymrg, int *Pnlig, int *Pncol, int llwin, int llicn, int llfon)
/* 
 *    initxt =  initialisation d'une fenetre de texte pour affichage
 *              d'ecrans de resultats. 
 *
 *    parametres =
 *    e  Pzlwin	= nom de la fenetre
 *    e  Pzlicn	= nom de l icone
 *    e  Pzlfon	= police de caracteres
 *    e  Pkmrg	= code marge
 *    e  Pxmrg	= marge horizontale
 *    e  Pymrg	= marge verticale
 *
 *    auteurs : M.Olagnon
 *              S.Coudray  ifremer/diti/som
 *    version %I% du %G%
 */

{
     Scrollbar Sbar;
     Rect Srec;
     Xv_font *Sfnt0;
     float xscl, yscl;	/* facteurs d echelle */
     DIMFSTRING (Zlwin, 64);
     DIMFSTRING (Zlicn, 64);
     DIMFSTRING (Zfnt, 64);       /* fonte    */
     int ichr1, ichr2;
     int ltblw, lprt;
     int lxchr, lychr;
     int lxwin, lywin, jxwin, jywin;
     int kmrg;
     extern void inistr ();
     extern void trmrgt ();
     extern void trmlft ();
     extern void cpystr ();
     extern void catstr ();
     extern void prttxt (void);
     extern void efftxt (void);
     extern char *fortoc();
     extern Xv_font *xv_pf_open ();

/* .... initialisation des chaines .................*/

     inistr (Zlwin, fortoc (Pzlwin, llwin), 64);
     inistr (Zlicn, fortoc (Pzlicn, llicn), 64);
     lenchr_ (Pzlfon, &ichr1, &ichr2, llfon);
     ichr1 = ichr1 - 1;
     ltblw = ichr2 - ichr1;
     inistr (Zfnt, fortoc (Pzlfon+ichr1, ltblw), 64);

     trmrgt (Zlwin);
     trmrgt (Zlicn);  

/*   nom de la fenetre 
 *     =  nom passe par l'utilisateur (sans blanc de gauche)
 *     + un tiret
 *     + le nom de l'icone
 */

      strcat (Zlwin, " - ");
      strcat (Zlwin, Zlicn); 

/* ... chargement de l icone ...............................*/

      Srec.r_left = 4;
      Srec.r_height = 12;
      Srec.r_top = ICON_DEFAULT_HEIGHT - 4 - 12;
      Srec.r_width = ICON_DEFAULT_WIDTH - 4 - 4;
      Simgi = xv_create (XV_NULL, SERVER_IMAGE,
                         XV_HEIGHT, ICON_DEFAULT_HEIGHT,
                         XV_WIDTH,   ICON_DEFAULT_WIDTH,
                         SERVER_IMAGE_DEPTH,          1, 
                         SERVER_IMAGE_BITS,       jicnt, 
                         0);

      Sicn = xv_create (XV_NULL,           ICON,
                        ICON_IMAGE,       Simgi,
                        0); 

      if (CHR (Zlicn, 1) != EOS) {
        xv_set (Sicn,
                ICON_LABEL_RECT, Srec,
                XV_LABEL, Zlicn, 
                0);
      }

               
/* ... chargement dune police de caracteres.................*/

        if ((Sfnt0 = xv_pf_open (Zfnt)) == NULL) {
	  Sfnt0 = xv_pf_open ("/usr/lib/fonts/fixedwidthfonts/screen.r.7");
        }

/* ... echelle ...................................................*/

	xscl = ((float) LXWIN) / XWIN;     
	yscl = ((float) LYWIN) / YWIN;  
	 
/* ... taille de la fenetre ..................................... */
        
	lxchr = (int) xv_get (Sfnt0, FONT_CHAR_WIDTH);
	lychr = (int) xv_get (Sfnt0, FONT_CHAR_HEIGHT);
	lxwin = *Pncol * lxchr;
	lywin = *Pnlig * lychr;

/* ... pour tenir compte du cadre et scrollbar .................. */

	lxwin = MRGG + LBAR + lxwin + MRGD;
	lywin = MRGB + lywin + MRGH + HCHX;

/* ... position de la fenetre ................................... */
        
        kmrg = *Pkmrg % 10;
	switch (kmrg) {
      
        case (1):
          jxwin = (int) (*Pxmrg * xscl);
          jywin = LYWIN - lywin - (int) (*Pymrg * yscl);
          break;
      
        case (2):
          jxwin = (LXWIN - lxwin) / 2;
          jywin = LYWIN - lywin - (int) (*Pymrg * yscl);
          break;      
      
        case (3):
          jxwin = LXWIN - lxwin - (int) (*Pxmrg * xscl);
          jywin = LYWIN - lywin - (int) (*Pymrg * yscl);
          break;      

        case (4):
          jxwin = (int) (*Pxmrg * xscl);
          jywin = (LYWIN - lywin) / 2;
          break;
      
        case (5):
          jxwin = (LXWIN - lxwin) / 2;
          jywin = (LYWIN - lywin) / 2;
          break;      
      
        case (6):
          jxwin = LXWIN - lxwin - (int) (*Pxmrg * xscl);
          jywin = (LYWIN - lywin) / 2;
          break;      
      
        case (7):
          jxwin = (int) (*Pxmrg * xscl);
          jywin = (int) (*Pymrg * yscl);
          break;
      
        case (8):
          jxwin = (LXWIN - lxwin) / 2;
          jywin = (int) (*Pymrg * yscl);
          break;      
      
        case (9):
          jxwin = LXWIN - lxwin - (int) (*Pxmrg * xscl);
          jywin = (int) (*Pymrg * yscl);
          break;      
      
        default:
          jxwin = (LXWIN - lxwin) / 2;
          jywin = (LYWIN - lywin) / 2;
          break;      
	}
      
	/* ... creation de l'enveloppe "frame" ......................*/

	Sfrmt =  xv_create (0, FRAME,
		FRAME_SHOW_LABEL, TRUE,
		XV_LABEL,	Zlwin,
		FRAME_NO_CONFIRM, TRUE,
                FRAME_ICON,      Sicn,
		WIN_X,		jxwin,
		WIN_Y,		jywin,
		WIN_WIDTH,	lxwin, 
		WIN_HEIGHT,	lywin,
		0);

	/* ... creation du panneau de controle ......................*/
 
	Spnlc = xv_create (Sfrmt,		PANEL,
	                        0);
	                        
	/* boutons .................................................*/
	
	Sbtnq = xv_create (Spnlc, PANEL_BUTTON,
	        PANEL_LABEL_STRING, "Quit",
	        PANEL_NOTIFY_PROC,  efftxt,
	        0);
	
	Sbtnp = xv_create (Spnlc, PANEL_BUTTON,
	        PANEL_LABEL_STRING, "Print",
	        PANEL_NOTIFY_PROC,  prttxt,
	        0);
	        
        window_fit_height (Spnlc);
	        
	/* ... creation de la fenetre texte .........................*/
 
	Stxtw = xv_create ( Sfrmt,		TEXTSW,
	                        0);
        xv_set (Stxtw,
		XV_FONT,		Sfnt0, 
		0);

        return (0);
}

void
efftxt (void)
{
       xv_destroy_safe (Sfrmt);
       return;
}

void
prttxt (void)
{
       DIMFSTRING (Zcmd, 256);
       DIMFSTRING (Zblc, 1);
       char zmsg [80];
       int kmsg, ktbl;
       int ichr1, ichr2, lmsg;
       extern system (const char *);
       extern void getmsg_ ();
       extern void  catstr ();
       extern char *fortoc ();
       extern void  inistr ();

       inistr (Zblc, " ", 1);
/* le nom de la commande est dans la table */
       ktbl = 0;
       kmsg = 99;
       zmsg [0] = '\0';
       getmsg_ (&ktbl, &kmsg, zmsg, 80);
       lenchr_ (zmsg, &ichr1, &ichr2, 80);
       ichr1 = ichr1 - 1;
       lmsg = ichr2 - ichr1;
       if ((zmsg [0] != '\0') && (zmsg [0] != ' ')) {
          inistr (Zcmd, fortoc (zmsg+ichr1, lmsg), 256);
       } else {
          inistr (Zcmd, "lpr", 256);
       }

/* on ajoute le nom du fichier */

       catstr (Zcmd, Zblc);
       catstr (Zcmd, Ztxtf);

/* on envoie */

       system (Zcmd);
       return;
}
E 1
