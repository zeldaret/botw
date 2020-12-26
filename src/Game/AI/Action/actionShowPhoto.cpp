#include "Game/AI/Action/actionShowPhoto.h"

namespace uking::action {

ShowPhoto::ShowPhoto(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ShowPhoto::~ShowPhoto() = default;

bool ShowPhoto::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ShowPhoto::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ShowPhoto::leave_() {
    ksys::act::ai::Action::leave_();
}

void ShowPhoto::loadParams_() {
    getDynamicParam(&mActorName_d, "ActorName");
}

void ShowPhoto::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
