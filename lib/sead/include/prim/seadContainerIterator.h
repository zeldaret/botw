#pragma once

// Provides a container wrapper that exposes legacy RandomAccessIterators
// to make it easier to use sead containers with the C++ standard library (e.g. with <algorithm>).

#include <iterator>
#include <type_traits>
#include <utility>
#include "basis/seadTypes.h"

namespace sead
{
namespace detail
{
template <typename T>
class ContainerWrapper
{
public:
    class Iterator
    {
    public:
        // LegacyIterator

        using difference_type = s32;
        using value_type = std::remove_reference_t<decltype(std::declval<T>()[0])>;
        using pointer = value_type*;
        using reference = value_type&;
        using iterator_category = std::random_access_iterator_tag;

        Iterator(T* container, s32 idx) : mIdx(idx), mContainer(container) {}

        reference operator*() const { return container()(mIdx); }

        Iterator& operator++()
        {
            ++mIdx;
            return *this;
        }

        // EqualityComparable

        friend bool operator==(Iterator a, Iterator b) { return a.mIdx == b.mIdx; }

        // LegacyInputIterator

        friend bool operator!=(Iterator a, Iterator b) { return !operator==(a, b); }

        Iterator* operator->() const { return &container()(mIdx); }

        Iterator operator++(int) const
        {
            Iterator result = *this;
            ++result;
            return result;
        }

        // LegacyBidirectionalIterator

        Iterator& operator--()
        {
            --mIdx;
            return *this;
        }

        Iterator operator--(int) const
        {
            Iterator result = *this;
            --result;
            return result;
        }

        // LegacyRandomAccessIterator

        Iterator& operator+=(difference_type n)
        {
            mIdx += n;
            return *this;
        }

        friend Iterator operator+(Iterator it, difference_type n)
        {
            auto result = it;
            return result += n;
        }

        friend Iterator operator+(difference_type n, Iterator it)
        {
            auto result = it;
            return result += n;
        }

        Iterator& operator-=(difference_type n)
        {
            mIdx -= n;
            return *this;
        }

        friend Iterator operator-(Iterator it, difference_type n)
        {
            auto result = it;
            return result -= n;
        }

        friend difference_type operator-(Iterator a, Iterator b) { return a.mIdx - b.mIdx; }

        reference operator[](difference_type n) const { return container()[n]; }

        friend bool operator<(Iterator a, Iterator b) { return a.mIdx < b.mIdx; }
        friend bool operator>(Iterator a, Iterator b) { return a.mIdx > b.mIdx; }
        friend bool operator<=(Iterator a, Iterator b) { return a.mIdx <= b.mIdx; }
        friend bool operator>=(Iterator a, Iterator b) { return a.mIdx >= b.mIdx; }

    private:
        auto& container() const { return *mContainer; }

        s32 mIdx;
        T* mContainer;
    };

    explicit ContainerWrapper(T& container) : mContainer(&container) {}

    auto begin() const { return Iterator(mContainer, 0); }
    auto end() const { return Iterator(mContainer, mContainer->size()); }

private:
    T* mContainer;
};
}  // namespace detail

template <typename T>
auto stdIterator(T& container)
{
    return detail::ContainerWrapper<T>(container);
}
}  // namespace sead
