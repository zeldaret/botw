#include "Game/AI/AI/aiChildDeviceReflectArrow.h"

namespace uking::ai {

ChildDeviceReflectArrow::ChildDeviceReflectArrow(const InitArg& arg) : WithoutWeaponArrow(arg) {}

ChildDeviceReflectArrow::~ChildDeviceReflectArrow() = default;

void ChildDeviceReflectArrow::enter_(ksys::act::ai::InlineParamPack* params) {
    WithoutWeaponArrow::enter_(params);
}

void ChildDeviceReflectArrow::loadParams_() {
    WithoutWeaponArrow::loadParams_();
    getStaticParam(&mReflectCountMax_s, "ReflectCountMax");
    getStaticParam(&mReflectAimSpeed_s, "ReflectAimSpeed");
    getStaticParam(&mReflectAccel_s, "ReflectAccel");
}

}  // namespace uking::ai
