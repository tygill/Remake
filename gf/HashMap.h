#pragma once
#include <boost/unordered_map.hpp>

namespace gf {

    template<class T, class U> class HashMap
    {
    public:
        HashMap();
        HashMap(const HashMap& other);
        ~HashMap();

        bool contains(T key) const;
        U get(T key) const;
        U add(T key, U value);
        U remove(T key);

        int size() const;
        bool empty() const;
    
        // C# style iterators
        void reset();
        bool moveNext();
        T currentKey() const;
        U currentValue() const;

    private:
        boost::unordered_map<T, U> values;
    };

}
