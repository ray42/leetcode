"""
For every solution .hpp file that does NOT have a class definition:
1. Add an empty Solution class stub
2. Create a corresponding gtest file

Then regenerate the LeetCodeTests .vcxproj and .filters.

Run from repo root:
    python add_missing_classes_and_tests.py
"""

import re
from pathlib import Path

SOLUTION_DIR = Path("src/LeetCode")
TEST_DIR = Path("src/LeetCodeTests")


def has_class(filepath: Path) -> bool:
    """Check if a file has any class definition (excluding TreeNode/ListNode)."""
    content = filepath.read_text(encoding="utf-8", errors="replace")
    # Match class definitions, excluding common types
    matches = re.findall(r'class\s+(\w+)', content)
    filtered = [m for m in matches if m not in ('TreeNode', 'ListNode', 'Node')]
    return len(filtered) > 0


def extract_problem_number(filename: str) -> str:
    """Extract the problem number from filename like '01249_Foo.hpp' -> '1249'."""
    num_str = filename.split('_')[0]
    return str(int(num_str))  # Remove leading zeros


def add_class_stub(filepath: Path, problem_num: str):
    """Add an empty Solution class to the end of the file."""
    content = filepath.read_text(encoding="utf-8", errors="replace")
    
    # Add the class stub at the end
    stub = f"\nclass Solution{problem_num} {{\npublic:\n}};\n"
    
    filepath.write_text(content + stub, encoding="utf-8")


def generate_test_content(header_name: str, problem_num: str, suite_name: str) -> str:
    """Generate a test file stub."""
    return (
        f'#include <gtest/gtest.h>\n'
        f'#include "{header_name}"\n'
        f'\n'
        f'TEST({suite_name}, Placeholder) {{\n'
        f'    // TODO: Add test cases for Solution{problem_num}\n'
        f'    EXPECT_TRUE(true);\n'
        f'}}\n'
    )


def generate_vcxproj(test_files: list[str]):
    """Regenerate LeetCodeTests.vcxproj."""
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
      <AdditionalOptions>/FS %(AdditionalOptions)</AdditionalOptions>
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
      <AdditionalOptions>/FS %(AdditionalOptions)</AdditionalOptions>
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
    print("=== Adding missing Solution classes and test files ===\n")

    solution_files = sorted(SOLUTION_DIR.glob("0*.hpp"))
    
    added_classes = 0
    created_tests = 0

    for sol_file in solution_files:
        problem_num = extract_problem_number(sol_file.stem)
        
        # Step 1: Add class stub if missing
        if not has_class(sol_file):
            add_class_stub(sol_file, problem_num)
            added_classes += 1
            print(f"  Added Solution{problem_num} to {sol_file.name}")
        
        # Step 2: Create test file if missing
        test_filename = sol_file.stem + "Tests.cpp"
        test_path = TEST_DIR / test_filename
        
        if not test_path.exists():
            # Extract suite name from filename: "00049_GroupAnagrams" -> "GroupAnagrams"
            parts = sol_file.stem.split('_', 1)
            suite_name = parts[1] if len(parts) > 1 else sol_file.stem
            
            content = generate_test_content(sol_file.name, problem_num, suite_name)
            test_path.write_text(content, encoding="utf-8")
            created_tests += 1

    print(f"\n  Added {added_classes} class stubs.")
    print(f"  Created {created_tests} new test files.\n")

    # Step 3: Regenerate project files with ALL test files
    all_test_files = sorted([f.name for f in TEST_DIR.glob("*.cpp")])
    print(f"Regenerating project files ({len(all_test_files)} files):")
    generate_vcxproj(all_test_files)
    generate_filters(all_test_files)

    print("\n=== Done! ===")


if __name__ == "__main__":
    main()
