#include "../include/instance.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "../include/util.h"
#include "../include/list.h"

/********************************************************************
 * task_t
 ********************************************************************/

struct task_t * new_task(char * id, unsigned long proctime, unsigned long reltime) {
	struct task_t * T = malloc(1*sizeof(struct task_t));
	T->id = malloc(strlen(id)+1); // +1 for null-terminator
    strcpy(T->id, id);
	T->processing_time = proctime;
	T->release_time = reltime;
	return T;
}

char * get_task_id(const struct task_t * task) {
	// A FAIRE
	return task->id;
}

unsigned long get_task_processing_time(const struct task_t * task) {
	// A FAIRE
	return task->processing_time;
}

unsigned long get_task_release_time(const struct task_t * task) {
	// A FAIRE
	return task->release_time;
}

void view_task(const void * task) {
	// A FAIRE
	printf("L'id de la tache est : %s\n",get_task_id(task));
	printf("La durée de la tache est : %lu\n",get_task_processing_time(task));
	printf("Sa date de liberation est : %lu\n",get_task_release_time(task));
	printf("\n");
}

void delete_task(void * task) {
	// A FAIRE
	struct task_t * T = (struct task_t *)task;
	free(T->id);
	free(T);
	T = NULL;
	//free(task);
	//task = NULL;
}

/********************************************************************
 * Instance
 ********************************************************************/

Instance read_instance(const char * filename) {
	// A FAIRE
	//printf("%s\n",filename);
	FILE * fich = fopen(filename,"r");
	
	if(fich == NULL)
	{
		printf("erreur open");
		exit(1);
	}
	struct list_t * I = new_list(view_task,delete_task);
    unsigned long a,b;
    //char * id=calloc(strlen(id)+1,sizeof(char));
	char * id = malloc(1*sizeof(char));
	while(fscanf(fich,"%s %lu %lu",id,&a,&b)!=EOF){
            struct task_t * Ta = new_task(id,a,b);
            list_insert_last(I,Ta);
	}
	fclose(fich);
    return I;
}

void view_instance(Instance I) {
	// A FAIRE
	printf( "[ " );
	for(struct list_node_t * E=get_list_head(I);E;E=get_successor(E)) {
            I->viewData(get_list_node_data(E));
            //printf("%d ",get_list_node_data(E));
	}
	printf( " ]\n\n" );
}

void delete_instance(Instance I, int deleteData) {
	// A FAIRE
	assert(I);
	//delete_list(I,deleteData);
	if(deleteData == 0)
	{
		delete_list(I,0);
	}
	else
	{
		delete_list(I,1);
	}
}