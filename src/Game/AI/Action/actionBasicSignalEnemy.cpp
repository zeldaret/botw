#include "Game/AI/Action/actionBasicSignalEnemy.h"

namespace uking::action {

BasicSignalEnemy::BasicSignalEnemy(const InitArg& arg) : ksys::act::ai::Action(arg) {}

BasicSignalEnemy::~BasicSignalEnemy() = default;

bool BasicSignalEnemy::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void BasicSignalEnemy::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void BasicSignalEnemy::leave_() {
    ksys::act::ai::Action::leave_();
}

void BasicSignalEnemy::loadParams_() {}

void BasicSignalEnemy::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
