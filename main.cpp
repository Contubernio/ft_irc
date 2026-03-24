#include "Server.hpp"
#include <iostream>
#include <signal.h>
#include <stdlib.h>

// Variable global para que la señal pueda detener el bucle
bool server_stop = false;

// Manejador de la señal Ctrl+C
void signalHandler(int signum) {
    (void)signum;
    std::cout << "\n[!] Deteniendo el servidor de forma segura..." << std::endl;
    server_stop = true;
}

int main(int argc, char **argv) {
    if (argc != 3) {
        std::cerr << "Uso: ./ircserv <puerto> <password>" << std::endl;
        return 1;
    }

    // Registramos la señal
    signal(SIGINT, signalHandler);

    try {
        int port = atoi(argv[1]);
        std::string password = argv[2];

        Server irc(port, password);
        irc.init();

        std::cout << "--- SERVIDOR IRC 42 INICIADO ---" << std::endl;
        std::cout << "Puerto: " << port << " | Pass: " << password << std::endl;
        std::cout << "Presiona Ctrl+C para salir limpiamente." << std::endl;

        // Bucle principal controlado por la señal
        while (!server_stop) {
            irc.run(); // Aquí dentro tu poll() debe tener un timeout corto (ej: 1000ms)
        }

    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    // Al salir del bucle, el destructor de 'irc' se llama AUTOMÁTICAMENTE
    // cerrando todos los fds y liberando la memoria.
    std::cout << "Servidor cerrado. ¡Buen trabajo en la evaluación!" << std::endl;
    return 0;
}