#include "Game/AI/Action/actionAppearFullPouchInfo.h"

namespace uking::action {

AppearFullPouchInfo::AppearFullPouchInfo(const InitArg& arg) : ksys::act::ai::Action(arg) {}

AppearFullPouchInfo::~AppearFullPouchInfo() = default;

bool AppearFullPouchInfo::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void AppearFullPouchInfo::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void AppearFullPouchInfo::leave_() {
    ksys::act::ai::Action::leave_();
}

void AppearFullPouchInfo::loadParams_() {
    getDynamicParam(&mPorchItemName_d, "PorchItemName");
}

void AppearFullPouchInfo::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
