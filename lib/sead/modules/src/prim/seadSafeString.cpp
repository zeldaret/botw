#include <prim/seadSafeString.h>
#include <prim/seadStringUtil.h>

namespace
{
static const char16 cEmptyStringChar16[1] = u"";

}  // namespace

namespace sead
{
template <>
const char SafeStringBase<char>::cNullChar = '\0';

template <>
const char SafeStringBase<char>::cLineBreakChar = '\n';

template <>
const SafeStringBase<char> SafeStringBase<char>::cEmptyString("");

template <>
const char16 SafeStringBase<char16>::cNullChar = 0;

template <>
const char16 SafeStringBase<char16>::cLineBreakChar = static_cast<char16>('\n');

template <>
const SafeStringBase<char16> SafeStringBase<char16>::cEmptyString(cEmptyStringChar16);

template <>
SafeStringBase<char>& SafeStringBase<char>::operator=(const SafeStringBase<char>& other) = default;

template <>
SafeStringBase<char16>&
SafeStringBase<char16>::operator=(const SafeStringBase<char16>& other) = default;

template <>
BufferedSafeStringBase<char>&
BufferedSafeStringBase<char>::operator=(const SafeStringBase<char>& other)
{
    copy(other);
    return *this;
}

template <>
BufferedSafeStringBase<char16>&
BufferedSafeStringBase<char16>::operator=(const SafeStringBase<char16>& other)
{
    copy(other);
    return *this;
}

template <>
HeapSafeStringBase<char>& HeapSafeStringBase<char>::operator=(const SafeStringBase<char>& other)
{
    this->copy(other);
    return *this;
}

template <>
HeapSafeStringBase<char16>&
HeapSafeStringBase<char16>::operator=(const SafeStringBase<char16>& other)
{
    this->copy(other);
    return *this;
}

template <>
void BufferedSafeStringBase<char>::assureTerminationImpl_() const
{
    auto* mutableSafeString = const_cast<BufferedSafeStringBase<char>*>(this);
    mutableSafeString->getMutableStringTop_()[mBufferSize - 1] = cNullChar;
}

template <>
void BufferedSafeStringBase<char16>::assureTerminationImpl_() const
{
    auto* mutableSafeString = const_cast<BufferedSafeStringBase<char16>*>(this);
    mutableSafeString->getMutableStringTop_()[mBufferSize - 1] = cNullChar;
}

template <>
s32 BufferedSafeStringBase<char>::formatImpl_(char* s, s32 n, const char* formatStr, va_list args)
{
    const s32 ret = StringUtil::vsnprintf(s, n, formatStr, args);
    return ret < 0 ? n - 1 : ret;
}

template <>
s32 BufferedSafeStringBase<char16>::formatImpl_(char16* s, s32 n, const char16* formatStr,
                                                va_list args)
{
    const s32 ret = StringUtil::vsnw16printf(s, n, formatStr, args);
    if (ret >= 0 && ret < n)
        return ret;
    s[n - 1] = WSafeString::cNullChar;
    return n - 1;
}

template <>
s32 BufferedSafeStringBase<char>::formatV(const char* formatStr, va_list args)
{
    char* mutableString = getMutableStringTop_();
    return formatImpl_(mutableString, mBufferSize, formatStr, args);
}

template <>
s32 BufferedSafeStringBase<char16>::formatV(const char16* formatStr, va_list args)
{
    char16* mutableString = getMutableStringTop_();
    return formatImpl_(mutableString, mBufferSize, formatStr, args);
}

template <>
s32 BufferedSafeStringBase<char>::format(const char* formatStr, ...)
{
    va_list args;
    va_start(args, formatStr);
    s32 ret = formatV(formatStr, args);
    va_end(args);

    return ret;
}

template <>
s32 BufferedSafeStringBase<char16>::format(const char16* formatStr, ...)
{
    va_list args;
    va_start(args, formatStr);
    s32 ret = formatV(formatStr, args);
    va_end(args);

    return ret;
}

template <>
s32 BufferedSafeStringBase<char>::appendWithFormatV(const char* format, std::va_list args)
{
    char* mutableString = getMutableStringTop_();
    const s32 len = calcLength();
    return formatImpl_(mutableString + len, mBufferSize - len, format, args) + len;
}

template <>
s32 BufferedSafeStringBase<char16>::appendWithFormatV(const char16* format, std::va_list args)
{
    char16* mutableString = getMutableStringTop_();
    const s32 len = calcLength();
    return formatImpl_(mutableString + len, mBufferSize - len, format, args) + len;
}

template <>
s32 BufferedSafeStringBase<char>::appendWithFormat(const char* format, ...)
{
    std::va_list args;
    va_start(args, format);
    const s32 ret = appendWithFormatV(format, args);
    va_end(args);
    return ret;
}

template <>
s32 BufferedSafeStringBase<char16>::appendWithFormat(const char16* format, ...)
{
    std::va_list args;
    va_start(args, format);
    const s32 ret = appendWithFormatV(format, args);
    va_end(args);
    return ret;
}

// NON_MATCHING
template <typename T>
s32 replaceStringImpl_(T* dst, s32* length, s32 dst_size, const T* src, s32 src_size,
                       const SafeStringBase<T>& old_str, const SafeStringBase<T>& new_str,
                       bool* is_buffer_overflow)
{
    s32 ret = 0;
    *is_buffer_overflow = false;
    const s32 dst_max_idx = dst_size - 1;

    const T* old_cstr = old_str.cstr();
    const s32 old_str_len = old_str.calcLength();

    if (old_str_len == 0)
    {
        if (dst == src)
            return 0;

        *is_buffer_overflow = src_size >= dst_size;
        if (src_size >= dst_size)
        {
            MemUtil::copy(dst, src, dst_max_idx);
            dst[dst_max_idx] = SafeStringBase<T>::cNullChar;
            if (length)
                *length = dst_max_idx;
        }
        else
        {
            MemUtil::copy(dst, src, src_size + 1);
            if (length)
                *length = src_size;
        }
        return 0;
    }

    const T* new_cstr = new_str.cstr();
    const s32 new_str_len = new_str.calcLength();

    // Replace in-place.
    if (dst == src && old_str_len < new_str_len)
    {
        s32 dst_final_size = 0;
        s32 src_final_size = 0;
        // First, terminate the string and check for buffer overflow.
        while (src_final_size < src_size)
        {
            const s32 cmp = MemUtil::compare(&dst[src_final_size], old_cstr, old_str_len);
            src_final_size += cmp == 0 ? old_str_len : 1;
            dst_final_size += cmp == 0 ? new_str_len : 1;
            if (dst_final_size >= dst_size)
            {
                *is_buffer_overflow = true;
                break;
            }
        }

        if (*is_buffer_overflow)
        {
            dst[dst_max_idx] = SafeStringBase<T>::cNullChar;
            if (length)
                *length = dst_max_idx;
        }
        else
        {
            dst[dst_final_size] = SafeStringBase<T>::cNullChar;
            if (length)
                *length = dst_final_size;
        }

        s32 dst_i = dst_final_size - 1;
        s32 src_i = src_final_size - 1;
        while (src_i >= 0)
        {
            const s32 cmp = MemUtil::compare(&dst[src_i + 1 - old_str_len], old_cstr, old_str_len);
            if (cmp == 0)
            {
                dst_i -= new_str_len;
                const s32 copy_size = std::min(new_str_len, dst_size - 2 - dst_i);
                if (copy_size > 0)
                {
                    MemUtil::copy(&dst[dst_i + 1], new_cstr, copy_size);
                    ret += 1;
                }
                src_i -= old_str_len;
            }
            else
            {
                if (dst_i < dst_max_idx)
                    dst[dst_i] = dst[src_i];
                if (src_i < 1)
                {
                    --src_i;
                    --dst_i;
                    break;
                }
            }
        }

        SEAD_ASSERT(dst_i == -1);
        SEAD_ASSERT(src_i == -1);
    }
    // Simpler case.
    else
    {
        s32 target_i = 0;
        s32 buffer_i = 0;
        while (target_i < src_size)
        {
            const s32 cmp = MemUtil::compare(&src[target_i], old_cstr, old_str_len);
            // Not old_str, copy one character to the buffer.
            if (cmp != 0)
            {
                if (buffer_i < dst_max_idx)
                {
                    dst[buffer_i++] = src[target_i++];
                    continue;
                }
            }
            // Found old_str, copy new_str to the buffer.
            else
            {
                const s32 copy_size = std::min(new_str_len, dst_max_idx - buffer_i);
                if (copy_size >= 1)
                    MemUtil::copy(&dst[buffer_i], new_cstr, copy_size);
                ret += new_str_len == 0 || copy_size > 0;
                if (copy_size >= new_str_len)
                {
                    buffer_i += new_str_len;
                    target_i += old_str_len;
                    continue;
                }
            }

            // Buffer overflow.
            *is_buffer_overflow = true;
            dst[dst_max_idx] = SafeStringBase<T>::cNullChar;
            if (length)
                *length = dst_max_idx;
            return ret;
        }

        SEAD_ASSERT(buffer_i <= dst_size);
        SEAD_ASSERT(target_i == src_size);

        dst[buffer_i] = SafeStringBase<T>::cNullChar;
        if (length)
            *length = buffer_i;
    }

    return ret;
}

template s32 replaceStringImpl_<char>(char* buffer, s32* length, s32 buffer_size,
                                      const char* target_buf, s32 target_len,
                                      const SafeStringBase<char>& old_str,
                                      const SafeStringBase<char>& new_str,
                                      bool* is_buffer_overflow);

template s32 replaceStringImpl_<char16>(char16* buffer, s32* length, s32 buffer_size,
                                        const char16* target_buf, s32 target_len,
                                        const SafeStringBase<char16>& old_str,
                                        const SafeStringBase<char16>& new_str,
                                        bool* is_buffer_overflow);

}  // namespace sead
