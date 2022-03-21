#include "prim/seadStringBuilder.h"
#include "heap/seadHeapMgr.h"
#include "math/seadMathCalcCommon.h"
#include "prim/seadPtrUtil.h"
#include "prim/seadStringUtil.h"

namespace sead
{
template <>
StringBuilder* StringBuilder::create(s32 buffer_size, Heap* heap, s32 alignment)
{
    return createImpl_(buffer_size, heap, alignment);
}

template <>
WStringBuilder* WStringBuilder::create(s32 buffer_size, Heap* heap, s32 alignment)
{
    return createImpl_(buffer_size, heap, alignment);
}

template <typename T>
StringBuilderBase<T>* StringBuilderBase<T>::create(const T* str, Heap* heap, s32 alignment)
{
    const s32 len = calcStrLength_(str);
    auto* builder = createImpl_(len + 1, heap, alignment);
    builder->copy(str, len);
    return builder;
}

template StringBuilder* StringBuilder::create(const char* str, Heap* heap, s32 alignment);
template WStringBuilder* WStringBuilder::create(const char16* str, Heap* heap, s32 alignment);

template <typename T>
StringBuilderBase<T>* StringBuilderBase<T>::createImpl_(s32 buffer_size, Heap* heap, s32 alignment)
{
    if (buffer_size <= 0)
    {
        SEAD_ASSERT_MSG(false, "buffer_size[%d] must be larger than 0", buffer_size);
        return nullptr;
    }

    if (!heap)
        heap = HeapMgr::instance()->getCurrentHeap();

    if (alignment > s32(alignof(StringBuilderBase<T>)))
    {
        const s32 buffer_offset = Mathi::roundUpPow2(sizeof(StringBuilderBase<T>), alignment);
        void* buffer = heap->alloc(buffer_offset + buffer_size * sizeof(T), alignment);
        return new (buffer) StringBuilderBase<T>(
            static_cast<T*>(PtrUtil::addOffset(buffer, buffer_offset)), buffer_size);
    }
    else
    {
        void* buffer = heap->alloc(buffer_size * sizeof(T) + sizeof(StringBuilderBase<T>),
                                   alignof(StringBuilderBase<T>));
        return new (buffer) StringBuilderBase<T>(
            static_cast<T*>(PtrUtil::addOffset(buffer, sizeof(StringBuilderBase<T>))), buffer_size);
    }
}

template <typename T>
bool StringBuilderBase<T>::endsWith(const T* suffix) const
{
    const s32 sub_str_len = calcStrLength_(suffix);
    if (sub_str_len == 0)
        return true;

    const T* strc = mBuffer;

    const s32 len = calcLength();
    if (len < sub_str_len)
        return false;

    for (s32 i = 0; i < sub_str_len; ++i)
    {
        if (strc[len - sub_str_len + i] != suffix[i])
            return false;
    }
    return true;
}

template bool StringBuilder::endsWith(const char* suffix) const;
template bool WStringBuilder::endsWith(const char16* suffix) const;

template <typename T>
s32 StringBuilderBase<T>::copy(const T* src, s32 copy_length)
{
    T* dst = mBuffer;
    const s32 buffer_size = mBufferSize;
    SEAD_ASSERT_MSG(src, "str must not be null");
    if (dst == src)
        return 0;

    if (copy_length == -1)
        copy_length = calcStrLength_(src);

    if (copy_length >= buffer_size)
    {
        SEAD_ASSERT_MSG(false, "Buffer overflow. (Buffer Size: %d, Copy Size: %d)", buffer_size,
                        copy_length);
        copy_length = buffer_size - 1;
    }

    if (copy_length >= 1)
    {
        MemUtil::copy(dst, src, copy_length * sizeof(T));
        dst[copy_length] = SafeStringBase<T>::cNullChar;
    }
    else
    {
        copy_length = 0;
        *dst = SafeStringBase<T>::cNullChar;
    }

    mLength = copy_length;
    return copy_length;
}

template s32 StringBuilder::copy(const char* src, s32 copy_length);
template s32 WStringBuilder::copy(const char16* src, s32 copy_length);

template <typename T>
s32 StringBuilderBase<T>::copyAt(s32 at_, const T* src, s32 copy_length)
{
    T* dst = getMutableStringTop_();
    const s32 buffer_size = mBufferSize;

    SEAD_ASSERT_MSG(src, "str must not be null");

    if (copy_length == -1)
        copy_length = calcStrLength_(src);

    s32 len = this->calcLength();
    s32 at = at_;
    if (at_ < 0)
    {
        const s32 at_new = len + at_ + 1;
        if (at_new < 0)
        {
            SEAD_ASSERT_MSG(false, "at(%d) out of range[%d, %d]", at_, -len - 1, len);
            at = 0;
            goto check_buffer_overflow;
        }
        at = at_new;
    }

    if (len < at)
    {
        SEAD_ASSERT_MSG(false, "at(%d) out of range[%d, %d]", at_, -len - 1, len);
        copy_length = 0;
        return copy_length;
    }

check_buffer_overflow:
    if (at + copy_length >= buffer_size)
    {
        SEAD_ASSERT_MSG(false, "Buffer overflow. (Buffer Size: %d, At: %d, Copy Length: %d)",
                        buffer_size, at, copy_length);
        copy_length = buffer_size - at - 1;
    }

    if (copy_length < 1)
        return 0;

    MemUtil::copy(dst + at, src, copy_length * sizeof(T));
    if (mLength < at + copy_length)
        dst[at + copy_length] = SafeStringBase<T>::cNullChar;

    if (mLength < at + copy_length)
        mLength = at + copy_length;
    return copy_length;
}

template s32 StringBuilder::copyAt(s32 at, const char* src, s32 copy_length);
template s32 WStringBuilder::copyAt(s32 at, const char16* src, s32 copy_length);

template <typename T>
s32 StringBuilderBase<T>::cutOffCopy(const T* src, s32 copy_length)
{
    T* dst = mBuffer;
    const s32 buffer_size = mBufferSize;
    SEAD_ASSERT_MSG(src, "str must not be null");
    if (dst == src)
        return 0;

    if (copy_length == -1)
        copy_length = calcStrLength_(src);

    if (copy_length >= buffer_size)
        copy_length = buffer_size - 1;

    if (copy_length >= 1)
    {
        MemUtil::copy(dst, src, copy_length * sizeof(T));
        dst[copy_length] = SafeStringBase<T>::cNullChar;
    }
    else
    {
        copy_length = 0;
        *dst = SafeStringBase<T>::cNullChar;
    }

    mLength = copy_length;
    return copy_length;
}

template s32 StringBuilder::cutOffCopy(const char* src, s32 copy_length);
template s32 WStringBuilder::cutOffCopy(const char16* src, s32 copy_length);

template <typename T>
s32 StringBuilderBase<T>::cutOffCopyAt(s32 at_, const T* src, s32 copy_length)
{
    T* dst = getMutableStringTop_();
    const s32 buffer_size = mBufferSize;

    SEAD_ASSERT_MSG(src, "str must not be null");

    if (copy_length == -1)
        copy_length = calcStrLength_(src);

    s32 len = this->calcLength();
    s32 at = at_;
    if (at_ < 0)
    {
        const s32 at_new = len + at_ + 1;
        if (at_new < 0)
        {
            SEAD_ASSERT_MSG(false, "at(%d) out of range[%d, %d]", at_, -len - 1, len);
            at = 0;
            goto check_buffer_overflow;
        }
        at = at_new;
    }

    if (len < at)
    {
        SEAD_ASSERT_MSG(false, "at(%d) out of range[%d, %d]", at_, -len - 1, len);
        copy_length = 0;
        return copy_length;
    }

check_buffer_overflow:
    if (at + copy_length >= buffer_size)
        copy_length = buffer_size - at - 1;

    if (copy_length < 1)
        return 0;

    MemUtil::copy(dst + at, src, copy_length * sizeof(T));
    if (mLength < at + copy_length)
        dst[at + copy_length] = SafeStringBase<T>::cNullChar;

    if (mLength < at + copy_length)
        mLength = at + copy_length;
    return copy_length;
}

template s32 StringBuilder::cutOffCopyAt(s32 at, const char* src, s32 copy_length);
template s32 WStringBuilder::cutOffCopyAt(s32 at, const char16* src, s32 copy_length);

template <typename T>
s32 StringBuilderBase<T>::copyAtWithTerminate(s32 at_, const T* src, s32 copy_length)
{
    T* dst = getMutableStringTop_();
    const s32 buffer_size = mBufferSize;

    SEAD_ASSERT_MSG(src, "str must not be null");

    if (copy_length == -1)
        copy_length = calcStrLength_(src);

    s32 len = this->calcLength();
    s32 at = at_;
    if (at_ < 0)
    {
        const s32 at_new = len + at_ + 1;
        if (at_new < 0)
        {
            SEAD_ASSERT_MSG(false, "at(%d) out of range[%d, %d]", at_, -len - 1, len);
            at = 0;
            goto check_buffer_overflow;
        }
        at = at_new;
    }

    if (len < at)
    {
        SEAD_ASSERT_MSG(false, "at(%d) out of range[%d, %d]", at_, -len - 1, len);
        copy_length = 0;
        return copy_length;
    }

check_buffer_overflow:
    if (at + copy_length >= buffer_size)
    {
        SEAD_ASSERT_MSG(false, "Buffer overflow. (Buffer Size: %d, At: %d, Copy Length: %d)",
                        buffer_size, at, copy_length);
        copy_length = buffer_size - at - 1;
    }

    if (copy_length < 1)
        return 0;

    MemUtil::copy(dst + at, src, copy_length * sizeof(T));
    dst[at + copy_length] = SafeStringBase<T>::cNullChar;

    if (at <= mLength)
        mLength = at + copy_length;
    return copy_length;
}

template s32 StringBuilder::copyAtWithTerminate(s32 at, const char* src, s32 copy_length);
template s32 WStringBuilder::copyAtWithTerminate(s32 at, const char16* src, s32 copy_length);

template <typename T>
s32 StringBuilderBase<T>::format(const T* format, ...)
{
    std::va_list args;
    va_start(args, format);
    s32 ret = formatV(format, args);
    va_end(args);
    return ret;
}

template s32 StringBuilder::format(const char* format, ...);
template s32 WStringBuilder::format(const char16* format, ...);

template <>
s32 StringBuilder::formatImpl_(char* s, s32 n, const char* format, va_list args)
{
    const s32 ret = StringUtil::vsnprintf(s, n, format, args);
    return ret < 0 ? n - 1 : ret;
}

template <>
s32 WStringBuilder::formatImpl_(char16* s, s32 n, const char16* format, va_list args)
{
    const s32 ret = StringUtil::vsnw16printf(s, n, format, args);
    if (ret >= 0 && ret < n)
        return ret;
    s[n - 1] = WSafeString::cNullChar;
    return n - 1;
}

template <typename T>
s32 StringBuilderBase<T>::appendWithFormat(const T* format, ...)
{
    std::va_list args;
    va_start(args, format);
    const s32 ret = appendWithFormatV(format, args);
    va_end(args);
    return ret;
}

template s32 StringBuilder::appendWithFormat(const char* format, ...);
template s32 WStringBuilder::appendWithFormat(const char16* format, ...);

template <typename T>
s32 StringBuilderBase<T>::append(const T* str, s32 append_length)
{
    T* dst = getMutableStringTop_();
    const s32 buffer_size = mBufferSize;

    SEAD_ASSERT_MSG(str, "str must not be null");

    if (append_length == -1)
        append_length = calcStrLength_(str);

    const s32 at = this->calcLength();

    if (at + append_length >= buffer_size)
    {
        SEAD_ASSERT_MSG(false, "Buffer overflow. (Buffer Size: %d, At: %d, Str Length: %d)",
                        buffer_size, at, append_length);
        append_length = buffer_size - at - 1;
    }

    if (append_length < 1)
        return 0;

    MemUtil::copy(dst + at, str, append_length * sizeof(T));
    dst[at + append_length] = SafeStringBase<T>::cNullChar;

    mLength = at + append_length;
    return append_length;
}

template s32 StringBuilder::append(const char* str, s32 append_length);
template s32 WStringBuilder::append(const char16* str, s32 append_length);

// NON_MATCHING: regalloc differences
template <typename T>
s32 appendImpl_(T* buffer_, s32* length_, const s32 buffer_size_, T c, s32 num)
{
    const s32 length = *length_;

    if (buffer_size_ <= num + length)
    {
        SEAD_ASSERT_MSG(false, "Buffer overflow. (Buffer Size: %d, Length: %d, Num: %d)",
                        buffer_size_, length, num);
        num = buffer_size_ - length - 1;
    }

    for (s32 i = 0; i < num; ++i)
        buffer_[length + i] = c;

    buffer_[length + num] = SafeStringBase<T>::cNullChar;
    *length_ = length + num;
    return num;
}

template <typename T>
s32 StringBuilderBase<T>::append(T c, s32 num)
{
    if (num < 0)
    {
        SEAD_ASSERT_MSG(false, "append error. num < 0, num = %d", num);
        return 0;
    }

    if (num == 0)
        return 0;

    return appendImpl_(mBuffer, &mLength, mBufferSize, c, num);
}

template s32 StringBuilder::append(char c, s32 n);
template s32 WStringBuilder::append(char16 c, s32 n);

template <typename T>
s32 StringBuilderBase<T>::chop(s32 chop_num)
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
        length = mLength;
        chop_num = mLength;
    }

    const s32 new_length = length - chop_num;
    buffer[new_length] = SafeStringBase<T>::cNullChar;
    mLength = new_length;
    return chop_num;
}

