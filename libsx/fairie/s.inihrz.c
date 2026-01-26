h58841
s 00508/00000/00000
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
#define    LHRZM   JGRO * 6
#define    LHRZD   JGRO * 3
XImage *Pimal;
int   lxlpe;
FILE *Pfhrz;
int iseg, ihrz, ifdebh;
int kxdir, kydir;
int jxloc,  jyloc,  jyloc1,  jyloc2;
int jxlocw, jylocw, jylocw1, jylocw2;
int jxorg0;
float xloc, yloc;
DIMFSTRING (Zhrz, 4);
DIMFSTRING (Zfnt, 64);
Xv_font *Sfnt;

void
inihrz_ (int *Pibtn, char *Pzlhrz, int llhrz)
                   /* type de bouton                   */
                   /* fichier horizon                  */
          

/*
 * inihrz = initialisation du pointe d'horizon 
 * version %I% du %G%
 */
     
{
      extern Xv_font *xv_pf_open ();
      extern void trmrgt ();
      extern void inistr ();
      extern char *fortoc ();
      extern void trtsit ();
      extern void btnhrz (Event *PSevn);
      extern void suihrz (Event *PSevn);
      extern void prtmsg_ ();
      extern void inilpe_ (int *Pibtn);
      
      DIMFSTRING (Zfhrz, 64);
      int ktbl, kpos1, kpos2, imsg;
      static int ifhrz;

/* ..... loupe initialisee ? ................*/

      if (iflpe == 0) {
         inilpe_ (Pibtn);
      }

/* ..... flag et bouton ......................*/

      switch (*Pibtn) {
      case 1:             /* MS_LEFT */
        kactl  = FAI_USR0;
        kactdl = FAI_USR0;
        PFactl = btnhrz;
        PFactdl = suihrz;
        break;
      default:
      case 2:             /* MS_MIDDLE */
        kactm  = FAI_USR0;
        kactdm = FAI_USR0;
        PFactm = btnhrz;
        PFactdm = suihrz;
        break;
      case 3:             /* MS_RIGHT */
        kactr  = FAI_USR0;
        kactdr = FAI_USR0;
        PFactr = btnhrz;
        PFactdr = suihrz;
        break;
      }
      
/* ..... deja initialise ? .......................................*/

      if (ifhrz) {
         return;
      }
      ifhrz = 1;

/* .... fonte ................................................... */

      cpystr (Zfnt, "/usr/lib/fonts/fixedwidthfonts/cour.r.18");
      Sfnt = xv_pf_open (Zfnt);

/* .... ouverture du fichier ..................................... */

      inistr (Zfhrz, fortoc (Pzlhrz, llhrz), 64);
      trmrgt (Zfhrz);
      if ((Pfhrz = fopen (Zfhrz, "a")) == NULL) {
        ktbl = 0;
        kpos1 = 1;
        kpos2 = 2;
	imsg = 36;
        prtmsg_ (&ktbl, &kpos1, &imsg, &kpos2);
        printf ( " %s\n", Pzlhrz);
        return;
      }
      
      ihrz = 1;  

}
void btnhrz (Event *PSevn)
             

