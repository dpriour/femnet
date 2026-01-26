h38503
s 00075/00000/00000
d D 1.1 95/10/17 12:16:25 molagnon 1 0
c date and time created 95/10/17 12:16:25 by molagnon
e
u
U
f e 0
t
T
I 1
#include "../include/faixvg.h"

void
fingra_ (void)
/*
 *      fingra = fin du graphique 
 *      version %I% du %G%
 */
         
{
     extern void rdcpxr ();

/* .... construction eventuelle de l'image .....................*/

     if (jgro > 1) {
        rdcpxr (PSimg, PSimgw, jprf, iclrb);
     }

     if (ifaff < 3) {
        (*PFactf) ();
     }
}

void
loogra (void)
/*
 * loogra : boucle appelee si pas de threads ou autres depuis
 *          inigra
 */
{                          
       extern void trtevn (Canvas Scnv, Event *PSevn);
       extern Notify_value tuedes (Notify_client client, Destroy_status status);

       ifaff = 3;
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

       xv_main_loop (Hfimg);
       return;           
}
void
etagra_ (int *Pketa)
           
/*
 * etagra : indique si le graphique est en cours ou fini
 */
{
      switch (ifaff) {
      default:
      case 0:
         if (PSimg) {
           *Pketa = 1;
         } else {
           *Pketa = 0;
         }
         break;
      case 1:
         *Pketa = 2;
         break;
      case 2:
      case 3:
      case 4:
         *Pketa = -1;
         break;
      }
}
E 1
