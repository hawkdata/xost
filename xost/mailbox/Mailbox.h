// mailbox.h (Header file)

#ifndef MAILBOX_H
#define MAILBOX_H

#include <iostream>

class Mailbox {
public:
    Mailbox(); // Default constructor
    ~Mailbox(); // Destructor
    void sayHello(); // Member function to print "Hello"
};

#endif // MAILBOX_H