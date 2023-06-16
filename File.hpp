/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: IO File
 */

#pragma once

#include <Kube/Core/Hash.hpp>
#include <Kube/Core/SmallString.hpp>

#include "Base.hpp"

namespace kF::IO
{
    class File;

    namespace Internal
    {
        template<typename Container>
        concept ResizableContainer =
            (sizeof(std::remove_cvref_t<decltype(*std::declval<Container>().data())>) == sizeof(std::byte))
            && requires(Container &container) {
                container.data();
                container.size();
                container.resize(std::declval<std::size_t>());
            };
    }
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

    /** @brief Get file name */
    [[nodiscard]] std::string_view filename(void) const noexcept;


    /** @brief Check if the file is a resource file (embedded into the executable) */
    [[nodiscard]] inline bool isResource(void) const noexcept { return _environmentHash; }

    /** @brief Get environment name */
    [[nodiscard]] inline Core::HashedName environmentHash(void) const noexcept { return _environmentHash; }

    /** @brief Get environment name */
    [[nodiscard]] inline std::string_view environment(void) const noexcept
        { return _path.toView().substr(EnvironmentBeginIndex, _environmentTo - EnvironmentBeginIndex); }


    /** @brief Check if resource exists */
    [[nodiscard]] bool resourceExists(void) const noexcept;

    /** @brief Get resource path */
    [[nodiscard]] inline std::string_view resourcePath(void) const noexcept
        { return _path.toView().substr(_environmentTo + 1); }

    /** @brief Query a resource */
    [[nodiscard]] ResourceView queryResource(void) const noexcept;


    /** @brief Check if the file exists */
    [[nodiscard]] bool exists(void) const noexcept;

    /** @brief Get the file size */
    [[nodiscard]] std::size_t fileSize(void) const noexcept;


    /** @brief Get current offset */
    [[nodiscard]] std::size_t offset(void) const noexcept { return _offset; }

    /** @brief Set read offset */
    void setReadOffset(const std::size_t offset) noexcept;


    /** @brief Read data and store it into range (use internal offset) */
    [[nodiscard]] inline std::size_t read(std::uint8_t * const from, std::uint8_t * const to) noexcept
        { return read(from, to, _offset); }

    /** @brief Read data and store it into range
     *  @param offset Offset in byte from where to start reading the file */
    [[nodiscard]] std::size_t read(std::uint8_t * const from, std::uint8_t * const to, const std::size_t offset) noexcept;

    /** @brief Read all file data and store it into custom container */
    template<kF::IO::Internal::ResizableContainer Container>
    [[nodiscard]] bool readAll(Container &container) noexcept;

    /** @brief Read all file data and store it into custom container */
    template<kF::IO::Internal::ResizableContainer Container>
    [[nodiscard]] Container readAll(void) noexcept;


    /** @brief Copy file to another location */
    bool copy(const std::string_view &destination) const noexcept;

    /** @brief remove file */
    bool remove(void) const noexcept;


private:
    /** @brief Ensure that this instance has an allocated stream */
    void ensureStream(void) noexcept;


    Core::SmallString<IOAllocator> _path {};
    Core::HashedName _environmentHash {};
    std::uint32_t _environmentTo {};
    StreamHandle *_stream {};
    std::size_t _offset {};
};

#include "File.ipp"