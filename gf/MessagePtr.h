#pragma once
#include <boost/shared_ptr.hpp>

#include "gf/Globals.h"

namespace gf {

    // T should extend the Message class
    template<class T> class MessagePtr
    {
    public:
        MessagePtr(T* mess);
        MessagePtr(boost::shared_ptr<T> mess);
        ~MessagePtr();
        
        // Smart pointer-ness
        T& operator*() const;
        T* operator->() const;
        bool operator bool() const;

        // Casting
        template<class U> MessagePtr<U> staticCast() const; // Should be fine for our use, as we should never be doing illegal casting with MessageTypes to check for us.
        template<class U> MessagePtr<U> dynamicCast() const;

    private:
        boost::shared_ptr<T> message;

    };

}
