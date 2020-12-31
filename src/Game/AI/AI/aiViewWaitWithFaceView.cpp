#include "Game/AI/AI/aiViewWaitWithFaceView.h"

namespace uking::ai {

ViewWaitWithFaceView::ViewWaitWithFaceView(const InitArg& arg) : ViewWait(arg) {}

ViewWaitWithFaceView::~ViewWaitWithFaceView() = default;

bool ViewWaitWithFaceView::init_(sead::Heap* heap) {
    return ViewWait::init_(heap);
}

void ViewWaitWithFaceView::enter_(ksys::act::ai::InlineParamPack* params) {
    ViewWait::enter_(params);
}

void ViewWaitWithFaceView::leave_() {
    ViewWait::leave_();
}

void ViewWaitWithFaceView::loadParams_() {
    ViewWait::loadParams_();
    getStaticParam(&mUseSimpleOffset_s, "UseSimpleOffset");
}

}  // namespace uking::ai
