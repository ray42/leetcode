"""
Generate Google Test stub files for all solution headers that contain classes.
Skips files that already have a test file.
Also updates LeetCodeTests.vcxproj and .filters.

Run from repo root:
    python generate_test_stubs.py
"""

import re
from pathlib import Path

SOLUTION_DIR = Path("src/LeetCode")
TEST_DIR = Path("src/LeetCodeTests")


def find_solution_classes(filepath: Path) -> list[tuple[str, str]]:
    """Find class names and their first public method signature in a solution file.
    Returns list of (class_name, method_signature) tuples."""
    content = filepath.read_text(encoding="utf-8", errors="replace")
    
    # Find all class definitions with their names
    classes = []
    # Match class ClassName { ... public: ... first_method
    class_pattern = re.compile(
        r'class\s+(\w+)\s*(?::\s*[^{]*)?\{',
        re.MULTILINE
    )
    
    for match in class_pattern.finditer(content):
        class_name = match.group(1)
        # Skip helper classes like ArrayHash, nested structs
        if class_name in ('TreeNode', 'ListNode', 'Node'):
            continue
        classes.append(class_name)
    
    return classes


def generate_test_content(header_name: str, classes: list[str]) -> str:
    """Generate a test file stub for the given header and its classes."""
    lines = []
    lines.append('#include <gtest/gtest.h>')
    lines.append(f'#include "{header_name}"')
    lines.append('')
    
    # Use the first class for the test suite name (strip "Solution" prefix variations)
    # Extract problem number from header name
    problem_num = header_name.split('_')[0].lstrip('0') or '0'
    
    # Extract problem name for test suite
    problem_name = header_name.replace('.hpp', '')
    # Remove the number prefix: "00001_TwoSum" -> "TwoSum"
    parts = problem_name.split('_', 1)
    if len(parts) > 1:
        suite_name = parts[1]
    else:
        suite_name = problem_name
    
    # Generate a placeholder test for the first (primary) class
    primary_class = classes[0] if classes else f"Solution{problem_num}"
    
    lines.append(f'TEST({suite_name}, Placeholder) {{')
    lines.append(f'    // TODO: Add test cases for {primary_class}')
    lines.append(f'    EXPECT_TRUE(true);')
    lines.append(f'}}')
    lines.append('')
    
    return '\n'.join(lines)


def get_existing_test_files() -> set[str]:
    """Get basenames of existing test files (without extension)."""
    existing = set()
    for f in TEST_DIR.glob("*.cpp"):
        existing.add(f.stem)
    return existing


