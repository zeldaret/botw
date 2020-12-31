#include "Game/AI/AI/aiPreyDead.h"

namespace uking::ai {

PreyDead::PreyDead(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

PreyDead::~PreyDead() = default;

bool PreyDead::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void PreyDead::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void PreyDead::leave_() {
    ksys::act::ai::Ai::leave_();
}

void PreyDead::loadParams_() {
    getStaticParam(&mSendRadius_s, "SendRadius");
    getStaticParam(&mIsEmitForceEscapeSignal_s, "IsEmitForceEscapeSignal");
}

}  // namespace uking::ai
