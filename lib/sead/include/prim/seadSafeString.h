#pragma once

#include <cstdarg>

#include <basis/seadRawPrint.h>
#include <basis/seadTypes.h>

namespace sead
{
class Heap;

template <typename T>
class BufferedSafeStringBase;

template <typename T>
class SafeStringBase
{
public:
    /// Iterates over every character of a string.
    /// Note that this is extremely inefficient and leads to quadratic time complexity
    /// because of the redundant calls to calcLength() in operator*.
    class iterator
    {
    public:
        explicit iterator(const SafeStringBase* string) : mString(string), mIndex(0) {}
        iterator(const SafeStringBase* string, s32 index) : mString(string), mIndex(index) {}
        bool operator==(const iterator& rhs) const
        {
            return mString == rhs.mString && mIndex == rhs.mIndex;
        }
        bool operator!=(const iterator& rhs) const { return !(rhs == *this); }
        iterator& operator++() { return mIndex++, *this; }
        iterator& operator--() { return mIndex--, *this; }
        const char& operator*() const { return mString->at(mIndex); }

        const SafeStringBase* getString() const { return mString; }
        s32 getIndex() const { return mIndex; }

    protected:
        const SafeStringBase* mString;
        s32 mIndex;
    };

    /// Iterates over a string as if it were split by one or several delimiter characters.
    class token_iterator : public iterator
    {
    public:
        token_iterator(const SafeStringBase* string, const SafeStringBase& delimiter)
            : iterator(string), mDelimiter(delimiter)
        {
        }

        token_iterator(const SafeStringBase* string, s32 index, const SafeStringBase& delimiter)
            : iterator(string, index), mDelimiter(delimiter)
        {
        }

        bool operator==(const token_iterator& rhs) const
        {
            return static_cast<const iterator&>(*this) == static_cast<const iterator&>(rhs);
        }
        bool operator!=(const token_iterator& rhs) const { return !(rhs == *this); }

        token_iterator& operator++();
        token_iterator& operator--();

        s32 get(BufferedSafeStringBase<T>* out) const;
        inline s32 getAndForward(BufferedSafeStringBase<T>* out);
        s32 cutOffGet(BufferedSafeStringBase<T>* out) const;
        s32 cutOffGetAndForward(BufferedSafeStringBase<T>* out);

    private:
        const SafeStringBase mDelimiter;
    };

    SafeStringBase() : mStringTop(&cNullChar) {}
    SafeStringBase(const T* str) : mStringTop(str)
    {
        SEAD_ASSERT_MSG(str != nullptr, "str must not be nullptr.");
    }
    SafeStringBase(const SafeStringBase& other) = default;

    virtual ~SafeStringBase() = default;

    virtual SafeStringBase& operator=(const SafeStringBase& other);

    bool operator==(const SafeStringBase& rhs) const { return isEqual(rhs); }
    bool operator!=(const SafeStringBase& rhs) const { return !(*this == rhs); }

    iterator begin() const { return iterator(this, 0); }
    iterator end() const { return iterator(this, calcLength()); }

    token_iterator tokenBegin(const SafeStringBase& delimiter) const
    {
        return token_iterator(this, delimiter);
    }

    token_iterator tokenEnd(const SafeStringBase& delimiter) const
    {
        return token_iterator(this, calcLength() + 1, delimiter);
    }

    const T* cstr() const
    {
        assureTerminationImpl_();
        return mStringTop;
    }

    inline const T& at(s32 idx) const;
    inline const T& operator[](s32 idx) const { return at(idx); }

    inline s32 calcLength() const;

    inline SafeStringBase<T> getPart(s32 at) const;
    inline SafeStringBase<T> getPart(const iterator& it) const;
    inline SafeStringBase<T> getPart(const token_iterator& it) const;

    inline bool include(const T& c) const;
    inline bool include(const SafeStringBase<T>& str) const;

    bool isEqual(const SafeStringBase<T>& str) const;
    inline s32 compare(const SafeStringBase<T>& str) const { return comparen(str, cMaximumLength); }
    inline s32 comparen(const SafeStringBase<T>& str, s32 n) const;

