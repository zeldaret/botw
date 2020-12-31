#include "Game/AI/AI/aiSeqGroundHit.h"

namespace uking::ai {

SeqGroundHit::SeqGroundHit(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SeqGroundHit::~SeqGroundHit() = default;

bool SeqGroundHit::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void SeqGroundHit::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void SeqGroundHit::leave_() {
    ksys::act::ai::Ai::leave_();
}

void SeqGroundHit::loadParams_() {
    getStaticParam(&mCheckType_s, "CheckType");
    getStaticParam(&mIsCheckChangeable_s, "IsCheckChangeable");
    getStaticParam(&mIsNoHitEnd_s, "IsNoHitEnd");
}

}  // namespace uking::ai
