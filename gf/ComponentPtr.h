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
        ~ComponentPtr();

        // Smart pointer-ness
        T& operator*() const;
        T* operator->() const;
        bool operator bool() const;

        // Casting
        template<class U> ComponentPtr<U> staticCast() const; // Should be fine for our use, as we should never be doing illegal casting with ComponentTypes to check for us.
        template<class U> ComponentPtr<U> dynamicCast() const;

    private:
        boost::shared_ptr<T> component;
        ComponentLock lock;
    };

    template<class T> ComponentPtr::ComponentPtr(boost::shared_ptr<T> comp, bool lockNow = true, bool isUniqueLock = true)
            : component(comp), lock(Component::componentType<T>(), lockNow, isUniqueLock) {}

    template<class T> ComponentPtr::~ComponentPtr() {}

    template<class T> T& ComponentPtr::operator*() const {
        return *component;
    }

    template<class T> T* ComponentPtr::operator->() const {
        return component.get();
    }

    template<class T> bool ComponentPtr::operator bool() const {
        return (bool)component;
    }

    template<class T, class U> ComponentPtr<U> ComponentPtr::staticCast() const {
        return boost::static_pointer_cast<U>(component);
    }

    template<class T, class U> ComponentPtr<U> ComponentPtr::dynamicCast() const {
        return boost::dynamic_pointer_cast<U>(component);
    }

}
