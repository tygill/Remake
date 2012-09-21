#pragma once
//#include <boost/unordered_set.hpp>

#include "gf/Globals.h"
#include "gf/OrderedSet.h"

namespace gf {

    typedef OrderedSet<EntityId> EntityIds;

}

/*
class EntityIds
{
public:
    typedef boost::unordered_set<EntityId>::iterator iterator;
    typedef boost::unordered_set<EntityId>::const_iterator const_iterator;

public:
    EntityIds();
    ~EntityIds();

    bool contains(EntityId id);
    bool add(EntityId id);
    bool remove(EntityId id);

    int size() const;

    // STL style iterators (simply uses the iterators from the interal structure)
    iterator begin();
    const_iterator begin() const;
    iterator end();
    const_iterator end() const;

private:
    boost::unordered_set<EntityId> components;
};
*/

