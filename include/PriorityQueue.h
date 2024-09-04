//
// Created by leth1 on 7/12/2024.
//

#ifndef CHESS_PRIORITYQUEUE_H
#define CHESS_PRIORITYQUEUE_H

#include <vector>
#include <stdexcept>
#include <mutex>
#include "Location.h"

// Comparator class to define the priority
struct MyComparator {
    int operator()(int a, int b) const {
        return a - b;
    }
};

class PriorityQueue {
public:
    void push(const Location& value);
    Location poll();
    bool isEmpty() const;

private:
    std::vector<Location> heap;
    mutable std::mutex mutex_;

};

#endif //CHESS_PRIORITYQUEUE_H