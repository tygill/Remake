#pragma once
#include <boost/cstdint.hpp>
#include <boost/thread.hpp>

#include "gf/Globals.h"
#include "gf/EntityManager.h"
#include "gf/Component.h"
#include "gf/ComponentPtr.h"
#include "gf/ComponentTypes.h"
#include "gf/ComponentLocks.h"
#include "gf/HashMap.h"

namespace gf {

    // Represents a read only mapping of an EntityId to a set of Components
    // The ComponentType of each component the Entity holds is locked for the duration of this Entity objects existance
    // Components can thus be modified, but the mapping of EntityId => Components cannot be changed by this class,
    // and will not change to reflect changes made to this mapping by other threads.
    //  Example:
    //   If thread 1 gets an Entity object with ComponentA and ComponentB, and then thread 2 adds ComponentC to that EntityId and removes ComponentB,
    //   thread 1 will still see ComponentA and ComponentB.
    class Entity
    {
    public:
        Entity(EntityManager* man, EntityId id, ComponentTypes readWrite, bool lockNow = true);
        Entity(EntityManager* man, EntityId id, ComponentTypes readWrite, ComponentTypes readOnly, bool lockNow = true);
        ~Entity();

        EntityId id();
    
        // T should extend Component
        // Has component checks whether the Entity has a component of that type - not whether this Entity object has that component to read
        template<class T> bool hasComponent() const;
        bool hasComponent(ComponentType type) const;
        
        template<class T> bool canGetComponent() const;
        bool canGetComponent(ComponentType type) const;

        // Gets an editable ptr to the component
        // Should this throw an exception is that comopnent type is not read/write locked?
        template<class T> ComponentPtr<T> getComponent() const;
        ComponentPtr<Component> getComponent(ComponentType type) const;

        // As a possible way of forcing const-ness on components, what about having two sets of methods to get components.
        // One version gets the read/write ones, and returns a ComponentPtr<T>, but only if that ComponentType was loaded as read/write
        // The other version gets read only ones, and returns a ComponentPtr<T const> for any ComponentType that was loaded (either read only or read/write)
        template<class T> bool canReadComponent() const;
        bool canReadComponent(ComponentType type) const;

        // Gets a read only ptr to the component
        template<class T> ComponentPtr<T const> readComponent() const;
        ComponentPtr<Component const> readComponent(ComponentType type) const;

        // Should this be the set of all components that the entity has, or all that were returned in full?
        ComponentTypes components() const;

    private:
        EntityManager* manager;
        EntityId entityId;
        // All components that this entity has
        ComponentTypes types;
        // Store the set of unique and shared ComponentTypes
        HashMap<ComponentType, ComponentPtr<Component> > components;
        // Stores the set of types that were requested as unique. All other types that are loaded 
        ComponentTypes uniqueTypes;
        ComponentLocks locks;
    };

    template<class T> bool Entity::hasComponent() const {
        return hasComponent(componentType<T>());
    }

    template<class T> bool canGetComponent() const {
        return canGetComponent(componentType<T>());
    }

    template<class T> ComponentPtr<T> getComponent() const {
        return getComponent(componentType<T>()).staticCast<T>();
    }

    template<class T> bool canReadComponent() const {
        return canReadComponent(componentType<T>());
    }

    template<class T> ComponentPtr<T const> readComponent() const {
        return readComponent(componentType<T>()).staticCast<T const>();
    }

}