    s32 findIndex(const SafeStringBase<T>& str) const;
    s32 findIndex(const SafeStringBase<T>& str, s32 start_pos) const;
    s32 rfindIndex(const SafeStringBase<T>& str) const;

    iterator findIterator(const SafeStringBase& str) const { return {this, findIndex(str)}; }
    iterator rfindIterator(const SafeStringBase& str) const { return {this, rfindIndex(str)}; }

    bool isEmpty() const;
    bool startsWith(const SafeStringBase<T>& prefix) const;
    bool endsWith(const SafeStringBase<T>& suffix) const;

    static const T cNullChar;
    static const T cLineBreakChar;
    static const SafeStringBase cEmptyString;
    static const s32 cMaximumLength = 0x80000;

protected:
    virtual void assureTerminationImpl_() const {}
    const T& unsafeAt_(s32 idx) const { return mStringTop[idx]; }

    const T* mStringTop;
};

template <>
const SafeStringBase<char> SafeStringBase<char>::cEmptyString;

template <typename T>
s32 replaceStringImpl_(T* dst, s32* length, s32 dst_size, const T* src, s32 src_size,
                       const SafeStringBase<T>& old_str, const SafeStringBase<T>& new_str,
                       bool* is_buffer_overflow);

template <typename T>
class BufferedSafeStringBase : public SafeStringBase<T>
{
public:
    __attribute__((always_inline)) BufferedSafeStringBase(T* buffer, s32 size)
        : SafeStringBase<T>(buffer)
    {
        mBufferSize = size;
        if (size <= 0)
        {
            SEAD_ASSERT_MSG(false, "Invalied buffer size(%d).\n", this->getBufferSize());
            this->mStringTop = nullptr;
            this->mBufferSize = 0;
        }
        else
        {
            this->assureTerminationImpl_();
        }
    }

    BufferedSafeStringBase(const BufferedSafeStringBase&) = default;
    ~BufferedSafeStringBase() override = default;

    BufferedSafeStringBase<T>& operator=(const SafeStringBase<T>& other) override;

    const T& operator[](s32 idx) const;

    T* getBuffer()
    {
        assureTerminationImpl_();
        return getMutableStringTop_();
    }
    s32 getBufferSize() const { return mBufferSize; }

    /// Copy up to copyLength characters to the beginning of the string, then writes NUL.
    /// @param src  Source string
    /// @param copyLength  Number of characters from src to copy (must not cause a buffer overflow)
    inline s32 copy(const SafeStringBase<T>& src, s32 copyLength = -1);
    /// Copy up to copyLength characters to the specified position, then writes NUL if the copy
    /// makes this string longer.
    /// @param at  Start position (-1 for end of string)
    /// @param src  Source string
    /// @param copyLength  Number of characters from src to copy (must not cause a buffer overflow)
    inline s32 copyAt(s32 at, const SafeStringBase<T>& src, s32 copyLength = -1);
    /// Copy up to copyLength characters to the beginning of the string, then writes NUL.
    /// Silently truncates the source string if the buffer is too small.
    /// @param src  Source string
    /// @param copyLength  Number of characters from src to copy
    inline s32 cutOffCopy(const SafeStringBase<T>& src, s32 copyLength = -1);
    /// Copy up to copyLength characters to the specified position, then writes NUL if the copy
    /// makes this string longer.
    /// Silently truncates the source string if the buffer is too small.
    /// @param at  Start position (-1 for end of string)
    /// @param src  Source string
    /// @param copyLength  Number of characters from src to copy
    inline s32 cutOffCopyAt(s32 at, const SafeStringBase<T>& src, s32 copyLength = -1);
    /// Copy up to copyLength characters to the specified position, then *always* writes NUL.
    /// @param at  Start position (-1 for end of string)
    /// @param src  Source string
    /// @param copyLength  Number of characters from src to copy (must not cause a buffer overflow)
    inline s32 copyAtWithTerminate(s32 at, const SafeStringBase<T>& src, s32 copyLength = -1);

    s32 format(const T* format, ...);
    s32 formatV(const T* format, std::va_list args);
    s32 appendWithFormat(const T* formatStr, ...);
    s32 appendWithFormatV(const T* formatStr, std::va_list args);