/* 
 * btnhrz : demarrage ou fin d'horizon
 */
{
      static int lhrz = 0;

      extern void rpncnv (Canvas Scnv, Xv_window Swin, Rectlist *PSare);
      extern void lpehrz (void);
      extern void inistr ();

/* .... affichage de la loupe ..................................*/

      if (event_is_down (PSevn)) {

          jxorg0 = jxorg;
          jxloc = (int) event_x (PSevn);
          jyloc = (int) event_y (PSevn);
          if (jxloc <= 0 || jxloc >= lxwin) return;
          if (jyloc <= 0 || jyloc >= lywin) return;
          jxlocw = jxloc * JGRO;
          jylocw = jyloc * JGRO;

          kxdir = 0;
          kydir = 0;
            
          ifdebh = 1;
          iseg = 0;

          inistr (Zhrz, NULL, 4);
          sprintf (Zhrz, "%d", ihrz);
          xv_text (Hwimg, jxlpe + LXLPE / 4, jylpe - 5,
               PIX_NOT (PIX_SRC & PIX_COLOR (1)), 
               Sfnt,
               Zhrz);

          xloc = (double) (jxloc * JGRO - jxorg0) / (double) xscl;
          yloc = (double)  (jyorg - jyloc * JGRO) / (double) yscl;

          lpehrz ();
          iflpeo = 1;

/* .... on cache la fleche .................................. */

          xv_set (Hwimg, WIN_CURSOR, Hcur, NULL);
      }
 
 /* .... desaffichage .......................................... */
 
      if (event_is_up (PSevn)) {
          if (ifdebh == 0) {
            iseg++;
            fprintf (Pfhrz, "%#8g, %#8g, %d\n", xloc, yloc, iseg); 
            fprintf (Pfhrz, "# ] .... - %s - \n", Zhrz);
            fflush  (Pfhrz);
            sprintf (Zhrz, "%d", ihrz);
          }

          xv_set (Hfimg, WIN_MOUSE_XY, jxloc, jyloc, NULL);
          xv_set (Hwimg, WIN_CURSOR, Hcur0, NULL);
          rpncnv (Hcimg, Hwimg, (Rectlist *) NULL);
          iflpeo = 0;
      }
}
void suihrz (Event *PSevn)
             

