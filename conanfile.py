from conan import ConanFile
from conan.tools.files import copy
import os


class CryptoNativeRecipe(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeToolchain", "CMakeDeps"

    def requirements(self):
        self.requires("ms-gsl/4.0.0")
        self.requires("fmt/10.2.1", options = {"shared": True})
        self.requires("spdlog/1.13.0", options = {"shared": True})
        self.requires("argparse/3.0") # header-only
        self.requires("botan/3.3.0", options = {"shared": True})
        self.requires("c4core/0.1.11", options = {"shared": True})
        self.requires("rapidyaml/0.5.0", options = {"shared": True})

    # def build_requirements(self):
    #     self.tool_requires("cmake/3.22.6")

    def layout(self):
        # We make the assumption that if the compiler is msvc the
        # CMake generator is multi-config
        builddir = os.environ.get('BUILDDIR', 'build')
        multi = True if self.settings.get_safe("compiler") == "msvc" else False
        if multi:
            self.folders.generators = os.path.join(builddir, "generators")
            self.folders.build = builddir
        else:
            self.folders.generators = os.path.join(
                builddir, str(self.settings.build_type), "generators"
            )
            self.folders.build = os.path.join(builddir, str(self.settings.build_type))
