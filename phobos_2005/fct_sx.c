#define PRINCIPAL 0
#include "phobos.h"

#include <sys/param.h>
#include <limits.h>
#include <sys/times.h>
#include <dirent.h>
#include <sys/param.h>
#include <sys/stat.h>
#include <string.h>
#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

#define TAG_DONE          99
#define TAG_NULL          0
#define TAG_STRING        1
#define TAG_INT           2
#define TAG_FLOAT         3
#define TAG_LABEL         4
#define TAG_WINDOW_LABEL  5
#define TAG_INIT    1
#define TAG_NOINIT  0
 char masque[80]; /* masque pour les fichiers */

typedef struct {
  Widget window;
  int cancelled;
  Widget *w;
  TagList *tags;
} MReqData;



/* protos */
static void mreq_ok(Widget w, MReqData *mdata);
static void mreq_cancel(Widget w, MReqData *mdata);
     
int GetValues(TagList *tags,char *window_name)
{
  MReqData mdata;
  int num_tags=0, num_widg=0, num_labels=0;
  int i, ww, l;
  Widget *label_w, ok_w, cancel_w;
  char string[256];/* window_name[256]="Requestor"; */
  int maxwidth=0, widest_label=-1;
  
  /* first count the number of tag items and required widgets */
  for(; tags[num_tags].tag != TAG_DONE; num_tags++)
    {
      if(tags[num_tags].tag == TAG_LABEL)
	{
	  num_labels++;
	  continue;
	}
      else if(tags[num_tags].tag == TAG_WINDOW_LABEL)
	{
	  if(!tags[num_tags].label)
	    {
	      fprintf(stderr, "Invalid window name passed to GetValues()\n");
	      return(TRUE);
	    }

	  strcpy(window_name, tags[num_tags].label);
	  continue;
	}
      
      /* determine the widest label */
      if(strlen(tags[num_tags].label) > maxwidth)
	{
	  maxwidth = strlen(tags[num_tags].label);
	  widest_label = num_labels;
	}

      num_labels++;
      num_widg++;
    }
      
  /* allocate mem for the widgets */
  if(!(mdata.w = (Widget *)malloc(num_widg * sizeof(Widget))))
    return(TRUE);
  if(!(label_w = (Widget *)malloc(num_labels * sizeof(Widget))))
    {
      free(mdata.w);
      return(TRUE);
    }
  
  mdata.window = MakeWindow(window_name, SAME_DISPLAY, EXCLUSIVE_WINDOW);
  mdata.tags = tags;

  /* create the label widgets first */
  for(i=0, l=0; i<num_tags; i++)
    {
      if(tags[i].tag == TAG_WINDOW_LABEL)
	continue;
      
      label_w[l] = MakeLabel(tags[i].label);
      if(l)
	SetWidgetPos(label_w[l], PLACE_UNDER, label_w[l-1], NO_CARE, NULL);
      l++;
    }
  
  for(i=0, ww=0, l=0; i<num_tags; i++)
    {
      switch(tags[i].tag)
	{
	case TAG_STRING:
	  if(tags[i].init)
	    mdata.w[ww]=MakeStringEntry((char *)tags[i].data, 250, NULL, NULL);
	  else
	    mdata.w[ww] = MakeStringEntry(NULL, 250, NULL, NULL);
	  
	  if(l)
	    SetWidgetPos(mdata.w[ww], PLACE_UNDER, label_w[l-1],
			 PLACE_RIGHT, label_w[widest_label]);
	  else
	    SetWidgetPos(mdata.w[ww], PLACE_RIGHT, label_w[widest_label],
			 NO_CARE, NULL);

	  l++;
	  ww++;
	  break;

	case TAG_INT:
	  if(tags[i].init)
	    {
	      sprintf(string, "%d", *((int *)tags[i].data));
	      mdata.w[ww] = MakeStringEntry(string, 250, NULL, NULL);
	    }
	  else
	    mdata.w[ww] = MakeStringEntry(NULL, 250, NULL, NULL);
	  
	  if(l)
	    SetWidgetPos(mdata.w[ww], PLACE_UNDER, label_w[l-1],
			 PLACE_RIGHT, label_w[widest_label]);
	  else
	    SetWidgetPos(mdata.w[ww], PLACE_RIGHT, label_w[widest_label],
			 NO_CARE, NULL);

	  l++;
	  ww++;
	  break;

	case TAG_FLOAT:
	  if(tags[i].init)
	    {
	      sprintf(string, "%f", *((float *)tags[i].data));
	      mdata.w[ww] = MakeStringEntry(string, 250, NULL, NULL);
	    }
	  else
	    mdata.w[ww] = MakeStringEntry(NULL, 250, NULL, NULL);
	  
	  if(l)
	    SetWidgetPos(mdata.w[ww], PLACE_UNDER, label_w[l-1],
			 PLACE_RIGHT, label_w[widest_label]);
	  else
	    SetWidgetPos(mdata.w[ww], PLACE_RIGHT, label_w[widest_label],
			 NO_CARE, NULL);

	  ww++;
	  l++;
	  break;

	case TAG_LABEL:
	  l++;
	  break;
	case TAG_WINDOW_LABEL:
	  break;
	  
	default:
	  fprintf(stderr, "GetValues() : Invalid tag item %d\n", tags[i].tag);
	}
    }
  
  ok_w = MakeButton("Ok", (void *)mreq_ok, &mdata);
  SetWidgetPos(ok_w, PLACE_UNDER, label_w[num_labels-1], NO_CARE, NULL);

  cancel_w = MakeButton("Cancel", (void *)mreq_cancel, &mdata);
  SetWidgetPos(cancel_w, PLACE_UNDER, label_w[num_labels-1],
	       PLACE_RIGHT, ok_w);

  ShowDisplay();
  MainLoop();
  
  SetCurrentWindow(ORIGINAL_WINDOW);

  /* check for cancel */
  if(mdata.cancelled)
    return(TRUE);

  free(mdata.w);
  free(label_w);
  
  return(FALSE);
}

