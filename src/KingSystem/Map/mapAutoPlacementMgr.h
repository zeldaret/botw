#pragma once

#include <heap/seadDisposer.h>
#include <prim/seadSafeString.h>

namespace ksys::act {
class Actor;
} // namespace ksys::act

namespace ksys::map {

class AutoPlacementMgr {
SEAD_SINGLETON_DISPOSER(AutoPlacementMgr)
public:
    AutoPlacementMgr();
    virtual ~AutoPlacementMgr();

    bool sub_7100659E40(ksys::act::Actor* actor, const sead::SafeString& actor_name, int count, bool is_box);
    void sub_7100659F94(ksys::act::Actor* actor);
};

}  // namespace ksys::map
