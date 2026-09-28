#include "Game/Actor/Action/actionBackWalkWithAS.h"

namespace uking::action {

BackWalkWithAS::BackWalkWithAS(const InitArg& arg) : NormalBackWalk(arg) {}

BackWalkWithAS::~BackWalkWithAS() = default;

void BackWalkWithAS::enter_(ksys::act::ai::InlineParamPack* params) {
    NormalBackWalk::enter_(params);
}

void BackWalkWithAS::loadParams_() {
    NormalBackWalk::loadParams_();
    getStaticParam(&mASName_s, "ASName");
}

void BackWalkWithAS::calc_() {
    NormalBackWalk::calc_();
}

}  // namespace uking::action
