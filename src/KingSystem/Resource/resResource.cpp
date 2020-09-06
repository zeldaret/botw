#include "KingSystem/Resource/resResource.h"

namespace ksys::res {

Resource::Resource() = default;

Context* Resource::getContext() const {
    return mContext;
}

void Resource::setContext(Context* context) {
    mContext = context;
}

void Resource::onDestroy() {
    onDestroy_();
}

void Resource::parse(Context*, sead::Heap* heap) {
    parse_(mRawData, mRawSize, heap);
}

bool Resource::finalize() {
    finalize_();
    return true;
}

bool Resource::finishParsing() {
    const bool ret = finishParsing_();
    mContext = nullptr;
    return ret;
}

bool Resource::m7() {
    return m7_();
}

}  // namespace ksys::res
