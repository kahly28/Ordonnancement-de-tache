#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../include/util.h"
#include "../include/instance.h"
#include "../include/schedule.h"
#include "../include/algo.h"
//#include "algo.c"


int main(int argc, char *argv[]) {
	if (argc != 3)
	{
		printf("icc?\n");
		ShowMessage("expe:main: invalid number of arguments", 1);
	}
	char* infilename = argv[1];
	int m = atoi(argv[2]);
	
	clock_t start, end;
	Instance I = read_instance(infilename);
	struct schedule_t * S;
	//printf("iioo\n");
	



	start = clock();
	S = create_schedule(I, m, 0, 1);
	end = clock();
	double cpu_time_used01 = ((double) (end - start)) / CLOCKS_PER_SEC;
	unsigned long makespan01 = get_makespan(S);
	//view_schedule(S);
	delete_schedule(S);



	start = clock();
	S = create_schedule(I, m, 0, 0);
	end = clock();
	double cpu_time_used00 = ((double) (end - start)) / CLOCKS_PER_SEC;
	unsigned long makespan00 = get_makespan(S);
	//view_schedule(S);
	delete_schedule(S);




	start = clock();
	S = create_schedule(I, m, 1, 0);
	end = clock();
	double cpu_time_used10 = ((double) (end - start)) / CLOCKS_PER_SEC;
	unsigned long makespan10 = get_makespan(S);
	//view_schedule(S);
	delete_schedule(S);


	start = clock();
	S = create_schedule(I, m, 1, 1);
	end = clock();
	double cpu_time_used11 = ((double) (end - start)) / CLOCKS_PER_SEC;
	unsigned long makespan11 = get_makespan(S);
	//view_schedule(S);
	
	delete_schedule(S);

	
	delete_instance(I, 1);
/*
	printf("makespan00 = %d\n",makespan00);
	printf("makespan01 = %d\n",makespan01);
	printf("makespan10 = %d\n",makespan10);
	printf("makespan11 = %d\n",makespan11);
	*/
	if (makespan10 != makespan11)
	{
		ShowMessage("Preemtive : The makespan is not the same when using balanced and non balanced trees.\n", 1);
	}
	if (makespan00 != makespan01)
	{
		ShowMessage("Non-Preemtive : The makespan is not the same when using balanced and non balanced trees.\n", 1);
	}

	printf("%lu %lf %lu %lf %lu %lf %lu %lf", makespan00, cpu_time_used00,
											  makespan01, cpu_time_used01,
											  makespan10, cpu_time_used10,
											  makespan11, cpu_time_used11);

	return EXIT_SUCCESS;
}
