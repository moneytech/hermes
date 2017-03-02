/* This is file FOPEN.C */
/* This file may have been modified by DJ Delorie (Jan 1991).  If so,
** these modifications are Coyright (C) 1991 DJ Delorie, 24 Kirsten Ave,
** Rochester NH, 03867-2954, USA.
*/

/*
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 */

#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "@(#)fopen.c	5.2 (Berkeley) 3/9/86";
#endif LIBC_SCCS and not lint

#include <sys/types.h>
#include <sys/file.h>
#include <stdio.h>

FILE *
fopen(file, mode)
	const char *file;
	register const char *mode;
{
	register FILE *iop;
	register f, rw, oflags;
	extern FILE *_findiop();
	char tbchar;

	iop = _findiop();
	if (iop == NULL)
		return (NULL);

	rw = (mode[1] == '+');

	switch (*mode) {
	case 'a':
		oflags = O_CREAT | (rw ? O_RDWR : O_WRONLY);
		break;
	case 'r':
		oflags = rw ? O_RDWR : O_RDONLY;
		break;
	case 'w':
		oflags = O_TRUNC | O_CREAT | (rw ? O_RDWR : O_WRONLY);
		break;
	default:
		return (NULL);
	}
	if (mode[1] == '+')
		tbchar = mode[2];
	else
		tbchar = mode[1];
	if (tbchar == 't')
		oflags |= O_TEXT;
	else if (tbchar == 'b')
		oflags |= O_BINARY;
	else
		oflags |= (_fmode & (O_TEXT|O_BINARY));

	f = open(file, oflags, 0666);
	if (f < 0)
		return (NULL);

	if (*mode == 'a')
		lseek(f, (off_t)0, L_XTND);

	iop->_cnt = 0;
	iop->_file = f;
	iop->_bufsiz = 0;
	if (rw)
		iop->_flag = _IORW;
	else if (*mode == 'r')
		iop->_flag = _IOREAD;
	else
		iop->_flag = _IOWRT;
	if (oflags & O_TEXT)
		iop->_flag |= _IOTEXT;

	iop->_base = iop->_ptr = NULL;
	return (iop);
}
