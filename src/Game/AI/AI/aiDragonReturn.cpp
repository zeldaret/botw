#include "Game/AI/AI/aiDragonReturn.h"

namespace uking::ai {

DragonReturn::DragonReturn(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

DragonReturn::~DragonReturn() = default;

bool DragonReturn::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void DragonReturn::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void DragonReturn::leave_() {
    ksys::act::ai::Ai::leave_();
}

void DragonReturn::loadParams_() {
    getStaticParam(&mSpeed_s, "Speed");
    getStaticParam(&mRotateRate_s, "RotateRate");
    getStaticParam(&mChangeMoveHeight_s, "ChangeMoveHeight");
    getStaticParam(&mFinishHeight_s, "FinishHeight");
    getStaticParam(&mAngle_s, "Angle");
    getStaticParam(&mAvoidStartDistance_s, "AvoidStartDistance");
    getStaticParam(&mReturnStartFrame_s, "ReturnStartFrame");
}

}  // namespace uking::ai
