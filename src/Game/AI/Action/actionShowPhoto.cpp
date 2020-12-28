#include "Game/AI/Action/actionShowPhoto.h"

namespace uking::action {

ShowPhoto::ShowPhoto(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ShowPhoto::~ShowPhoto() = default;

bool ShowPhoto::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ShowPhoto::loadParams_() {
    getDynamicParam(&mActorName_d, "ActorName");
}

}  // namespace uking::action
