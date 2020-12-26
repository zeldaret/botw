#include "Game/AI/Action/actionShowMemoryPhoto.h"

namespace uking::action {

ShowMemoryPhoto::ShowMemoryPhoto(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ShowMemoryPhoto::~ShowMemoryPhoto() = default;

bool ShowMemoryPhoto::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ShowMemoryPhoto::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ShowMemoryPhoto::leave_() {
    ksys::act::ai::Action::leave_();
}

void ShowMemoryPhoto::loadParams_() {
    getDynamicParam(&mPhotoNo_d, "PhotoNo");
}

void ShowMemoryPhoto::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
