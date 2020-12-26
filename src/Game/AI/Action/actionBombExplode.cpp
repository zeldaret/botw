#include "Game/AI/Action/actionBombExplode.h"

namespace uking::action {

BombExplode::BombExplode(const InitArg& arg) : ActionEx(arg) {}

BombExplode::~BombExplode() = default;

bool BombExplode::init_(sead::Heap* heap) {
    return ActionEx::init_(heap);
}

void BombExplode::enter_(ksys::act::ai::InlineParamPack* params) {
    ActionEx::enter_(params);
}

void BombExplode::leave_() {
    ActionEx::leave_();
}

void BombExplode::loadParams_() {}

void BombExplode::calc_() {
    ActionEx::calc_();
}

}  // namespace uking::action
