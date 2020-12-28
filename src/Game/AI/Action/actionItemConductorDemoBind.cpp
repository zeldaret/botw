#include "Game/AI/Action/actionItemConductorDemoBind.h"

namespace uking::action {

ItemConductorDemoBind::ItemConductorDemoBind(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ItemConductorDemoBind::~ItemConductorDemoBind() = default;

void ItemConductorDemoBind::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ItemConductorDemoBind::leave_() {
    ksys::act::ai::Action::leave_();
}

void ItemConductorDemoBind::loadParams_() {
    getDynamicParam(&mRotOffsetX_d, "RotOffsetX");
    getDynamicParam(&mRotOffsetY_d, "RotOffsetY");
    getDynamicParam(&mRotOffsetZ_d, "RotOffsetZ");
    getDynamicParam(&mTransOffsetX_d, "TransOffsetX");
    getDynamicParam(&mTransOffsetY_d, "TransOffsetY");
    getDynamicParam(&mTransOffsetZ_d, "TransOffsetZ");
    getDynamicParam(&mActorName_d, "ActorName");
    getDynamicParam(&mUniqueName_d, "UniqueName");
    getDynamicParam(&mNodeName_d, "NodeName");
}

void ItemConductorDemoBind::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
