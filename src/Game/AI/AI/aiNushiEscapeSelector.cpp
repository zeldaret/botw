#include "Game/AI/AI/aiNushiEscapeSelector.h"

namespace uking::ai {

NushiEscapeSelector::NushiEscapeSelector(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

NushiEscapeSelector::~NushiEscapeSelector() = default;

bool NushiEscapeSelector::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void NushiEscapeSelector::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void NushiEscapeSelector::leave_() {
    ksys::act::ai::Ai::leave_();
}

void NushiEscapeSelector::loadParams_() {
    getStaticParam(&mNumOfAllowedEscapes_s, "NumOfAllowedEscapes");
}

}  // namespace uking::ai
