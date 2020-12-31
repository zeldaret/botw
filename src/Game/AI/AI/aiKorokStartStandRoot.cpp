#include "Game/AI/AI/aiKorokStartStandRoot.h"

namespace uking::ai {

KorokStartStandRoot::KorokStartStandRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

KorokStartStandRoot::~KorokStartStandRoot() = default;

bool KorokStartStandRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void KorokStartStandRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void KorokStartStandRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void KorokStartStandRoot::loadParams_() {}

}  // namespace uking::ai
