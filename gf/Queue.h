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

}
