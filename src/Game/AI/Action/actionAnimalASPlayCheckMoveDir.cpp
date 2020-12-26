#include "Game/AI/Action/actionAnimalASPlayCheckMoveDir.h"

namespace uking::action {

AnimalASPlayCheckMoveDir::AnimalASPlayCheckMoveDir(const InitArg& arg) : ForkAnimalASPlay(arg) {}

AnimalASPlayCheckMoveDir::~AnimalASPlayCheckMoveDir() = default;

bool AnimalASPlayCheckMoveDir::init_(sead::Heap* heap) {
    return ForkAnimalASPlay::init_(heap);
}

void AnimalASPlayCheckMoveDir::enter_(ksys::act::ai::InlineParamPack* params) {
    ForkAnimalASPlay::enter_(params);
}

void AnimalASPlayCheckMoveDir::leave_() {
    ForkAnimalASPlay::leave_();
}

void AnimalASPlayCheckMoveDir::loadParams_() {
    ForkAnimalASPlay::loadParams_();
}

void AnimalASPlayCheckMoveDir::calc_() {
    ForkAnimalASPlay::calc_();
}

}  // namespace uking::action
