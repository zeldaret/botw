#pragma once

#include <basis/seadTypes.h>
#include <container/seadBuffer.h>
#include <container/seadObjArray.h>
#include <framework/seadTaskParameter.h>
#include <prim/seadSafeString.h>
#include "KingSystem/Utils/Types.h"

namespace ksys::frm {

struct RootTaskParam : public sead::TaskParameter {
    SEAD_RTTI_OVERRIDE(RootTaskParam, sead::TaskParameter)
public:
    using ThreadIdArray = sead::FixedObjArray<u32, 4>;

    RootTaskParam() = default;

    bool _8 = true;
    bool _9 = false;
    bool _a = true;
    void* _10 = nullptr;
    void* _18 = nullptr;
    sead::SafeString app_name;
    sead::SafeString _30;
    sead::FixedObjArray<u32, 4> thread_ids;
    sead::Buffer<const char*> res_extensions1;
    sead::Buffer<const char*> res_extensions2;
    u8 _c0 = 0;
    u8 _c1 = 0;
    u8 _c2 = 0;
    s32 _c4 = -1;
    u32 constant_a = 0;
    u32 constant_b = 0;
    u32 heap_size = 0;
    u32 constant_c = 0;
    u32 constant_d = 0;
    u32 _dc = 0;
};
KSYS_CHECK_SIZE_NX150(RootTaskParam::ThreadIdArray, 0x60);
KSYS_CHECK_SIZE_NX150(RootTaskParam, 0xe0);

}  // namespace ksys::frm
