/****************************************************************************
 *  Lists Library                                                           *
 ****************************************************************************
 * Copyright  : Georgi D. Sotirov <gdsotirov@gmail.com>                     *
 * Begin date : 2002-08-22                                                  *
 * Modify date: 2003-06-03                                                  *
 * Version    : 0.1.0                                                       *
 * File       : lstlib.cpp          Type: source                            *
 * File desc. : Definitions of functions and classes.                       *
 ****************************************************************************/

#include <stdio.h>
#include <string.h>

#include "lsterrs.h"
#include "liblst.h"

void LstLib::GetErrMsg(long errno, char *errstr) {
    switch ( errno ) {
        case ERR_NOERROR:
            sprintf(errstr, "lstlib: %s", ESTR_NOERROR);
            break;
        case ERR_CNT_ALOC_MEM:
            sprintf(errstr, "lstlib: %s", ESTR_CNT_ALOC_MEM);
            break;
        case ERR_LST_EMPTY:
            sprintf(errstr, "lstlib: %s", ESTR_LST_EMPTY);
            break;
        case ERR_NULL_ELEMENT:
            sprintf(errstr, "lstlib: %s", ESTR_NULL_ELEMENT);
            break;
        case ERR_INVLD_INDEX:
            sprintf(errstr, "lstlib: %s", ESTR_INVLD_INDEX);
            break;
        default:
            sprintf(errstr, "lstlib: Unknown\n");
            break;
    }
}

/****************************************************************************
 * Class CList implementation                                               *
 ****************************************************************************/

LstLib::CList::CList() {
    count = 0;
}

long LstLib::CList::GetCount(void) const {
    return count;
}

LstLib::CList::~CList() {
}

/****************************************************************************
 * Class CStack implementation                                              *
 ****************************************************************************/

LstLib::CStack::CStack() {
    pTop      = NULL;
    pCurElem  = NULL;
    pPrevElem = NULL;
}

/* Function: CStack::Push
 * Purpose : Push element at the top of the stack.
 * Input   : Pointer to the element to push.
 * Return  : Null on successful operation or not null otherwise.
 */
int LstLib::CStack::Push(void *pData) {
    if ( pData != NULL ) {
        LstLib::TListItem *pNewItem = new TListItem;
        if ( pNewItem != NULL ) {
            pNewItem->pData = pData;
            pNewItem->Next = pTop;
            pTop = pNewItem;
            count++;
            return ERR_NOERROR;
        }
        else return ERR_CNT_ALOC_MEM;
    }
    else return ERR_NULL_ELEMENT;
}

/* Function: CStack::Pop
 * Purpose : Pop element from the top of the stack.
 * Return  : Pointer to element at the top.
 */
void * LstLib::CStack::Pop(void) {
    void *pData = NULL;
    if ( pTop != NULL ) {
        TListItem *pItem = pTop;
        pData = pItem->pData;
        pTop = pTop->Next;
        delete pItem;
        count--;
    }
    return pData;
}

/* Function: CStack::Get
 * Purpose : Get pointer to element at the top of the stack.
 */
void * LstLib::CStack::Get(void) {
    pPrevElem = NULL;
    pCurElem = pTop;
    if ( pCurElem != NULL )
        return pCurElem->pData;
    else return NULL;
}

/* Function: CStack::Next
 * Purpose : Get pointer to next element in the stack.
 */
void * LstLib::CStack::Next(void) {
    pPrevElem = pCurElem;
    pCurElem = pCurElem->Next;
    if ( pCurElem != NULL )
        return pCurElem->pData;
    else return NULL;
}

/* Function: CStack::Position
 * Purpose : Position the list pointers at element with specific index.
 * Return  : Function always return 0.
 */
int LstLib::CStack::Position(long index) {
    long ix = 0;
    Get();
    while ( ix < index ) {
        ix++;
        Next();
    }
    return 0;
}

/* Function: CStack::Clear
 * Purpose : Clear contents of the stack.
 */
void LstLib::CStack::Clear(void) {
    ClearStack();
}

/* Function: CStack::ClearStack
 * Purpose : Pop all elements from the stack
 */
void LstLib::CStack::ClearStack(void) {
    while ( pTop != NULL )
        Pop();
}

/* Function: CStack::IsEmpty
 * Purpose : Check for empty stack.
 */
bool LstLib::CStack::IsEmpty(void) {
    return (pTop == NULL);
}

/* Function: CStack::Have
 * Purpose : Check if element is presented in the stack.
 */
bool LstLib::CStack::Have(void *pData) {
    TListItem *pIndex = pTop;
    while ( pIndex != NULL ) {
        if ( pIndex->pData == pData )
            return true;
    }
    return false;
}

LstLib::CStack::~CStack() {
    ClearStack();
}

/****************************************************************************
 * Class CQueue implementation                                              *
 ****************************************************************************/

