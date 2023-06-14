#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

struct estacao {
    int assentos_livres;
    int vagao_presente;
    pthread_mutex_t mutex;
    pthread_cond_t cond_vagao;
    pthread_cond_t cond_passageiro;
};

void estacao_init(struct estacao *estacao) {
    estacao->assentos_livres = 0;
    estacao->vagao_presente = 0;
    pthread_mutex_init(&estacao->mutex, NULL);
    pthread_cond_init(&estacao->cond_vagao, NULL);
    pthread_cond_init(&estacao->cond_passageiro, NULL);
}

void estacao_preencher_vagao(struct estacao *estacao, int assentos) {
    pthread_mutex_lock(&estacao->mutex);

    while (estacao->assentos_livres != 0 || estacao->vagao_presente) {
        pthread_cond_wait(&estacao->cond_vagao, &estacao->mutex);
    }

    estacao->assentos_livres = assentos;
    estacao->vagao_presente = 1;
    

    pthread_cond_broadcast(&estacao->cond_passageiro);
    pthread_mutex_unlock(&estacao->mutex);
}

void estacao_espera_pelo_vagao(struct estacao *estacao) {
    pthread_mutex_lock(&estacao->mutex);

    while (estacao->assentos_livres == 0 || !estacao->vagao_presente) {
        pthread_cond_wait(&estacao->cond_passageiro, &estacao->mutex);
        
    }

    estacao->assentos_livres--;

    pthread_mutex_unlock(&estacao->mutex);
}

void estacao_embarque(struct estacao *estacao) {
    pthread_mutex_lock(&estacao->mutex);

    if (estacao->assentos_livres == 0) {
        estacao->vagao_presente = 0;
        pthread_cond_signal(&estacao->cond_vagao);
    }

    pthread_mutex_unlock(&estacao->mutex);
}