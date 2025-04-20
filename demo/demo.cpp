// demo/demo.cpp

#include <xost/mailbox/Mailbox.h>
#include <xost/concurr/CompletableFuture.h>

int main() {
    Mailbox myMailbox;
    myMailbox.sayHello();

    CompletableFuture completableFuture;
    completableFuture.printHello();
    return 0;
}