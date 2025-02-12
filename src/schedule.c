#include "../include/schedule.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>

#include "../include/util.h"
#include "../include/list.h"
#include "../include/instance.h"

/********************************************************************
 * schedule_node_t
 ********************************************************************/

/**
 * @brief Construire et initialiser un nouveau nœud d'un ordonnancement.
 * 
 * @param[in] task 
 * @param[in] bt 
 * @param[in] et 
 * @return struct schedule_node_t* 
 */
static struct schedule_node_t * new_schedule_node(struct task_t * task, unsigned long bt, unsigned long et) {
	assert(bt < et);
	struct schedule_node_t * N = calloc(1,sizeof(struct schedule_node_t));
	N->task = task;
	set_schedule_node_begin_time(N,bt);
	set_schedule_node_end_time(N,et);
	return N;
	// A FAIRE
}

struct task_t * get_schedule_node_task(const struct schedule_node_t * snode) {
	// A FAIRE
	return snode->task;
}

unsigned long get_schedule_node_begin_time(const struct schedule_node_t * snode) {
	// A FAIRE
	return snode->begin_time;
}

unsigned long get_schedule_node_end_time(const struct schedule_node_t * snode) {
	// A FAIRE
	return snode->end_time;
}

void set_schedule_node_begin_time(struct schedule_node_t * snode, unsigned long new_bt) {
	// A FAIRE
	snode->begin_time = new_bt;
}

void set_schedule_node_end_time(struct schedule_node_t * snode, unsigned long new_et) {
	// A FAIRE
	snode->end_time = new_et;
}

void view_schedule_node(const void * snode) {
	// A FAIRE

	view_task(get_schedule_node_task(snode));
	printf("Debut de l'execution est  :%lu\n",get_schedule_node_begin_time(snode));
	printf("Fin de l'execution est : %lu\n",get_schedule_node_end_time(snode));
	printf("\n");
}

void delete_schedule_node(void * snode) {
	// A FAIRE
	struct schedule_node_t * N = (struct schedule_node_t *)snode;
	free(N);
	N = NULL;
}

/********************************************************************
 * schedule_t
 ********************************************************************/

struct schedule_t * new_schedule(int num_m) {
	assert(num_m >= 1);
	// A FAIRE
	struct schedule_t * S = calloc(1,sizeof(struct schedule_t));
	S->schedule = calloc(num_m,sizeof(struct list_t));
	for(int i = 0; i < num_m;i++)
	{
		S->schedule[i] = new_list(view_schedule_node,delete_schedule_node);
	}
	S->num_machines = num_m;
	return S;
}

struct list_t * get_schedule_of_machine(const struct schedule_t * S, const int machine) {
	// A FAIRE
	return S->schedule[machine];
}

int get_num_machines(const struct schedule_t * S) {
	// A FAIRE
	return S->num_machines;
}

void view_schedule(const struct schedule_t * S) {
	// A FAIRE
	for(int i = 0;i < get_num_machines(S);i++)
	{
		struct list_t * L = get_schedule_of_machine(S,i);
		//printf("Machine numero : M%d\n",i+1);
		view_list(L);

	}
	printf("\n");

}

void delete_schedule(struct schedule_t * S) {
	// A FAIRE
	for(int i = 0; i<get_num_machines(S);i++)
	{
		struct list_t * L = get_schedule_of_machine(S,i);
		delete_list(L,1);
	}
	free(S->schedule);
	free(S);
	S = NULL;
}

