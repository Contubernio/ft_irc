#ifndef SERVER_HPP
#define SERVER_HPP

#include "Client.hpp"
#include "Channel.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <poll.h>
#include <unistd.h>
#include <map>
#include <sstream>
#include <ctime>

class Server {
private:
    int         _port;
    std::string _password;
    int         _serverSocket;

    std::vector<struct pollfd> _fds;
    std::map<int, Client*> _clients;
    std::map<std::string, Channel*> _channels;

    // --- MÉTODOS DE RED (GESTIÓN INTERNA) ---
    void acceptNewConnection();
    void handleClientData(size_t &i);
    void processBuffer(Client* client, size_t &i);
    void executeCommand(Client* client, std::string message, size_t &i);
    void disconnectClient(size_t &i);

    // --- MÉTODOS AUXILIARES ---
    void    sendResponse(Client* client, std::string msg);
    Client* findClientByNick(std::string nick);

    // --- MANEJADORES DE COMANDOS (EL CEREBRO) ---
    // He añadido todos los que pide el subject + los que ya tienes
    void handlePass(Client* client, std::string message);
    void handleNick(Client* client, std::string message);
    void handleUser(Client* client, std::string message);
    void handleQuit(Client* client, std::string message, size_t &i);
    void handleJoin(Client* client, std::string message);
    void handlePrivmsg(Client* client, std::string message);
    void handleInvite(Client* client, std::string message);
    void handleTopic(Client* client, std::string message);
    void handleKick(Client* client, std::string message);
    void handleList(Client* client, std::string message);
    void handlePart(Client* client, std::string message);
    void handleMode(Client* client, std::string message);
    void handleNotice(Client* client, std::string message);
    void checkBotCommands(Client* client, std::string target, std::string message);
    void sendWelcome(Client* client);

public:
    Server(int port, std::string password);
    ~Server();

    void init();
    void run();
};

#endif