#include "Game/AI/AI/aiBokoblinRestraint.h"

namespace uking::ai {

BokoblinRestraint::BokoblinRestraint(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

BokoblinRestraint::~BokoblinRestraint() = default;

void BokoblinRestraint::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void BokoblinRestraint::leave_() {
    ksys::act::ai::Ai::leave_();
}

void BokoblinRestraint::loadParams_() {
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getStaticParam(&mBaseDist_s, "BaseDist");
    getStaticParam(&mLostVMin_s, "LostVMin");
    getStaticParam(&mLostVMax_s, "LostVMax");
    getStaticParam(&mLostTimer_s, "LostTimer");
    getStaticParam(&mLostRange_s, "LostRange");
}

}  // namespace uking::ai
