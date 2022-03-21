/**
 * @file string.h
 * @brief NEX String Implementation.
 */

#pragma once

#include <nn/nex/RootObject.h>

namespace nn {
namespace nex {
class String : public nn::nex::RootObject {
public:
    String();
    String(const char*);
    String(const wchar_t*);
    String(const char16_t*);
    String(const String&);
    String(String&&);

    String& operator=(String&&);
    String& operator=(const char*);
    String& operator=(const wchar_t*);
    String& operator=(const String&);
    String& operator=(const char16_t*);
    String& operator+=(const String&);
    String operator==(const String&);
    bool operator<(nn::nex::String const&);

    void Truncate(u64) const;
    u64 GetLength() const;
    void Reserve(u64);
    void SetBufferChar(char*);
    void SetStringToPreReservedBuffer(char const*);
    s32 GetWideCharLength() const;
    void CopyString(char*, u64) const;
    void CreateCopy(wchar_t**) const;
    void ReleaseCopy(wchar_t*);
    void ToUpper();
    void ToLower();
    void DeleteContent();

    template <typename T>
    void Assign(T const*);
};
};  // namespace nex
};  // namespace nn