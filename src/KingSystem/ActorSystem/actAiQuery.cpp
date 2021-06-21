#include "KingSystem/ActorSystem/actAiQuery.h"
#include <evfl/Param.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/ActorSystem/actAiClassDef.h"
#include "KingSystem/ActorSystem/actAiRoot.h"
#include "KingSystem/Resource/Actor/resResourceAIProgram.h"

namespace ksys::act::ai {

Query::Query(const InitArg& arg) : mActor(arg.actor), mDefIdx(arg.def_idx) {}

inline res::AIProgram* Query::getAIProg() const {
    return mActor->getParam()->getRes().mAIProgram;
}

bool Query::init(sead::Heap* heap) {
    if (mDefIdx != -1) {
        AIDefSet set;
        set.dynamic_params.num_params = 0;
        set.ai_tree_params.num_params = 0;

        auto* inst = AIClassDef::instance();
        const auto& query = getAIProg()->getQueries()[mDefIdx];
        inst->getDef(query.mClassName, &set, AIDefType::Query);

        if (mActor->getRootAi()->loadMapUnitParams(set.map_unit_params, heap) &&
            mActor->getRootAi()->loadAITreeParams(set.ai_tree_params, heap) &&
            (set.dynamic_params.num_params < 1 ||
             mParamPack.load(*mActor, set.dynamic_params, heap, AIDefInstParamKind::Dynamic))) {
            loadParams();
            return init_(heap);
        }
    }
    return false;
}

const char* Query::getName() const {
    if (mDefIdx == -1)
        return nullptr;

    return getAIProg()->getQueries()[mDefIdx].mClassName;
}

bool Query::getStaticParam(const f32** value, const sead::SafeString& param) const {
    const auto& def = getAIProg()->getQueries()[mDefIdx];
    return getAIProg()->getSInstParam(value, def, param);
}

bool Query::getDynamicParam(sead::SafeString* value, const sead::SafeString& param) const {
    if (mParamPack.getString(value, param))
        return true;
    *value = "";
    return false;
}

bool Query::getDynamicParam(s32** value, const sead::SafeString& param) const {
    static s32 sDefault{};
    return getDynamicParamImpl<s32>(value, param, AIDefParamType::Int, &sDefault);
}

bool Query::getDynamicParam(f32** value, const sead::SafeString& param) const {
    static f32 sDefault{};
    return getDynamicParamImpl<f32>(value, param, AIDefParamType::Float, &sDefault);
}

bool Query::getDynamicParam(bool** value, const sead::SafeString& param) const {
    static bool sDefault{};
    auto ret = static_cast<bool*>(mParamPack.getAITreeVariablePointer(param, AIDefParamType::Bool));
    *value = ret ? ret : &sDefault;
    return ret != nullptr;
}

bool Query::loadString(const evfl::ParamAccessor& accessor, const sead::SafeString& param) {
    ore::StringView value;
    if (!accessor.FindString(&value, param.cstr()))
        return false;

    return mParamPack.setString(value.data(), param);
}

bool Query::loadInt(const evfl::ParamAccessor& accessor, const sead::SafeString& param) {
    int value;
    if (!accessor.FindInt(&value, param.cstr()))
        return false;

    return mParamPack.setAITreeVariable(param, AIDefParamType::Int, value);
}

bool Query::loadFloat(const evfl::ParamAccessor& accessor, const sead::SafeString& param) {
    float value;
    if (!accessor.FindFloat(&value, param.cstr()))
        return false;

    return mParamPack.setAITreeVariable(param, AIDefParamType::Float, value);
}

bool Query::loadBool(const evfl::ParamAccessor& accessor, const sead::SafeString& param) {
    bool value;
    if (!accessor.FindBool(&value, param.cstr()))
        return false;

    return mParamPack.setAITreeVariable(param, AIDefParamType::Bool, value);
}

bool Query::getAITreeVariable(sead::SafeString** value, const sead::SafeString& param) const {
    return mActor->getRootAi()->getAITreeVariable(value, param);
}

bool Query::getAITreeVariable(void** value, const sead::SafeString& param) const {
    return mActor->getRootAi()->getAITreeVariable(value, param);
}

}  // namespace ksys::act::ai
