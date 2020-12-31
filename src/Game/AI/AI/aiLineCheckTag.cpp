#include "Game/AI/AI/aiLineCheckTag.h"

namespace uking::ai {

LineCheckTag::LineCheckTag(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

LineCheckTag::~LineCheckTag() = default;

bool LineCheckTag::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void LineCheckTag::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void LineCheckTag::leave_() {
    ksys::act::ai::Ai::leave_();
}

void LineCheckTag::loadParams_() {
    getMapUnitParam(&mLineCheckType_m, "LineCheckType");
    getMapUnitParam(&mLineCheckVec_m, "LineCheckVec");
}

}  // namespace uking::ai
