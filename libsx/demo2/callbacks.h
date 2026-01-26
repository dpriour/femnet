/* This file contains prototypes for the functions in callbacks.c.  It is
 * included by main.c so that when you create a new widget, you can tie
 * its callback function to something that has been defined (otherwise the
 * compiler will give you and error.
 *
 * If you add any functions to callbacks.c, you should put a corresponding 
 * function prototype in here.
 */


/* callback protos */
void quit(Widget w,     void *data);
void pattern1(Widget w, void *data);
void pattern2(Widget w, void *data);
void redisplay(Widget w, int new_width, int new_height, void *data);


