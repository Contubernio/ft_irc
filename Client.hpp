#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <string>

class Client {
private:
    int         _fd;
    std::string _nickname;
    std::string _buffer;
    bool        _isAuthenticated;
    bool        _isRegistered;

public:
    Client(int fd);
    ~Client();

    // Getters y Setters
    int         getFd() const;
    std::string getNickname() const;
    void        setNickname(const std::string& nick);
    
    bool        isAuthenticated() const;
    void        setAuthenticated(bool status);
    
    bool        isRegistered() const;
    void        setRegistered(bool status);

    // Gestión de Buffer
    void        addToBuffer(std::string str);
    std::string getBuffer() const;
    void        setBuffer(std::string str);
};

#endif