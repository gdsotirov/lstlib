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

