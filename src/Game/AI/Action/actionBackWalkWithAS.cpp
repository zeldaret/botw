#include "Game/AI/Action/actionBackWalkWithAS.h"

namespace uking::action {

BackWalkWithAS::BackWalkWithAS(const InitArg& arg) : BackWalkEx(arg) {}

BackWalkWithAS::~BackWalkWithAS() = default;

void BackWalkWithAS::enter_(ksys::act::ai::InlineParamPack* params) {
    BackWalkEx::enter_(params);
}

void BackWalkWithAS::loadParams_() {
    BackWalkEx::loadParams_();
    getStaticParam(&mASName_s, "ASName");
}

void BackWalkWithAS::calc_() {
    BackWalkEx::calc_();
}

}  // namespace uking::action