template s32 StringBuilder::chop(s32 chop_num);
template s32 WStringBuilder::chop(s32 chop_num);

template <typename T>
s32 StringBuilderBase<T>::chopMatchedChar(T c)
{
    const s32 length = this->calcLength();
    if (length < 1)
        return 0;

    const s32 new_length = length - 1;
    if (mBuffer[new_length] == c)
    {
        mBuffer[new_length] = SafeStringBase<T>::cNullChar;
        mLength = new_length;
        return 1;
    }

    return 0;
}

template s32 StringBuilder::chopMatchedChar(char c);
template s32 WStringBuilder::chopMatchedChar(char16 c);

template <typename T>
s32 StringBuilderBase<T>::chopMatchedChar(const T* characters)
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
            mLength = length - 1;
            return 1;
        }
    }

    return 0;
}

template s32 StringBuilder::chopMatchedChar(const char* characters);
template s32 WStringBuilder::chopMatchedChar(const char16* characters);

template <typename T>
s32 StringBuilderBase<T>::chopUnprintableAsciiChar()
{
    const s32 length = this->calcLength();
    if (length < 1)
        return 0;

    const s32 new_length = length - 1;
    if (mBuffer[new_length] <= ' ' || mBuffer[new_length] == 0x7F)
    {
        mBuffer[new_length] = SafeStringBase<T>::cNullChar;
        mLength = new_length;
        return 1;
    }

    return 0;
}

