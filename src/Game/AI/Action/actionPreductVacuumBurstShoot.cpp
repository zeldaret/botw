#include "Game/AI/Action/actionPreductVacuumBurstShoot.h"

namespace uking::action {

PreductVacuumBurstShoot::PreductVacuumBurstShoot(const InitArg& arg)
    : HoverPredictVacuumShoot(arg) {}

PreductVacuumBurstShoot::~PreductVacuumBurstShoot() = default;

bool PreductVacuumBurstShoot::init_(sead::Heap* heap) {
    return HoverPredictVacuumShoot::init_(heap);
}

void PreductVacuumBurstShoot::enter_(ksys::act::ai::InlineParamPack* params) {
    HoverPredictVacuumShoot::enter_(params);
}

void PreductVacuumBurstShoot::leave_() {
    HoverPredictVacuumShoot::leave_();
}

void PreductVacuumBurstShoot::loadParams_() {
    HoverPredictVacuumShoot::loadParams_();
    getStaticParam(&mBulletOffset_s, "BulletOffset");
    getStaticParam(&mPartsKey2_s, "PartsKey2");
    getStaticParam(&mPartsKey3_s, "PartsKey3");
}

void PreductVacuumBurstShoot::calc_() {
    HoverPredictVacuumShoot::calc_();
}

}  // namespace uking::action
