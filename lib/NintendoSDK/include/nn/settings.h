#pragma once

namespace nn {
namespace settings {
enum Language {
    Language_Japanese,
    Language_English,
    Language_French,
    Language_German,
    Language_Italian,
    Language_Spanish,
    Language_Chinese,
    Language_Korean,
    Language_Dutch,
    Language_Portuguese,
    Language_Russian,
    Language_Taiwanese,
    Language_BritishEnglish,
    Language_CanadianFrench,
    Language_LatinAmericanSpanish
};

struct LanguageCode {
    char code[0x8];

    static LanguageCode Make(nn::settings::Language);
};

bool operator==(nn::settings::LanguageCode const&, nn::settings::LanguageCode const&);
};  // namespace settings
};  // namespace nn