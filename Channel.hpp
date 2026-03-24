#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <string>
#include <vector>
#include "Client.hpp"

class Channel {
private:
    std::string             _name;
    std::vector<Client*>    _members;
    std::string             _topic;
    Client* _admin; 
    
    // Campos para el modo +i
    bool                     _inviteOnly;      
    std::vector<std::string> _invitedNicks;    
    // campos para el modo +t
    bool                     _topicProtected;
    int _limit; // -1 si no hay límite
    std::string _key; // Vacío si no hay contraseña

public:
    Channel(std::string name);
    ~Channel();

    // Métodos básicos
    std::string getName() const;
    const std::vector<Client*>& getMembers() const;
    void addMember(Client* client);
    void removeMember(Client* client);
    void broadcast(std::string message, Client* exclude);
    std::string getNamesList();
    void setTopic(std::string newTopic);
    std::string getTopic() const;
    void setAdmin(Client* client);
    Client* getAdmin() const;

    // Métodos para Invitaciones (Solo la declaración)
    void setInviteOnly(bool status);
    bool isInviteOnly() const;
    void addGuest(std::string nick);
    bool isInvited(std::string nick) const;
    void removeGuest(std::string nick);

    //+t
    void setTopicProtected(bool status);
    bool isTopicProtected() const;
    //+l
    void setLimit(int limit) { _limit = limit; }
    int  getLimit() const { return _limit; }
    bool isFull() const {
        // Si el límite es > 0 y los miembros actuales son >= al límite
        if (_limit > 0 && (int)_members.size() >= _limit) return true;
        return false;
    }
    void setKey(std::string key) { _key = key; }
    std::string getKey() const { return _key; }

    bool isMember(Client* cl) const;
};

#endif