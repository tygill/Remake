#include "gf/Entity.h"
#include "gf/EntityManager.h"

namespace gf {

    // TODO: Optimization - if necessary, only load the complete set of component types if needed?
    // TODO: Optimization - pass ComponentTypes by reference always - would require work to make iterating work for const
    Entity::Entity(EntityManager* man, EntityId id, ComponentTypes readWrite, bool lockNow)
        : manager(man), entityId(id), types(manager->componentTypes(id)), uniqueTypes(readWrite), locks(readWrite, lockNow)
    {
        ComponentTypes::Enumerator itr = readWrite.enumerator();
        while (itr.moveNext()) {
            components.add(itr.current(), man->getComponent(itr.current(), id));
        }
    }

    Entity::Entity(EntityManager* man, EntityId id, ComponentTypes readWrite, ComponentTypes readOnly, bool lockNow)
        : manager(man), entityId(id), types(manager->componentTypes(id)), uniqueTypes(readWrite), locks(readWrite, readOnly, lockNow)
    {
        ComponentTypes::Enumerator itr = readWrite.enumerator();
        while (itr.moveNext()) {
            components.add(itr.current(), man->getComponent(itr.current(), id));
        }

        itr = readOnly.enumerator();
        while (itr.moveNext()) {
            components.add(itr.current(), man->getComponent(itr.current(), id));
        }
    }

    Entity::~Entity()
    {
    }

    EntityId Entity::id() const {
        return entityId;
    }

    bool Entity::hasComponent(ComponentType type) const {
        return types.contains(type);
    }

    bool Entity::canGetComponent(ComponentType type) const {
        return uniqueTypes.contains(type);
    }

    ComponentPtr<Component> Entity::getComponent(ComponentType type) const {
        return components.get(type);
    }

    bool Entity::canReadComponent(ComponentType type) const {
        return components.contains(type);
    }

    ComponentPtr<Component const> Entity::readComponent(ComponentType type) const {
        return components.get(type).staticCast<Component const>();
    }

    ComponentTypes Entity::componentTypes() const {
        return types;
    }

}
