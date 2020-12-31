#include "Game/AI/AI/aiSimpleWildlifeRoot.h"

namespace uking::ai {

SimpleWildlifeRoot::SimpleWildlifeRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SimpleWildlifeRoot::~SimpleWildlifeRoot() = default;

bool SimpleWildlifeRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void SimpleWildlifeRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void SimpleWildlifeRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void SimpleWildlifeRoot::loadParams_() {
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
