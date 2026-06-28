"""
Post-rename cleanup script:
1. Adds #pragma once to all solution .hpp files (if not already present)
2. Replaces local TreeNode/ListNode struct definitions with #include "common_types.hpp"

Run from repo root:
    python add_pragma_and_fix_types.py
"""

import re
from pathlib import Path

SOLUTION_DIR = Path("src/LeetCode")

# Regex patterns to match the struct definitions (various formatting styles)
TREE_NODE_PATTERN = re.compile(
    r'(?://[^\n]*\n)*'           # Optional comment lines before
    r'\s*'                        # Leading whitespace
    r'(?://\s*Definition[^\n]*\n)?'  # Optional "// Definition for..." comment
    r'\s*'
    r'struct TreeNode\s*\{[^}]*\};',  # The struct itself
    re.DOTALL
)

LIST_NODE_PATTERN = re.compile(
    r'(?://[^\n]*\n)*'           # Optional comment lines before
    r'\s*'                        # Leading whitespace
    r'(?://\s*Definition[^\n]*\n)?'  # Optional "// Definition for..." comment
    r'\s*'
    r'struct ListNode\s*\{[^}]*\};',  # The struct itself
    re.DOTALL
)


def add_pragma_once(filepath: Path) -> bool:
    """Add #pragma once to a file if not already present. Returns True if modified."""
    content = filepath.read_text(encoding="utf-8", errors="replace")
    
    if "#pragma once" in content:
        return False
    
    filepath.write_text("#pragma once\n" + content, encoding="utf-8")
    return True


def replace_struct_definition(filepath: Path) -> bool:
    """Replace local TreeNode/ListNode definitions with #include. Returns True if modified."""
    content = filepath.read_text(encoding="utf-8", errors="replace")
    original = content
    
    has_tree_node = "struct TreeNode" in content
    has_list_node = "struct ListNode" in content
    
    if not has_tree_node and not has_list_node:
        return False
    
    # Remove the struct definitions
    if has_tree_node:
        content = TREE_NODE_PATTERN.sub("", content)
    if has_list_node:
        content = LIST_NODE_PATTERN.sub("", content)
    
    # Check if we actually removed something
    if content == original:
        # Regex didn't match - try a more aggressive approach
        lines = content.split("\n")
        new_lines = []
        i = 0
        while i < len(lines):
            line = lines[i]
            # Detect start of struct definition
            if re.match(r'\s*struct\s+(TreeNode|ListNode)\s*', line):
                # Skip until we find the closing };
                while i < len(lines) and "};" not in lines[i]:
                    i += 1
                i += 1  # skip the }; line too
                continue
            # Skip "// Definition for..." comment lines right before a removed struct
            if re.match(r'\s*//\s*Definition for', line):
                # Check if next non-empty line is a struct we're removing
                j = i + 1
                while j < len(lines) and lines[j].strip() == "":
                    j += 1
                if j < len(lines) and re.match(r'\s*struct\s+(TreeNode|ListNode)\s*', lines[j]):
                    i += 1
                    continue
            new_lines.append(line)
            i += 1
        content = "\n".join(new_lines)
    
    if content == original:
        return False
    
    # Add the include for common_types.hpp after #pragma once
    if '#include "common_types.hpp"' not in content:
        # Insert after #pragma once line
        content = content.replace(
            "#pragma once\n",
            '#pragma once\n#include "common_types.hpp"\n',
            1
        )
    
    filepath.write_text(content, encoding="utf-8")
    return True


def main():
    print("=== Adding #pragma once and fixing shared types ===\n")
    
    # Get all solution .hpp files
    hpp_files = sorted(SOLUTION_DIR.glob("0*.hpp"))
    print(f"Found {len(hpp_files)} solution headers.\n")
    
    # Also include common_types.hpp (already has pragma once)
    
    # Step 1: Add #pragma once to all files
    print("Adding #pragma once:")
    pragma_count = 0
    for f in hpp_files:
        if add_pragma_once(f):
            pragma_count += 1
    print(f"  Added to {pragma_count} files.\n")
    
    # Step 2: Replace struct definitions
    print("Replacing local TreeNode/ListNode definitions:")
    replaced_count = 0
    replaced_files = []
    for f in hpp_files:
        if replace_struct_definition(f):
            replaced_count += 1
            replaced_files.append(f.name)
            print(f"  Fixed: {f.name}")
    
    print(f"\n  Replaced definitions in {replaced_count} files.\n")
    
    if replaced_files:
        print("Files that now include common_types.hpp:")
        for name in replaced_files:
            print(f"  - {name}")
    
    print("\n=== Done! ===")


if __name__ == "__main__":
    main()
