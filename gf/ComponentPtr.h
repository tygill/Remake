#pragma once
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>

#include "gf/Component.h"
#include "gf/ComponentLock.h"

namespace gf {

    // TODO:
    // Currently, the Entity class is set to provide enforcement of read/write and read only loading of components at the access layer.
    // This class also supports locking for both read/write or read only, but has no plans for enforcing it at the compile/runtime level.
    // If there is a doable method for this that doesn't complicate its use too much, look into it.
    template<class T> class ComponentPtr
    {
    public:
        ComponentPtr(T* comp, bool lockNow = true, bool isUniqueLock = true);
        ComponentPtr(boost::shared_ptr<T> comp, bool lockNow = true, bool isUniqueLock = true);
        ComponentPtr(boost::shared_ptr<T> comp, const ComponentLock& otherLock, bool isUniqueLock);
        ~ComponentPtr();

        // Smart pointer-ness
        T& operator*() const;
        T* operator->() const;
        operator bool() const;
        ComponentPtr& operator=(const ComponentPtr& other);

        // Casting
        template<class U> ComponentPtr<U> staticCast() const; // Should be fine for our use, as we should never be doing illegal casting with ComponentTypes to check for us.
        template<class U> ComponentPtr<U> dynamicCast() const;
        template<class U> ComponentPtr<U> constCast() const;

    private:
        boost::shared_ptr<T> component;
        ComponentLock lock;
    };
    
    template<class T> ComponentPtr<T>::ComponentPtr(T* comp, bool lockNow, bool isUniqueLock)
        : component(comp), lock(component->type(), lockNow, isUniqueLock) {}

    template<class T> ComponentPtr<T>::ComponentPtr(boost::shared_ptr<T> comp, bool lockNow, bool isUniqueLock)
        : component(comp), lock(component->type(), lockNow, isUniqueLock) {}

    template<class T> ComponentPtr<T>::ComponentPtr(boost::shared_ptr<T> comp, const ComponentLock& otherLock, bool isUniqueLock)
        : component(comp), lock(otherLock) {}

    template<class T> ComponentPtr<T>::~ComponentPtr() {}

    template<class T> T& ComponentPtr<T>::operator*() const {
        return *component;
    }

    template<class T> T* ComponentPtr<T>::operator->() const {
        return component.get();
    }

    template<class T> ComponentPtr<T>::operator bool() const {
        return (bool)component;
    }

    template<class T> ComponentPtr<T>& ComponentPtr<T>::operator=(const ComponentPtr<T>& other) {
        component = other.component;
        lock = other.lock;
        uniqueLock = other.uniqueLock;
        return *this;
    }

    template<class T> template<class U> ComponentPtr<U> ComponentPtr<T>::staticCast() const {
        return ComponentPtr<U>(boost::static_pointer_cast<U>(component), lock, lock.unique());
    }

    template<class T> template<class U> ComponentPtr<U> ComponentPtr<T>::dynamicCast() const {
        return ComponentPtr<U>(boost::dynamic_pointer_cast<U>(component), lock, lock.unique());
    }

    template<class T> template<class U> ComponentPtr<U> ComponentPtr<T>::constCast() const {
        return ComponentPtr<U>(boost::const_pointer_cast<U>(component), lock, lock.unique());
    }

}
