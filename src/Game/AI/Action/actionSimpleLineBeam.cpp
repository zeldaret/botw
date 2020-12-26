#include "Game/AI/Action/actionSimpleLineBeam.h"

namespace uking::action {

SimpleLineBeam::SimpleLineBeam(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SimpleLineBeam::~SimpleLineBeam() = default;

bool SimpleLineBeam::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SimpleLineBeam::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void SimpleLineBeam::leave_() {
    ksys::act::ai::Action::leave_();
}

void SimpleLineBeam::loadParams_() {
    getStaticParam(&mIsGuarantee_s, "IsGuarantee");
    getStaticParam(&mType_s, "Type");
    getStaticParam(&mIsGuardPierces_s, "IsGuardPierces");
    getStaticParam(&mIsSetAtIgnoreObstacle_s, "IsSetAtIgnoreObstacle");
}

void SimpleLineBeam::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