def generate_vcxproj(test_files: list[str]):
    """Regenerate LeetCodeTests.vcxproj with all test files."""
    
    cl_compile_entries = "\n".join(
        f'    <ClCompile Include="{f}" />'
        for f in sorted(test_files)
    )
    
    content = f'''<?xml version="1.0" encoding="utf-8"?>
<Project DefaultTargets="Build" xmlns="http://schemas.microsoft.com/developer/msbuild/2003">
  <ItemGroup Label="ProjectConfigurations">
    <ProjectConfiguration Include="Debug|x64">
      <Configuration>Debug</Configuration>
      <Platform>x64</Platform>
    </ProjectConfiguration>
    <ProjectConfiguration Include="Release|x64">
      <Configuration>Release</Configuration>
      <Platform>x64</Platform>
    </ProjectConfiguration>
  </ItemGroup>
  <PropertyGroup Label="Globals">
    <VCProjectVersion>18.0</VCProjectVersion>
    <Keyword>Win32Proj</Keyword>
    <ProjectGuid>{{A1B2C3D4-E5F6-7890-ABCD-EF1234567890}}</ProjectGuid>
    <RootNamespace>LeetCodeTests</RootNamespace>
    <WindowsTargetPlatformVersion>10.0</WindowsTargetPlatformVersion>
  </PropertyGroup>
  <Import Project="$(VCTargetsPath)\\Microsoft.Cpp.Default.props" />
  <PropertyGroup Condition="'$(Configuration)|$(Platform)'=='Debug|x64'" Label="Configuration">
    <ConfigurationType>Application</ConfigurationType>
    <UseDebugLibraries>true</UseDebugLibraries>
    <PlatformToolset>v145</PlatformToolset>
    <CharacterSet>Unicode</CharacterSet>
  </PropertyGroup>
  <PropertyGroup Condition="'$(Configuration)|$(Platform)'=='Release|x64'" Label="Configuration">
    <ConfigurationType>Application</ConfigurationType>
    <UseDebugLibraries>false</UseDebugLibraries>
    <PlatformToolset>v145</PlatformToolset>
    <WholeProgramOptimization>true</WholeProgramOptimization>
    <CharacterSet>Unicode</CharacterSet>
  </PropertyGroup>
  <Import Project="$(VCTargetsPath)\\Microsoft.Cpp.props" />
  <ImportGroup Label="ExtensionSettings">
  </ImportGroup>
  <ImportGroup Label="Shared">
  </ImportGroup>
  <ImportGroup Label="PropertySheets" Condition="'$(Configuration)|$(Platform)'=='Debug|x64'">
    <Import Project="$(UserRootDir)\\Microsoft.Cpp.$(Platform).user.props" Condition="exists('$(UserRootDir)\\Microsoft.Cpp.$(Platform).user.props')" Label="LocalAppDataPlatform" />
  </ImportGroup>
  <ImportGroup Label="PropertySheets" Condition="'$(Configuration)|$(Platform)'=='Release|x64'">
    <Import Project="$(UserRootDir)\\Microsoft.Cpp.$(Platform).user.props" Condition="exists('$(UserRootDir)\\Microsoft.Cpp.$(Platform).user.props')" Label="LocalAppDataPlatform" />
  </ImportGroup>
  <PropertyGroup Label="UserMacros" />
  <PropertyGroup>
    <VcpkgRoot Condition="Exists('$(LOCALAPPDATA)\\vcpkg\\vcpkg.path.txt')">$([System.IO.File]::ReadAllText('$(LOCALAPPDATA)\\vcpkg\\vcpkg.path.txt').Trim())</VcpkgRoot>
    <VcpkgTriplet>x64-win-utc</VcpkgTriplet>
  </PropertyGroup>
  <ItemDefinitionGroup Condition="'$(Configuration)|$(Platform)'=='Debug|x64'">
    <ClCompile>
      <WarningLevel>Level3</WarningLevel>
      <SDLCheck>true</SDLCheck>
      <PreprocessorDefinitions>_DEBUG;_CONSOLE;%(PreprocessorDefinitions)</PreprocessorDefinitions>
      <ConformanceMode>true</ConformanceMode>
      <LanguageStandard>stdcpp20</LanguageStandard>
      <AdditionalIncludeDirectories>$(VcpkgRoot)\\installed\\$(VcpkgTriplet)\\include;..\\LeetCode;%(AdditionalIncludeDirectories)</AdditionalIncludeDirectories>
    </ClCompile>
    <Link>
      <SubSystem>Console</SubSystem>
      <GenerateDebugInformation>true</GenerateDebugInformation>
      <AdditionalLibraryDirectories>$(VcpkgRoot)\\installed\\$(VcpkgTriplet)\\debug\\lib;%(AdditionalLibraryDirectories)</AdditionalLibraryDirectories>
      <AdditionalDependencies>gtest.lib;%(AdditionalDependencies)</AdditionalDependencies>
    </Link>
  </ItemDefinitionGroup>
  <ItemDefinitionGroup Condition="'$(Configuration)|$(Platform)'=='Release|x64'">
    <ClCompile>
      <WarningLevel>Level3</WarningLevel>
      <FunctionLevelLinking>true</FunctionLevelLinking>
      <IntrinsicFunctions>true</IntrinsicFunctions>
      <SDLCheck>true</SDLCheck>
      <PreprocessorDefinitions>NDEBUG;_CONSOLE;%(PreprocessorDefinitions)</PreprocessorDefinitions>
      <ConformanceMode>true</ConformanceMode>
      <LanguageStandard>stdcpp20</LanguageStandard>
      <AdditionalIncludeDirectories>$(VcpkgRoot)\\installed\\$(VcpkgTriplet)\\include;..\\LeetCode;%(AdditionalIncludeDirectories)</AdditionalIncludeDirectories>
    </ClCompile>
    <Link>
      <SubSystem>Console</SubSystem>
      <GenerateDebugInformation>true</GenerateDebugInformation>
      <AdditionalLibraryDirectories>$(VcpkgRoot)\\installed\\$(VcpkgTriplet)\\lib;%(AdditionalLibraryDirectories)</AdditionalLibraryDirectories>
      <AdditionalDependencies>gtest.lib;%(AdditionalDependencies)</AdditionalDependencies>
    </Link>
  </ItemDefinitionGroup>
  <ItemGroup>
{cl_compile_entries}
  </ItemGroup>
  <Import Project="$(VCTargetsPath)\\Microsoft.Cpp.targets" />
  <ImportGroup Label="ExtensionTargets">
  </ImportGroup>
</Project>
'''
    
    outpath = TEST_DIR / "LeetCodeTests.vcxproj"
    outpath.write_text(content, encoding="utf-8")
    print(f"  Generated: {outpath}")


