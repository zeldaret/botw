#pragma once

#include <algorithm>
#include <type_traits>

#include <prim/seadMemUtil.h>
#ifndef SEAD_PRIM_SAFE_STRING_H_
#include <prim/seadSafeString.h>
#endif

namespace sead
{
template <typename T>
inline typename SafeStringBase<T>::token_iterator& SafeStringBase<T>::token_iterator::operator++()
{
    s32 index = this->mIndex;
    const s32 length = this->mString->calcLength();
    if (0 <= index && index <= length)
    {
        while (true)
        {
            SEAD_ASSERT(0 <= index && index <= length);
            if (this->mString->unsafeAt_(index) == cNullChar)
                break;
            if (mDelimiter.include(this->mString->unsafeAt_(index)))
                break;
            ++index;
        }

        this->mIndex = index + 1;
    }
    else
    {
        SEAD_ASSERT_MSG(false, "index(%d) out of range [0, %d].\n", index, length);
    }
    return *this;
}

template <typename T>
inline typename SafeStringBase<T>::token_iterator& SafeStringBase<T>::token_iterator::operator--()
{
    s32 index = this->mIndex;
    const s32 length = this->mString->calcLength();

    if (index == 0)
        return *this;

    if (index == 1)
    {
        this->mIndex = 0;
        return *this;
    }

    if (0 <= index && index <= length + 1)
    {
        index -= 2;
        s32 j;
        while (true)
        {
            j = index;
            SEAD_ASSERT(0 <= index && index <= length);
            if (this->mString->unsafeAt_(index) == cNullChar)
                break;
            if (mDelimiter.include(this->mString->unsafeAt_(index)))
                break;
            --index;
            if (j == 0)
            {
                j = index;
                break;
            }
        }

        this->mIndex = j + 1;
    }
    else
    {
        SEAD_ASSERT_MSG(false, "index(%d) out of range [0, %d].\n", index, length + 1);
    }
    return *this;
}

template <typename T>
inline s32 SafeStringBase<T>::token_iterator::get(BufferedSafeStringBase<T>* out) const
{
    token_iterator it = *this;
    ++it;
    const s32 part_length = it.getIndex() - this->getIndex() - 1;

    const SafeStringBase<T> part = this->mString->getPart(*this);
    return out->copy(part, part_length);
}

template <typename T>
inline s32 SafeStringBase<T>::token_iterator::getAndForward(BufferedSafeStringBase<T>* out)
{
    s32 index = this->mIndex;
    const s32 length = this->mString->calcLength();
    if (index < 0 || index > length)
    {
        SEAD_ASSERT_MSG(false, "index(%d) out of range [0, %d].\n", index, length);
        return 0;
    }

    T* outc = out->getBuffer();
    const s32 out_max_length = out->getBufferSize() - 1;

    s32 i = 0;
    while (true)
    {
        SEAD_ASSERT(0 <= index && index <= length);
        if (out_max_length < i)
        {
            SEAD_ASSERT_MSG(false, "token str exceeds out buffer length[%d]", out_max_length);
            return 0;
        }

        const T& c = this->mString->unsafeAt_(index);
        if (c == cNullChar || mDelimiter.include(c))
            break;

        outc[i] = c;
        ++i;
        ++index;
    }

    outc[i] = cNullChar;
    this->mIndex = index + 1;
    return i;
}

template <typename T>
inline s32 SafeStringBase<T>::token_iterator::cutOffGet(BufferedSafeStringBase<T>* out) const
{
    token_iterator it = *this;
    ++it;
    const s32 part_length = it.getIndex() - this->getIndex() - 1;

    const SafeStringBase<T> part = this->mString->getPart(this->getIndex());
    return out->cutOffCopy(part, part_length);
}

template <typename T>
inline s32 SafeStringBase<T>::token_iterator::cutOffGetAndForward(BufferedSafeStringBase<T>* out)
{
    s32 index = this->mIndex;
    const s32 length = this->mString->calcLength();
    if (index < 0 || index > length)
    {
        SEAD_ASSERT_MSG(false, "index(%d) out of range [0, %d].\n", index, length);
        return 0;
    }

    T* outc = out->getBuffer();
    const s32 out_max_length = out->getBufferSize() - 1;

    s32 i = 0;
    while (true)
    {
        SEAD_ASSERT(0 <= index && index <= length);

        const T& c = this->mString->unsafeAt_(index);
        if (c == cNullChar || mDelimiter.include(c))
            break;

        if (i < out_max_length)
            outc[i++] = c;
        ++index;
    }

    SEAD_ASSERT(i <= out_max_length);
    outc[i] = cNullChar;
    this->mIndex = index + 1;
    return i;
}

template <typename T>
inline const T& SafeStringBase<T>::at(s32 idx) const
{
    const int length = calcLength();
    if (idx < 0 || idx > length)
    {
        SEAD_ASSERT_MSG(false, "index(%d) out of range[0, %d]", idx, length);
        return cNullChar;
    }
    return mStringTop[idx];
}

template <typename T>
inline SafeStringBase<T> SafeStringBase<T>::getPart(s32 at) const
{
    s32 len = calcLength();
    if (at < 0 || at > len)
    {
        SEAD_ASSERT_MSG(false, "index(%d) out of range[0, %d]", at, len);
        return SafeStringBase<T>::cEmptyString;
    }

    return SafeStringBase<T>(mStringTop + at);
}

template <typename T>
inline SafeStringBase<T> SafeStringBase<T>::getPart(const SafeStringBase::iterator& it) const
{
    return getPart(it.getIndex());
}

template <typename T>
inline SafeStringBase<T> SafeStringBase<T>::getPart(const SafeStringBase::token_iterator& it) const
{
    return getPart(it.getIndex());
}

template <typename T>
inline s32 SafeStringBase<T>::calcLength() const
{
    SEAD_ASSERT(mStringTop);
    assureTerminationImpl_();
    s32 length = 0;

    for (;;)
    {
        if (length > cMaximumLength || mStringTop[length] == cNullChar)
            break;

        length++;
    }

    if (length > cMaximumLength)
    {
        SEAD_ASSERT_MSG(false, "too long string");
        return 0;
    }

    return length;
}

template <typename T>
inline bool SafeStringBase<T>::include(const T& c) const
{
    assureTerminationImpl_();
    for (s32 i = 0; i <= cMaximumLength; ++i)
    {
        if (unsafeAt_(i) == cNullChar)
            break;
        if (unsafeAt_(i) == c)
            return true;
    }
    return false;
}

template <typename T>
inline bool SafeStringBase<T>::include(const SafeStringBase<T>& str) const
{
    return findIndex(str) != -1;
}

template <typename T>
inline bool SafeStringBase<T>::isEqual(const SafeStringBase<T>& str) const
{
    assureTerminationImpl_();
    if (cstr() == str.cstr())
        return true;

    for (s32 i = 0; i <= cMaximumLength; i++)
    {
        if (unsafeAt_(i) != str.unsafeAt_(i))
            return false;

        if (unsafeAt_(i) == cNullChar)
            return true;
    }

    SEAD_ASSERT_MSG(false, "too long string\n");
    return false;
}

template <typename T>
inline s32 SafeStringBase<T>::comparen(const SafeStringBase<T>& str, s32 n) const
{
    assureTerminationImpl_();
    const char* top = cstr();
    if (top == str.cstr())
        return 0;

    if (n > cMaximumLength)
    {
        SEAD_ASSERT_MSG(false, "paramater(%d) out of bounds [0, %d]", n, cMaximumLength);
        n = cMaximumLength;
    }

    for (s32 i = 0; i < n; ++i)
    {
        const s32 cmp = unsafeAt_(i) - str.unsafeAt_(i);

        if (cmp != 0)
            return cmp < 0 ? -1 : 1;

        if (unsafeAt_(i) == cNullChar)
            return 0;
    }

    return 0;
}

template <typename T>
inline s32 SafeStringBase<T>::findIndex(const SafeStringBase<T>& str) const
{
    const s32 len = calcLength();
    const s32 sub_str_len = str.calcLength();

    for (s32 i = 0; i <= len - sub_str_len; ++i)
    {
        if (SafeStringBase<T>(&mStringTop[i]).comparen(str, sub_str_len) == 0)
            return i;
    }
    return -1;
}

template <typename T>
inline s32 SafeStringBase<T>::findIndex(const SafeStringBase<T>& str, s32 start_pos) const
{
    const s32 len = calcLength();

    if (start_pos < 0 || start_pos > len)
    {
        SEAD_ASSERT_MSG(false, "start_pos(%d) out of range[0, %d]", start_pos, len);
        return -1;
    }

    const s32 sub_str_len = str.calcLength();

    for (s32 i = start_pos; i <= len - sub_str_len; ++i)
    {
        if (SafeStringBase<T>(&mStringTop[i]).comparen(str, sub_str_len) == 0)
            return i;
    }
    return -1;
}

template <typename T>
inline s32 SafeStringBase<T>::rfindIndex(const SafeStringBase<T>& str) const
{
    const s32 len = calcLength();
    const s32 sub_str_len = str.calcLength();

    for (s32 i = len - sub_str_len; i >= 0; --i)
    {
        if (SafeStringBase<T>(&mStringTop[i]).comparen(str, sub_str_len) == 0)
            return i;
    }
    return -1;
}

template <typename T>
inline bool SafeStringBase<T>::isEmpty() const
{
    return unsafeAt_(0) == cNullChar;
}

template <typename T>
inline bool SafeStringBase<T>::startsWith(const SafeStringBase<T>& prefix) const
{
    const T* strc = mStringTop;
    const T* prefixc = prefix.mStringTop;
    s32 i = 0;
    while (prefixc[i] != cNullChar)
    {
        if (strc[i] != prefixc[i])
            return false;
        ++i;
    }
    return true;
}

template <typename T>
inline bool SafeStringBase<T>::endsWith(const SafeStringBase<T>& suffix) const
{
    const s32 sub_str_len = suffix.calcLength();
    if (sub_str_len == 0)
        return true;

    const T* strc = mStringTop;
    const T* suffixc = suffix.mStringTop;

    const s32 len = calcLength();
    if (len < sub_str_len)
        return false;

    for (s32 i = 0; i < sub_str_len; ++i)
    {
        if (strc[len - sub_str_len + i] != suffixc[i])
            return false;
    }
    return true;
}

template <typename T>
inline const T& BufferedSafeStringBase<T>::operator[](s32 idx) const
{
    if (idx >= 0 && idx < this->mBufferSize)
        return this->mStringTop[idx];

    SEAD_ASSERT_MSG(false, "index(%d) out of range[0, %d]", idx, this->mBufferSize - 1);
    return this->cNullChar;
}

template <typename T>
inline s32 BufferedSafeStringBase<T>::copy(const SafeStringBase<T>& src, s32 copyLength)
{
    T* dst = getMutableStringTop_();
    const T* csrc = src.cstr();
    if (dst == csrc)
        return 0;

    if (copyLength < 0)
        copyLength = src.calcLength();

    if (copyLength >= mBufferSize)
    {
        SEAD_ASSERT_MSG(false, "Buffer overflow. (Buffer Size: %d, Copy Size: %d)", mBufferSize,
                        copyLength);
        copyLength = mBufferSize - 1;
    }

    MemUtil::copy(dst, csrc, copyLength * sizeof(T));
    dst[copyLength] = SafeStringBase<T>::cNullChar;

    return copyLength;
}

template <typename T>
inline s32 BufferedSafeStringBase<T>::copyAt(s32 at, const SafeStringBase<T>& src, s32 copyLength)
{
    T* dst = getMutableStringTop_();
    s32 len = this->calcLength();

    if (at < 0)
    {
        at = len + at + 1;
        if (at < 0)
        {
            SEAD_ASSERT_MSG(false, "at(%d) out of range[0, %d]", at, len);
            at = 0;
        }
    }

    if (copyLength < 0)
        copyLength = src.calcLength();

    if (copyLength >= mBufferSize - at)
    {
        SEAD_ASSERT_MSG(false, "Buffer overflow. (Buffer Size: %d, At: %d, Copy Length: %d)",
                        mBufferSize, at, copyLength);
        copyLength = mBufferSize - at - 1;
    }

    if (copyLength <= 0)
        return 0;

    MemUtil::copy(dst + at, src.cstr(), copyLength * sizeof(T));
    if (at + copyLength > len)
        dst[at + copyLength] = SafeStringBase<T>::cNullChar;

    return copyLength;
}

template <typename T>
inline s32 BufferedSafeStringBase<T>::cutOffCopy(const SafeStringBase<T>& src, s32 copyLength)
{
    T* dst = getMutableStringTop_();
    const T* csrc = src.cstr();
    if (dst == csrc)
        return 0;

    if (copyLength < 0)
        copyLength = src.calcLength();

    if (copyLength >= mBufferSize)
        copyLength = mBufferSize - 1;

    MemUtil::copy(dst, csrc, copyLength * sizeof(T));
    dst[copyLength] = SafeStringBase<T>::cNullChar;

    return copyLength;
}

template <typename T>
inline s32 BufferedSafeStringBase<T>::cutOffCopyAt(s32 at, const SafeStringBase<T>& src,
                                                   s32 copyLength)
{
    T* dst = getMutableStringTop_();
    s32 len = this->calcLength();

    if (at < 0)
    {
        at = len + at + 1;
        if (at < 0)
            at = 0;
    }

    if (copyLength < 0)
        copyLength = src.calcLength();

    if (copyLength >= mBufferSize - at)
        copyLength = mBufferSize - at - 1;

    if (copyLength <= 0)
        return 0;

    MemUtil::copy(dst + at, src.cstr(), copyLength * sizeof(T));
    if (at + copyLength > len)
        dst[at + copyLength] = SafeStringBase<T>::cNullChar;

    return copyLength;
}

template <typename T>
inline s32 BufferedSafeStringBase<T>::copyAtWithTerminate(s32 at, const SafeStringBase<T>& src,
                                                          s32 copyLength)
{
    T* dst = getMutableStringTop_();

    if (at < 0)
    {
        const s32 len = this->calcLength();
        at = len + at + 1;
        if (at < 0)
        {
            SEAD_ASSERT_MSG(false, "at(%d) out of range[0, %d]", at, len);
            at = 0;
        }
    }

    if (copyLength < 0)
        copyLength = src.calcLength();

    if (copyLength >= mBufferSize - at)
    {
        SEAD_ASSERT_MSG(false, "Buffer overflow. (Buffer Size: %d, At: %d, Copy Length: %d)",
                        mBufferSize, at, copyLength);
        copyLength = mBufferSize - at - 1;
    }

    if (copyLength <= 0)
        return 0;

    MemUtil::copy(dst + at, src.cstr(), copyLength * sizeof(T));
    dst[at + copyLength] = SafeStringBase<T>::cNullChar;

    return copyLength;
}

template <typename T>
inline s32 BufferedSafeStringBase<T>::append(const SafeStringBase<T>& str, s32 append_length)
{
    return copyAt(-1, str, append_length);
}

template <typename T>
inline s32 BufferedSafeStringBase<T>::append(T c, s32 num)
{
    if (num < 0)
    {
        SEAD_ASSERT_MSG(false, "append error. num < 0, num = %d", num);
        return 0;
    }

    if (num < 1)
        return 0;

    const s32 length = this->calcLength();

    if (getBufferSize() - length <= num)
    {
        SEAD_ASSERT_MSG(false, "Buffer overflow. (Buffer Size: %d, Length: %d, Num: %d)",
                        getBufferSize(), length, num);
        num = getBufferSize() - length - 1;
    }

    T* top = getMutableStringTop_();
    for (s32 i = 0; i < num; ++i)
        top[length + i] = c;

    top[num + length] = this->cNullChar;
    return num;
}

template <typename T>
s32 BufferedSafeStringBase<T>::prepend(const SafeStringBase<T>& str, s32 prepend_length)
{
    if (prepend_length == -1)
        prepend_length = str.calcLength();

    s32 length = this->calcLength();
    T* buffer = getMutableStringTop_();
    const s32 buffer_size = mBufferSize;

    if (prepend_length >= buffer_size - length)
    {
        SEAD_ASSERT_MSG(false, "Buffer overflow. (Buffer Size: %d, Length: %d, Prepend Length: %d)",
                        buffer_size, length, prepend_length);
        if (prepend_length >= buffer_size)
            prepend_length = buffer_size - 1;
        length = buffer_size + (-prepend_length - 1);
    }

    MemUtil::copyOverlap(&buffer[prepend_length], buffer, length * sizeof(T));
    MemUtil::copy(buffer, str.cstr(), prepend_length * sizeof(T));
    buffer[length + prepend_length] = SafeStringBase<T>::cNullChar;
    return length + prepend_length;
}

// UNCHECKED
template <typename T>
inline s32 BufferedSafeStringBase<T>::chop(s32 chop_num)
{
    s32 length = this->calcLength();
    T* buffer = getMutableStringTop_();
    const auto fail = [=] {
        SEAD_ASSERT_MSG(false, "chop_num(%d) out of range[0, %d]", chop_num, length);
    };

    if (chop_num < 0)
    {
        fail();
        return 0;
    }

    if (chop_num > length)
    {
        fail();
        chop_num = length;
    }

    const s32 new_length = length - chop_num;
    buffer[new_length] = SafeStringBase<T>::cNullChar;
    return chop_num;
}

// UNCHECKED
template <typename T>
inline s32 BufferedSafeStringBase<T>::chopMatchedChar(T c)
{
    const s32 length = this->calcLength();
    if (length < 1)
        return 0;

    const s32 new_length = length - 1;
    T* buffer = getMutableStringTop_();
    if (buffer[new_length] == c)
    {
        buffer[new_length] = SafeStringBase<T>::cNullChar;
        return 1;
    }

    return 0;
}

// UNCHECKED
template <typename T>
inline s32 BufferedSafeStringBase<T>::chopMatchedChar(const T* characters)
{
    const s32 length = this->calcLength();
    if (length < 1)
        return 0;

    T* buffer = getMutableStringTop_();
    for (const T* it = characters; *it; ++it)
    {
        if (buffer[length - 1] == *it)
        {
            buffer[length - 1] = SafeStringBase<T>::cNullChar;
            return 1;
        }
    }

    return 0;
}

// UNCHECKED
template <typename T>
inline s32 BufferedSafeStringBase<T>::chopUnprintableAsciiChar()
{
    const s32 length = this->calcLength();
    if (length < 1)
        return 0;

    T* buffer = getMutableStringTop_();
    if (buffer[length - 1] <= ' ' || buffer[length - 1] == 0x7F)
    {
        buffer[length - 1] = this->cNullChar;
        return 1;
    }

    return 0;
}

// UNCHECKED
template <typename T>
inline s32 BufferedSafeStringBase<T>::rstrip(const T* characters)
{
    const s32 length = this->calcLength();
    if (length <= 0)
        return 0;

    T* buffer = getMutableStringTop_();
    s32 new_length = length;
    const auto should_strip = [characters, buffer](s32 idx) {
        for (auto it = characters; *it; ++it)
        {
            if (buffer[idx] == *it)
                return true;
        }
        return false;
    };
    while (new_length >= 1 && should_strip(new_length - 1))
        --new_length;

    if (length <= new_length)
        return 0;

    buffer[new_length] = SafeStringBase<T>::cNullChar;
    return length - new_length;
}

// UNCHECKED
template <typename T>
inline s32 BufferedSafeStringBase<T>::rstripUnprintableAsciiChars()
{
    const s32 length = this->calcLength();
    if (length < 1)
        return 0;

    T* buffer = getMutableStringTop_();
    s32 new_length = length;
    while (new_length && (buffer[new_length - 1] <= 0x20 || buffer[new_length - 1] == 0x7F))
        --new_length;

    if (length <= new_length)
        return 0;

    buffer[new_length] = this->cNullChar;
    return length - new_length;
}

template <typename T>
inline s32 BufferedSafeStringBase<T>::trim(s32 trim_length)
{
    T* mutableString = getMutableStringTop_();

    if (trim_length >= mBufferSize)
    {
        SEAD_ASSERT_MSG(false, "trim_length(%d) out of bounds.  [0, %d)", trim_length, mBufferSize);
        return this->calcLength();
    }

    if (trim_length < 0)
    {
        SEAD_ASSERT_MSG(false, "trim_length(%d) out of bounds.  [0, %d)", trim_length, mBufferSize);
        trim_length = 0;
    }

    mutableString[trim_length] = SafeStringBase<T>::cNullChar;
    return trim_length;
}

template <typename T>
inline s32 calcStrLength_(const T* str)
{
    s32 len = 0;
    while (str[len])
        ++len;
    return len;
}

template <typename T>
inline s32 BufferedSafeStringBase<T>::trimMatchedString(const SafeStringBase<T>& suffix)
{
    const s32 length = this->calcLength();
    T* buffer = getMutableStringTop_();

    const s32 suffix_length = suffix.calcLength();
    const s32 new_length = length - suffix_length;

    if (length < suffix_length)
        return length;

    if (SafeStringBase<T>(&buffer[new_length]).comparen(suffix, suffix_length) != 0)
        return length;

    buffer[new_length] = SafeStringBase<T>::cNullChar;
    return new_length;
}

// UNCHECKED
template <typename T>
inline s32 BufferedSafeStringBase<T>::replaceChar(T old_char, T new_char)
{
    const s32 length = this->calcLength();
    T* buffer = getMutableStringTop_();

    s32 replaced_count = 0;
    for (s32 i = 0; i < length; ++i)
    {
        if (buffer[i] == old_char)
        {
            ++replaced_count;
            buffer[i] = new_char;
        }
    }
    return replaced_count;
}

template <typename T>
inline s32 BufferedSafeStringBase<T>::replaceCharList(const SafeStringBase<T>& old_chars,
                                                      const SafeStringBase<T>& new_chars)
{
    const s32 length = this->calcLength();
    T* buffer = getMutableStringTop_();

    s32 old_chars_len = old_chars.calcLength();
    const s32 new_chars_len = new_chars.calcLength();

    if (old_chars_len != new_chars_len)
    {
        // yes, this is undefined behavior for T = char16. Nintendo, fix your code
        SEAD_ASSERT_MSG(false, "old_chars(%s).length is not equal to new_chars(%s).length.",
                        old_chars.cstr(), new_chars.cstr());
        if (old_chars_len > new_chars_len)
            old_chars_len = new_chars_len;
    }

    const T* old_chars_c = old_chars.cstr();
    const T* new_chars_c = new_chars.cstr();

    s32 replaced_count = 0;
    for (s32 i = 0; i < length; ++i)
    {
        for (s32 character_idx = 0; character_idx < old_chars_len; ++character_idx)
        {
            if (buffer[i] == old_chars_c[character_idx])
            {
                ++replaced_count;
                buffer[i] = new_chars_c[character_idx];
                break;
            }
        }
    }
    return replaced_count;
}

template <typename T>
inline s32 BufferedSafeStringBase<T>::setReplaceString(const SafeStringBase<T>& target_str,
                                                       const SafeStringBase<T>& old_str,
                                                       const SafeStringBase<T>& new_str)
{
    bool is_buffer_overflow = false;
    const s32 ret =
        replaceStringImpl_(getMutableStringTop_(), nullptr, getBufferSize(), target_str.cstr(),
                           target_str.calcLength(), old_str, new_str, &is_buffer_overflow);
    SEAD_ASSERT_MSG(!is_buffer_overflow, "Buffer overflow! (%s : s/%s/%s/g, Buffer Size: %d )",
                    target_str.cstr(), old_str.cstr(), new_str.cstr(), getBufferSize());
    return ret;
}

template <typename T>
inline s32 BufferedSafeStringBase<T>::replaceString(const SafeStringBase<T>& old_str,
                                                    const SafeStringBase<T>& new_str)
{
    bool is_buffer_overflow = false;
    const s32 ret =
        replaceStringImpl_(getMutableStringTop_(), nullptr, getBufferSize(), this->cstr(),
                           this->calcLength(), old_str, new_str, &is_buffer_overflow);
    SEAD_ASSERT_MSG(!is_buffer_overflow,
                    "Buffer overflow! (%s(replacing) : s/%s/%s/g, Buffer Size: %d )", this->cstr(),
                    old_str.cstr(), new_str.cstr(), getBufferSize());
    return ret;
}

template <typename T>
template <typename OtherType>
inline s32 BufferedSafeStringBase<T>::convertFromOtherType_(const SafeStringBase<OtherType>& src,
                                                            s32 src_size)
{
    s32 copy_size = src.calcLength();

    if (src_size != -1)
    {
        if (src_size < 0)
        {
            SEAD_ASSERT_MSG(false, "src_size(%d) out of bounds [%d,%d]", src_size, 0, copy_size);
            copy_size = 0;
            return copy_size;
        }
        if (copy_size < src_size)
            SEAD_ASSERT_MSG(false, "src_size(%d) out of bounds [%d,%d]", src_size, 0, copy_size);
        else
            copy_size = src_size;
    }

    if (getBufferSize() <= copy_size)
    {
        SEAD_ASSERT_MSG(false, "copy_size(%d) out of bounds[%d, %d)", copy_size, 0,
                        getBufferSize());
        copy_size = getBufferSize() - 1;
    }

    T* raw_dst = getMutableStringTop_();
    const OtherType* raw_src = src.cstr();

    for (s32 i = 0; i < copy_size; ++i)
        raw_dst[i] = raw_src[i];

    raw_dst[copy_size] = this->cNullChar;
    return copy_size;
}

template <typename T>
inline s32 BufferedSafeStringBase<T>::convertFromMultiByteString(const SafeStringBase<char>& str,
                                                                 s32 str_length)
{
    if constexpr (std::is_same<char, T>())
        return copy(str, str_length);
    else
        return convertFromOtherType_(str, str_length);
}

template <typename T>
inline s32 BufferedSafeStringBase<T>::convertFromWideCharString(const SafeStringBase<char16>& str,
                                                                s32 str_length)
{
    if constexpr (std::is_same<char16, T>())
        return copy(str, str_length);
    else
        return convertFromOtherType_(str, str_length);
}

}  // namespace sead
