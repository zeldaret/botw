#include "Game/AI/AI/aiWetSelect.h"

namespace uking::ai {

WetSelect::WetSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

WetSelect::~WetSelect() = default;

bool WetSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void WetSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void WetSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void WetSelect::loadParams_() {
    getStaticParam(&mWetRateThreashold_s, "WetRateThreashold");
}

}  // namespace uking::ai
