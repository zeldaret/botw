#include "Game/AI/Action/actionGiantSleep.h"

namespace uking::action {

GiantSleep::GiantSleep(const InitArg& arg) : Sleep(arg) {}

GiantSleep::~GiantSleep() = default;

bool GiantSleep::init_(sead::Heap* heap) {
    return Sleep::init_(heap);
}

void GiantSleep::enter_(ksys::act::ai::InlineParamPack* params) {
    Sleep::enter_(params);
}

void GiantSleep::leave_() {
    Sleep::leave_();
}

void GiantSleep::loadParams_() {
    Sleep::loadParams_();
    getStaticParam(&mRidableRigidBodyName_s, "RidableRigidBodyName");
    getStaticParam(&mASName_s, "ASName");
}

void GiantSleep::calc_() {
    Sleep::calc_();
}

}  // namespace uking::action
