#include "Game/AI/AI/aiOutOfScreen.h"

namespace uking::ai {

OutOfScreen::OutOfScreen(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

OutOfScreen::~OutOfScreen() = default;

bool OutOfScreen::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void OutOfScreen::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void OutOfScreen::leave_() {
    ksys::act::ai::Ai::leave_();
}

void OutOfScreen::loadParams_() {
    getStaticParam(&mUpdateInterval_s, "UpdateInterval");
    getStaticParam(&mTagetDistance_s, "TagetDistance");
    getStaticParam(&mDeleteDistance_s, "DeleteDistance");
}

}  // namespace uking::ai
