// MetricReader.cpp
#include "MetricReader.h"
#include <sstream>

namespace xost {
namespace share_mem_monitor {

MetricReader::MetricReader() :
    sharedMemoryFd(-1),
    sharedMemorySize(0),
    sharedMemoryPtr(nullptr) {}

MetricReader::~MetricReader() {
    if (sharedMemoryPtr != nullptr) {
        if (munmap(sharedMemoryPtr, sharedMemorySize) == -1) {
            LOG_ERROR("munmap failed for key: " << sharedMemoryKey);
        }
        sharedMemoryPtr = nullptr;
    }
    if (sharedMemoryFd != -1) {
        close(sharedMemoryFd);
        sharedMemoryFd = -1;
    }
}

bool MetricReader::init(const std::string& monitorKey, pid_t managerPid) {
    if (sharedMemoryPtr != nullptr) {
        LOG("Already initialized for key: " << sharedMemoryKey);
        return true;
    }

    std::stringstream ss_;
    ss_ << monitorKey << "_" << managerPid;
    sharedMemoryKey = ss_.str();

    sharedMemoryFd = shm_open(sharedMemoryKey.c_str(), O_RDONLY, 0);
    if (sharedMemoryFd == -1) {
        LOG_ERROR("shm_open failed for key: " << sharedMemoryKey);
        return false;
    }

    struct stat shm_stat;
    if (fstat(sharedMemoryFd, &shm_stat) == -1) {
        LOG_ERROR("fstat failed for key: " << sharedMemoryKey);
        close(sharedMemoryFd);
        sharedMemoryFd = -1;
        return false;
    }
    sharedMemorySize = shm_stat.st_size;

    sharedMemoryPtr = mmap(nullptr, sharedMemorySize, PROT_READ, MAP_SHARED, sharedMemoryFd, 0);
    if (sharedMemoryPtr == MAP_FAILED) {
        LOG_ERROR("mmap failed for key: " << sharedMemoryKey);
        close(sharedMemoryFd);
        sharedMemoryFd = -1;
        sharedMemorySize = 0;
        sharedMemoryPtr = nullptr;
        return false;
    }

    LOG("Successfully hooked to shared memory for key: " << sharedMemoryKey << " with size: " << sharedMemorySize);
    return true;
}

void* MetricReader::getData() const {
    return sharedMemoryPtr;
}

size_t MetricReader::getSize() const {
    return sharedMemorySize;
}

} // namespace share_mem_monitor
} // namespace xost


