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
    
        class Enumerator;

        Enumerator enumerator() const;

    private:
        boost::unordered_set<T> values;
    };

    template<class T> class HashSet<T>::Enumerator {
    public:
        Enumerator(const HashSet<T>& owner);
        Enumerator(const Enumerator& other);
        ~Enumerator();

        Enumerator& operator=(const Enumerator& other);
    
        // C# style iterators
        void reset();
        bool moveNext();
        T current() const;

    private:
        const HashSet<T>* ownedBy;
        typename boost::unordered_set<T>::const_iterator itr;
    };
    
    template<class T> HashSet<T>::HashSet() {}

    template<class T> HashSet<T>::HashSet(const HashSet& other)
        : values(other.values) {}

    template<class T> HashSet<T>::~HashSet() {}

    template<class T> bool HashSet<T>::contains(T value) const {
        return values.find(value) != values.end();
    }

    template<class T> bool HashSet<T>::add(T value) {
        return values.insert(value).second;
    }

    template<class T> bool HashSet<T>::remove(T value) {
        typename boost::unordered_set<T>::iterator itr = values.find(value);
        if (itr != values.end()) {
            values.erase(itr);
            return true;
        } else {
            return false;
        }
    }

    template<class T> int HashSet<T>::size() const {
        return values.size();
    }

    template<class T> bool HashSet<T>::empty() const {
        return values.size() == 0;
    }

    template<class T> typename HashSet<T>::Enumerator HashSet<T>::enumerator() const {
        return Enumerator(*this);
    }

    template<class T> HashSet<T>::Enumerator::Enumerator(const HashSet<T>& owner)
        : ownedBy(&owner), itr(owner.values.end()) {}

    template<class T> HashSet<T>::Enumerator::Enumerator(typename const HashSet<T>::Enumerator& other)
        : ownedBy(other.ownedBy), itr(other.itr) {}

    template<class T> HashSet<T>::Enumerator::~Enumerator() {}
    
    template<class T> typename HashSet<T>::Enumerator& HashSet<T>::Enumerator::operator=(typename const HashSet<T>::Enumerator& other) {
        ownedBy = other.owndedBy;
        itr = other.itr;
        return *this;
    }

    template<class T> void HashSet<T>::Enumerator::reset() {
        itr = ownedBy->values.end();
    }

    template<class T> bool HashSet<T>::Enumerator::moveNext() {
        if (itr == ownedBy->values.end()) {
            // We need to start the iterator over again
            itr = ownedBy->values.begin();
        } else {
            // Otherwise we just move to the next item
            ++itr;
        }

        return itr != ownedBy->values.end();
    }

    template<class T> T HashSet<T>::Enumerator::current() const {
        // This had better not be called when the iterator points to nothing.
        // But if it is, it just returns the default T I believe
        return *itr;
    }

}
