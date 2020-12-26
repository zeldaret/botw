#include "Game/AI/Action/actionMamonoShopStand.h"

namespace uking::action {

MamonoShopStand::MamonoShopStand(const InitArg& arg) : ksys::act::ai::Action(arg) {}

MamonoShopStand::~MamonoShopStand() = default;

bool MamonoShopStand::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void MamonoShopStand::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void MamonoShopStand::leave_() {
    ksys::act::ai::Action::leave_();
}

void MamonoShopStand::loadParams_() {}

void MamonoShopStand::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
