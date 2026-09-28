#include "Game/Actor/AI/aiMagneGrabbedPartsRangeSelector.h"

namespace uking::ai {

MagneGrabbedPartsRangeSelector::MagneGrabbedPartsRangeSelector(const InitArg& arg)
    : NewRangeSelect(arg) {}

MagneGrabbedPartsRangeSelector::~MagneGrabbedPartsRangeSelector() = default;

bool MagneGrabbedPartsRangeSelector::init_(sead::Heap* heap) {
    return NewRangeSelect::init_(heap);
}

void MagneGrabbedPartsRangeSelector::enter_(ksys::act::ai::InlineParamPack* params) {
    NewRangeSelect::enter_(params);
}

void MagneGrabbedPartsRangeSelector::leave_() {
    NewRangeSelect::leave_();
}

void MagneGrabbedPartsRangeSelector::loadParams_() {
    NewRangeSelect::loadParams_();
    getStaticParam(&mPartsName_s, "PartsName");
}

}  // namespace uking::ai
