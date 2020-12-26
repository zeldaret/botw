#include "Game/AI/Action/actionReuseActorDelete.h"

namespace uking::action {

ReuseActorDelete::ReuseActorDelete(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ReuseActorDelete::~ReuseActorDelete() = default;

bool ReuseActorDelete::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ReuseActorDelete::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ReuseActorDelete::leave_() {
    ksys::act::ai::Action::leave_();
}

void ReuseActorDelete::loadParams_() {
    getStaticParam(&mIsCheckCreateParent_s, "IsCheckCreateParent");
    getStaticParam(&mIsCheckBulletAttacker_s, "IsCheckBulletAttacker");
    getStaticParam(&mIsCheckBulletHolder_s, "IsCheckBulletHolder");
    getMapUnitParam(&mIsReuseActor_m, "IsReuseActor");
}

void ReuseActorDelete::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
