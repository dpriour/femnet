/* callback protos */
void quit(Widget w, void *data);
void redraw_curve(Widget w, void *data);
void reset_curve(Widget w, void *data);
void bez_anim(Widget w, void *data);
void stop_anim(Widget w, void *data);
void time_out_adjust(Widget w, float newval, void *data);

void redisplay(Widget w, int width, int height, void *data);
void button_down(Widget w, int which_button, int x, int y, void *data);
void button_up(Widget w, int which_button, int x, int y, void *data);
void process_motion(Widget w, int x, int y, void *data);

