#include "Game/AI/AI/aiGanonRecognizeRoot.h"

namespace uking::ai {

GanonRecognizeRoot::GanonRecognizeRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

GanonRecognizeRoot::~GanonRecognizeRoot() = default;

bool GanonRecognizeRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void GanonRecognizeRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void GanonRecognizeRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void GanonRecognizeRoot::loadParams_() {}

}  // namespace uking::ai
