/* This header file contains various little structure definitions for things
 * like points and rectangles.  You would probably want to build up from
 * the things defined in here.
 *
 *
 *
 *               -- This code under the GNU copyleft --
 *
 *   Dominic Giampaolo
 */

#ifndef GFX_H
#define GFX_H


/* Two dimensional things */
typedef struct Point 
{
  short x, y;
} Point;
typedef struct Point Point2d;
typedef Point Vector2d;

typedef struct FPoint
{
  float x, y;
}FPoint;
typedef struct FPoint Fpoint;
typedef struct FPoint FPoint2d;


typedef struct Rectangle
{
  unsigned short left_edge, top_edge;
  unsigned short width, height;
} Rectangle;
typedef struct Rectangle Box;
typedef struct Rectangle Square;


typedef struct FRectangle
{
  float left_edge, top_edge;
  float width, height;
} FRectangle;
typedef struct FRectangle FBox;
typedef struct FRectangle FSquare;



#endif  /* GFX_H */
