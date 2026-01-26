h48410
s 00188/00000/00000
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
#include <thread.h>

#define   NCHXM   16
#define   LCHXM   16
DIMFSTRING (Zchxt [NCHXM], LCHXM);
DIMFSTRING (Ztit, LCHXM);
Menu Hmnu;
Menu_item Hchx;
thread_t Twin;
int *Pichx, nchx;
int ifmnu;
                          
void inimnu_ (int *Pibtn, char *Pzchxt, int *Pnchx, int lzchx)
                   /* bouton declenchant                   */
                   /* textes des choix                     */
                   /* nombre de choix                      */
           

/*
 *      inimnu = initialisation du menu
 *      version %I% du %G%
 */

{
      extern void chxmnu (Menu Hmnuw, Menu_item Hchxw);
      extern void btnmnu (Event *PSevn);
      extern void trmrgt ();
      extern void inistr ();
      extern void cpystr ();
      extern void getmsg_ ();
      extern char *fortoc ();
      int ichx;
      char *Pzchx;
      int kmsg, ktbl;

/* ..... flag et bouton ......................*/

      switch (*Pibtn) {
      case 1:             /* MS_LEFT */
        kactl = FAI_MNU;
        kactdl = FAI_NONE;
        PFactl = btnmnu;
        break;
      case 2:             /* MS_MIDDLE */
        kactm = FAI_MNU;
        kactdm = FAI_NONE;
        PFactm = btnmnu;
        break;
      default:
      case 3:             /* MS_RIGHT */
        kactr = FAI_MNU;
        kactdr = FAI_NONE;
        PFactr = btnmnu;
        break;
      }

/* ..... deja initialise ? ...................*/

      if (ifmnu != 0) {
         xv_destroy_safe (Hmnu);
      }
      ifmnu = 1;

/* ..... on le cree vide .....................*/

      inistr (Ztit, NULL, LCHXM);
      ktbl = 1;
      kmsg = 1;
      getmsg_ (&ktbl, &kmsg, Ztit, LCHXM);
      trmrgt (Ztit);
      if (strlen (Ztit) == 0) {
        inistr (Ztit, "MENU", LCHXM);
      }

      Hmnu = (Menu) xv_create (XV_NULL, MENU,
                               MENU_TITLE_ITEM,  Ztit,
                               MENU_NOTIFY_PROC, menu_return_item,
                               MENU_DONE_PROC,   chxmnu,
                               NULL);

/* ..... chargement des choix ................*/

      for (ichx = 0 ; ichx < NCHXM ; ichx ++) {
          inistr (Zchxt [ichx], NULL, LCHXM);
      }
      Pzchx = Pzchxt;
      nchx = (NCHXM < *Pnchx) ? NCHXM : *Pnchx;
      for (ichx = 0 ; ichx < nchx ; ichx ++) {
          cpystr (Zchxt [ichx], fortoc (Pzchx, lzchx), LCHXM);
          Pzchx += lzchx;
          Hchx = (Menu_item) xv_create (XV_NULL,          MENUITEM,
                                        MENU_STRING,      Zchxt [ichx],
                                        MENU_RELEASE,
                                        NULL);
          xv_set (Hmnu, MENU_APPEND_ITEM, Hchx, NULL);
      }

}
void btnmnu (Event *PSevn)
             

      /* 
       * btnmnu : affichage ou fin du menu
       */
{

      if (ifaff != 1) {
          return;
      }
      if (event_is_down (PSevn)) {
          menu_show (Hmnu, Hwimg, PSevn, NULL);
      }
}
void chxmnu (Menu Hmnuw, Menu_item Hchxw)
           
                

      /* 
       * chxmnu : traitement du choix retenu
       */
{
      char *Pzret;
      int ichx;

      if (Hchxw == (Menu_item) 0) return;
      Pzret = (char *) xv_get (Hchxw, MENU_STRING);
      if (*Pzret == '\0') {
          *Pichx = 0;
      } else {      
          for (ichx = 0 ; ichx < nchx ; ichx ++) {
            if (strcmp (Pzret, Zchxt [ichx]) == 0) {
               *Pichx = ichx + 1;
               break;
            }
          }
      }

 /* .... cede la main  ........................ */
 
      (void) thr_setprio (thr_self (), MINPRIO);
      (void) thr_yield ();
}
void attmnu_ (int *Pichxr)
                    /* choix retenu */
     /*
      * attmnu = arrete le programme jusqu'a menu
      */
{
        extern void trtevn (Canvas Scnv, Event *PSevn);
        static int ifdeb = 0;

        Pichx = Pichxr;

        if (ifmnu == 0) {
           return;
        }

/* .... lancement eventuel du multithread ............... */

        if (ifaff == 0) {
          affgra_ ();
        } else {
          if (ifaff > 1)  return;
        }

/* .... on autorise les evenements ............................*/

        if (ifdeb == 0) {
          ifdeb = 1;
          xv_set (Hwimg, WIN_CONSUME_EVENTS,
                             WIN_UP_EVENTS,
                             LOC_DRAG,
                             LOC_WINEXIT,
                             WIN_LEFT_KEYS,
                             WIN_ASCII_EVENTS, 
                             0,
                         WIN_EVENT_PROC, trtevn, 
                         0);
        }

/* .... on passe la main a la fenetre ..............*/

        (void) thr_setprio (thr_self (), (MAXPRIO / 2));
        (void) thr_setprio (Twin, MAXPRIO);
        (void) thr_yield ();
        (void) thr_setprio (thr_self (), MAXPRIO);
}
E 1
