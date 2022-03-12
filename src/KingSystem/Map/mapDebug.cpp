#include "KingSystem/Map/mapDebug.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace ksys::map {

bool printDebugMsg(Object* object, const sead::SafeString& msg, const char* config_name) {
    if (object == nullptr)
        return false;

    makeProjectMapMuuntPath(sead::FixedSafeString<0x200>(), object);
    return true;
}

bool printDebugMsg(ksys::act::Actor* actor, const sead::SafeString& msg, const char* config_name) {
    Object* o = actor->getMapObject();
    if (o == nullptr)
        return false;

    makeProjectMapMuuntPath(sead::FixedSafeString<0x200>(), o);
    return true;
}

}  // namespace ksys::map
