#pragma once

#include <string>

namespace embed {
    class File {
        const unsigned char* start;
        const unsigned char* end;
    public:
        inline File(const unsigned char* start, const unsigned char* end) : start(start), end(end) {}
        inline File(const unsigned char* start, size_t size) : start(start), end(start + size) {}

        const unsigned char* data() const { return start; }
        size_t size() const { return end - start; }
    };

    File get(const std::string& path);
}