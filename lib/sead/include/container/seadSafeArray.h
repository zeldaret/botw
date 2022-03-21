#pragma once

#include <basis/seadRawPrint.h>
#include <basis/seadTypes.h>
#include <type_traits>
#include <utility>

namespace sead
{
/// A lightweight std::array like wrapper for a C style array.
template <typename T, s32 N>
class SafeArray
{
public:
    T mBuffer[N];

    T& operator[](s32 idx)
    {
        if (u32(idx) < N)
            return mBuffer[idx];
#ifdef MATCHING_HACK_NX_CLANG
            // Force __LINE__ to be an odd number that cannot be encoded as an immediate for ORR.
            // Otherwise, LLVM's register coalescer can get rid of too many register copies,
            // which messes up register allocation.
#line 44
#endif
        SEAD_ASSERT_MSG(false, "range over [0, %d) : %d", N, idx);
        return mBuffer[0];
    }

    const T& operator[](s32 idx) const
    {
        if (u32(idx) < N)
            return mBuffer[idx];
#ifdef MATCHING_HACK_NX_CLANG
            // Force __LINE__ to be an even number that can be encoded as an immediate for ORR.
            // Otherwise, LLVM's register coalescer can fail to get rid of some register copies,
            // which messes up register allocation.
#line 59
#endif
        SEAD_ASSERT_MSG(false, "range over [0, %d) : %d", N, idx);
        return mBuffer[0];
    }

    T& operator()(s32 idx) { return mBuffer[idx]; }
    const T& operator()(s32 idx) const { return mBuffer[idx]; }

    T& front() { return mBuffer[0]; }
    const T& front() const { return mBuffer[0]; }
    T& back() { return mBuffer[N - 1]; }
    const T& back() const { return mBuffer[N - 1]; }

    int size() const { return N; }
    u32 getByteSize() const { return N * sizeof(T); }

    T* getBufferPtr() { return mBuffer; }
    const T* getBufferPtr() const { return mBuffer; }

    void fill(const T& value)
    {
        for (s32 i = 0; i < N; ++i)
            mBuffer[i] = value;
    }

    class iterator
    {
    public:
        iterator(T* buffer, s32 idx) : mBuffer(buffer), mIdx(idx) {}
        bool operator==(const iterator& rhs) const
        {
            return mBuffer == rhs.mBuffer && mIdx == rhs.mIdx;
        }
        bool operator!=(const iterator& rhs) const { return !(*this == rhs); }
        iterator& operator++()
        {
            ++mIdx;
            return *this;
        }
        iterator& operator--()
        {
            --mIdx;
            return *this;
        }
        T* operator->() const { return &mBuffer[mIdx]; }
        T& operator*() const { return mBuffer[mIdx]; }

    private:
        T* mBuffer;
        s32 mIdx;
    };

    iterator begin() { return iterator(mBuffer, 0); }
    iterator end() { return iterator(mBuffer, N); }

    class constIterator
    {
    public:
        constIterator(const T* buffer, s32 idx) : mBuffer(buffer), mIdx(idx) {}
        bool operator==(const constIterator& rhs) const
        {
            return mBuffer == rhs.mBuffer && mIdx == rhs.mIdx;
        }
        bool operator!=(const constIterator& rhs) const { return !(*this == rhs); }
        constIterator& operator++()
        {
            ++mIdx;
            return *this;
        }
        constIterator& operator--()
        {
            --mIdx;
            return *this;
        }
        const T* operator->() const { return &mBuffer[mIdx]; }
        const T& operator*() const { return mBuffer[mIdx]; }

    private:
        const T* mBuffer;
        s32 mIdx;
    };

    constIterator constBegin() const { return constIterator(mBuffer, 0); }
    constIterator constEnd() const { return constIterator(mBuffer, N); }

    constIterator begin() const { return constIterator(mBuffer, 0); }
    constIterator end() const { return constIterator(mBuffer, N); }
};

namespace detail
{
// From https://en.cppreference.com/w/cpp/container/array/to_array
template <class T, std::size_t N, std::size_t... I>
constexpr SafeArray<std::remove_cv_t<T>, N> to_array_impl(T (&a)[N], std::index_sequence<I...>)
{
    return {{a[I]...}};
}

template <class T, std::size_t N, std::size_t... I>
constexpr SafeArray<std::remove_cv_t<T>, N> to_array_impl(T(&&a)[N], std::index_sequence<I...>)
{
    return {{std::move(a[I])...}};
}
}  // namespace detail

// Implementation of C++20 std::to_array for sead::SafeArray.
template <class T, std::size_t N>
constexpr sead::SafeArray<std::remove_cv_t<T>, N> toArray(T (&a)[N])
{
    return detail::to_array_impl(a, std::make_index_sequence<N>{});
}

// Implementation of C++20 std::to_array for sead::SafeArray.
template <class T, std::size_t N>
constexpr sead::SafeArray<std::remove_cv_t<T>, N> toArray(T(&&a)[N])
{
    return detail::to_array_impl(std::move(a), std::make_index_sequence<N>{});
}
}  // namespace sead
