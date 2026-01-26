/*
 * -Allen Martin (amartin@wpi.wpi.edu)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "libsx.h"		/* gets us in the door with libsx */
#include "multireq.h"

int init_display(int argc, char **argv, void *data);

/* callback protos */
void edit(Widget w, void *data);
void quit(Widget w, void *data);


void main(int argc, char **argv)
{
  argc = init_display(argc, argv, NULL);  /* setup the display */
  if (argc == 0)
    exit(0);

  MainLoop();                                /* go right into the main loop */
}


/* This function sets up the display.  For any kind of a real program, 
 * you'll probably want to save the values returned by the MakeXXX calls
 * so that you have a way to refer to the display objects you have 
 * created (like if you have more than one drawing area, and want to
 * draw into both of them).
 */
int init_display(int argc, char **argv, void *data)
{
  Widget w[2];

  argc = OpenDisplay(argc, argv);
  if (argc == FALSE)
    return argc;

  w[0]  = MakeButton("Edit",     edit,   data);
  w[1]  = MakeButton("Quit!",    quit,   data);

  SetWidgetPos(w[1], PLACE_RIGHT, w[0], NO_CARE, NULL);

  ShowDisplay();
  
  GetStandardColors();

  return argc;
}

/*
 */
void edit(Widget w, void *data)
{
  static char name[1024] = "Computer Geek";
  static char address[1024] = "Fuller Labs, WPI";
  static int number=123;
  static float height=456.789;
  
  TagList tags[] = {
    {TAG_STRING, "Name:",        name,     TAG_INIT},
    {TAG_LABEL,  "Please Enter your Address below",     NULL,  TAG_NOINIT}, 
    {TAG_STRING, "Address:",     address,  TAG_INIT}, 
    {TAG_INT,    "Number:",      &number,  TAG_INIT}, 
    {TAG_FLOAT,  "Height:",      &height,  TAG_INIT}, 
    {TAG_DONE,   NULL,           NULL,     TAG_NOINIT}
  };

  if(GetValues(tags))
    printf("Cancelled\n");
  else
    {
      printf("Name: %s\n", name);
      printf("Address: %s\n", address); 
      printf("Number: %d\n", number); 
      printf("Height: %f\n", height); 
    }
}

/*
 * quit() - Callback function for the quit button
 */
void quit(Widget w, void *data)
{
  exit(0);
}






