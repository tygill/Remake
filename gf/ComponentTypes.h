#pragma once
#include <boost/unordered_set.hpp>

#include "gf/Globals.h"

namespace gf {

    typedef OrderedSet<ComponentType> ComponentTypes;

    /*
    // Unordered set of ComponentTypes
    class ComponentTypes
    {
    public:
        typedef boost::unordered_set<ComponentType>::iterator iterator;
        typedef boost::unordered_set<ComponentType>::const_iterator const_iterator;

    public:
        ComponentTypes();
        ~ComponentTypes();

        bool contains(ComponentType type);
        bool add(ComponentType type);
        bool remove(ComponentType type);

        int size() const;

        // STL style iterators (simply uses the iterators from the interal structure)
        iterator begin();
        const_iterator begin() const;
        iterator end();
        const_iterator end() const;

    private:
        boost::unordered_set<ComponentType> components;
    };
    */

}
