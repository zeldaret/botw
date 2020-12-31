#include "Game/AI/AI/aiDisplaySelect.h"

namespace uking::ai {

DisplaySelect::DisplaySelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

DisplaySelect::~DisplaySelect() = default;

bool DisplaySelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void DisplaySelect::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void DisplaySelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void DisplaySelect::loadParams_() {
    getStaticParam(&mRadius_s, "Radius");
    getStaticParam(&mIsCheckEveryFrame_s, "IsCheckEveryFrame");
}

}  // namespace uking::ai
