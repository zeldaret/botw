#pragma once

#include <heap/seadDisposer.h>
#include <prim/seadSafeString.h>
#include <thread/seadCriticalSection.h>
#include <container/seadObjArray.h>
#include "KingSystem/Resource/resHandle.h"
#include "KingSystem/Utils/Types.h"

#include "ArcResourceMgr.h"

namespace nn::pl {
u64 RequestSharedFontLoad(int);
}

namespace ksys::ui {

class LayoutResourceMgr {
    SEAD_SINGLETON_DISPOSER(LayoutResourceMgr)
    LayoutResourceMgr() = default;
    virtual ~LayoutResourceMgr();

public:

    void init(sead::Heap* heap);
    u8* loadMsgPack(u32* size);
    void loadLangFont(sead::Heap* heap);
    void loadExtraLangFonts(sead::Heap* heap);

private:
    res::Handle* mMsgPackHandle = nullptr;
    res::Handle* mLangFontHandle = nullptr;
    res::Handle* mVersionHandle = nullptr;
    sead::FixedPtrArray<res::Handle, 8> mExtraLangFontHandles;
    res::Handle* mZeldaGlyphHandle = nullptr;
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
    u16 mMaxDefArtLen = 0;
    u16 mMaxIndefArtLen = 0;
    sead::FixedSafeString<16> mVersionString;
    int _120 = 0;
    sead::CriticalSection mCriticalSection;
};
KSYS_CHECK_SIZE_NX150(LayoutResourceMgr, 0x168);

}
