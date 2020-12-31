#include "Game/AI/AI/aiSeqTimeredAction.h"

namespace uking::ai {

SeqTimeredAction::SeqTimeredAction(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SeqTimeredAction::~SeqTimeredAction() = default;

bool SeqTimeredAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void SeqTimeredAction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void SeqTimeredAction::leave_() {
    ksys::act::ai::Ai::leave_();
}

void SeqTimeredAction::loadParams_() {
    getStaticParam(&mActionTime_s, "ActionTime");
}

}  // namespace uking::ai
