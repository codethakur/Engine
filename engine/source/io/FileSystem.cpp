#include "io/FileSystem.h"
#include <mach-o/dyld.h>
#include<string>
#include"config.h"
#if defined _Win32
#include <window.h>
#elif defined(__APPLE__)
#include <mach-o/dyld.h>
#elif defined(__linux)
#include <unistd.h>
#include <limits.h>
#endif
namespace eng
{
    std::filesystem::path FileSystem::GetExecutablFolder() const {
#if defined _Win32
        wchar_t buf[MAX_PATH]
        GetModuleFileNameW(NULL, buf, MAX_PATH);
        return std::filesystem::path(buf).remove_filename();
#elif defined(__APPLE__)
        uint32_t size = 0;
        _NSGetExecutablePath(nullptr, &size);
        std::string temp(size, '\0');
        _NSGetExecutablePath(temp.data(), &size);
        return std::filesystem::weakly_canonical(std::filesystem::path(temp)).remove_filename();
#elif defined(__linux)
        return std::filesystem::weakly_canonical(std::filesystem::read_symlink("/proc/sef/exe")).remove_filename();
#else
        return std::filesystem::current_path();
#endif
    }
    std::filesystem::path FileSystem::GetAssertFolder() const
    {
    #if defined(ASSERT_ROOT)
        auto path =  std::filesystem::path (std::string(ASSERT_ROOT));
        if( std::filesystem::exits(path))
        {
            return path;
        } 
    #endif
        return std::filesystem::weakly_canonical(GetExecutablFolder()/"assets");
    }
}
