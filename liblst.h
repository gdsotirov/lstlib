/****************************************************************************
 *  Lists Library                                                           *
 ****************************************************************************
 * Copyright  : Georgi D. Sotirov <gdsotirov@gmail.com>                     *
 * Begin date : 2002-08-22                                                  *
 * Modify date: 2003-06-03                                                  *
 * Version    : 0.1.0                                                       *
 * File       : lstlib.h            Type: header                            *
 * File desc. : Declarations of functions and classes.                      *
 ****************************************************************************/

/**
 * @file liblst.h
 * @brief Declarations of functions and classes.
 */

#ifndef _LSTLIB_H
#define _LSTLIB_H

#ifndef __cplusplus
#error "This file requires C++ compiler!"
#endif

namespace LstLib {

void GetErrMsg(long, char *);

/** @brief List item */
typedef struct ListItem {
    void *pData;    /**< Data pointer */
    ListItem *Next; /**< Next item pointer */
} TListItem;

/**
 * @brief Base class for lists like stack and queue.
 */
class CList {
protected:
    /** @brief Number of elements in the list */
    long count;
public:
    /* constructors */
    CList();
    /* get/set functions */
    virtual long GetCount(void) const;
    /* main functions */
    /** @brief Must be implemented to push element to the list */
    virtual int Push(void *)=0;
    /** @brief Must be implemented to pop element from the list */
    virtual void * Pop(void)=0;
    /** @brief Must be implemented to get element from the list */
    virtual void * Get(void)=0;
    /** @brief Must be implemented to get next element in the list */
    virtual void * Next(void)=0;
    /** @brief Must be implemented to clear the list by removing all
     * elements */
    virtual void Clear(void)=0;
    /** @brief Must be implemented to checks whether list is empty */
    virtual bool IsEmpty(void)=0;
    /** @brief Must be implemented to check whether an element is present in
     * the list */
    virtual bool Have(void *)=0;
    /* destructor */
    virtual ~CList();
};

class CCollection;

/**
 * @brief Class implementing stack.
 *
 * Stack organization is First In First Out (FIFO).
 */
class CStack : public CList {
private:
    void ClearStack(void);
protected:
    /** @brief Pointer to the element at the top of the stack */
    TListItem *pTop;
    /**
     * @brief Pointer to the current element in the stack
     *
     * Used when iterating the stack.
     */
    TListItem *pCurElem;
    /**
     * @brief Pointer to the previous element in the stack
     *
     * Used when iterating the stack.
     */
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

/**
 * @brief Class implementing queue.
 *
 * Queue organization is First In Last Out (FILO).
 */
class CQueue : public CStack {
private:
    void ClearQueue(void);
protected:
    /** @brief Pointer to the end of the queue */
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

/**
 * @brief A class for collection of data pointers
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
