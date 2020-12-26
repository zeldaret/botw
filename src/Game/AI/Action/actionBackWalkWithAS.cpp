#include "Game/AI/Action/actionBackWalkWithAS.h"

namespace uking::action {

BackWalkWithAS::BackWalkWithAS(const InitArg& arg) : BackWalkEx(arg) {}

BackWalkWithAS::~BackWalkWithAS() = default;

bool BackWalkWithAS::init_(sead::Heap* heap) {
    return BackWalkEx::init_(heap);
}

void BackWalkWithAS::enter_(ksys::act::ai::InlineParamPack* params) {
    BackWalkEx::enter_(params);
}

void BackWalkWithAS::leave_() {
    BackWalkEx::leave_();
}

void BackWalkWithAS::loadParams_() {
    BackWalkEx::loadParams_();
    getStaticParam(&mASName_s, "ASName");
}

void BackWalkWithAS::calc_() {
    BackWalkEx::calc_();
}

}  // namespace uking::action
