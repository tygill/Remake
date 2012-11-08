#pragma once
#include <boost/shared_ptr.hpp>

#include "gf/Globals.h"

namespace gf {

    template<class T> class ResourcePtr
    {
    public:
        ResourcePtr(T* res);
        ResourcePtr(boost::shared_ptr<T> res);
        ~ResourcePtr();
        
        // Smart pointer-ness
        T& operator*() const;
        T* operator->() const;
        operator bool() const;
        ResourcePtr& operator=(const ResourcePtr& other);

        // Casting
        template<class U> ResourcePtr<U> staticCast() const; // Should be fine for our use, as we should never be doing illegal casting with ResourceTypes to check for us.
        template<class U> ResourcePtr<U> dynamicCast() const;
        template<class U> ResourcePtr<U> constCast() const;

    private:
        boost::shared_ptr<T> resource;
    };
    
    template<class T> ResourcePtr<T>::ResourcePtr(T* res)
        : resource(res) {}

    template<class T> ResourcePtr<T>::ResourcePtr(boost::shared_ptr<T> res)
        : resource(res) {}

    template<class T> ResourcePtr<T>::~ResourcePtr() {}

    template<class T> T& ResourcePtr<T>::operator*() const {
        return *resource;
    }

    template<class T> T* ResourcePtr<T>::operator->() const {
        return resource.get();
    }

    template<class T> ResourcePtr<T>::operator bool() const {
        return (bool)resource;
    }

    template<class T> ResourcePtr<T>& ResourcePtr<T>::operator=(const ResourcePtr<T>& other) {
        resource = other.resource;
        return *this;
    }
    
    template<class T> template<class U> ResourcePtr<U> ResourcePtr<T>::staticCast() const {
        return ResourcePtr<U>(boost::static_pointer_cast<U>(resource));
    }
    
    template<class T> template<class U> ResourcePtr<U> ResourcePtr<T>::dynamicCast() const {
        return ResourcePtr<U>(boost::dynamic_pointer_cast<U>(resource));
    }

    template<class T> template<class U> ResourcePtr<U> ResourcePtr<T>::constCast() const {
        return ResourcePtr<U>(boost::const_pointer_cast<U>(resource));
    }

}
