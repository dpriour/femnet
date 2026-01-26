h63135
s 00352/00000/00000
d D 1.1 95/10/17 12:16:31 molagnon 1 0
c date and time created 95/10/17 12:16:31 by molagnon
e
u
U
f e 0
t
T
I 1
#include "../include/faixvg.h"
XImage *Pimal;
WORD jlpet [LXLPE * LYLPE / WRDBYT];


inilpe_ (int *Pibtn)
              

/*
 *       inilpe = initialisation de la loupe graphique 
 *       version %I% du %G%
 */

{
      DIMFSTRING (Zrep, 64);       /* repertoire         */
      DIMFSTRING (Zfnt, 64);       /* fonte              */
      int kmsg, ktbl;
      
      void trmrgt ();
      void inistr ();
      void cpystr ();
      void catstr ();
      extern void btnlpe (Event *PSevn);

/* ..... flag et bouton ......................*/

      switch (*Pibtn) {
      case 1:             /* MS_LEFT */
        kactl  = FAI_LPE;
        kactdl = FAI_LPE;
        PFactl = btnlpe;
        PFactdl = btnlpe;
        break;
      default:
      case 2:             /* MS_MIDDLE */
        kactm  = FAI_LPE;
        kactdm = FAI_LPE;
        PFactm = btnlpe;
        PFactdm = btnlpe;
        break;
      case 3:             /* MS_RIGHT */
        kactr  = FAI_LPE;
        kactdr = FAI_LPE;
        PFactr = btnlpe;
        PFactdr = btnlpe;
        break;
      }
      
/* ..... deja initialise ? ...................*/

      if (iflpe) {
         return;
      }
      iflpe = 1;
      jgro = JGRO;

/* .... grossissement .................................*/

      xscl = xscl * JGRO;
      yscl = yscl * JGRO;
      
/* .... position ......................................*/
      
       jxlpe = 0;
       jylpe = lywin - LYLPE;

/* .... rechargement des fontes .........................*/

       zm_dlf (PSfnt1);
       zm_dlf (PSfnt2);
       zm_dlf (PSfnt3);
       zm_dlf (PSfnt4);

      inistr (Zfnt, NULL, 64);
      inistr (Zrep, NULL, 64);
     
       ktbl = 0;
       kmsg = 96;
       getmsg_ (&ktbl, &kmsg, Zrep, 64);

       trmrgt (Zrep);
       if (strlen (Zrep) == 0) {
         cpystr (Zrep, ".");
       }
       cpystr (Zfnt, Zrep);
       catstr (Zfnt, "/oyo.5\0");
       PSfnt1 = zm_opf (Zfnt);
       if (PSfnt1 == NULL) PSfnt1 = zm_dff ();
       cpystr (Zfnt, Zrep);
       catstr (Zfnt, "/oyo.6\0");
       PSfnt2 = zm_opf (Zfnt);
       if (PSfnt2 == NULL) PSfnt2 = zm_dff ();
       cpystr (Zfnt, Zrep);
       catstr (Zfnt, "/oyo.7\0");
       PSfnt3 = zm_opf (Zfnt);
       if (PSfnt3 == NULL) PSfnt3 = zm_dff ();
       cpystr (Zfnt, Zrep);
       catstr (Zfnt, "/oyo.8\0");
       PSfnt4 = zm_opf (Zfnt);
       if (PSfnt4 == NULL) PSfnt4 = zm_dff ();
       
/* .... fonte par defaut .... ...........................*/

       PSfnt0 = PSfnt3;

/* .... repositionnement de l origine ...................*/

       jxorg *= JGRO;
       jyorg *= JGRO;     

/* .... repositionnement du curseur .....................*/

       jxpnt0 *= JGRO;
       jypnt0 *= JGRO;
             
/* .... definition de l'image de la loupe ...............*/

       PSlpe = zm_bld (LXLPE, LYLPE, jprf, (BYTE *) jlpet);

       if (jprf == jprfe) {
          Pimal = XCreateImage (Sdsp, DefaultVisual (Sdsp, Hscr), jprf,
                                ZPixmap, 0,
                                (BYTE *) jlpet,
                                LXLPE, LYLPE, BitmapPad (Sdsp), 0);
      } else {
          Pimal = XCreateImage (Sdsp, DefaultVisual (Sdsp, Hscr), jprf,
                                XYBitmap, 0,
                                (BYTE *) jlpet,
                                LXLPE, LYLPE, BitmapPad (Sdsp), 0);
          Pimal->byte_order = MSBFirst;
          Pimal->bitmap_bit_order = MSBFirst;
      }

/* .... initialisation de la grande image  .....................*/

       PSimg = zm_cre (JGRO * lxwin, JGRO * lywin, jprf);
       xpdpxr (PSimgw, PSimg, jprf, 0);

/* .... preparation du curseur invisible ...................... */

       Icur = (Server_image) xv_create (XV_NULL, SERVER_IMAGE,
                                XV_WIDTH, 16,
                                XV_HEIGHT, 16,
                                SERVER_IMAGE_BITS, jcurt,
                                NULL);
       Hcur0 = (Xv_cursor) xv_create (XV_NULL, CURSOR, 
                                CURSOR_SRC_CHAR, OLC_BASIC_PTR,
                                CURSOR_MASK_CHAR, OLC_BASIC_MASK_PTR,
                                NULL);
       Hcur = (Xv_cursor) xv_create (XV_NULL, CURSOR, 
                                CURSOR_IMAGE, Icur,
                                NULL);
}
void btnlpe (Event *PSevn)
             

