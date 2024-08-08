
#include "LayoutResourceMgr.h"
#include "devenv/seadEnvUtil.h"

namespace ksys::ui {

SEAD_SINGLETON_DISPOSER_IMPL(LayoutResourceMgr)

void LayoutResourceMgr::init(sead::Heap* heap) {
    mHandleAtx28 = new (heap) res::Handle;
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

}  // namespace ksys::ui
