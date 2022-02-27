#include "KingSystem/ActorSystem/actASSetting.h"
#include "KingSystem/Resource/resLoadRequest.h"
#include "KingSystem/Resource/resResourceASSetting.h"

namespace ksys::act {

SEAD_SINGLETON_DISPOSER_IMPL(ASSetting)

ASSetting::~ASSetting() = default;

void ASSetting::init(const sead::SafeString& config_path, sead::Heap* heap) {
    res::LoadRequest req;
    req.mRequester = "ASSetting";
    req._22 = true;
    mHandle.load(config_path, &req);
}

// NON_MATCHING: sead::DirectResource to res::ASSetting cast nullptr check; branching for the return
res::ASParamParser* ASSetting::getBoneParams(const sead::SafeString& key) const {
    auto* res = sead::DynamicCast<res::ASSetting>(mHandle.getResource());
    if (!res)
        return nullptr;

    for (auto& bones : res->getBlenderBones()) {
        if (key == bones.mKeyName.ref())
            return &bones.mBoneParams;
    }
    return nullptr;
}

}  // namespace ksys::act
