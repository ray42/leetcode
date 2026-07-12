#pragma once
#include <string>
#include <stack>
#include <vector>

class Solution71 {
public:
  std::string simplifyPath(std::string& path) const {
    // Using a vector as a stack to store the valid directory names.
    auto components = std::vector<std::string>{};
    auto currentComponent = std::string{};

    path.push_back('/'); // Append a trailing slash to handle the last component.

    for (auto c : path) 
    {
        if (c == '/') // We reached the end of one path component.
        {
          if (currentComponent == "" || currentComponent == ".")
          {
            // Ignore empty components and current directory references.
          }
          else if(currentComponent == "..")
          {
            if (!components.empty()) 
            {
              components.pop_back(); // Go up one directory.
            }
          }
          else
          {
            // Normal directory name.
            // Important: "..." or "..hidden" are NOT special.
            // Example: "/a/.../b" keeps "..."
            components.push_back(currentComponent); // Valid directory name.
          }
          currentComponent.clear(); // Reset for the next component.
        }
        else 
        {
          currentComponent += c; // Build the current component.
        }
    }
    
    // Construct the simplified path from the components.
    auto simplifiedPath = std::string{};
    for (const auto& component : components) {
        simplifiedPath += "/" + component;
    }
    return simplifiedPath.empty() ? "/" : simplifiedPath;
  }
};
