/*----------------------------------------------------------------------
 *
 *	FileUtils.c	File handling utility routines that are part
 *			of my own library of useful stuff.
 *
 *---------------------------------------------------------------------- 
 * $Id: FileUtils.c,v 1.21 2020/12/29 21:28:50 cmb Exp $
 *
 * $Log: FileUtils.c,v $
 * Revision 1.21  2020/12/29 21:28:50  cmb
 * Updated the file compare utility routine so it will work properly on
 * binary files (that may have a bytes in them that would otherwise be
 * interpreted as end of string!).
 *
 * Revision 1.20  2020/12/29 21:21:37  cmb
 * Rewrite of CopyFile routine when I realised it was truncating large
 * files on copy - probably some kind of kernel limit thing. Used a code
 * snippet from stackoverflow to redo it.
 *
 * Revision 1.19  2020/05/28 19:30:05  cmb
 * Fixed typo
 *
 * Revision 1.18  2020/05/28 19:29:11  cmb
 * Added file compare function
 *
 * Revision 1.17  2020/03/03 21:14:14  cmb
 * Clarified commenting!
 *
 * Revision 1.16  2020/03/03 20:38:05  cmb
 * Added routine to return the FileSize, given the filename
 *
 * Revision 1.15  2019/12/16 19:07:36  cmb
 * Added 'CopyFile' routine to mimic command line 'cp'...
 *
 * Revision 1.14  2019/05/02 21:37:44  cmb
 * Added routines to check for the existence of directories and "regular"
 * objects (files, directories and symlinks).
 *
 * Revision 1.13  2019/01/09 17:01:24  cmb
 * Added a file-existence check routine - checks for regular files
 *
 * Revision 1.12  2016/08/09 15:54:38  cmb
 * Added a function to create a whole directory path
 *
 * Revision 1.11  2016/06/16 16:57:15  cmb
 * Summary: Added a routine to read an integer value from a file.
 *
 * Revision 1.10  2013/01/30 15:47:24  cmb
 * Updated to remove compilation warning - sorted some casts...
 *
 * Revision 1.9  2009/08/12 20:29:28  cmb
 * Added routine to check whether one file is more recently modified than
 * another.
 *
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

    if ((void *)(f->page = mmap(0, f->length, PROT_READ,
				MAP_SHARED, f->file_descriptor, 0)) == MAP_FAILED)
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

/*----------------------------------------------------------------------
 * IsNewerN	Routine to return true if file 'f1' is newer than file
 *		'f2', and false otherwise.
 *----------------------------------------------------------------------*/

int IsNewerN(char *f1, char *f2)
{
    struct stat sbuf1, sbuf2;

    if (stat(f1, &sbuf1) == -1)
    {
        error("Failed to stat file: %s\n", f1);
    }
    if (stat(f2, &sbuf2) == -1)
    {
        error("Failed to stat file: %s\n", f2);
    }
    return(sbuf1.st_mtime > sbuf2.st_mtime);
}

/*----------------------------------------------------------------------
 * IsFile	Does the filename point to an actual file?
 *----------------------------------------------------------------------*/

int IsFile(char *f)
{
    struct stat sbuf;

    if (stat(f, &sbuf) == -1)	/* It doesn't exist at all */
    {
        return(false);
    }
    if (S_ISREG(sbuf.st_mode))
    {
	return(true);	/* Its a regular file */
    }
    return(false);	/* Its not a regular file, but does exists - link, directory... */
}

/*----------------------------------------------------------------------
 * IsDir	Does the filename point to a directory?
 *----------------------------------------------------------------------*/

int IsDir(char *f)
{
    struct stat sbuf;

    if (stat(f, &sbuf) == -1)	/* It doesn't exist at all */
    {
        return(false);
    }
    if (S_ISDIR(sbuf.st_mode))
    {
	return(true);	/* Its a directory */
    }
    return(false);	/* Its not a directory, but does exist - link, regular file... */
}

/*----------------------------------------------------------------------
 * IsExisting	Does the filename point to an existing file or directory?
 *----------------------------------------------------------------------*/

int IsExisting(char *f)
{
    struct stat sbuf;

    if (stat(f, &sbuf) == -1)	/* It doesn't exist at all */
    {
        return(false);
    }
    if (S_ISDIR(sbuf.st_mode) || S_ISREG(sbuf.st_mode) || S_ISLNK(sbuf.st_mode))
    {
	return(true);	/* It exists and is a file, directory or symlink */
    }
    return(false);	/* Its not a file, directory or symlink, but does exist - device, pipe, socket... */
}

/*----------------------------------------------------------------------
 * FileSize	Return the filesize if a regular file, and -1 otherwise
 *----------------------------------------------------------------------*/