// Pour le format du fichier à créer, regardez dans la présentation du cours.
void save_schedule(struct schedule_t * S, char * filename) {
	// A FAIRE
	FILE * fichier = fopen(filename,"w");
	if(fichier==NULL)
	{
		printf("Erreur ouverture\n");
		exit(1);
	}
	fprintf(fichier,"%d\n",get_num_machines(S));
	for(int i =0; i< get_num_machines(S);i++)
	{
		fprintf(fichier,"M%d\n",i);
		struct list_t * L = get_schedule_of_machine(S,i);
		struct list_node_t * ListNode = get_list_head(L);
		while(ListNode != NULL)
		{
			struct schedule_node_t * ScheduleNode = get_list_node_data(ListNode);
			view_schedule_node(ScheduleNode);
			if(get_successor(ListNode) == NULL && i+1 ==get_num_machines(S))
			{
				fprintf(fichier,"%lu %lu %s\0",get_schedule_node_begin_time(ScheduleNode),get_schedule_node_end_time(ScheduleNode),get_task_id(get_schedule_node_task(ScheduleNode)));

			}
			else
			{
				fprintf(fichier,"%lu %lu %s\n",get_schedule_node_begin_time(ScheduleNode),get_schedule_node_end_time(ScheduleNode),get_task_id(get_schedule_node_task(ScheduleNode)));

			}
			ListNode = get_successor(ListNode);
		}
	}
	/*
	long int pos;
	fseek(fichier, -1, SEEK_END);
    while(fgetc(fichier) != '\n') {
        fseek(fichier, -2, SEEK_CUR);
    }

    pos = ftell(fichier);
    fseek(fichier, pos, SEEK_SET);
    ftruncate(fileno(fichier), pos);
*/
	fclose(fichier);
}


int find_empty_machine(struct schedule_t * S, unsigned long time) {
	// A FAIRE
	int num_machine = get_num_machines(S);
	for(int i = 0; i < num_machine;i++)
	{

		struct list_t * L = get_schedule_of_machine(S,i);
		if(list_is_empty(L) == 1)
		{
			return i;
		}
		struct list_node_t * ListNode = get_list_tail(L);
	
		struct schedule_node_t * N = get_list_node_data(ListNode);
		/*
		printf("HEEEELAAA \n");
		printf("%lu\n",get_schedule_node_end_time(N));
		printf("%lu\n",time);
		*/
		if(N == NULL || get_schedule_node_end_time(N) <= time)
		{
			return i;
		}
	}
	return -1;
}

int find_machine_to_interrupt(struct schedule_t * S, unsigned long time, unsigned long processing_time) {
	// A FAIRE
	int num_machine = get_num_machines(S);
	int min = -1;
	unsigned long min_remaining = ULONG_MAX;
	for(int i = 0;i < num_machine;i++)
	{
		struct list_t * L = get_schedule_of_machine(S,i);
		struct list_node_t * LN = get_list_tail(L);
		struct schedule_node_t * N = get_list_node_data(LN);
		struct task_t * task = get_schedule_node_task(N);
		unsigned long remaining = (get_task_release_time(task) + get_task_processing_time(task) ) - time;
		//if(time - get_schedule_node_begin_time(N) >= processing_time )//&& remaining < min_remaining)
		if(remaining > processing_time && remaining < min_remaining)
		{
			min = i;
			//return i;
			min_remaining = remaining;
		}
	}
	return min;

}

void add_task_to_schedule(struct schedule_t * S, struct task_t * task, int machine, unsigned long bt, unsigned long et) {
	// A FAIRE
	struct schedule_node_t * N = new_schedule_node(task,bt,et);
	if(list_is_empty(get_schedule_of_machine(S,machine)))
	{
		list_insert_first(get_schedule_of_machine(S,machine),N);
	}
	else
	{
		list_insert_last(get_schedule_of_machine(S,machine),N);
	}
}

unsigned long preempt_task(struct schedule_t * S, int machine, unsigned long new_et) {
	// A FAIRE
	struct list_node_t * tail_node = get_list_tail(get_schedule_of_machine(S,machine));
    struct schedule_node_t * der_node = get_list_node_data(tail_node);
	struct task_t * task = get_schedule_node_task(der_node);
    unsigned long old_et = get_schedule_node_end_time(der_node);
    set_schedule_node_end_time(der_node, new_et);
    return get_schedule_node_end_time(der_node);
}

unsigned long get_makespan(struct schedule_t * S) {
	// A FAIRE
	unsigned long makespan = 0;
    struct list_node_t * tail_node;
    struct schedule_node_t * last_node;

    for (int i = 0; i < get_num_machines(S); i++) {
        tail_node = get_list_tail(get_schedule_of_machine(S,i));
        if (tail_node != NULL) {
            last_node = get_list_node_data(tail_node);
            if (get_schedule_node_end_time(last_node) > makespan) {
                makespan = get_schedule_node_end_time(last_node);
            }
        }
    }
    return makespan;
}