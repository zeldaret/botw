#include "agl/Utils/aglParameterObj.h"
#include <basis/seadRawPrint.h>
#include <prim/seadFormatPrint.h>
#include "agl/Utils/aglParameter.h"

namespace agl::utl {

IParameterObj::IParameterObj() = default;

void IParameterObj::pushBackListNode(ParameterBase* p_node) {
    SEAD_ASSERT(p_node != nullptr);

    ParameterBase** ptr;
    if (mParamListTail) {
        ptr = &mParamListTail->mNext;
    } else {
        ptr = &mParamListHead;
        mParamListTail = p_node;
    }

    *ptr = p_node;
    mParamListTail = p_node;
    ++mParamListSize;
}

const char* IParameterObj::getTagName() {
    return "param_array";
}

sead::SafeString IParameterObj::getName() const {
#ifdef SEAD_DEBUG
    return mName;
#else
    return sead::SafeString::cEmptyString;
#endif
}

void IParameterObj::applyResParameterObj(ResParameterObj obj1, ResParameterObj obj2, f32 t,
                                         IParameterList* list) {
    if (obj1.ptr() && t <= 0.0f) {
        applyResParameterObj_(false, obj1, {}, 0.0f, list);
        return;
    }

    if (obj2.ptr() && t >= 1.0f) {
        applyResParameterObj_(false, obj2, {}, 0.0f, list);
        return;
    }

    applyResParameterObj_(true, obj1, obj2, t, list);
}

bool IParameterObj::isComplete(ResParameterObj obj, bool check_values) const {
    if (!obj.ptr() || obj.getNum() != mParamListSize)
        return false;

    ParameterBase* param = mParamListHead;

    while (param) {
        const auto idx = obj.searchIndex(param->getNameHash());
        if (idx == -1)
            return false;

        if (check_values) {
            const auto res = obj.getResParameter(idx);

            // As usual, booleans are a special case.
            if (ParameterType(res.ptr()->getType()) == ParameterType::Bool) {
                const bool value = *res.getData<u32>() != 0;
                if (value != *param->ptrT<bool>())
                    return false;
            } else {
                if (sead::MemUtil::compare(param->ptr(), res.getData<void>(), res.getDataSize()))
                    return false;
            }
        }

        param = param->mNext;
    }
    return true;
}

bool IParameterObj::verify() const {
    bool ret = true;
    for (auto* param = mParamListHead; param; param = param->mNext)
        ret &= verify(param, param->mNext);
    return ret;
}

bool IParameterObj::verify(ParameterBase* p_check, ParameterBase* other) const {
    SEAD_ASSERT(p_check != nullptr);
    auto* param = other;
    bool ok = true;
    while (param) {
        if (p_check->getNameHash() == param->getNameHash()) {
            sead::BufferingPrintFormatter ss;
            ss << "Same hash code at [%s] and [%s]. Please change.\n"
               << p_check->getName().cstr() << param->getName().cstr()
               << sead::flush;
            ok = false;
        }
        param = param->mNext;
    }
    return ok;
}

ParameterBase* IParameterObj::searchParameter_(u32 hash) {
    for (auto* param = mParamListHead; param; param = param->mNext) {
        if (param->getNameHash() == hash)
            return param;
    }
    return nullptr;
}

ParameterBase* IParameterObj::searchParameter_(u32 hash) const {
    for (auto* param = mParamListHead; param; param = param->mNext) {
        if (param->getNameHash() == hash)
            return param;
    }
    return nullptr;
}

void IParameterObj::copy(ParameterBase* first, ParameterBase* last, const ParameterBase* src_first,
                         const ParameterBase* src_last) {
    if (!preCopy_())
        return;

    copy_(first, last, src_first, src_last);

    postCopy_();
}

void IParameterObj::copy_(ParameterBase* first, ParameterBase* last, const ParameterBase* src_first,
                          const ParameterBase* src_last) {
    auto target = first;
    auto source = src_first;
    while (target != last && source != src_last) {
        const bool result = target->copy(*source);
        SEAD_ASSERT(result);
        target = target->mNext;
        source = source->mNext;
    }
}

void IParameterObj::copy(const IParameterObj& obj) {
    if (!preCopy_())
        return;

    auto* mpHead = mParamListHead;
    SEAD_ASSERT(mpHead != nullptr);

    auto* src = obj.mParamListHead;
    while (src && src->getNameHash() != mpHead->getNameHash())
        src = src->mNext;

    while (src && mpHead) {
        const bool result = mpHead->copy(*src);
        SEAD_ASSERT(result);
        mpHead = mpHead->mNext;
        if (!mpHead)
            break;
        src = src->mNext;
    }

    postCopy_();
}

void IParameterObj::copyLerp(ParameterBase* first, ParameterBase* last,
                             const ParameterBase* src1_first, const ParameterBase* src1_last,
                             const ParameterBase* src2_first, const ParameterBase* src2_last,
                             f32 t) {
    if (!preCopy_())
        return;

    if (t <= 0.0)
        copy_(first, last, src1_first, src1_last);
    else if (t >= 1.0)
        copy_(first, last, src2_first, src2_last);
    else
        copyLerp_(first, last, src1_first, src1_last, src2_first, src2_last, t);

    postCopy_();
}

void IParameterObj::copyLerp(const IParameterObj& obj1, const IParameterObj& obj2, f32 t) {
    if (!preCopy_())
        return;

    auto mpHead = mParamListHead;
    SEAD_ASSERT(mpHead);

    const u32 hash = mpHead->getNameHash();

    auto* it1 = obj1.mParamListHead;
    while (it1 && it1->getNameHash() != hash)
        it1 = it1->mNext;

    auto* it2 = obj2.mParamListHead;
    while (it2 && it2->getNameHash() != hash)
        it2 = it2->mNext;

    while (it1 && it2 && mpHead) {
        const bool result = mpHead->copyLerp(*it1, *it2, t);
        SEAD_ASSERT(result);
        it2 = it2->mNext;
        if (!it2)
            break;
        mpHead = mpHead->mNext;
        if (!mpHead)
            break;
        it1 = it1->mNext;
    }

    postCopy_();
}

void IParameterObj::copyLerp_(ParameterBase* first, ParameterBase* last,
                              const ParameterBase* src1_first, const ParameterBase* src1_last,
                              const ParameterBase* src2_first, const ParameterBase* src2_last,
                              f32 t) {
    auto* it = first;
    auto* src1 = src1_first;
    auto* src2 = src2_first;
    while (it != last && src1 != src1_last && src2 != src2_last) {
        const bool result = it->copyLerp(*src1, *src2, t);
        SEAD_ASSERT(result);
        it = it->mNext;
        src1 = src1->mNext;
        src2 = src2->mNext;
    }
}

}  // namespace agl::utl
