#include "Game/AI/AI/aiMagneGrabSelect.h"

namespace uking::ai {

MagneGrabSelect::MagneGrabSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

MagneGrabSelect::~MagneGrabSelect() = default;

bool MagneGrabSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void MagneGrabSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void MagneGrabSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void MagneGrabSelect::loadParams_() {}

}  // namespace uking::ai
