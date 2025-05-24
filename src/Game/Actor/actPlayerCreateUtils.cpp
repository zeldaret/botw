#include "Game/Actor/actPlayerCreateUtils.h"
#include "Game/Actor/actPlayerCreateMgr.h"
#include "Game/Actor/actWeapon.h"
#include "Game/UI/uiPauseMenuDataMgr.h"
#include "KingSystem/ActorSystem/Profiles/actWeaponBase.h"

namespace uking::act {

void requestCreateWeaponByRawLife(const char* actor_class, const sead::Matrix34f& matrix, f32 scale,
                                  sead::Heap* heap, ksys::act::BaseProcHandle* handle, s32 life,
                                  bool is_player_put, const WeaponModifierInfo* modifier,
                                  s32 task_lane_id, s32 res_lane_id) {
    ksys::act::InstParamPack params;
    params->add(is_player_put, "IsPlayerPut");
    if (modifier) {
        modifier->addModifierParams(params);
    }
    params->add(true, "IsWeaponCreateByRawLife");
    params->addResourceLane(res_lane_id);

    ksys::act::WeaponBase::requestCreateWeaponActor(actor_class, matrix, scale, heap, handle, life,
                                                    &params, task_lane_id);
}

}  // namespace uking::act
