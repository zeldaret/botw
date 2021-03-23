#include "KingSystem/ActorSystem/actAiParam.h"
#include <agl/Utils/aglParameter.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiClassDef.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace ksys::act {
class BaseProcHandle;
}

namespace ksys::act::ai {

ParamPack::ParamPack() = default;

ParamPack::~ParamPack() {
    auto* param = mParams;
    while (param) {
        if (param->data) {
            switch (param->type) {
            case AIDefParamType::String:
                delete static_cast<sead::SafeString*>(param->data);
                break;
            case AIDefParamType::Int:
                delete static_cast<int*>(param->data);
                break;
            case AIDefParamType::Float:
                delete static_cast<float*>(param->data);
                break;
            case AIDefParamType::Vec3:
                delete static_cast<sead::Vector3f*>(param->data);
                break;
            case AIDefParamType::Bool:
                delete static_cast<bool*>(param->data);
                break;
            case AIDefParamType::AITreeVariablePointer:
                delete static_cast<void**>(param->data);
                break;
            case AIDefParamType::UInt:
                delete static_cast<u32*>(param->data);
                break;
            case AIDefParamType::MesTransceiverId:
                delete static_cast<MesTransceiverId*>(param->data);
                break;
            case AIDefParamType::BaseProcHandle:
                delete static_cast<BaseProcHandle**>(param->data);
                break;
            case AIDefParamType::Rail:
                delete static_cast<Rail**>(param->data);
                break;
            case AIDefParamType::BaseProcLink:
                delete static_cast<BaseProcLink*>(param->data);
                break;
            default:
                break;
            }
        }
        param = mParams->next;
        if (mParams)
            delete mParams;
        mParams = param;
    }
}

template <typename T>
T* ParamPack::getVariable(const sead::SafeString& key, AIDefParamType type, bool a4) const {
    const u32 hash = agl::utl::ParameterBase::calcHash(key);
    auto* param = mParams;
    if (!param)
        return nullptr;
    while (param->hash != hash || param->type != type) {
        param = param->next;
        if (!param)
            return nullptr;
    }
    if (a4)
        param->used = true;
    return static_cast<T*>(param->data);
}

bool ParamPack::load(const Actor& actor, const ParamNameTypePairs& pairs, s32 count,
                     sead::Heap* heap) {
    AIDef def;
    def.no_stop = false;
    def.trigger_action = false;
    def.dynamic_param_child = false;
    def._24b = false;
    def.num_params = 0;
    def.calc_timing = CalcTiming::AIAfter;

    for (s32 i = 0; i < pairs.count; ++i) {
        const auto& pair = pairs.pairs[i];
        if (pair.use_count < count) {
            def.param_names[def.num_params] = pair.name;
            def.param_types[def.num_params] = pair.type;
            def.param_values[def.num_params].vec3 = {0, 0, 0};
            def.param_values[def.num_params].variable_ptr = nullptr;
            ++def.num_params;
        }
    }

    return load(actor, def, heap, AIDefInstParamKind::Dynamic);
}

void* ParamPack::getAITreeVariablePointer(const sead::SafeString& key, AIDefParamType type,
                                          bool x) const {
    return getVariable<void>(key, type, x);
}

void ParamPack::copy(InlineParamPack* dest, bool x) const {
    for (auto* param = mParams; param; param = param->next) {
        if (!param->data || !param->used)
            continue;

        const s32 dest_idx = dest->findIndex(param->name, param->type);

        switch (param->type) {
        case AIDefParamType::String: {
            dest->addString(*static_cast<sead::SafeString*>(param->data), param->name, dest_idx);
            break;
        }
        case AIDefParamType::Int:
            dest->addInt(*static_cast<s32*>(param->data), param->name, dest_idx);
            break;
        case AIDefParamType::Float:
            dest->addFloat(*static_cast<f32*>(param->data), param->name, dest_idx);
            break;
        case AIDefParamType::Vec3:
            dest->addVec3(*static_cast<sead::Vector3f*>(param->data), param->name, dest_idx);
            break;
        case AIDefParamType::Bool:
            dest->addBool(*static_cast<bool*>(param->data), param->name, dest_idx);
            break;
        case AIDefParamType::UInt:
            dest->addUInt(*static_cast<u32*>(param->data), param->name, dest_idx);
            break;
        case AIDefParamType::BaseProcLink:
            dest->addActor(*static_cast<BaseProcLink*>(param->data), param->name, dest_idx);
            break;
        case AIDefParamType::MesTransceiverId:
            if (!x) {
                dest->addMesTransceiverId(*static_cast<MesTransceiverId*>(param->data), param->name,
                                          dest_idx);
                break;
            }
            [[fallthrough]];
        case AIDefParamType::BaseProcHandle:
            if (!x) {
                dest->addPointer(*static_cast<BaseProcHandle**>(param->data), param->name,
                                 AIDefParamType::BaseProcHandle, dest_idx);
                break;
            }
            [[fallthrough]];
        case AIDefParamType::Rail:
            dest->addPointer(*static_cast<Rail**>(param->data), param->name, AIDefParamType::Rail,
                             dest_idx);
            break;
        case AIDefParamType::Tree:
        case AIDefParamType::AITreeVariablePointer:
        case AIDefParamType::Other:
            break;
        }
    }
}

void InlineParamPack::addString(const char* value, const sead::SafeString& key, s32 idx) {
    auto& param = getParam(idx);
    param.key = key.cstr();
    param.cstr = value;
    param.type = AIDefParamType::String;
}

void InlineParamPack::addInt(s32 value, const sead::SafeString& key, s32 idx) {
    auto& param = getParam(idx);
    param.key = key.cstr();
    param.i = value;
    param.type = AIDefParamType::Int;
}

void InlineParamPack::addFloat(f32 value, const sead::SafeString& key, s32 idx) {
    auto& param = getParam(idx);
    param.key = key.cstr();
    param.f = value;
    param.type = AIDefParamType::Float;
}

void InlineParamPack::addVec3(const sead::Vector3f& value, const sead::SafeString& key, s32 idx) {
    auto& param = getParam(idx);
    param.key = key.cstr();
    param.vec3 = value;
    param.type = AIDefParamType::Vec3;
}

void InlineParamPack::addBool(bool value, const sead::SafeString& key, s32 idx) {
    auto& param = getParam(idx);
    param.key = key.cstr();
    param.b = value;
    param.type = AIDefParamType::Bool;
}

void InlineParamPack::addUInt(u32 value, const sead::SafeString& key, s32 idx) {
    auto& param = getParam(idx);
    param.key = key.cstr();
    param.u = value;
    param.type = AIDefParamType::UInt;
}

void InlineParamPack::addActor(const BaseProcLink& value, const sead::SafeString& key, s32 idx) {
    auto& param = getParam(idx);
    param.key = key.cstr();
    param.baseProcLink = value;
    param.type = AIDefParamType::BaseProcLink;
}

void InlineParamPack::addMesTransceiverId(const MesTransceiverId& value,
                                          const sead::SafeString& key, s32 idx) {
    auto& param = getParam(idx);
    param.key = key.cstr();
    param.mesTransceiverId = value;
    param.type = AIDefParamType::MesTransceiverId;
}

void ParamPack::getPairs(ParamNameTypePairs* pairs, bool update_use_count) const {
    for (auto* param = mParams; param; param = param->next) {
        if (param->data)
            pairs->addPair(param->type, param->name, update_use_count);
    }
}

void ParamNameTypePairs::addPair(AIDefParamType type, const sead::SafeString& name,
                                 bool update_use_count) {
    for (s32 i = 0; i < count; ++i) {
        auto& pair = pairs[i];
        if (pair.type == type && name == pair.name) {
            if (update_use_count)
                ++pair.use_count;
            return;
        }
    }

    if (count >= pairs.size())
        return;

    auto& pair = pairs[count];
    pair.type = type;
    pair.name = name.cstr();
    pair.use_count = 1;
    ++count;
}

bool ParamPack::getString(sead::SafeString* value, const sead::SafeString& key) const {
    auto* str = getVariable<sead::SafeString>(key, AIDefParamType::String, false);
    if (!str)
        return false;
    *value = str->cstr();
    return true;
}

bool ParamPack::setString(const sead::SafeString& value, const sead::SafeString& key) const {
    auto* str = getVariable<sead::BufferedSafeString>(key, AIDefParamType::String);
    if (!str)
        return false;
    str->copy(value);
    return true;
}

bool ParamPack::getActor(BaseProc* proc, const sead::SafeString& key) const {
    auto* link = getVariable<BaseProcLink>(key, AIDefParamType::BaseProcLink);
    if (!link)
        return false;
    link->acquire(proc, false);
    return true;
}

bool ParamPack::setActor(const BaseProcLink& new_link, const sead::SafeString& key) const {
    auto* link = getVariable<BaseProcLink>(key, AIDefParamType::BaseProcLink);
    if (!link)
        return false;
    *link = new_link;
    return true;
}

bool ParamPack::load(const Actor& actor, const AIDef& def, sead::Heap* heap,
                     AIDefInstParamKind kind) {
    bool load_map_unit_params = false;
    bool used = false;

    if (kind == AIDefInstParamKind::AITree) {
        load_map_unit_params = false;
        used = true;
    } else if (kind == AIDefInstParamKind::MapUnit) {
        load_map_unit_params = def._24b == 0;
        used = true;
    }

    const auto& iter = actor.getMapObjIter();
    for (s32 i = 0; i < def.num_params; ++i) {
        const auto hash = agl::utl::ParameterBase::calcHash(def.param_names[i]);

        bool found = false;
        for (auto* entry = mParams; entry; entry = entry->next) {
            if (entry->hash == hash) {
                found = true;
                break;
            }
        }
        if (found)
            continue;

        // Otherwise, allocate a new entry.
        auto* entry = new (heap) Param;
        if (!entry)
            return false;
        entry->data = nullptr;
        entry->next = mParams;
        mParams = entry;
        switch (def.param_types[i]) {
        case AIDefParamType::String: {
            const char* value = def.param_values[i].str ? def.param_values[i].str : "";

            if (load_map_unit_params)
                iter.tryGetParamStringByKey(&value, def.param_names[i]);

            entry->data = new (heap) sead::FixedSafeString<80>(value);
            break;
        }
        case AIDefParamType::Int: {
            int value = def.param_values[i].i;
            if (load_map_unit_params)
                iter.tryGetParamIntByKey(&value, def.param_names[i]);
            entry->data = new (heap) int(value);
            break;
        }
        case AIDefParamType::Float: {
            float value = def.param_values[i].f;
            if (load_map_unit_params)
                iter.tryGetParamFloatByKey(&value, def.param_names[i]);
            entry->data = new (heap) float(value);
            break;
        }
        case AIDefParamType::Vec3: {
            const auto& src = def.param_values[i].vec3;
            sead::Vector3f value{src.x, src.y, src.z};
            if (load_map_unit_params)
                iter.tryGetFloatArrayByKey(value.e.data(), def.param_names[i]);
            entry->data = new (heap) sead::Vector3f(value);
            break;
        }
        case AIDefParamType::Bool: {
            bool value = def.param_values[i].b;
            if (load_map_unit_params)
                iter.tryGetParamBoolByKey(&value, def.param_names[i]);
            entry->data = new (heap) bool(value);
            break;
        }
        case AIDefParamType::AITreeVariablePointer:
            entry->data = new (heap) void*();
            break;
        case AIDefParamType::UInt: {
            u32 value = def.param_values[i].u;
            if (load_map_unit_params)
                iter.tryGetParamUIntByKey(&value, def.param_names[i]);
            entry->data = new (heap) u32(value);
            break;
        }
        case AIDefParamType::BaseProcLink:
            if (kind == AIDefInstParamKind::Dynamic)
                entry->data = new (heap) BaseProcLink();
            break;
        case AIDefParamType::MesTransceiverId:
            if (kind == AIDefInstParamKind::Dynamic)
                entry->data = new (heap) MesTransceiverId();
            break;
        case AIDefParamType::BaseProcHandle:
            if (kind == AIDefInstParamKind::Dynamic)
                entry->data = new (heap) BaseProcHandle*();
            break;
        case AIDefParamType::Rail:
            if (kind == AIDefInstParamKind::Dynamic)
                entry->data = new (heap) Rail*();
            break;
        case AIDefParamType::Tree:
        case AIDefParamType::Other:
            break;
        }

        if (!entry->data)
            return false;

        entry->hash = hash;
        entry->name = def.param_names[i];
        entry->used = used;
        entry->_23 = def._24b;
        entry->type = def.param_types[i];
    }

    return true;
}

void InlineParamPack::addPointer(void* value, const sead::SafeString& key, AIDefParamType type,
                                 s32 idx) {
    auto& param = getParam(idx);
    param.key = key.cstr();
    param.ptr = value;
    param.type = type;
}

void InlineParamPack::acquireActor(BaseProc* proc, const sead::SafeString& key, s32 idx) {
    auto& param = getParam(idx);
    param.key = key.cstr();
    param.baseProcLink.acquire(proc, false);
    param.type = AIDefParamType::BaseProcLink;
}

void InlineParamPack::copyToParamPack(ParamPack& pack) const {
    const u32 n = count >= 0x1F ? 0x1F : count;
    const InlineParam* param = params;
    for (u32 i = 0; i < n; ++i, ++param) {
        switch (param->type) {
        case AIDefParamType::String: {
            const sead::SafeString src = param->cstr;
            const sead::SafeString key = param->key;
            auto* dst = pack.getVariable<sead::BufferedSafeString>(key, AIDefParamType::String);
            if (dst)
                dst->copy(src);
            break;
        }
        case AIDefParamType::Int:
            pack.setVariable(param->key, AIDefParamType::Int, param->i);
            break;
        case AIDefParamType::Float:
            pack.setVariable(param->key, AIDefParamType::Float, param->f);
            break;
        case AIDefParamType::Vec3:
            if (auto* dst = pack.getVariable<sead::Vector3f>(param->key, AIDefParamType::Vec3)) {
                dst->x = param->vec3.x;
                dst->y = param->vec3.y;
                dst->z = param->vec3.z;
            }
            break;
        case AIDefParamType::Bool:
            pack.setVariable(param->key, AIDefParamType::Bool, param->b);
            break;
        case AIDefParamType::UInt:
            pack.setVariable(param->key, AIDefParamType::UInt, param->u);
            break;
        case AIDefParamType::BaseProcLink:
            pack.setVariable(param->key, AIDefParamType::BaseProcLink, param->baseProcLink);
            break;
        case AIDefParamType::MesTransceiverId:
            pack.setVariable(param->key, AIDefParamType::MesTransceiverId, param->mesTransceiverId);
            break;
        case AIDefParamType::BaseProcHandle: {
            auto* baseProcHandle = static_cast<BaseProcHandle*>(param->ptr);
            pack.setVariable(param->key, AIDefParamType::BaseProcHandle, baseProcHandle);
            break;
        }
        case AIDefParamType::Rail: {
            auto* rail = static_cast<Rail*>(param->ptr);
            pack.setVariable(param->key, AIDefParamType::Rail, rail);
            break;
        }
        default:
            break;
        }
    }
}

}  // namespace ksys::act::ai
