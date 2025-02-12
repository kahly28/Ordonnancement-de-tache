#include "../include/algo.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <limits.h>

#include "../include/util.h"
#include "../include/list.h"
#include "../include/tree.h"
#include "../include/instance.h"
#include "../include/schedule.h"

/********************************************************************
 * event_key_t
 ********************************************************************/

/**
 * @brief 
 * Une structure qui definit la clé de l'ensemble des événements.
 */
struct event_key_t {
	int event_type; // 0 si l'événement correspond à la libération d'une tâche,
					// 1 si l'événement correspond à la fin d'exécution d'une tâche
	unsigned long event_time;
	unsigned long processing_time; // par convention, 0 si l'événement correspond à la fin d'exécution d'une tâche
								   // sinon, la durée opératoire de la tâche qui va être libérée
	char * task_id;
	int machine; // par convention, 0 si l'événement correspond à la libération d'une tâche,
				 // sinon, la machine qui exécute la tâche de l'événement
};

/**
 * @brief 
 * 
 * @param[in] event_type 
 * @param[in] event_time 
 * @param[in] processing_time 
 * @param[in] task_id 
 * @param[in] machine 
 * @return struct event_key_t* 
 */
struct event_key_t * new_event_key(int event_type, unsigned long event_time, unsigned long processing_time, char * task_id, int machine) {
	// A FAIRE
	struct event_key_t * event_key = calloc(1,sizeof(struct event_key_t));
	event_key->task_id = calloc(1,strlen(task_id)+1);
	strcpy(event_key->task_id,task_id);
	event_key->event_type = event_type;
	event_key->event_time = event_time;
	event_key->processing_time = processing_time;
	event_key->machine = machine;
	return event_key;
}

/**
 * @brief 
 * 
 * @param[in] key 
 * @return int 
 */
int get_event_type(const struct event_key_t * key) {
	// A FAIRE
	return key->event_type;
}

/**
 * @brief 
 * 
 * @param[in] key 
 * @return unsigned long 
 */
unsigned long get_event_time(const struct event_key_t * key) {
	// A FAIRE
	return key->event_time;
}

/**
 * @brief 
 * 
 * @param[in] key 
 * @return unsigned long 
 */
unsigned long get_event_processing_time(const struct event_key_t * key) {
	// A FAIRE
	return key->processing_time;
}

/**
 * @brief 
 * 
 * @param[in] key 
 * @return char* 
 */
char * get_event_task_id(const struct event_key_t * key) {
	// A FAIRE
	return key->task_id;
}

/**
 * @brief 
 * 
 * @param[in] key 
 * @return int 
 */
int get_event_machine(const struct event_key_t * key) {
	// A FAIRE
	return key->machine;
}

/**
 * @brief 
 * 
 * @param[in] key 
 */
void view_event_key(const void * key) {
	// A FAIRE
	printf("Key id : %s\n",get_event_task_id(key));
	printf("Nombre de machine : %d\n",get_event_machine(key));
	printf("Event type : %d\n",get_event_type(key));
	printf("Event time : %lu\n",get_event_time(key));
	printf("Event processing time : %lu\n",get_event_processing_time(key));
	printf("laaa ?\n");
}

/**
 * @brief 
 * 
 * @param[in] key 
 */
void delete_event_key(void * key) {
	// A FAIRE
	struct event_key_t * KEY = (struct event_key_t*)key;
	free(KEY->task_id);
	free(KEY);
	KEY = NULL;

}

/**
 * @brief Comparer deux événements \p a et \p b.
 * Les règles de comparaison sont données dans la présentation du cours.
 * 
 * @param[in] a 
 * @param[in] b 
 * @return int 
 */
