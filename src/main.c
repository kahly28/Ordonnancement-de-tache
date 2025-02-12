#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/util.h"
#include "../include/instance.h"
#include "../include/schedule.h"
#include "../include/algo.h"
#include "../include/tree.h"
#include "../include/list.h"



void display_help() {
	ShowMessage("", 0);
	ShowMessage("./exe in=infilename out=outfilename m=machines pre=preemption bal=balanced\n", 0);
	ShowMessage("preemption:", 0);
	ShowMessage("\t0 - without preemption", 0);
	ShowMessage("\t1 - with preemption", 0);
	ShowMessage("", 0);
	ShowMessage("balanced:", 0);
	ShowMessage("\t0 - use a binary search tree", 0);
	ShowMessage("\t1 - use a balanced binary search tree", 0);
	ShowMessage("", 1);
}


int main(int argc, char *argv[]) {
		if (argc != 6)
		{
			printf("argc = %d\n",argc);
			display_help();
		}
	 
	char* infilename = malloc(strlen(argv[1])+1); 
	strcpy(infilename,argv[1]);
	char* outfilename = malloc(strlen(argv[2])+1);  ;
	strcpy(outfilename,argv[2]);

	char * machine = malloc(strlen(argv[3])+1);
	strcpy(machine,argv[3]);
	int m= atoi(machine);
	
	char * preempt = malloc(strlen(argv[4])+1);
	strcpy(preempt,argv[4]);
	int preemption = atoi(preempt);

	char * balance = malloc(strlen(argv[5])+1);
	strcpy(balance,argv[5]);
	int balanced = balance;
	printf("prrrempt = %d\n",balanced);
	printf("laaa?\n");
	Instance I = read_instance(infilename);
	printf("lkdlk\n");
	struct schedule_t * S = create_schedule(I, m, preemption, balanced);
	printf("The makespan of the constructed schedule is %lu\n\n", get_makespan(S));


	view_schedule(S);
	save_schedule(S, outfilename);
	delete_schedule(S);
	delete_instance(I, 1);
	free(infilename);
	free(outfilename);
	free(machine);
	free(preempt);
	free(balance);

	return EXIT_SUCCESS;
}
