#include "Game/AI/Action/actionPredictVacuumShoot.h"

namespace uking::action {

PredictVacuumShoot::PredictVacuumShoot(const InitArg& arg) : ksys::act::ai::Action(arg) {}

PredictVacuumShoot::~PredictVacuumShoot() = default;

bool PredictVacuumShoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void PredictVacuumShoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void PredictVacuumShoot::leave_() {
    ksys::act::ai::Action::leave_();
}

void PredictVacuumShoot::loadParams_() {
    getStaticParam(&mPosReduceRatio_s, "PosReduceRatio");
    getStaticParam(&mAngReduceRatio_s, "AngReduceRatio");
    getStaticParam(&mRotSpd_s, "RotSpd");
    getStaticParam(&mASName_s, "ASName");
    getStaticParam(&mIsReuseBullet_s, "IsReuseBullet");
    // FIXME: CALL sub_710073ED20 @ 0x710073ed20
    // FIXME: CALL sub_710073EEE4 @ 0x710073eee4
}

void PredictVacuumShoot::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