/* 
 * suihrz : suivi d'un horizon
 */
{
      int kclrf;
      int mxcur, mycur;
      int jxcurn, jycurn;
      static int nseg = 0;
      static int jxcur, jycur;

      extern void clrhrz (void);
      extern void lpehrz (void);
      extern void poshrz (int *Pkclr);
      extern void rpncnv (Canvas Scnv, Xv_window Swin, Rectlist *PSare);
 
      if (iflpeo == 0) {
         return;
      }

/* .... sortie de la souris ....... */
 
      if (event_id (PSevn) == LOC_WINEXIT) {
          xv_set (Hfimg, WIN_MOUSE_XY, lxwin / 2, lywin / 2, NULL);
      }

      if (event_id (PSevn) == LOC_DRAG) {
          if (jxorg != jxorg0) {
             int lxdec;
             lxdec = (jxorg0 - jxorg) / JGRO;
             jxloc  -= lxdec;
             jxcur  -= lxdec;
             jxlocw -= lxdec * JGRO;
             jxorg0 = jxorg;
          }
          jxcurn = (int) event_x (PSevn);
          jycurn = (int) event_y (PSevn);
          
          if (jxcurn < 10 || jxcurn > lxwin - 10
           || jycurn < 10 || jycurn > lywin - 10) {
               xv_set (Hfimg, WIN_MOUSE_XY, lxwin / 2, lywin / 2, NULL);
          }
          if (ifdebh == 1) {
              mxcur = jxcurn - jxloc;
              mycur = jycurn - jyloc;
          } else {
              mxcur = jxcurn - jxcur;
              mycur = jycurn - jycur;
          }
          jxcur = jxcurn;
          jycur = jycurn;

          if (mxcur <= lxwin / 4 && mycur <= lywin / 4) {

            if (kxdir == 0) {
              if (mxcur > 0)  kxdir = 1;
              if (mxcur < 0)  kxdir = -1;
            } else {
              switch (kydir) {
              default:
              case 0:
                 if (mycur > 1)  kydir = 1;
                 if (mycur < -1) kydir = -1;
                 break;
              case 1:
                 if (mycur < -1) {
                    kydir = -1;
                 } else {
                    if (mycur <= 1) kydir = 0;
                 }
                 break;
              case -1:
                 if (mycur > 1) {
                    kydir = 1;
                 } else {
                    if (mycur >= -1) kydir = 0;
                 }
                 break;
              }

/* .... le segment precedent est valide par le deplacement ..........*/

              if (ifdebh == 1) {
                  ifdebh = 0;
/* .... on ecrit dans le fichier ....................................*/

                  if (ihrz == 1) {
                    fprintf (Pfhrz, "# --------------------- {\n");
                  }
                  ihrz++;
                  fprintf (Pfhrz, "#   .... - %s - [\n", Zhrz); 
                  XSetForeground (Sdsp, Sgc, (unsigned long) 1);
              } else {
/* .... on colorie ..................................................*/

                  clrhrz ();

/* .... on ecrit dans le fichier ....................................*/

                  iseg++;
                  fprintf (Pfhrz, "%#8g, %#8g, %d\n", xloc, yloc, iseg);   
              }

/* .... on memorise la position .........................*/

              xloc = (double) (jxloc * JGRO - jxorg) / (double) xscl;
              yloc = (double) (jyorg - jyloc * JGRO) / (double) yscl; 
            }

/* .... on se positionne sur le segment suivant ..............*/

            poshrz (&kclrf); 
            if (jxloc <= 0 || jxloc >= lxwin ||
                jyloc <= 0 || jyloc >= lywin )  {
                if (ifdebh == 0) {
                   iseg++;
                   fprintf (Pfhrz, "%#8g, %#8g, %d\n", xloc, yloc, iseg); 
                   fprintf (Pfhrz, "# ] .... - %s - \n", Zhrz);
                   fflush  (Pfhrz); 
                   sprintf (Zhrz, "%d", ihrz);
                 }

                 xv_set (Hfimg, WIN_MOUSE_XY, jxloc, jyloc, NULL);
                 xv_set (Hwimg, WIN_CURSOR, Hcur0, NULL);
                 rpncnv (Hcimg, Hwimg, (Rectlist *) NULL);
                 iflpeo = 0;
                 return;
            }
            lpehrz (); 
         }
     }
}
void poshrz (int *Pkclr) 
           

      /* 
       * poshrz : positionne le marqueur d'horizon
       */
{
      int ipnt, ipnt0, ipnt1, ipnt2;
      int kclr0, kclr1, kclr2;
      static int lhrz, nseg;

/* .... initialisation .......................................... */ 

      jxloc  += kxdir;
      if (jxloc <= 0 || jxloc >= lxwin) {
        jxloc -= kxdir;
        return;
      }
      jylocw += kydir * JGRO / 2;
      if (jylocw <= 0 || jylocw >= lywin * JGRO) {
        jxloc  -= kxdir;
        jylocw -= kydir * JGRO / 2;
        return;
      }
      jxlocw += kxdir * JGRO;

      kclr0 = zm_get (PSimg, jxlocw, jylocw);
      kclr1 = kclr0;
      
/* .... calcul des bornes :  
 *       avec une preference pour la direction privilegiee, on va
 *       chercher le minimum relatif le plus proche et le plus 
 *       profond (ipnt0), et des remontees qui l'encadrent (ipnt1
 *       et ipnt2)
 */

      ipnt0 = 0;
      ipnt1 = -LHRZM;
      ipnt2 = LHRZM;
      if (kydir > 0) {
        for (ipnt = 1; ipnt <= LHRZM; ipnt ++) {
          if (ipnt2 == LHRZM) {
             kclr2 = zm_get (PSimg, jxlocw, jylocw + ipnt);
             if (kclr2 < kclr1) {
                kclr1 = kclr2;
                ipnt0 = ipnt;
             }
             if (kclr2 > kclr1)  ipnt2 = ipnt - 1;
          }
          if (ipnt1 == -LHRZM) {
             kclr2 = zm_get (PSimg, jxlocw, jylocw - ipnt);
             if (kclr2 < kclr1) {
                kclr1 = kclr2;
                ipnt0 = -ipnt;
             }
             if (kclr2 > kclr1)  ipnt1 = -ipnt + 1;
          }
        }
      } else {
        for (ipnt = 1; ipnt <= LHRZM; ipnt ++) {
          if (ipnt1 == -LHRZM) {
             kclr2 = zm_get (PSimg, jxlocw, jylocw - ipnt);
             if (kclr2 < kclr1) {
                kclr1 = kclr2;
                ipnt0 = -ipnt;
             }
             if (kclr2 > kclr1)  ipnt1 = -ipnt + 1;
          }
          if (ipnt2 == LHRZM) {
             kclr2 = zm_get (PSimg, jxlocw, jylocw + ipnt);
             if (kclr2 < kclr1) {
                kclr1 = kclr2;
                ipnt0 = ipnt;
             }
             if (kclr2 > kclr1)  ipnt2 = ipnt - 1;
          }
        }
      }

/* .... cas normal .................................. */
     
      if (ipnt1 > -LHRZM && ipnt2 < LHRZM) {
        nseg += 2;
        lhrz += ipnt2 - ipnt1 + 1;
      } else {

/* .... cas particuliers .................................. */
     
        if (nseg == 0) {
          if (ipnt1 == -LHRZM) ipnt1 = -LHRZD;
          if (ipnt2 == LHRZM)  ipnt2 =  LHRZD;
        } else {
          if (ipnt1 == -LHRZM && ipnt2 == LHRZM) {
            ipnt2 = lhrz / nseg;
            ipnt1 = - ipnt2;
          } else {
          if (ipnt1 == -LHRZM) {
            ipnt1 = ipnt0 - LHRZD;
          } else {
          if (ipnt2 == LHRZM)  {
            ipnt2 = ipnt0 + LHRZD;
          }}}
        }
      }
      
/* .... on identifie le plat de fond de vallee ........... */

      if (kclr1 < kclr0) {
        for (ipnt = ipnt0 + 1; ipnt < ipnt2 ; ipnt ++) {
             kclr2 = zm_get (PSimg, jxlocw, jylocw + ipnt);
             if (kclr2 > kclr1) {
                ipnt2 = ipnt;
                break;
             }
        }
        for (ipnt = ipnt0 - 1; ipnt > ipnt1 ; ipnt --) {
             kclr2 = zm_get (PSimg, jxlocw, jylocw + ipnt);
             if (kclr2 > kclr1) {
                ipnt1 = ipnt;
                break;
             }
        }

      }

/* .... positionne le marqueur au milieu du segment .........*/

        jylocw1  = jylocw + ipnt1;
        jylocw2  = jylocw + ipnt2;
        jylocw   = (jylocw1 + jylocw2) / 2;
        jyloc1  = jylocw1 / JGRO;
        jyloc2  = jylocw2 / JGRO;
        jyloc   = jylocw  / JGRO;
        *Pkclr  = kclr1;
            
        return;
}
void clrhrz (void) 
/* 
 * clrhrz : colorie l'horizon
 */
{

/* .... trace la ligne sur le point courant ...................*/

      zm_vct (PSimgw, jxloc, jyloc1, jxloc, jyloc2, 1);
      zm_set (PSimg, jxlocw, jylocw1, JGRO, jylocw2 - jylocw1 + 1, 1);
      XDrawLine (Sdsp, Hwin, Sgc, jxloc, jyloc1,
                                  jxloc, jyloc2);

      return;

}
void lpehrz (void) 

