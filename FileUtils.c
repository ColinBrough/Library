/*----------------------------------------------------------------------
 *
 *	FileUtils.c	File handling utility routines that are part
 *			of my own library of useful stuff.
 *
 *---------------------------------------------------------------------- * $Id: FileUtils.c,v 1.8 1998/08/21 20:52:03 cmb Exp $
 *
 * $Log: FileUtils.c,v $
 * Revision 1.8  1998/08/21 20:52:03  cmb
 * Removed use of varargs, since was introducing a bug. Made routines
 * take a path argument, which will be explicitly NULL when no path needs
 * to be prepended to the filename.
 *
 * Revision 1.7  1998/08/05 15:18:30  cmb
 * Made copy_file able to take an optional third argument which specifies
 * a path to be prepended to the filename.
 *
 * Revision 1.6  1998/08/04 22:15:56  cmb
 * Updated a couple of the function definitions so that they properly
 * label a couple of arguments that they use only as input with 'const',
 * as they should.
 *
 * Revision 1.5  1998/08/04 21:59:42  cmb
 * Removed development printing of progress output.
 *
 * Revision 1.4  1998/08/04 19:12:48  cmb
 * Made the MapFile wrapper use the stdarg macros to detect whether,
 * along with the filename, a path component is passed in. If so,
 * construct the full path using path then filename, otherwise just use
 * the filename.
 *
 * Revision 1.3  1998/08/04 18:23:06  cmb
 * Added wrapper functions round the lower level file mapping and
 * unmapping functions that allows them to be used slightly more easily
 * by applications.
 *
 * Revision 1.2  1998/07/25 15:02:58  cmb
 * Added a load of error checking.
 *
 * Revision 1.1  1998/07/25 14:30:30  cmb
 * Initial revision
 *
 *----------------------------------------------------------------------*/

#include <cmb.h>

/*----------------------------------------------------------------------
 * Utility routines to map and unmap a file.
 *----------------------------------------------------------------------*/

void
map_file(FileDes *f)
{
    struct stat sbuf;

    if ((f->file = fopen(f->filename, "r")) == NULL)
    {
        printf("Failed to open file: %s\n", f->filename);
        exit(-1);
    }
    f->file_descriptor = fileno(f->file);

    if (fstat(f->file_descriptor, &sbuf) == -1)
    {
        printf("Failed to stat file: %s\n", f->filename);
        exit(-1);
    }
    f->length = sbuf.st_size;
    f->page = 0;

    if ((int)(f->page = mmap(0, f->length, PROT_READ,
                             MAP_SHARED, f->file_descriptor, 0)) == -1)
    {
        printf("Failed to mmap file: %s\n", f->filename);
        exit(-1);
    }
}

void
unmap_file(FileDes *f)
{
    if (munmap(f->page, f->length) != 0)
    {
        printf("Failed to unmap file: %s\n", f->filename);
        exit(-1);
    }
    if (fclose(f->file) == EOF)
    {
        printf("Failed to close file: %s\n", f->filename);
        exit(-1);
    }
}

/*----------------------------------------------------------------------
 * Copy a file, given filename, onto the stream passed in as first
 * parameter. The optional third argument is a path that can be prepended
 * to the filename, in much the same way as MapFile below.
 *----------------------------------------------------------------------*/

void
copy_file(FILE *outs, const char *infname, const char *path)
{
    FileDes f;

    if ((path != NULL) && (strlen(path) != 0))
    {
        sprintf(f.filename, "%s/%s", path, infname);
    }
    else
    {
        strcpy(f.filename, infname);
    }
    
    map_file(&f);
    fwrite(f.page, sizeof(char), f.length, outs);
    unmap_file(&f);
}

/*----------------------------------------------------------------------
 * MapFile	Wrapper round the lower level file mapper, which allows
 *		a filename to be passed in and returns a FileDes struct
 *		having allocated memory for it. This memory will be freed
 *		when the file is unmapped.
 *----------------------------------------------------------------------*/

FileDes *
MapFile(const char *filename, const char *path)
{
    FileDes *f;
    
    if ((f = (FileDes *) malloc(sizeof(FileDes))) == NULL)
    {
        error("Failed to allocate memory for a file descriptor structure "
              "while trying\nto map the file: %s\n", filename);
    }

    if ((path != NULL) && (strlen(path) != 0))
    {
        sprintf(f->filename, "%s/%s", path, filename);
    }
    else
    {
        strcpy(f->filename, filename);
    }
    
    map_file(f);

    return(f);
}

/*----------------------------------------------------------------------
 * UnmapFile	Wrapper round the lower level file unmapper, which calls
 *		that routine and then frees the memory allocated for
 *		the file descriptor struct.
 *----------------------------------------------------------------------*/

void
UnmapFile(FileDes *f)
{
    unmap_file(f);
    free(f);
}
