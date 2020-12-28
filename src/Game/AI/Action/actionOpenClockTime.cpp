#include "Game/AI/Action/actionOpenClockTime.h"

namespace uking::action {

OpenClockTime::OpenClockTime(const InitArg& arg) : ksys::act::ai::Action(arg) {}

OpenClockTime::~OpenClockTime() = default;

bool OpenClockTime::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void OpenClockTime::loadParams_() {}

}  // namespace uking::action
