#include "Game/AI/Action/actionBulletVertivalRotateOwner.h"

namespace uking::action {

BulletVertivalRotateOwner::BulletVertivalRotateOwner(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

BulletVertivalRotateOwner::~BulletVertivalRotateOwner() = default;

bool BulletVertivalRotateOwner::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void BulletVertivalRotateOwner::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void BulletVertivalRotateOwner::leave_() {
    ksys::act::ai::Action::leave_();
}

void BulletVertivalRotateOwner::loadParams_() {
    getStaticParam(&mRotSpeed_s, "RotSpeed");
    getStaticParam(&mRotSpdAccRatio_s, "RotSpdAccRatio");
    getStaticParam(&mOffsetY_s, "OffsetY");
}

void BulletVertivalRotateOwner::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
