/* from Data Compression Book 2nd Edition" */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include "domainModel/xArithCodec/errhand.h"

void fatal_error(char *fmt, ... ) /*char *fmt; on next line... */
{
  va_list argptr;

  va_start( argptr, fmt );
  printf( "Fatal error: " );
  vprintf( fmt, argptr );
  va_end( argptr );
  exit( -1 );
}
