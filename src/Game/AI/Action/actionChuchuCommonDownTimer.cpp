#include "Game/AI/Action/actionChuchuCommonDownTimer.h"

namespace uking::action {

ChuchuCommonDownTimer::ChuchuCommonDownTimer(const InitArg& arg) : Fork(arg) {}

ChuchuCommonDownTimer::~ChuchuCommonDownTimer() = default;

bool ChuchuCommonDownTimer::init_(sead::Heap* heap) {
    return Fork::init_(heap);
}

void ChuchuCommonDownTimer::enter_(ksys::act::ai::InlineParamPack* params) {
    Fork::enter_(params);
}

void ChuchuCommonDownTimer::leave_() {
    Fork::leave_();
}

void ChuchuCommonDownTimer::loadParams_() {
    Fork::loadParams_();
    getStaticParam(&mMinWaitFrame_s, "MinWaitFrame");
    getAITreeVariable(&mChemicalChuchuCommonDownTime_a, "ChemicalChuchuCommonDownTime");
}

void ChuchuCommonDownTimer::calc_() {
    Fork::calc_();
}

}  // namespace uking::action
