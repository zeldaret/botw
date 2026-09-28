#include "Game/Actor/Action/actionBasicSignalEnemyNotice.h"

namespace uking::action {

BasicSignalEnemyNotice::BasicSignalEnemyNotice(const InitArg& arg) : ksys::act::ai::Action(arg) {}

BasicSignalEnemyNotice::~BasicSignalEnemyNotice() = default;

bool BasicSignalEnemyNotice::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void BasicSignalEnemyNotice::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void BasicSignalEnemyNotice::leave_() {
    ksys::act::ai::Action::leave_();
}

void BasicSignalEnemyNotice::loadParams_() {}

void BasicSignalEnemyNotice::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
