#pragma once

#include <algorithm>
#include <ore/Types.h>
#include <string>

namespace ore {

template <typename T>
constexpr size_t StringLength(const T* str) {
    if (str == nullptr || str[0] == 0)
        return 0;

    size_t len = 0;
    while (*str++ != 0)
        ++len;

#ifdef MATCHING_HACK_NX_CLANG
    __builtin_assume(len <= 0xffffffff);
#endif
    return len;
}

template <typename T>
class TStringView {
public:
    // Annoyingly enough, this cannot be defaulted (otherwise Clang will not dynamically
    // initialize static StringView variables).
    TStringView() {}

    constexpr TStringView(const T* data, size_t len) : m_data(data), m_len(len) {}

    /// @param data A null-terminated string. Must not be nullptr.
    // NOLINTNEXTLINE(google-explicit-constructor)
    TStringView(const T* data) : m_data(data), m_len(StringLength(data)) {}

    constexpr const T* data() const { return m_data; }
    constexpr int size() const { return m_len; }
    constexpr int length() const { return m_len; }
    constexpr bool empty() const { return size() == 0; }

    constexpr auto begin() const { return m_data; }
    constexpr auto cbegin() const { return m_data; }
    constexpr auto end() const { return m_data + m_len; }
    constexpr auto cend() const { return m_data + m_len; }

    const T& operator[](size_t idx) const { return m_data[idx]; }

    static int Compare(TStringView lhs, TStringView rhs) {
        const T* s1 = lhs.data();
        const T* s2 = rhs.data();
        int len = std::min(lhs.size(), rhs.size());
        if (len < 1)
            return lhs.size() - rhs.size();
        while (len-- > 0) {
            if (*s1 == 0 || *s1 != *s2)
                return *s1 - *s2;
            ++s1, ++s2;
        }
        return lhs.size() - rhs.size();
    }

    int Compare(TStringView rhs) const { return Compare(*this, rhs); }

    friend bool operator==(TStringView lhs, TStringView rhs) {
        return lhs.size() == rhs.size() && Compare(lhs, rhs) == 0;
    }

    friend bool operator!=(TStringView lhs, TStringView rhs) { return !operator==(lhs, rhs); }

private:
    const T* m_data{};
    u32 m_len{};
};

using StringView = TStringView<char>;
using WStringView = TStringView<wchar_t>;

}  // namespace ore
