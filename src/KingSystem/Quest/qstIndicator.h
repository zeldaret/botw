#pragma once

#include <heap/seadHeap.h>
#include "KingSystem/Quest/qstManager.h"
#include "KingSystem/Utils/Byaml/Byaml.h"

namespace ksys::qst {

struct Step;

struct IndicatorActor {
    IndicatorActor();
    virtual ~IndicatorActor();

    act::BaseProcLink link;
    bool has_far;
    const char* instance_name;
    sead::Vector3f location;
    const char* name;
    const char* off_flag;
    u32 is_remains;
    u32 hash_name = 0;
    u32 hash_instance_name = 0;
    void* _58;
};

struct Indicator {
    Indicator(Step* step, sead::Heap* heap);
    virtual ~Indicator();

    bool init(al::ByamlIter* iter, sead::BufferedSafeString* out_message);
    void finalize();

    void acquireActors();
    void sub_7100FD4FC4();
    const IndicatorActor* sub_7100FD54E4(int idx) const;
    const IndicatorActor* sub_7100FD5518(int idx) const;

    sead::ObjArray<IndicatorActor> actors;
    sead::ObjArray<IndicatorActor> _28;
    sead::Heap* heap;
    Step* step;
};

}  // namespace ksys::qst
