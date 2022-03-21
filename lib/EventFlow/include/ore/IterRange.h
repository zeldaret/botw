#pragma once

#include <iterator>

namespace ore {

template <typename T>
class IterRange {
public:
    constexpr IterRange() = default;
    constexpr IterRange(const T& begin_, const T& end_) : m_begin(begin_), m_end(end_) {}
    template <typename Other>
    // NOLINTNEXTLINE(google-explicit-constructor)
    constexpr IterRange(Other& x) : IterRange(std::begin(x), std::end(x)) {}

    constexpr IterRange(const T& begin, int size) : m_begin(begin), m_end(begin + size) {}

    const auto& begin() const { return m_begin; }
    const auto& end() const { return m_end; }

    int size() const { return end() - begin(); }

private:
    T m_begin{};
    T m_end{};
};

}  // namespace ore
