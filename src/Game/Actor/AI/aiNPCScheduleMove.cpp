#include "Game/Actor/AI/aiNPCScheduleMove.h"

namespace uking::ai {

NPCScheduleMove::NPCScheduleMove(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

NPCScheduleMove::~NPCScheduleMove() = default;

bool NPCScheduleMove::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void NPCScheduleMove::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void NPCScheduleMove::leave_() {
    ksys::act::ai::Ai::leave_();
}

void NPCScheduleMove::loadParams_() {}

}  // namespace uking::ai
