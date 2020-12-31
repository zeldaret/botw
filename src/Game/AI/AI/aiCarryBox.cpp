#include "Game/AI/AI/aiCarryBox.h"

namespace uking::ai {

CarryBox::CarryBox(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

CarryBox::~CarryBox() = default;

bool CarryBox::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void CarryBox::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void CarryBox::leave_() {
    ksys::act::ai::Ai::leave_();
}

void CarryBox::loadParams_() {}

}  // namespace uking::ai
