#include "Game/AI/Action/actionSearch.h"

namespace uking::action {

Search::Search(const InitArg& arg) : ActionWithAS(arg) {}

Search::~Search() = default;

bool Search::init_(sead::Heap* heap) {
    return ActionWithAS::init_(heap);
}

void Search::enter_(ksys::act::ai::InlineParamPack* params) {
    ActionWithAS::enter_(params);
}

void Search::leave_() {
    ActionWithAS::leave_();
}

void Search::loadParams_() {
    ActionWithPosAngReduce::loadParams_();
    getStaticParam(&mNoChangeTime_s, "NoChangeTime");
}

void Search::calc_() {
    ActionWithAS::calc_();
}

}  // namespace uking::action
