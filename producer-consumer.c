//producer-consumer
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];
int in = 0;
int out = 0;

sem_t empty;
sem_t full;
sem_t mutex;

void* producer(void* arg) {
    int item;
    while (1) {
        item = produce_item();
        sem_wait(&empty);  // Wait if the buffer is full
        sem_wait(&mutex);  // Acquire mutual exclusion to modify the buffer
        buffer[in] = item;
        in = (in + 1) % BUFFER_SIZE;
        sem_post(&mutex);  // Release mutual exclusion
        sem_post(&full);  // Signal that the buffer is not empty
    }
}

void* consumer(void* arg) {
    int item;
    while (1) {
        sem_wait(&full);  // Wait if the buffer is empty
        sem_wait(&mutex);  // Acquire mutual exclusion to modify the buffer
        item = buffer[out];
        out = (out + 1) % BUFFER_SIZE;
        sem_post(&mutex);  // Release mutual exclusion
        sem_post(&empty);  // Signal that the buffer is not full
        consume_item(item);
    }
}

int main() {
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    sem_init(&mutex, 0, 1);

    pthread_t producer_thread, consumer_thread;
    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);

    // Run the threads for a certain duration or until termination condition

    pthread_cancel(producer_thread);
    pthread_cancel(consumer_thread);

    sem_destroy(&empty);
    sem_destroy(&full);
    sem_destroy(&mutex);

    return 0;
}
