#pragma once

#include <heap/seadDisposer.h>
#include <prim/seadSafeString.h>
#include <prim/seadSizedEnum.h>
#include "KingSystem/Utils/Types.h"

namespace ksys {

enum class AIDefType {
    AI = 0,
    Action = 1,
    Behavior = 2,
    Query = 3,
};

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

// FIXME
class AIClassDef {
    SEAD_SINGLETON_DISPOSER(AIClassDef)
public:
    void init(const sead::SafeString& aidef_file_name, sead::Heap* heap);

    void getDef(AIDef* def, const sead::SafeString& class_name, AIDefInstParamKind param_kind,
                AIDefType class_type);

private:
    class Data;

    Data* mData;
    // res::Handle mResHandle;
};
// KSYS_CHECK_SIZE_NX150(AIClassDef, 0x78);

}  // namespace ksys
