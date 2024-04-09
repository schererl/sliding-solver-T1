#ifndef MEMCONTROL_H
#define MEMCONTROL_H

#include <memory>
#include <iostream>
#include <cstddef>

#define MEMORY_LIMIT_GB 8
#define NODE_SIZE sizeof(Node)
#define MAX_NODES (static_cast<uint64_t>(MEMORY_LIMIT_GB) * 1024 * 1024 * 1024) / NODE_SIZE

struct AllocationMetrics{
    uint64_t total_alloc = 0;
    uint64_t total_freed = 0;
    uint64_t CurrentUsage() const;
};


extern AllocationMetrics alloc_metrics;
void* operator new(size_t size);
void operator delete(void* memory, size_t size);
void PrintMemoryUsage();
bool IsMemoryLimitExceeded();

#endif // MEMCONTROL_H
