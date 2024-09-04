#include "../include/PriorityQueue.h"

void PriorityQueue::push(const Location& value) {
    std::lock_guard<std::mutex> lock(mutex_);
    heap.push_back(value);
}

Location PriorityQueue::poll() {
    std::lock_guard<std::mutex> lock(mutex_);
    if (heap.empty()) {
        throw std::out_of_range("Heap is empty");
    }
    Location top = heap.back();
    heap.pop_back();
    return top;
}

bool PriorityQueue::isEmpty() const {
    std::lock_guard<std::mutex> lock(mutex_);
    return heap.empty();
}
