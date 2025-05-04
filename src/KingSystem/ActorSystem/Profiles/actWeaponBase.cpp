#include "KingSystem/ActorSystem/Profiles/actWeaponBase.h"
#include "KingSystem/ActorSystem/actActorCreator.h"
#include "KingSystem/ActorSystem/actInstParamPack.h"

namespace ksys::act {

void WeaponBase::requestCreateWeaponActor(const char* actor, const sead::Matrix34f& matrix,
                                          f32 scale, sead::Heap* heap,
                                          ksys::act::BaseProcHandle* handle, s32 life,
                                          ksys::act::InstParamPack* params_in, s32 task_lane_id) {
    ksys::act::InstParamPack params;
    if (params_in) {
        params = *params_in;
    }

    ksys::act::ActorCreator::addScale(params, scale);
    params->add(life, "Life");
    params->addMatrix(matrix);
    ksys::act::ActorCreator::instance()->requestCreateActor(actor, heap, handle, &params, nullptr,
                                                            task_lane_id);
}

}  // namespace ksys::act
