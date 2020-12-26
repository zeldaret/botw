#include "Game/AI/Action/actionDungeonMoveReset.h"

namespace uking::action {

DungeonMoveReset::DungeonMoveReset(const InitArg& arg) : ksys::act::ai::Action(arg) {}

DungeonMoveReset::~DungeonMoveReset() = default;

bool DungeonMoveReset::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void DungeonMoveReset::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void DungeonMoveReset::leave_() {
    ksys::act::ai::Action::leave_();
}

void DungeonMoveReset::loadParams_() {
    getStaticParam(&mAccel_s, "Accel");
    getDynamicParam(&mDynMoveDis_d, "DynMoveDis");
    getDynamicParam(&mDynMoveSpeed_d, "DynMoveSpeed");
    getMapUnitParam(&mInitDgnPriority_m, "InitDgnPriority");
}

void DungeonMoveReset::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
