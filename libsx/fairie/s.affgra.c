h03258
s 00296/00000/00000
d D 1.1 95/10/17 12:16:19 molagnon 1 0
c date and time created 95/10/17 12:16:19 by molagnon
e
u
U
f e 0
t
T
I 1
#include "../include/faixvg.h"
#include <thread.h>

Notify_client Saff;
thread_t Twin;

void
affgra_ (void)
/*
 * affgra = affiche le graphique en cours d elaboration
 * version %I% du %G%
 * auteur  phm R/D/I+ 

 --> affgra --> return ---> fingra --> finsrv |
        |                                 |
        V                                 V
     loothr ----------------------------------------------->

      */
{
  extern void loothr (void);
  extern void finsrv (void);
  extern void rpnthr (void);
  extern void rdcpxr ();
  extern Notify_func trtaff (Notify_client Sclt, Notify_event jevn, Notify_arg Sarg, Notify_event_type ktrt);
  

  if (ifaff == 0) {

/* .... construction eventuelle de l'image .....................*/

     if (jgro > 1) {
        rdcpxr (PSimg, PSimgw, jprf, iclrb);
     }

/* .... actions de fin et de peinture .................*/

     PFactf = finsrv;
     PFactp = rpnthr;
     ifaff = 1;

/* .... on initialise le multi thread  ................ */

     Saff = (Notify_client) 10;
     notify_set_event_func (Saff,
                            (void *) trtaff,
                            NOTIFY_SAFE);

     (void) thr_create (NULL, 0, (void *) loothr, NULL, THR_NEW_LWP,
                        &Twin);

/* .... on laisse la fenetre se creer ........................... */
  
     (void) thr_yield ();
     (void) thr_setprio (thr_self (), MAXPRIO);
     (void) thr_setprio (Twin, MINPRIO);

  } else {

/* .... on demande de recopier l'image sur l'ecran ............... */
  
     notify_post_event (Saff,  (Notify_event) 1,
                               NOTIFY_SAFE);
/* .... on repasse la main a la fenetre ........ */

     (void) thr_yield ();
  }

  return;
           
}

void loothr (void)
     /* ====================================================
      * loothr = traitement de la fenetre reelle
      *====================================================*/
{
     extern void timstp (void);

/* .... boucle ......................................*/

     signal (SIGALRM, (void *) timstp);
     xv_main_loop (Hfimg);
     
     (void) thr_exit (NULL);
     
}
void rpnthr (void)
{
/* .... recopie de la partie visible de l image ................. */

     XPutImage (Sdsp, Hwin, Sgc, Pima, 0,0,0,0,lxwin,lywin);
       
/* .... gestion du multi taches ............ */

     if (ifaff == 1) {
        (void) thr_yield ();
     }
}

void finsrv (void)

/*
 * finsrv : fin du thread de calcul, passe la main.
 */
{
     extern void trtevn (Canvas Scnv, Event *PSevn);
     extern Notify_value tuedes (Notify_client client, Destroy_status status);

     XPutImage (Sdsp, Hwin, Sgc, Pima, 0,0,0,0,lxwin,lywin);

     xv_set (Hwimg, WIN_CONSUME_EVENTS,
                 WIN_UP_EVENTS,
                 LOC_DRAG,
                 LOC_WINEXIT,
                 WIN_LEFT_KEYS,
                 WIN_ASCII_EVENTS, 
                 0,
                 WIN_EVENT_PROC, trtevn, 
                 0);

     notify_interpose_destroy_func (Hfimg, tuedes);

     ifaff = 2;
     (void) thr_yield ();
     (void) thr_exit (NULL);
}
void rfrgra_ (void)
{
  extern void affgra_ (void);
  
  affgra_ ();
  
}
Notify_func trtaff (Notify_client Sclt, Notify_event jevn, Notify_arg Sarg, Notify_event_type ktrt)
                   
                   
                   
                       
     /*
      * trtaff = affichage de l ecran courant
      */
{
  extern void rdcpxr ();

/* .... construction eventuelle de l'image .....................*/

     if (jgro > 1) {
        rdcpxr (PSimg, PSimgw, jprf, iclrb);
     }

/* .... affichage de l'image ................... */

     XPutImage (Sdsp, Hwin, Sgc, Pima, 0,0,0,0,lxwin,lywin);
       
/* .... gestion du multi taches ............ */

     if (ifaff == 1) {
        (void) thr_yield ();
     }

     return (NOTIFY_DONE);
} 
void arrgra_ (int *Pibtn)
                   /* bouton declenchant la reprise */

