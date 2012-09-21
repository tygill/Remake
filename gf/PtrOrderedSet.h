#pragma once
#include <boost/ptr_container/ptr_set.hpp>

namespace gf {

    template<class T> class PtrOrderedSet
    {
    public:
        PtrOrderedSet();
        PtrOrderedSet(const PtrOrderedSet& other);
        ~PtrOrderedSet();

        bool contains(T* value) const;
        bool add(T* value);
        bool remove(T* value);

        int size() const;
        bool empty() const;
    
        // C# style iterators
        void reset();
        bool moveNext();
        T& current() const;

    private:
        boost::ptr_set<T> values;
    };

}
