#include "Game/AI/Action/actionGiantCatchTreeWeapon.h"

namespace uking::action {

GiantCatchTreeWeapon::GiantCatchTreeWeapon(const InitArg& arg) : Catch(arg) {}

GiantCatchTreeWeapon::~GiantCatchTreeWeapon() = default;

bool GiantCatchTreeWeapon::init_(sead::Heap* heap) {
    return Catch::init_(heap);
}

void GiantCatchTreeWeapon::enter_(ksys::act::ai::InlineParamPack* params) {
    Catch::enter_(params);
}

void GiantCatchTreeWeapon::leave_() {
    Catch::leave_();
}

void GiantCatchTreeWeapon::loadParams_() {
    Catch::loadParams_();
    getStaticParam(&mCatchPosOffset_s, "CatchPosOffset");
}

void GiantCatchTreeWeapon::calc_() {
    Catch::calc_();
}

}  // namespace uking::action
