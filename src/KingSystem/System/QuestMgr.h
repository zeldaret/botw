#pragma once

#include <container/seadPtrArray.h>
#include <heap/seadDisposer.h>
#include <prim/seadSafeString.h>
#include "KingSystem/System/Quest.h"
#include "agl/Utils/aglParameter.h"

namespace ksys {

class QuestMgr {
    SEAD_SINGLETON_DISPOSER(QuestMgr)
public:
    QuestMgr();
    ~QuestMgr();

    bool setQuestStep(const sead::SafeString& quest_name, const sead::SafeString& step_name,
                      bool copy_name, bool force_run_telop, bool setAocVersionFlag1);

    struct Quests : public sead::PtrArrayImpl {};

private:
    Quests mQuests;
    res::Handle* mHandle = nullptr;
    u32 _e4 = 0;
    s32 _e8 = -1;
    u32 _d0 = 0;
    sead::Heap* mHeap = nullptr;
    u32 mFlags;
};

}  // namespace ksys
