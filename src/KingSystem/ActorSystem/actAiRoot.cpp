#include "KingSystem/ActorSystem/actAiRoot.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiClassDef.h"
#include "KingSystem/Utils/InitTimeInfo.h"

namespace ksys::act::ai {

RootAi::RootAi(const InitArg& arg) : Ai(arg) {
    mBehaviorsByStopAndCalcTiming[0].fill({});
    mBehaviorsByStopAndCalcTiming[1].fill({});
}

RootAi::~RootAi() {
    mQueries.finalize();
    mBehaviors.finalize();
    mAis.finalize();
    mActions.finalize();
    if (_140)
        delete _140;
}

bool RootAi::loadMapUnitParams(const AIDef& def, sead::Heap* heap) {
    return mMapUnitParams.load(*mActor, def, heap, AIDefInstParamKind::MapUnit);
}

bool RootAi::loadAITreeParams(const AIDef& def, sead::Heap* heap) {
    return mAiTreeParams.load(*mActor, def, heap, AIDefInstParamKind::AITree);
}

bool RootAi::isActorDeletedOrDeleting() const {
    return mActor->isDeletedOrDeleting();
}

bool RootAi::getMapUnitParam(sead::SafeString* value, const sead::SafeString& key) const {
    sead::SafeString out;
    if (mMapUnitParams.getString(&out, key)) {
        *value = out.cstr();
        return true;
    }
    *value = sead::SafeString::cEmptyString;
    return false;
}

bool RootAi::getMapUnitParam(const s32** value, const sead::SafeString& key) const {
    auto* ptr =
        static_cast<int*>(mMapUnitParams.getAITreeVariablePointer(key, AIDefParamType::Int));
    static const s32 sDefault{};
    *value = ptr ? ptr : &sDefault;
    return ptr != nullptr;
}

bool RootAi::getMapUnitParam(const f32** value, const sead::SafeString& key) const {
    auto* ptr =
        static_cast<f32*>(mMapUnitParams.getAITreeVariablePointer(key, AIDefParamType::Float));
    static const f32 sDefault{};
    *value = ptr ? ptr : &sDefault;
    return ptr != nullptr;
}

bool RootAi::getMapUnitParam(const sead::Vector3f** value, const sead::SafeString& key) const {
    auto* ptr = static_cast<sead::Vector3f*>(
        mMapUnitParams.getAITreeVariablePointer(key, AIDefParamType::Vec3));
    *value = ptr ? ptr : &sead::Vector3f::zero;
    return ptr != nullptr;
}

bool RootAi::getMapUnitParam(const bool** value, const sead::SafeString& key) const {
    auto* ptr =
        static_cast<bool*>(mMapUnitParams.getAITreeVariablePointer(key, AIDefParamType::Bool));
    static const bool sDefault{};
    *value = ptr ? ptr : &sDefault;
    return ptr != nullptr;
}

namespace {
sead::FixedSafeString<64> sDefaultString;

struct Vec3Wrapper {
    util::InitTimeInfoEx init_time_info_ex;
    sead::Vector3f sDefaultVec3{0, 0, 0};
};
Vec3Wrapper sDefaultAITreeVariables;
}  // namespace

bool RootAi::getAITreeVariable(sead::SafeString** value, const sead::SafeString& key) const {
    auto* ptr = static_cast<sead::SafeString*>(
        mAiTreeParams.getAITreeVariablePointer(key, AIDefParamType::String));
    *value = ptr ? ptr : &sDefaultString;
    return ptr != nullptr;
}

bool RootAi::getAITreeVariable(s32** value, const sead::SafeString& key) const {
    auto* ptr = static_cast<s32*>(mAiTreeParams.getAITreeVariablePointer(key, AIDefParamType::Int));
    static s32 sDefault{};
    *value = ptr ? ptr : &sDefault;
    return ptr != nullptr;
}

bool RootAi::getAITreeVariable(f32** value, const sead::SafeString& key) const {
    auto* ptr =
        static_cast<f32*>(mAiTreeParams.getAITreeVariablePointer(key, AIDefParamType::Float));
    static f32 sDefault{};
    *value = ptr ? ptr : &sDefault;
    return ptr != nullptr;
}

bool RootAi::getAITreeVariable(sead::Vector3f** value, const sead::SafeString& key) const {
    auto* ptr = static_cast<sead::Vector3f*>(
        mAiTreeParams.getAITreeVariablePointer(key, AIDefParamType::Vec3));
    *value = ptr ? ptr : &sDefaultAITreeVariables.sDefaultVec3;
    return ptr != nullptr;
}

bool RootAi::getAITreeVariable(bool** value, const sead::SafeString& key) const {
    auto* ptr =
        static_cast<bool*>(mAiTreeParams.getAITreeVariablePointer(key, AIDefParamType::Bool));
    static bool sDefault{};
    *value = ptr ? ptr : &sDefault;
    return ptr != nullptr;
}

bool RootAi::getAITreeVariable(void** value, const sead::SafeString& key) const {
    auto* ptr = static_cast<void**>(
        mAiTreeParams.getAITreeVariablePointer(key, AIDefParamType::AITreeVariablePointer));
    static void* sDefault{};
    *value = ptr ? ptr : &sDefault;
    return ptr != nullptr;
}

bool RootAi::getAITreeVariable(u32** value, const sead::SafeString& key) const {
    auto* ptr =
        static_cast<u32*>(mAiTreeParams.getAITreeVariablePointer(key, AIDefParamType::UInt));
    static u32 sDefault{};
    *value = ptr ? ptr : &sDefault;
    return ptr != nullptr;
}

bool RootAi::getAITreeVariable2(sead::Vector3f** value, const sead::SafeString& key) const {
    return getAITreeVariable(value, key);
}

bool RootAi::getAITreeVariable2(bool** value, const sead::SafeString& key) const {
    return getAITreeVariable(value, key);
}

const char* getDefaultAiName(s32 root_idx) {
    static constexpr const char* names[] = {"DemoRootAI", "Root"};
    if (root_idx >= 2)
        return "";
    return names[root_idx];
}

const char* getDefaultActionName(s32) {
    return "";
}

}  // namespace ksys::act::ai
