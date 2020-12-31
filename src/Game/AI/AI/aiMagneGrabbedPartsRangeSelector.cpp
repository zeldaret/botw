#include "Game/AI/AI/aiMagneGrabbedPartsRangeSelector.h"

namespace uking::ai {

MagneGrabbedPartsRangeSelector::MagneGrabbedPartsRangeSelector(const InitArg& arg)
    : RangeSelect(arg) {}

MagneGrabbedPartsRangeSelector::~MagneGrabbedPartsRangeSelector() = default;

bool MagneGrabbedPartsRangeSelector::init_(sead::Heap* heap) {
    return RangeSelect::init_(heap);
}

void MagneGrabbedPartsRangeSelector::enter_(ksys::act::ai::InlineParamPack* params) {
    RangeSelect::enter_(params);
}

void MagneGrabbedPartsRangeSelector::leave_() {
    RangeSelect::leave_();
}

void MagneGrabbedPartsRangeSelector::loadParams_() {
    RangeSelect::loadParams_();
    getStaticParam(&mPartsName_s, "PartsName");
}

}  // namespace uking::ai
