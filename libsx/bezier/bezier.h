void bezier4(Point *control_pts, int num_steps);

/*
 * Gag, this is ugly.  Can't find a reliable way to pick up the
 * typedef for ushort, so we #define it instead.
 *
 * Will unix ever be clean?
 */
#ifndef ushort
#define ushort unsigned short
#endif
