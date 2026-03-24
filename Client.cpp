#include "Client.hpp"

Client::Client(int fd) : _fd(fd), _isAuthenticated(false), _isRegistered(false) {}

Client::~Client() {}

int Client::getFd() const { return _fd; }

std::string Client::getNickname() const { return _nickname; }

void Client::setNickname(const std::string& nick) { _nickname = nick; }

bool Client::isAuthenticated() const { return _isAuthenticated; }

void Client::setAuthenticated(bool status) { _isAuthenticated = status; }

bool Client::isRegistered() const { return _isRegistered; }

void Client::setRegistered(bool status) { _isRegistered = status; }

void Client::addToBuffer(std::string str) { _buffer += str; }

std::string Client::getBuffer() const { return _buffer; }

void Client::setBuffer(std::string str) { _buffer = str; }