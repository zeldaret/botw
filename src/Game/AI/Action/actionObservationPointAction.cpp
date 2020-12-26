#include "Game/AI/Action/actionObservationPointAction.h"

namespace uking::action {

ObservationPointAction::ObservationPointAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ObservationPointAction::~ObservationPointAction() = default;

bool ObservationPointAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ObservationPointAction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ObservationPointAction::leave_() {
    ksys::act::ai::Action::leave_();
}

void ObservationPointAction::loadParams_() {
    getMapUnitParam(&mPointName_m, "PointName");
}

void ObservationPointAction::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
