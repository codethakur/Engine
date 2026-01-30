#pragma once
#include <filesystem>
#include <vector>
#include<string>
namespace eng
{
    class FileSystem
    {
    public:
        std::filesystem::path GetExecutablFolder() const;
        std::filesystem::path GetAssetFolder() const;

        std::vector<char> LoadFile(const std::filesystem::path &path);
        std::vector<char>LoadAssetFile(const std::string& relativePath);
        std::string LoadAssetFileText(const std::string& relativePath);
    };
}