#pragma once

#include <agl/Utils/aglParameter.h>
#include <basis/seadTypes.h>
#include <container/seadSafeArray.h>
#include <math/seadVector.h>
#include <prim/seadSafeString.h>
#include <prim/seadSizedEnum.h>

#include "KingSystem/ActorSystem/actAiClassDef.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/Utils/Thread/MessageTransceiverId.h"
#include "KingSystem/Utils/Types.h"

namespace ksys {

class Rail;

namespace act {
class Actor;
class BaseProc;
}  // namespace act

namespace act::ai {

struct InlineParamPack;

struct ParamNameType {
    const char* name;
    AIDefParamType type;
    s32 use_count;
};
KSYS_CHECK_SIZE_NX150(ParamNameType, 0x10);

struct ParamNameTypePairs {
    void addPair(AIDefParamType type, const sead::SafeString& name, bool update_use_count);

    sead::SafeArray<ParamNameType, 32> pairs{};
    s32 count = 0;
};
KSYS_CHECK_SIZE_NX150(ParamNameTypePairs, 0x208);

struct Param {
    Param* next;
    u32 hash;
    const char* name;
    void* data;
    sead::SizedEnum<AIDefParamType, u16> type;
    bool used;
    u8 _23;
};
KSYS_CHECK_SIZE_NX150(Param, 0x28);

class ParamPack {
public:
    ParamPack();
    ~ParamPack();

    template <typename T>
    T* getVariable(const sead::SafeString& key, AIDefParamType type, bool a4 = true) const {
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

    template <typename T>
    void setVariable(const sead::SafeString& key, AIDefParamType type, const T& val) const {
        T* variable = getVariable<T>(key, type, true);
        if (variable)
            *variable = val;
    }

    bool load(const Actor& actor, const ParamNameTypePairs& pairs, s32 count, sead::Heap* heap);
    void* getAITreeVariablePointer(const sead::SafeString& key, AIDefParamType type,
                                   bool x = false) const;
    void copy(InlineParamPack* dest, bool x) const;
    void getPairs(ParamNameTypePairs* pairs, bool update_use_count) const;

    template <typename T, AIDefParamType Type>
    bool getPtrGeneric(T** value, const sead::SafeString& key) const {
        auto* ptr = static_cast<T*>(getAITreeVariablePointer(key, Type));
        *value = ptr;
        return ptr != nullptr;
    }

    // TODO: rename this -- why does this exist?
    template <typename T, AIDefParamType Type>
    bool getPtrGeneric2(T** value, const sead::SafeString& key) const {
        auto* ptr = static_cast<T*>(getAITreeVariablePointer(key, Type));
        *value = ptr;
        return ptr != nullptr;
    }

    bool getString(sead::SafeString* value, const sead::SafeString& key) const;
    bool setString(const sead::SafeString& value, const sead::SafeString& key) const;

    bool getActor(BaseProc* proc, const sead::SafeString& key) const;
    bool setActor(const BaseProcLink& link, const sead::SafeString& key) const;

    bool load(const Actor& actor, const AIDef& def, sead::Heap* heap, AIDefInstParamKind kind);

private:
    Param* mParams = nullptr;
};

struct InlineParam {
    union {
        bool b;
        int i;
        u32 u;
        float f;
        const char* cstr;
        void* ptr;
    };
    BaseProcLink baseProcLink;
    sead::Vector3f vec3;
    MesTransceiverId mesTransceiverId;
    AIDefParamType type;
    const char* key;
};
KSYS_CHECK_SIZE_NX150(InlineParam, 0x50);

struct InlineParamPack {
    InlineParamPack() = default;

    InlineParam& getParam(s32 idx) {
        if (idx < 0) {
            idx = count;
            if (count > NumParamsMax - 1)
                idx = 0;
            else
                count = idx + 1;
        }
        return params[idx];
    }

    s32 findIndex(const sead::SafeString& name, AIDefParamType type) const {
        for (s32 i = 0; i < count; ++i) {
            if (params[i].type == type && name == params[i].key)
                return i;
        }
        return -1;
    }

    void addString(const char* value, const sead::SafeString& key, s32 idx);
    void addString(const sead::SafeString& value, const sead::SafeString& key, s32 idx) {
        addString(value.cstr(), key, idx);
    }
    void addInt(s32 value, const sead::SafeString& key, s32 idx);
    void addFloat(f32 value, const sead::SafeString& key, s32 idx);
    void addVec3(const sead::Vector3f& value, const sead::SafeString& key, s32 idx);
    void addBool(bool value, const sead::SafeString& key, s32 idx);
    void addUInt(u32 value, const sead::SafeString& key, s32 idx);
    void addActor(const BaseProcLink& value, const sead::SafeString& key, s32 idx);
    void addMesTransceiverId(const MesTransceiverId& value, const sead::SafeString& key, s32 idx);
    void addPointer(void* value, const sead::SafeString& key, AIDefParamType type, s32 idx);
    void acquireActor(BaseProc* proc, const sead::SafeString& key, s32 idx);
    void copyToParamPack(ParamPack& pack) const;

    static constexpr s32 NumParamsMax = 32;
    InlineParam params[NumParamsMax];
    int count = 0;
};
KSYS_CHECK_SIZE_NX150(InlineParamPack, 0xA08);

}  // namespace act::ai

}  // namespace ksys
