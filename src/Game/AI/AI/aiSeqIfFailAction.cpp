#include "Game/AI/AI/aiSeqIfFailAction.h"

namespace uking::ai {

SeqIfFailAction::SeqIfFailAction(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SeqIfFailAction::~SeqIfFailAction() = default;

bool SeqIfFailAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void SeqIfFailAction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void SeqIfFailAction::leave_() {
    ksys::act::ai::Ai::leave_();
}

void SeqIfFailAction::loadParams_() {
    getStaticParam(&mIsEndChangeable_s, "IsEndChangeable");
}

}  // namespace uking::ai
