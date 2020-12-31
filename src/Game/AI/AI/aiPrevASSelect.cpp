#include "Game/AI/AI/aiPrevASSelect.h"

namespace uking::ai {

PrevASSelect::PrevASSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

PrevASSelect::~PrevASSelect() = default;

bool PrevASSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void PrevASSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void PrevASSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void PrevASSelect::loadParams_() {
    getStaticParam(&mASName_s, "ASName");
}

}  // namespace uking::ai
