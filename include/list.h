#ifndef LIST_H_
#define LIST_H_

#include <stdlib.h>
#include <stdio.h>
#include <map.h>
#include <sprite.h>
#include <window.h>


struct list {
	void* data;
	int x, y;
	struct list* next;
};

// Create a new list
struct list* list_new();

// Return data
void* list_data(struct list* l);

// Insert data
struct list* list_insert_head(struct list* l, int x, int y, void* data);
struct list* list_insert_tail(struct list* l, int x, int y, void* data);

// Search an element in the list
struct list* list_find(struct list* l, int x, int y);

// Search an element and delete it
struct list* list_find_delete(struct list* l, int x, int y);

// Delete data
struct list* list_delete_head(struct list* l);
struct list* list_delete_tail(struct list* l);

// Delete an entire list
struct list* list_delete(struct list* l);


#endif
