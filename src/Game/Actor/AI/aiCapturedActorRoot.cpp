#include "Game/Actor/AI/aiCapturedActorRoot.h"

namespace uking::ai {

CapturedActorRoot::CapturedActorRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

CapturedActorRoot::~CapturedActorRoot() = default;

bool CapturedActorRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void CapturedActorRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void CapturedActorRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void CapturedActorRoot::loadParams_() {
    getStaticParam(&mInvalidTgtTimerVal_s, "InvalidTgtTimerVal");
    getStaticParam(&mInvalidEscapeTimerVal_s, "InvalidEscapeTimerVal");
    getStaticParam(&mIsDeleteWhenDead_s, "IsDeleteWhenDead");
    getStaticParam(&mIsDeadWhenPut_s, "IsDeadWhenPut");
    getStaticParam(&mIsEscapeWhenPut_s, "IsEscapeWhenPut");
    getStaticParam(&mIsDeadWhenDrop_s, "IsDeadWhenDrop");
    getMapUnitParam(&mIsPlayerPut_m, "IsPlayerPut");
    getMapUnitParam(&mIsLocatorCreate_m, "IsLocatorCreate");
    getMapUnitParam(&mIsCreateDead_m, "IsCreateDead");
    // FIXME: CALL _ZNK4ksys3act2ai6RootAi18getAITreeVariable2EPPbRKN4sead14SafeStringBaseIcEE @
    // 0x7100d66968
}

}  // namespace uking::ai