//Si la clef est plus petite elle retourne 0, sinon 1
int event_preceed(const void * a, const void * b) {
	// A FAIRE
	if(get_event_time(a) < get_event_time(b))
	{
		return 0;
	}
	if(get_event_time(a) == get_event_time(b))
	{
		//tj =tk et typej =≪ arriv ́ee≫ et typek =≪ fin d'execution≫
		if(get_event_type(a) == 0 && get_event_type(b) == 1)
		{
			return 0;
		}
		//tj =tk typej =typek =≪ arriv ́ee≫ et pj <pk
		else if(get_event_type(a) == 0 && get_event_type(b) == 0)
		{
			if(get_event_processing_time(a) < get_event_processing_time(b))
			{
				return 0;
			}
		}
		//tj = tk typej =typek =≪ arriv ́ee≫ et pj =pk et j<k
		else if(get_event_type(a)==0 && get_event_type(b) == 0)
		{
			if(get_event_processing_time(a) == get_event_processing_time(b))
			{
				if(atoi(get_event_task_id(a)) < atoi(get_event_task_id(b)))
				{
					return 0;
				}
			}
		}
		//tj =tk et typej =typek =≪ find’ex ́ecution≫ et mj <mk
		else if(get_event_type(a) == 1 && get_event_type(b) == 1 )
		{
			if(get_event_machine(a) < get_event_machine(b))
			{
				return 0;
			}
			
			else if(get_event_machine(a) == get_event_machine(b))
			{
				if(get_event_processing_time(a) < get_event_processing_time(b))
				{
					return 0;
				}
				else if(get_event_processing_time(a) == get_event_processing_time(b))
				{
					
					if(atoi(get_event_task_id(a)) <  atoi(get_event_task_id(b)))
					{
						return 0;
					}
					
				}
			}
			
			

		}

	}
	return 1;
}
	





/********************************************************************
 * ready_task_key_t
 ********************************************************************/

/**
 * @brief
 * Une structure qui définit la clé de la file d'attente avec les "ready tasks".
 */
struct ready_task_key_t {
	unsigned long remaining_processing_time;
	char * task_id;
};

/**
 * @brief 
 * 
 * @param[in] remaining_processing_time 
 * @param[in] task_id 
 * @return struct ready_task_key_t* 
 */
struct ready_task_key_t * new_ready_task_key(unsigned long remaining_processing_time, char * task_id) {
	// A FAIRE
	struct ready_task_key_t * New_Ready_Task_Key = calloc(1,sizeof(struct ready_task_key_t));
	New_Ready_Task_Key->task_id = calloc(1,strlen(task_id)+1);
	strcpy(New_Ready_Task_Key->task_id, task_id);	
	New_Ready_Task_Key->remaining_processing_time = remaining_processing_time;
	return New_Ready_Task_Key;
}

/**
 * @brief 
 * 
 * @param[in] key 
 * @return unsigned long 
 */
unsigned long get_ready_task_remaining_processing_time(const struct ready_task_key_t * key) {
	// A FAIRE
	return key->remaining_processing_time;
}

/**
 * @brief 
 * 
 * @param[in] key 
 * @return char* 
 */
char * get_ready_task_id(const struct ready_task_key_t * key) {
	// A FAIRE
	return key->task_id;
}

/**
 * @brief 
 * 
 * @param[in] key 
 */
void view_ready_task_key(const void * key) {
	// A FAIRE
	printf("Task id : %s\n",get_ready_task_id(key));
	printf("Remaining time : %lu\n",get_ready_task_remaining_processing_time(key));
}

/**
 * @brief 
 * 
 * @param[in] key 
 */
void delete_ready_task_key(void * key) {
	// A FAIRE
	struct ready_task_key_t * k = (struct ready_task_key_t *)key;
	free(k->task_id);
	free(k);
	k = NULL;
}

/**
 * @brief Comparer deux tâches \p a et \p b de la file d'attente afin de définir la tâche la plus prioritaire.
 * Les deux paramètres d'entrée \p a et \p b sont de type struct ready_task_key_t *.
 * Les règles de comparaison sont données dans la présentation du cours.
 *
 * @param[in] a 
 * @param[in] b 
 * @return int 
 */
int ready_task_preceed(const void * a, const void * b) {
	// A FAIRE

	if(get_ready_task_remaining_processing_time(a) < get_ready_task_remaining_processing_time(b))
	{
		return 0;
	}
	else if(get_ready_task_remaining_processing_time(a) == get_ready_task_remaining_processing_time(b))
	{
	
		if(atoi(get_ready_task_id(a)) < atoi(get_ready_task_id(b)))
		{
			return 0;

		}
	}
	return 1;
}

/********************************************************************
 * The algorithm
 ********************************************************************/

