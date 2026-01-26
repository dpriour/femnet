h65443
s 00045/00000/00000
d D 1.1 95/10/17 12:24:18 molagnon 1 0
c date and time created 95/10/17 12:24:18 by molagnon
e
u
U
f e 0
t
T
I 1
/*
 *      tabclr  = choix de la table des couleurs 
 *          0 = monochrome
 *          1 = echelle de gris
 *          2 = arc en ciel
 *          3 = rgb
 *          4 = coloredit
 *          5 = grayedit
 *           
 *      auteur  = Ph.Morvan  R/D/I+    
 *      version = %I% du %G%     
 */

void
tabclr_ (Pktblc)
int *Pktblc;   /* numero de la table des couleurs  */
{
      int ktblw;   
      extern void chxclr_ (int *Pktbl);
      extern void inineb_ (void);

      switch (*Pktblc) {
      case 0:
        inineb_ ();
        break;
      case 1:
        chxclr_ (Pktblc);
        break;
      case 2:
        chxclr_ (Pktblc);
        break;
      case 3:
        chxclr_ (Pktblc);
        break;
      default:
      case 4:
        ktblw = 12;
        chxclr_ (&ktblw);
        break;
      case 5:
        ktblw = 13;
        chxclr_ (&ktblw);
        break;
      }
}
E 1
