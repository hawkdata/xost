// metric_manager.h
#ifndef METRIC_MANAGER_H
#define METRIC_MANAGER_H

#include <string>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdexcept>
#include "common/common.h"

namespace xost::share_mem_monitor {

    class MetricManager {
    public:
        explicit MetricManager(const std::string& monitorKey);
        ~MetricManager();

        bool setup(size_t size);
        [[nodiscard]] void* getDataPtr() const;
        [[nodiscard]] size_t getSize() const;

    private:
        std::string monitorKey;
        std::string sharedMemoryKey;
        int sharedMemoryFd = -1;
        void* sharedMemoryPtr = nullptr;
        size_t sharedMemorySize = 0;

        bool createSharedMemory(size_t size);
    };

} // namespace xost::share_mem_monitor

#endif // METRIC_MANAGER_H