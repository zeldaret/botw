#include "Game/Actor/AI/aiNoticePartsRangeSelector.h"

namespace uking::ai {

NoticePartsRangeSelector::NoticePartsRangeSelector(const InitArg& arg) : NewRangeSelect(arg) {}

NoticePartsRangeSelector::~NoticePartsRangeSelector() = default;

bool NoticePartsRangeSelector::init_(sead::Heap* heap) {
    return NewRangeSelect::init_(heap);
}

void NoticePartsRangeSelector::enter_(ksys::act::ai::InlineParamPack* params) {
    NewRangeSelect::enter_(params);
}

void NoticePartsRangeSelector::leave_() {
    NewRangeSelect::leave_();
}

void NoticePartsRangeSelector::loadParams_() {
    NewRangeSelect::loadParams_();
    getStaticParam(&mPartsName_s, "PartsName");
}

}  // namespace uking::ai
