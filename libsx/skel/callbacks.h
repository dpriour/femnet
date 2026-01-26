/* This file contains prototypes for the functions in callbacks.c.  It is
 * included by main.c so that when you create a new widget, you can tie
 * its callback function to something that has been defined (otherwise the
 * compiler will give you and error).
 *
 * If you add any functions to callbacks.c, you should put a corresponding 
 * function prototype in here.
 */


/* callback protos */
void quit(Widget w,    void *data);
void button1(Widget w, void *data);
void button2(Widget w, void *data);


void redisplay(Widget w, int new_width, int new_height, void *data);
void button_down(Widget w, int which_button, int x,int y, void *data);
void button_up(Widget w, int which_button, int x, int y, void *data);
void keypress(Widget w, char *input, int up_or_down, void *data);
void motion(Widget w, int x, int y, void *data);
