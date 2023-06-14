# README - MetroRec

Este repositório contém a implementação em C de um sistema de sincronização para automatizar o embarque de passageiros nos vagões do metrô, a fim de melhorar a eficiência da METROREC. O sistema utiliza threads independentes para controlar cada vagão e passageiro.

## Funcionalidades

O programa implementa as seguintes funcionalidades:

### 1. Inicialização da estação

Antes de utilizar o sistema, é necessário chamar a função `estacao_init` para inicializar o objeto da estação.

```c
void estacao_init(struct estacao *estacao);
```

### 2. Preenchimento do vagão

Quando um carro chega à estação e tem as portas abertas, deve-se chamar a função `estacao_preencher_vagao` para preencher o vagão de forma ordenada. O parâmetro `assentos` indica quantos assentos há no vagão. Essa função não retorna até que o vagão esteja satisfatoriamente preenchido, ou seja, todos os passageiros estejam sentados e ou o vagão esteja cheio ou todos os passageiros que estavam esperando tenham embarcado.

```c
void estacao_preencher_vagao(struct estacao *estacao, int assentos);
```

### 3. Espera pelo vagão

Quando um passageiro chega à estação, ele deve chamar a função `estacao_espera_pelo_vagao` para aguardar a chegada de um vagão à estação e a disponibilidade de assentos livres no carro. Essa função não retorna até que um vagão esteja na estação, ou seja, a função `estacao_preencher_vagao` esteja em execução, e haja assentos livres no carro para o passageiro sentar-se. Uma vez que essa função retorne, o passageiro poderá embarcar e ocupar um assento.

```c
void estacao_espera_pelo_vagao(struct estacao *estacao);
```

### 4. Embarque do passageiro

Após esperar pelo vagão, o passageiro embarca e ocupa um assento. Em seguida, a função `estacao_embarque` é chamada para indicar ao vagão que o passageiro embarcou. É importante ressaltar que não há ordem de chegada, ou seja, o primeiro passageiro a chegar não necessariamente será o primeiro a embarcar.

```c
void estacao_embarque(struct estacao *estacao);
```

## Especificações

O programa foi implementado em C e é executável em sistemas Linux, Unix ou macOS. Ele utiliza as seguintes funções de sincronização:

- pthread_mutex_init
- pthread_mutex_lock
- pthread_mutex_unlock
- pthread_cond_init
- pthread_cond_signal
- pthread_cond_wait
- pthread_cond_broadcast

**Observações:**
- Não foram utilizados semáforos nem outras primitivas de sincronização.
- Foi utilizado apenas um único lock em cada struct estacao.
- O código assume que nunca haverá mais de um carro na estação por vez, e que todos os carros e passageiros estão indo para o mesmo destino.
- O código permite que passageiros embarquem simultaneamente, ou seja, é permitido que diversos passageiros chamem a função `estacao_espera_pelo_vagao`, e a função retorna