def generate_filters(test_files: list[str]):
    """Regenerate LeetCodeTests.vcxproj.filters."""
    
    cl_compile_entries = "\n".join(
        f'    <ClCompile Include="{f}">\n'
        f'      <Filter>Source Files</Filter>\n'
        f'    </ClCompile>'
        for f in sorted(test_files)
    )
    
    content = f'''<?xml version="1.0" encoding="utf-8"?>
<Project ToolsVersion="4.0" xmlns="http://schemas.microsoft.com/developer/msbuild/2003">
  <ItemGroup>
    <Filter Include="Source Files">
      <UniqueIdentifier>{{4FC737F1-C7A5-4376-A066-2A32D752A2FF}}</UniqueIdentifier>
      <Extensions>cpp;c;cc;cxx;c++;cppm;ixx;def;odl;idl;hpj;bat;asm;asmx</Extensions>
    </Filter>
  </ItemGroup>
  <ItemGroup>
{cl_compile_entries}
  </ItemGroup>
</Project>
'''
    
    outpath = TEST_DIR / "LeetCodeTests.vcxproj.filters"
    outpath.write_text(content, encoding="utf-8")
    print(f"  Generated: {outpath}")


def main():
    print("=== Generating Test Stubs ===\n")
    
    # Find all solution headers with classes
    solution_files = sorted(SOLUTION_DIR.glob("0*.hpp"))
    existing_tests = get_existing_test_files()
    
    created = 0
    all_test_files = ["tests_main.cpp"]  # Always include main
    
    # Add existing test files
    for f in TEST_DIR.glob("*.cpp"):
        if f.stem != "tests_main":
            all_test_files.append(f.name)
    
    # Track which new files we create
    new_test_stems = set()
    
    for sol_file in solution_files:
        classes = find_solution_classes(sol_file)
        if not classes:
            continue
        
        # Test file name: 00001_TwoSum.hpp -> 00001_TwoSumTests.cpp
        test_stem = sol_file.stem + "Tests"
        test_filename = test_stem + ".cpp"
        test_path = TEST_DIR / test_filename
        
        # Skip if already exists
        if test_stem in existing_tests or test_path.exists():
            if test_filename not in all_test_files:
                all_test_files.append(test_filename)
            continue
        
        # Generate stub
        content = generate_test_content(sol_file.name, classes)
        test_path.write_text(content, encoding="utf-8")
        all_test_files.append(test_filename)
        new_test_stems.add(test_stem)
        created += 1
        print(f"  Created: {test_filename}")
    
    print(f"\n  Created {created} new test files.\n")
    
    # Deduplicate and sort
    all_test_files = sorted(set(all_test_files))
    
    # Regenerate project files
    print("Regenerating project files:")
    generate_vcxproj(all_test_files)
    generate_filters(all_test_files)
    
    print(f"\n=== Done! {len(all_test_files)} total test files in project. ===")


if __name__ == "__main__":
    main()
