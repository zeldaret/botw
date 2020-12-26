#include "Game/AI/Action/actionSetMaterialVisible.h"

namespace uking::action {

SetMaterialVisible::SetMaterialVisible(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SetMaterialVisible::~SetMaterialVisible() = default;

bool SetMaterialVisible::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SetMaterialVisible::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void SetMaterialVisible::leave_() {
    ksys::act::ai::Action::leave_();
}

void SetMaterialVisible::loadParams_() {
    getStaticParam(&mIsVisible_s, "IsVisible");
    getDynamicParam(&mMaterialName_d, "MaterialName");
}

void SetMaterialVisible::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
