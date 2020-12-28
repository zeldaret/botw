#include "Game/AI/Action/actionNPCHorseCustomReception.h"

namespace uking::action {

NPCHorseCustomReception::NPCHorseCustomReception(const InitArg& arg) : ksys::act::ai::Action(arg) {}

NPCHorseCustomReception::~NPCHorseCustomReception() = default;

bool NPCHorseCustomReception::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void NPCHorseCustomReception::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void NPCHorseCustomReception::loadParams_() {
    getDynamicParam(&mCustomItemType_d, "CustomItemType");
}

void NPCHorseCustomReception::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
