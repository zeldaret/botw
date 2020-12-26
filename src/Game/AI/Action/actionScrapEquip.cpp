#include "Game/AI/Action/actionScrapEquip.h"

namespace uking::action {

ScrapEquip::ScrapEquip(const InitArg& arg) : ActionWithAS(arg) {}

ScrapEquip::~ScrapEquip() = default;

bool ScrapEquip::init_(sead::Heap* heap) {
    return ActionWithAS::init_(heap);
}

void ScrapEquip::enter_(ksys::act::ai::InlineParamPack* params) {
    ActionWithAS::enter_(params);
}

void ScrapEquip::leave_() {
    ActionWithAS::leave_();
}

void ScrapEquip::loadParams_() {
    ActionWithPosAngReduce::loadParams_();
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mDropSpd_s, "DropSpd");
}

void ScrapEquip::calc_() {
    ActionWithAS::calc_();
}

}  // namespace uking::action
