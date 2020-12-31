#include "Game/AI/AI/aiNoticePartsRangeSelector.h"

namespace uking::ai {

NoticePartsRangeSelector::NoticePartsRangeSelector(const InitArg& arg) : RangeSelect(arg) {}

NoticePartsRangeSelector::~NoticePartsRangeSelector() = default;

bool NoticePartsRangeSelector::init_(sead::Heap* heap) {
    return RangeSelect::init_(heap);
}

void NoticePartsRangeSelector::enter_(ksys::act::ai::InlineParamPack* params) {
    RangeSelect::enter_(params);
}

void NoticePartsRangeSelector::leave_() {
    RangeSelect::leave_();
}

void NoticePartsRangeSelector::loadParams_() {
    RangeSelect::loadParams_();
    getStaticParam(&mPartsName_s, "PartsName");
}

}  // namespace uking::ai
