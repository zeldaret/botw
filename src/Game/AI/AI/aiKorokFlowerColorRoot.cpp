#include "Game/AI/AI/aiKorokFlowerColorRoot.h"

namespace uking::ai {

KorokFlowerColorRoot::KorokFlowerColorRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

KorokFlowerColorRoot::~KorokFlowerColorRoot() = default;

bool KorokFlowerColorRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void KorokFlowerColorRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void KorokFlowerColorRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void KorokFlowerColorRoot::loadParams_() {
    getMapUnitParam(&mKorokFlowerColorNum_m, "KorokFlowerColorNum");
}

}  // namespace uking::ai