LstLib::CQueue::CQueue() {
    pEnd = NULL;
}

/* Function: CQueue::Push
 * Purpose : Push element at the end of the queue.
 * Input   : Pointer to the element to push.
 * Return  : Error code for the operation.
 */
int LstLib::CQueue::Push(void *pData) {
    if ( pData != NULL ) {
        LstLib::TListItem *pNewItem = new TListItem;
        if ( pNewItem != NULL ) {
            pNewItem->pData = pData;
            pNewItem->Next = NULL;
            if ( pTop != NULL ) {
                pEnd->Next = pNewItem;
                pEnd = pNewItem;
            }
            else {
                pTop = pNewItem;
                pEnd = pNewItem;
            }
            count++;
            return ERR_NOERROR;
        }
        else return ERR_CNT_ALOC_MEM;
    }
    else return ERR_NULL_ELEMENT;
}

/* Function: CQueue::Pop
 * Purpose : Pop element from the top of the queue.
 * Return  : Pointer to element at the top.
 */
void * LstLib::CQueue::Pop(void) {
    void *pData = NULL;
    if ( pTop != NULL ) {
        LstLib::TListItem *pItem = pTop;
        pData = pTop->pData;
        pTop = pTop->Next;
        delete pItem;
        count--;
    }
    return pData;
}

void LstLib::CQueue::Clear(void) {
    ClearQueue();
}

void LstLib::CQueue::ClearQueue(void) {
    while ( pTop != NULL )
        Pop();
    pEnd = NULL;
}

LstLib::CQueue::~CQueue() {
    ClearQueue();
}

/****************************************************************************
 * Class CCollection implementation                                         *
 ****************************************************************************/

LstLib::CCollection::CCollection() {
    pList = NULL;
}

/* Function: CCollection::GetCount
 * Purpose : Retrive count of element in the collection.
 */
long LstLib::CCollection::GetCount(void) {
    if ( pList != NULL )
        return pList->GetCount();
    else return 0;
}

/* Function: CCollectoin::Insert
 * Purpose : Insert element in the collection.
 */
int LstLib::CCollection::Insert(void *pData) {
    if ( pList == NULL )
        pList = new CQueue();
    if ( pList != NULL )
        return pList->Push(pData);
    else return ERR_CNT_ALOC_MEM;
}

/* Function: CCollection::Replace
 * Purpose : Replace element at the specified index.
 */
int LstLib::CCollection::Replace(void *pData, long index) {
    if ( pList != NULL ) {
        if ( !pList->IsEmpty() ) {
            if ( (index >= 0) && (index < pList->count) ) {
                pList->Position(index);
                if ( pList->pCurElem != NULL ) {
                    pList->pCurElem->pData = pData;
                    return ERR_NOERROR;
                }
            }
            return ERR_INVLD_INDEX;
        }
    }
    return ERR_LST_EMPTY;
}

/* Function: CCollection::Remove
 * Purpose : Remove element at specified index from the collection.
 * Return  : NULL if element can't be removed or error ocured else pointer
 *           to the removed element data.
 */
void * LstLib::CCollection::Remove(long index) {
    void *pData = NULL;
    if ( pList != NULL ) {
        if ( index == 0 ) {
            pData = pList->Pop();
            pList->Get();
        }
        if ( (index > 0) && (index < pList->count) ) {
            pList->Position(index);
            if ( (pList->pCurElem != NULL) && (pList->pPrevElem != NULL) ) {
                pData = pList->pCurElem->pData;
                pList->pPrevElem->Next = pList->pCurElem->Next;
                if ( pList->pPrevElem->Next == NULL )
                    pList->pEnd = pList->pPrevElem;
                delete pList->pCurElem;
                pList->Get();
            }
        }
    }
    return pData;
}

/* Function: CCollection::At
 * Purpose : Extract element at specified index.
 *           This function is just a shell over the operator [].
 */
void * LstLib::CCollection::At(long index) {
    return operator [](index);
}

/* Function: CCollection::operator []
 * Purpose : Operation for indexing the collection.
 */
void * LstLib::CCollection::operator [](long index) {
    void *pData = NULL;
    if ( pList != NULL ) {
        if ( (index >= 0) && (index < pList->count) ) {
            pList->Position(index);
            if ( pList->pCurElem != NULL )
                pData = pList->pCurElem->pData;
        }
    }
    return pData;
}

/* Function: CCollection::Clear
 * Purpose : Remove all elements from the collection.
 */
void LstLib::CCollection::Clear(void) {
    if ( pList != NULL )
        pList->Clear();
}


bool LstLib::CCollection::IsEmpty(void) {
    if ( pList != NULL )
        return pList->IsEmpty();
    else return false;
}

LstLib::CCollection::~CCollection() {
    if ( pList != NULL )
        delete pList;
}

