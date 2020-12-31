#include "Game/AI/AI/aiRemoteBomb.h"

namespace uking::ai {

RemoteBomb::RemoteBomb(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

RemoteBomb::~RemoteBomb() = default;

bool RemoteBomb::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void RemoteBomb::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void RemoteBomb::leave_() {
    ksys::act::ai::Ai::leave_();
}

void RemoteBomb::loadParams_() {
    getStaticParam(&mWindRatio_s, "WindRatio");
    getStaticParam(&mXLinkKey_s, "XLinkKey");
    getAITreeVariable(&mIsIgniteCarriedBomb_a, "IsIgniteCarriedBomb");
}

}  // namespace uking::ai
