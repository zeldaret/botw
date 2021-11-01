#pragma once

#include <array>
#include <cstddef>
#include <type_traits>

namespace ksys::util {

// https://stackoverflow.com/a/53190503/1636285

struct concat_op {};

template <std::size_t N>
struct FixedString {
    constexpr static std::size_t length() { return N; }
    constexpr static std::size_t capacity() { return N + 1; }

    template <std::size_t L, std::size_t R>
    constexpr FixedString(concat_op, FixedString<L> l, FixedString<R> r) : FixedString() {
        static_assert(L + R == N);
        overwrite(0, l.data(), L);
        overwrite(L, r.data(), R);
    }

    constexpr FixedString() : buffer_{} {}

    constexpr FixedString(const char (&source)[N + 1]) : FixedString() {
        do_copy(source, buffer_.data());
    }

    constexpr const char* data() const { return buffer_.data(); }

    constexpr char* data() { return buffer_.data(); }

private:
    static constexpr void do_copy(const char (&source)[N + 1], char* dest) {
        for (std::size_t i = 0; i < capacity(); ++i)
            dest[i] = source[i];
    }

    constexpr void overwrite(std::size_t where, const char* source, std::size_t len) {
        auto dest = buffer_.data() + where;
        while (len--)
            *dest++ = *source++;
    }

    std::array<char, capacity()> buffer_;
};

template <std::size_t N>
constexpr FixedString<N - 1> Str(const char (&c)[N]) {
    return FixedString<N - 1>(c);
}

template <auto N, int base = 10>
constexpr auto Str() {
    constexpr char digits[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    constexpr auto len = [] {
        unsigned int len = N > 0 ? 0 : 1;
        for (auto n = N; n; len++, n /= base)
            continue;
        return len;
    }();

    FixedString<len> buf{};

    auto ptr = buf.data() + buf.length();
    if (N == 0) {
        buf.data()[0] = '0';
    } else {
        for (auto n = N; n; n /= base)
            *--ptr = digits[(N < 0 ? -1 : 1) * (n % base)];
        if (N < 0)
            *--ptr = '-';
    }

    return buf;
}

template <std::size_t L, std::size_t R>
constexpr auto operator+(FixedString<L> l, FixedString<R> r) -> FixedString<L + R> {
    auto result = FixedString<L + R>(concat_op(), l, r);
    return result;
}

/// Takes any expression that returns a FixedString<N> and returns a const char*.
#define KSYS_STR(STR)                                                                              \
    ([]() -> const char* {                                                                         \
        using ksys::util::Str;                                                                     \
        static constexpr auto x = STR;                                                             \
        return x.data();                                                                           \
    }())

}  // namespace ksys::util
