#include "Game/AI/AI/aiSeqTimeredPlusRandomTwoAction.h"

namespace uking::ai {

SeqTimeredPlusRandomTwoAction::SeqTimeredPlusRandomTwoAction(const InitArg& arg)
    : SeqTimeredTwoAction(arg) {}

SeqTimeredPlusRandomTwoAction::~SeqTimeredPlusRandomTwoAction() = default;

bool SeqTimeredPlusRandomTwoAction::init_(sead::Heap* heap) {
    return SeqTimeredTwoAction::init_(heap);
}

void SeqTimeredPlusRandomTwoAction::enter_(ksys::act::ai::InlineParamPack* params) {
    SeqTimeredTwoAction::enter_(params);
}

void SeqTimeredPlusRandomTwoAction::leave_() {
    SeqTimeredTwoAction::leave_();
}

void SeqTimeredPlusRandomTwoAction::loadParams_() {
    SeqTimeredTwoAction::loadParams_();
    getStaticParam(&mFirstActionRandMax_s, "FirstActionRandMax");
    getStaticParam(&mSecondActionRandMax_s, "SecondActionRandMax");
}

}  // namespace uking::ai
