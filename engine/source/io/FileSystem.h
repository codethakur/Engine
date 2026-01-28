#pragma once
#include <filesystem>
namespace eng
{
    class FileSystem
    {
    public:
        std::filesystem::path GetExecutablFolder() const;
        std::filesystem::path GetAssertFolder()const;
    };
}