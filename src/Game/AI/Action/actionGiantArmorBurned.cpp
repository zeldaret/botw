#include "Game/AI/Action/actionGiantArmorBurned.h"

namespace uking::action {

GiantArmorBurned::GiantArmorBurned(const InitArg& arg) : GiantArmorAction(arg) {}

GiantArmorBurned::~GiantArmorBurned() = default;

bool GiantArmorBurned::init_(sead::Heap* heap) {
    return GiantArmorAction::init_(heap);
}

void GiantArmorBurned::enter_(ksys::act::ai::InlineParamPack* params) {
    GiantArmorAction::enter_(params);
}

void GiantArmorBurned::leave_() {
    GiantArmorAction::leave_();
}

void GiantArmorBurned::loadParams_() {
    GiantArmorAction::loadParams_();
}

void GiantArmorBurned::calc_() {
    GiantArmorAction::calc_();
}

}  // namespace uking::action
