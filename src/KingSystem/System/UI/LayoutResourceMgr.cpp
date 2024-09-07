#include <devenv/seadEnvUtil.h>
#include <nn/pl.h>
#include <prim/seadScopedLock.h>

#include "KingSystem/Resource/resLoadRequest.h"
#include "KingSystem/System/StarterPackMgr.h"
#include "KingSystem/System/UI/ArcResource.h"
#include "KingSystem/System/UI/LayoutResourceMgr.h"

namespace ksys::ui {

SEAD_SINGLETON_DISPOSER_IMPL(LayoutResourceMgr)

void LayoutResourceMgr::init(sead::Heap* heap) {
    mMsgPackHandle = new (heap) res::Handle;
    mLangFontHandle = new (heap) res::Handle;
    mVersionHandle = new (heap) res::Handle;

    int count;
    switch (sead::EnvUtil::getRegionLanguage().value()) {
    case sead::RegionLanguageID::KRko:
    case sead::RegionLanguageID::CNzh:
    case sead::RegionLanguageID::TWzh:
        count = cExtraLangFontCount;
        break;
    default:
        count = 0;
        break;
    }
    for (int i = 0; i < count; i++) {
        mExtraLangFontHandles.pushBack(new (heap) res::Handle);
    }
    if (count > 0) {
        mZeldaGlyphHandle = new (heap) res::Handle;
    }
}

u8* LayoutResourceMgr::loadMsgPack(u32* size) {
    mMsgPackHandle->resetUnitFlag20000IfSuccess();
    mMsgPackHandle->unload();

    res::LoadRequest req;
    req.mRequester = "LayoutResourceMgr";
    req._22 = true;
    req._21 = true;
    req.mLoadDataAlignment = 0x80;
    req._26 = false;
    req.mPackHandle = StarterPackMgr::instance()->getBootupLangPack();

    sead::FixedSafeString<0x20> path;
    path.format("Message/Msg_%s.product.sarc", sead::EnvUtil::getRegionLanguage().text());

    res::Handle::Status status;
    auto* resource =
        sead::DynamicCast<sead::DirectResource>(mMsgPackHandle->load(path, &req, &status));

    *size = resource->getRawSize();
    return resource->getRawData();
}

void LayoutResourceMgr::loadLangFont(sead::Heap* heap) {
    mLangFontHandle->resetUnitFlag20000IfSuccess();
    mLangFontHandle->unload();
    mLangFontResource = nullptr;

    res::LoadRequest req;
    req.mRequester = "LayoutResourceMgr";
    req._22 = true;
    req.mLoadDataAlignment = 0x1000;
    req._26 = false;

    sead::FixedSafeString<0x20> path;
    path.format("Font/Font_%s.bfarc", sead::EnvUtil::getRegion().text());

    mLangFontHandle->requestLoad(path, &req, nullptr);
}

void LayoutResourceMgr::loadExtraLangFonts(sead::Heap* heap) {
    sead::RegionLanguageID lang_id = sead::EnvUtil::getRegionLanguage();
    auto* fonts = sExtraLangFontFiles;
    for (int i = 0; i <= cExtraLangCount; i++) {
        if (lang_id.value() == sead::RegionLanguageID::KRko + i) {
            break;
        }
        if (i == cExtraLangCount - 1) {
            return;
        }
        fonts += cExtraLangFontCount;
    }

    res::LoadRequest req;
    req.mRequester = "ui::LayoutResourceMgr";
    req._26 = false;

    res::Handle::Status status = res::Handle::Status::NoFile;
    for (int i = 0; i < cExtraLangFontCount; ++i) {
        auto* handle = mExtraLangFontHandles[i];
        sead::FixedSafeString<0x20> path;
#ifdef MATCHING_HACK_NX_CLANG
        asm("");
#endif
        path.format("Font/%s.bfttf", fonts[i]);
        handle->requestLoad(path, &req, &status);
    }

    mZeldaGlyphHandle->requestLoad("Font/ZeldaGlyphs-v2-Deco.bfotf", &req, &status);
    nn::pl::RequestSharedFontLoad(nn::pl::SharedFontType::STANDARD);
}

bool LayoutResourceMgr::checkLangFontReady() {
    if (mLangFontResource) {
        return true;
    }
    if (!mLangFontHandle->isReady()) {
        return false;
    }
    mLangFontResource = sead::DynamicCast<sead::DirectResource>(mLangFontHandle->getResource());
    return true;
}

bool LayoutResourceMgr::checkExtraLangFontsReady() const {
    switch (sead::EnvUtil::getRegionLanguage().value()) {
    case sead::RegionLanguageID::KRko:
    case sead::RegionLanguageID::CNzh:
    case sead::RegionLanguageID::TWzh:
        break;
    default:
        return true;
    }
    for (const auto& handle : mExtraLangFontHandles) {
        if (!handle.isReady()) {
            return false;
        }
    }
    if (!mZeldaGlyphHandle || mZeldaGlyphHandle->isReady()) {
        return nn::pl::GetSharedFontLoadState(nn::pl::SharedFontType::STANDARD) ==
               nn::pl::LoadState::LOADED;
    }
    return false;
}

void LayoutResourceMgr::loadVersion() {
    res::LoadRequest req;
    req.mRequester = "LayoutResourceMgr";
    req._26 = false;

    mVersionHandle->requestLoad("System/Version.txt", &req, nullptr);
}

bool LayoutResourceMgr::checkVersionReady() {
    if (!mVersionHandle) {
        return true;
    }
    if (mVersionHandle->isReady()) {
        auto* resource = sead::DynamicCast<sead::DirectResource>(mVersionHandle->getResource());
        instance()->mVersionString.copy(reinterpret_cast<const char*>(resource->getRawData()),
                                        static_cast<s32>(resource->getRawSize()));
        delete mVersionHandle;
        mVersionHandle = nullptr;
        return true;
    }
    return false;
}

void LayoutResourceMgr::loadCommonLayoutArchive(sead::ExpHeap* heap) {
    mArcResourceMgr->loadArchive(heap, "Layout/Common.sblarc");
}

void LayoutResourceMgr::loadTitleLayout(sead::Heap* heap) {
    mTitleLayout.allocate(heap);

    res::LoadRequest req;
    req.mRequester = "ui::LayoutResourceMgr";
    req.mLoadDataAlignment = 0x1000;
    req._22 = false;
    req._26 = false;
    req._c = 2;

    res::Handle::Status status = res::Handle::Status::NoFile;
    mTitleLayout.getHandle()->requestLoad("Layout/Title.blarc", &req, &status);
}

bool LayoutResourceMgr::loadTitleLayoutResource() {
    return loadArcResource(mTitleLayout, "Title");
}

void LayoutResourceMgr::unloadTitleLayout() {
    mTitleLayout.deallocate();
}

bool LayoutResourceMgr::loadHorseLayout(sead::Heap* heap) {
    sead::ScopedLock<sead::CriticalSection> lock(&mCriticalSection);

    if (mHorseLayoutLoadCount++) {
        return false;
    }

    mHorseLayout.allocate(heap);

    res::LoadRequest req;
    req.mRequester = "ui::LayoutResourceMgr";
    req.mLoadDataAlignment = 0x1000;
    req._22 = false;
    req._26 = true;
    req._c = 2;

    res::Handle::Status status = res::Handle::Status::NoFile;
    mHorseLayout.getHandle()->requestLoad("Layout/Horse.blarc", &req, &status);

    return true;
}

bool LayoutResourceMgr::loadHorseLayoutResource() {
    sead::ScopedLock<sead::CriticalSection> lock(&mCriticalSection);
    return loadArcResource(mHorseLayout, "Horse");
}

bool LayoutResourceMgr::hasHorseLayoutLoadFailure() const {
    if (mHorseLayout.getHandle()) {
        if (mHorseLayout.getHandle()->isReady() && !mHorseLayout.getHandle()->isSuccess()) {
            return true;
        }
    }
    return false;
}

bool LayoutResourceMgr::unloadHorseLayout() {
    sead::ScopedLock<sead::CriticalSection> lock(&mCriticalSection);
    int old_count = mHorseLayoutLoadCount--;

    if (mHorseLayoutLoadCount == 0) {
        mHorseLayout.deallocate();
        return true;
    }

    return old_count < 2;
}

bool LayoutResourceMgr::loadArcResource(Archive& archive, const char* name) {
    if (!archive.getResource()) {
        if (!archive.getHandle()->isReady()) {
            return false;
        }
        if (archive.getHandle()->isSuccess()) {
            auto* resource =
                sead::DynamicCast<sead::DirectResource>(archive.getHandle()->getResource());
            if (resource) {
                auto* arc_resource = reinterpret_cast<ArcResource*>(archive.mResourceStorage);
                arc_resource->init(mArcResourceMgr, name, resource->getRawData(), archive.mHandle);
                archive.mResource = arc_resource;
                mArcResourceMgr->addArchive(archive.getResource());
            }
        }
    }
    return true;
}

void LayoutResourceMgr::unloadA8() {
    _a8.deallocate();
}

}  // namespace ksys::ui
