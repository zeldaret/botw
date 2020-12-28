#include "Game/AI/Action/actionAppearNumTargets.h"

namespace uking::action {

AppearNumTargets::AppearNumTargets(const InitArg& arg) : ksys::act::ai::Action(arg) {}

AppearNumTargets::~AppearNumTargets() = default;

bool AppearNumTargets::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void AppearNumTargets::loadParams_() {
    getDynamicParam(&mGameDataIntTargetCounter_d, "GameDataIntTargetCounter");
}

}  // namespace uking::action
