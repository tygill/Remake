#pragma once

#include <boost/cstdint.hpp>

namespace gf {
    
    typedef uint32_t EntityId;
    typedef uint32_t ComponentType;
    typedef uint32_t MessageType;
    typedef uint32_t ResourceType;

    // Some helper template methods to get types of various things
    template<class T> ComponentType componentType() {
        return T::staticType();
    }
    
    template<class T> MessageType messageType() {
        return T::staticType();
    }
    
    template<class T> ResourceType resourceType() {
        return T::staticType();
    }

}
