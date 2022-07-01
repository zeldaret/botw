#pragma once

#include <type_traits>

namespace ksys::util {

template <typename IntType>
class IntRange {
public:
    static_assert(std::is_integral_v<IntType>, "T is not a integer type");

    class Iterator {
    public:
        constexpr explicit Iterator(IntType value) : mValue(value) {}

        constexpr bool operator==(Iterator rhs) const { return mValue == rhs.mValue; }
        constexpr bool operator!=(Iterator rhs) const { return !operator==(rhs); }

        constexpr IntType operator*() const { return mValue; }

        constexpr Iterator& operator++() {
            ++mValue;
            return *this;
        }

        constexpr Iterator operator++(int) const { return Iterator(mValue + 1); }

    private:
        IntType mValue;
    };

    constexpr IntRange(IntType begin, IntType end) : mBegin(begin), mEnd(end) {}

    constexpr Iterator begin() const { return mBegin; }
    constexpr Iterator end() const { return mEnd; }
    constexpr Iterator cbegin() const { return mBegin; }
    constexpr Iterator cend() const { return mEnd; }

private:
    Iterator mBegin;
    Iterator mEnd;
};

/// Range [begin, end) with a step of 1.
template <typename IntType>
constexpr IntRange<IntType> range(IntType begin, IntType end) {
    return {begin, end};
}

/// Range [0, end) with a step of 1.
template <typename IntType>
constexpr auto range(IntType end) {
    return IntRange<IntType>{0, end};
}

/// Use this as a replacement for `for (int i = 0, n = c.size(); i < n; ++i)` loops.
///
/// @warning The even better option is to use the container's own iterators,
/// as index-based loops can result in useless bounds checks at every iteration.
template <typename Container>
class IndexRange {
public:
    class ElementProxy {
    public:
        constexpr ElementProxy(Container& container, int index)
            : mIndex(index), mContainer(container) {}

        constexpr int getIndex() const { return mIndex; }
        constexpr decltype(auto) get() const { return mContainer[mIndex]; }
        constexpr decltype(auto) operator*() const { return get(); }
        constexpr auto* operator->() const { return &get(); }

    private:
        int mIndex;
        Container& mContainer;
    };

    class Iterator {
    public:
        constexpr Iterator(Container& container, int index)
            : mIndex(index), mContainer(container) {}

        constexpr bool operator==(Iterator rhs) const { return mIndex == rhs.mIndex; }
        constexpr bool operator!=(Iterator rhs) const { return !operator==(rhs); }

        constexpr int getIndex() const { return mIndex; }
        constexpr ElementProxy operator*() const { return ElementProxy(mContainer, mIndex); }

        constexpr Iterator& operator++() {
            ++mIndex;
            return *this;
        }

        constexpr Iterator operator++(int) const {
            auto copy = *this;
            ++copy;
            return copy;
        }

    private:
        int mIndex;
        Container& mContainer;
    };

    class EndIterator {
    public:
        constexpr explicit EndIterator(int index) : mIndex(index) {}
        constexpr bool notEnd(Iterator it) const { return it.getIndex() < mIndex; }
        friend constexpr bool operator!=(EndIterator end, Iterator it) { return end.notEnd(it); }
        friend constexpr bool operator!=(Iterator it, EndIterator end) { return end.notEnd(it); }

    private:
        int mIndex;
    };

    constexpr explicit IndexRange(Container& container) : mContainer(container) {}

    constexpr Iterator begin() const { return Iterator(mContainer, 0); }
    constexpr EndIterator end() const { return EndIterator(mContainer.size()); }

private:
    Container& mContainer;
};

template <typename Container>
constexpr auto indexIter(Container& container) {
    return IndexRange<Container>{container};
}

}  // namespace ksys::util
