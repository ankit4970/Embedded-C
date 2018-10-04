/* ************************************************************************************************
 * synchronization.c
 *************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <limits.h>
#include <stdint.h>

#define NUM_OF_ELEMENTS 10

int array[NUM_OF_ELEMENTS];
int writeIndex = 0;
int count = 0;
int readIndex = 0;

pthread_mutex_t count_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t condp = PTHREAD_COND_INITIALIZER;

/* **********************************************************************************************
 * producer
 ************************************************************************************************/
void* producer() 
{
	for (int i = 0 ; i < 100 ; ++i) 
	{
		pthread_mutex_lock(&count_mutex);				// protect buffer
		while (count == NUM_OF_ELEMENTS)		  		// If buffer is full then wait
		{
			printf(" Buffer is full, going to sleep\n");
			pthread_cond_wait(&condp, &count_mutex);
		}

		count++;
		int write = rand()%10;
		printf("Produced  = %d writeIndex = %d\n", write, writeIndex);
		array[writeIndex] = write;
		writeIndex = (writeIndex+1)%NUM_OF_ELEMENTS;	// keep index within 0 - 9 range
		
		pthread_cond_signal(&condp);					// wake up consumer 
		pthread_mutex_unlock(&count_mutex);				// release the buffer
	}
	pthread_exit(0);
}

/* **********************************************************************************************
 * consumer
 ************************************************************************************************/
void* consumer() 
{
	for (int i = 0 ; i < 100 ; ++i)
	{
		pthread_mutex_lock(&count_mutex);			// protect buffer
		while (count == 0)							// If there is nothing in the buffer then wait
		{
			printf(" Buffer is empty, going to sleep\n");
			pthread_cond_wait(&condp, &count_mutex);	
		}
		
		int read = array[readIndex];
		printf("Consumed  = %d\n", read);
		readIndex = (readIndex+1)%NUM_OF_ELEMENTS;	// keep index within 0 - 9 range
		count--;
		pthread_cond_signal(&condp);				// wake up producer
		pthread_mutex_unlock(&count_mutex);			// release the buffer
	}
	pthread_exit(0);
}

/* **********************************************************************************************
 * syncMain
 ************************************************************************************************/
int syncMain()
{
	pthread_t thread1, thread2;
	pthread_create( &thread1, NULL, &producer, NULL);
	pthread_create( &thread2, NULL, &consumer, NULL);
	pthread_join( thread1, NULL);
	pthread_join( thread2, NULL);
	exit(0);
}