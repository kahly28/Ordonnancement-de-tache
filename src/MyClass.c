#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../include/util.h"
#include "../include/instance.h"
#include "../include/schedule.h"
#include "../include/algo.h"
#include "../include/application_MyClass.h"

JNIEXPORT void JNICALL Java_application_MyClass_runSchedule
  (JNIEnv * env, jobject, jstring i, jstring o , jint m, jint p, jint b)
{
     const char *IN = (*env)->GetStringUTFChars(env, i, NULL);
     const char *OUT = (*env)->GetStringUTFChars(env, o, NULL);
     Instance I = read_instance(IN);
     struct schedule_t * S = create_schedule(I, m, p, b);
     save_schedule(S, OUT);
}

/*

int main(int argc, char const *argv[])
{
/*
    char * instanceIn = malloc(strlen(argv[1])+1);
	strcpy(instanceIn,argv[1]);

    char * scheduleOut = malloc(strlen(argv[2])+1);
    strcpy(scheduleOut,argv[2]);

    char * machine = malloc(strlen(argv[3])+1);
    strcpy(machine,argv[3]);
    int NbMachine = atoi(machine);

    char * pree = malloc(strlen(argv[4])+1);
    strcpy(pree,argv[4]);
    int preempt = atoi(pree);

    char * ba = malloc(strlen(argv[5])+1);
    strcpy(ba,argv[5]);
    int balance = atoi(ba);

    runSchedule(instanceIn,scheduleOut,NbMachine,preempt,balance);

    return 0;
}
*/
