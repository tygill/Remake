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
        bool operator bool() const;

        // Casting
        template<class U> ResourcePtr<U> staticCast() const; // Should be fine for our use, as we should never be doing illegal casting with ResourceTypes to check for us.
        template<class U> ResourcePtr<U> dynamicCast() const;

    private:
        boost::shared_ptr<T> resource;

    };

}
