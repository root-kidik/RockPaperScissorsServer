from conan import ConanFile
from conan.tools.cmake import CMake, CMakeToolchain, CMakeDeps, cmake_layout

class RockPaperScissorsRecipe(ConanFile):
    settings = "os", "compiler", "build_type", "arch"

    def requirements(self):
        self.requires("qt/6.7.3")
        if self.settings.build_type == "Debug":
            self.requires("gtest/1.15.0")

    def layout(self):
        cmake_layout(self)  

    def generate(self):
        tc = CMakeToolchain(self)
        tc.generate()
        deps = CMakeDeps(self)
        deps.generate()
