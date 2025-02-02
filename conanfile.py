from conan import ConanFile
from conan.tools.cmake import cmake_layout

class Recipe(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeToolchain", "CMakeDeps"

    def requirements(self):
        self.requires("qt/6.7.3")
        self.requires("gtest/1.15.0")

    def layout(self):
        cmake_layout(self)
