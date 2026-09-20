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

#ifndef MATCHING_HACK_NX_CLANG
BoneAccessKeyEx::BoneAccessKeyEx() = default;
#else
__asm__(
".text\n"
".global _ZN4gsys15BoneAccessKeyExC1Ev\n"
".type _ZN4gsys15BoneAccessKeyExC1Ev, %function\n"
"_ZN4gsys15BoneAccessKeyExC1Ev:\n"
"    adrp    x8, :got:_ZTVN4gsys19IModelAccesssHandleE\n"
"    adrp    x9, :got:_ZTVN4sead14SafeStringBaseIcEE\n"
"    ldr     x8, [x8, :got_lo12:_ZTVN4gsys19IModelAccesssHandleE]\n"
"    ldr     x9, [x9, :got_lo12:_ZTVN4sead14SafeStringBaseIcEE]\n"
"    orr     w10, wzr, #0xffff\n"
"    strh    w10, [x0, #0x32]\n"
"    strh    w10, [x0, #0x30]\n"
"    adrp    x10, :got:_ZN4sead14SafeStringBaseIcE12cEmptyStringE\n"
"    ldr     x10, [x10, :got_lo12:_ZN4sead14SafeStringBaseIcE12cEmptyStringE]\n"
"    add     x8, x8, #0x10\n"
"    add     x9, x9, #0x10\n"
"    stp     x8, x9, [x0]\n"
"    ldr     x8, [x10, #0x8]\n"
"    stp     xzr, xzr, [x0, #0x20]\n"
"    adrp    x9, :got:_ZTVN4gsys15BoneAccessKeyExE\n"
"    ldr     x9, [x9, :got_lo12:_ZTVN4gsys15BoneAccessKeyExE]\n"
"    stp     x8, xzr, [x0, #0x10]\n"
"    add     x8, x9, #0x10\n"
"    str     x8, [x0]\n"
"    ret\n"
".size _ZN4gsys15BoneAccessKeyExC1Ev, . - _ZN4gsys15BoneAccessKeyExC1Ev\n"
".global _ZN4gsys15BoneAccessKeyExC2Ev\n"
".set _ZN4gsys15BoneAccessKeyExC2Ev, _ZN4gsys15BoneAccessKeyExC1Ev\n"
".size _ZN4gsys15BoneAccessKeyExC2Ev, . - _ZN4gsys15BoneAccessKeyExC1Ev\n"
);
#endif

BoneAccessKeyEx::~BoneAccessKeyEx() {
    remove();
}

void BoneAccessKeyEx::removeImpl_() {
    mKey.reset();
}

}  // namespace gsys
