#include "Server.hpp"
#include <iostream>
#include <signal.h>
#include <stdlib.h>
#include <string>
#include <limits>
#include <cctype> // Para isdigit e isspace

// Variable global para que la señal pueda detener el bucle
bool server_stop = false;

// Manejador de la señal Ctrl+C
void signalHandler(int signum) {
    (void)signum;
    std::cout << "\n[!] Deteniendo el servidor de forma segura..." << std::endl;
    server_stop = true;
}

/**
 * Función auxiliar para validar si una cadena es un número positivo
 */
bool isValidPort(const std::string& str) {
    if (str.empty()) return false;
    for (size_t i = 0; i < str.length(); i++) {
        if (!isdigit(str[i])) return false;
    }
    return true;
}

/**
 * Función auxiliar para validar que el password no sea solo espacios
 */
bool isOnlySpaces(const std::string& str) {
    if (str.empty()) return true;
    for (size_t i = 0; i < str.length(); i++) {
        if (!isspace(str[i])) return false;
    }
    return true;
}

int main(int argc, char **argv) {
    // 1. Validar número de argumentos
    if (argc != 3) {
        std::cerr << "Uso: ./ircserv <puerto> <password>" << std::endl;
        return 1;
    }

    // 2. Validar puerto (solo dígitos)
    std::string portStr = argv[1];
    if (!isValidPort(portStr)) {
        std::cerr << "Error: El puerto '" << portStr << "' no es un número válido." << std::endl;
        return 1;
    }

    // 3. Validar rango del puerto (1024 - 65535)
    long portCheck = atol(argv[1]);
    if (portCheck < 1024 || portCheck > 65535) {
        std::cerr << "Error: Puerto fuera de rango. Usa uno entre 1024 y 65535." << std::endl;
        return 1;
    }
    int port = static_cast<int>(portCheck);

    // 4. Validar password (que no esté vacío ni sean solo espacios)
    std::string password = argv[2];
    if (isOnlySpaces(password)) {
        std::cerr << "Error: El password no puede estar vacío o contener solo espacios." << std::endl;
        return 1;
    }

    // Registramos la señal
    signal(SIGINT, signalHandler);

    try {
        Server irc(port, password);
        irc.init();

        std::cout << "--- SERVIDOR IRC 42 INICIADO ---" << std::endl;
        std::cout << "Puerto: " << port << " | Pass: [" << password << "]" << std::endl;
        std::cout << "Presiona Ctrl+C para salir limpiamente." << std::endl;

        // Bucle principal controlado por la señal
        while (!server_stop) {
            irc.run(); 
        }

    } catch (const std::exception &e) {
        std::cerr << "Error crítico: " << e.what() << std::endl;
        return 1;
    }

    std::cout << "Servidor cerrado. ¡Buen trabajo en la evaluación!" << std::endl;
    return 0;
}