#include "Game/AI/Action/actionLookAtTheFront.h"

namespace uking::action {

LookAtTheFront::LookAtTheFront(const InitArg& arg) : ksys::act::ai::Action(arg) {}

LookAtTheFront::~LookAtTheFront() = default;

bool LookAtTheFront::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void LookAtTheFront::loadParams_() {
    getDynamicParam(&mIsValid_d, "IsValid");
}

}  // namespace uking::action
