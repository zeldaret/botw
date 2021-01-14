#include "KingSystem/Map/mapObjectLink.h"
#include "KingSystem/Map/mapObject.h"

namespace ksys::map {

ObjectLinkData::ObjectLinkData() = default;

act::BaseProc* ObjectLink::getObjectProc() const {
    if (other_obj == nullptr)
        return nullptr;

    return other_obj->getActor_0(false);
}

bool ObjectLink::getObjectProcWithAccessor(act::ActorLinkConstDataAccess& accessor) const {
    if (other_obj == nullptr)
        return accessor.acquire(nullptr);
    else
        return other_obj->getActorWithAccessor(accessor);
}

}  // namespace ksys::map
