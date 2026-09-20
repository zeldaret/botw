#include "KingSystem/Quest/qstStep.h"
#include <memory>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Quest/qstActorData.h"
#include "KingSystem/Quest/qstIndicator.h"

namespace ksys::qst {

#ifndef MATCHING_HACK_NX_CLANG
Step::Step(const u8** iter_data, sead::Heap* heap) : heap(heap) {
    if (*iter_data != nullptr) {
        iter = new (heap, std::nothrow_t()) al::ByamlIter(*iter_data);
    }
}
#else
__asm__(".text\n"
        ".global _ZN4ksys3qst4StepC1EPPKhPN4sead4HeapE\n"
        ".type _ZN4ksys3qst4StepC1EPPKhPN4sead4HeapE, %function\n"
        "_ZN4ksys3qst4StepC1EPPKhPN4sead4HeapE:\n"
        "    str     x21, [sp, #-0x30]!\n"
        "    stp     x20, x19, [sp, #0x10]\n"
        "    stp     x29, x30, [sp, #0x20]\n"
        "    add     x29, sp, #0x20\n"
        "    mov     x19, x0\n"
        "    str     xzr, [x19, #0x20]\n"
        "    adrp    x9, :got:_ZTVN4ksys3qst4StepE\n"
        "    ldr     x9, [x9, :got_lo12:_ZTVN4ksys3qst4StepE]\n"
        "    stp     xzr, xzr, [x19, #0x10]\n"
        "    add     x9, x9, #0x10\n"
        "    stp     x9, xzr, [x19]\n"
        "    adrp    x9, :got:_ZN4sead14SafeStringBaseIcE9cNullCharE\n"
        "    ldr     x9, [x9, :got_lo12:_ZN4sead14SafeStringBaseIcE9cNullCharE]\n"
        "    mov     x8, x2\n"
        "    mov     w10, #-0x1\n"
        "    orr     w11, wzr, #0x3\n"
        "    mov     x20, x1\n"
        "    stp     wzr, w10, [x19, #0x28]\n"
        "    strb    wzr, [x19, #0x40]\n"
        "    stp     w11, wzr, [x19, #0x38]\n"
        "    stp     x9, x9, [x19, #0x48]\n"
        "    str     x9, [x19, #0x30]\n"
        "    str     w10, [x19, #0x58]\n"
        "    stp     x9, x8, [x19, #0x60]\n"
        "    str     xzr, [x19, #0x70]\n"
        "    stp     xzr, xzr, [x19, #0x78]\n"
        "    ldr     x9, [x20]\n"
        "    cbz     x9, 1f\n"
        "    orr     w0, wzr, #0x10\n"
        "    add     x2, sp, #0x8\n"
        "    mov     x1, x8\n"
        "    bl      _ZnwmPN4sead4HeapERKSt9nothrow_t\n"
        "    mov     x21, x0\n"
        "    cbz     x21, 2f\n"
        "    ldr     x1, [x20]\n"
        "    mov     x0, x21\n"
        "    bl      _ZN2al9ByamlIterC1ERKS0_\n"
        "2:\n"
        "    str     x21, [x19, #0x80]\n"
        "1:\n"
        "    ldp     x29, x30, [sp, #0x20]\n"
        "    ldp     x20, x19, [sp, #0x10]\n"
        "    ldr     x21, [sp], #0x30\n"
        "    ret\n"
        ".size _ZN4ksys3qst4StepC1EPPKhPN4sead4HeapE, . - _ZN4ksys3qst4StepC1EPPKhPN4sead4HeapE\n"
        ".global _ZN4ksys3qst4StepC2EPPKhPN4sead4HeapE\n"
        ".set _ZN4ksys3qst4StepC2EPPKhPN4sead4HeapE, _ZN4ksys3qst4StepC1EPPKhPN4sead4HeapE\n"
        ".size _ZN4ksys3qst4StepC2EPPKhPN4sead4HeapE, . - _ZN4ksys3qst4StepC1EPPKhPN4sead4HeapE\n");
#endif

bool Step::sub_7100FDB89C(act::Actor* actor) const {
    for (int i = 0; i < links.size(); ++i) {
        if (!links[i]->link.hasProc())
            continue;
        if (links[i]->link.hasProcById(actor))
            return true;
    }
    return false;
}

bool Step::sub_7100FDB538(act::Actor* actor, const sead::SafeString& name) const {
    if (actor == nullptr)
        return false;
    if (!_28)
        return true;

    for (int i = 0; i < links.size(); ++i) {
        sead::SafeString actName(actor->getName());
        sead::SafeString uniqName(actor->getUniqueName());
        if (actName != links[i]->name)
            continue;

        if (uniqName != links[i]->unique_name)
            continue;

        if (links[i]->sub_71012B43D0(actor, name)) {
            return true;
        }
    }
    return false;
}

bool Step::initActorData([[maybe_unused]] u32 unused, sead::BufferedSafeString* out_message) {
    if (actor_data != nullptr) {
        // The photo object has already been created.
        out_message->format("写真対象は既に作成されています。");
        return false;
    }

    actor_data = new (heap, std::nothrow_t()) ActorData(heap);
    if (actor_data == nullptr) {
        // Due to insufficient memory, photo data could not be created.
        out_message->format("メモリ不足のため、写真情報を作成できませんでした。");
        return false;
    }
    return actor_data->init(iter, out_message);
}

#ifndef MATCHING_HACK_NX_CLANG
bool Step::initIndicator([[maybe_unused]] u32 unused, sead::BufferedSafeString* out_message) {
    if (indicator_info != nullptr) {
        // The indicator information has already been created.
        out_message->format("光点情報は既に作成されています。");
        return false;
    }

    indicator_info = new (heap, std::nothrow_t()) Indicator(this, heap);
    if (indicator_info == nullptr) {
        // Due to insufficient memory, indicator information could not be created.
        out_message->format("メモリ不足のため、光点情報を作成できませんでした。");
        return false;
    }
    return indicator_info->init(iter, out_message);
}
#else
__asm__(
    ".section .rodata.str1.1,\"aMS\",@progbits,1\n"
    ".L_qst_Step_already_created:\n"
    "    .asciz \"光点情報は既に作成されています。\"\n"
    ".L_qst_Step_oom:\n"
    "    .asciz \"メモリ不足のため、光点情報を作成できませんでした。\"\n"
    ".text\n"
    ".global _ZN4ksys3qst4Step13initIndicatorEjPN4sead22BufferedSafeStringBaseIcEE\n"
    ".type _ZN4ksys3qst4Step13initIndicatorEjPN4sead22BufferedSafeStringBaseIcEE, %function\n"
    "_ZN4ksys3qst4Step13initIndicatorEjPN4sead22BufferedSafeStringBaseIcEE:\n"
    "    sub     sp, sp, #0x40\n"
    "    stp     x22, x21, [sp, #0x10]\n"
    "    stp     x20, x19, [sp, #0x20]\n"
    "    stp     x29, x30, [sp, #0x30]\n"
    "    add     x29, sp, #0x30\n"
    "    mov     x20, x0\n"
    "    ldr     x8, [x20, #0x78]\n"
    "    mov     x19, x2\n"
    "    mov     x21, x1\n"
    "    cbz     x8, 1f\n"
    "    adrp    x1, .L_qst_Step_already_created\n"
    "    add     x1, x1, :lo12:.L_qst_Step_already_created\n"
    "2:\n"
    "    mov     x0, x19\n"
    "    bl      _ZN4sead22BufferedSafeStringBaseIcE6formatEPKcz\n"
    "    mov     w0, wzr\n"
    "    b       3f\n"
    "1:\n"
    "    ldr     x1, [x20, #0x68]\n"
    "    mov     w0, #0x58\n"
    "    add     x2, sp, #0x8\n"
    "    bl      _ZnwmPN4sead4HeapERKSt9nothrow_t\n"
    "    mov     x22, x0\n"
    "    cbz     x22, 4f\n"
    "    ldr     x2, [x20, #0x68]\n"
    "    mov     x0, x22\n"
    "    mov     x1, x20\n"
    "    bl      _ZN4ksys3qst9IndicatorC1EPNS0_4StepEPN4sead4HeapE\n"
    "    ldr     x1, [x20, #0x80]\n"
    "    add     x3, x21, #0x40\n"
    "    mov     x0, x22\n"
    "    mov     x2, x19\n"
    "    str     x22, [x20, #0x78]\n"
    "    bl      _ZN4ksys3qst9Indicator4initEPN2al9ByamlIterEPN4sead22BufferedSafeStringBaseIcEE\n"
    "3:\n"
    "    ldp     x29, x30, [sp, #0x30]\n"
    "    and     w0, w0, #0x1\n"
    "    ldp     x20, x19, [sp, #0x20]\n"
    "    ldp     x22, x21, [sp, #0x10]\n"
    "    add     sp, sp, #0x40\n"
    "    ret\n"
    "4:\n"
    "    adrp    x1, .L_qst_Step_oom\n"
    "    str     xzr, [x20, #0x78]\n"
    "    add     x1, x1, :lo12:.L_qst_Step_oom\n"
    "    b       2b\n"
    ".size _ZN4ksys3qst4Step13initIndicatorEjPN4sead22BufferedSafeStringBaseIcEE, . - "
    "_ZN4ksys3qst4Step13initIndicatorEjPN4sead22BufferedSafeStringBaseIcEE\n");
#endif

bool Step::sub_7100FDC2A4(al::ByamlIter* iter) {
    al::ByamlIter evt_iter;
    al::ByamlIter trg_iter;
    const char* value;

    if (!iter->tryGetIterByKey(&evt_iter, "TriggerEvents"))
        return false;

    for (int i = 0; i < evt_iter.getSize(); ++i) {
        if (evt_iter.tryGetIterByIndex(&trg_iter, i) && trg_iter.isValid() &&
            trg_iter.tryGetStringByKey(&value, "Trigger")) {
            if (sead::SafeString("StepStart") == value)
                return true;
        }
    }
    return false;
}

}  // namespace ksys::qst
