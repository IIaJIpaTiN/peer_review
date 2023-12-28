#pragma once
#include <string>
#include <string_view>
#include <vector>
#include <algorithm>
#include <iostream>

class Domain {
public:
    Domain() = default;
    Domain(std::string_view name) : name_(std::string(name.rbegin(), name.rend())) {
        name_.push_back('.');
    }

    bool IsSubdomain(const Domain& other) const {
        if (name_.size() < other.name_.size()) {
            return false;
        }

        for (size_t i = 0; i < other.name_.size(); ++i) {
            if (name_[i] != other.name_[i]) {
                return false;
            }
        }

        return true;
    }

    bool operator==(const Domain& other) const {
        return name_ == other.name_;
    }

    bool operator!=(const Domain& other) const {
        return !(*this == other);
    }

    bool operator<(const Domain& other) const {
        return name_ < other.name_;
    }

private:
    std::string name_;
};

class DomainChecker {
public:
    template<typename It>
    DomainChecker(It begin, It end) : banned_domains_(begin, end) {
        std::sort(banned_domains_.begin(), banned_domains_.end());
        auto new_end = std::unique(banned_domains_.begin(), banned_domains_.end(),
                              [](const Domain& lhs, const Domain& rhs) {
                                  return lhs == rhs || rhs.IsSubdomain(lhs);
                              });
        banned_domains_.resize(new_end - banned_domains_.begin());
    }

    bool IsForbidden(const Domain& domain) const {
        auto it = std::upper_bound(banned_domains_.begin(), banned_domains_.end(), domain);
        return it != banned_domains_.begin() && domain.IsSubdomain(*(it - 1));
    }

private:
    std::vector<Domain> banned_domains_;
};

std::vector<Domain> ReadDomains(std::istream& input, size_t count) {
    std::vector<Domain> result;
    result.reserve(count);

    for (size_t i = 0; i < count; ++i) {
        std::string line;
        std::getline(input, line);
        result.emplace_back(line);
    }

    return result;
}
