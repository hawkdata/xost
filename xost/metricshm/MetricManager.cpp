
// metric_manager.cpp
#include "MetricManager.h"
#include <sstream>
#include <cstring>

namespace xost::share_mem_monitor {

MetricManager::MetricManager(const std::string& monitorKey) : monitorKey(monitorKey) {}

MetricManager::~MetricManager() {
    if (sharedMemoryPtr != nullptr) {
        if (munmap(sharedMemoryPtr, sharedMemorySize) == -1) {
            LOG_ERROR("munmap failed for key: " << sharedMemoryKey);
        }
    }
    if (sharedMemoryFd != -1) {
        if (close(sharedMemoryFd) == -1) {
            LOG_ERROR("close failed for key: " << sharedMemoryKey);
        }
        if (shm_unlink(sharedMemoryKey.c_str()) == -1) {
            LOG_ERROR("shm_unlink failed for key: " << sharedMemoryKey);
        }
    }
}

bool MetricManager::setup(size_t size) {
    pid_t pid = getpid();
    std::stringstream ss_;
    ss_ << "/" << monitorKey << "_" << pid;
    sharedMemoryKey = ss_.str();
    sharedMemorySize = size;

    // Check if shared memory object already exists
    sharedMemoryFd = shm_open(sharedMemoryKey.c_str(), O_RDWR, 0666);
    if (sharedMemoryFd == -1) {
        if (errno == ENOENT) {
            // Shared memory object does not exist, create it
            return createSharedMemory(size);
        } else {
            LOG_ERROR("shm_open failed for key: " << sharedMemoryKey << ", error: " << std::strerror(errno));
            return false;
        }
    } else {
        // Shared memory object exists, map it
        sharedMemoryPtr = mmap(nullptr, sharedMemorySize, PROT_READ | PROT_WRITE, MAP_SHARED, sharedMemoryFd, 0);
        if (sharedMemoryPtr == MAP_FAILED) {
            LOG_ERROR("mmap failed for existing key: " << sharedMemoryKey << ", error: " << strerror(errno));
            close(sharedMemoryFd);
            sharedMemoryFd = -1;
            return false;
        }
        LOG("Successfully hooked to existing shared memory: " << sharedMemoryKey);
        return true;
    }
}

void* MetricManager::getDataPtr() const {
    return sharedMemoryPtr;
}

size_t MetricManager::getSize() const {
    return sharedMemorySize;
}

bool MetricManager::createSharedMemory(size_t size) {
    sharedMemoryFd = shm_open(sharedMemoryKey.c_str(), O_CREAT | O_RDWR, 0666);
    if (sharedMemoryFd == -1) {
        LOG_ERROR("shm_open (creation) failed for key: " << sharedMemoryKey << ", error: " << strerror(errno));
        return false;
    }

    if (ftruncate(sharedMemoryFd, size) == -1) {
        LOG_ERROR("ftruncate failed for key: " << sharedMemoryKey << ", error: " << strerror(errno));
        close(sharedMemoryFd);
        shm_unlink(sharedMemoryKey.c_str());
        sharedMemoryFd = -1;
        return false;
    }

    sharedMemoryPtr = mmap(nullptr, sharedMemorySize, PROT_READ | PROT_WRITE, MAP_SHARED, sharedMemoryFd, 0);
    if (sharedMemoryPtr == MAP_FAILED) {
        LOG_ERROR("mmap failed for newly created key: " << sharedMemoryKey << ", error: " << strerror(errno));
        close(sharedMemoryFd);
        shm_unlink(sharedMemoryKey.c_str());
        sharedMemoryFd = -1;
        return false;
    }

    LOG("Successfully created and mapped shared memory: " << sharedMemoryKey << " with size: " << sharedMemorySize);
    return true;
}

} // namespace xost::share_mem_monitor