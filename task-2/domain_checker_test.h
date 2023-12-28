#pragma once
#include "domain_checker.h"
#include <cassert>
#include <sstream>
#include <vector>

using namespace std::string_literals;

namespace detail {

void TestDomainEquals() {
    const Domain d1 = Domain("example.com"s);
    const Domain d2 = Domain("example.com"s);
    const Domain d3 = Domain("example.net"s);

    assert(d1 == d2);
    assert(d1 != d3);
}

void TestIsSubdomain() {
    const Domain d1 = Domain("gdz.ru"s);
    const Domain d2 = Domain("math.gdz.ru"s);
    const Domain d3 = Domain("freegdz.ru"s);

    assert(d2.IsSubdomain(d1));
    assert(!d3.IsSubdomain(d1));
}

void TestReadDomains() {
    std::istringstream input("example.com\nexample.net\nexample.org\nexample.ru\n"s);
    const auto domains = ReadDomains(input, 4);

    assert(domains.size() == 4);
    assert(domains[0] == Domain("example.com"s));
    assert(domains[1] == Domain("example.net"s));
    assert(domains[2] == Domain("example.org"s));
    assert(domains[3] == Domain("example.ru"s));
}

void TestIsForbidden() {
    const auto banned_domains = std::vector<Domain>{Domain("math.gdz.ru"s), Domain("gdz.ru"s),
                                                    Domain("example.coz"s), Domain("hhhhh.ru"s)};
    DomainChecker checker(banned_domains.begin(), banned_domains.end());

    assert(checker.IsForbidden(Domain("math.gdz.ru"s)));
    assert(!checker.IsForbidden(Domain("freegdz.ru"s)));
}

} // namespace detail;

void TestDomainChecker() {
    using namespace detail;

    TestDomainEquals();
    TestIsSubdomain();
    TestReadDomains();
    TestIsForbidden();
}