/* This file contains the various things related to the main body of the 
 * program.  It is pretty sparse, and really shouldn't be too cluttered
 * up.
 *
 */

/* This structure contains information relevant to your program.
 * You should fill it in with information that you need.
 *
 */
typedef struct MyProgram
{
  int var1, var2;
  int curstate;
  int flags;
}MyProgram;


/* protos */
void init_display(int argc, char **argv, MyProgram *me);


#ifndef TRUE
#define TRUE  1
#define FALSE 0
#endif