/*
 * arrgra = arrete le programme jusqu'a une action sur le bouton
 */
{
        extern void trtevn (Canvas Scnv, Event *PSevn);
        extern void rdcpxr ();
        extern void btncnt (Event *PSevn);
        extern void affgra_ (void);
        void (*PFact);
        int   kact, kactd;
  
        if (ifaff > 1) {
           return;
        }

/* ..... flag et bouton ......................*/

        switch (*Pibtn) {
        default:
        case 1:
          kact   = kactl;
          kactd  = kactdl;
          PFact  = PFactl;
          kactl  = FAI_CNT;
          kactdl = FAI_NONE;
          PFactl = btncnt;
          break;
        case 2:
          kact   = kactm;
          kactd  = kactdm;
          PFact  = PFactm;
          kactm  = FAI_CNT;
          kactdm = FAI_NONE;
          PFactm = btncnt;
          break;
        case 3:
          kact   = kactr;
          kactd  = kactdr;
          PFact  = PFactr;
          kactr  = FAI_CNT;
          kactdr = FAI_NONE;
          PFactr = btncnt;
          break;
        }

/* .... affichage du dessin en l'etat ................*/

        if (ifaff == 0) {
           affgra_ ();
        } else {

/* .... construction eventuelle de l'image .....................*/

           if (jgro > 1) {
              rdcpxr (PSimg, PSimgw, jprf, iclrb);
           }

/* .... affichage ..............................................*/

           XPutImage (Sdsp, Hwin, Sgc, Pima, 0,0,0,0,lxwin,lywin);
        }

/* .... on autorise les evenements (souris et ^D) ...*/

        xv_set (Hwimg, WIN_CONSUME_EVENTS,
                           WIN_UP_EVENTS,
                           WIN_ASCII_EVENTS, 
                           0,
                       WIN_EVENT_PROC, trtevn, 
                       0);

/* .... on passe la main a la fenetre ..............*/

        (void) thr_setprio (thr_self (), (MAXPRIO / 2));
        (void) thr_setprio (Twin, MAXPRIO);
        (void) thr_yield ();
        (void) thr_setprio (thr_self (), MAXPRIO);

/* ..... remise en etat ............................*/

        switch (*Pibtn) {
        default:
        case 1:
          kactl  = kact;
          kactdl = kactd;
          PFactl = PFact;
          break;
        case 2:
          kactm  = kact;
          kactdm = kactd;
          PFactm = PFact;
          break;
        case 3:
          kactr  = kact;
          kactdr = kactd;
          PFactr = PFact;
          break;
        }

}
void
btncnt (Event *PSevn)
             

/*
 *     cede la main quand on relache
 */
{
        if (event_is_up (PSevn)) {
          (void) thr_setprio (thr_self (), MINPRIO);
          (void) thr_yield ();
        }
}
void
timstp (void)

/*
 *    arret sur temps ecoule
 */
{
        if (Hfedtc != XV_NULL) {
           xv_destroy_safe (Hfedtc);
        }
        if (Hfedtg != XV_NULL) {
           xv_destroy_safe (Hfedtg);
        }
        xv_destroy_safe (Hfimg);
        ifaff = 4;
        return;
}
E 1
