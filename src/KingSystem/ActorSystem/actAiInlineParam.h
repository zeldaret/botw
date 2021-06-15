#pragma once

#include <basis/seadTypes.h>
#include <math/seadVector.h>
#include <prim/seadSafeString.h>

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
