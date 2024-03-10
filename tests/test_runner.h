#pragma once

#include <iostream>
#include <sstream>
#include <string>

#include "../src/AdvAuction.h"

template <typename U>
std::ostream& operator<<(std::ostream& os, const std::vector<U> vec) {
    os << "{";
    for (int i = 0; i < vec.size(); ++i) {
        os << vec[i] << " ";
    }
    os << "}" << std::endl;

    return os;
}

std::ostream& operator<<(std::ostream& os, const Banner banner) {
    os << "{";
    os << banner.price << " " << banner.campaign_id;
    os << "{";
    for (int i = 0; i != banner.countries.size(); ++i) {
        os << banner.countries[i] << " ";
    }
    os << "} ";
    os << banner.internal_id;
    os << "}" << std::endl;

    return os;
}

bool operator==(const Banner& left, const Banner& right) {
    return left.price == right.price && left.campaign_id == right.campaign_id
        && left.countries == right.countries && left.internal_id == right.internal_id;
}

template <class T, class U>
void AssertEqual(const T& t, const U& u, const std::string& hint = {}) {
    if (!(t == u)) {
        std::ostringstream os;
        os << "Assertion failed: " << t << " != " << u;
        if (!hint.empty()) {
            os << " hint: " << hint;
        }
        throw std::runtime_error(os.str());
    }
}

inline void Assert(bool b, const std::string& hint) {
    AssertEqual(b, true, hint);
}

class TestRunner {
public:
    template <class TestFunc>
    void RunTest(TestFunc func, const std::string& test_name) {
        try {
            func();
            std::cerr << test_name << " OK" << std::endl;
        }
        catch (std::exception& e) {
            ++fail_count;
            std::cerr << test_name << " fail: " << e.what() << std::endl;
        }
        catch (...) {
            ++fail_count;
            std::cerr << "Unknown exception caught" << std::endl;
        }
    }

    ~TestRunner() {
        std::cerr.flush();
        if (fail_count > 0) {
            std::cerr << fail_count << " unit tests failed. Terminate" << std::endl;
            exit(1);
        }
    }

private:
    int fail_count = 0;
};

#ifndef FILE_NAME
#define FILE_NAME __FILE__
#endif

#define ASSERT_EQUAL(x, y)                                               \
  {                                                                      \
    std::ostringstream __assert_equal_private_os;                        \
    __assert_equal_private_os << #x << " != " << #y << ", " << FILE_NAME \
                              << ":" << __LINE__;                        \
    AssertEqual(x, y, __assert_equal_private_os.str());                  \
  }

#define ASSERT(x)                                                  \
  {                                                                \
    std::ostringstream __assert_private_os;                        \
    __assert_private_os << #x << " is false, " << FILE_NAME << ":" \
                        << __LINE__;                               \
    Assert(x, __assert_private_os.str());                          \
  }

#define RUN_TEST(tr, func) tr.RunTest(func, #func)
