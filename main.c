#include "header/index.h"

bool player_status = true;
int numero_de_players = 0;
int capacidade_de_players = 5;
nave_player *players;
int numero_inimigos = 0;
int numero_inimigos_inicial = 1;
int capacidade_inimigos = MAXIMO_INIMIGOS;
nave_inimiga *inimigos;
int numero_obstaculos = 2;
obstaculo *obstaculos;
armas *arsenal;
int numero_balas;
int capacidade_balas = 25;
bala *balas;
int numero_meteoros = 0;
int capacidade_meteoros = 10;
meteoro *meteoros;
int numero_pacotes = 0;
pacote *pacotes;
int numero_explosoes = 0;
int capacidades_explosoes = 25;
explosao *explosoes;
int numero_paredes_defensivas = 0;
int capacidade_paredes_defensivas = 15;
parede_defensiva *paredes_defensiva;
int numero_robos_metralhadora = 0;
int capacidade_robos_metralhadora = 5;
robo_metralhadora *robos_metralhadora;

#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>

#include "header/processarDados.h"

#define PORT 8080
#define MAX_CLIENTS 5  // Número máximo de clientes simultâneos

void* handle_client(void* socket_desc) {
    int sock = *(int*)socket_desc;
    free(socket_desc);  // Liberar a memória alocada para o socket

    while (1) {
        if(!actualizarComCliente(sock)) break;
    }

    close(sock);
    return NULL;
}

int main() {
    int server_fd, *new_socket;
    struct sockaddr_in address;
    socklen_t addrlen = sizeof(address);

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    bind(server_fd, (struct sockaddr*)&address, sizeof(address));
    listen(server_fd, MAX_CLIENTS);

    printf("Servidor aguardando conexões na porta %d...\n", PORT);

    while (1) {
        new_socket = malloc(sizeof(int));  // Alocar memória para cada novo socket
        *new_socket = accept(server_fd, (struct sockaddr*)&address, &addrlen);
        if (*new_socket < 0) {
            perror("Erro ao aceitar conexão");
            free(new_socket);
            continue;
        }

        printf("Novo cliente conectado!\n");

        pthread_t thread;
        pthread_create(&thread, NULL, handle_client, (void*)new_socket);
        pthread_detach(thread);  // Desvincula a thread para liberar recursos automaticamente
    }

    close(server_fd);
    return 0;
}
