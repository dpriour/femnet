h28759
s 00487/00000/00000
d D 1.1 95/10/17 12:16:30 molagnon 1 0
c date and time created 95/10/17 12:16:30 by molagnon
e
u
U
f e 0
t
T
I 1
#include "../include/faixvg.h"
#include <math.h>
#define  FAI_LEFT    1
#define  FAI_MIDDLE  2
#define  FAI_RIGHT   4
#define  CTRL_D      4
Screen *Sscr;
Colormap Smapd;


void
inigra_ (char *Pzlwin, char *Pzlicn, int *Pkmrg, float *Pxmrg, float *Pymrg, float *Pxwin, float *Pywin, int llwin, int llicn)
                         /* nom de la fenetre                      */
                         /* nom de l icone                         */
                         /* code marge                             */
                         /* marge horizontale                      */
                         /* marge verticale                        */
                         /* taille en x de la fenetre              */
                         /* taille en y de la fenetre              */
              
              

/*
 *      inigra = initialisation du graphique 
 *      version %I% du %G%
 */
     
{
      int ktbl, kmsg;
      extern void trmrgt ();
      extern void trmlft ();
      extern void inistr ();
      extern void inicms (void);
      extern void cpystr ();
      extern void catstr ();
      extern void rpncnv (Canvas Scnv, Xv_window Swin, Rectlist *PSare);
      extern void loogra (void);
      extern void rpngra (void);

      int jxwin, jywin;
      float dxpxl, dypxl, dzpxl;
      DIMFSTRING (Zlwin, 64);
      DIMFSTRING (Zlicn, 64);
      DIMFSTRING (Zfnt, 64);       /* fonte              */
      DIMFSTRING (Zrep, 64);       /* fonte              */
      int iclr;
      int lximg;

      Rect Srec;
        
/* .... initialisation des chaines .................*/

     inistr (Zlwin, fortoc (Pzlwin, llwin), 64);
     inistr (Zlicn, fortoc (Pzlicn, llicn), 64);
     inistr (Zfnt, NULL, 64);
     inistr (Zrep, NULL, 64);

     trmrgt (Zlwin);
     trmrgt (Zlicn);
     inicms (); 

/* .... echelle et grossissement .....................*/

      xscl = ((float) LXWIN) / XWIN;     
      yscl = ((float) LYWIN) / YWIN; 
      jgro = 1;
      
/* .... nom de la fenetre 
 *    =  nom passe par l'utilisateur (sans blanc de gauche)
 *     + un tiret
 *     + le nom de l'icone
 */
 
      catstr (Zlwin, " - ");
      catstr (Zlwin, Zlicn); 
       
/* .... taille de la fenetre ........................... */

      lxwin = MRGG + ((int) (*Pxwin * xscl)) + MRGD;
      lxwin = 2 * (lxwin / 2);
      lywin = MRGB + ((int) (*Pywin * yscl)) + MRGH;
      lywin = 2 * (lywin / 2);

/* .... position de la fenetre ......................... */

      switch (*Pkmrg % 10) {
      
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
      
      lxwin = (int) (*Pxwin * xscl);
      lywin = (int) (*Pywin * yscl);
      
      xscl = xscl * jgro;
      yscl = yscl * jgro;
      
/* .... chargement des fontes .........................*/

       ktbl = 0;
       kmsg = 96;
       getmsg_ (&ktbl, &kmsg, Zrep, 64);
       trmrgt (Zrep);
       trmlft (Zrep);
       cpystr (Zfnt, Zrep);
       catstr (Zfnt, "/oyo.1");
       PSfnt1 = zm_opf (Zfnt);
       if (PSfnt1 == NULL) PSfnt1 = zm_dff ();
       cpystr (Zfnt, Zrep);
       catstr (Zfnt, "/oyo.2");
       PSfnt2 = zm_opf (Zfnt);
       if (PSfnt2 == NULL) PSfnt2 = zm_dff ();
       cpystr (Zfnt, Zrep);
       catstr (Zfnt, "/oyo.3");
       PSfnt3 = zm_opf (Zfnt);
       if (PSfnt3 == NULL) PSfnt3 = zm_dff ();
       PSfntc = zm_opf (Zfnt);
       if (PSfntc == NULL) PSfntc = zm_dff ();
       cpystr (Zfnt, Zrep);
       catstr (Zfnt, "/oyo.4");
       PSfnt4 = zm_opf (Zfnt);
       if (PSfnt4 == NULL) PSfnt4 = zm_dff ();

/* .... fonte par defaut .... ........................*/

       PSfnt0 = PSfnt3;

/* .... largeur trait ................................*/

      pxlsiz_ (&dxpxl, &dypxl);
      dzpxl = sqrt ((dxpxl * dxpxl + dypxl * dypxl) * 0.5);
      
      jwdt1 = (int) (0.1 / dzpxl + 0.5);
      if (jwdt1 < 1) jwdt1 = 1;
      jwdt2 = (int) (0.3 / dzpxl + 0.5);
      if (jwdt2 < 1) jwdt2 = 1;
      jwdt3 = (int) (0.6 / dzpxl + 0.5);
      if (jwdt3 < 1) jwdt3 = 1;
      jwdt4 = (int) (1.2 / dzpxl + 0.5);
      if (jwdt4 < 1) jwdt4 = 1;
      
      jwdt0 = jwdt2;

      
/* .... alignement du texte ............................*/

      kalh0 = 0;
      kalv0 = 0;

/* .... origine ........................................*/

      jxorg = 0;
      jyorg = lywin;     

/* .... position actuelle du curseur ...................*/

      jxpnt0 = jxorg;
      jypnt0 = jyorg;

/* .... chargement de l icone ............................*/

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

/* .... creation de la fenetre de dessin ................*/

      Hfimg =  xv_create (XV_NULL, FRAME,
               XV_LABEL,         Zlwin,
               XV_NAME,         "Fairie",
               FRAME_ICON,       Sicn,
               FRAME_NO_CONFIRM, TRUE,
               WIN_X,           jxwin,
               WIN_Y,           jywin,
               WIN_HEIGHT,      lywin,
               WIN_WIDTH,       lxwin, 
               WIN_SHOW,        FALSE,
               0);

/* .... profondeur (nombre de plans) ...................*/

      jprfe = (int) xv_get (Hfimg, WIN_DEPTH);
      switch (jprf) {
      default:
      case 0:
        jprf = jprfe;
        break;
      case 1:
        break;
      }

/* .... creation du canevas de dessin ................*/

      if (jprf == 1) {
        if (jprfe != 1) {
           xv_destroy_safe (Hfimg);
           Hfimg =  xv_create (XV_NULL, FRAME,
                    XV_LABEL,         Zlwin,
                    XV_NAME,         "Fairie",
                    FRAME_ICON,       Sicn,
                    FRAME_NO_CONFIRM, TRUE,
                    WIN_X,           jxwin,
                    WIN_Y,           jywin,
                    WIN_HEIGHT,      lywin,
                    WIN_DEPTH,        jprf,
                    WIN_WIDTH,       lxwin, 
                    WIN_SHOW,        FALSE,
                    0);
        }
        Hcimg = xv_create (Hfimg, CANVAS,
                               CANVAS_AUTO_SHRINK,   FALSE,
                               CANVAS_REPAINT_PROC, rpncnv,
                               WIN_DYNAMIC_VISUAL,   FALSE,
                               0);

        Hwimg = canvas_paint_window (Hcimg);
        Sdsp  = (Display *) xv_get (Hwimg, XV_DISPLAY);
        Hwin  = (Window) xv_get (Hwimg, XV_XID);
        Sscr  = XDefaultScreenOfDisplay (Sdsp);

        ifcms = 0;      
        nclr = 2;
        iclrd = 0;
        iclrb = 0;
       
/* .... creation de l'image memoire ou l'on va dessiner ......*/
       
        PSimg  = zm_cre (lxwin, lywin, jprf);
        PSimgw = PSimg;             
        zm_set (PSimg, 0, 0, lxwin, lywin, 0);

      } else {

/*
 * .... creation du canevas
 */
          
        Hcimg = xv_create (Hfimg, CANVAS,
                           CANVAS_AUTO_SHRINK,   FALSE,
                           CANVAS_REPAINT_PROC,  rpncnv,
                           WIN_DYNAMIC_VISUAL,   TRUE,
                           CANVAS_X_PAINT_WINDOW, TRUE,
                           0);
        nclr  = NCLRM;
        iclrb = FCL_RBW1 + JPXLD;
        if (iclrd == 0)  iclrd = iclrb;
        Hwimg = canvas_paint_window (Hcimg);
        Sdsp  = (Display *) xv_get (Hwimg, XV_DISPLAY);
        Hwin  = (Window) xv_get (Hwimg, XV_XID);
        Sscr  = XDefaultScreenOfDisplay (Sdsp);
        Smapd = DefaultColormapOfScreen (Sscr);
        XSetWindowColormap (Sdsp, Hwin, Smapd);
        ifcms = 1;

/* .... creation de l'image memoire ou l'on va dessiner ......*/
       
        PSimg = zm_cre (lxwin, lywin, jprfe);
        PSimgw = PSimg;             
        zm_set (PSimg, 0, 0, lxwin, lywin, iclrb);

      }

      Sgc = XCreateGC (Sdsp, Hwin, 0, NULL);
      Hscr = DefaultScreen (Sdsp);
      if (jprf == jprfe) {
         lximg = PSimgw->x;
         Pima = XCreateImage (Sdsp, DefaultVisual (Sdsp, Hscr),
                              jprf,
                              ZPixmap, 0,
                              (BYTE *) PSimgw->d,
                              lximg, lywin, BitmapPad (Sdsp), 0);
      } else {
         lximg = PSimgw->x;
         Pima = XCreateImage (Sdsp, DefaultVisual (Sdsp, Hscr),
                              jprf,
                              XYBitmap, 0,
                              (BYTE *) PSimgw->d,
                              lximg, lywin, BitmapPad (Sdsp), 0);
         Pima->byte_order = MSBFirst;
         Pima->bitmap_bit_order = MSBFirst;
         XSetForeground (Sdsp, Sgc, (WORD) 1);
         XSetBackground (Sdsp, Sgc, (WORD) 0);
      }

/* .... couleur par defaut = noir ................................ */   

      kclr0 = iclrd + nclr - 1;
      
/* .... on initialise le flag d etat a 0
 *                                     1 = creation en cours
 *                                     2 = creation terminee
 */
                                       
      ifaff = 0;
      PFactf = loogra;
      PFactp = rpngra;
      xv_set (Hfimg, WIN_SHOW, TRUE, 0);

}
void
trtevn (Canvas Scnv, Event *PSevn)
            
             
 
/*
 *       trtevn = traitement des evenements
 *       auteur ph morvan rdi+
 */

{
      static int ibtno;

/* .... souris ................................... */

      if (event_id (PSevn) == LOC_DRAG || event_id (PSevn) == LOC_WINEXIT) {
         if ((ibtno & FAI_LEFT) == FAI_LEFT     && kactdl != FAI_NONE) {
            (*PFactdl) (PSevn);
         }
         if ((ibtno & FAI_MIDDLE) == FAI_MIDDLE && kactdm != FAI_NONE) {
            (*PFactdm) (PSevn);
         }
         if ((ibtno & FAI_RIGHT) == FAI_RIGHT   && kactdr != FAI_NONE) {
            (*PFactdr) (PSevn);
         }

      }  else {      

         if (event_id (PSevn) == MS_LEFT   && kactl != FAI_NONE) {
            if (event_is_down (PSevn)) ibtno |= FAI_LEFT;
            (*PFactl) (PSevn);
            if (event_is_up (PSevn))   ibtno &= ~(FAI_LEFT);
         }
         if (event_id (PSevn) == MS_MIDDLE && kactm != FAI_NONE) {
            if (event_is_down (PSevn)) ibtno |= FAI_MIDDLE;
            (*PFactm) (PSevn);
            if (event_is_up (PSevn))   ibtno &= ~(FAI_MIDDLE);
         }
         if (event_id (PSevn) == MS_RIGHT  && kactr != FAI_NONE) {
            if (event_is_down (PSevn)) ibtno |= FAI_RIGHT;
            (*PFactr) (PSevn);
            if (event_is_up (PSevn))   ibtno &= ~(FAI_RIGHT);
         }
      }

/* .... fonctions ................ */
 
      if (event_is_key_left (PSevn) && event_is_up (PSevn))   {
        if (event_id (PSevn) == KEY_LEFT (7)) {
          xv_set (Hfimg, FRAME_CLOSED, TRUE, 0);
        }
        if (event_id (PSevn) == KEY_LEFT (5)) {
          xv_set (Hfimg, WIN_SHOW, TRUE, 0);
        }
        if (event_id (PSevn) == KEY_LEFT (1)) {
          if (Hfedtc != XV_NULL) {
             xv_destroy_safe (Hfedtc);
          }
          if (Hfedtg != XV_NULL) {
             xv_destroy_safe (Hfedtg);
          }
          xv_destroy_safe (Hfimg);
          ifaff = 4;
        }
      }
/* .... clavier ................ */
 
/* .... controle d ................ */
 
      if (event_id (PSevn) == CTRL_D) {
          if (Hfedtc != XV_NULL) {
             xv_destroy_safe (Hfedtc);
          }
          if (Hfedtg != XV_NULL) {
             xv_destroy_safe (Hfedtg);
          }
          xv_destroy_safe (Hfimg);
          ifaff = 4;
      }
      return;
}

void
rpncnv (Canvas Scnv, Xv_window Swin, Rectlist *PSare)
               
               
                 
/*
 * rpncnv = repaint le canevas
 */
{
      (void) (*PFactp) ();
}

void
rpngra (void)
       
/* .... recopie de la partie visible de l image ................. */
{
        XPutImage (Sdsp, Hwin, Sgc, Pima, 0,0,0,0,lxwin,lywin);
}


Notify_value
tuedes (Notify_client client, Destroy_status status)
                     
                      

/*
 *    arret sur raison externe
 */
{
/*
        if (Hfedtc != XV_NULL) {
           xv_destroy_safe (Hfedtc);
        }
        if (Hfedtg != XV_NULL) {
           xv_destroy_safe (Hfedtg);
        }
*/
        ifaff = 4;
        return (notify_next_destroy_func (client, status));
}
E 1
