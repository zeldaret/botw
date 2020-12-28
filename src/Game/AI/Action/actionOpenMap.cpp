#include "Game/AI/Action/actionOpenMap.h"

namespace uking::action {

OpenMap::OpenMap(const InitArg& arg) : ksys::act::ai::Action(arg) {}

OpenMap::~OpenMap() = default;

bool OpenMap::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void OpenMap::loadParams_() {
    getDynamicParam(&mScaleLevel_d, "ScaleLevel");
    getDynamicParam(&mWorldPos_d, "WorldPos");
}

}  // namespace uking::action
