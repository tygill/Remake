#pragma once
#include <boost/unordered_set.hpp>

namespace gf {

    // This class provides a standardized, simplified wrapper around boost::unordered_set that doesn't have to deal with iterators when adding, removing, and checking for values.
    template<class T> class HashSet
    {
    public:
        HashSet();
        template<class Itr> HashSet(Itr begin, Itr end);
        HashSet(const HashSet& other);
        ~HashSet();

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
        boost::unordered_set<T> values;
    };

}
