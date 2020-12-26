#include "Game/AI/Action/actionAddAutoPlacementCreator.h"

namespace uking::action {

AddAutoPlacementCreator::AddAutoPlacementCreator(const InitArg& arg) : ksys::act::ai::Action(arg) {}

AddAutoPlacementCreator::~AddAutoPlacementCreator() = default;

bool AddAutoPlacementCreator::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void AddAutoPlacementCreator::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void AddAutoPlacementCreator::leave_() {
    ksys::act::ai::Action::leave_();
}

void AddAutoPlacementCreator::loadParams_() {
    getMapUnitParam(&mCount_m, "Count");
    getMapUnitParam(&mActorName_m, "ActorName");
    getMapUnitParam(&mShape_m, "Shape");
}

void AddAutoPlacementCreator::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
