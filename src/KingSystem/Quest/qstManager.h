#pragma once

#include <container/seadObjArray.h>
#include <heap/seadDisposer.h>
#include <prim/seadSafeString.h>
#include "KingSystem/Quest/qstQuest.h"
#include "KingSystem/Resource/resHandle.h"
#include "agl/Utils/aglParameter.h"

namespace ksys::qst {

struct Quest;

class Manager {
    SEAD_SINGLETON_DISPOSER(Manager)
public:
    Manager();
    virtual ~Manager();

    void init(sead::Heap* heap);
    void cleanUp();

    void auto0(act::Actor* actor);
    bool auto4(act::Actor* actor) const;

    bool sub_7100FD78F8();

    bool sub_7100FD7B30(const sead::SafeString& quest_name, const sead::SafeString& step_name,
                        bool setAocVersionFlag1);
    bool setQuestStepFromEvent(const sead::SafeString& quest_name,
                               const sead::SafeString& step_name, bool force_run_telop,
                               bool setAocVersionFlag1);
    bool setQuestStep(const sead::SafeString& quest_name, const sead::SafeString& step_name,
                      bool copy_name, bool force_run_telop, bool setAocVersionFlag1);

    bool isQuestActor(act::Actor* actor) const;
    static act::BaseProc* sub_7100FD5848(const sead::SafeString& s1, const sead::SafeString& s2);

private:
    u32 _28;
    u32 _2c;
    u32 _30;
    void* temp;
    u32 temp2;
    u32 _44;
    sead::PtrArray<ActorData> _48;
    u32 _58;
    u32 temp3;
    u32 temp4;
    res::Handle mHandle;
    sead::ObjArray<Quest> mQuests;
    sead::Heap* mHeap = nullptr;
    u16 mFlags;
    u32 _e4;
    s32 _e8 = -1;
    u32 _d0 = 0;

    static bool sDisable;
};

}  // namespace ksys::qst
