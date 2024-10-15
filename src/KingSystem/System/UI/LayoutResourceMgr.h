#pragma once

#include <container/seadObjArray.h>
#include <heap/seadDisposer.h>
#include <hostio/seadHostIONode.h>
#include <prim/seadSafeString.h>
#include <thread/seadCriticalSection.h>
#include "KingSystem/Resource/resHandle.h"
#include "KingSystem/System/UI/ArcResource.h"
#include "KingSystem/System/UI/ArcResourceMgr.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::ui {

class LayoutResourceMgr final : public sead::hostio::Node {
    SEAD_SINGLETON_DISPOSER(LayoutResourceMgr)
    LayoutResourceMgr() = default;
    ~LayoutResourceMgr() = default;

public:
    static constexpr int cExtraLangFontCount = 4;
    static constexpr int cExtraLangCount = 3;

private:
    class Archive {
        friend class LayoutResourceMgr;

    public:
        void allocate(sead::Heap* heap) {
            mHandle = new (heap) res::Handle;
            mResourceStorage = new (heap) u8[sizeof(ArcResource)];
        }
        void deallocate() {
            if (mResource) {
                delete mResource;
                mResource = nullptr;
            } else {
                delete mHandle;
                delete[] mResourceStorage;
            }
            mHandle = nullptr;
            mResourceStorage = nullptr;
        }

        res::Handle* getHandle() { return mHandle; }
        const res::Handle* getHandle() const { return mHandle; }
        ArcResource* getResource() { return mResource; }
        const ArcResource* getResource() const { return mResource; }

    private:
        res::Handle* mHandle = nullptr;
        ArcResource* mResource = nullptr;
        u8* mResourceStorage = nullptr;
    };

public:
    void init(sead::Heap* heap);
    u8* loadMsgPack(u32* size);
    void loadLangFont(sead::Heap* heap);
    void loadExtraLangFonts(sead::Heap* heap);
    bool checkLangFontReady();
    bool checkExtraLangFontsReady() const;
    void loadVersion();
    bool checkVersionReady();
    void loadCommonLayoutArchive(sead::ExpHeap* heap);
    void loadTitleLayout(sead::Heap* heap);
    bool loadTitleLayoutResource();
    void unloadTitleLayout();
    bool loadHorseLayout(sead::Heap* heap);
    bool loadHorseLayoutResource();
    bool hasHorseLayoutLoadFailure() const;
    bool unloadHorseLayout();
    void unloadA8();
    void doSomethingWithFontTextureCache(void* texture_cache);

    bool loadArcResource(Archive& archive, const char* name);

private:
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
