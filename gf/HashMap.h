#pragma once
#include <boost/unordered_map.hpp>
#include "gf/Exceptions.h"

namespace gf {

    template<class T, class U> class HashMap
    {
    public:
        HashMap();
        HashMap(const HashMap& other);
        ~HashMap();

        HashMap& operator=(const HashMap& other);

        bool contains(T key) const;
        U get(T key) const;
        bool add(T key, U value);
        bool remove(T key);

        int size() const;
        bool empty() const;

        class Enumerator;

        Enumerator enumerator() const;

    private:
        boost::unordered_map<T, U> values;
    };

    template<class T, class U> class HashMap<T, U>::Enumerator {
    public:
        Enumerator(const HashMap<T, U>& owner);
        Enumerator(const Enumerator& other);
        ~Enumerator();

        Enumerator& operator=(const Enumerator& other);
    
        // C# style iterators
        void reset();
        bool moveNext();
        T currentKey() const;
        U currentValue() const;

    private:
        const HashMap<T, U>* ownedBy;
        typename boost::unordered_map<T, U>::const_iterator itr;
    };
    
    template<class T, class U> HashMap<T, U>::HashMap() {}

    template<class T, class U> HashMap<T, U>::HashMap(const HashMap<T, U>& other)
        : values(other.values) {}

    template<class T, class U> HashMap<T, U>::~HashMap() {}

    template<class T, class U> HashMap<T, U>& HashMap<T, U>::operator=(const HashMap<T, U>& other) {
        values = other.values;
        return *this;
    }

    template<class T, class U> bool HashMap<T, U>::contains(T key) const {
        return values.find(key) != values.end();
    }

    template<class T, class U> U HashMap<T, U>::get(T key) const {
        typename boost::unordered_map<T, U>::const_iterator itr = values.find(key);
        if (itr != values.end()) {
            return itr->second;
        } else {
            throw InvalidContainerAccessException("HashMap::get()");
        }
    }
    
    template<class T, class U> bool HashMap<T, U>::add(T key, U value) {
        return values.insert(std::make_pair(key, value)).second;
    }

    template<class T, class U> bool HashMap<T, U>::remove(T key) {
        return values.erase(key) > 0;
    }

    template<class T, class U> int HashMap<T, U>::size() const {
        return values.size();
    }

    template<class T, class U> bool HashMap<T, U>::empty() const {
        return values.empty();
    }

    template<class T, class U> typename HashMap<T, U>::Enumerator HashMap<T, U>::enumerator() const {
        return Enumerator(*this);
    }
    
    template<class T, class U> HashMap<T, U>::Enumerator::Enumerator(const HashMap<T, U>& owner)
        : ownedBy(&owner), itr(owner.values.end()) {}

    template<class T, class U> HashMap<T, U>::Enumerator::Enumerator(typename const HashMap<T, U>::Enumerator& other)
        : ownedBy(other.ownedBy), itr(other.itr) {}

    template<class T, class U> HashMap<T, U>::Enumerator::~Enumerator() {}
    
    template<class T, class U> typename HashMap<T, U>::Enumerator& HashMap<T, U>::Enumerator::operator=(typename const HashMap<T, U>::Enumerator& other) {
        ownedBy = other.owndedBy;
        itr = other.itr;
        return *this;
    }

    template<class T, class U> void HashMap<T, U>::Enumerator::reset() {
        itr = ownedBy->values.end();
    }

    template<class T, class U> bool HashMap<T, U>::Enumerator::moveNext() {
        if (itr == ownedBy->values.end()) {
            // We need to start the iterator over again
            itr = ownedBy->values.begin();
        } else {
            // Otherwise we just move to the next item
            ++itr;
        }

        return itr != ownedBy->values.end();
    }

    template<class T, class U> T HashMap<T, U>::Enumerator::currentKey() const {
        // This had better not be called when the iterator points to nothing.
        // But if it is, it just returns the default T I believe
        return itr->first;
    }

    template<class T, class U> U HashMap<T, U>::Enumerator::currentValue() const {
        // This had better not be called when the iterator points to nothing.
        // But if it is, it just returns the default U I believe
        // It might complain if there is no default U() though...
        return itr->second;
    }

}
