
    #include "metricshm/MetricManager.h"
    #include <iostream>
    #include <unistd.h>
    #include <cstring>

using namespace xost::share_mem_monitor;
using namespace std;

int main() {
    const string monitorKey = "my_metric";
    const size_t sharedMemorySize = 1024;

    MetricManager manager(monitorKey);
    if (!manager.setup(sharedMemorySize)) {
        LOG_ERROR("Producer failed to setup shared memory");
        return 1;
    }

    // Write data to shared memory in a loop, stop after 2 minutes
    char* data = static_cast<char*>(manager.getDataPtr());
    const char* messagePrefix = "Hello from producer process with PID: ";
    int counter = 0;
    auto startTime = chrono::steady_clock::now();
    while (chrono::duration_cast<chrono::minutes>(chrono::steady_clock::now() - startTime).count() < 2) {
        string fullMessage = string(messagePrefix) + to_string(getpid()) + " - " + to_string(counter);
        strncpy(data, fullMessage.c_str(), sharedMemorySize - 1);
        data[sharedMemorySize - 1] = '\0'; // Ensure null termination

        LOG("Producer process wrote data: " << fullMessage);
        counter++;
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
    LOG("Producer process finished after 2 minutes.");
    return 0;
}