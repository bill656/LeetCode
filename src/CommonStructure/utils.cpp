#include "CommonStructure/utils.h"

#include <sstream>

std::string serialize(const std::vector<int>& vec) {
    std::string out = "[";
    for (int i = 0; i < vec.size(); ++i) {
        out += std::to_string(vec[i]);
        if (i != vec.size() - 1) out += ',';
    }
    out += ']';
    return out;
}

std::string serialize(const std::vector<std::vector<int>>& vec) {
    std::string res = "[";
    for (int i = 0; i < vec.size(); ++i) {
        res += serialize(vec[i]);
        if (i != vec.size() - 1) res += ',';
    }
    res += "]";
    return res;
}

std::vector<std::string_view> stringSplit(const std::string_view& str, const std::string& delim) {
    size_t previous = 0;
    size_t current = str.find_first_of(delim);
    std::vector<std::string_view> elems;
    while (current != std::string_view::npos) {
        if (current > previous)
            elems.emplace_back(str.substr(previous, current - previous));
        previous = current + 1;
        current = str.find_first_of(delim, previous);
    }
    if (previous != str.size())
        elems.emplace_back(str.substr(previous));
    return elems;
}

std::vector<int> vectorDeserializer1d(const std::string_view& str) {
    auto s = str.substr(1, str.length() - 2);
    auto&& items = stringSplit(s, ",");
    std::vector<int> res;
    for (const auto& item: items) {
        std::stringstream stream;
        stream << item;
        int val;
        if (item == "null") val = -1;
        else
            stream >> val;
        res.push_back(val);
    }
    return res;
}
