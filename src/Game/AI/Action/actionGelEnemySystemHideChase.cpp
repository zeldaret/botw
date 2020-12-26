#include "Game/AI/Action/actionGelEnemySystemHideChase.h"

namespace uking::action {

GelEnemySystemHideChase::GelEnemySystemHideChase(const InitArg& arg) : SystemHideChase(arg) {}

GelEnemySystemHideChase::~GelEnemySystemHideChase() = default;

bool GelEnemySystemHideChase::init_(sead::Heap* heap) {
    return SystemHideChase::init_(heap);
}

void GelEnemySystemHideChase::enter_(ksys::act::ai::InlineParamPack* params) {
    SystemHideChase::enter_(params);
}

void GelEnemySystemHideChase::leave_() {
    SystemHideChase::leave_();
}

void GelEnemySystemHideChase::loadParams_() {
    SystemHideChase::loadParams_();
}

void GelEnemySystemHideChase::calc_() {
    SystemHideChase::calc_();
}

}  // namespace uking::action
