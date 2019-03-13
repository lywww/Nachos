// threadtest.cc 
//	Simple test case for the threads assignment.
//
//	Create two threads, and have them context switch
//	back and forth between themselves by calling Thread::Yield, 
//	to illustratethe inner workings of the thread system.
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation 
// of liability and disclaimer of warranty provisions.

#include "copyright.h"
#include "system.h"
#include "elevatortest.h"

// testnum is set in main.cc
int testnum = 1;

//----------------------------------------------------------------------
// SimpleThread
// 	Loop 5 times, yielding the CPU to another ready thread 
//	each iteration.
//
//	"which" is simply a number identifying the thread, for debugging
//	purposes.
//----------------------------------------------------------------------

void
SimpleThread(int which)
{
    int num;
    
    for (num = 0; num < 5; num++) {
	printf("*** thread %d with uid %d and tid %d looped %d times\n", which, currentThread->get_uid(), currentThread->get_tid(), num);
        currentThread->Yield();
    }
}

//----------------------------------------------------------------------
// ThreadTest1
// 	Set up a ping-pong between two threads, by forking a thread 
//	to call SimpleThread, and then calling SimpleThread ourselves.
//----------------------------------------------------------------------

void
ThreadTest1()
{
    DEBUG('t', "Entering ThreadTest1");
    Thread *t = new Thread("forked thread");

    t->Fork(SimpleThread, (void*)1);
    SimpleThread(0);
}

//----------------------------------------------------------------------
//Lab 1 TS
//	Print the information and status of all threads
//----------------------------------------------------------------------
void
TS()
{
   Thread *t = new Thread("forked thread");
   char *status[4] = {"JUST_CREATED", "RUNNING", "READY", "BLOCKED" };
   for(int i=0; i<maxthread; i++)
   {
       if(tid_available[i] == 1)
       {
            Thread *pointer = thread_pointer[i];
            printf("Thread %s with tid %d and uid %d is %s.\n", pointer->getName(), pointer->get_tid(), pointer->get_uid(), status[pointer->get_status()]);
       }
   }
}

//----------------------------------------------------------------------
// ThreadTest
// 	Invoke a test routine.
//----------------------------------------------------------------------

void
ThreadTest()
{
    switch (testnum) {
    case 1:
	ThreadTest1();
	break;
    //Lab 1
    case 2:
        TS();
        break;
    //Lab 1
    default:
	printf("No test specified.\n");
	break;
    }
}

