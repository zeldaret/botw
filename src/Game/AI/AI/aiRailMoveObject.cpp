#include "Game/AI/AI/aiRailMoveObject.h"

namespace uking::ai {

RailMoveObject::RailMoveObject(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

RailMoveObject::~RailMoveObject() = default;

bool RailMoveObject::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void RailMoveObject::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void RailMoveObject::leave_() {
    ksys::act::ai::Ai::leave_();
}

void RailMoveObject::loadParams_() {
    getStaticParam(&mASKeyName_On_s, "ASKeyName_On");
    getStaticParam(&mASKeyName_Off_s, "ASKeyName_Off");
    getMapUnitParam(&mRailMoveSpeed_m, "RailMoveSpeed");
}

}  // namespace uking::ai
