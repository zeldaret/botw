#include "Game/AI/Action/actionCollaborationShootingStarAnchor.h"

namespace uking::action {

CollaborationShootingStarAnchor::CollaborationShootingStarAnchor(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

CollaborationShootingStarAnchor::~CollaborationShootingStarAnchor() = default;

bool CollaborationShootingStarAnchor::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void CollaborationShootingStarAnchor::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void CollaborationShootingStarAnchor::leave_() {
    ksys::act::ai::Action::leave_();
}

void CollaborationShootingStarAnchor::loadParams_() {
    getMapUnitParam(&mCollaboShootingStarStartHour_m, "CollaboShootingStarStartHour");
    getMapUnitParam(&mCollaboShootingStarEndHour_m, "CollaboShootingStarEndHour");
}

void CollaborationShootingStarAnchor::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
