export module FileUtilities;

import std;

export namespace jod {
std::string GetFileExtension(std::string_view absPath) {
    const auto extension = absPath.substr(absPath.find_last_of('.') + 1);
    return extension.data();
}

std::string GetFilenameNoExtension(std::string_view absPath) {
    const auto nameWithExt =
        std::string(absPath.substr(absPath.find_last_of('/') + 1));
    const auto fileName = nameWithExt.substr(
        0, nameWithExt.find_last_of('.'));
    return fileName;
}
}