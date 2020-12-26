#include "Game/AI/Action/actionOpenDungeonMessage.h"

namespace uking::action {

OpenDungeonMessage::OpenDungeonMessage(const InitArg& arg) : ksys::act::ai::Action(arg) {}

OpenDungeonMessage::~OpenDungeonMessage() = default;

bool OpenDungeonMessage::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void OpenDungeonMessage::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void OpenDungeonMessage::leave_() {
    ksys::act::ai::Action::leave_();
}

void OpenDungeonMessage::loadParams_() {
    getDynamicParam(&mMessageId_d, "MessageId");
}

void OpenDungeonMessage::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
