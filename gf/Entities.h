#pragma once

#include "gf/Globals.h"
#include "gf/PtrOrderedSet.h"
#include "gf/Entity.h"
#include "gf/EntityIds.h"

namespace gf {

    class Entities
    {
    public:
        Entities();
        Entities(EntityIds ids, ComponentTypes readWrite, bool lockNow = true);
        Entities(EntityIds ids, ComponentTypes readWrite, ComponentTypes readOnly, bool lockNow = true);
        ~Entities();

        int size() const;
        bool empty() const;

        // C# style iterators are used here
        bool moveNext();
        Entity current() const;

    private:
        PtrOrderedSet<Entity> entities;
        ComponentLocks locks;
    };

}
