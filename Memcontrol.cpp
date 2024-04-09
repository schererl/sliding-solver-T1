
#include <memory>
#include <iostream>
#include <cstddef> // for size_t
#include "Memcontrol.h"
AllocationMetrics alloc_metrics;
uint64_t AllocationMetrics::CurrentUsage() const { return total_alloc - total_freed; }


void* operator new(size_t size) {
    // if (size + alloc_metrics.CurrentUsage() > MEMORY_LIMIT_GB * 1024 * 1024 * 1024) {
    //     throw std::bad_alloc();
    // }
    alloc_metrics.total_alloc += size;
    return malloc(size);
}

void operator delete(void* memory, size_t size) {
    alloc_metrics.total_freed += size;
    free(memory);
}

void PrintMemoryUsage() {
    double memoryUsageGB = static_cast<double>(alloc_metrics.CurrentUsage()) / (1024 * 1024 * 1024);
    std::cout << "Memory Usage: " << memoryUsageGB << " GB" << std::endl;
}

bool IsMemoryLimitExceeded() {
    return alloc_metrics.CurrentUsage() > static_cast<uint64_t>(MEMORY_LIMIT_GB) * 1024 * 1024 * 1024;
}


