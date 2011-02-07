/* Copyright 2011 Ian Sproates <ian@sproates.net> */

#ifndef LIST_H
#define LIST_H

/**
 * @file list.h
 * A doubly-linked list.
 */

/* public structure definitions */

/**
 * Represents a node in a doubly-linked list that has absolutely no type safety.
 */
struct _list {

  /**
   * The data associated with the node.
   */
  void * data;

  /**
   * The previous node in the list. Zero if this node is the head.
   */
  struct _list * prev;

  /**
   * The next node in the list. Zero if this is the tail.
   */
  struct _list * next;
};

/**
 * Represents a node in a doubly-linked list.
 */
typedef struct _list list;

/* public function prototypes */

/**
 * Construct a list with the given data item.
 * @param data The data.
 * @return The constructed list on success, zero on failure.
 */
list * list_new(void * data);

/**
 * Destructs a list. Does not free the associated data.
 * @param x The list to destroy.
 */
void list_del(list * x);

/**
 * Prepend one list to another.
 * @param x The list to prepend to.
 * @param y The list to prepend from.
 * @return The modified list.
 */
list * list_prepend(list * x, list * y);

/**
 * Append one list to another.
 * @param x The list to append to.
 * @param y The list to append from.
 * @return The modified list.
 */
list * list_append(list * x, list * y);

/**
 * Remove a node from a list.
 * @param x The list.
 * @param y The node to remove.
 * @return The modified list.
 */
list * list_remove(list * x, list * y);

/**
 * Get the head node in a list.
 * @param x The list.
 * @return The head node of the list.
 */
list * list_head(list * x);

/**
 * Get the tail node in a list.
 * @param x The list.
 * return The tail node of the list.
 */
list * list_tail(list * x);

/**
 * Get the number of items in a list.
 * @param x The list.
 * @return The number of items in the list.
 */
unsigned int list_size(list * x);

/**
 * Get the number of list nodes that have been allocated.
 * @return The number of allocated list nodes.
 */
unsigned int list_get_allocated(void);

/**
 * Get the number of list nodes that have been freed.
 * @return The number of freed list nodes.
 */
unsigned int list_get_freed(void);

#endif
