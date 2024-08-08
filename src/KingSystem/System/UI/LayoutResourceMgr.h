#pragma once

#include <container/seadObjArray.h>
#include <heap/seadDisposer.h>
#include <prim/seadSafeString.h>
#include <thread/seadCriticalSection.h>
#include "KingSystem/Resource/resHandle.h"
#include "KingSystem/Utils/Types.h"

#include "ArcResourceMgr.h"

namespace nn::pl {
enum SharedFontType : int { Unknown = 0 };
u64 RequestSharedFontLoad(nn::pl::SharedFontType type);
u32 GetSharedFontLoadState(nn::pl::SharedFontType type);
}  // namespace nn::pl

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
    bool checkLangFontReady();
    bool checkExtraLangFontsReady() const;

private:
    res::Handle* mMsgPackHandle = nullptr;
    res::Handle* mLangFontHandle = nullptr;
    res::Handle* mVersionHandle = nullptr;
    sead::FixedPtrArray<res::Handle, 8> mExtraLangFontHandles;
    res::Handle* mZeldaGlyphHandle = nullptr;
    ArcResourceMgr* mArcResourceMgr = nullptr;
    sead::DirectResource* mLangFontResource = nullptr;
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

}  // namespace ksys::ui
