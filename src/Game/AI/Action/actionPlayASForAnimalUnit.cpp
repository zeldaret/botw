#include "Game/AI/Action/actionPlayASForAnimalUnit.h"

namespace uking::action {

PlayASForAnimalUnit::PlayASForAnimalUnit(const InitArg& arg) : ForkAnimalASPlay(arg) {}

PlayASForAnimalUnit::~PlayASForAnimalUnit() = default;

bool PlayASForAnimalUnit::init_(sead::Heap* heap) {
    return ForkAnimalASPlay::init_(heap);
}

void PlayASForAnimalUnit::enter_(ksys::act::ai::InlineParamPack* params) {
    ForkAnimalASPlay::enter_(params);
}

void PlayASForAnimalUnit::leave_() {
    ForkAnimalASPlay::leave_();
}

void PlayASForAnimalUnit::loadParams_() {
    ForkAnimalASPlay::loadParams_();
}

void PlayASForAnimalUnit::calc_() {
    ForkAnimalASPlay::calc_();
}

}  // namespace uking::action