template s32 StringBuilder::chopUnprintableAsciiChar();
template s32 WStringBuilder::chopUnprintableAsciiChar();

template <typename T>
s32 StringBuilderBase<T>::rstrip(const T* characters)
{
    const s32 length = this->calcLength();
    if (length <= 0)
        return 0;

    T* buffer = mBuffer;
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

    mBuffer[new_length] = SafeStringBase<T>::cNullChar;
    mLength = new_length;
    return length - new_length;
}

template s32 StringBuilder::rstrip(const char* characters);
template s32 WStringBuilder::rstrip(const char16* characters);

// NON_MATCHING: equivalent, two instruction reorders
template <typename T>
s32 StringBuilderBase<T>::rstripUnprintableAsciiChars()
{
    const s32 length = this->calcLength();
    if (length <= 0)
        return 0;

    T* buffer = mBuffer;
    s32 new_length = length;
    while (new_length >= 1 && (buffer[new_length - 1] <= 0x20 || buffer[new_length - 1] == 0x7F))
        --new_length;

    if (length <= new_length)
        return 0;

    const s32 ret = length - new_length;
    mBuffer[new_length] = SafeStringBase<T>::cNullChar;
    mLength = new_length;
    return ret;
}

template s32 StringBuilder::rstripUnprintableAsciiChars();
template s32 WStringBuilder::rstripUnprintableAsciiChars();

