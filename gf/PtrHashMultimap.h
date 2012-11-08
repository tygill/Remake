#pragma once
#include <boost/ptr_container/ptr_unordered_map.hpp>
#include "gf/Exceptions.h"

namespace gf {

    template<class T, class U> class PtrHashMultimap
    {
    public:
        PtrHashMultimap();
        PtrHashMultimap(const PtrHashMultimap& other);
        ~PtrHashMultimap();

        PtrHashMultimap& operator=(const PtrHashMultimap& other);

        bool contains(T key) const;
        U& get(T key) const; // This will only get the first of the given key
        bool add(T key, U* value);
        bool remove(T key);
        
        int size() const;
        bool empty() const;
    
        class Enumerator;

        Enumerator enumerator() const;
        Enumerator enumerator(T key) const;

    private:
        boost::ptr_unordered_multimap<T, U> values;
    };

    template<class T, class U> class PtrHashMultimap<T, U>::Enumerator {
    public:
        Enumerator(const PtrHashMultimap<T, U>& owner);
        Enumerator(const PtrHashMultimap<T, U>& owner, T k);
        Enumerator(const Enumerator& other);
        ~Enumerator();
    
        Enumerator& operator=(const Enumerator& other);

        // C# style iterators
        void reset();
        bool moveNext();
        T currentKey() const;
        U& currentValue() const;

    private:
        const PtrHashMultimap<T, U>* ownedBy;
        typename boost::ptr_unordered_multimap<T, U>::const_iterator itr;
        typename boost::ptr_unordered_multimap<T, U>::const_iterator upperBound;
        bool singleKey;
        T key;
    };

    template<class T, class U> PtrHashMultimap<T, U>::PtrHashMultimap() {}

    template<class T, class U> PtrHashMultimap<T, U>::PtrHashMultimap(const PtrHashMultimap<T, U>& other)
        : values(other.values) {}

    template<class T, class U> PtrHashMultimap<T, U>::~PtrHashMultimap() {}

    template<class T, class U> PtrHashMultimap<T, U>& PtrHashMultimap<T, U>::operator=(const PtrHashMultimap<T, U>& other) {
        values = other.values;
        return *this;
    }

    template<class T, class U> bool PtrHashMultimap<T, U>::contains(T key) const {
        return values.find(key) != values.end();
    }

    template<class T, class U> U& PtrHashMultimap<T, U>::get(T key) const {
        boost::unordered_map<T, U>::const_iterator itr = values.find(key);
        if (itr != values.end()) {
            return *(itr->second);
        } else {
            throw InvalidContainerAccessException("PtrHashMultimap::get()");
        }
    }
    
    template<class T, class U> bool PtrHashMultimap<T, U>::add(T key, U* value) {
        return values.insert(std::make_pair(key, value)).second;
    }

    template<class T, class U> bool PtrHashMultimap<T, U>::remove(T key) {
        return values.erase(key) > 0;
    }

    template<class T, class U> int PtrHashMultimap<T, U>::size() const {
        return values.size();
    }

    template<class T, class U> bool PtrHashMultimap<T, U>::empty() const {
        return values.empty();
    }

    template<class T, class U> typename PtrHashMultimap<T, U>::Enumerator PtrHashMultimap<T, U>::enumerator() const {
        return Enumerator(*this);
    }

    template<class T, class U> typename PtrHashMultimap<T, U>::Enumerator PtrHashMultimap<T, U>::enumerator(T key) const {
        return Enumerator(*this, key);
    }
    
    template<class T, class U> PtrHashMultimap<T, U>::Enumerator::Enumerator(const PtrHashMultimap<T, U>& owner)
        : ownedBy(&owner), itr(owner.values.end()), singleKey(false) {}

    template<class T, class U> PtrHashMultimap<T, U>::Enumerator::Enumerator(const PtrHashMultimap<T, U>& owner, T k)
        : ownedBy(&owner), itr(owner.values.end()), upperBound(owner.values.upper_bound(k)), singleKey(true), key(k) {}

    template<class T, class U> PtrHashMultimap<T, U>::Enumerator::Enumerator(typename const PtrHashMultimap<T, U>::Enumerator& other)
        : ownedBy(other.ownedBy), itr(other.itr), upperBound(other.upperBound), singleKey(other.singleKey), key(other.key) {}

    template<class T, class U> PtrHashMultimap<T, U>::Enumerator::~Enumerator() {}
    
    template<class T, class U> typename PtrHashMultimap<T, U>::Enumerator& PtrHashMultimap<T, U>::Enumerator::operator=(typename const PtrHashMultimap<T, U>::Enumerator& other) {
        ownedBy = other.owndedBy;
        itr = other.itr;
        upperBound = other.upperBound;
        singleKey = other.singleKey;
        key = other.key;
        return *this;
    }

    template<class T, class U> void PtrHashMultimap<T, U>::Enumerator::reset() {
        if (!singleKey) {
            itr = ownedBy->values.end();
        } else {
            itr = upperBound;
        }
    }

    template<class T, class U> bool PtrHashMultimap<T, U>::Enumerator::moveNext() {
        if (!singleKey) {
            if (itr == ownedBy->values.end()) {
                // We need to start the iterator over again
                itr = ownedBy->values.begin();
            } else {
                // Otherwise we just move to the next item
                ++itr;
            }

            return itr != ownedBy->values.end();
        } else {
            if (itr == upperBound) {
                itr = ownedBy->values.lower_bound(key);
            } else {
                ++itr;
            }

            return itr != upperBound;
        }
    }

    template<class T, class U> T PtrHashMultimap<T, U>::Enumerator::currentKey() const {
        // This had better not be called when the iterator points to nothing.
        // But if it is, it just returns the default T I believe
        return itr->first;
    }

    template<class T, class U> U& PtrHashMultimap<T, U>::Enumerator::currentValue() const {
        // This had better not be called when the iterator points to nothing.
        // But if it is, it just returns the default T I believe
        return const_cast<U&>(*(itr->second));
    }

}
