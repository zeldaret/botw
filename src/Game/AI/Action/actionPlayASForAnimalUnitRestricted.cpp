#include "Game/AI/Action/actionPlayASForAnimalUnitRestricted.h"

namespace uking::action {

PlayASForAnimalUnitRestricted::PlayASForAnimalUnitRestricted(const InitArg& arg)
    : PlayASForAnimalUnit(arg) {}

PlayASForAnimalUnitRestricted::~PlayASForAnimalUnitRestricted() = default;

bool PlayASForAnimalUnitRestricted::init_(sead::Heap* heap) {
    return PlayASForAnimalUnit::init_(heap);
}

void PlayASForAnimalUnitRestricted::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayASForAnimalUnit::enter_(params);
}

void PlayASForAnimalUnitRestricted::leave_() {
    PlayASForAnimalUnit::leave_();
}

void PlayASForAnimalUnitRestricted::loadParams_() {
    PlayASForAnimalUnit::loadParams_();
}

void PlayASForAnimalUnitRestricted::calc_() {
    PlayASForAnimalUnit::calc_();
}

}  // namespace uking::action
