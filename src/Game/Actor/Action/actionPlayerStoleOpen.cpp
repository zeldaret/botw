#include "Game/Actor/Action/actionPlayerStoleOpen.h"

namespace uking::action {

PlayerStoleOpen::PlayerStoleOpen(const InitArg& arg) : BindPlayerNodeEx(arg) {}

void PlayerStoleOpen::enter_(ksys::act::ai::InlineParamPack* params) {
    BindPlayerNodeEx::enter_(params);
}

void PlayerStoleOpen::loadParams_() {
    BindPlayerNodeBase::loadParams_();
    getStaticParam(&mEnlargeSpd_s, "EnlargeSpd");
}

void PlayerStoleOpen::calc_() {
    BindPlayerNodeEx::calc_();
}

}  // namespace uking::action
