#include "KingSystem/XLink/xlinkInfoData.h"
#include "KingSystem/Resource/resLoadRequest.h"

namespace ksys::xlink {

SEAD_SINGLETON_DISPOSER_IMPL(InfoData)

InfoData::~InfoData() {
    if (mRootIter)
        delete mRootIter;
}

void InfoData::loadInfo(sead::Heap* heap) {
    res::LoadRequest req;
    req.mRequester = "xlink::InfoData";
    req._22 = true;
    mResHandle.load("Actor/XLink/XLinkInfo.byml", &req);

    auto* resource = sead::DynamicCast<sead::DirectResource>(mResHandle.getResource());

    if (mRootIter)
        delete mRootIter;
    mRootIter = new (heap) al::ByamlIter(resource->getRawData());
}

void InfoData::init(sead::Heap* heap) {
    loadInfo(heap);
}

al::ByamlIter InfoData::getIter(const sead::SafeString& key) const {
    const auto iter = mRootIter->getIterByKey(key.cstr());
    return al::ByamlIter(iter);
}

sead::SafeString InfoData::getXLinkSettingPropertyTableName(const al::ByamlIter& iter) const {
    const char* value = "ActorBasic";
    iter.tryGetStringByKey(&value, "XLinkSettingPropertyTableName");
    return value;
}

sead::SafeString InfoData::getXLinkSettingFootStepProcTypeName(const al::ByamlIter& iter) const {
    const char* value = "None";
    iter.tryGetStringByKey(&value, "XLinkSettingFootStepProcTypeName");
    return value;
}

float InfoData::getXLinkSettingVeloClampThreshold(const al::ByamlIter& iter) const {
    float value = 0.0;
    iter.tryGetFloatByKey(&value, "XLinkSettingVeloClampThreshold");
    return value;
}

float InfoData::getXLinkSettingVeloRollClampThreshold(const al::ByamlIter& iter) const {
    float value = 0.0;
    iter.tryGetFloatByKey(&value, "XLinkSettingVeloRollClampThreshold");
    return value;
}

bool InfoData::getXLinkSettingIsReactionTargetEnemy(const al::ByamlIter& iter) const {
    bool value = false;
    iter.tryGetBoolByKey(&value, "XLinkSettingIsReactionTargetEnemy");
    return value;
}

bool InfoData::getXLinkSettingIsReactionTargetTinyEnemy(const al::ByamlIter& iter) const {
    bool value = false;
    iter.tryGetBoolByKey(&value, "XLinkSettingIsReactionTargetTinyEnemy");
    return value;
}

bool InfoData::getXLinkSettingIsReactionTargetObject(const al::ByamlIter& iter) const {
    bool value = false;
    iter.tryGetBoolByKey(&value, "XLinkSettingIsReactionTargetObject");
    return value;
}

bool InfoData::getXLinkSettingIsIgnoreDamageToObject(const sead::SafeString& key) const {
    const auto iter = getIter(key);
    bool value = false;
    iter.tryGetBoolByKey(&value, "XLinkSettingIsIgnoreDamageToObject");
    return value;
}

}  // namespace ksys::xlink
