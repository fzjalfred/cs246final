#ifndef RESOURCE_H
#define RESOURCE_H 
#include <iostream>
#include <string>

class Resource {
    std::string type;
    int num;

    public:
    explicit Resource(std::string, int);
    friend std::ostream &operator<<(std::ostream &out, const Resource &r);
};

std::ostream &operator<<(std::ostream &out, const Resource &r);

#endif
