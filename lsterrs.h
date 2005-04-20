/****************************************************************************
 *  Lists Library                                                           *
 ****************************************************************************
 * Written by George D. Sotirov                                             *
 * Begin date : 2002-08-22                                                  *
 * Modify date: 2003-06-03                                                  *
 * Version    : 0.1.0                                                       *
 * File       : lstlib.cpp          Type: source                            *
 * File desc. : Definitions of error messages and codes.                    *
 * CVS Id     : $Id: lsterrs.h,v 1.2 2005/04/20 18:13:45 gsotirov Exp $
 ****************************************************************************/

#ifndef __LSTLIB_ERRORS_H
#define __LSTLIB_ERRORS_H

/* general errors */
#define ERR_NOERROR                     0
#define ERR_CNT_ALOC_MEM                1
/* list operation errors */
#define ERR_LST_EMPTY                   101
#define ERR_NULL_ELEMENT                102
#define ERR_INVLD_INDEX                 103

#define ESTR_NOERROR                    ""
#define ESTR_CNT_ALOC_MEM               "Can't allocate memory!"
#define ESTR_LST_EMPTY                  "List is empty!"
#define ESTR_NULL_ELEMENT               "Null pointer to element!"
#define ESTR_INVLD_INDEX                "Invalid index for the list!"

#endif

