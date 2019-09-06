#include "utils.hpp"

#include <string>
#include <vector>
#include <unordered_map>
#include <ostream>
#include <functional>
#include <assert.h>
#include <fstream>
#include <sstream>

using std::string;
using std::vector;

namespace webio {

std::string ReadFile(std::string file_name) {
  std::ifstream fd(file_name);
  std::stringstream buffer;
  buffer << fd.rdbuf();
  fd.close();
  return buffer.str();
};

void WriteFile(std::string file_name, std::string content) {
  std::ofstream fd(file_name);
  fd << content;
  fd.close();
};

vector<string> SplitString(const string& input, char split_by, int limit) {
  vector<string> output;
  int first = 0;
  for (int i = 0; i < input.size(); i++) {
    if (input[i] == split_by) {
      output.push_back(input.substr(first, i-first));
      first = i+1;
      if (limit != -1 && output.size() >= limit) {
        break;
      }
    }
  }
  if (limit == -1 || output.size() < limit) {
    output.push_back(input.substr(first, input.size()-first));
  }
  return output;
}

} // namespace webio

