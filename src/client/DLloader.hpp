/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** DLLoader
*/

#ifndef DLLOADER_HPP_
#define DLLOADER_HPP_

#include <string>
#include <iostream>
#include "./Error/DLError.hpp"

#if defined(_WIN32) || defined(_WIN64)
#define NOMINMAX
#include <windows.h>
#else
#include <dlfcn.h>
#endif

class DLLoader {
    public:
        DLLoader() : handle(nullptr) {
        }

        DLLoader(const std::string& nameLib) {
#if defined(_WIN32) || defined(_WIN64)
            handle = LoadLibrary(nameLib.c_str());
            if (!handle) {
                std::cerr << "Error loading lib " << nameLib << std::endl;
                throw RType::DLError("Error loading lib " + nameLib, "src/DLLoader.hpp/DLLoader");
            }
#else
            handle = dlopen(nameLib.c_str(), RTLD_NOW);
            if (!handle) {
                std::cerr << "Error loading lib " << nameLib << std::endl;
                throw RType::DLError("Error loading lib " + nameLib, "src/DLLoader.hpp/DLLoader");
            }
#endif
        }

        ~DLLoader() {
            if (handle) {
#if defined(_WIN32) || defined(_WIN64)
                FreeLibrary(static_cast<HMODULE>(handle));
#else
                dlclose(handle);
#endif
            }
        }

        template <typename T> T* getInstance(const std::string& symbolName) const {
            if (!handle) return nullptr;

#if defined(_WIN32) || defined(_WIN64)
            T* (*entryPoint)();
            entryPoint =
                reinterpret_cast<T* (*)()>(GetProcAddress(static_cast<HMODULE>(handle), symbolName.c_str()));
            if (!entryPoint) {
                std::cerr << "Error loading symbol: " << symbolName << std::endl;
                throw RType::DLError("Error loading symbol", "src/DLLoader.hpp/getInstance");
            }
#else
            char* error = nullptr;
            T* (*entryPoint)();
            entryPoint = (T * (*)()) dlsym(handle, symbolName.c_str());
            if (!entryPoint) {
                std::cerr << "Error loading symbol: " << symbolName << std::endl;
                throw RType::DLError("Error loading symbol", "src/DLLoader.hpp/getInstance");
            }
            error = dlerror();
            if (error) std::cerr << "dlsym error: " << error << std::endl;

#endif
            return entryPoint();
        }

    private:
        void* handle;
};

#endif /* !DLLOADER_HPP_ */
