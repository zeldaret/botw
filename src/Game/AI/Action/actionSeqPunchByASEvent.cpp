#include "Game/AI/Action/actionSeqPunchByASEvent.h"

namespace uking::action {

SeqPunchByASEvent::SeqPunchByASEvent(const InitArg& arg) : ActionWithAS(arg) {}

SeqPunchByASEvent::~SeqPunchByASEvent() = default;

bool SeqPunchByASEvent::init_(sead::Heap* heap) {
    return ActionWithAS::init_(heap);
}

void SeqPunchByASEvent::enter_(ksys::act::ai::InlineParamPack* params) {
    ActionWithAS::enter_(params);
}

void SeqPunchByASEvent::leave_() {
    ActionWithAS::leave_();
}

void SeqPunchByASEvent::loadParams_() {
    ActionWithPosAngReduce::loadParams_();
    getStaticParam(&mASName_s, "ASName");
    getStaticParam(&mAttackIntensity_s, "AttackIntensity");
    getStaticParam(&mIsHammer_s, "IsHammer");
    getStaticParam(&mASName_s, "ASName");
}

void SeqPunchByASEvent::calc_() {
    ActionWithAS::calc_();
}

}  // namespace uking::action
