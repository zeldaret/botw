#include "Game/AI/Action/actionCapturedActElectricParalyisis.h"

namespace uking::action {

CapturedActElectricParalyisis::CapturedActElectricParalyisis(const InitArg& arg)
    : ElectricParalysis(arg) {}

CapturedActElectricParalyisis::~CapturedActElectricParalyisis() = default;

bool CapturedActElectricParalyisis::init_(sead::Heap* heap) {
    return ElectricParalysis::init_(heap);
}

void CapturedActElectricParalyisis::enter_(ksys::act::ai::InlineParamPack* params) {
    ElectricParalysis::enter_(params);
}

void CapturedActElectricParalyisis::leave_() {
    ElectricParalysis::leave_();
}

void CapturedActElectricParalyisis::loadParams_() {
    ElectricParalysis::loadParams_();
    getStaticParam(&mPauseDelayFrames_s, "PauseDelayFrames");
}

void CapturedActElectricParalyisis::calc_() {
    ElectricParalysis::calc_();
}

}  // namespace uking::action
