#include "Game/AI/Action/actionGelEnemyFreeze.h"

namespace uking::action {

GelEnemyFreeze::GelEnemyFreeze(const InitArg& arg) : Freeze(arg) {}

GelEnemyFreeze::~GelEnemyFreeze() = default;

bool GelEnemyFreeze::init_(sead::Heap* heap) {
    return Freeze::init_(heap);
}

void GelEnemyFreeze::enter_(ksys::act::ai::InlineParamPack* params) {
    Freeze::enter_(params);
}

void GelEnemyFreeze::leave_() {
    Freeze::leave_();
}

void GelEnemyFreeze::loadParams_() {
    Freeze::loadParams_();
    getStaticParam(&mASName_s, "ASName");
}

void GelEnemyFreeze::calc_() {
    Freeze::calc_();
}

}  // namespace uking::action
