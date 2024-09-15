//
// Created by hua on 2024/9/15.
//

#include "string_utils.h"

bool StringUtils::startWidth(const std::string &str, const std::string &prefix) {
    return str.substr(0, prefix.size()) == prefix;
}
