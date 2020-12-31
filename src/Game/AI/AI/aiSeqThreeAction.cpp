#include "Game/AI/AI/aiSeqThreeAction.h"

namespace uking::ai {

SeqThreeAction::SeqThreeAction(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SeqThreeAction::~SeqThreeAction() = default;

bool SeqThreeAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void SeqThreeAction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void SeqThreeAction::leave_() {
    ksys::act::ai::Ai::leave_();
}

void SeqThreeAction::loadParams_() {
    getStaticParam(&mIsFinishedByFailAction_s, "IsFinishedByFailAction");
    getStaticParam(&mIsEndChangeable_s, "IsEndChangeable");
    getStaticParam(&mIsNoChangeable_s, "IsNoChangeable");
}

}  // namespace uking::ai
