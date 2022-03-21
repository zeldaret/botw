#pragma once

#include <iterator>
#include <ore/IterRange.h>
#include <ore/StringView.h>
#include <type_traits>

namespace ore {

namespace detail::EnumUtil {

int FindIndex(int value, const IterRange<const int*>& values);
void Parse(const IterRange<StringView*>& out, StringView definition);

constexpr int CountValues(const char* text_all, size_t text_all_len) {
    int count = 1;
    for (size_t i = 0; i < text_all_len; ++i) {
        if (text_all[i] == ',')
            ++count;
    }
    return count;
}

}  // namespace detail::EnumUtil

template <class T>
struct Enum {
public:
    Enum() { T::Init(); }

    static Enum<T>& Info() { return s_Info; }

    StringView name{};
    IterRange<StringView*> members{};

private:
    static inline Enum<T> s_Info{};
};

#define ORE_ENUM(NAME, ...)                                                                        \
    class NAME {                                                                                   \
    public:                                                                                        \
        enum Type { __VA_ARGS__ };                                                                 \
                                                                                                   \
        static void Init() {                                                                       \
            static ore::StringView names[cCount];                                                  \
            ore::detail::EnumUtil::Parse(ore::IterRange<ore::StringView*>(names), cTextAll);       \
            ore::Enum<NAME>::Info().name = #NAME;                                                  \
            ore::Enum<NAME>::Info().members = ore::IterRange<ore::StringView*>(names);             \
        }                                                                                          \
                                                                                                   \
        static constexpr int Size() { return cCount; }                                             \
        static constexpr Type Invalid() { return Type(Size()); }                                   \
                                                                                                   \
    private:                                                                                       \
        static constexpr const char* cTextAll = #__VA_ARGS__;                                      \
        static constexpr size_t cTextAllLen = sizeof(#__VA_ARGS__);                                \
        static constexpr int cCount = ore::detail::EnumUtil::CountValues(cTextAll, cTextAllLen);   \
    };

// FIXME
template <class T>
class ValuedEnum {
public:
    ValuedEnum() { T::Init(); }

    static Enum<T>& Info() { return s_Info; }

    StringView name{};
    IterRange<StringView*> members{};

private:
    static inline Enum<T> s_Info{};
};

#define ORE_VALUED_ENUM(NAME, ...)                                                                 \
    class NAME {                                                                                   \
    public:                                                                                        \
        enum Type { __VA_ARGS__ };                                                                 \
                                                                                                   \
        static void Init() {                                                                       \
            static ore::StringView names[cCount];                                                  \
            ore::detail::EnumUtil::Parse(ore::IterRange<ore::StringView*>(names), cTextAll);       \
            ore::ValuedEnum<NAME>::Info().name = #NAME;                                            \
            ore::ValuedEnum<NAME>::Info().members = ore::IterRange<ore::StringView*>(names);       \
        }                                                                                          \
                                                                                                   \
        static constexpr int Size() { return cCount; }                                             \
        static constexpr Type Invalid() { return Type(Size()); }                                   \
                                                                                                   \
    private:                                                                                       \
        static constexpr const char* cTextAll = #__VA_ARGS__;                                      \
        static constexpr size_t cTextAllLen = sizeof(#__VA_ARGS__);                                \
        static constexpr int cCount = ore::detail::EnumUtil::CountValues(cTextAll, cTextAllLen);   \
    };

/// For storing an enum with a particular storage size when specifying the underlying type of the
/// enum is not an option.
template <typename Enum, typename Storage>
struct SizedEnum {
    static_assert(std::is_enum<Enum>());
    static_assert(!std::is_enum<Storage>());

    constexpr SizedEnum() = default;
    constexpr SizedEnum(Enum value) { *this = value; }
    constexpr operator Enum() const { return static_cast<Enum>(mValue); }
    constexpr SizedEnum& operator=(Enum value) {
        mValue = static_cast<Storage>(value);
        return *this;
    }

    Storage mValue;
};

}  // namespace ore
