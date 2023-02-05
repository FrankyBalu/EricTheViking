//
// Created by frank on 05.02.2023.
//

#ifndef ERIC_LIBERIC_HPP
#define ERIC_LIBERIC_HPP

// Definitionen, falls libEric unter windows als dll gebaut/genutzt werden soll
#if defined(_WIN32)
    #if defined(BUILD_LIBTYPE_SHARED)
        #define LIBERIC_API __declspec(dllexport)     // We are building the library as a Win32 shared library (.dll)
    #elif defined(USE_LIBTYPE_SHARED)
        #define LIBERIC_API __declspec(dllimport)     // We are using the library as a Win32 shared library (.dll)
    #endif
#endif

#ifndef LIBERIC_API
#define LIBERIC_API       // Functions defined as 'extern' by default (implicit specifiers)
#endif

#endif //ERIC_LIBERIC_HPP