static void mreq_ok(Widget w, MReqData *mdata)
{
  int widg_num;
  TagList *tagptr;
  char *cptr;
  
  /* extract the info from the widgets */
  for(widg_num=0, tagptr=mdata->tags; tagptr->tag != TAG_DONE; tagptr++)
    {
      switch(tagptr->tag)
	{
	case TAG_STRING:
	  cptr = GetStringEntry(mdata->w[widg_num++]);
	  strcpy(tagptr->data, cptr);
	  break;
	case TAG_INT:
	  cptr = GetStringEntry(mdata->w[widg_num++]);
	  *((int *)tagptr->data) = atoi(cptr);
	  break;
	case TAG_FLOAT:
	  cptr = GetStringEntry(mdata->w[widg_num++]);
	  *((float *)tagptr->data) = atof(cptr);
	  break;
	case TAG_WINDOW_LABEL:
	case TAG_LABEL:
	  break;
	default:
	  fprintf(stderr, "GetValues() : Invalid tag item %d\n", tagptr->tag);
	}
    }
  
  mdata->cancelled = FALSE;
  SetCurrentWindow(mdata->window);
  CloseWindow();
}

static void mreq_cancel(Widget w, MReqData *mdata)
{
  mdata->cancelled = TRUE;
  SetCurrentWindow(mdata->window);
  CloseWindow();
}


/********************************************************************/

#ifndef CLK_TCK
#include <unistd.h>
#define  CLK_TCK  sysconf(_SC_CLK_TCK)    /* seems to work right */
#endif  /* CLK_TCK */


typedef struct {
  Widget freq_window;
  Widget file_path;
  Widget file_name;
  Widget file_list;

  char **dirlist;            /* used by the list widget */
  char fpath[MAXPATHLEN];
  char fname[MAXPATHLEN];
  
  clock_t last_click;        /* time of last click */

} FReqData;

static void load_cancel(Widget w, FReqData *fdata);
static void load_ok(Widget w, FReqData *fdata);
static void load_list(Widget w, char *string, int index, FReqData *fdata);
static void load_dir(Widget w, char *string, FReqData *fdata);
static void load_name(Widget w, char *string, FReqData *fdata);
static int mystrcmp(const void *a, const void *b);

char **get_dir_list(char *pname, int *num);
void free_dirlist(char **table);


/*
 * GetFile() - This is the entry point to the file requestor.  A single
 *             argument is passed - the path name for the initial list.
 *             If this path name is passed as NULL, the current directory
 *             is used instead.  The function returns a character string
 *             that is the name of the selected file, path included.  If
 *             an error occurs, or the user selects CANCEL, NULL is returned.
 */
