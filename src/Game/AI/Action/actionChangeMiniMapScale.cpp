#include "Game/AI/Action/actionChangeMiniMapScale.h"

namespace uking::action {

ChangeMiniMapScale::ChangeMiniMapScale(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ChangeMiniMapScale::~ChangeMiniMapScale() = default;

bool ChangeMiniMapScale::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ChangeMiniMapScale::loadParams_() {
    getDynamicParam(&mScaleLevel_d, "ScaleLevel");
}

}  // namespace uking::action
