#ifndef ERROR_H
#define ERROR_H

#include <cstdlib>
#include <iostream>

enum struct MessageType { Error, Warning, Info, Debug };

namespace fdse{
    template <typename T, typename... Args>
    void print_info(MessageType type, T args1, Args&&... args) {
        switch (type) {
        case MessageType::Error:
            std::cerr << "\033[1;31m[ERROR]: " << args1 << "\033[0m" << "\033[1;35m";
            ((std::cerr << args), ...);
            std::cerr << "\033[0m\n";
            std::exit(1);
            break;
        case MessageType::Warning:
            std::cerr << "\033[1;33m[WARNING]: " << args1 << "\033[0m" << "\033[1;35m";
            ((std::cerr << args), ...);
            std::cerr << "\033[0m\n";
            break;
        case MessageType::Info:
            std::cerr << "\033[1;32m[INFO]: " << args1 << "\033[0m" << "\033[1;35m";
            ((std::cerr << args), ...);
            std::cerr << "\033[0m\n";
            break;
        case MessageType::Debug:
            std::cerr << "\033[1;34m[DEBUG]: " << args1 <<"\033[0m" << "\033[1;35m";
            ((std::cerr << args), ...);
            std::cerr << "\033[0m\n";
            break;
        }
    }
}

#endif