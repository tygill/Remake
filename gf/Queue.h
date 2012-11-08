#pragma once
#include <queue>

namespace gf {

    template<class T> class Queue
    {
    public:
        Queue();
        Queue(const Queue& other);
        ~Queue();

        T front() const;
        void enqueue(T value);
        T dequeue();

        int size() const;
        bool empty() const;
    
    private:
        std::queue<T> values;
    };

    template<class T> Queue<T>::Queue() {}

    template<class T> Queue<T>::Queue(const Queue<T>& other)
        : values(other.values) {}

    template<class T> Queue<T>::~Queue() {}

    template<class T> T Queue<T>::front() const {
        return values.front();
    }

    template<class T> void Queue<T>::enqueue(T value) {
        values.push(value);
    }

    template<class T> T Queue<T>::dequeue() {
        return values.pop();
    }

    template<class T> int Queue<T>::size() const {
        return values.size();
    }

    template<class T> bool Queue<T>::empty() const {
        return values.empty();
    }

}
