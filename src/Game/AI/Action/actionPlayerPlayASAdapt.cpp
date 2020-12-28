#include "Game/AI/Action/actionPlayerPlayASAdapt.h"

namespace uking::action {

PlayerPlayASAdapt::PlayerPlayASAdapt(const InitArg& arg) : PlayASForDemo(arg) {}

PlayerPlayASAdapt::~PlayerPlayASAdapt() = default;

void PlayerPlayASAdapt::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayASForDemo::enter_(params);
}

void PlayerPlayASAdapt::leave_() {
    PlayASForDemo::leave_();
}

void PlayerPlayASAdapt::loadParams_() {
    PlayASForDemo::loadParams_();
    getDynamicParam(&mIsOneTimeEndKeep_d, "IsOneTimeEndKeep");
    getDynamicParam(&mNoErrorCheck_d, "NoErrorCheck");
}

void PlayerPlayASAdapt::calc_() {
    PlayASForDemo::calc_();
}

}  // namespace uking::action
