from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMakeDeps, CMake, cmake_layout

class Fuse(ConanFile):
    name = "Fuse"
    version = "0.1.0"
    settings = "os", "compiler", "build_type", "arch"
    default_options = { "libcurl/*:shared": True }

    def requirements(self):
        self.requires("libcurl/8.0.1")

    def imports(self):
        self.copy("*.dll", dst="bin", src="bin")
        self.copy("*.dylib*", dst="bin", src="lib")

    def layout(self):
        cmake_layout(self)

    def generate(self):
        tc = CMakeToolchain(self)
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()
        #cmake.test()

    def package(self):
        cmake = CMake(self)
        cmake.install()
