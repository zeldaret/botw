#pragma once

#include <cstdarg>

#include "prim/seadSafeString.h"

namespace sead
{
class Heap;
template <typename T>
class StringBuilderBase
{
public:
    static StringBuilderBase* create(s32 buffer_size, Heap* heap, s32 alignment);
    static StringBuilderBase* create(const T* str, Heap* heap, s32 alignment);

    StringBuilderBase(const StringBuilderBase<T>& other) = delete;

    class iterator
    {
    public:
        explicit iterator(const StringBuilderBase* builder) : mBuilder(builder), mIndex(0) {}
        iterator(const StringBuilderBase* string, s32 index) : mBuilder(string), mIndex(index) {}
        bool operator==(const iterator& rhs) const
        {
            return mBuilder == rhs.mBuilder && mIndex == rhs.mIndex;
        }
        bool operator!=(const iterator& rhs) const { return !(rhs == *this); }
        iterator& operator++() { return mIndex++, *this; }
        iterator& operator--() { return mIndex--, *this; }
        const char& operator*() const { return mBuilder->at(mIndex); }

        const StringBuilderBase* getBuilder() const { return mBuilder; }
        s32 getIndex() const { return mIndex; }

    protected:
        const StringBuilderBase* mBuilder;
        s32 mIndex;
    };

    iterator begin() const { return iterator(this, 0); }
    iterator end() const { return iterator(this, mLength); }

    // TODO: tokenBegin, tokenEnd

    operator SafeStringBase<T>() const { return cstr(); }

    s32 getLength() const { return mLength; }
    s32 calcLength() const { return getLength(); }
    s32 getBufferSize() const { return mBufferSize; }

    const T* cstr() const;
    const T& at(s32 idx) const;
    const T& operator[](s32 idx) const { return at(idx); }

    SafeStringBase<T> getPart(s32 at) const;
    SafeStringBase<T> getPart(const iterator& it) const;

    bool include(T c) const;
    bool include(const T* str) const;

    s32 findIndex(const T* str) const { return findIndex(str, 0); }
    s32 findIndex(const T* str, s32 start_pos) const;
    s32 rfindIndex(const T* str) const;

    bool isEmpty() const { return mLength == 0; }
    bool startsWith(const T* prefix) const;
    bool endsWith(const T* suffix) const;
    bool isEqual(const T* str) const;
    s32 comparen(const T* str, s32 n) const;

    void clear();

    /// Copy up to copyLength characters to the beginning of the string, then writes NUL.
    /// @param src  Source string
    /// @param copy_length  Number of characters from src to copy (must not cause a buffer overflow)
    s32 copy(const T* src, s32 copy_length = -1);
    /// Copy up to copyLength characters to the specified position, then writes NUL if the copy
    /// makes this string longer.
    /// @param at  Start position (-1 for end of string)
    /// @param src  Source string
    /// @param copyLength  Number of characters from src to copy (must not cause a buffer overflow)
    s32 copyAt(s32 at, const T* src, s32 copy_length = -1);
    /// Copy up to copyLength characters to the beginning of the string, then writes NUL.
    /// Silently truncates the source string if the buffer is too small.
    /// @param src  Source string
    /// @param copyLength  Number of characters from src to copy
    s32 cutOffCopy(const T* src, s32 copy_length = -1);
    /// Copy up to copyLength characters to the specified position, then writes NUL if the copy
    /// makes this string longer.
    /// Silently truncates the source string if the buffer is too small.
    /// @param at  Start position (-1 for end of string)
    /// @param src  Source string
    /// @param copyLength  Number of characters from src to copy
    s32 cutOffCopyAt(s32 at, const T* src, s32 copy_length = -1);
    /// Copy up to copyLength characters to the specified position, then *always* writes NUL.
    /// @param at  Start position (-1 for end of string)
    /// @param src  Source string
    /// @param copyLength  Number of characters from src to copy (must not cause a buffer overflow)
    s32 copyAtWithTerminate(s32 at, const T* src, s32 copy_length = -1);

    s32 format(const T* format, ...);
    s32 formatV(const T* format, std::va_list args)
    {
        mLength = formatImpl_(mBuffer, mBufferSize, format, args);
        return mLength;
    }
    s32 appendWithFormat(const T* format, ...);
    s32 appendWithFormatV(const T* format, std::va_list args)
    {
        const s32 ret = formatImpl_(mBuffer + mLength, mBufferSize - mLength, format, args);
        mLength += ret;
        return ret;
    }

    /// Append append_length characters from str.
    s32 append(const T* str, s32 append_length);
    /// Append a character.
    s32 append(T c) { return append(c, 1); }
    /// Append a character n times.
    s32 append(T c, s32 n);

    /// Remove num characters from the end of the string.
    /// @return the number of characters that were removed
    s32 chop(s32 chop_num);
    /// Remove the last character if it is equal to c.
    /// @return the number of characters that were removed
    s32 chopMatchedChar(T c);
    /// Remove the last character if it is equal to any of the specified characters.
    /// @param characters  List of characters to remove
    /// @return the number of characters that were removed
    s32 chopMatchedChar(const T* characters);
    /// Remove the last character if it is unprintable.
    /// @warning The behavior of this function is not standard: a character is considered
    /// unprintable if it is <= 0x20 or == 0x7F. In particular, the space character is unprintable.
    /// @return the number of characters that were removed
    s32 chopUnprintableAsciiChar();

    /// Remove trailing characters that are in the specified list.
    /// @param characters  List of characters to remove
    /// @return the number of characters that were removed
    s32 rstrip(const T* characters);
    /// Remove trailing characters that are unprintable.
    /// @warning The behavior of this function is not standard: a character is considered
    /// unprintable if it is <= 0x20 or == 0x7F. In particular, the space character is unprintable.
    /// @return the number of characters that were removed
    s32 rstripUnprintableAsciiChars();

