#include "Game/AI/Action/actionOpenMap.h"

namespace uking::action {

OpenMap::OpenMap(const InitArg& arg) : ksys::act::ai::Action(arg) {}

OpenMap::~OpenMap() = default;

bool OpenMap::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void OpenMap::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void OpenMap::leave_() {
    ksys::act::ai::Action::leave_();
}

void OpenMap::loadParams_() {
    getDynamicParam(&mScaleLevel_d, "ScaleLevel");
    getDynamicParam(&mWorldPos_d, "WorldPos");
}

void OpenMap::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
