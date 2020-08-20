#pragma once

#include <agl/Utils/aglParameter.h>
#include <basis/seadTypes.h>
#include <math/seadVector.h>
#include <prim/seadSafeString.h>

#include "KingSystem/ActorSystem/actBaseProc.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/MessageSystem/mesTransceiver.h"
#include "KingSystem/Utils/Types.h"

namespace ksys {

class Rail;

namespace act::ai {

struct Param {
    enum class Type {
        String = 0,
        Int = 1,
        Float = 2,
        Vec3 = 3,
        Bool = 4,
        Tree = 5,
        AITreeVariablePointer = 6,
        UInt = 7,
        BaseProcLink = 8,
        MesTransceiverId = 9,
        BaseProcHandle = 10,
        Rail = 11,
        Other = 12,
    };

    Param* next;
    u32 hash;
    const char* name;
    void* data;
    u16 type;
    bool used;
    u8 _23;
};
KSYS_CHECK_SIZE_NX150(Param, 0x28);

class ParamPack {
public:
    ParamPack();
    ~ParamPack();

    template <typename T>
    T* getVariable(const sead::SafeString& key, Param::Type type, bool a4 = true) const {
        const u32 hash = agl::utl::ParameterBase::calcHash(key);
        auto* param = mParams;
        if (!param)
            return nullptr;
        while (param->hash != hash || Param::Type(param->type) != type) {
            param = param->next;
            if (!param)
                return nullptr;
        }
        if (a4)
            param->used = true;
        return static_cast<T*>(param->data);
    }

    template <typename T>
    void setVariable(const sead::SafeString& key, Param::Type type, const T& val) const {
        T* variable = getVariable<T>(key, type, true);
        if (variable)
            *variable = val;
    }

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
    Param::Type type;
    const char* key;
};
KSYS_CHECK_SIZE_NX150(InlineParam, 0x50);

struct InlineParamPack {
    void copyToParamPack(ParamPack& pack) const;

    InlineParam params[32];
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
