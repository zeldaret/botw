#include "Game/AI/AI/aiGearRangeSelect.h"

namespace uking::ai {

GearRangeSelect::GearRangeSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

GearRangeSelect::~GearRangeSelect() = default;

bool GearRangeSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void GearRangeSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void GearRangeSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void GearRangeSelect::loadParams_() {
    getStaticParam(&mGearThreashold_s, "GearThreashold");
    getStaticParam(&mCheckOnce_s, "CheckOnce");
}

}  // namespace uking::ai
