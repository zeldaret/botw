#include "Game/AI/AI/aiSeqTimeredTwoAction.h"

namespace uking::ai {

SeqTimeredTwoAction::SeqTimeredTwoAction(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SeqTimeredTwoAction::~SeqTimeredTwoAction() = default;

bool SeqTimeredTwoAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void SeqTimeredTwoAction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void SeqTimeredTwoAction::leave_() {
    ksys::act::ai::Ai::leave_();
}

void SeqTimeredTwoAction::loadParams_() {
    getStaticParam(&mFirstActionTime_s, "FirstActionTime");
    getStaticParam(&mSecondActionTime_s, "SecondActionTime");
    getStaticParam(&mAllActionTime_s, "AllActionTime");
}

}  // namespace uking::ai
