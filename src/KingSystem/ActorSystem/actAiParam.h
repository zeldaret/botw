#pragma once

#include <agl/Utils/aglParameter.h>
#include <basis/seadTypes.h>
#include <math/seadVector.h>
#include <prim/seadSafeString.h>
#include <prim/seadSizedEnum.h>

#include "KingSystem/ActorSystem/actAiClassDef.h"
#include "KingSystem/ActorSystem/actBaseProc.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/MessageSystem/mesTransceiver.h"
#include "KingSystem/Utils/Types.h"

namespace ksys {

class Rail;

namespace act::ai {

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

    void* getAITreeVariablePointer(const sead::SafeString& key, AIDefParamType type, bool x) const;

    bool getString(sead::SafeString* value, const sead::SafeString& key) const;
    bool setString(const sead::SafeString& value, const sead::SafeString& key) const;

    bool getActor(BaseProc* proc, const sead::SafeString& key) const;
    bool setActor(const BaseProcLink& link, const sead::SafeString& key) const;

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
    mes::TransceiverId mesTransceiverId;
    AIDefParamType type;
    const char* key;
};
KSYS_CHECK_SIZE_NX150(InlineParam, 0x50);

struct InlineParamPack {
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

    void addInt(s32 value, const sead::SafeString& key, s32 idx);
    void addFloat(f32 value, const sead::SafeString& key, s32 idx);
    void addVec3(const sead::Vector3f& value, const sead::SafeString& key, s32 idx);
    void addBool(bool value, const sead::SafeString& key, s32 idx);
    void addActor(const BaseProcLink& value, const sead::SafeString& key, s32 idx);
    void addMesTransceiverId(const mes::TransceiverId& value, const sead::SafeString& key, s32 idx);
    void addPointer(void* value, const sead::SafeString& key, AIDefParamType type, s32 idx);
    void acquireActor(BaseProc* proc, const sead::SafeString& key, s32 idx);
    void copyToParamPack(ParamPack& pack) const;

    static constexpr s32 NumParamsMax = 32;
    InlineParam params[NumParamsMax];
    int count;
};
KSYS_CHECK_SIZE_NX150(InlineParamPack, 0xA08);

template <typename T>
class ParamRef {
public:
    const T& value() const { return *mValue; }
    void setValuePtr(const T* ptr) { mValue = ptr; }

private:
    const T* mValue = nullptr;
};
}  // namespace act::ai

}  // namespace ksys
