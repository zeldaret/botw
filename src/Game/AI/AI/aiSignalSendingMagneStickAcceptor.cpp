#include "Game/AI/AI/aiSignalSendingMagneStickAcceptor.h"

namespace uking::ai {

SignalSendingMagneStickAcceptor::SignalSendingMagneStickAcceptor(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

SignalSendingMagneStickAcceptor::~SignalSendingMagneStickAcceptor() = default;

bool SignalSendingMagneStickAcceptor::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void SignalSendingMagneStickAcceptor::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void SignalSendingMagneStickAcceptor::leave_() {
    ksys::act::ai::Ai::leave_();
}

void SignalSendingMagneStickAcceptor::loadParams_() {
    getMapUnitParam(&mMagneStickMaxSearchDistance_m, "MagneStickMaxSearchDistance");
}

}  // namespace uking::ai
