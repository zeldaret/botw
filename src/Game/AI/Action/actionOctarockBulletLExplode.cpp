#include "Game/AI/Action/actionOctarockBulletLExplode.h"

namespace uking::action {

OctarockBulletLExplode::OctarockBulletLExplode(const InitArg& arg) : Explode(arg) {}

OctarockBulletLExplode::~OctarockBulletLExplode() = default;

bool OctarockBulletLExplode::init_(sead::Heap* heap) {
    return Explode::init_(heap);
}

void OctarockBulletLExplode::enter_(ksys::act::ai::InlineParamPack* params) {
    Explode::enter_(params);
}

void OctarockBulletLExplode::leave_() {
    Explode::leave_();
}

void OctarockBulletLExplode::loadParams_() {
    Explode::loadParams_();
}

void OctarockBulletLExplode::calc_() {
    Explode::calc_();
}

}  // namespace uking::action
