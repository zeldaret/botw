#include "Game/AI/Action/actionForbidSettingInstEventFlag.h"

namespace uking::action {

ForbidSettingInstEventFlag::ForbidSettingInstEventFlag(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

ForbidSettingInstEventFlag::~ForbidSettingInstEventFlag() = default;

bool ForbidSettingInstEventFlag::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForbidSettingInstEventFlag::loadParams_() {}

}  // namespace uking::action
