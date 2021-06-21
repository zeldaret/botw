#pragma once

#include <basis/seadTypes.h>
#include <container/seadSafeArray.h>
#include <prim/seadSafeString.h>
#include <prim/seadSizedEnum.h>

#include "KingSystem/Utils/Types.h"

namespace ksys {

namespace act {
class Actor;
class BaseProc;
class BaseProcLink;
}  // namespace act

struct AIDef;
class Rail;
enum class AIDefInstParamKind;

enum class AIDefParamType {
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
    T* getVariable(const sead::SafeString& key, AIDefParamType type, bool a4 = true) const;

    template <typename T>
    bool setVariable(const sead::SafeString& key, AIDefParamType type, const T& val) const {
        T* variable = getVariable<T>(key, type, true);
        if (!variable)
            return false;
        *variable = val;
        return true;
    }

    template <typename T>
    bool setAITreeVariable(const sead::SafeString& key, AIDefParamType type, const T& val) const {
        auto* variable = static_cast<T*>(getAITreeVariablePointer(key, type, true));
        if (!variable)
            return false;
        *variable = val;
        return true;
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

}  // namespace act::ai

}  // namespace ksys
