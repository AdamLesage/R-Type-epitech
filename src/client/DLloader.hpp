/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** DLLoader
*/

#ifndef DLLOADER_HPP_
#define DLLOADER_HPP_

#include <string>
#include <dlfcn.h>
#include "./Error/DLError.hpp"


class DLLoader {
    public:
        DLLoader(std::string nameLib) {
            this->handle = dlopen(nameLib.c_str(), RTLD_NOW);
            std::cout << nameLib << std::endl;
            if (!handle) {
                throw RType::DLError("Error loading lib", "src/DLloader.hpp/DLloader");
            }
        }
        ~DLLoader() {
            dlclose(this->handle);
        }

        /**
         * @brief Get the Instance object
         * 
         * @param Name path of the shared library
         * @return T* Template of the current instance of the class
        */
        template <typename T>
        T *getInstance(std::string Name) const // load the class in the library
        {
            char *error = NULL;
            T *(*entryPoint)();

            entryPoint = (T *(*)()) dlsym(handle, Name.c_str());
            if (!entryPoint) {
                std::cout << Name << std::endl;
                throw RType::DLError("Error loading entyPoint", "stc/DLloader.hpp/getInstance");
            }
            error = dlerror();
            if (error != NULL) {
                printf("error\n");
            }
            return entryPoint();
        }
    private:
        void *handle;
};

#endif /* !DLLOADER_HPP_ */