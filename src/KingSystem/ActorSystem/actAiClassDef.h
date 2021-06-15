#pragma once

#include <basis/seadTypes.h>
#include <container/seadBuffer.h>
#include <container/seadSafeArray.h>
#include <heap/seadDisposer.h>
#include <math/seadVector.h>
#include <prim/seadSafeString.h>
#include <prim/seadSizedEnum.h>
#include "KingSystem/Resource/resHandle.h"
#include "KingSystem/Utils/Byaml/Byaml.h"
#include "KingSystem/Utils/SafeDelete.h"
#include "KingSystem/Utils/Types.h"

namespace ksys {

namespace act {
class BaseProcLink;
}

enum class AIDefType {
    AI = 0,
    Action = 1,
    Behavior = 2,
    Query = 3,
};

constexpr s32 NumAIDefTypes = 4;

enum class AIDefInstParamKind {
    Static = 0,
    Dynamic = 1,
    MapUnit = 2,
    AITree = 3,
};

constexpr bool paramKindHasValue(AIDefInstParamKind kind) {
    return kind == AIDefInstParamKind::MapUnit || kind == AIDefInstParamKind::AITree;
}

constexpr s32 NumAIDefInstParamKinds = 4;

enum class AIDefParamType;

enum class CalcTiming {
    AIAfter = 0,
    ModelAfter = 1,
    ChangeDeleteState = 2,
};

struct AIDef {
    union Value {
        Value() {}
        std::array<u8, 16> raw;
        const char* str;
        s32 i;
        f32 f;
        sead::Vector3f vec3;
        bool b;
        void* tree;
        void* variable_ptr;
        u32 u;
        act::BaseProcLink* proc_link;
    };

    static constexpr size_t NumParametersMax = 64;

    const char* param_names[NumParametersMax];
    sead::SizedEnum<AIDefParamType, u8> param_types[NumParametersMax];
    s32 num_params;
    CalcTiming calc_timing;
    bool no_stop;
    bool trigger_action;
    bool dynamic_param_child;
    u8 _24b;
    Value param_values[NumParametersMax];
};
KSYS_CHECK_SIZE_NX150(AIDef, 0x650);

struct AIDefSet {
    static constexpr size_t NumChildrenMax = 256;

    const char* children[NumChildrenMax];
    s32 num_children;
    AIDef dynamic_params;
    AIDef map_unit_params;
    AIDef ai_tree_params;
};
KSYS_CHECK_SIZE_NX150(AIDefSet, 0x1af8);

class AIClassDef {
    SEAD_SINGLETON_DISPOSER(AIClassDef)
    AIClassDef() = default;
    ~AIClassDef();

public:
    void init(const sead::SafeString& aidef_file_name, sead::Heap* heap);

    void getDef(const sead::SafeString& class_name, AIDefSet* set, AIDefType class_type) const;
    void getDef(AIDef* def, const sead::SafeString& class_name, AIDefInstParamKind param_kind,
                AIDefType class_type) const;

    bool isSystemQuery(const sead::SafeString& query) const;

private:
    struct Data {
        struct Def {
            u32 name_hash;
            al::ByamlIter iter;
        };

        explicit Data(const u8* root) : root_iter(root) {}
        bool load(sead::Heap* heap);

        sead::SafeArray<al::ByamlIter, NumAIDefTypes> iters;
        sead::SafeArray<sead::Buffer<Def>, NumAIDefTypes> defs;
        sead::SafeArray<s32, NumAIDefInstParamKinds> inst_params_key_idx;
        s32 idx_Childs = -1;
        al::ByamlIter root_iter;
    };
    KSYS_CHECK_SIZE_NX150(Data, 0xa8);

    inline void freeData() {
        if (!mData)
            return;

        for (auto& defs : mData->defs)
            defs.freeBuffer();

        util::safeDelete(mData);
    }

    s32 getRawDefIdx(const sead::SafeString& def_name, AIDefType type) const;
    const sead::Buffer<Data::Def>& getRawDefs(AIDefType type) const {
        return mData->defs[s32(type)];
    }

    void doGetDef(AIDef* def, const al::ByamlIter& iter, AIDefInstParamKind param_kind,
                  AIDefType class_type, s32 key_idx) const;

    Data* mData = nullptr;
    res::Handle mResHandle;
};
KSYS_CHECK_SIZE_NX150(AIClassDef, 0x78);

}  // namespace ksys
