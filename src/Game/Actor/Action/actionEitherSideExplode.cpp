#include "Game/Actor/Action/actionEitherSideExplode.h"

namespace uking::action {

EitherSideExplode::EitherSideExplode(const InitArg& arg) : Explode(arg) {}

EitherSideExplode::~EitherSideExplode() = default;

bool EitherSideExplode::init_(sead::Heap* heap) {
    return Explode::init_(heap);
}

void EitherSideExplode::enter_(ksys::act::ai::InlineParamPack* params) {
    Explode::enter_(params);
}

void EitherSideExplode::leave_() {
    Explode::leave_();
}

void EitherSideExplode::loadParams_() {
    Explode::loadParams_();
    getDynamicParam(&mIsPlayerAttack_d, "IsPlayerAttack");
}

void EitherSideExplode::calc_() {
    Explode::calc_();
}

}  // namespace uking::action
