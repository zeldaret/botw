#include "Game/AI/AI/aiTemperatureRandSelect.h"

namespace uking::ai {

TemperatureRandSelect::TemperatureRandSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

TemperatureRandSelect::~TemperatureRandSelect() = default;

bool TemperatureRandSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void TemperatureRandSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void TemperatureRandSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void TemperatureRandSelect::loadParams_() {
    getStaticParam(&mBaseChangeRatio_s, "BaseChangeRatio");
    getStaticParam(&museBaseRatioTiming_s, "useBaseRatioTiming");
    getStaticParam(&mTemperatureChangeRatio_s, "TemperatureChangeRatio");
    getStaticParam(&mBaseTemperature_s, "BaseTemperature");
}

}  // namespace uking::ai
