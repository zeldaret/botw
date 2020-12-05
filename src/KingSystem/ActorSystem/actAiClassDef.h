#pragma once

#include <container/seadBuffer.h>
#include <container/seadSafeArray.h>
#include <heap/seadDisposer.h>
#include <prim/seadSafeString.h>
#include <prim/seadSizedEnum.h>
#include "KingSystem/Resource/resHandle.h"
#include "KingSystem/Utils/Byaml/Byaml.h"
#include "KingSystem/Utils/SafeDelete.h"
#include "KingSystem/Utils/Types.h"

namespace ksys {

enum class AIDefType {
    AI = 0,
    Action = 1,
    Behavior = 2,
    Query = 3,
};

static constexpr s32 NumAIDefTypes = 4;

enum class AIDefInstParamKind {
    Static = 0,
    Dynamic = 1,
    MapUnit = 2,
    AITree = 3,
};

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

struct AIDef {
    union Value {
        u8 raw[16];
    };

    static constexpr size_t NumParametersMax = 64;

    const char* param_names[NumParametersMax];
    sead::SizedEnum<AIDefParamType, u8> param_types[NumParametersMax];
    s32 num_params;
    u32 calc_timing;
    bool no_stop;
    bool trigger_action;
    bool dynamic_param_child;
    u8 _24b;
    Value param_values[NumParametersMax];
};
KSYS_CHECK_SIZE_NX150(AIDef, 0x650);

class AIClassDef {
    SEAD_SINGLETON_DISPOSER(AIClassDef)
    AIClassDef() = default;
    ~AIClassDef();

public:
    void init(const sead::SafeString& aidef_file_name, sead::Heap* heap);

    void getDef(AIDef* def, const sead::SafeString& class_name, AIDefInstParamKind param_kind,
                AIDefType class_type);

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
        s32 idx_StaticInstParams;
        s32 idx_DynamicInstParams;
        s32 idx_MapUnitInstParams;
        s32 idx_AITreeVariables;
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

    Data* mData = nullptr;
    res::Handle mResHandle;
};
KSYS_CHECK_SIZE_NX150(AIClassDef, 0x78);

}  // namespace ksys
