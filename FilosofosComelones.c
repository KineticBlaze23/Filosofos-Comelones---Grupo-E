#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_FILOSOFOS 5  // Número de filósofos

sem_t tenedores[NUM_FILOSOFOS];      // Semáforos para los tenedores
sem_t max_filosofos;                 // Semáforo para evitar interbloqueo

void *accion_filosofos(void *args) {
    int id = *(int *)args;
    int tenedor_izquierdo = id;
    int tenedor_derecho = (id + 1) % NUM_FILOSOFOS;

    while (1) {
        // Filósofo pensando
        printf("Filósofo %d está pensando...\n", id);
        sleep(1 + rand() % 3);

        // Intenta entrar a la zona de comer (controlado por max_filosofos)
        sem_wait(&max_filosofos);

        // Intenta tomar los tenedores
        printf("Filósofo %d tiene hambre y quiere comer...\n", id);
        sem_wait(&tenedores[tenedor_izquierdo]);
        printf("Filósofo %d toma el tenedor izquierdo (%d).\n", id, tenedor_izquierdo);
        sem_wait(&tenedores[tenedor_derecho]);
        printf("Filósofo %d toma el tenedor derecho (%d).\n", id, tenedor_derecho);

        // Filósofo comiendo
        printf("Filósofo %d está comiendo...\n", id);
        sleep(1 + rand() % 3);

        // Suelta los tenedores
        printf("Filósofo %d regresa los tenedores %d y %d.\n", id, tenedor_izquierdo, tenedor_derecho);
        sem_post(&tenedores[tenedor_derecho]);
        sem_post(&tenedores[tenedor_izquierdo]);

        // Sale de la zona de comer
        sem_post(&max_filosofos);
    }
}

int main() {
    pthread_t filosofos[NUM_FILOSOFOS];
    int ids_filosofos[NUM_FILOSOFOS];
    int i;

    srand(time(NULL));

    // Inicializa el semáforo para limitar a N-1 filósofos comiendo simultáneamente
    sem_init(&max_filosofos, 0, NUM_FILOSOFOS - 1);

    // Inicializa los semáforos de los tenedores
    for (i = 0; i < NUM_FILOSOFOS; i++)
        sem_init(&tenedores[i], 0, 1);

    // Crea los hilos de los filósofos
    for (i = 0; i < NUM_FILOSOFOS; i++) {
        ids_filosofos[i] = i;
        pthread_create(&filosofos[i], NULL, accion_filosofos, &ids_filosofos[i]);
    }

    // Espera a que los hilos terminen (nunca sucede en este caso)
    for (i = 0; i < NUM_FILOSOFOS; i++)
        pthread_join(filosofos[i], NULL);

    // Limpieza (aunque no se alcanza)
    sem_destroy(&max_filosofos);
    for (i = 0; i < NUM_FILOSOFOS; i++)
        sem_destroy(&tenedores[i]);

    return 0;
}
