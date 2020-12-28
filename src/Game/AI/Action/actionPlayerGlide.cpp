#include "Game/AI/Action/actionPlayerGlide.h"

namespace uking::action {

PlayerGlide::PlayerGlide(const InitArg& arg) : PlayerAction(arg) {}

void PlayerGlide::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerGlide::leave_() {
    PlayerAction::leave_();
}

void PlayerGlide::loadParams_() {
    getStaticParam(&mGlideSpeedMax_s, "GlideSpeedMax");
    getStaticParam(&mLv2GlideSpeedMax_s, "Lv2GlideSpeedMax");
    getStaticParam(&mGlideBodyFrontX_s, "GlideBodyFrontX");
    getStaticParam(&mGlideBodyBackX_s, "GlideBodyBackX");
    getStaticParam(&mGlideBodySideZ_s, "GlideBodySideZ");
    getStaticParam(&mGlideRotMax_s, "GlideRotMax");
    getStaticParam(&mGlideRotMin_s, "GlideRotMin");
    getStaticParam(&mGlideRotRate_s, "GlideRotRate");
    getStaticParam(&mWindScale_s, "WindScale");
    getStaticParam(&mOverSpeedDec_s, "OverSpeedDec");
    getStaticParam(&mGlideRotSpeed_s, "GlideRotSpeed");
    getStaticParam(&mGlideNoSideAngle_s, "GlideNoSideAngle");
}

void PlayerGlide::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action
