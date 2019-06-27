/****************************************************************************
 *  Lists Library                                                           *
 ****************************************************************************
 * Written by George D. Sotirov                                             *
 * Begin date : 2002-08-22                                                  *
 * Modify date: 2003-06-03                                                  *
 * Version    : 0.1.0                                                       *
 * File       : lstlib.h            Type: header                            *
 * File desc. : Declarations of functions and classes.                      *
 * CVS Id     : $Id: liblst.h,v 1.2 2005/04/20 18:13:45 gsotirov Exp $
 ****************************************************************************/

#ifndef _LSTLIB_H
#define _LSTLIB_H

#ifndef __cplusplus
#error "This file requires C++ compiler!"
#endif

namespace LstLib {

void GetErrMsg(long, char *);

typedef struct ListItem {
    void *pData;
    ListItem *Next;
} TListItem;

/* Class  : CList
 * Purpose: Base class for lists like stack and queue.
 */
class CList {
protected:
    long count;
public:
    /* constructors */
    CList();
    /* get/set functions */
    virtual long GetCount(void) const;
    /* main functions */
    virtual int Push(void *)=0;
    virtual void * Pop(void)=0;
    virtual void * Get(void)=0;
    virtual void * Next(void)=0;
    virtual void Clear(void)=0;
    virtual bool IsEmpty(void)=0;
    virtual bool Have(void *)=0;
    /* destructor */
    virtual ~CList();
};

class CCollection;

/* Class  : CStack
 * Purpose: Class releasing a stack.
 */
class CStack : public CList {
private:
    void ClearStack(void);
protected:
    TListItem *pTop;
    TListItem *pCurElem;
    TListItem *pPrevElem;
    int Position(long);
    friend class CCollection;
public:
    /* constructors */
    CStack();
    /* main functions */
    int Push(void *);
    void * Pop(void);
    void * Get(void);
    void * Next(void);
    void Clear(void);
    bool IsEmpty(void);
    bool Have(void *);
    /* destructor */
    ~CStack();
};

/* Class  : CQueue
 * Purpose: Class releasing a queue.
 */
class CQueue : public CStack {
private:
    void ClearQueue(void);
protected:
    TListItem *pEnd;
protected:
    friend class CCollection;
public:
    /* constructors */
    CQueue();
    /* overrides */
    int Push(void *);
    void * Pop(void);
    void Clear(void);
    /* destructor */
    ~CQueue();
};

/* Class  : CCollection
 * Purpose: Class for collection of data pointers.
 */
class CCollection {
private:
    CQueue *pList;
public:
    /* constructors */
    CCollection();
    /* main functions */
    long GetCount(void);
    void * operator [](long);
    void * At(long);
    int Insert(void *);
    int Replace(void *, long);
    void * Remove(long);
    void Clear(void);
    bool IsEmpty(void);
    /* destructor */
    ~CCollection();
};

} /* namespace LSTLIB */

#endif /* lstlib.h */
