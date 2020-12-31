#include "Game/AI/AI/aiChangeWindTagRoot.h"

namespace uking::ai {

ChangeWindTagRoot::ChangeWindTagRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

ChangeWindTagRoot::~ChangeWindTagRoot() = default;

bool ChangeWindTagRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void ChangeWindTagRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void ChangeWindTagRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void ChangeWindTagRoot::loadParams_() {
    getMapUnitParam(&mDirection_m, "Direction");
    getMapUnitParam(&mWindSpeed_m, "WindSpeed");
}

}  // namespace uking::ai
