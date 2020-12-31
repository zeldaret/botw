#include "Game/AI/AI/aiForbidDoubleNoticeSelect.h"

namespace uking::ai {

ForbidDoubleNoticeSelect::ForbidDoubleNoticeSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

ForbidDoubleNoticeSelect::~ForbidDoubleNoticeSelect() = default;

bool ForbidDoubleNoticeSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void ForbidDoubleNoticeSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void ForbidDoubleNoticeSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void ForbidDoubleNoticeSelect::loadParams_() {}

}  // namespace uking::ai
