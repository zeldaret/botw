#pragma once

#include <basis/seadTypes.h>
#include <codec/seadHashCRC32.h>
#include <container/seadTreeMap.h>
#include <prim/seadDelegate.h>

namespace ksys::util {

class StrTreeMapKey {
public:
    StrTreeMapKey() = default;
    StrTreeMapKey(u32 key_hash, const sead::SafeString& key) : mKeyHash(key_hash), mKey(key) {}
    StrTreeMapKey(const sead::SafeString& key)
        : StrTreeMapKey(sead::HashCRC32::calcStringHash(key.cstr()), key) {}

    const sead::SafeString& key() const { return mKey; }

    void setKey(const sead::SafeString& key) { *this = StrTreeMapKey{key}; }

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
    using KeyType = StrTreeMapKey;
    ~StrTreeMapNode() override { ; }
    void erase_() override { mLeft = mRight = nullptr; }
};

template <typename Node>
class StrTreeMap : public sead::IntrusiveTreeMap<StrTreeMapKey, Node> {};

}  // namespace ksys::util