/* 
 * btnlpe : boite contenant un fragment de la grande image
 *
 */
{
      static int jxloc, jyloc;
      extern void lpepnt (int jxloc, int jyloc);
      extern void rpncnv (Canvas Scnv, Xv_window Swin, Rectlist *PSare);

/* .... affichage de la loupe (avec test si trop pres du bord) ..*/

      if (event_id (PSevn) == LOC_DRAG) {

          jxloc = (int) event_x (PSevn);
          jyloc = (int) event_y (PSevn);

/* .... test si trop pres du bord ............... */
 
          if (jxloc <= 0 || jxloc >= lxwin
           || jyloc <= 0 || jyloc >= lywin) {
              rpncnv (Hcimg, Hwimg, (Rectlist *) NULL);
              iflpeo = 0;
              return;
          }

          lpepnt (jxloc, jyloc);
          iflpeo = 1;
      }
 
      if (event_is_down (PSevn)) {

          jxloc = (int) event_x (PSevn);
          jyloc = (int) event_y (PSevn);

          lpepnt (jxloc, jyloc);
          iflpeo = 1;

/* .... on cache la fleche .................................. */

          xv_set (Hwimg, WIN_CURSOR, Hcur, NULL);

      }
 
 /* .... desaffichage .......................................... */
 
      if (event_is_up (PSevn)) {
          xv_set (Hfimg, WIN_MOUSE_XY, jxloc, jyloc, NULL);
          xv_set (Hwimg, WIN_CURSOR, Hcur0, NULL);
          rpncnv (Hcimg, Hwimg, (Rectlist *) NULL);
          iflpeo = 0;
      }
}
void
lpepnt (int jxloc, int jyloc) 
                 

