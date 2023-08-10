//Reader writer
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

int readers_count = 0;
int resource = 0;

sem_t mutex;
sem_t rw_mutex;

void* reader(void* arg) {
    while (1) {
        sem_wait(&mutex);  // Acquire mutual exclusion for updating readers count
        readers_count++;
        if (readers_count == 1) {
            sem_wait(&rw_mutex);  // Acquire mutual exclusion if first reader
        }
        sem_post(&mutex);  // Release mutual exclusion

        // Read the resource
        read_resource(resource);

        sem_wait(&mutex);  // Acquire mutual exclusion for updating readers count
        readers_count--;
        if (readers_count == 0) {
            sem_post(&rw_mutex);  // Release mutual exclusion if last reader
        }
        sem_post(&mutex);  // Release mutual exclusion
    }
}

void* writer(void* arg) {
    while (1) {
        sem_wait(&rw_mutex);  // Acquire mutual exclusion for writers

        // Write to the resource
        write_resource(resource);

        sem_post(&rw_mutex);  // Release mutual exclusion for writers
    }
}

int main() {
    sem_init(&mutex, 0, 1);
    sem_init(&rw_mutex, 0, 1);

    pthread_t reader_threads[NUM_READERS];
    pthread_t writer_threads[NUM_WRITERS];

    for (int i = 0; i < NUM_READERS; i++) {
        pthread_create(&reader_threads[i], NULL, reader, NULL);
    }

    for (int i = 0; i < NUM_WRITERS; i++) {
        pthread_create(&writer_threads[i], NULL, writer, NULL);
    }

    // Run the threads for a certain duration or until termination condition

    for (int i = 0; i < NUM_READERS; i++) {
        pthread_cancel(reader_threads[i]);
    }

    for (int i = 0; i < NUM_WRITERS; i++) {
        pthread_cancel(writer_threads[i]);
    }

    sem_destroy(&mutex);
    sem_destroy(&rw_mutex);

    return 0;
}
