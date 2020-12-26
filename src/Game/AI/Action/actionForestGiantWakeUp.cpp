#include "Game/AI/Action/actionForestGiantWakeUp.h"

namespace uking::action {

ForestGiantWakeUp::ForestGiantWakeUp(const InitArg& arg) : PlayASForAnimalUnit(arg) {}

ForestGiantWakeUp::~ForestGiantWakeUp() = default;

bool ForestGiantWakeUp::init_(sead::Heap* heap) {
    return PlayASForAnimalUnit::init_(heap);
}

void ForestGiantWakeUp::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayASForAnimalUnit::enter_(params);
}

void ForestGiantWakeUp::leave_() {
    PlayASForAnimalUnit::leave_();
}

void ForestGiantWakeUp::loadParams_() {
    PlayASForAnimalUnit::loadParams_();
}

void ForestGiantWakeUp::calc_() {
    PlayASForAnimalUnit::calc_();
}

}  // namespace uking::action