char *GetFile(char *_path)
{
  FReqData fdata;
  Widget w[8];
  int num_dir;
  char path[MAXPATHLEN],*buffer;

  if(!_path || strcmp(_path, ".") == 0 || strcmp(_path, "./") == 0)
    buffer = getcwd(path, MAXPATHLEN);
  else
    strcpy(path, _path);
  
  if(path[strlen(path)-1] != '/')
    strcat(path, "/");

  if(!(fdata.dirlist = get_dir_list(path, &num_dir)))
    return(NULL);
  
  qsort(fdata.dirlist, num_dir, sizeof(char *), mystrcmp);

  fdata.freq_window = MakeWindow("Selection de fichiers", SAME_DISPLAY,
				 EXCLUSIVE_WINDOW);

  w[0]  = MakeLabel("Repertoire:");
  w[1]  = MakeStringEntry(path, 300, (void *)load_dir,         &fdata);
  w[2]  = MakeScrollList(fdata.dirlist, 350+8*5, 300, (void *)load_list, &fdata);
  w[3]  = MakeLabel("Fichier :");
  w[4]  = MakeStringEntry("", 300+2*8, (void *)load_name,          &fdata);
  w[5]  = MakeButton("    Ok    ",         (void *)load_ok,            &fdata);
  w[6]  = MakeLabel("                              ");
  w[7]  = MakeButton(" Abandon ",     (void *)load_cancel,        &fdata);
  
  SetWidgetPos(w[1], PLACE_RIGHT, w[0], NO_CARE,     NULL);
  SetWidgetPos(w[2], PLACE_UNDER, w[0], NO_CARE,     NULL);
  SetWidgetPos(w[3], PLACE_UNDER, w[2], NO_CARE,     NULL);
  SetWidgetPos(w[4], PLACE_UNDER, w[2], PLACE_RIGHT, w[3]);
  SetWidgetPos(w[5], PLACE_UNDER, w[3], NO_CARE,     NULL);
  SetWidgetPos(w[6], PLACE_UNDER, w[3], PLACE_RIGHT, w[5]);
  SetWidgetPos(w[7], PLACE_UNDER, w[3], PLACE_RIGHT, w[6]);

  /* save the file name & file list widgets, so we can use them later */
  fdata.file_path = w[1];
  fdata.file_list = w[2];
  fdata.file_name = w[4];

  fdata.last_click = 0;

  /* set up the file path */
  strcpy(fdata.fpath, path);
  
  ShowDisplay();
  MainLoop();
  
  /* free the directory list */
  if (fdata.dirlist)
    free_dirlist(fdata.dirlist);
  
  SetCurrentWindow(ORIGINAL_WINDOW);

  if(fdata.fname[0] == '\0')
    return(NULL);
  else
    return((char *)strdup(fdata.fname));
}

/*
 * load_cancel() - Callback routine for CANCEL button
 */
static void load_cancel(Widget w, FReqData *fdata)
{
  SetCurrentWindow(fdata->freq_window);
  CloseWindow();
  strcpy(fdata->fname, "");
}

/*
 * load_ok() - Callback routine for OK button
 */
static void load_ok(Widget w, FReqData *fdata)
{
  char *fpath, *fname;
  char fullname[MAXPATHLEN];
  
  fpath = GetStringEntry(fdata->file_path);
  fname = GetStringEntry(fdata->file_name);

  sprintf(fullname, "%s%s", fpath, fname);

  /* right here we should check the validity of the file name */
  /* and abort if invalid */

  strcpy(fdata->fname, fullname);

  SetCurrentWindow(fdata->freq_window);
  CloseWindow();
}

/*
 * load_list() - Callback routine for scrollable list widget
 */
