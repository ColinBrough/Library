/*----------------------------------------------------------------------
 *
 *	FileUtils.c	File handling utility routines that are part
 *			of my own library of useful stuff.
 *
 *----------------------------------------------------------------------
 * $Id: FileUtils.c,v 1.3 1998/08/04 18:23:06 cmb Exp $
 *
 * $Log: FileUtils.c,v $
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
 * parameter.
 *----------------------------------------------------------------------*/

void
copy_file(FILE *outs, char *infname)
{
    FileDes f;

    strcpy(f.filename, infname);
    
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
MapFile(char *filename)
{
    FileDes *f;
    if ((f = (FileDes *) malloc(sizeof(FileDes))) == NULL)
    {
        error("Failed to allocate memory for a file descriptor structure "
              "while trying\nto map the file: %s\n", filename);
    }

    strcpy(f->filename, filename);
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
