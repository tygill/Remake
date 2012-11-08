#pragma once
#include <set>

namespace gf {

    // This class provides a standardized, simplified wrapper around std::set that doesn't have to deal with iterators when adding, removing, and checking for values.
    // EntityIds, ComponentTypes and other tree sets are typedefs of this class.
    template<class T> class OrderedSet
    {
    public:
        OrderedSet();
        //template<class Itr> OrderedSet(Itr begin, Itr end);
        OrderedSet(const OrderedSet& other);
        ~OrderedSet();

        bool contains(T value) const;
        bool add(T value);
        bool remove(T value);

        int size() const;
        bool empty() const;
        
        class Enumerator;

        Enumerator enumerator() const;

    private:
        std::set<T> values;
    };

    template<class T> class OrderedSet<T>::Enumerator {
    public:
        Enumerator(const OrderedSet<T>& owner);
        Enumerator(const Enumerator& other);
        ~Enumerator();
    
        Enumerator& operator=(const Enumerator& other);

        // C# style iterators
        void reset();
        bool moveNext();
        T current() const;

    private:
        const OrderedSet<T>* ownedBy;
        typename std::set<T>::const_iterator itr;

    };

    template<class T> OrderedSet<T>::OrderedSet() {}

    //template<class T, class Itr> OrderedSet<T>::OrderedSet(Itr begin, Itr end)
    //    : values(begin, end) {}

    template<class T> OrderedSet<T>::OrderedSet(const OrderedSet& other)
        : values(other.values) {}

    template<class T> OrderedSet<T>::~OrderedSet() {}

    template<class T> bool OrderedSet<T>::contains(T value) const {
        return values.find(value) != values.end();
    }

    template<class T> bool OrderedSet<T>::add(T value) {
        return values.insert(value).second;
    }

    template<class T> bool OrderedSet<T>::remove(T value) {
        typename std::set<T>::iterator itr = values.find(value);
        if (itr != values.end()) {
            values.erase(itr);
            return true;
        } else {
            return false;
        }
    }

    template<class T> int OrderedSet<T>::size() const {
        return values.size();
    }

    template<class T> bool OrderedSet<T>::empty() const {
        return values.size() == 0;
    }

    template<class T> typename OrderedSet<T>::Enumerator OrderedSet<T>::enumerator() const {
        return Enumerator(*this);
    }

    template<class T> OrderedSet<T>::Enumerator::Enumerator(const OrderedSet<T>& owner)
        : ownedBy(&owner), itr(owner.values.end()) {}

    template<class T> OrderedSet<T>::Enumerator::Enumerator(typename const OrderedSet<T>::Enumerator& other)
        : ownedBy(other.ownedBy), itr(other.itr) {}

    template<class T> OrderedSet<T>::Enumerator::~Enumerator() {}

    template<class T> typename OrderedSet<T>::Enumerator& OrderedSet<T>::Enumerator::operator=(typename const OrderedSet<T>::Enumerator& other) {
        ownedBy = other.ownedBy;
        itr = other.itr;
        return *this;
    }

    template<class T> void OrderedSet<T>::Enumerator::reset() {
        itr = ownedBy->values.end();
    }

    template<class T> bool OrderedSet<T>::Enumerator::moveNext() {
        if (itr == ownedBy->values.end()) {
            // We need to start the iterator over again
            itr = ownedBy->values.begin();
        } else {
            // Otherwise we just move to the next item
            ++itr;
        }

        return itr != ownedBy->values.end();
    }

    template<class T> T OrderedSet<T>::Enumerator::current() const {
        // This had better not be called when the iterator points to nothing.
        // But if it is, it just returns the default T I believe
        return *itr;
    }

}
