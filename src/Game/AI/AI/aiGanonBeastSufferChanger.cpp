#include "Game/AI/AI/aiGanonBeastSufferChanger.h"

namespace uking::ai {

GanonBeastSufferChanger::GanonBeastSufferChanger(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

GanonBeastSufferChanger::~GanonBeastSufferChanger() = default;

bool GanonBeastSufferChanger::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void GanonBeastSufferChanger::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void GanonBeastSufferChanger::leave_() {
    ksys::act::ai::Ai::leave_();
}

void GanonBeastSufferChanger::loadParams_() {
    getStaticParam(&mWeakPoint1Time_s, "WeakPoint1Time");
    getStaticParam(&mWeakPoint2Time_s, "WeakPoint2Time");
    getStaticParam(&mWeakPoint3Time_s, "WeakPoint3Time");
    getStaticParam(&mWeakPoint4Time_s, "WeakPoint4Time");
    getStaticParam(&mCloseOption_s, "CloseOption");
    getStaticParam(&mTimer_s, "Timer");
    getStaticParam(&mmstxtName_s, "mstxtName");
    getStaticParam(&mlabelName_s, "labelName");
    getStaticParam(&mlabelName2_s, "labelName2");
    getStaticParam(&mlabelName3_s, "labelName3");
    getAITreeVariable(&mIsWeakPointAppearMode_a, "IsWeakPointAppearMode");
    getAITreeVariable(&mSufferChangeStopCounter_a, "SufferChangeStopCounter");
    getAITreeVariable(&mSimpleDialogUnit_a, "SimpleDialogUnit");
    getAITreeVariable(&mInBeastGanonVoiceSequence_a, "InBeastGanonVoiceSequence");
}

}  // namespace uking::ai
