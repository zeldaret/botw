#include <devenv/seadEnvUtil.h>

#include <cstddef>
#include "KingSystem/Resource/resLoadRequest.h"
#include "KingSystem/System/StarterPackMgr.h"

#include "LayoutResourceMgr.h"

namespace ksys::ui {

SEAD_SINGLETON_DISPOSER_IMPL(LayoutResourceMgr)

void LayoutResourceMgr::init(sead::Heap* heap) {
    mMsgPackHandle = new (heap) res::Handle;
    mLangFontHandle = new (heap) res::Handle;
    mVersionHandle = new (heap) res::Handle;
    int count;
    // value() needed because operator int() is volatile
    switch (sead::EnvUtil::getRegionLanguage().value()) {
    case sead::RegionLanguageID::KRko:
    case sead::RegionLanguageID::CNzh:
    case sead::RegionLanguageID::TWzh:
        count = 4;
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
    mLangFontHandle = nullptr;

    res::LoadRequest req;
    req.mRequester = "LayoutResourceMgr";
    req._22 = true;
    req.mLoadDataAlignment = 0x1000;
    req._26 = false;

    sead::FixedSafeString<0x20> path;
    // TODO: needs sead::EnvUtil::getRegion() and sead::RegionID
    /* path.format("Font/Font_%s.bfarc", sead::EnvUtil::getRegion()); */

    mLangFontHandle->load(path, &req, nullptr);
}

constexpr const char* cExtraFontFiles[12] = {
    "AsiaKCUBE-R", "AsiaKDREAM2R", "AsiaKDREAM4R", "AsiaKDREAM7R", "DFP_GBZY9", "DFP_GB_H3",
    "DFP_GB_H5",   "DFHEI5A",      "DFT_ZY9",      "DFT_B3",       "DFT_B5",    "DFT_B9"};

void LayoutResourceMgr::loadExtraLangFonts(sead::Heap* heap) {
    sead::RegionLanguageID lang_id = sead::EnvUtil::getRegionLanguage();
    const char* const* fonts = cExtraFontFiles;
    for (int i = 0; i <= 2; i++) {
        if (lang_id.value() == sead::RegionLanguageID::KRko + i) {
            break;
        }
        if (i == 2) {
            return;
        }
        fonts += 4;
    }

    res::LoadRequest req;
    req.mRequester = "ui::LayoutResourceMgr";
    req._26 = false;

    // non-matching: reordering
    res::Handle::Status status = res::Handle::Status::NoFile;
    for (int i = 0; i < 4; ++i) {
        auto* handle = mExtraLangFontHandles[i];
        sead::FixedSafeString<0x20> path;
        path.format("Font/Font_%s.bfttf", fonts[i]);
        handle->requestLoad(path, &req, &status);
    }
    mZeldaGlyphHandle->requestLoad("Font/ZeldaGlyphs-v2-Deco.bfotf", &req, &status);
    nn::pl::RequestSharedFontLoad(nn::pl::SharedFontType::Unknown);
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
        return nn::pl::GetSharedFontLoadState(nn::pl::SharedFontType::Unknown) == 1;
    }
    return false;
}

}  // namespace ksys::ui
