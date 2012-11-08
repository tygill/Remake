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
    
        class Enumerator;

        Enumerator enumerator() const;

    private:
        boost::ptr_set<T> values;
    };

    template<class T> class PtrOrderedSet<T>::Enumerator {
    public:
        Enumerator(const PtrOrderedSet<T>& owner);
        Enumerator(const Enumerator& other);
        ~Enumerator();

        Enumerator& operator=(const Enumerator& other);
    
        // C# style iterators
        void reset();
        bool moveNext();
        T& current() const;

    private:
        const PtrOrderedSet<T>* ownedBy;
        typename boost::ptr_set<T>::const_iterator itr;
    };
    
    template<class T> PtrOrderedSet<T>::PtrOrderedSet() {}

    //template<class T, class Itr> PtrOrderedSet<T>::PtrOrderedSet(Itr begin, Itr end)
    //    : values(begin, end) {}

    template<class T> PtrOrderedSet<T>::PtrOrderedSet(const PtrOrderedSet<T>& other)
        : values(other.values) {}

    template<class T> PtrOrderedSet<T>::~PtrOrderedSet() {}

    template<class T> bool PtrOrderedSet<T>::contains(T* value) const {
        return values.find(value) != values.end();
    }

    template<class T> bool PtrOrderedSet<T>::add(T* value) {
        return values.insert(value).second;
    }

    template<class T> bool PtrOrderedSet<T>::remove(T* value) {
        typename std::set<T>::iterator itr = values.find(value);
        if (itr != values.end()) {
            values.erase(itr);
            return true;
        } else {
            return false;
        }
    }

    template<class T> int PtrOrderedSet<T>::size() const {
        return values.size();
    }

    template<class T> bool PtrOrderedSet<T>::empty() const {
        return values.size() == 0;
    }

    template<class T> typename PtrOrderedSet<T>::Enumerator PtrOrderedSet<T>::enumerator() const {
        return Enumerator(*this);
    }

    template<class T> PtrOrderedSet<T>::Enumerator::Enumerator(const PtrOrderedSet<T>& owner)
        : ownedBy(&owner), itr(owner.values.end()) {}

    template<class T> PtrOrderedSet<T>::Enumerator::Enumerator(typename const PtrOrderedSet<T>::Enumerator& other)
        : ownedBy(other.ownedBy), itr(other.itr) {}

    template<class T> PtrOrderedSet<T>::Enumerator::~Enumerator() {}

    template<class T> typename PtrOrderedSet<T>::Enumerator& PtrOrderedSet<T>::Enumerator::operator=(typename const PtrOrderedSet<T>::Enumerator& other) {
        ownedBy = other.owndedBy;
        itr = other.itr;
        return *this;
    }

    template<class T> void PtrOrderedSet<T>::Enumerator::reset() {
        itr = ownedBy->values.end();
    }

    template<class T> bool PtrOrderedSet<T>::Enumerator::moveNext() {
        if (itr == ownedBy->values.end()) {
            // We need to start the iterator over again
            itr = ownedBy->values.begin();
        } else {
            // Otherwise we just move to the next item
            ++itr;
        }

        return itr != ownedBy->values.end();
    }

    template<class T> T& PtrOrderedSet<T>::Enumerator::current() const {
        // This had better not be called when the iterator points to nothing.
        //if (itr != ownedBy->values.end()) {
            return const_cast<T&>(*itr);
        //} else {
        //    return T();
        //}
    }

}
