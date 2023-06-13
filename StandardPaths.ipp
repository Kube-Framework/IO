/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: IO StandardPaths
 */

#include <Kube/Core/Platform.hpp>

#if KUBE_COMPILER_GCC | KUBE_COMPILER_CLANG
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsign-conversion"
#endif
#include <whereami.h>
#if KUBE_COMPILER_GCC | KUBE_COMPILER_CLANG
#pragma GCC diagnostic pop
#endif

#include <platform_folders.h>

#include <Kube/Core/Abort.hpp>

#include "StandardPaths.hpp"

template<typename Type>
Type kF::IO::GetExecutablePath(void) noexcept
{
    using Range = decltype(std::size(std::declval<Type>()));

    // Init container
    const auto expectedSize = wai_getExecutablePath(nullptr, 0, nullptr);
    if (expectedSize == -1) [[unlikely]]
        return Type {};
    Type container(static_cast<Range>(expectedSize));

    // Query path
    const auto finalSize = wai_getExecutablePath(container.data(), static_cast<int>(container.size()), nullptr);
    kFEnsure(finalSize == expectedSize,
        "IO::GetExecutableDirectory: Couldn't retreive executable path");

    return container;
}

template<typename Type>
Type kF::IO::GetExecutableDirectory(void) noexcept
{
    using Range = decltype(std::size(std::declval<Type>()));

    // Init container
    const auto expectedSize = wai_getModulePath(nullptr, 0, nullptr);
    if (expectedSize == -1) [[unlikely]]
        return Type {};
    Type container(static_cast<Range>(expectedSize));

    // Query path
    int dirIndex {};
    const auto finalSize = wai_getModulePath(container.data(), static_cast<int>(container.size()), &dirIndex);
    kFEnsure(finalSize == expectedSize,
        "IO::GetExecutableDirectory: Couldn't retreive executable path");

#if KUBE_PLATFORM_APPLE
    // @todo fix this
    while (!container.empty() && container.back() != '/')
        container.pop();
#endif
    return container;
}

template<typename Type>
Type kF::IO::GetConfigPath(void) noexcept
{
    return Type(std::string_view(sago::getConfigHome()));
}

template<typename Type>
Type kF::IO::GetDataPath(void) noexcept
{
    return Type(std::string_view(sago::getDataHome()));
}

template<typename Type>
Type kF::IO::GetStatePath(void) noexcept
{
    return Type(std::string_view(sago::getStateDir()));
}

template<typename Type>
Type kF::IO::GetCachePath(void) noexcept
{
    return Type(std::string_view(sago::getCacheDir()));
}

template<typename Type>
Type kF::IO::GetDocumentsPath(void) noexcept
{
    return Type(std::string_view(sago::getDocumentsFolder()));
}

template<typename Type>
Type kF::IO::GetDesktopPath(void) noexcept
{
    return Type(std::string_view(sago::getDesktopFolder()));
}

template<typename Type>
Type kF::IO::GetPicturesPath(void) noexcept
{
    return Type(std::string_view(sago::getPicturesFolder()));
}

template<typename Type>
Type kF::IO::GetMusicPath(void) noexcept
{
    return Type(std::string_view(sago::getMusicFolder()));
}

template<typename Type>
Type kF::IO::GetVideoPath(void) noexcept
{
    return Type(std::string_view(sago::getVideoFolder()));
}

template<typename Type>
Type kF::IO::GetDownloadPath(void) noexcept
{
    return Type(std::string_view(sago::getDownloadFolder()));
}

template<typename Type>
Type kF::IO::GetSavePath(void) noexcept
{
    return Type(std::string_view(sago::getSaveGamesFolder1()));
}
