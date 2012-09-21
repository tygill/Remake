#pragma once
#include <boost/ptr_container/ptr_unordered_map.hpp>

namespace gf {

    template<class T, class U> class PtrHashMap
    {
    public:
        PtrHashMap();
        PtrHashMap(const PtrHashMap& other);
        ~PtrHashMap();

        bool contains(T key) const;
        U& get(T key) const;
        U& add(T key, U* value);
        bool remove(T key);

        int size() const;
        bool empty() const;

        // C# style iterators
        void reset();
        bool moveNext();
        T currentKey() const;
        U currentValue() const;

    private:
        boost::ptr_unordered_map<T, U> values;
    };

}
