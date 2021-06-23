#pragma once

#include <container/seadObjArray.h>
#include <container/seadPtrArray.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/GameData/gdtFlagHandle.h"
#include "KingSystem/Utils/Byaml/Byaml.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::qst {

struct ActorData;
struct Indicator;

struct Step {
    struct ActLink {
        void* _0;
        act::BaseProcLink link;
        void* _18;
        const char* name;
        void* _28;
        void* _30;
        void* _38;
        void* _40;
        const char* unique_name;

        bool sub_71012B43D0(act::Actor* actor, const sead::SafeString& name) const;
    };

    Step(const u8** iter_data, sead::Heap* heap);
    virtual ~Step();

    bool sub_7100FDB89C(act::Actor* actor) const;
    bool sub_7100FDB538(act::Actor* actor, const sead::SafeString& name) const;
    bool sub_7100FDB794(act::Actor* actor) const;
    bool initActorData(u32 unused, sead::BufferedSafeString* out_message);
    bool initIndicator(u32 unused, sead::BufferedSafeString* out_message);
    bool sub_7100FDC2A4(al::ByamlIter* iter);

    sead::ObjArray<ActLink> links;
    u32 _28 = 0;
    gdt::FlagHandle dep_flag = gdt::InvalidHandle;
    const char* dep_flag_name = &sead::SafeString::cNullChar;
    u32 _38 = 3;
    u32 _3c = 0;
    bool attention_off = false;
    const char* message_name = &sead::SafeString::cNullChar;
    const char* name = &sead::SafeString::cNullChar;
    gdt::FlagHandle next_flag = gdt::InvalidHandle;
    const char* next_flag_name = &sead::SafeString::cNullChar;
    sead::Heap* heap = nullptr;
    ActorData* actor_data = nullptr;
    Indicator* indicator_info = nullptr;
    al::ByamlIter* iter = nullptr;
};
KSYS_CHECK_SIZE_NX150(Step, 0x88);

}  // namespace ksys::qst
