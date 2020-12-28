#include "Game/AI/Action/actionAppearFullPouchInfo.h"

namespace uking::action {

AppearFullPouchInfo::AppearFullPouchInfo(const InitArg& arg) : ksys::act::ai::Action(arg) {}

AppearFullPouchInfo::~AppearFullPouchInfo() = default;

bool AppearFullPouchInfo::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void AppearFullPouchInfo::loadParams_() {
    getDynamicParam(&mPorchItemName_d, "PorchItemName");
}

}  // namespace uking::action
