/* from Data Compression Book 2nd Edition" */

#ifndef _ERRHAND_H
#define _ERRHAND_H

//#include "domainModel/global.hpp"

#ifdef __cplusplus
extern "C" {
#endif

void fatal_error( char *fmt, ... );

#ifdef __cplusplus
}
#endif

#endif
