#include "Game/AI/Action/actionCloseClockTime.h"

namespace uking::action {

CloseClockTime::CloseClockTime(const InitArg& arg) : ksys::act::ai::Action(arg) {}

CloseClockTime::~CloseClockTime() = default;

bool CloseClockTime::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void CloseClockTime::loadParams_() {}

}  // namespace uking::action
