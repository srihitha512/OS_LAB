#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define N 5

pthread_mutex_t forks[N];

void *philosopher(void *num) {
    int id = *(int *)num;

    while (1) {
        // Thinking
        printf("Philosopher %d is thinking\n", id);
        sleep(1);

        // Pick up forks
        if (id % 2 == 0) {
            pthread_mutex_lock(&forks[id]);
            printf("Philosopher %d picked up left fork %d\n", id, id);

            pthread_mutex_lock(&forks[(id + 1) % N]);
            printf("Philosopher %d picked up right fork %d\n",
                   id, (id + 1) % N);
        } else {
            pthread_mutex_lock(&forks[(id + 1) % N]);
            printf("Philosopher %d picked up right fork %d\n",
                   id, (id + 1) % N);

            pthread_mutex_lock(&forks[id]);
            printf("Philosopher %d picked up left fork %d\n", id, id);
        }

        // Eating
        printf("Philosopher %d is eating\n", id);
        sleep(2);

        // Put down forks
        pthread_mutex_unlock(&forks[id]);
        pthread_mutex_unlock(&forks[(id + 1) % N]);

        printf("Philosopher %d put down forks and starts thinking\n", id);
    }

    return NULL;
}

int main() {
    pthread_t philosophers[N];
    int ids[N];

    for (int i = 0; i < N; i++) {
        pthread_mutex_init(&forks[i], NULL);
    }

    for (int i = 0; i < N; i++) {
        ids[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, &ids[i]);
    }

    for (int i = 0; i < N; i++) {
        pthread_join(philosophers[i], NULL);
    }

    for (int i = 0; i < N; i++) {
        pthread_mutex_destroy(&forks[i]);
    }

    return 0;
}
