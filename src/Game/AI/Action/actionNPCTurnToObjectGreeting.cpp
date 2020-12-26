#include "Game/AI/Action/actionNPCTurnToObjectGreeting.h"

namespace uking::action {

NPCTurnToObjectGreeting::NPCTurnToObjectGreeting(const InitArg& arg) : NPCTurnToObject(arg) {}

NPCTurnToObjectGreeting::~NPCTurnToObjectGreeting() = default;

bool NPCTurnToObjectGreeting::init_(sead::Heap* heap) {
    return NPCTurnToObject::init_(heap);
}

void NPCTurnToObjectGreeting::enter_(ksys::act::ai::InlineParamPack* params) {
    NPCTurnToObject::enter_(params);
}

void NPCTurnToObjectGreeting::leave_() {
    NPCTurnToObject::leave_();
}

void NPCTurnToObjectGreeting::loadParams_() {
    NPCTurnToObject::loadParams_();
    getDynamicParam(&mGreetingType_d, "GreetingType");
}

void NPCTurnToObjectGreeting::calc_() {
    NPCTurnToObject::calc_();
}

}  // namespace uking::action
