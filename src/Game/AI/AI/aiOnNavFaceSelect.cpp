#include "Game/AI/AI/aiOnNavFaceSelect.h"

namespace uking::ai {

OnNavFaceSelect::OnNavFaceSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

OnNavFaceSelect::~OnNavFaceSelect() = default;

bool OnNavFaceSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void OnNavFaceSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void OnNavFaceSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void OnNavFaceSelect::loadParams_() {}

}  // namespace uking::ai
