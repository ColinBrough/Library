/*----------------------------------------------------------------------
 *
 *	FileUtils.c	File handling utility routines that are part
 *			of my own library of useful stuff.
 *
 *----------------------------------------------------------------------
 * $Id: FileUtils.c,v 1.1 1998/07/25 14:30:30 cmb Exp $
 *
 * $Log: FileUtils.c,v $
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

    f->file = fopen(f->filename, "r");
    f->file_descriptor = fileno(f->file);
    fstat(f->file_descriptor, &sbuf);
    f->length = sbuf.st_size;
    f->page = 0;
    f->page = mmap(0, f->length, PROT_READ, MAP_SHARED, f->file_descriptor, 0);
}

void
unmap_file(FileDes *f)
{
    munmap(f->page, f->length);
    fclose(f->file);
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
