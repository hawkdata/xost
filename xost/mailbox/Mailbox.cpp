// mailbox.cpp (Source file)

#include "Mailbox.h"

Mailbox::Mailbox() {
    std::cout << "Mailbox created." << std::endl;
}

Mailbox::~Mailbox() {
    std::cout << "Mailbox destroyed." << std::endl;
}

void Mailbox::sayHello() {
    std::cout << "Hello" << std::endl;
}