    /// Append append_length characters from str.
    s32 append(const SafeStringBase<T>& str, s32 append_length = -1);
    /// Append a character.
    s32 append(T c) { return append(c, 1); }
    /// Append a character n times.
    s32 append(T c, s32 n);

    // Implementation note: These member functions appear to be inlined in most titles.
    // However, StringBuilderBase<T> conveniently duplicates the APIs and implementations of
    // SafeStringBase<T> and BufferedSafeString<T>: some assertion messages are even identical,
    // and the good news is that most StringBuilderBase<T> functions are not inlined!

    /// Append prepend_length characters from str.
    /// @return the new length
    s32 prepend(const SafeStringBase<T>& str, s32 prepend_length = -1);

    /// Remove num characters from the end of the string.
    /// @return the number of characters that were removed
    s32 chop(s32 num);
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
    inline s32 trim(s32 trim_length);
    /// Remove the specified suffix from the string if it ends with the suffix.
    /// @return the new length
    inline s32 trimMatchedString(const SafeStringBase<T>& suffix);
    /// Remove the specified suffix from the string if it ends with the suffix.
    /// Alias of trimMatchedString.
    /// @return the new length
    inline s32 removeSuffix(const SafeStringBase<T>& suffix) { return trimMatchedString(suffix); }

    /// @return the number of characters that were replaced
    inline s32 replaceChar(T old_char, T new_char);
    /// @return the number of characters that were replaced
    inline s32 replaceCharList(const SafeStringBase<T>& old_chars,
                               const SafeStringBase<T>& new_chars);
    /// Set the contents of this string to target_str, after replacing occurrences of old_str in
    /// target_str with new_str.
    /// @return the number of replaced occurrences
    inline s32 setReplaceString(const SafeStringBase<T>& target_str,
                                const SafeStringBase<T>& old_str, const SafeStringBase<T>& new_str);
    /// Replace occurrences of old_str in this string with new_str.
    /// @return the number of replaced occurrences
    inline s32 replaceString(const SafeStringBase<T>& old_str, const SafeStringBase<T>& new_str);

    s32 convertFromMultiByteString(const SafeStringBase<char>& str, s32 str_length);
    s32 convertFromWideCharString(const SafeStringBase<char16>& str, s32 str_length);

    inline void clear() { getMutableStringTop_()[0] = this->cNullChar; }

protected:
    void assureTerminationImpl_() const override;

    T* getMutableStringTop_() { return const_cast<T*>(this->mStringTop); }

    static s32 formatImpl_(T* dst, s32 dst_size, const T* format, std::va_list arg);

    template <typename OtherType>
    s32 convertFromOtherType_(const SafeStringBase<OtherType>& src, s32 src_size);

    s32 mBufferSize;
};

template <typename T, s32 L>
class FixedSafeStringBase : public BufferedSafeStringBase<T>
{
public:
    FixedSafeStringBase() : BufferedSafeStringBase<T>(mBuffer, L) { this->clear(); }

    FixedSafeStringBase(const SafeStringBase<T>& str) : BufferedSafeStringBase<T>(mBuffer, L)
    {
        this->copy(str);
    }

    FixedSafeStringBase(const FixedSafeStringBase& str) : BufferedSafeStringBase<T>(mBuffer, L)
    {
        this->copy(str);
    }

    ~FixedSafeStringBase() override = default;

    FixedSafeStringBase& operator=(const FixedSafeStringBase& other)
    {
        this->copy(other);
        return *this;
    }

    FixedSafeStringBase& operator=(const SafeStringBase<T>& other) override
    {
        this->copy(other);
        return *this;
    }

