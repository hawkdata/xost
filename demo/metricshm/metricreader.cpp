
#include "metricshm/MetricReader.h"
#include <iostream>
#include <unistd.h>

using namespace xost::share_mem_monitor;
using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <writer_pid>" << endl;
        return 1;
    }

    const string monitorKey = "my_metric";
    pid_t writerPid = atoi(argv[1]);

    MetricReader reader;
    if (!reader.init(monitorKey, writerPid)) {
        LOG_ERROR("Reader failed to initialize shared memory");
        return 1;
    }

    // Read data from shared memory
    const char* receivedData = static_cast<const char*>(reader.getData());
    if (receivedData) {
        LOG("Reader process read data: " << receivedData);
    } else {
        LOG_ERROR("Reader process read null data");
    }

    return 0;
}
