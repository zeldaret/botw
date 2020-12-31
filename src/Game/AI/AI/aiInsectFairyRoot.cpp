#include "Game/AI/AI/aiInsectFairyRoot.h"

namespace uking::ai {

InsectFairyRoot::InsectFairyRoot(const InitArg& arg) : InsectRoot(arg) {}

InsectFairyRoot::~InsectFairyRoot() = default;

bool InsectFairyRoot::init_(sead::Heap* heap) {
    return InsectRoot::init_(heap);
}

void InsectFairyRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    InsectRoot::enter_(params);
}

void InsectFairyRoot::leave_() {
    InsectRoot::leave_();
}

void InsectFairyRoot::loadParams_() {
    InsectRoot::loadParams_();
}

}  // namespace uking::ai
