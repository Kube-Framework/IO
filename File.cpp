/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: IO File
 */

#include <fstream>
#include <filesystem>

#include <Kube/Core/Abort.hpp>
#include <Kube/Core/Assert.hpp>

#include "File.hpp"
#include "ResourceManager.hpp"

using namespace kF;

struct IO::File::StreamHandle
{
    std::ifstream ifs;
    std::size_t fileSize {};
};

IO::File::~File(void) noexcept
{
    if (_stream) [[unlikely]] {
        _stream->~StreamHandle();
        IOAllocator::Deallocate(_stream, sizeof(StreamHandle), alignof(StreamHandle));
    }
}

IO::File::File(const std::string_view &path) noexcept
    : _path(path)
{
    if (path.starts_with(ResourcePrefix)) {
        const auto to = static_cast<std::uint32_t>(path.find('/', EnvironmentBeginIndex));
        _environmentTo = to;
        _environmentHash = Core::Hash(path.substr(EnvironmentBeginIndex, to - EnvironmentBeginIndex));
    }
}

bool IO::File::resourceExists(void) const noexcept
{
    return ResourceManager::Get().resourceExists(
        _environmentHash,
        resourcePath()
    );
}

IO::ResourceView IO::File::queryResource(void) const noexcept
{
    return ResourceManager::Get().queryResource(
        _environmentHash,
        resourcePath()
    );
}

std::size_t IO::File::fileSize(void) const noexcept
{
    if (isResource()) {
        return queryResource().size();
    } else {
        return std::filesystem::file_size(_path);
    }
}

std::size_t IO::File::read(std::uint8_t * const from, std::uint8_t * const to, const std::size_t offset) noexcept
{
    constexpr auto GetReadSize = [](const std::size_t offset, const std::size_t desired, const std::size_t size) {
        if (offset < size) [[likely]]
            return std::min(size - offset, desired);
        else [[unlikely]]
            return static_cast<std::size_t>(0ul);
    };

    const auto count = static_cast<std::size_t>(std::distance(from, to));

    if (isResource()) {
        const auto range = queryResource();
        const auto readCount = GetReadSize(offset, count, range.size());
        if (readCount) [[likely]] {
            const auto begin = range.begin() + offset;
            std::copy(begin, begin + readCount, from);
        }
        return readCount;
    } else {
        ensureStream();
        const auto readCount = GetReadSize(offset, count, _stream->fileSize);
        if (readCount) [[likely]] {
            _stream->ifs.seekg(offset);
            if (_stream->ifs.good())
                _stream->ifs.read(reinterpret_cast<char *>(from), readCount);
            else
                return 0u;
        }
        return readCount;
    }
}

void kF::IO::File::ensureStream(void) noexcept
{
    if (!_stream) [[unlikely]] {
        const auto alloc = IOAllocator::Allocate(sizeof(StreamHandle), alignof(StreamHandle));
        _stream = new (alloc) StreamHandle {
            .ifs = std::ifstream(std::string(_path), std::ios::binary | std::ios::ate),
            .fileSize = std::filesystem::file_size(_path)
        };
        kFEnsure(_stream->ifs.good(),
            "UI::File::ensureStream: Stream opened with invalid file path '", _path, '\'');
    }
}