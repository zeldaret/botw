#pragma once

#include <container/seadListImpl.h>
#include <prim/seadSafeString.h>

namespace gsys {

class Model;

// sic: this should be called IModelAccessHandle
class IModelAccesssHandle {
public:
    IModelAccesssHandle();
    virtual ~IModelAccesssHandle();

    bool search(const Model* p_model, const sead::SafeString& name);
    bool search();
    void remove();

    static constexpr size_t getListNodeOffset() { return offsetof(IModelAccesssHandle, mListNode); }

protected:
    virtual bool searchImpl_() = 0;
    virtual void removeImpl_() = 0;

    sead::SafeString mName = sead::SafeString::cEmptyString;
    const Model* mModel{};
    sead::ListNode mListNode;
};

struct BoneAccessKey {
    BoneAccessKey() { reset(); }

    void reset() {
        model_unit_index = -1;
        bone_index = -1;
    }

    s16 model_unit_index{};
    s16 bone_index{};
};

class BoneAccessKeyEx : public IModelAccesssHandle {
public:
    BoneAccessKeyEx();
    ~BoneAccessKeyEx() override;

    using IModelAccesssHandle::search;
    bool search(const Model* p_model, const BoneAccessKey& key);

protected:
    bool searchImpl_() override;
    void removeImpl_() override;

    BoneAccessKey mKey;
};

}  // namespace gsys
