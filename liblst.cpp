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

/**
 * @brief Gets error message string
 *
 * Write the corresponding to the error code error message into the character
 * buffer pointed by the second parameter.
 * @param errno Error number.
 * @param errstr Error string.
 */
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

/**
 * @brief Default constructor
 *
 * Initializes empty list.
 */
LstLib::CList::CList() {
    count = 0;
}

/**
 * @brief Retrieves the number of items in the list
 */
long LstLib::CList::GetCount(void) const {
    return count;
}

/**
 * @brief Destructor
 *
 * Does noting.
 */
LstLib::CList::~CList() {}

/****************************************************************************
 * Class CStack implementation                                              *
 ****************************************************************************/

/**
 * @brief Default constructor
 *
 * Initializes empty stack.
 */
LstLib::CStack::CStack() {
    pTop      = NULL;
    pCurElem  = NULL;
    pPrevElem = NULL;
}

/**
 * @brief Pushes element at the top of the stack
 * @param pData Pointer to the element to push.
 * @return Zero on successful operation, non-zero otherwise.
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

/**
 * @brief Pops element from the top of the stack
 * @return Pointer to the element at the top of the stack.
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

/**
 * @brief Gets pointer to the element at the top of the stack
 * @return Pointer to the element at the top of the stack.
 */
void * LstLib::CStack::Get(void) {
    pPrevElem = NULL;
    pCurElem = pTop;
    if ( pCurElem != NULL )
        return pCurElem->pData;
    else return NULL;
}

/**
 * @brief Gets pointer to next element in the stack
 * @return Pointer to the next element in the stack.
 */
void * LstLib::CStack::Next(void) {
    pPrevElem = pCurElem;
    pCurElem = pCurElem->Next;
    if ( pCurElem != NULL )
        return pCurElem->pData;
    else return NULL;
}

/**
 * @brief Positions the stack at element with given index
 * @param index Numeric element index.
 * @return Always zero.
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

/**
 * @brief Clears all elements from the stack
 */
void LstLib::CStack::Clear(void) {
    ClearStack();
}

/**
 * @brief Pops all elements from the stack
 */
void LstLib::CStack::ClearStack(void) {
    while ( pTop != NULL )
        Pop();
}

/**
 * @brief Checks for empty stack
 * @return True if stack is empty, false otherwise.
 */
bool LstLib::CStack::IsEmpty(void) {
    return (pTop == NULL);
}

/**
 * @brief Checks if element is present in the stack
 * @param pData Pointer to element.
 * @return True if element is present, false otherwise.
 */
bool LstLib::CStack::Have(void *pData) {
    TListItem *pIndex = pTop;
    while ( pIndex != NULL ) {
        if ( pIndex->pData == pData )
            return true;
    }
    return false;
}

/**
 * @brief Destructor
 *
 * Clears all elements from the stack.
 */
LstLib::CStack::~CStack() {
    ClearStack();
}

/****************************************************************************
 * Class CQueue implementation                                              *
 ****************************************************************************/

/**
 * @brief Default constructor
 *
 * Initializes empty queue.
 */
LstLib::CQueue::CQueue() {
    pEnd = NULL;
}

/**
 * @brief Pushes element at the end of the queue
 * @param pData Pointer to an element to push.
 * @return Error code for the operation. Could be translated to message
 * with LstLib::GetErrMsg function.
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

/**
 * @brief Pops element from the top of the queue
 * @return Pointer to element at the top.
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

/**
 * @brief Clears all element from the queue
 */
void LstLib::CQueue::Clear(void) {
    ClearQueue();
}

/**
 * @brief Pops all elements from the queue
 */
void LstLib::CQueue::ClearQueue(void) {
    while ( pTop != NULL )
        Pop();
    pEnd = NULL;
}

/**
 * @brief Destructor
 *
 * Clears all elements from the queue.
 */
LstLib::CQueue::~CQueue() {
    ClearQueue();
}

/****************************************************************************
 * Class CCollection implementation                                         *
 ****************************************************************************/

/**
 * @brief Default constructor
 *
 * Initializes empty collection.
 */
LstLib::CCollection::CCollection() {
    pList = NULL;
}

/**
 * @brief Retrieves the count of element in the collection
 *
 * If collection is empty returns zero.
 * @return Number of elements.
 */
long LstLib::CCollection::GetCount(void) {
    if ( pList != NULL )
        return pList->GetCount();
    else return 0;
}

/**
 * @brief Inserts element in the collection
 * @param pData Pointer to the element.
 * @return Error code. Could be translated to message with
 * LstLib::GetErrMsg function.
 */
int LstLib::CCollection::Insert(void *pData) {
    if ( pList == NULL )
        pList = new CQueue();
    if ( pList != NULL )
        return pList->Push(pData);
    else return ERR_CNT_ALOC_MEM;
}

/**
 * @brief Replaces element at given index.
 * @param pData Pointer to the new element.
 * @param index Index of the element to replace.
 * @return Error code. Could be translated to message with
 * LstLib::GetErrMsg function.
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

/**
 * @brief Removes element at given index
 * @param index Index of the element to remove.
 * @return NULL if the element cannot be removed or if error cured, else
 * pointer to the removed element.
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

/**
 * @brief Extracts element at given index
 *
 * This function is an alias for operator [].
 * @param index Index of the element to extract.
 * @return
 */
void * LstLib::CCollection::At(long index) {
    return operator [](index);
}

/**
 * @brief Operator for indexing the collection
 *
 * @param index Index of the element.
 * @return Pointer to the element at the given index.
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

/**
 * @brief Removes all elements from the collection
 */
void LstLib::CCollection::Clear(void) {
    if ( pList != NULL )
        pList->Clear();
}

/**
 * @brief Checks whether collection is empty or not.
 * @return True if empty, false otherwise.
 */
bool LstLib::CCollection::IsEmpty(void) {
    if ( pList != NULL )
        return pList->IsEmpty();
    else return false;
}

/**
 * @brief Destructor
 *
 * Removes all elements from the collection if not empty.
 */
LstLib::CCollection::~CCollection() {
    if ( pList != NULL )
        delete pList;
}

