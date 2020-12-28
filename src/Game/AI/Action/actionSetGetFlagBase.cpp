#include "Game/AI/Action/actionSetGetFlagBase.h"

namespace uking::action {

SetGetFlagBase::SetGetFlagBase(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SetGetFlagBase::~SetGetFlagBase() = default;

bool SetGetFlagBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SetGetFlagBase::loadParams_() {}

}  // namespace uking::action