static void load_list(Widget w, char *string, int index, FReqData *fdata)
{
  char newpath[MAXPATHLEN], *cptr, *fpath, fullname[MAXPATHLEN];
  char **old_dirlist=NULL;
  static char oldfile[MAXPATHLEN] = { '\0', };
  clock_t cur_click;
  struct tms junk_tms;  /* not used, but passed to times() */
  int num_dir;
  float tdiff;    /* difference in time between two clicks as % of a second */
  
  /*
   * First we check fora double click.
   *
   * If the time between the last click and this click is greater than
   * 0.5 seconds or the last filename and the current file name
   * are different, then it's not a double click, so we just return.
   */
  cur_click = times(&junk_tms);
  tdiff = ((float)(cur_click - fdata->last_click) / CLK_TCK);

  if(tdiff > 0.50 || strcmp(oldfile, string) != 0)
   {
     fdata->last_click = cur_click;
     strcpy(oldfile, string);
     SetStringEntry(fdata->file_name, string);
     return;
   }
  
  /* check if a directory was selected */
  if(string[strlen(string)-1] != '/')   /* a regular file double click */
   {
     fpath = GetStringEntry(fdata->file_path);
     
     sprintf(fullname, "%s%s", fpath, string);
     
     /* right here we should check the validity of the file name */
     /* and abort if invalid */
     
     strcpy(fdata->fname, fullname);
     
     SetCurrentWindow(fdata->freq_window);
     CloseWindow();
     return;
   }

  /*
   * Else, we've got a directory name and should deal with it
   * as approrpriate.
   */

  /* check for special cases "./" and "../" */
  if(strcmp(string, "./") == 0)
   {
     if (fdata->fpath)
       strcpy(newpath, fdata->fpath);
     else
       strcpy(newpath, "./");
   }
  else if(strcmp(string, "../") == 0)
   {
     strcpy(newpath, fdata->fpath);
     
     if (strcmp(newpath, "./") == 0)
       strcpy(newpath, string);
     else 
      {
	/*
	 * chop off the last path component and look at what it 
	 * is to determine what to do with the `..' we just got.
	 */
	cptr = strrchr(newpath, '/');
	if (cptr)
	  *cptr = '\0';
	cptr = strrchr(newpath, '/');
	if (cptr)
	  *cptr = '\0';

	if (  (cptr != NULL && strcmp(cptr+1,  "..") == 0)
	    ||(cptr == NULL && strcmp(newpath, "..") == 0))
	 {
	   if (cptr)
	     *cptr = '/';

	   strcat(newpath, "/");      /* put back the / we took out */
	   strcat(newpath, "../");    /* and append the new ../ */
	 }
	else
	 {
	   if(cptr == NULL && strcmp(fdata->fpath, "/") == 0)
	     strcpy(newpath, "/");
	   else if (cptr == NULL)
	     strcpy(newpath, "./");

	   if (newpath[strlen(newpath)-1] != '/')
	     strcat(newpath, "/");
	 }
      }
   }
  else /* not a `./' or `../', so it's just a regular old directory name */
   {
     if (fdata->fpath[strlen(fdata->fpath)-1] == '/')
       sprintf(newpath, "%s%s", fdata->fpath, string);
     else
       sprintf(newpath, "%s/%s", fdata->fpath, string);
   }

  old_dirlist = fdata->dirlist;
  if(!(fdata->dirlist = get_dir_list(newpath, &num_dir)))
    /* should beep the display or something here */
    return;
  
  qsort(fdata->dirlist, num_dir, sizeof(char *), mystrcmp);
  
  strcpy(fdata->fpath, newpath);
  SetStringEntry(fdata->file_path, fdata->fpath);
  SetStringEntry(fdata->file_name, "");
  strcpy(fdata->fpath, newpath);
  ChangeScrollList(fdata->file_list, fdata->dirlist);
  
  /* free the directory list */
  if (old_dirlist)
    free_dirlist(old_dirlist);
  
  
  fdata->last_click = 0;  /* re-init double-click time */
  
  return;
}

/*
 * load_dir() - Callback routine for pathname string entry widget
 */
static void load_dir(Widget w, char *string, FReqData *fdata)
{
  char **old_dirlist, temp[MAXPATHLEN],mask[MAXPATHLEN];
  int num_dir;
	int i;

  /* make sure the name has a '/' at the end */
  strcpy(temp, string);
  strcpy(mask,string);
  i=strlen(mask);
	while (i>0 && mask[i]!='*') i--;
 if (i==0) masque[0]=0;
 else {strcpy(masque,mask+i+1);temp[i]=0;}
 /*printf("masque= %s\n",masque);*/
  if(temp[strlen(temp)-1] != '/')
    strcat(temp, "/");
  
  old_dirlist = fdata->dirlist;
  
  if(!(fdata->dirlist = get_dir_list(temp, &num_dir)))
    {
      /* bad path - reset the file path and return */
      SetStringEntry(fdata->file_path, fdata->fpath);
      return;
    }
  
  qsort(fdata->dirlist, num_dir, sizeof(char *), mystrcmp);

  strcpy(fdata->fpath, temp);
  SetStringEntry(fdata->file_path, temp);
  ChangeScrollList(fdata->file_list, fdata->dirlist);

  /* free the directory list */
  if (old_dirlist)
    free_dirlist(old_dirlist);
}

/*
 * load_name() - Callback routine for file name string entry widget
 */
static void load_name(Widget w, char *string, FReqData *fdata)
{
  char *fpath, fullname[MAXPATHLEN];
  
  fpath = GetStringEntry(fdata->file_path);
  
  sprintf(fullname, "%s%s", fpath, string);
  
  /* right here we should check the validity of the file name */
  /* and abort if invalid */
  
  strcpy(fdata->fname, fullname);

  SetCurrentWindow(fdata->freq_window);
  CloseWindow();
  return;
}


