#include "Game/AI/AI/aiPartsNoticeSelect.h"

namespace uking::ai {

PartsNoticeSelect::PartsNoticeSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

PartsNoticeSelect::~PartsNoticeSelect() = default;

bool PartsNoticeSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void PartsNoticeSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void PartsNoticeSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void PartsNoticeSelect::loadParams_() {
    getStaticParam(&mPartsName_s, "PartsName");
}

}  // namespace uking::ai
