#include "Game/AI/AI/aiSeqGroundHitAssassinBoss.h"

namespace uking::ai {

SeqGroundHitAssassinBoss::SeqGroundHitAssassinBoss(const InitArg& arg) : SeqGroundHit(arg) {}

SeqGroundHitAssassinBoss::~SeqGroundHitAssassinBoss() = default;

bool SeqGroundHitAssassinBoss::init_(sead::Heap* heap) {
    return SeqGroundHit::init_(heap);
}

void SeqGroundHitAssassinBoss::enter_(ksys::act::ai::InlineParamPack* params) {
    SeqGroundHit::enter_(params);
}

void SeqGroundHitAssassinBoss::leave_() {
    SeqGroundHit::leave_();
}

void SeqGroundHitAssassinBoss::loadParams_() {
    SeqGroundHit::loadParams_();
}

}  // namespace uking::ai