struct schedule_t * create_schedule(Instance I, int num_m, int preemption, int balanced_tree) 
{
	// A FAIRE
	struct schedule_t * schedule = new_schedule(num_m);
	if(preemption == 0)
	{
		struct tree_t * Tree = new_tree(balanced_tree,event_preceed,view_event_key,view_task,delete_event_key,delete_task);
		struct tree_t * ReadyTasks = new_tree(balanced_tree,ready_task_preceed,view_ready_task_key,view_task,delete_ready_task_key,delete_task);
		struct list_node_t * L = get_list_head(I);
		while(L != NULL)
		{
			struct task_t * task = get_list_node_data(L);
			struct event_key_t * key = new_event_key(0,get_task_release_time(task),get_task_processing_time(task),get_task_id(task),0);
			tree_insert(Tree,key,task);
			L = get_successor(L);
		}
	
		while(tree_is_empty(Tree) == 0)
		{
			struct tree_node_t * keeey = tree_min(get_root(Tree));
			struct event_key_t * KEY = get_tree_node_key(keeey);
			struct task_t * taskToAdd = get_tree_node_data(keeey);
			unsigned long TIME = get_event_time(KEY);

			if(get_event_type(KEY) == 0)
			{
				int machine = find_empty_machine(schedule,get_event_time(KEY));
				if(machine != -1)
				{
					//Ajouter tache dans schedule
					add_task_to_schedule(schedule,taskToAdd,machine,get_event_time(KEY),get_event_time(KEY)+get_event_processing_time(KEY));
					//Ajouter dans Tree levenement <<fin d'execution>> de la tache
					struct event_key_t * keyCompletion= new_event_key(1,TIME+get_task_processing_time(taskToAdd),get_task_processing_time(taskToAdd),get_task_id(taskToAdd),machine);
					tree_insert(Tree,keyCompletion,taskToAdd);
					tree_remove(Tree,KEY);
				}
		
				else if(machine == -1)
				{
					struct ready_task_key_t * readyyTask = new_ready_task_key(get_task_processing_time(taskToAdd),get_task_id(taskToAdd));
					tree_insert(ReadyTasks,readyyTask,taskToAdd);
					tree_remove(Tree,KEY);
				}
			}
			else if(get_event_type(KEY)  == 1)
			{
				if(tree_is_empty(ReadyTasks) == 0)
				{
					int machine = find_empty_machine(schedule,TIME);
					if(machine != -1)
					{
						struct tree_node_t * nodeKey = tree_min(get_root(ReadyTasks));
						struct ready_task_key_t * newKey = get_tree_node_key(nodeKey);
						struct task_t * ReadyTaskToAdd = get_tree_node_data(nodeKey);
						tree_remove(ReadyTasks,newKey);
						tree_remove(Tree,KEY);
				
						add_task_to_schedule(schedule,ReadyTaskToAdd,machine,TIME,get_ready_task_remaining_processing_time(newKey)+TIME);
						//add_task_to_schedule(schedule,ReadyTaskToAdd,machine,get_event_time(KEY),get_ready_task_remaining_processing_time(newKey)+get_event_time);
						struct event_key_t * ReadyTaskEnd = new_event_key(1,TIME+get_task_processing_time(ReadyTaskToAdd),get_task_processing_time(ReadyTaskToAdd),get_task_id(ReadyTaskToAdd),machine);
						tree_insert(Tree,ReadyTaskEnd,ReadyTaskToAdd);
					}
		
				if(machine == -1)
				{
					tree_remove(Tree,KEY);

				}
				

				
				}
				else if(tree_is_empty(ReadyTasks) == 1)
				{
					tree_remove(Tree,KEY);
				}
			}
			/*
			printf("NB Tree %d\n",get_tree_size(Tree));
			printf("View Tree\n");
			view_tree(Tree);

			printf("NB ReadyTasks %d\n",get_tree_size(ReadyTasks));
			printf("View ReadyTasks\n");
			view_tree(ReadyTasks);

			printf("view schedule \n");
			view_schedule(schedule);
			*/
		
	
		}

		delete_tree(Tree,1,1);
		delete_tree(ReadyTasks,1,1);
		

	
	}
	else if(preemption ==1)
	{
		struct tree_t * Tree = new_tree(balanced_tree,event_preceed,view_event_key,view_task,delete_event_key,delete_task);
		struct tree_t * ReadyTasks = new_tree(balanced_tree,ready_task_preceed,view_ready_task_key,view_task,delete_ready_task_key,delete_task);
		struct list_node_t * L = get_list_head(I);
		while(L != NULL)
		{
			struct task_t * task = get_list_node_data(L);
			struct event_key_t * key = new_event_key(0,get_task_release_time(task),get_task_processing_time(task),get_task_id(task),0);
			tree_insert(Tree,key,task);
			L = get_successor(L);
		}
		//view_tree(Tree);
		while(tree_is_empty(Tree) == 0)
		{
	
			struct tree_node_t * keeey = tree_min(get_root(Tree));
			struct event_key_t * KEY = get_tree_node_key(keeey);
			struct task_t * taskToAdd = get_tree_node_data(keeey);
			unsigned long TIME = get_event_time(KEY);
			//printf("EVENT KEY : ");
			//view_event_key(KEY);
			//printf("\n");
			if(get_event_type(KEY) == 0)
			{
				int machine = find_empty_machine(schedule,get_event_time(KEY));
				if(machine != -1)
				{
					
					add_task_to_schedule(schedule,taskToAdd,machine,get_event_time(KEY),get_event_time(KEY)+get_event_processing_time(KEY));
					//Ajouter dans Tree levenement <<fin d'execution>> de la tache
					struct event_key_t * keyCompletion= new_event_key(1,TIME+get_task_processing_time(taskToAdd),get_task_processing_time(taskToAdd),get_task_id(taskToAdd),machine);
					tree_insert(Tree,keyCompletion,taskToAdd);
					tree_remove(Tree,KEY);
				}

				else if(find_machine_to_interrupt(schedule,TIME,get_task_processing_time(taskToAdd)) != -1)
				{
					int MachineToInter = find_machine_to_interrupt(schedule,TIME,get_task_processing_time(taskToAdd));
					int preempt = preempt_task(schedule,find_machine_to_interrupt(schedule,TIME,get_task_processing_time(taskToAdd)),TIME);
					struct event_key_t * KEYTASK = get_tree_node_key(tree_max(get_root(Tree)));
					struct task_t * TASK = tree_remove(Tree,get_tree_node_key(tree_max(get_root(Tree))));
					//view_event_key(KEYTASK);
				
					
					unsigned long TimeRelease= TIME - get_task_release_time(TASK);
				
					//struct ready_task_key_t * keyTASK = new_ready_task_key(get_task_processing_time(TASK)-TimeRelease,get_task_id(TASK));
					struct ready_task_key_t * keyTASK = new_ready_task_key(get_event_time(KEYTASK)-TIME,get_task_id(TASK));


					tree_insert(ReadyTasks,keyTASK,TASK);

					add_task_to_schedule(schedule,taskToAdd,MachineToInter,get_event_time(KEY),get_event_time(KEY)+get_event_processing_time(KEY));

					struct event_key_t * ev = new_event_key(1,TIME+get_event_processing_time(KEY),get_task_processing_time(taskToAdd),get_task_id(taskToAdd),MachineToInter);
					tree_insert(Tree,ev,taskToAdd);
					tree_remove(Tree,KEY);


				}
				
				else if(machine == -1)
				{
					struct ready_task_key_t * readyyTask = new_ready_task_key(get_task_processing_time(taskToAdd),get_task_id(taskToAdd));
					tree_insert(ReadyTasks,readyyTask,taskToAdd);
					tree_remove(Tree,KEY);
				}
			}
			else if(get_event_type(KEY)  == 1)
			{
				if(tree_is_empty(ReadyTasks) == 0)
				{
					int machine = find_empty_machine(schedule,TIME);
					if(machine != -1)
					{
						struct tree_node_t * nodeKey = tree_min(get_root(ReadyTasks));
						struct ready_task_key_t * newKey = get_tree_node_key(nodeKey);
						struct task_t * ReadyTaskToAdd = get_tree_node_data(nodeKey);
						tree_remove(ReadyTasks,newKey);
						tree_remove(Tree,KEY);
						//ReadyTaskToAdd->release_time = TIME;
						add_task_to_schedule(schedule,ReadyTaskToAdd,machine,TIME,get_ready_task_remaining_processing_time(newKey)+TIME);
						struct event_key_t * ReadyTaskEnd = new_event_key(1,TIME+get_task_processing_time(ReadyTaskToAdd),get_task_processing_time(ReadyTaskToAdd),get_task_id(ReadyTaskToAdd),machine);
						tree_insert(Tree,ReadyTaskEnd,ReadyTaskToAdd);
					}
					
				if(machine == -1)
				{
					tree_remove(Tree,KEY);

				}
				

				
				}
				else if(tree_is_empty(ReadyTasks) == 1)
				{
					tree_remove(Tree,KEY);
				}
			}
			
			/*
			printf("View Tree\n");
			view_tree(Tree);

			printf("View ReadyTaskss\n");
			view_tree(ReadyTasks);

			printf("view schedule \n");
			view_schedule(schedule);
			
		*/
			
		}

		delete_tree(Tree,1,1);
		delete_tree(ReadyTasks,1,1);
		

	}

	//printf("End create schedule\n");
	return schedule;
}