template <typename T>
s32 StringBuilderBase<T>::trim(s32 trim_length)
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
    if (trim_length < mLength)
        mLength = trim_length;
    return trim_length;
}

template s32 StringBuilder::trim(s32 trim_length);
template s32 WStringBuilder::trim(s32 trim_length);

template <typename T>
s32 StringBuilderBase<T>::trimMatchedString(const T* str)
{
    T* buffer = getMutableStringTop_();
    const s32 length = this->calcLength();

    const s32 trim_str_length = calcStrLength_(str);
    const s32 new_length = length - trim_str_length;

    if (length < trim_str_length)
        return length;

    T* substring = &buffer[new_length];
    for (s32 i = 0; i < trim_str_length; ++i)
    {
        if (substring[i] != str[i])
            return length;
    }

    buffer[new_length] = SafeStringBase<T>::cNullChar;
    mLength = new_length;
    return new_length;
}

template s32 StringBuilder::trimMatchedString(const char* str);
template s32 WStringBuilder::trimMatchedString(const char16* str);

template <typename T>
s32 StringBuilderBase<T>::replaceChar(T old_char, T new_char)
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

template s32 StringBuilder::replaceChar(char old_char, char new_char);
template s32 WStringBuilder::replaceChar(char16 old_char, char16 new_char);

