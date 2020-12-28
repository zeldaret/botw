#include "Game/AI/Action/actionSetMaterialVisible.h"

namespace uking::action {

SetMaterialVisible::SetMaterialVisible(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SetMaterialVisible::~SetMaterialVisible() = default;

bool SetMaterialVisible::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SetMaterialVisible::loadParams_() {
    getStaticParam(&mIsVisible_s, "IsVisible");
    getDynamicParam(&mMaterialName_d, "MaterialName");
}

}  // namespace uking::action
