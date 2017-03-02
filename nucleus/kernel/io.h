

#ifndef __IO_H__
#define __IO_H__

#include <stdarg.h>


void printf( const char *fmt, ... );
void vsprintf( char *buf, const char *fmt, va_list argp );

void cls( void );
void output_char( unsigned char ch );
void output_string( const char *str );

void init_basicio( void );

#endif