template <typename T>
s32 StringBuilderBase<T>::replaceCharList(const SafeStringBase<T>& old_chars,
                                          const SafeStringBase<T>& new_chars)
{
    T* buffer = getMutableStringTop_();
    const s32 length = this->calcLength();

    s32 old_chars_len = old_chars.calcLength();
    const s32 new_chars_len = new_chars.calcLength();

    if (old_chars_len != new_chars_len)
    {
        // Nintendo's code just uses the same format string for both T = char and T = char16_t,
        // which is undefined behavior and produces annoying format warnings, so let's fix it...
        if constexpr (std::is_same<T, char>())
        {
            SEAD_ASSERT_MSG(false, "old_chars(%s).length is not equal to new_chars(%s).length.",
                            old_chars.cstr(), new_chars.cstr());
        }
        else if constexpr (std::is_same<T, char16>())
        {
            // There is no standard format specifier for char16_t strings :/
            SEAD_ASSERT_MSG(false, "old_chars(%p).length is not equal to new_chars(%p).length.",
                            old_chars.cstr(), new_chars.cstr());
        }
        if (old_chars_len > new_chars_len)
            old_chars_len = new_chars_len;
    }

    const T* old_chars_c = old_chars.cstr();
    const T* new_chars_c = new_chars.cstr();

    if (length < 1)
        return 0;

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

template s32 StringBuilder::replaceCharList(const SafeString& old_chars,
                                            const SafeString& new_chars);
template s32 WStringBuilder::replaceCharList(const WSafeString& old_chars,
                                             const WSafeString& new_chars);

template <typename T>
template <typename OtherType>
s32 StringBuilderBase<T>::convertFromOtherType_(const OtherType* src, s32 src_size)
{
    T* dst = mBuffer;
    const s32 buffer_size = mBufferSize;
    SEAD_ASSERT_MSG(src, "str must not be null");

    s32 copy_size = src_size;
    if (src_size == -1)
        copy_size = calcStrLength_(src);

    if (copy_size >= buffer_size)
    {
        SEAD_ASSERT_MSG(false, "str_length(%d) out of bounds. [0, %d) \n", src_size, buffer_size);
        copy_size = buffer_size - 1;
    }

    if (copy_size <= 0)
    {
        copy_size = 0;
        *dst = SafeStringBase<T>::cNullChar;
    }
    else
    {
        for (s32 i = 0; i < copy_size; ++i)
            dst[i] = src[i];

        dst[copy_size] = SafeStringBase<T>::cNullChar;
    }
    mLength = copy_size;
    return copy_size;
}

template <typename T>
s32 StringBuilderBase<T>::convertFromMultiByteString(const char* str, s32 str_length)
{
    if constexpr (std::is_same<char, T>())
        return copy(str, str_length);
    else
        return convertFromOtherType_(str, str_length);
}

template <typename T>
s32 StringBuilderBase<T>::convertFromWideCharString(const char16* str, s32 str_length)
{
    if constexpr (std::is_same<char16, T>())
        return copy(str, str_length);
    else
        return convertFromOtherType_(str, str_length);
}

template s32 StringBuilder::convertFromMultiByteString(const char* str, s32 str_length);
template s32 StringBuilder::convertFromWideCharString(const char16* str, s32 str_length);
template s32 WStringBuilder::convertFromMultiByteString(const char* str, s32 str_length);
template s32 WStringBuilder::convertFromWideCharString(const char16* str, s32 str_length);

template <typename T>
s32 StringBuilderBase<T>::cutOffAppend(const T* str, s32 append_length)
{
    T* dst = getMutableStringTop_();
    const s32 buffer_size = mBufferSize;

    SEAD_ASSERT_MSG(str, "str must not be null");

    if (append_length == -1)
        append_length = calcStrLength_(str);

    const s32 at = this->calcLength();

    if (at + append_length >= buffer_size)
        append_length = buffer_size - at - 1;

    if (append_length < 1)
        return 0;

    MemUtil::copy(dst + at, str, append_length * sizeof(T));
    dst[at + append_length] = SafeStringBase<T>::cNullChar;

    mLength = at + append_length;
    return append_length;
}

template s32 StringBuilder::cutOffAppend(const char* str, s32 append_length);
template s32 WStringBuilder::cutOffAppend(const char16* str, s32 append_length);

template <typename T>
s32 StringBuilderBase<T>::cutOffAppend(T c, s32 num)
{
    if (num < 0)
    {
        SEAD_ASSERT_MSG(false, "append error. num < 0, num = %d", num);
        return 0;
    }

    if (num == 0)
        return 0;

    const s32 buffer_size = mBufferSize;
    const s32 length = mLength;

    if (num + length >= buffer_size)
        num = buffer_size - length - 1;

    if (num <= 0)
        return 0;

    T* buffer = mBuffer;
    for (s32 i = 0; i < num; ++i)
        buffer[length + i] = c;

    buffer[length + num] = SafeStringBase<T>::cNullChar;
    mLength = length + num;
    return num;
}

template s32 StringBuilder::cutOffAppend(char c, s32 num);
template s32 WStringBuilder::cutOffAppend(char16 c, s32 num);

// NON_MATCHING: operands to some `add` instructions are swapped
template <typename T>
s32 StringBuilderBase<T>::prepend(const T* str, s32 prepend_length)
{
    T* buffer = getMutableStringTop_();
    const s32 buffer_size = mBufferSize;

    SEAD_ASSERT_MSG(str, "str must not be null");

    if (prepend_length == -1)
        prepend_length = calcStrLength_(str);

    const s32 length = this->calcLength();

    s32 move_length;
    if (prepend_length >= buffer_size - length)
    {
        SEAD_ASSERT_MSG(false, "Buffer overflow. (Buffer Size: %d, Length: %d, Prepend Length: %d)",
                        buffer_size, length, prepend_length);
        if (prepend_length >= buffer_size)
            prepend_length = buffer_size - 1;
        move_length = buffer_size - 1 - prepend_length;
    }
    else
    {
        move_length = mLength;
    }

    void* dest = PtrUtil::addOffset(buffer, prepend_length * sizeof(T));
    MemUtil::copyOverlap(dest, buffer, move_length * sizeof(T));

    MemUtil::copy(buffer, str, prepend_length * sizeof(T));
    buffer[move_length + prepend_length] = SafeStringBase<T>::cNullChar;

    mLength = move_length + prepend_length;
    return move_length + prepend_length - length;
}

template s32 StringBuilder::prepend(const char* str, s32 prepend_length);
template s32 WStringBuilder::prepend(const char16* str, s32 prepend_length);

// NON_MATCHING: same regalloc issue as append()
template <typename T>
s32 StringBuilderBase<T>::prepend(T c, s32 num)
{
    if (num < 0)
    {
        // copy and paste error by Nintendo
        SEAD_ASSERT_MSG(false, "append error. num < 0, num = %d", num);
        return 0;
    }

    if (num == 0)
        return 0;

    const s32 length = mLength;
    const s32 buffer_size = mBufferSize;
    T* buffer = mBuffer;

    s32 move_length = length;
    if (buffer_size - length <= num)
    {
        SEAD_ASSERT_MSG(false, "Buffer overflow. (Buffer Size: %d, Length: %d, Num: %d)",
                        buffer_size, length, num);
        if (buffer_size <= num)
            num = buffer_size - 1;
        move_length = buffer_size - 1 - num;
    }

    MemUtil::copyOverlap(buffer + num, buffer, move_length * sizeof(T));
    for (s32 i = 0; i < num; ++i)
        buffer[i] = c;

    buffer[num + move_length] = SafeStringBase<T>::cNullChar;
    mLength = num + move_length;
    return num + move_length - length;
}

template s32 StringBuilder::prepend(char c, s32 length);
template s32 WStringBuilder::prepend(char16_t c, s32 length);
}  // namespace sead
