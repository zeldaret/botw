#pragma once

#include <container/seadObjArray.h>
#include <heap/seadDisposer.h>
#include <prim/seadSafeString.h>
#include <thread/seadCriticalSection.h>
#include "KingSystem/Resource/resHandle.h"
#include "KingSystem/System/UI/ArcResource.h"
#include "KingSystem/System/UI/ArcResourceMgr.h"
#include "KingSystem/Utils/Types.h"

namespace nn::pl {
enum SharedFontType : int { Unknown = 0 };
u64 RequestSharedFontLoad(nn::pl::SharedFontType type);
u32 GetSharedFontLoadState(nn::pl::SharedFontType type);
}  // namespace nn::pl
#include "prim/seadEnum.h"
namespace sead {
SEAD_ENUM(RegionID, JP, US, EU, KR, CN)
class EnvUtil2 {
public:
    static RegionID getRegion();
};
}  // namespace sead

namespace ksys::ui {

class LayoutResourceMgr {
    SEAD_SINGLETON_DISPOSER(LayoutResourceMgr)
    LayoutResourceMgr() = default;
    ~LayoutResourceMgr() = default;

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
    virtual void this_class_has_vtable();

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
