#pragma once

#include <container/seadObjArray.h>
#include <prim/seadRuntimeTypeInfo.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiClassDef.h"

namespace uking {
class AirOctaDataMgr {
    SEAD_RTTI_BASE(AirOctaDataMgr)
public:
    ksys::act::BaseProcLink& getProc() { return mBaseProcLink; }
    void changeOctasYheightMaybe();

    struct MessageData {
        u32 unk_00;
        u64 unk_08;
    };

    /* 0x08 */ ksys::act::BaseProcLink mBaseProcLink;
    /* 0x18 */ ksys::act::BaseProcLink mBaseProcLink2;
    /* 0x28 */ void* unk_28{};
    /* 0x30 */ u32 unk_30{};
    /* 0x34 */ sead::Vector3f unk_34{sead::Vector3f::zero};
    /* 0x40 */ void* unk_40{};
    /* 0x48 */ u32 unk_48{};
    /* 0x4C */ sead::Vector3f unk_4C{sead::Vector3f::zero};
    /* 0x58 */ sead::FixedObjArray<MessageData, 4> obj_arr;
    /* 0xD8 */ u16 unk_D8{};
    /* 0xDA */ bool unk_DA{};
    /* 0xDC */ u32 unk_DC;
    /* 0xE0 */ sead::Vector3f vec_E0{sead::Vector3f::zero};
    /* 0xEC */ sead::Vector3f vec_EC{sead::Vector3f::zero};
    /* 0xF8 */ sead::Vector3f vec_F8{sead::Vector3f::zero};
    /*0x104 */ sead::Vector3f vec_104{sead::Vector3f::zero};
    /*0x110 */ float unk_110;
    /*0x114 */ float unk_114;
    /*0x118 */ float unk_118;
    /*0x11c */ float unk_11c;
    /*0x120 */ u32 mFlags;
};
}  // namespace uking