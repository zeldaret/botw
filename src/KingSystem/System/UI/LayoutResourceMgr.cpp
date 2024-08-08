#include <devenv/seadEnvUtil.h>
#include "KingSystem/Resource/resLoadRequest.h"
#include "KingSystem/System/StarterPackMgr.h"

#include "LayoutResourceMgr.h"

namespace ksys::ui {

SEAD_SINGLETON_DISPOSER_IMPL(LayoutResourceMgr)

void LayoutResourceMgr::init(sead::Heap* heap) {
    mMsgPackHandle = new (heap) res::Handle;
    mLangFontTodo = new (heap) res::Handle;
    mVersionRes = new (heap) res::Handle;
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
        mArray.pushBack(new (heap) res::Handle);
    }
    if (count > 0) {
        mHandleAtx90 = new (heap) res::Handle;
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
    auto* resource = sead::DynamicCast<sead::DirectResource>(
            mMsgPackHandle->load(path, &req, &status)
        );

    *size = resource->getRawSize();
    return resource->getRawData();
}

}  // namespace ksys::ui
