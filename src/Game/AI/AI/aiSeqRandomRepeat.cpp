#include "Game/AI/AI/aiSeqRandomRepeat.h"

namespace uking::ai {

SeqRandomRepeat::SeqRandomRepeat(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SeqRandomRepeat::~SeqRandomRepeat() = default;

bool SeqRandomRepeat::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void SeqRandomRepeat::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void SeqRandomRepeat::leave_() {
    ksys::act::ai::Ai::leave_();
}

void SeqRandomRepeat::loadParams_() {
    getStaticParam(&mMinActionNum_s, "MinActionNum");
    getStaticParam(&mMaxActionNum_s, "MaxActionNum");
    getStaticParam(&mIsEndChangeable_s, "IsEndChangeable");
}

}  // namespace uking::ai
