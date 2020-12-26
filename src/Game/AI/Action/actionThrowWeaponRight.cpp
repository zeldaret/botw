#include "Game/AI/Action/actionThrowWeaponRight.h"

namespace uking::action {

ThrowWeaponRight::ThrowWeaponRight(const InitArg& arg) : ThrowWeapon(arg) {}

ThrowWeaponRight::~ThrowWeaponRight() = default;

bool ThrowWeaponRight::init_(sead::Heap* heap) {
    return ThrowWeapon::init_(heap);
}

void ThrowWeaponRight::enter_(ksys::act::ai::InlineParamPack* params) {
    ThrowWeapon::enter_(params);
}

void ThrowWeaponRight::leave_() {
    ThrowWeapon::leave_();
}

void ThrowWeaponRight::loadParams_() {
    ActionWithPosAngReduce::loadParams_();
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mSpeedMin_s, "SpeedMin");
    getStaticParam(&mSpeedMax_s, "SpeedMax");
    getStaticParam(&mThrowAng_s, "ThrowAng");
    getStaticParam(&mThrowBoomerangAng_s, "ThrowBoomerangAng");
    getStaticParam(&mThrowBoomerangSpeedMax_s, "ThrowBoomerangSpeedMax");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getStaticParam(&mIsForceDead_s, "IsForceDead");
}

void ThrowWeaponRight::calc_() {
    ThrowWeapon::calc_();
}

}  // namespace uking::action
