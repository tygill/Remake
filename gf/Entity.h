#pragma once
#include <boost/cstdint.hpp>
#include <boost/thread.hpp>
#include <boost/unordered_map.hpp>

#include "gf/Globals.h"
#include "gf/Component.h"
#include "gf/ComponentPtr.h"
#include "gf/ComponentTypes.h"
#include "gf/ComponentLocks.h"

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
        // T should be an iterator over ComponentType objects
        //template<class T> Entity(EntityId id, T readWriteBegin, T readWriteEnd, bool lockNow = true);
        //template<class T> Entity(EntityId id, T readWriteBegin, T readWriteEnd, T readOnlyBegin, T readOnlyEnd, bool lockNow = true);
        Entity(EntityId id, ComponentTypes readWrite, bool lockNow = true);
        Entity(EntityId id, ComponentTypes readWrite, ComponentTypes readOnly, bool lockNow = true);
        ~Entity();

        EntityId id();
    
        // T should extend ComponentType
        template<class T> bool hasComponent() const;
        bool hasComponent(ComponentType type) const;
        template<class T> ComponentPtr<T> getComponent() const;
        ComponentPtr<Component> getComponent(ComponentType type) const;
        // As a possible way of forcing const-ness on components, what about having two sets of methods to get components.
        // One version gets the read/write ones, and returns a ComponentPtr<T>, but only if that ComponentType was loaded as read/write
        // The other version gets read only ones, and returns a ComponentPtr<T const> for any ComponentType that was loaded (either read only or read/write)
        template<class T> bool canReadComponent() const;
        bool canReadComponent(ComponentType type) const;
        template<class T> ComponentPtr<T const> readComponent() const;
        ComponentPtr<Component const> readComponent(ComponentType type) const;

        // Should this be the set of all components that the entity has, or all that were returned in full?
        ComponentTypes components() const;
        // Two methods for distinction?
        ComponentTypes loadedComponents() const;

    private:
        EntityId entityId;
        // Store the set of unique and shared ComponentTypes
        boost::unordered_map<ComponentType, boost::shared_ptr<Component> > components;
        ComponentLocks locks;
    };

}
