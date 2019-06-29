/****************************************************************************
 *  Lists Library                                                           *
 ****************************************************************************
 * Copyright  : Georgi D. Sotirov <gdsotirov@gmail.com>                     *
 * Begin date : 2002-08-22                                                  *
 * Modify date: 2003-06-03                                                  *
 * Version    : 0.1.0                                                       *
 * File       : lstlib.cpp          Type: source                            *
 * File desc. : Definitions of error messages and codes.                    *
 ****************************************************************************/

/**
 * @file lsterrs.h
 * @brief Definitions of error messages and codes.
 */

#ifndef __LSTLIB_ERRORS_H
#define __LSTLIB_ERRORS_H

/* general errors */
/** @brief No error ID */
#define ERR_NOERROR                     0
/** @brief Cannot allocate memory error ID */
#define ERR_CNT_ALOC_MEM                1
/* list operation errors */
/** @brief List is empty error ID */
#define ERR_LST_EMPTY                   101
/** @brief Null pointer error ID */
#define ERR_NULL_ELEMENT                102
/** @brief Invalid index error ID */
#define ERR_INVLD_INDEX                 103

/** @brief No error string (empty string) */
#define ESTR_NOERROR                    ""
/** @brief Cannot allocate memory error string */
#define ESTR_CNT_ALOC_MEM               "Can't allocate memory!"
/** @brief List is empty error string */
#define ESTR_LST_EMPTY                  "List is empty!"
/** @brief Null pointer error string */
#define ESTR_NULL_ELEMENT               "Null pointer to element!"
/** @brief Invalid index error string */
#define ESTR_INVLD_INDEX                "Invalid index for the list!"

#endif

