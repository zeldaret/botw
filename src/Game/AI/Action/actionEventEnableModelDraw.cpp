#include "Game/AI/Action/actionEventEnableModelDraw.h"

namespace uking::action {

EventEnableModelDraw::EventEnableModelDraw(const InitArg& arg) : ksys::act::ai::Action(arg) {}

EventEnableModelDraw::~EventEnableModelDraw() = default;

bool EventEnableModelDraw::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventEnableModelDraw::loadParams_() {}

}  // namespace uking::action
