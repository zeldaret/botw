#pragma once

#include <heap/seadDisposer.h>
#include <prim/seadSafeString.h>
#include <thread/seadCriticalSection.h>
#include <container/seadObjArray.h>
#include "KingSystem/Resource/resHandle.h"
#include "KingSystem/Utils/Types.h"

#include "ArcResourceMgr.h"

namespace ksys::ui {

class LayoutResourceMgr {
    SEAD_SINGLETON_DISPOSER(LayoutResourceMgr)
    LayoutResourceMgr() = default;
    virtual ~LayoutResourceMgr();

public:

    void init(sead::Heap* heap);
private:
    res::Handle* mHandleAtx28 = nullptr;
    res::Handle* mLangFontTodo = nullptr;
    res::Handle* mVersionRes = nullptr;
    sead::FixedPtrArray<res::Handle, 8> mArray;
    res::Handle* mHandleAtx90 = 0;
    ArcResourceMgr* mArcResourceMgr = nullptr;
    res::Handle* mLangFontRes = nullptr;
    void* _a8 = nullptr;
    void* _b0 = nullptr;
    void* _b8 = nullptr;
    void* mTitleLayoutArchiveTodo = nullptr;
    void* _c8 = nullptr;
    u64 mSizexA8BufTodo = 0;
    res::Handle* mHorseLayoutResu = nullptr;
    u64 _e0 = 0;
    u64 _e8 = 0;
    u32 _f0 = 0;
    sead::FixedSafeString<16> mVersionString;
    int _120 = 0;
    sead::CriticalSection mCriticalSection;
};
KSYS_CHECK_SIZE_NX150(LayoutResourceMgr, 0x168);

}
