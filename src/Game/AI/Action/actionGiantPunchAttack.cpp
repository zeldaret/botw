#include "Game/AI/Action/actionGiantPunchAttack.h"

namespace uking::action {

GiantPunchAttack::GiantPunchAttack(const InitArg& arg) : PunchAttack(arg) {}

GiantPunchAttack::~GiantPunchAttack() = default;

bool GiantPunchAttack::init_(sead::Heap* heap) {
    return PunchAttack::init_(heap);
}

void GiantPunchAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    PunchAttack::enter_(params);
}

void GiantPunchAttack::leave_() {
    PunchAttack::leave_();
}

void GiantPunchAttack::loadParams_() {
    PunchAttack::loadParams_();
    getStaticParam(&mCoBodyName_s, "CoBodyName");
}

void GiantPunchAttack::calc_() {
    PunchAttack::calc_();
}

}  // namespace uking::action
