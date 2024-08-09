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
    void loadVersion();

private:

    class Archive {
    public:
        res::Handle* mHandle = nullptr;
        void* _8 = nullptr;
        void* _sizeA8Buf = nullptr;
    };

    res::Handle* mMsgPackHandle = nullptr;
    res::Handle* mLangFontHandle = nullptr;
    res::Handle* mVersionHandle = nullptr;
    sead::FixedPtrArray<res::Handle, 8> mExtraLangFontHandles;
    res::Handle* mZeldaGlyphHandle = nullptr;
    ArcResourceMgr* mArcResourceMgr = nullptr;
    sead::DirectResource* mLangFontResource = nullptr;
    Archive _a8;
    Archive mTitleLayout;
    Archive mHorseLayout;
    u16 mMaxDefArtLen = 0;
    u16 mMaxIndefArtLen = 0;
    sead::FixedSafeString<16> mVersionString;
    int mHorseLayoutLoadCount = 0;
    sead::CriticalSection mCriticalSection;
};
KSYS_CHECK_SIZE_NX150(LayoutResourceMgr, 0x168);

}  // namespace ksys::ui
