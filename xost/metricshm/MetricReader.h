
// MetricReader.h
#ifndef METRIC_READER_H
#define METRIC_READER_H

#include "common/common.h"
#include <string>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

namespace xost {
    namespace share_mem_monitor {

        class MetricReader {
        public:
            MetricReader();
            ~MetricReader();

            bool init(const std::string& monitorKey, pid_t managerPid);
            void* getData() const;
            size_t getSize() const;

        private:
            std::string sharedMemoryKey;
            int sharedMemoryFd;
            size_t sharedMemorySize;
            void* sharedMemoryPtr;
        };

    } // namespace share_mem_monitor
} // namespace xost

#endif // METRIC_READER_H