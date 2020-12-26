#include "Game/AI/Action/actionChangeMiniMapScale.h"

namespace uking::action {

ChangeMiniMapScale::ChangeMiniMapScale(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ChangeMiniMapScale::~ChangeMiniMapScale() = default;

bool ChangeMiniMapScale::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ChangeMiniMapScale::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ChangeMiniMapScale::leave_() {
    ksys::act::ai::Action::leave_();
}

void ChangeMiniMapScale::loadParams_() {
    getDynamicParam(&mScaleLevel_d, "ScaleLevel");
}

void ChangeMiniMapScale::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
