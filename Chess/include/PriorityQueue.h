#pragma once

#include <list>
#include <algorithm>
#include <stdexcept>  
#include <sstream>     
#include <string>  

template <typename T, typename Comparator>
class PriorityQueue {
private:
    size_t maxSize;
    std::list<T> data;
    Comparator comp;

    void flipUp(typename std::list<T>::iterator it) {
        if (it == data.begin()) return;
        auto idx = std::distance(data.begin(), it);
        auto parentIdx = (idx - 1) / 2;
        auto parentIt = std::next(data.begin(), parentIdx);
        if (comp(*it, *parentIt) > 0) {
            std::iter_swap(it, parentIt);
            flipUp(parentIt);
        }
    }

public:
    explicit PriorityQueue(size_t maxSize = 5)
        : maxSize(maxSize)
    {}

    bool isEmpty() const {
        return data.empty();
    }

    void push(const T& element) {
        data.push_back(element);
        flipUp(std::prev(data.end()));
        if (data.size() > maxSize) {
            data.pop_back();
        }
    }

    T poll() {
        if (isEmpty()) {
            throw std::runtime_error("Heap is empty!");
        }
        T top = data.front();
        data.pop_front();
        return top;
    }
};