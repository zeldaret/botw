#include "Game/Actor/Action/actionCollaboShootingStarAreaTag.h"

namespace uking::action {

CollaboShootingStarAreaTag::CollaboShootingStarAreaTag(const InitArg& arg) : AreaActionBase(arg) {}

CollaboShootingStarAreaTag::~CollaboShootingStarAreaTag() = default;

bool CollaboShootingStarAreaTag::init_(sead::Heap* heap) {
    return AreaActionBase::init_(heap);
}

void CollaboShootingStarAreaTag::enter_(ksys::act::ai::InlineParamPack* params) {
    AreaActionBase::enter_(params);
}

void CollaboShootingStarAreaTag::leave_() {
    AreaActionBase::leave_();
}

void CollaboShootingStarAreaTag::loadParams_() {
    getMapUnitParam(&mcollaboSSFalloutFlagName_m, "collaboSSFalloutFlagName");
}

void CollaboShootingStarAreaTag::calc_() {
    AreaActionBase::calc_();
}

}  // namespace uking::action
