#include "Game/AI/Action/actionGiantArmorElectric.h"

namespace uking::action {

GiantArmorElectric::GiantArmorElectric(const InitArg& arg) : GiantArmorAction(arg) {}

GiantArmorElectric::~GiantArmorElectric() = default;

bool GiantArmorElectric::init_(sead::Heap* heap) {
    return GiantArmorAction::init_(heap);
}

void GiantArmorElectric::enter_(ksys::act::ai::InlineParamPack* params) {
    GiantArmorAction::enter_(params);
}

void GiantArmorElectric::leave_() {
    GiantArmorAction::leave_();
}

void GiantArmorElectric::loadParams_() {
    GiantArmorAction::loadParams_();
    getStaticParam(&mTimeMin_s, "TimeMin");
}

void GiantArmorElectric::calc_() {
    GiantArmorAction::calc_();
}

}  // namespace uking::action
