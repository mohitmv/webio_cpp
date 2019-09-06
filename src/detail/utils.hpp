#ifndef _WEBIO_UTILS_HPP_
#define _WEBIO_UTILS_HPP_

#include <string>
#include <vector>
#include <unordered_map>
#include <map>

namespace webio {


std::string ReadFile(std::string file_name);

void WriteFile(std::string file_name, std::string content);

std::vector<std::string> SplitString(const std::string& input, char split_by, int limit=-1);

namespace quick {

template <typename ContainerType, class KeyType>
bool ContainsKey(const ContainerType& container, const KeyType& key) {
  return container.find(key) != container.end();
}

}

namespace qk = quick;


} // namespace webio

#endif //  _WEBIO_UTILS_HPP_
