#include "Game/AI/Action/actionShowMemoryPhoto.h"

namespace uking::action {

ShowMemoryPhoto::ShowMemoryPhoto(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ShowMemoryPhoto::~ShowMemoryPhoto() = default;

bool ShowMemoryPhoto::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ShowMemoryPhoto::loadParams_() {
    getDynamicParam(&mPhotoNo_d, "PhotoNo");
}

}  // namespace uking::action
