#include "../include/list.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "../include/util.h"
#include "../include/tree.h"


/********************************************************************
 * list_node_t
 ********************************************************************/

/**
 * @brief
 * Construit et initialise un nouveau nœud d'une liste doublement chaînée.
 * 
 * @param[in] data Donnée à affecter au nouveau nœud.
 * @return struct list_node_t* Le nouveau nœud créé.
 */
static struct list_node_t * new_list_node(void * data) {
	struct list_node_t * L = calloc(1, sizeof(struct list_node_t));
	assert(L);
	L->data = data;
	return L;

}

void * get_list_node_data(const struct list_node_t * node) {
	return node->data;
}

struct list_node_t * get_successor(const struct list_node_t* node) {
    return node->successor;
}

struct list_node_t * get_predecessor(const struct list_node_t * node) {
	return node->predecessor;
}

void set_list_node_data(struct list_node_t * node, void * newData) {
	node->data = newData;
}

void set_successor(struct list_node_t * node, struct list_node_t * newSucc) {
	node->successor = newSucc;
}

void set_predecessor(struct list_node_t * node, struct list_node_t * newPred) {
	node->predecessor = newPred;
}

/********************************************************************
 * list_t
 ********************************************************************/

struct list_t * new_list(void (*viewData)(const void*), void (*freeData)(void*)) {
	struct list_t * L = calloc(1, sizeof(struct list_t));
	assert(L);
	L->viewData = viewData;
	L->freeData = freeData;
	set_list_size(L,0);
	return L;
}

int list_is_empty(struct list_t * L) {
	if(L->numelm == 0)
	{
		return 1;
	}
	else 
	{
		return 0;
	}
}

int get_list_size(const struct list_t * L) {
	return L->numelm;
}

struct list_node_t * get_list_head(const struct list_t * L) {
	return L->head;
}

struct list_node_t * get_list_tail(const struct list_t * L) {
	return L->tail;
}

void increase_list_size(struct list_t * L) {
	L->numelm = L->numelm + 1;
}

void decrease_list_size(struct list_t * L) {
	L->numelm = L->numelm - 1;
}

void set_list_size(struct list_t * L, int newSize) {
	L->numelm = newSize;
}

void set_head(struct list_t * L, struct list_node_t * newHead) {
	L->head = newHead;
}

void set_tail(struct list_t * L, struct list_node_t * newTail) {
	L->tail = newTail;
}

void delete_list(struct list_t * L, int deleteData) {
	
	while(list_is_empty(L) != 1)
	{
		struct list_node_t * LN = get_list_head(L);
		void * data = list_remove_node(L,LN);
		if(deleteData && data != NULL)
		{
			L->freeData(data);
		}
		//printf("laaa?\n");

	}
	free(L);
	L = NULL;

}

void view_list(const struct list_t * L) {
	
	printf("[ ");
	struct list_node_t * E = get_list_head(L);
	for (E; E != NULL ; E = get_successor(E))
	{
		L->viewData(get_list_node_data(E));
	}
	printf("]\n\n");
}

void list_insert_first(struct list_t * L, void * data) {
	assert(L);
	struct list_node_t * N = new_list_node(data);
	if(list_is_empty(L) == 1)
	{
		set_tail(L,N);
		set_head(L,N);
	}
	else
	{
		set_successor(N,get_list_head(L));
		set_predecessor(get_list_head(L),N);
		set_head(L,N);
	}
	increase_list_size(L);
}

void list_insert_last(struct list_t * L, void * data) {
	assert(L);
	struct list_node_t * N = new_list_node(data);
	if(list_is_empty(L) == 1)
	{	
		
		set_tail(L,N);
		set_head(L,N);

	}
	else
	{
		set_predecessor(N,get_list_tail(L));
		set_successor(get_list_tail(L),N);
		set_tail(L,N);
	}
	increase_list_size(L);
}

void list_insert_after(struct list_t * L, void * data, struct list_node_t * ptrelm) {
	assert(L);
	if(list_is_empty(L) == 1 || !ptrelm)
	{
		list_insert_first(L,data);
		set_head(L,data);
	}
	else if (ptrelm == get_list_tail(L))
	{
		list_insert_last(L,data);
		set_tail(L,data);
	}
	else{
		struct list_node_t * E = get_list_head(L);
		struct list_node_t * ToInsert = new_list_node(data);
		while(E != ptrelm)
		{
			E = get_successor(E);
		}
		if(E == ptrelm)
		{
			set_predecessor(ToInsert,ptrelm);
			set_successor(ToInsert,get_successor(ptrelm));
			set_predecessor(get_successor(ptrelm),ToInsert);
			set_successor(ptrelm,ToInsert);
		}
	}
	increase_list_size(L);
}

void * list_remove_first(struct list_t * L) {
	assert(L);
	
	if ( !list_is_empty(L) )
	{
		struct list_node_t * Temp = get_list_head(L);
		if(get_successor(Temp) == NULL)
		{
			L->numelm = 0;
			set_head(L,NULL);
			set_tail(L,NULL);
		}
		else
		{
			increase_list_size(L);
			set_head(L,get_successor(get_list_head(L)));
			set_predecessor(get_list_head(L),NULL);
		}
	
		return get_list_node_data(Temp);
		
	}
	else
	{
		printf("Erreur : La liste ne peut pas être vide");
		return NULL;
	}
	

}

void * list_remove_last(struct list_t * L) {
	assert(L);
	if ( !list_is_empty(L) )
	{
		struct list_node_t * Temp = get_list_tail(L);
		if(get_predecessor(Temp) == NULL)
		{
			L->numelm = 0;
			set_head(L,NULL);
			set_tail(L,NULL);
		}
		else
		{
			set_tail(L,get_predecessor(get_list_tail(L)));
			set_successor(get_list_tail(L),NULL);
			set_predecessor(Temp,NULL);
			return Temp;
		}
		return get_list_node_data(Temp);
	}
	else
	{
		printf("Erreur : La liste ne peut pas être vide");
		return NULL;
	}
}

void * list_remove_node(struct list_t * L, struct list_node_t * node) {
	assert(L);	
	void * data = get_list_node_data(node);
	if(node == get_list_head(L))
	{
		set_head(L,get_successor(node));
	}
	if(node == get_list_tail(L))
	{		

		set_tail(L,get_predecessor(node));
	}
	if(get_predecessor(node) != NULL)
	{
		set_successor(get_predecessor(node),get_successor(node));
	}
	if(get_successor(node) != NULL)
	{
		set_predecessor(get_successor(node),get_predecessor(node));
	}

	free(node);
	node = NULL;
	decrease_list_size(L);
	//L->numelm = L->numelm-1;
	return data;
}