    T mBuffer[L];
};

typedef SafeStringBase<char> SafeString;
typedef SafeStringBase<char16> WSafeString;
typedef BufferedSafeStringBase<char> BufferedSafeString;
typedef BufferedSafeStringBase<char16> WBufferedSafeString;

template <>
s32 BufferedSafeStringBase<char>::format(const char* formatStr, ...);
template <>
s32 BufferedSafeStringBase<char16>::format(const char16* formatStr, ...);
template <>
s32 BufferedSafeStringBase<char>::formatV(const char* formatStr, va_list args);
template <>
s32 BufferedSafeStringBase<char16>::formatV(const char16* formatStr, va_list args);
template <>
s32 BufferedSafeStringBase<char>::appendWithFormat(const char* formatStr, ...);
template <>
s32 BufferedSafeStringBase<char16>::appendWithFormat(const char16* formatStr, ...);
template <>
s32 BufferedSafeStringBase<char>::appendWithFormatV(const char* formatStr, va_list args);
template <>
s32 BufferedSafeStringBase<char16>::appendWithFormatV(const char16* formatStr, va_list args);

template <s32 L>
class FixedSafeString : public FixedSafeStringBase<char, L>
{
public:
    FixedSafeString() : FixedSafeStringBase<char, L>() {}
    FixedSafeString(const SafeString& str) : FixedSafeStringBase<char, L>(str) {}
    FixedSafeString(const FixedSafeString& other)
        : FixedSafeString(static_cast<const SafeString&>(other))
    {
    }

    FixedSafeString& operator=(const FixedSafeString& other)
    {
        this->copy(other);
        return *this;
    }

    FixedSafeString<L>& operator=(const SafeStringBase<char>& other) override
    {
        this->copy(other);
        return *this;
    }
};

template <s32 L>
class WFixedSafeString : public FixedSafeStringBase<char16, L>
{
public:
    WFixedSafeString() : FixedSafeStringBase<char16, L>() {}

    WFixedSafeString(const WSafeString& str) : FixedSafeStringBase<char16, L>(str) {}
};

template <s32 L>
class FormatFixedSafeString : public FixedSafeString<L>
{
public:
    FormatFixedSafeString() : FormatFixedSafeString("") {}

#ifdef __GNUC__
    [[gnu::format(printf, 2, 3)]]
#endif
    explicit FormatFixedSafeString(const char* format, ...)
        : FixedSafeString<L>()
    {
        std::va_list args;
        va_start(args, format);
        this->formatV(format, args);
        va_end(args);
    }
    ~FormatFixedSafeString() override = default;
};

template <s32 L>
class WFormatFixedSafeString : public WFixedSafeString<L>
{
public:
    explicit WFormatFixedSafeString(const char16* format, ...)
    {
        std::va_list args;
        va_start(args, format);
        this->formatV(format, args);
        va_end(args);
    }
    ~WFormatFixedSafeString() override = default;
};

template <typename T>
class HeapSafeStringBase : public BufferedSafeStringBase<T>
{
public:
    HeapSafeStringBase(Heap* heap, const SafeStringBase<T>& string, s32 alignment = sizeof(void*))
        : BufferedSafeStringBase<T>(new (heap, alignment) T[string.calcLength() + 1](),
                                    string.calcLength() + 1)
    {
        this->copy(string);
    }

    HeapSafeStringBase(const HeapSafeStringBase&) = delete;
    HeapSafeStringBase& operator=(const HeapSafeStringBase&) = delete;

    HeapSafeStringBase(HeapSafeStringBase&& other) noexcept
    {
        this->mStringTop = other.mStringTop;
        other.mStringTop = nullptr;
    }
    HeapSafeStringBase& operator=(HeapSafeStringBase&& other) noexcept
    {
        this->mStringTop = other.mStringTop;
        other.mStringTop = nullptr;
        return *this;
    }

    ~HeapSafeStringBase() override
    {
        if (this->mStringTop)
            delete[] this->mStringTop;
    }

    HeapSafeStringBase<T>& operator=(const SafeStringBase<T>& other) override;
};

using HeapSafeString = HeapSafeStringBase<char>;
using WHeapSafeString = HeapSafeStringBase<char16>;

inline bool operator<(const SafeString& lhs, const SafeString& rhs)
{
    return lhs.compare(rhs) < 0;
}

inline bool operator>(const SafeString& lhs, const SafeString& rhs)
{
    return lhs.compare(rhs) > 0;
}

inline bool operator<=(const SafeString& lhs, const SafeString& rhs)
{
    return lhs.compare(rhs) <= 0;
}

inline bool operator>=(const SafeString& lhs, const SafeString& rhs)
{
    return lhs.compare(rhs) >= 0;
}

}  // namespace sead

#define SEAD_PRIM_SAFE_STRING_H_
#include <prim/seadSafeString.hpp>
#undef SEAD_PRIM_SAFE_STRING_H_
