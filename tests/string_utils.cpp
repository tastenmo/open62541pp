#include <cstring>

#include <catch2/catch_test_macros.hpp>

#include "open62541pp/detail/string_utils.hpp"

using namespace opcua;

TEST_CASE("UA_String from string_view") {
    SECTION("Test string") {
        std::string_view sv{"test123"};
        UA_String str = detail::toNativeString(sv);
        CHECK(str.length == sv.size());
        CHECK((void*)str.data == (void*)sv.data());
    }

    SECTION("Null string") {
        UA_String str = detail::toNativeString({});
        CHECK(str.length == 0);
        CHECK(str.data == nullptr);
    }

    SECTION("Empty string") {
        UA_String str = detail::toNativeString("");
        CHECK(str.length == 0);
        CHECK(str.data != nullptr);
    }
}

TEST_CASE("Alloc UA_String from string_view") {
    const char* cstr = "test123";
    std::string_view sv{cstr};
    auto str = detail::allocNativeString(sv);
    CHECK(str.length == 7);
    CHECK(std::strncmp((char*)str.data, sv.data(), 7) == 0);  // NOLINT
    UA_clear(&str, &UA_TYPES[UA_TYPES_STRING]);
}

TEST_CASE("Alloc const char* from string_view") {
    const char* cstr = detail::allocCString("test123");
    CHECK(std::strlen(cstr) == 7);
    CHECK(std::strcmp(cstr, "test123") == 0);
    CHECK(cstr[7] == '\0');  // NOLINT
    detail::clear(cstr);
}

TEST_CASE("Alloc UA_String from non-null-terminated string_view") {
    std::string str{"test123"};
    std::string_view sv(str.c_str(), 4);
    auto uaString = detail::allocNativeString(sv);
    CHECK(uaString.length == 4);
    CHECK(std::strncmp((char*)uaString.data, sv.data(), 4) == 0);  // NOLINT
    UA_clear(&uaString, &UA_TYPES[UA_TYPES_STRING]);
}

TEST_CASE("String conversion UA_String -> string") {
    SECTION("Test string") {
        UA_String str = UA_STRING_ALLOC("test123");
        CHECK(detail::toStringView(str) == "test123");
        UA_clear(&str, &UA_TYPES[UA_TYPES_STRING]);
    }

    SECTION("Null string") {
        UA_String str{};
        CHECK(detail::toStringView(str) == "");
    }

    SECTION("Empty string") {
        UA_String str = UA_STRING_ALLOC("");
        CHECK(detail::toStringView(str) == "");
        UA_clear(&str, &UA_TYPES[UA_TYPES_STRING]);
    }
}
