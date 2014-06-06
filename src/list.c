#include <list.h>
#include <assert.h>

struct list* list_new()
{
	return NULL;
}

struct list* list_insert_head(struct list* l, int x, int y, void* data)
{
	struct list* tmp = malloc( sizeof(*tmp) );
	tmp->data = data;
	tmp->x = x;
	tmp->y = y;
	tmp->next = l;
    return tmp;
}

void* list_data(struct list* l)
{
	return l->data;
}

struct list* list_insert_tail(struct list* l, int x, int y, void* data)
{
	struct list* tmp = malloc( sizeof(*tmp) );
	tmp->data = data;
	tmp->x = x;
	tmp->y = y;
	tmp->next = NULL;

	if(l == NULL)
		return tmp;
	else{
		struct list* new = l;
		while(new->next != NULL){
			new = new->next;
		}
		new->next = tmp;
		return l;
	}
}


struct list* list_find(struct list* l, int x, int y)
{
	struct list* tmp = l;
	while(tmp != NULL)
	{
		if(tmp->x == x && tmp->y == y)
			return tmp;
		tmp = tmp->next;
	}
	return NULL;
}

struct list* list_find_delete(struct list* l, int x, int y)
{
	if(l == NULL)
	        return NULL;
	if(l->x == x && l->y == y){
	        struct list* tmp = l->next;
	        free(l);
	        tmp = list_find_delete(tmp, x, y);
	        return tmp;
	} else {
		l->next = list_find_delete(l->next, x, y);
		return l;
	}
}

struct list* list_delete_head(struct list* l)
{
	if(l != NULL){
		struct list* tmp = l->next;
		free(l);
		return tmp;
	}
	else {
		return NULL;
	}
}

struct list* list_delete_tail(struct list* l)
{
	if(l == NULL)
		return NULL;
	if(l->next == NULL){
		free(l);
		return NULL;
	}
	struct list* tmp = l;
	struct list* ptmp = l;
	while(tmp->next != NULL){
			ptmp = tmp;
			tmp = tmp->next;
	}
	ptmp->next = NULL;
	free(tmp);
	return l;
}

struct list* list_delete(struct list* l)
{
	if(l == NULL){
		return NULL;
	} else {
		struct list* tmp;
		tmp = l->next;
		free(l);
		return list_delete(tmp);
	}
}

