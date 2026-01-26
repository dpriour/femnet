h37544
s 00072/00000/00000
d D 1.1 95/10/17 12:16:32 molagnon 1 0
c date and time created 95/10/17 12:16:32 by molagnon
e
u
U
f e 0
t
T
I 1
#include "../include/faixvg.h"
                          
char  *Pzrass; 
int lzrass;
int ifras;

void
iniras_ (int *Pibtn, char *Pzras, int lzras)
                  /* bouton declenchant                   */
                  /* fichier rasterfile                   */
          

/*
 *      iniras = initialisation de sauvegarde rasterfile
 *      version %I% du %G%
 */
     
{
      extern char *fortoc ();
      extern void trmrgt ();
      extern void inistr ();
      extern void btnras (Event *PSevn);

/* ..... flag et bouton ......................*/

      switch (*Pibtn) {
      default:
      case 1:             /* MS_LEFT */
        kactl = FAI_RAS;
        kactdl = FAI_NONE;
        PFactl = btnras;
        break;
      case 2:             /* MS_MIDDLE */
        kactm = FAI_RAS;
        kactdm = FAI_NONE;
        PFactm = btnras;
        break;
      case 3:             /* MS_RIGHT */
        kactr = FAI_RAS;
        kactdr = FAI_NONE;
        PFactr = btnras;
        break;
      }

/* ..... deja initialise ? ...................*/

      if (ifras) {
         return;
      }
      ifras = 1;

/* ..... fichier ..................................... */

      Pzrass = Pzras;
      lzrass = lzras;

}
void
btnras (Event *PSevn) 
             

/* 
 * btnras : sauve l'image dans un fichier
 *
 */
{
        extern int savimg_ (char *Pzfil, int lzfil);

        if (event_is_up (PSevn)) {
           (void *) savimg_ (Pzrass, lzrass);
        }
}
E 1
