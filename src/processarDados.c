#include "../header/processarDados.h"

bool actualizarComCliente(int sock){
    if (!recv(sock, &player, sizeof(nave_player), 0)) {
        printf("Cliente desconectado.\n");
        return false;
    }

    if (send(sock, &player, sizeof(nave_player), 0) < 0) {
        perror("Erro ao enviar dados ao cliente");
        return false;
    }

    char tecla;
    recv(sock, &tecla, sizeof(char), 0);
    
    return true;
}