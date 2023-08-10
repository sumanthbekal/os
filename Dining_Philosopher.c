//Dining Philosophers Problem
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define NUM_PHILOSOPHERS 5

sem_t forks[NUM_PHILOSOPHERS];
sem_t mutex;

void* philosopher(void* arg) {
    int id = *(int*)arg;
    int left_fork = id;
    int right_fork = (id + 1) % NUM_PHILOSOPHERS;

    while (1) {
        think();  // Philosopher thinks

        sem_wait(&mutex);  // Acquire mutual exclusion for picking up forks
        sem_wait(&forks[left_fork]);  // Acquire left fork
        sem_wait(&forks[right_fork]);  // Acquire right fork
        sem_post(&mutex);  // Release mutual exclusion

        eat();  // Philosopher eats

        sem_post(&forks[right_fork]);  // Release right fork
        sem_post(&forks[left_fork]);  // Release left fork
    }
}

int main() {
    sem_init(&mutex, 0, 1);

    pthread_t philosopher_threads[NUM_PHILOSOPHERS];
    int philosopher_ids[NUM_PHILOSOPHERS];

    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        sem_init(&forks[i], 0, 1);
        philosopher_ids[i] = i;
        pthread_create(&philosopher_threads[i], NULL, philosopher, &philosopher_ids[i]);
    }

    // Run the threads for a certain duration or until termination condition

    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_cancel(philosopher_threads[i]);
        sem_destroy(&forks[i]);
    }

    sem_destroy(&mutex);

    return 0;
}
