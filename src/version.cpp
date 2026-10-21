#include "j1939/version.hpp"

constexpr std::string_view j1939_version = "1.0";

std::string_view j1939::version() noexcept {
    return j1939_version;
}