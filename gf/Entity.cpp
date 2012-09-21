#include "gf/Entity.h"

namespace gf {

    // TODO: Optimization - if necessary, only load the complete set of component types if needed?
    // TODO: Optimization - pass ComponentTypes by reference always - would require work to make iterating work for const
    Entity::Entity(EntityManager* man, EntityId id, ComponentTypes readWrite, bool lockNow = true)
        : manager(man), entityId(id), types(manager->componentTypes(id)), uniqueTypes(readWrite), locks(readWrite, lockNow)
    {
        readWrite.reset();
        while (readWrite.moveNext()) {
            components.add(readWrite.current(), man->getComponent(readWrite.current(), id));
        }
    }

    Entity::Entity(EntityManager* man, EntityId id, ComponentTypes readWrite, ComponentTypes readOnly, bool lockNow = true)
        : manager(man), entityId(id), types(manager->componentTypes(id)), uniqueTypes(readWrite), locks(readWrite, readOnly, lockNow)
    {
        readWrite.reset();
        while (readWrite.moveNext()) {
            components.add(readWrite.current(), man->getComponent(readWrite.current(), id));
        }

        readOnly.reset();
        while (readOnly.moveNext()) {
            components.add(readOnly.current(), man->getComponent(readOnly.current(), id));
        }
    }

    Entity::~Entity()
    {
    }

}
