#include "gsys/gsysModelAccessKey.h"
#include <basis/seadRawPrint.h>
#include <prim/seadMemUtil.h>
#include <prim/seadScopedLock.h>
#include "gsys/gsysModel.h"

namespace gsys {

IModelAccesssHandle::IModelAccesssHandle() = default;

IModelAccesssHandle::~IModelAccesssHandle() {
    ;
}

bool IModelAccesssHandle::search(const Model* p_model, const sead::SafeString& name) {
    SEAD_ASSERT(p_model != nullptr);
    SEAD_ASSERT_MSG(!sead::MemUtil::isStack(name.cstr()), "String[%s] is on stack.", name.cstr());

    if (mModel != p_model) {
        remove();
        p_model->add_(this);
        mModel = p_model;
    }

    mName = name;
    return search();
}

void IModelAccesssHandle::remove() {
    if (!mModel)
        return;

    auto lock = sead::makeScopedLock(mModel->getCS());
    if (!mListNode.isLinked())
        return;

    SEAD_ASSERT(mModel != nullptr);
    mModel->remove_(this);
    mModel = nullptr;
    removeImpl_();
}

bool IModelAccesssHandle::search() {
    if (!mListNode.isLinked())
        return false;

    SEAD_ASSERT(mModel != nullptr);
    return searchImpl_();
}

BoneAccessKeyEx::BoneAccessKeyEx() = default;

BoneAccessKeyEx::~BoneAccessKeyEx() {
    remove();
}

void BoneAccessKeyEx::removeImpl_() {
    mKey.reset();
}

}  // namespace gsys
