#ifndef SFCOMMON_H
#define SFCOMMON_H

#include <exception>
#include <string>

class SFException : public std::exception {
    
public:
    SFException(std::string message) : message(message) {}

    virtual const char* what() const throw() { return message.c_str(); }
    
private:
    std::string message;
};

// Forward declaration of classes
class SFEvent;
class SFAsset;

#endif
