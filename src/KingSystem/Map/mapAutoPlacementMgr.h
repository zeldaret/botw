#pragma once

#include <heap/seadDisposer.h>
#include <math/seadVector.h>
#include <prim/seadDelegate.h>
#include <prim/seadSafeString.h>

#include "KingSystem/Utils/Types.h"

namespace ksys::act {
class Actor;
}  // namespace ksys::act

namespace ksys::map {

class AutoPlacementMgr {
    SEAD_SINGLETON_DISPOSER(AutoPlacementMgr)
public:
    AutoPlacementMgr();
    virtual ~AutoPlacementMgr();

    bool sub_7100659E40(act::Actor* actor, const sead::SafeString& actor_name, int count,
                        bool is_box);
    void sub_7100659F94(act::Actor* actor);

    // 0x0000007100654e44
    bool threadFn();
    // 0x0000007100656030
    bool auto9();
    // 0x0000007100656d24
    bool auto2(const sead::SafeString& name, const sead::Vector3f& pos);
    // 0x0000007100659188
    bool auto0(const sead::Vector3f& pos, u32 placement_type);
    // 0x0000007100659350
    bool auto11(const sead::Vector3f& pos);

    sead::DelegateR<AutoPlacementMgr, bool> mDelegate;
};
// KSYS_CHECK_SIZE_NX150(AutoPlacementMgr, 0x189E38);

}  // namespace ksys::map
