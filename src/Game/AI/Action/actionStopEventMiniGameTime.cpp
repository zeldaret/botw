#include "Game/AI/Action/actionStopEventMiniGameTime.h"

namespace uking::action {

StopEventMiniGameTime::StopEventMiniGameTime(const InitArg& arg) : ksys::act::ai::Action(arg) {}

StopEventMiniGameTime::~StopEventMiniGameTime() = default;

bool StopEventMiniGameTime::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void StopEventMiniGameTime::loadParams_() {}

}  // namespace uking::action
