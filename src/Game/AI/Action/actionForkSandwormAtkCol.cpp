#include "Game/AI/Action/actionForkSandwormAtkCol.h"

namespace uking::action {

ForkSandwormAtkCol::ForkSandwormAtkCol(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForkSandwormAtkCol::~ForkSandwormAtkCol() = default;

bool ForkSandwormAtkCol::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkSandwormAtkCol::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ForkSandwormAtkCol::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForkSandwormAtkCol::loadParams_() {
    getStaticParam(&mMinDamage_s, "MinDamage");
    getStaticParam(&mIsUseTossAt_s, "IsUseTossAt");
    getStaticParam(&mIsColNoHitPlayer_s, "IsColNoHitPlayer");
}

void ForkSandwormAtkCol::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
