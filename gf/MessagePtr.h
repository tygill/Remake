#pragma once
#include <boost/shared_ptr.hpp>

#include "gf/Globals.h"
#include "gf/Message.h"

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
        operator bool() const;
        MessagePtr& operator=(const MessagePtr& other);

        // Casting
        template<class U> MessagePtr<U> staticCast() const; // Should be fine for our use, as we should never be doing illegal casting with MessageTypes to check for us.
        template<class U> MessagePtr<U> dynamicCast() const;
        template<class U> MessagePtr<U> constCast() const;

    private:
        boost::shared_ptr<T> message;
    };

    template<class T> MessagePtr<T>::MessagePtr(T* mess)
        : message(mess) {}

    template<class T> MessagePtr<T>::MessagePtr(boost::shared_ptr<T> mess)
        : message(mess) {}

    template<class T> MessagePtr<T>::~MessagePtr() {}

    template<class T> T& MessagePtr<T>::operator*() const {
        return *message;
    }

    template<class T> T* MessagePtr<T>::operator->() const {
        return message.get();
    }

    template<class T> MessagePtr<T>::operator bool() const {
        return (bool)message;
    }

    template<class T> MessagePtr<T>& MessagePtr<T>::operator=(const MessagePtr<T>& other) {
        message = other.message;
        return *this;
    }
    
    template<class T> template<class U> MessagePtr<U> MessagePtr<T>::staticCast() const {
        return MessagePtr<U>(boost::static_pointer_cast<U>(message));
    }
    
    template<class T> template<class U> MessagePtr<U> MessagePtr<T>::dynamicCast() const {
        return MessagePtr<U>(boost::dynamic_pointer_cast<U>(message));
    }

    template<class T> template<class U> MessagePtr<U> MessagePtr<T>::constCast() const {
        return MessagePtr<U>(boost::const_pointer_cast<U>(message));
    }

}
