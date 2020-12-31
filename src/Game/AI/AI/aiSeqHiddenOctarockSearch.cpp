#include "Game/AI/AI/aiSeqHiddenOctarockSearch.h"

namespace uking::ai {

SeqHiddenOctarockSearch::SeqHiddenOctarockSearch(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SeqHiddenOctarockSearch::~SeqHiddenOctarockSearch() = default;

bool SeqHiddenOctarockSearch::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void SeqHiddenOctarockSearch::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void SeqHiddenOctarockSearch::leave_() {
    ksys::act::ai::Ai::leave_();
}

void SeqHiddenOctarockSearch::loadParams_() {}

}  // namespace uking::ai
