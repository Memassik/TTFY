#ifndef TTFY_DEFINE_H
#define TTFY_DEFINE_H

#ifdef __linux__
#define TTFY_EXPORT
#define TTFY_IMPORT
#elif _WIN32
#define TTFY_EXPORT __declspec(dllexport)
#define TTFY_IMPORT __declspec(dllimport)
#else
#error "Platform Not Supported"
#endif

#ifdef __cplusplus
#define TTFY_CPP extern "C"
#else
#define TTFY_CPP
#endif

#ifdef TTFY_DLL
#define TTFY_DLL_EXPORT TTFY_EXPORT
#define TTFY_DLL_IMPORT TTFY_IMPORT
#else
#define TTFY_DLL_EXPORT
#define TTFY_DLL_IMPORT
#endif

#ifdef TTFY_BUILD
#define TTFY_API TTFY_CPP TTFY_DLL_EXPORT
#else
#define TTFY_API TTFY_CPP TTFY_DLL_IMPORT
#endif

#endif