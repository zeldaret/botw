/**
 * @file nn.h
 * @brief Barebones NN functions, such as init and nnMain.
 */

#pragma once

#include <nn/types.h>

namespace nn {
typedef u64 ApplicationId;
};

#ifdef __cplusplus
extern "C" {
#endif

int main(int argc, char** argv);
void nninitStartup();

void _init();
void _fini();
void __nnDetailNintendoSdkRuntimeObjectFileRefer();
void __nnDetailNintendoSdkRuntimeObjectFile();
void __nnDetailNintendoSdkNsoFileRefer();

void __nnmusl_init_dso_0();
void __nnmusl_fini_dso_0();
void __nnDetailNintendoSdkNsoFile_0();

#ifdef __cplusplus
}
#endif