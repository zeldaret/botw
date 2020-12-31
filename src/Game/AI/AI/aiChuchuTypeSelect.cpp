#include "Game/AI/AI/aiChuchuTypeSelect.h"

namespace uking::ai {

ChuchuTypeSelect::ChuchuTypeSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

ChuchuTypeSelect::~ChuchuTypeSelect() = default;

bool ChuchuTypeSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void ChuchuTypeSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void ChuchuTypeSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void ChuchuTypeSelect::loadParams_() {}

}  // namespace uking::ai
