#include "Game/AI/AI/aiNPCTravelBase.h"

namespace uking::ai {

NPCTravelBase::NPCTravelBase(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

NPCTravelBase::~NPCTravelBase() = default;

bool NPCTravelBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void NPCTravelBase::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void NPCTravelBase::leave_() {
    ksys::act::ai::Ai::leave_();
}

void NPCTravelBase::loadParams_() {}

}  // namespace uking::ai
