#pragma once


/*
The best approach is length-prefix encoding: <number_of_characters>#<string_content>
["hello", "world"] -> "5#hello5#world"
*/

#include <string>
#include <vector>

using namespace std;

class Solution271 {
public:
  // Encodes a list of strings to a single string.
  string encode(vector<string>& strs) {
    string encoded;

    for (const string& s : strs) {
      encoded += to_string(s.size());
      encoded += '#';
      encoded += s;
    }

    return encoded;
  }

  // Decodes a single string to a list of strings.
  vector<string> decode(string s) {
    vector<string> result;
    int i = 0;

    while (i < s.size()) {
      int j = i;

      // Find the delimiter after the length
      while (s[j] != '#') {
        j++;
      }

      // Extract length
      int length = stoi(s.substr(i, static_cast<std::string::size_type>(j) - i));

      // Move past '#'
      j++;

      // Extract the actual string
      result.push_back(s.substr(j, length));

      // Move to the next encoded string
      i = j + length;
    }

    return result;
  }
};
