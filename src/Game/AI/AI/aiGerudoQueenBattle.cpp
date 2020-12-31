#include "Game/AI/AI/aiGerudoQueenBattle.h"

namespace uking::ai {

GerudoQueenBattle::GerudoQueenBattle(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

GerudoQueenBattle::~GerudoQueenBattle() = default;

bool GerudoQueenBattle::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void GerudoQueenBattle::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void GerudoQueenBattle::leave_() {
    ksys::act::ai::Ai::leave_();
}

void GerudoQueenBattle::loadParams_() {
    getStaticParam(&mRetireFrame_s, "RetireFrame");
}

}  // namespace uking::ai