/* 
 * lpepnt : trace une boite contenant un zoom autour du point
 *
 */
{

      static int jxret, jyret, lxret, lyret;
      
      int jxbox, jybox;
      int jxclp, jyclp, lxclp, lyclp;
      void extern clpbox (int jxwin, int jywin, int lxwin, int lywin, int jxbox, int jybox, int lxbox, int lybox, int *Pjxclp, int *Pjyclp, int *Plxclp, int *Plyclp);

/* .... calcul de l image a afficher dans la loupe ............ */
 
      jxbox = jxloc - LXRET / 2;       
      jybox = jyloc - LYRET / 2;
      clpbox (0, 0, lxwin, lywin,
              jxbox, jybox, LXRET, LYRET, 
              &jxclp, &jyclp, &lxclp, &lyclp);

/* .... si il y a du clipping on reinitialise la loupe ........ */

      if (lxclp != LXRET || lyclp != LYRET) {
          zm_set (PSlpe, 0, 0, LXLPE, LYLPE, 0);
      }

/* .... on charge l'image dans la loupe ....................... */

      zm_cpy (PSimg, jxclp * JGRO, jyclp * JGRO,
                     lxclp * JGRO, lyclp * JGRO, 
              PSlpe, 0, 0);

      zm_vct (PSlpe,         0,     0, LXLPE - 1,         0, 1);
      zm_vct (PSlpe, LXLPE - 1,     0, LXLPE - 1, LYLPE - 1, 1);

/* .... affichage de la croix dans la loupe .................... */

      zm_vct (PSlpe, LXLPE / 2, (LYLPE - LYRET) / 2,
                     LXLPE / 2, (LYLPE + LYRET) / 2,
                     1);
      zm_vct (PSlpe, (LXLPE - LXRET) / 2, LYLPE / 2,
                     (LXLPE + LXRET) / 2, LYLPE / 2,
                     1);

/* .... affichage de l'image dans la loupe .................... */

      XPutImage (Sdsp, Hwin, Sgc, Pimal,     0,     0,
                                         jxlpe, jylpe,
                                         LXLPE, LYLPE);

/* .... reticule ............................................... */
 
/* .... on efface l'ancien .......... */

      if (iflpeo == 1) {
          XPutImage (Sdsp, Hwin, Sgc, Pima, jxret, jyret,
                                            jxret, jyret,
                                            lxret, lyret);
      }

/* .... trace du reticule dans l image ........................ */
 
      jxret = jxloc - LXRET / 2;
      jyret = jyloc - LYRET / 2;
      xv_vector (Hwimg, jxret,             jyret,
                        jxret + LXRET - 1, jyret, 
                        PIX_SRC | PIX_COLOR (0), 1);
      xv_vector (Hwimg, jxret + LXRET - 1, jyret, 
                        jxret + LXRET - 1, jyret + LYRET - 1, 
                        PIX_SRC | PIX_COLOR (0), 1);
      xv_vector (Hwimg, jxret + LXRET - 1, jyret + LYRET - 1,
                        jxret,             jyret + LYRET - 1, 
                        PIX_SRC | PIX_COLOR (0), 1);
      xv_vector (Hwimg, jxret,             jyret + LYRET - 1,
                        jxret,             jyret, 
                        PIX_SRC | PIX_COLOR (0), 1);
          
/* .... croix du reticule .................*/
           
      xv_vector (Hwimg, jxloc, jyloc - 5,
                        jxloc, jyloc + 5,
                        PIX_SRC | PIX_COLOR (0), 1);
      xv_vector (Hwimg, jxloc - 5, jyloc,
                        jxloc + 5, jyloc,
                        PIX_SRC | PIX_COLOR (0), 1);
      jxret = jxclp;
      jyret = jyclp;
      lxret = lxclp;
      lyret = lyclp;

}
void clpbox (int jxwin, int jywin, int lxwin, int lywin, int jxbox, int jybox, int lxbox, int lybox, int *Pjxclp, int *Pjyclp, int *Plxclp, int *Plyclp)
             
                               
                               
                                       

      /* 
       * clpbox : clippe une boite aux limites d'une fenetre
       */
{
    register int jxbox0 = jxbox;
    register int jybox0 = jybox;
    register int jxbox1 = jxbox + lxbox;
    register int jybox1 = jybox + lybox;

    if (jxbox1 >= jxwin + lxwin) {
       jxbox1 = jxwin + lxwin - 1;
       if (jxbox0 >= jxwin + lxwin) {
         jxbox0 = jxwin + lxwin - 1;
       }
    }

    if (jxbox0 < jxwin) {
       jxbox0 = jxwin;
       if (jxbox1 < jxwin) {
          jxbox1 = jxwin;
       }
    }

    if (jybox1 >= jywin + lywin) {
       jybox1 = jywin + lywin - 1;
       if (jybox0 >= jywin + lywin) {
         jybox0 = jywin + lywin - 1;
       }
    }

    if (jybox0 < jywin) {
       jybox0 = jywin;
       if (jybox1 < jywin) {
          jybox1 = jywin;
       }
    }

    *Pjxclp = jxbox0;
    *Pjyclp = jybox0;
    *Plxclp = jxbox1 - jxbox0;
    *Plyclp = jybox1 - jybox0;

}
E 1
