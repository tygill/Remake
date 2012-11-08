#pragma once
#include <boost/ptr_container/ptr_unordered_map.hpp>
#include "gf/Exceptions.h"

namespace gf {

    template<class T, class U> class PtrHashMap
    {
    public:
        PtrHashMap();
        PtrHashMap(const PtrHashMap& other);
        ~PtrHashMap();

        PtrHashMap& operator=(const PtrHashMap& other);

        bool contains(T key) const;
        const U& get(T key) const;
        U& get(T key);
        bool add(T key, U* value);
        bool remove(T key);

        int size() const;
        bool empty() const;
        
        class Enumerator;
        
        Enumerator enumerator() const;

    private:
        boost::ptr_unordered_map<T, U> values;
    };

    template<class T, class U> class PtrHashMap<T, U>::Enumerator {
    public:
        Enumerator(const PtrHashMap<T, U>& owner);
        Enumerator(const Enumerator& other);
        ~Enumerator();
    
        Enumerator& operator=(const Enumerator& other);

        // C# style iterators
        void reset();
        bool moveNext();
        T currentKey() const;
        //const U& currentValue() const;
        U& currentValue();

    private:
        const PtrHashMap<T, U>* ownedBy;
        typename boost::ptr_unordered_map<T, U>::const_iterator itr;
    };

    template<class T, class U> PtrHashMap<T, U>::PtrHashMap() {}

    template<class T, class U> PtrHashMap<T, U>::PtrHashMap(const PtrHashMap<T, U>& other)
        : values(other.values) {}

    template<class T, class U> PtrHashMap<T, U>::~PtrHashMap() {}

    template<class T, class U> PtrHashMap<T, U>& PtrHashMap<T, U>::operator=(const PtrHashMap<T, U>& other) {
        values = other.values;
        return *this;
    }

    template<class T, class U> bool PtrHashMap<T, U>::contains(T key) const {
        return values.find(key) != values.end();
    }
    
    template<class T, class U> const U& PtrHashMap<T, U>::get(T key) const {
        typename boost::ptr_unordered_map<T, U>::const_iterator itr = values.find(key);
        if (itr != values.end()) {
            return *(itr->second);
        } else {
            // Should this throw an exception instead?
            return U();
        }
    }
    
    template<class T, class U> U& PtrHashMap<T, U>::get(T key) {
        typename boost::ptr_unordered_map<T, U>::iterator itr = values.find(key);
        if (itr != values.end()) {
            return *(itr->second);
        } else {
            throw InvalidContainerAccessException("PtrHashMap::get()");
        }
    }
    
    template<class T, class U> bool PtrHashMap<T, U>::add(T key, U* value) {
        if (!contains(key)) {
            values.insert(key, value);
            return true;
        } else {
            return false;
        }
    }

    template<class T, class U> bool PtrHashMap<T, U>::remove(T key) {
        return values.erase(key) > 0;
    }

    template<class T, class U> int PtrHashMap<T, U>::size() const {
        return values.size();
    }

    template<class T, class U> bool PtrHashMap<T, U>::empty() const {
        return values.empty();
    }
    
    template<class T, class U> typename PtrHashMap<T, U>::Enumerator PtrHashMap<T, U>::enumerator() const {
        return Enumerator(*this);
    }
    
    template<class T, class U> PtrHashMap<T, U>::Enumerator::Enumerator(const PtrHashMap<T, U>& owner)
        : ownedBy(&owner), itr(owner.values.end()) {}

    template<class T, class U> PtrHashMap<T, U>::Enumerator::Enumerator(typename const PtrHashMap<T, U>::Enumerator& other)
        : ownedBy(other.ownedBy), itr(other.itr) {}

    template<class T, class U> PtrHashMap<T, U>::Enumerator::~Enumerator() {}
    
    template<class T, class U> typename PtrHashMap<T, U>::Enumerator& PtrHashMap<T, U>::Enumerator::operator=(typename const PtrHashMap<T, U>::Enumerator& other) {
        ownedBy = other.owndedBy;
        itr = other.itr;
        return *this;
    }

    template<class T, class U> void PtrHashMap<T, U>::Enumerator::reset() {
        itr = ownedBy->values.end();
    }

    template<class T, class U> bool PtrHashMap<T, U>::Enumerator::moveNext() {
        if (itr == ownedBy->values.end()) {
            // We need to start the iterator over again
            itr = ownedBy->values.begin();
        } else {
            // Otherwise we just move to the next item
            ++itr;
        }

        return itr != ownedBy->values.end();
    }

    template<class T, class U> T PtrHashMap<T, U>::Enumerator::currentKey() const {
        // This had better not be called when the iterator points to nothing.
        // But if it is, it just returns the default T I believe
        return itr->first;
    }
    
    /*
    template<class T, class U> const U& PtrHashMap<T, U>::Enumerator::currentValue() const {
        // This had better not be called when the iterator points to nothing.
        //if (itr != ownedBy.values.end()) {
            return *(itr->second);
        //} else {
        //    return U();
        //}
    }
    */

    template<class T, class U> U& PtrHashMap<T, U>::Enumerator::currentValue() {
        // This had better not be called when the iterator points to nothing.
        return const_cast<U&>(*(itr->second)); // hack in const correctness...while this is kinda bad, its easier than making a whole second Enumerator class
    }

}
