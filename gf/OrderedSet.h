#pragma once
#include <set>

namespace gf {

    // This class provides a standardized, simplified wrapper around std::set that doesn't have to deal with iterators when adding, removing, and checking for values.
    // EntityIds, ComponentTypes and other tree sets are typedefs of this class.
    template<class T> class OrderedSet
    {
    public:
        OrderedSet();
        template<class Itr> OrderedSet(Itr begin, Itr end);
        OrderedSet(const OrderedSet& other);
        ~OrderedSet();

        bool contains(T value) const;
        bool add(T value);
        bool remove(T value);

        int size() const;
        bool empty() const;
        
        // C# style iterators
        void reset();
        bool moveNext();
        T current() const;

    private:
        std::set<T> values;
    };

}
