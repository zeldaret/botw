#pragma once

#include <basis/seadTypes.h>
#include <codec/seadHashCRC32.h>
#include <container/seadTreeMap.h>

namespace ksys::util {

class StrTreeMapKey {
public:
    const sead::SafeString& key() const { return mKey; }

    // NON_MATCHING: stack
    void setKey(u32 hash, sead::SafeString key) {
        mKeyHash = hash;
        mKey = key;
    }

    void setKey(const sead::SafeString& key) {
        setKey(sead::HashCRC32::calcStringHash(key.cstr()), key);
    }

    s32 compare(const StrTreeMapKey& rhs) const {
        if (mKeyHash < rhs.mKeyHash)
            return -1;
        if (mKeyHash > rhs.mKeyHash)
            return 1;
        return mKey.compare(rhs.mKey);
    }

private:
    u32 mKeyHash = 0;
    sead::SafeString mKey;
};

class StrTreeMapNode : public sead::TreeMapNode<StrTreeMapKey> {
public:
    ~StrTreeMapNode() override { ; }
    void erase_() override { mLeft = mRight = nullptr; }
};

template <typename Node>
class StrTreeMap : public sead::IntrusiveTreeMap<StrTreeMapKey, Node> {};

}  // namespace ksys::util
