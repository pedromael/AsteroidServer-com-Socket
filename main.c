#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080

typedef struct {
    int id;
    float x, y;
    int vida;
} PlayerData;

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    socklen_t addrlen = sizeof(address);
    
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    bind(server_fd, (struct sockaddr*)&address, sizeof(address));
    listen(server_fd, 3);

    printf("Aguardando conexão...\n");
    new_socket = accept(server_fd, (struct sockaddr*)&address, &addrlen);

    while (1) {
        PlayerData player;
        int bytes_received = recv(new_socket, &player, sizeof(PlayerData), 0);
        if (bytes_received <= 0) break;

        // Convertendo dados de rede para valores locais (caso necessário)
        player.id = ntohl(player.id);
        player.vida = ntohl(player.vida);
        
        printf("Jogador %d - Posição: (%.2f, %.2f), Vida: %d\n", player.id, player.x, player.y, player.vida);
    }

    close(new_socket);
    close(server_fd);
    return 0;
}
