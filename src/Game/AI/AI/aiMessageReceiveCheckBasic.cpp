#include "Game/AI/AI/aiMessageReceiveCheckBasic.h"

namespace uking::ai {

MessageReceiveCheckBasic::MessageReceiveCheckBasic(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

MessageReceiveCheckBasic::~MessageReceiveCheckBasic() = default;

bool MessageReceiveCheckBasic::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void MessageReceiveCheckBasic::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void MessageReceiveCheckBasic::leave_() {
    ksys::act::ai::Ai::leave_();
}

void MessageReceiveCheckBasic::loadParams_() {}

}  // namespace uking::ai
