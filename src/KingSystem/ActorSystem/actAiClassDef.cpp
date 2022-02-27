#include "KingSystem/ActorSystem/actAiClassDef.h"
#include <algorithm>
#include <codec/seadHashCRC32.h>
#include <prim/seadContainerIterator.h>
#include <resource/seadResource.h>
#include "KingSystem/ActorSystem/actAiParam.h"
#include "KingSystem/Resource/resLoadRequest.h"
#include "KingSystem/Utils/Byaml/ByamlData.h"
#include "KingSystem/Utils/Byaml/ByamlHashIter.h"

namespace ksys {

const char* str_AIAfter = "AIAfter";
const char* str_ModelAfter = "ModelAfter";
const char* str_ChangeDeleteState = "ChangeDeleteState";
const char* str_StaticInstParams = "StaticInstParams";
const char* str_DynamicInstParams = "DynamicInstParams";
const char* str_MapUnitInstParams = "MapUnitInstParams";
const char* str_AITreeVariables = "AITreeVariables";
const char* str_AIs = "AIs";
const char* str_Actions = "Actions";
const char* str_Behaviors = "Behaviors";
const char* str_Querys = "Querys";

SEAD_SINGLETON_DISPOSER_IMPL(AIClassDef)

AIClassDef::~AIClassDef() {
    freeData();
}

void AIClassDef::init(const sead::SafeString& aidef_file_name, sead::Heap* heap) {
    res::LoadRequest req;
    req.mRequester = "AIClassDef";
    req._22 = true;
    sead::FixedSafeString<128> path;
    path.format("Actor/AIDef/%s", aidef_file_name.cstr());

    auto* res = sead::DynamicCast<sead::DirectResource>(mResHandle.load(path, &req));

    freeData();
    mData = new (heap) Data(res->getRawData());
    mData->load(heap);
}

// NON_MATCHING: not trying to match the heap sort. The rest should be equivalent
bool AIClassDef::Data::load(sead::Heap* heap) {
    root_iter.tryGetIterByKey(&iters[s32(AIDefType::AI)], str_AIs);
    root_iter.tryGetIterByKey(&iters[s32(AIDefType::Action)], str_Actions);
    root_iter.tryGetIterByKey(&iters[s32(AIDefType::Behavior)], str_Behaviors);
    root_iter.tryGetIterByKey(&iters[s32(AIDefType::Query)], str_Querys);

    inst_params_key_idx[0] = root_iter.getKeyIndex(str_StaticInstParams);
    inst_params_key_idx[1] = root_iter.getKeyIndex(str_DynamicInstParams);
    inst_params_key_idx[2] = root_iter.getKeyIndex(str_MapUnitInstParams);
    inst_params_key_idx[3] = root_iter.getKeyIndex(str_AITreeVariables);
    idx_Childs = root_iter.getKeyIndex("childs");

    static_cast<void>(heap->getFreeSize());

    for (s32 type = 0; type < NumAIDefTypes; ++type) {
        if (!iters[type].isValid())
            continue;

        const s32 count = iters[type].getSize();
        if (count <= 0)
            continue;

        auto& buffer = defs[type];
        buffer.allocBufferAssert(count, heap);

        for (s32 i = 0; i < count; ++i) {
            buffer[i].name_hash = 0;
            const char* name = nullptr;
            if (iters[type].tryGetIterAndKeyNameByIndex(&buffer[i].iter, &name, i))
                buffer[i].name_hash = sead::HashCRC32::calcStringHash(name);
        }

        auto ct = sead::stdIterator(buffer);
        std::sort(ct.begin(), ct.end(),
                  [](const Def& lhs, const Def& rhs) { return lhs.name_hash < rhs.name_hash; });
    }

    return true;
}

s32 AIClassDef::getRawDefIdx(const sead::SafeString& def_name, AIDefType type) const {
    const auto hash = sead::HashCRC32::calcStringHash(def_name);

    if (!mData)
        return -1;

    return getRawDefs(type).binarySearch(
        hash, +[](const Data::Def& def, const u32& hash) {
            if (def.name_hash < hash)
                return -1;
            if (def.name_hash > hash)
                return 1;
            return 0;
        });
}

void AIClassDef::getDef(const sead::SafeString& class_name, AIDefSet* set,
                        AIDefType class_type) const {
    set->num_children = 0;
    set->dynamic_params.num_params = 0;
    set->map_unit_params.num_params = 0;
    set->ai_tree_params.num_params = 0;

    const s32 idx = getRawDefIdx(class_name, class_type);
    if (idx < 0)
        return;

    const auto* data = mData;
    const auto& iter = getRawDefs(class_type)[idx].iter;

    if (class_type == AIDefType::AI) {
        al::ByamlHashIter hash_iter{iter.getRootNode()};
        al::ByamlData byaml_data;
        if (hash_iter.getDataByKey(&byaml_data, data->idx_Childs)) {
            al::ByamlIter it{iter.getData(), iter.getData() + byaml_data.getValue()};
            if (it.isValid()) {
                const s32 num_children = it.getSize();
                for (s32 i = 0; i < num_children; ++i) {
                    if (!it.tryGetStringByIndex(&set->children[set->num_children], i))
                        set->children[set->num_children] = nullptr;
                    ++set->num_children;
                }
            }
        }
    }

    doGetDef(&set->dynamic_params, iter, AIDefInstParamKind::Dynamic, class_type,
             data->inst_params_key_idx[s32(AIDefInstParamKind::Dynamic)]);
    doGetDef(&set->map_unit_params, iter, AIDefInstParamKind::MapUnit, class_type,
             data->inst_params_key_idx[s32(AIDefInstParamKind::MapUnit)]);
    doGetDef(&set->ai_tree_params, iter, AIDefInstParamKind::AITree, class_type,
             data->inst_params_key_idx[s32(AIDefInstParamKind::AITree)]);
}

// NON_MATCHING: CalcTiming ifs are reordered
void AIClassDef::doGetDef(AIDef* def, const al::ByamlIter& iter, AIDefInstParamKind param_kind,
                          AIDefType class_type, s32 key_idx) const {
    def->no_stop = false;
    def->trigger_action = false;
    def->dynamic_param_child = false;
    def->_24b = 0;
    def->num_params = 0;
    def->calc_timing = CalcTiming::AIAfter;

    if (param_kind == AIDefInstParamKind::Static) {
        switch (class_type) {
        case AIDefType::Action:
            iter.tryGetBoolByKey(&def->trigger_action, "TriggerAction");
            break;
        case AIDefType::AI:
            iter.tryGetBoolByKey(&def->trigger_action, "TriggerAction");
            iter.tryGetBoolByKey(&def->dynamic_param_child, "DynamicParamChild");
            break;
        case AIDefType::Behavior: {
            const char* timing_c;
            if (iter.tryGetStringByKey(&timing_c, "CalcTiming")) {
                const sead::SafeString timing = timing_c;
                if (timing == str_AIAfter)
                    def->calc_timing = CalcTiming::AIAfter;
                else if (timing == str_ModelAfter)
                    def->calc_timing = CalcTiming::ModelAfter;
                else if (timing == str_ChangeDeleteState)
                    def->calc_timing = CalcTiming::ChangeDeleteState;
            }
            iter.tryGetBoolByKey(&def->no_stop, "NoStop");
            break;
        }
        case AIDefType::Query:
            break;
        }
    }

    if (!iter.getRootNode())
        return;

    al::ByamlHashIter hash_iter{iter.getRootNode()};
    al::ByamlData data;
    if (!hash_iter.getDataByKey(&data, key_idx))
        return;

    al::ByamlIter params_iter{iter.getData(), iter.getData() + data.getValue()};
    if (!params_iter.isValid())
        return;

    const s32 num_params = params_iter.getSize();
    for (s32 i = 0; i < num_params; ++i) {
        al::ByamlIter it;
        if (!params_iter.tryGetIterByIndex(&it, i))
            continue;

        if (it.tryGetStringByKey(&def->param_names[def->num_params], "Name")) {
            const char* type_cstr = nullptr;
            if (it.tryGetStringByKey(&type_cstr, "Type")) {
                const sead::SafeString type = type_cstr;

                if (type == "Int") {
                    def->param_types[def->num_params] = AIDefParamType::Int;
                    def->param_values[def->num_params].i = 0;
                    if (paramKindHasValue(param_kind))
                        it.tryGetIntByKey(&def->param_values[def->num_params].i, "Value");

                } else if (type == "Float" || type == "Angle") {
                    def->param_types[def->num_params] = AIDefParamType::Float;
                    def->param_values[def->num_params].f = 0;
                    if (paramKindHasValue(param_kind))
                        it.tryGetFloatByKey(&def->param_values[def->num_params].f, "Value");

                } else if (type == "Bool") {
                    def->param_types[def->num_params] = AIDefParamType::Bool;
                    def->param_values[def->num_params].b = false;
                    if (paramKindHasValue(param_kind))
                        it.tryGetBoolByKey(&def->param_values[def->num_params].b, "Value");

                } else if (type == "Vec3" || type == "Angle3") {
                    def->param_types[def->num_params] = AIDefParamType::Vec3;
                    al::ByamlIter vec_iter;
                    def->param_values[def->num_params].vec3.x = 0;
                    def->param_values[def->num_params].vec3.y = 0;
                    def->param_values[def->num_params].vec3.z = 0;
                    if (paramKindHasValue(param_kind) && it.tryGetIterByKey(&vec_iter, "Value")) {
                        vec_iter.tryGetFloatByIndex(&def->param_values[def->num_params].vec3.x, 0);
                        vec_iter.tryGetFloatByIndex(&def->param_values[def->num_params].vec3.y, 1);
                        vec_iter.tryGetFloatByIndex(&def->param_values[def->num_params].vec3.z, 2);
                    }

                } else if (type == "String" || type == "AS") {
                    def->param_types[def->num_params] = AIDefParamType::String;
                    def->param_values[def->num_params].str = "";
                    if (paramKindHasValue(param_kind))
                        it.tryGetStringByKey(&def->param_values[def->num_params].str, "Value");

                } else if (type == "Tree") {
                    def->param_types[def->num_params] = AIDefParamType::Tree;
                } else if (type == "Actor") {
                    def->param_types[def->num_params] = AIDefParamType::BaseProcLink;
                } else if (type == "MesTransceiverId") {
                    def->param_types[def->num_params] = AIDefParamType::MesTransceiverId;
                } else if (type == "BaseProcHandle") {
                    def->param_types[def->num_params] = AIDefParamType::BaseProcHandle;
                } else if (type == "AITreeVariablePointer") {
                    def->param_types[def->num_params] = AIDefParamType::AITreeVariablePointer;
                } else if (type == "Rail") {
                    def->param_types[def->num_params] = AIDefParamType::Rail;
                } else {
                    def->param_types[def->num_params] = AIDefParamType::Other;
                }
            } else {
                def->param_types[def->num_params] = AIDefParamType::Other;
            }
        } else {
            def->param_names[def->num_params] = nullptr;
            def->param_types[def->num_params] = AIDefParamType::Other;
        }
        ++def->num_params;
    }
}

void AIClassDef::getDef(AIDef* def, const sead::SafeString& class_name,
                        AIDefInstParamKind param_kind, AIDefType class_type) const {
    def->num_params = 0;
    def->calc_timing = CalcTiming::AIAfter;
    def->no_stop = false;
    def->trigger_action = false;
    def->dynamic_param_child = false;
    def->_24b = 0;

    const s32 idx = getRawDefIdx(class_name, class_type);
    if (idx < 0)
        return;

    doGetDef(def, getRawDefs(class_type)[idx].iter, param_kind, class_type,
             mData->inst_params_key_idx[s32(param_kind)]);
}

bool AIClassDef::isSystemQuery(const sead::SafeString& query) const {
    bool ret = false;

    const s32 idx = getRawDefIdx(query, AIDefType::Query);
    if (idx < 0)
        return false;

    getRawDefs(AIDefType::Query)[idx].iter.tryGetBoolByKey(&ret, "SystemQuery");
    return ret;
}

}  // namespace ksys
