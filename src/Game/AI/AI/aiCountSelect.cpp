#include "Game/AI/AI/aiCountSelect.h"

namespace uking::ai {

CountSelect::CountSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

CountSelect::~CountSelect() = default;

bool CountSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void CountSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void CountSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void CountSelect::loadParams_() {
    getStaticParam(&mCounter_s, "Counter");
}

}  // namespace uking::ai
