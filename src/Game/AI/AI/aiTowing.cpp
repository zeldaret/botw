#include "Game/AI/AI/aiTowing.h"

namespace uking::ai {

Towing::Towing(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

Towing::~Towing() = default;

bool Towing::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void Towing::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void Towing::leave_() {
    ksys::act::ai::Ai::leave_();
}

void Towing::loadParams_() {
    getStaticParam(&mKeepMaxTime_s, "KeepMaxTime");
    getStaticParam(&mStopTowingDef_s, "StopTowingDef");
    getStaticParam(&mMaxSpeed_s, "MaxSpeed");
    getStaticParam(&mInitSpeed_s, "InitSpeed");
    getStaticParam(&mAddSpeed_s, "AddSpeed");
    getStaticParam(&mStandardSpeed_s, "StandardSpeed");
    getStaticParam(&mBrakeDecSpeed_s, "BrakeDecSpeed");
    getStaticParam(&mAttFrontRate_s, "AttFrontRate");
    getStaticParam(&mSandCheckLength_s, "SandCheckLength");
    getStaticParam(&mSandCheckAngle_s, "SandCheckAngle");
}

}  // namespace uking::ai
