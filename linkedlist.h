#ifndef __LIST_H
#define __LIST_H
 
// a common function used to free malloc'd objects
typedef void (*freeFunction)(void *);
 
typedef enum { FALSE, TRUE } bool;
 
typedef bool (*listIterator)(void *);
 
typedef struct _listNode {
  void *data;
  struct _listNode *next;
  struct _listNode *prev;
} listNode;
 
typedef struct {
  unsigned int logicalLength;
  size_t elementSize;
  listNode *head;
  listNode *tail;
  freeFunction freeFn;
} list;
 
void list_new(list *list, size_t elementSize, freeFunction freeFn);
void list_destroy(list *list);
 
void list_prepend(list *list, void *element);
void list_append(list *list, void *element);
unsigned int list_size(list *list);
 
void list_for_each(list *list, listIterator iterator);
void list_head(list *list, void *element, bool removeFromList);
void list_tail(list *list, void *element, bool removeFromList);
 
#endif