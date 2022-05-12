/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: IO File
 */

#pragma once

#include <Kube/Core/Hash.hpp>

#include "Base.hpp"

namespace kF::IO
{
    class File;
}

class kF::IO::File
{
public:
    struct StreamHandle;


    /** @brief Destructor */
    ~File(void) noexcept;

    /** @brief Default constructor */
    File(void) noexcept = default;

    /** @brief Copy constructor */
    File(const File &path) noexcept = default;

    /** @brief Move constructor */
    File(File &&path) noexcept = default;

    /** @brief Set file of given 'path' */
    File(const std::string_view &path) noexcept;

    /** @brief Copy assignment */
    File &operator=(const File &path) noexcept = default;

    /** @brief Move assignment */
    File &operator=(File &&path) noexcept = default;


    /** @brief Get file path */
    [[nodiscard]] std::string_view path(void) const noexcept { return _path; }


    /** @brief Check if the file is a resource file (embedded into the executable) */
    [[nodiscard]] inline bool isResource(void) const noexcept { return _environmentHash; }

    /** @brief Get environment name */
    [[nodiscards]] inline Core::HashedName environmentHash(void) const noexcept { return _environmentHash; }

    /** @brief Get environment name */
    [[nodiscards]] inline std::string_view environment(void) const noexcept
        { return _path.substr(EnvironmentBeginIndex, _environmentTo - EnvironmentBeginIndex); }


    /** @brief Check if resource exists */
    [[nodiscard]] bool resourceExists(void) const noexcept;

    /** @brief Get resource path */
    [[nodiscards]] inline std::string_view resourcePath(void) const noexcept
        { return _path.substr(_environmentTo + 1); }

    /** @brief Query a resource */
    [[nodiscard]] ResourceView queryResource(void) const noexcept;


    /** @brief Get the file size */
    [[nodiscard]] std::size_t fileSize(void) const noexcept;


    /** @brief Read data and store it into range
     *  @param offset Offset in byte from where to start reading the file */
    [[nodiscard]] std::size_t read(std::uint8_t * const from, std::uint8_t * const to, const std::size_t offset) noexcept;


private:
    /** @brief Ensure that this instance has an allocated stream */
    void ensureStream(void) noexcept;


    std::string_view _path {};
    Core::HashedName _environmentHash {};
    std::uint32_t _environmentTo {};
    StreamHandle *_stream {};
};