/* 
 * lpehrz : trace une boite contenant un zoom autour du point
 */
{

      static int jxret, jyret;

      int jxbox, jybox;
      int jxclp, jyclp, lxclp, lyclp;
      extern void clpbox (int jxwin, int jywin, int lxwin, int lywin, int jxbox, int jybox, int lxbox, int lybox, int *Pjxclp, int *Pjyclp, int *Plxclp, int *Plyclp);


/* .... calcul de l image a afficher dans la loupe ............ */

      jxbox = jxloc - LXRET / 2;       
      jybox = jyloc - LYRET / 2;
      clpbox (0, 0, lxwin, lywin,
              jxbox, jybox, LXRET, LYRET, 
              &jxclp, &jyclp, &lxclp, &lyclp);
         
/* .... si il y a du clipping on reinitialise la loupe .......*/

      if (lxclp != LXRET || lyclp != LYRET) {
          zm_set (PSlpe, 0, 0, LXLPE, LYLPE, 0);
      }

/* .... on charge l'image dans la loupe .......................*/

      zm_cpy (PSimg, jxclp * JGRO, jyclp * JGRO,
                     lxclp * JGRO, lyclp * JGRO, 
              PSlpe, (jxclp - jxbox) * JGRO,
                     (jyclp - jybox) * JGRO);

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

}
E 1
