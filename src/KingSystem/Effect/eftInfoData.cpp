#include "KingSystem/Effect/eftInfoData.h"
#include "KingSystem/Resource/resLoadRequest.h"

namespace ksys::eft {

SEAD_SINGLETON_DISPOSER_IMPL(InfoData)

InfoData::~InfoData() {
    if (mRootIter)
        delete mRootIter;
}

void InfoData::loadEffectInfo(sead::Heap* heap) {
    res::LoadRequest req;
    req.mRequester = "eft::InfoData";
    req._22 = true;
    mResHandle.load("Actor/Effect/EffectInfo.byml", &req);

    auto* resource = sead::DynamicCast<sead::DirectResource>(mResHandle.getResource());

    if (mRootIter)
        delete mRootIter;
    mRootIter = new (heap) al::ByamlIter(resource->getRawData());
}

void InfoData::init(sead::Heap* heap) {
    loadEffectInfo(heap);
}

al::ByamlIter InfoData::getIter(const sead::SafeString& key) const {
    const auto iter = mRootIter->getIterByKey(key.cstr());
    return al::ByamlIter(iter);
}

sead::SafeString InfoData::getEffectSettingUserName(const sead::SafeString& key) const {
    const auto iter = getIter(key);
    const char* value = "Dummy";
    iter.tryGetStringByKey(&value, "EffectSettingUserName");
    return value;
}

}  // namespace ksys::eft
