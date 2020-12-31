#include "Game/AI/AI/aiGanonNormalRoot.h"

namespace uking::ai {

GanonNormalRoot::GanonNormalRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

GanonNormalRoot::~GanonNormalRoot() = default;

bool GanonNormalRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void GanonNormalRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void GanonNormalRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void GanonNormalRoot::loadParams_() {}

}  // namespace uking::ai
