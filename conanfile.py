from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMakeDeps, CMake, cmake_layout
from conans import tools, RunEnvironment, CMake

class Fuse(ConanFile):
    name = "Fuse"
    version = "0.1.0"
    settings = "os", "compiler", "build_type", "arch"
    generators = "qt", "CMakeDeps", "CMakeToolchain", "cmake_paths", "cmake_find_package"
    default_options = { 
        "libcurl/*:shared": True,

        "qt/*:shared": True,
        "qt/*:with_vulkan": True,
        "qt/*:widgets": True
        }

    def requirements(self):
        self.requires("libcurl/8.0.1")
        self.requires("qt/6.5.0")
        self.requires("openssl/1.1.1t")

    def imports(self):
        self.copy("*.dll", dst="bin", src="bin")
        self.copy("*.dylib*", dst="bin", src="lib")

    def layout(self):
        cmake_layout(self)

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()
        #cmake.test()

    def package(self):
        cmake = CMake(self)
        cmake.install()
