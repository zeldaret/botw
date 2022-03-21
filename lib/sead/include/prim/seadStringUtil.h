#ifndef SEAD_STRING_UTIL_H_
#define SEAD_STRING_UTIL_H_

#include <stdarg.h>
#include <stdio.h>

#include <basis/seadTypes.h>
#include <container/seadBuffer.h>
#include <prim/seadSafeString.h>

namespace sead
{
namespace StringUtil
{
struct Char16Pair
{
    char16 before;
    char16 after;
};

enum class CardinalNumber
{
    BaseAuto = -1,
    Base2 = 2,
    Base8 = 8,
    Base10 = 10,
    Base16 = 16,
};

bool tryParseU64(u64* out, const SafeString& str, CardinalNumber base);
bool tryParseS64(s64* out, const SafeString& str, CardinalNumber base);
bool tryParseU32(u32* out, const SafeString& str, CardinalNumber base);
bool tryParseS32(s32* out, const SafeString& str, CardinalNumber base);
bool tryParseU16(u16* out, const SafeString& str, CardinalNumber base);
bool tryParseS16(s16* out, const SafeString& str, CardinalNumber base);
bool tryParseU8(u8* out, const SafeString& str, CardinalNumber base);
bool tryParseS8(s8* out, const SafeString& str, CardinalNumber base);
bool tryParseF32(f32* out, const SafeString& str);
bool tryParseF64(f64* out, const SafeString& str);

u64 parseU64(const SafeString& str, CardinalNumber base);
s64 parseS64(const SafeString& str, CardinalNumber base);
u32 parseU32(const SafeString& str, CardinalNumber base);
s32 parseS32(const SafeString& str, CardinalNumber base);
u16 parseU16(const SafeString& str, CardinalNumber base);
s16 parseS16(const SafeString& str, CardinalNumber base);
u8 parseU8(const SafeString& str, CardinalNumber base);
s8 parseS8(const SafeString& str, CardinalNumber base);
f32 parseF32(const SafeString& str);
f64 parseF64(const SafeString& str);

char16* wcs16cpy(char16*, size_t n, const char16*);

s32 snprintf(char* s, size_t n, const char* format, ...);
s32 sw16printf(char16* s, size_t n, const char16* format, ...);
s32 vsnprintf(char* s, size_t n, const char* format, va_list args);
s32 vsw16printf(char16* s, size_t n, const char16* format, std::va_list args);
// TODO
s32 vsnw16printf(char16* s, size_t n, const char16* format, std::va_list args);

s32 convertSjisToUtf16(char16* dst, u32 dst_len, const char* src, s32 src_len);
s32 convertUtf16ToSjis(char* dst, u32 dst_len, const char16* src, s32 src_len);
s32 convertUtf8ToUtf16(char16* dst, u32 dst_len, const char* src, s32 src_len);
s32 convertUtf16ToUtf8(char* dst, u32 dst_len, const char16* src, s32 src_len);
s32 convertSjisToUtf8(char* dst, u32 dst_len, const char* src, s32 src_len);
s32 convertUtf8ToSjis(char* dst, u32 dst_len, const char* src, s32 src_len);

char16 replace(char16 c, const Buffer<const Char16Pair>& sorted_table);

char16 toUpperCapital(char16 c);
void toUpperCapitalFirstCharactor(WBufferedSafeString* str);

char16 toLowerCapital(char16 c);
void toLowerCapitalFirstCharactor(WBufferedSafeString* str);

}  // namespace StringUtil
}  // namespace sead

#endif  // SEAD_STRING_UTIL_H_
