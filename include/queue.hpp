#include "deque.hpp"

template <typename T>
class Queue {
private:
    Deque<T> deque;

public:
    void enqueue(const T& val) {
        deque.push_back(val);
    }

    void dequeue() {
        if (isEmpty()) {
            throw std::out_of_range("Queue is empty");
        }
        deque.pop_front();
    }

    T& front() {
        if (isEmpty()) {
            throw std::out_of_range("Queue is empty");
        }
        return deque[0];
    }

    bool isEmpty() const {
        return deque.size() == 0;
    }

    size_t size() const {
        return deque.size();
    }
};