    /// Trim a string to only keep trimLength characters.
    /// @return the new length
    s32 trim(s32 trim_length);
    /// Trim a string to only keep trimLength characters.
    /// @return the new length
    s32 trimMatchedString(const T* str);

    /// @return the number of characters that were replaced
    s32 replaceChar(T old_char, T new_char);
    /// @return the number of characters that were replaced
    s32 replaceCharList(const SafeStringBase<T>& old_chars, const SafeStringBase<T>& new_chars);

    s32 convertFromMultiByteString(const char* str, s32 str_length);
    s32 convertFromWideCharString(const char16* str, s32 str_length);

    s32 cutOffAppend(const T* str, s32 append_length);
    s32 cutOffAppend(T c, s32 num);

    s32 prepend(const T* str, s32 prepend_length);
    s32 prepend(T c, s32 num);

protected:
    StringBuilderBase(T* buffer, s32 buffer_size)
        : mBuffer(buffer), mLength(0), mBufferSize(buffer_size)
    {
        mBuffer[0] = SafeStringBase<T>::cNullChar;
    }

    static StringBuilderBase<T>* createImpl_(s32 buffer_size, Heap* heap, s32 alignment);
    static s32 formatImpl_(T* dst, s32 dst_size, const T* format, std::va_list arg);

    template <typename OtherType>
    s32 convertFromOtherType_(const OtherType* src, s32 src_size);

    T* getMutableStringTop_() const { return mBuffer; }

    T* mBuffer;
    s32 mLength;
    s32 mBufferSize;
};

using StringBuilder = StringBuilderBase<char>;
using WStringBuilder = StringBuilderBase<char16>;

template <s32 N>
class FixedStringBuilder : public StringBuilder
{
public:
    FixedStringBuilder() : StringBuilder(mStorage, N) {}

private:
    char mStorage[N];
};

template <typename T>
inline const T* StringBuilderBase<T>::cstr() const
{
    return mBuffer;
}

// UNCHECKED
template <typename T>
inline const T& StringBuilderBase<T>::at(s32 idx) const
{
    if (idx < 0 || idx > mLength)
    {
        SEAD_ASSERT_MSG(false, "index(%d) out of range[0, %d]", idx, mLength);
        return SafeStringBase<T>::cNullChar;
    }
    return mBuffer[idx];
}

// UNCHECKED
template <typename T>
inline SafeStringBase<T> StringBuilderBase<T>::getPart(s32 at) const
{
    if (at < 0 || at > mLength)
    {
        SEAD_ASSERT_MSG(false, "index(%d) out of range[0, %d]", at, mLength);
        return SafeStringBase<T>::cEmptyString;
    }

    return SafeStringBase<T>(mBuffer + at);
}

// UNCHECKED
template <typename T>
inline SafeStringBase<T> StringBuilderBase<T>::getPart(const StringBuilderBase::iterator& it) const
{
    return getPart(it.getIndex());
}

// UNCHECKED
template <typename T>
inline bool StringBuilderBase<T>::include(T c) const
{
    for (s32 i = 0; i < mLength; ++i)
    {
        if (mBuffer[i] == c)
            return true;
    }
    return false;
}

// UNCHECKED
template <typename T>
inline bool StringBuilderBase<T>::include(const T* str) const
{
    return findIndex(str) != -1;
}

// UNCHECKED
template <typename T>
inline s32 StringBuilderBase<T>::findIndex(const T* str, s32 start_pos) const
{
    const s32 len = calcLength();

    if (start_pos < 0 || start_pos > len)
    {
        SEAD_ASSERT_MSG(false, "start_pos(%d) out of range[0, %d]", start_pos, len);
        return -1;
    }

    const s32 sub_str_len = calcStrLength_(str);

    for (s32 i = start_pos; i <= len - sub_str_len; ++i)
    {
        if (SafeStringBase<T>(&mBuffer[i]).comparen(str, sub_str_len) == 0)
            return i;
    }
    return -1;
}

// UNCHECKED
template <typename T>
inline s32 StringBuilderBase<T>::rfindIndex(const T* str) const
{
    const s32 len = calcLength();
    const s32 sub_str_len = calcStrLength_(str);

    for (s32 i = len - sub_str_len; i >= 0; --i)
    {
        if (SafeStringBase<T>(&mBuffer[i]).comparen(str, sub_str_len) == 0)
            return i;
    }
    return -1;
}

// UNCHECKED
template <typename T>
inline bool StringBuilderBase<T>::startsWith(const T* prefix) const
{
    return findIndex(prefix) == 0;
}

// UNCHECKED
template <typename T>
inline bool StringBuilderBase<T>::isEqual(const T* str) const
{
    for (s32 i = 0; i < mLength; i++)
    {
        if (str[i] == SafeStringBase<T>::cNullChar)
            return false;
        if (mBuffer[i] != str[i])
            return false;
    }
    return true;
}

// UNCHECKED
template <typename T>
inline s32 StringBuilderBase<T>::comparen(const T* str, s32 n) const
{
    if (n > mLength)
    {
        SEAD_ASSERT_MSG(false, "paramater(%d) out of bounds [0, %d]", n, mLength);
        n = mLength;
    }

    for (s32 i = 0; i < n; ++i)
    {
        if (mBuffer[i] < str[i])
            return -1;

        if (mBuffer[i] > str[i])
            return 1;

        if (str[i] == SafeStringBase<T>::cNullChar)
            return 1;
    }

    return 0;
}

// UNCHECKED
template <typename T>
inline void StringBuilderBase<T>::clear()
{
    mBuffer[0] = SafeStringBase<T>::cNullChar;
    mLength = 0;
}
}  // namespace sead
