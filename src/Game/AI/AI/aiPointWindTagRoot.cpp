#include "Game/AI/AI/aiPointWindTagRoot.h"

namespace uking::ai {

PointWindTagRoot::PointWindTagRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

PointWindTagRoot::~PointWindTagRoot() = default;

bool PointWindTagRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void PointWindTagRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void PointWindTagRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void PointWindTagRoot::loadParams_() {
    getMapUnitParam(&mDirection_m, "Direction");
    getMapUnitParam(&mWindSpeed_m, "WindSpeed");
    getMapUnitParam(&mShape_m, "Shape");
}

}  // namespace uking::ai
