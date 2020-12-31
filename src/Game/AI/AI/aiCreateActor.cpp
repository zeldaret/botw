#include "Game/AI/AI/aiCreateActor.h"

namespace uking::ai {

CreateActor::CreateActor(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

CreateActor::~CreateActor() = default;

bool CreateActor::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void CreateActor::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void CreateActor::leave_() {
    ksys::act::ai::Ai::leave_();
}

void CreateActor::loadParams_() {
    getStaticParam(&mCreatePriorityState_s, "CreatePriorityState");
    getStaticParam(&mScale_s, "Scale");
    getStaticParam(&mActorName_s, "ActorName");
}

}  // namespace uking::ai
