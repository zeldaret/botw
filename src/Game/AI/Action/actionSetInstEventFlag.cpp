#include "Game/AI/Action/actionSetInstEventFlag.h"

namespace uking::action {

SetInstEventFlag::SetInstEventFlag(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SetInstEventFlag::~SetInstEventFlag() = default;

bool SetInstEventFlag::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SetInstEventFlag::loadParams_() {}

}  // namespace uking::action
