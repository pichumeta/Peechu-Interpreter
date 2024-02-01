//
// Created by Jamie on 01/02/2024.
//

#ifndef FILE_H
#define FILE_H

#include <fstream>
#include <sstream>

namespace utils::file {

    inline std::string GetContents(const std::string &file_path) {
        std::stringstream sstream;
        const std::fstream file(file_path, std::ios::in);

        sstream << file.rdbuf();

        return sstream.str();
    }

}

#endif //FILE_H
