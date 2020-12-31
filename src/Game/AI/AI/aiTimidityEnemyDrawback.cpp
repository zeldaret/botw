#include "Game/AI/AI/aiTimidityEnemyDrawback.h"

namespace uking::ai {

TimidityEnemyDrawback::TimidityEnemyDrawback(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

TimidityEnemyDrawback::~TimidityEnemyDrawback() = default;

bool TimidityEnemyDrawback::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void TimidityEnemyDrawback::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void TimidityEnemyDrawback::leave_() {
    ksys::act::ai::Ai::leave_();
}

void TimidityEnemyDrawback::loadParams_() {
    getStaticParam(&mEscapeDist_s, "EscapeDist");
    getStaticParam(&mEscapeDistFromHome_s, "EscapeDistFromHome");
    getStaticParam(&mLostRange_s, "LostRange");
    getStaticParam(&mLostVMin_s, "LostVMin");
    getStaticParam(&mLostVMax_s, "LostVMax");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
