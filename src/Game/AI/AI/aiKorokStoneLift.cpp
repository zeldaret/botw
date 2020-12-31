#include "Game/AI/AI/aiKorokStoneLift.h"

namespace uking::ai {

KorokStoneLift::KorokStoneLift(const InitArg& arg) : SimpleLiftable(arg) {}

KorokStoneLift::~KorokStoneLift() = default;

bool KorokStoneLift::init_(sead::Heap* heap) {
    return SimpleLiftable::init_(heap);
}

void KorokStoneLift::enter_(ksys::act::ai::InlineParamPack* params) {
    SimpleLiftable::enter_(params);
}

void KorokStoneLift::leave_() {
    SimpleLiftable::leave_();
}

void KorokStoneLift::loadParams_() {}

}  // namespace uking::ai
