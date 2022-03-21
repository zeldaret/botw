#pragma once

#include <nn/settings.h>

namespace nn {
namespace err {
enum ErrorCodeCategoryType : u32 {
    unk1,
    unk2,
};

class ApplicationErrorArg {
public:
    ApplicationErrorArg();
    ApplicationErrorArg(u32 error_code, const char* dialog_message, const char* fullscreen_message,
                        const nn::settings::LanguageCode& languageCode);
    void SetApplicationErrorCodeNumber(u32 error_code);
    void SetDialogMessage(const char* message);
    void SetFullScreenMessage(const char* message);

    u64 unk;
    u32 error_code;
    nn::settings::LanguageCode language_code;
    char dialog_message[2048];
    char fullscreen_message[2048];
};

u32 MakeErrorCode(ErrorCodeCategoryType err_category_type, u32 errorCodeNumber);
void ShowApplicationError(const ApplicationErrorArg& arg);
}  // namespace err
}  // namespace nn
