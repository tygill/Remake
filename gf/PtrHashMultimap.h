#pragma once
#include <boost/ptr_container/ptr_unordered_map.hpp>

namespace gf {

    template<class T, class U> class PtrHashMultimap
    {
    public:
        PtrHashMultimap();
        PtrHashMultimap(const PtrHashMultimap& other);
        ~PtrHashMultimap();

        bool contains(T key) const;
        U& get(T key) const; // This will only get the first of the given key
        U& add(T key, U* value);
        bool remove(T key);

        // These methods provide the multipleness of the map, and rely on the current state of the map.
        reset(T key);
        bool moveNext(T key);
        U& currentValue(T key);

        int size() const;
        bool empty() const;
    
        // C# style iterators
        void reset();
        bool moveNext();
        T currentKey() const;
        U& currentValue() const;

    private:
        boost::ptr_unordered_multimap<T, U> values;
    };

}