/*
 * This function is just a wrapper for mystrcmp(), and is called by qsort()
 * (if used) down below.
 */
static int mystrcmp(const void *a, const void *b)
{
  return strcmp(*(char **)a, *(char **)b);
}
/**************************************/
void free_table(char **table, int n)
{
  char **orig = table;

  for(; n > 0; n--, table++)
   {
     if (*table)
       free(*table);
   }

  free(orig);
}


void free_dirlist(char **table)
{
  char **orig = table;

  while(*table)
   {
     free(*table);
     table++;
   }

  free(orig);
}


char *get_file_name(struct dirent *d)
{
  struct stat s;
  char *name;

  if (d == NULL)
   {
     fprintf(stderr, "BUG BUG BUG (got a NULL in get_file_name()).\n");
     return NULL;
   }

  if (stat(d->d_name, &s) < 0)
   {
     perror(d->d_name);
     return NULL;
   }
  
  if (S_ISDIR(s.st_mode))
   {
     name = (char *)malloc(strlen(d->d_name)+2);
     if (name == NULL)
       return NULL;
     sprintf(name, "%s/", d->d_name);
   }
  else  if (  ((int)strlen(d->d_name)>strlen(masque) && strcmp(masque,d->d_name+strlen(d->d_name)-strlen(masque))==0 )  )
   { /*if (  ((int)strlen(name)>3 && strcmp(".ita",name+strlen(name)-4)==0 )  ) printf("[%s]\n",name+strlen(name)-4);*/
     name = (char *)strdup(d->d_name); 
   }
 else {/*printf(" > %s\n",name+strlen(name)-4);*/return NULL;}
  return name;
}




#define CHUNK  100


char **get_dir_list(char *dirname, int *num_entries)
{
  int i,size=CHUNK,itmp;
  char **table, old_dir[MAXPATHLEN],*buffer;
  DIR  *dir;
  struct dirent *dirent;

/* debut modifdp du 15 mars 2010*/
  int j,valid,fin,length;
  char *toto;
  toto = (char *)calloc(size, sizeof(char *));
/* debut modifdp du 15 mars 2010*/

  buffer = getcwd(old_dir, MAXPATHLEN);
  if (dirname && chdir(dirname) < 0)
    return NULL;
  
  dir = opendir(".");
  if (dir == NULL)
   {
     itmp = chdir(old_dir);
     return NULL;
   }
  
  table = (char **)calloc(size, sizeof(char *));
  if (table == NULL)
   {
     closedir(dir);
     itmp = chdir(old_dir);

     return NULL;
   }

  dirent = NULL;   i = 0;
  for(dirent = readdir(dir); dirent != NULL; dirent = readdir(dir))
   {
/* debut modifdp du 15 mars 2010*/
     /*table[i] = get_file_name(dirent);*/
     toto = get_file_name(dirent);/**/
     valid = 0;
     fin = -1;
     length=strlen(toto);
     /*printf("toto = %s length = %d\n",toto,length);*/
     do
     	{
     	fin++;
     	if (toto[fin]=='/') valid = 1;
     	if ((toto[fin]=='.') && (toto[fin+1]=='d') && (toto[fin+2]=='o') && (toto[fin+3]=='n')) valid = 1;
     	if ((toto[fin]=='.') && (toto[fin+1]=='m') && (toto[fin+2]=='d') && (toto[fin+3]=='g')) valid = 1;
     	if ((toto[fin]=='.') && (toto[fin+1]=='s') && (toto[fin+2]=='t') && (toto[fin+3]=='a')) valid = 1;
     	if ((toto[fin]=='.') && (toto[fin+1]=='d') && (toto[fin+2]=='y') && (toto[fin+3]=='n')) valid = 1;
     	if (toto[fin]=='~') valid = 0;
     	}
     while (fin != length);	
     if (valid == 1) table[i] = toto;
     /*printf("table[%d] = %s\n",i,table[i]);*/
/* debut modifdp du 15 mars 2010*/
     if (table[i] == NULL)   /* continue if there was an error */
      {
	continue;
      }

     i++;
     if (i == size)
      {
	char **table2;

	size *= 2;
	table2 = (char **)realloc(table, size * sizeof(char *));
	if (table2 == NULL)
	 {
	   free_table(table, i);
	   closedir(dir);
	   itmp = chdir(old_dir);

	   return NULL;
	 }

	table = table2;
      }
   }

  table[i] = NULL;    /* make sure the table ends with a NULL */

  if (num_entries)
    *num_entries = i;
  
  closedir(dir);
  itmp = chdir(old_dir);
  
  return table;
}

