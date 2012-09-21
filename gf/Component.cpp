#include "gf/Component.h"

#include "gf/Exceptions.h"
#include "gf/ComponentLock.h"

namespace gf {

    ComponentType Component::nextRegistrationType = 1;

    Component::Component()
    {
    }

    Component::~Component()
    {
    }

    ComponentType Component::type() const {
        throw MethodNotDefinedException("Method not defined: ComponentType::type()\n Did you forget to include GF_DEFINE_COMPONENT somewhere?");
    }

    ComponentType Component::registerType() {
        ComponentType type = nextRegistrationType++;
        ComponentLock::registerComponentType(type);
        return type;
    }

}
