/*
**
** A simple "dir" application. Shows detailed info.
**
*/

#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//------------------------------------------------------------------------------------------------------------------
// Globals...
//------------------------------------------------------------------------------------------------------------------
WIN32_FIND_DATA *fd;

//------------------------------------------------------------------------------------------------------------------
// Protos...
//------------------------------------------------------------------------------------------------------------------
int     showdir(const char *path, BOOL recursive);
int     fixpath(const char *inpath, char *outpath);

//------------------------------------------------------------------------------------------------------------------
// showdir()
//------------------------------------------------------------------------------------------------------------------
int showdir(const char *_path,BOOL recursive)
{
  HANDLE fh;
  int    attrib_a=0;
  int    attrib_c=0;
  int    attrib_d=0;
  int    attrib_h=0;
  int    attrib_n=0;
  int    attrib_o=0;
  int    attrib_r=0;
  int    attrib_s=0;
  int    attrib_t=0;
  int    filecnt=0;
  char	 path[MAX_PATH];
  char	 tmppath[MAX_PATH];

  fd = malloc(sizeof(WIN32_FIND_DATA));

  fixpath(_path,path);
  strcat(path,"*");

  printf("\nScanning: %s\n",path);

  fh = FindFirstFile((LPCSTR) path,fd);

  if(fh != INVALID_HANDLE_VALUE)
  {
    do
    {
      filecnt++;
      if(fd->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
      {
        printf("[%-33.33s] ",fd->cFileName);
        if((0 != strcmp(fd->cFileName,".")) && (0 != strcmp(fd->cFileName,"..")))
        {
          fixpath(_path,tmppath);
          strcat(tmppath,fd->cFileName);
          fixpath(tmppath,tmppath);
          if(recursive)
            showdir(tmppath,recursive);
        }
      }
      else
      {
        printf("%-35.35s "  ,fd->cFileName);
      }

      if(fd->dwFileAttributes & FILE_ATTRIBUTE_ARCHIVE) 		printf("A") && attrib_a++ ; else printf("-");
      if(fd->dwFileAttributes & FILE_ATTRIBUTE_COMPRESSED) 	        printf("C") && attrib_c++ ; else printf("-");
      if(fd->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)		printf("D") && attrib_d++ ; else printf("-");
      if(fd->dwFileAttributes & FILE_ATTRIBUTE_HIDDEN)			printf("H") && attrib_h++ ; else printf("-");
      if(fd->dwFileAttributes & FILE_ATTRIBUTE_NORMAL)			printf("N") && attrib_n++ ; else printf("-");
      if(fd->dwFileAttributes & FILE_ATTRIBUTE_OFFLINE)			printf("O") && attrib_o++ ; else printf("-");
      if(fd->dwFileAttributes & FILE_ATTRIBUTE_READONLY)		printf("R") && attrib_r++ ; else printf("-");
      if(fd->dwFileAttributes & FILE_ATTRIBUTE_SYSTEM)			printf("S") && attrib_s++ ; else printf("-");
      if(fd->dwFileAttributes & FILE_ATTRIBUTE_TEMPORARY)		printf("T") && attrib_t++ ; else printf("-");

      //printf("Creation time    : %d\n",fd->ftCreationTime);
      //printf("Last access time : %d\n",fd->ftLastAccessTime);
      //printf("Last write time  : %d\n",fd->ftLastWriteTime);
      printf(" Size : %16lu bytes\n",((fd->nFileSizeHigh * MAXDWORD)+fd->nFileSizeLow));

    }
    while(FindNextFile(fh,fd));
  }

  printf("\nStatistics : (%d files)\n",filecnt);
  printf("Archived   : % 8d\n",attrib_a);
  printf("Compressed : % 8d\n",attrib_c);
  printf("Directory  : % 8d\n",attrib_d);
  printf("Hidden     : % 8d\n",attrib_h);
  printf("Normal     : % 8d\n",attrib_n);
  printf("Offline    : % 8d\n",attrib_o);
  printf("Read only  : % 8d\n",attrib_r);
  printf("System     : % 8d\n",attrib_s);
  printf("Temporary  : % 8d\n",attrib_t);

  FindClose(fh);

  return 1;
}

//------------------------------------------------------------------------------------------------------------------
// fixpath() - Adds \ to the end of a path if not present.
//------------------------------------------------------------------------------------------------------------------
int fixpath(const char *inpath, char *outpath)
{
  int   n=0;

  strcpy(outpath,inpath);

  while(inpath[n]) n++;

  if(inpath[n-1] != '\\')
  {
    strcat(outpath,"\\");
    return 1;
  }

  return 0;
}

//------------------------------------------------------------------------------------------------------------------
// Entry point...
//------------------------------------------------------------------------------------------------------------------
int main(int argc, char *argv[])
{
  int recursive=0;
  int ndirs=0;

  while(*++argv)
  {
    if(!strcmp(*argv, "-r") || !strcmp(*argv, "/r"))
      recursive=1;
    else
    {
      showdir(*argv, recursive);
      ++ndirs;
    }
  }
  if(!ndirs) showdir(".", recursive);
  system("pause");
  return 0;
}