int FileSize(char *f)
{
    struct stat sbuf;

    if (stat(f, &sbuf) == -1)	/* It doesn't exist at all */
    {
        return(-1);
    }
    if (S_ISREG(sbuf.st_mode))
    {
	return(sbuf.st_size);	/* Return file size */
    }
    return(-1);	/* Its not a regular file, so return -1 */
}

/*----------------------------------------------------------------------
 * ReadIntFromFile	Routine to read an integer value from a file
 *----------------------------------------------------------------------*/

int ReadIntFromFile(char *fname)
{
    FILE *f;
    char buf[100];

    bzero(buf, 100);
    f = fopen(fname, "r");
    fgets(buf, 100, f);
    fclose(f);

    return(atoi(buf));
}

/*----------------------------------------------------------------------
 * CreateDirectoryPath	Routine to create a whole directory path, creating
 *			parent components where necessary.
 *----------------------------------------------------------------------*/

void CreateDirectoryPath(char *pname)
{
    char *currentwd = NULL,
	*segment = NULL,
	*pathname;
    int KeepGoing = TRUE, j;
    struct stat sbuf;
    
    pathname = strdup(pname);	/* This is necessary because we are modifying 
				 * the string in place - and if it is sent in as a
				 * string constant, that doesn't work!!
				 */

    if (pathname == NULL)
    {
	return;
    }
    if (strlen(pathname) == 0)
    {
	return;
    }

    currentwd = getcwd(currentwd, 0);
    
    if (pathname[0] == '/')	/* Its an absolute pathname */
    {
	chdir("/");		/* Make the current directory the root dir */
	pathname++;		/* And skip past the leading '/' */
    }

    /*------------------------------------------------------------------
     * Loop through the segments of the path, picking off the first chunk,
     * making sure it exists (if not creating it), then iterating on to
     * next. Completes when no more '/' left in path...
     *------------------------------------------------------------------*/
    while (KeepGoing)
    {
	segment = pathname;
	pathname = strchr(pathname, '/');
	if (pathname == NULL)
	{
	    KeepGoing = FALSE;
	}
	else
	{
	    *pathname = '\0';	/* Replace the '/' with end of string character */
	    pathname++;		/* Position 'pathname' at the start of the next segment */
	}
	/* Now check whether 'segment' already exists, or needs created... */
	j = stat(segment, &sbuf);
	if (j == -1)
	{
	    /* Directory doesn't exist; create it */
	    mkdir(segment, 511);
	}
	else if ((sbuf.st_mode & S_IFMT) != S_IFDIR)
	{
	    error("A segment of the directory path to be created already exists, but is not a\n"
		  "directory. Segment is: '%s'\n", segment);
	}
	/* The fall through case of that 'if' clause is the segment already exists and is a 
	 * directory - so we can just 'chdir' into it, as if we'd just created it... */
	chdir(segment);
    }

    chdir(currentwd);
    free(currentwd);
}

/*----------------------------------------------------------------------
 * CopyFile	The equivalent of the command 'cp'...
 *----------------------------------------------------------------------*/

void CopyFile(char *src, char *dest)
{    
    int input, output;
    char buf[4096];
    ssize_t nread;

    if ((input = open(src, O_RDONLY)) == -1)
    {
        error("Can't open source file to copy: %s\n", src);
    }    
    if ((output = creat(dest, 0660)) == -1)
    {
        close(input);
        error("Can't creat destination file for copy: %s\n", dest);
    }

    while (nread = read(input, buf, sizeof buf), nread > 0)
    {
        char *out_ptr = buf;
        ssize_t nwritten;

        do
	{
            nwritten = write(output, out_ptr, nread);

            if (nwritten >= 0)
            {
                nread -= nwritten;
                out_ptr += nwritten;
            }
            else if (errno != EINTR)
            {
                error("Unknown error condition while copying\n");
            }
        }
	while (nread > 0);
    }
    if (nread != 0)
    {
	error("Error condition while copying\n");
    }
    
    if (close(output) < 0)
    {
	error("Failed to close output file descriptor on file copy\n");
    }
    close(input);
}

/*----------------------------------------------------------------------
 * CmpFile	The equivalent of the command 'cmp'... returns zero if 
 *		two files are identical.
 *----------------------------------------------------------------------*/

int CmpFile(char *src, char *dest)
{
    FileDes *Fsrc, *Fdest;
    int compared;
    
    Fsrc  = MapFile(src,  NULL);
    Fdest = MapFile(dest, NULL);

    if (Fsrc->length != Fdest->length)
    {
	compared = -1;
    }
    else
    {
	compared = bcmp(Fsrc->page, Fdest->page, Fsrc->length);
    }
    UnmapFile(Fdest);
    UnmapFile(Fsrc);
    return(compared);
}

/*----------------------------------------------------------------------*/
