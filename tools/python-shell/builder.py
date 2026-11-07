import os
import subprocess
import shutil
import platform
import argparse

from common.utils import find_executable

from enum import Enum
from dataclasses import dataclass, field

class arch_e(Enum):
    NONE    = 0
    X64     = 1
    ARM64   = 2
    RISCV   = 3

class build_system_e(Enum):
    NONE        = 0
    NMAKE       = 1
    UNIX_MAKE   = 2
    NINJA       = 3

class compiler_e(Enum):
    NONE    = 0
    GCC     = 1
    CLANG   = 2
    TCC     = 3 # TinyCC
    KEFIR   = 4
    IFX     = 5 # Intel's compiler LLVM based
    ZIG     = 6
    MSVC    = 7

class platform_e(Enum):
    NONE    = 0
    LINUX   = 1
    BSD     = 2
    SOLARIS = 3
    BEOS    = 4
    WINDOWS = 5
    MACOS   = 6
    AROS    = 7

@dataclass
class arch_c:
    current : arch_e = arch_e.NONE
    target  : arch_e = arch_e.NONE

@dataclass
class platform_c:
    current     : platform_e = platform_e.NONE
    target      : platform_e = platform_e.NONE

@dataclass
class build_flags_c:
    no_asm      : bool = False
    no_cpp      : bool = False
    no_glew     : bool = False
    no_glfw3    : bool = False
    no_opengl   : bool = False
    no_sdl2     : bool = False
    no_sdl3     : bool = False
    no_vulkan   : bool = False


@dataclass
class builder_settings_c:
    build_system :  build_system_e  = build_system_e.NONE
    compiler :      compiler_e      = compiler_e.NONE

    arch :          arch_c          = field(default_factory = arch_c)
    platform :      platform_c      = field(default_factory = platform_c)
    flags :         build_flags_c   = field(default_factory = build_flags_c)


class builder_c:
    '''
        This class handles the state of the build-shell's
        build system setting compilers, architecture and
        build system(make,ninja and etc...).

        The goal is to have a fast and easy way to have
        build being generated in independent folders and
        linked into a single bin directory inside build.
    '''

    def __init__(self, home):
        '''
            Keywords Arguments:
                home -- The home directory for the project.
        '''
        self.settings = builder_settings_c() # <-- new settings system

        self.home = home
        self.arch = platform.machine()
        self.build_system = None
        self.compiler = None
        self.platform = platform.system()

        self.arch_target = None
        self.platform_target = None

        if not os.path.exists("build"):
            os.mkdir("build")

        if not os.path.exists("build/bin"):
            os.mkdir("build/bin")

    def clang(self, args):
        '''
            Keywords Arguments:
                args -- A argument list.
        '''
        a = self.parse_args(args)

        self.set_build_system(a)
        self.set_compilers("clang", "clang", "clang++")

    def gcc(self, args):
        '''
            Keywords Arguments:
                args -- A argument list.
        '''
        if "nt" == os.name:
            print("gcc is unsupported on windows!")
            return

        a = self.parse_args(args)

        self.set_build_system(a, "make")
        self.set_compilers("gcc", "gcc", "g++")

    def icx(self, args):
        a = self.parse_args(args)

        self.set_build_system(a, "ninja")
        self.set_compilers("icx", "icx")

    def msvc(self, args):
        if "nt" != os.name:
            print("Sorry MSVC is windows only...")
            return

        a = self.parse_args(args)

        self.set_build_system(a, "visual")
        self.set_compilers("msvc", "cl", "cl")

    def tcc(self, args):
        if "nt" == os.name:
            print("TinyCC is unsupported on windows!")
            return

        a = self.parse_args(args)
        self.set_build_system(a, "make")
        self.set_compilers("tcc", "tcc")

    def kefir(self, args):
        a = self.parse_args(args)

        self.set_build_system(a, "make")
        self.set_compilers("kefir", "kefir")

    def zig(self, args):
        a = self.parse_args(args)
        self.set_build_system(a, "ninja")
        self.set_compilers("zig", "zig cc", "zig c++")

    def parse_args(self, args):
        parser = argparse.ArgumentParser(
            prog='clang selector',
            description='What the program does',
            epilog='Text at the bottom of help'
        )

        parser.add_argument(
            "--arch",
            help="Set the architecture"
        )

        parser.add_argument(
            "--build-system",
            default=None,
            help="Set the build system to use"
        )

        return parser.parse_args(args)

    def parse_args_build(self, args):
        parser = argparse.ArgumentParser(
            prog='build',
            description='What the program does',
            epilog='Text at the bottom of help'
        )

        parser.add_argument(
            "--no-sdl3",
            action="store_true",
            help="Set the architecture"
        )

        parser.add_argument(
            "--no-sdl2",
            action="store_true",
            help="Set the architecture"
        )

        parser.add_argument(
            "--no-glfw3",
            action="store_true",
            help="Set the architecture"
        )

        parser.add_argument(
            "--no-vulkan",
            action="store_true",
            help="Set the architecture"
        )

        parser.add_argument(
            "--no-glew",
            action="store_true",
            help="Set the architecture"
        )

        return parser.parse_args(args)

    def set_build_system(self, args=None, dbs="ninja"):
        bs = args.build_system

        if bs is None:
            bs = dbs

        match bs.lower():
            case "ninja":
                self.settings.build_system = build_system_e.NINJA
                self.build_system = "Ninja"
            case "make":
                if "nt" == os.name:
                    self.settings.build_system = build_system_e.NMAKE
                    self.build_system = "NMake Makefiles"
                else:
                    self.settings.build_system = build_system_e.UNIX_MAKE
                    self.build_system = "Unix Makefiles"
            case "visual":
                if "nt" != os.name:
                    print("Visual is for windows ONLY!")
                    return
                self.build_system = "Visual Studio 17 2022"
            case _:
                self.settings.build_system = build_system_e.NINJA
                self.build_system = "Ninja"

    def set_compilers(self, name: str, cc: str, cxx: str = None):
        if shutil.which(cc) is None:
            print(f"Compiler [ {name} ] not installed")
            return

        match name.lower():
            case "gcc":
                self.settings.compiler = compiler_e.GCC
            case "clang":
                self.settings.compiler = compiler_e.CLANG
            case "tcc":
                self.settings.compiler = compiler_e.TCC
            case "kefir":
                self.settings.compiler = compiler_e.KEFIR
            case "zig":
                self.settings.compiler = compiler_e.ZIG
            case "ifx":
                self.settings.compiler = compiler_e.IFX
            case "msvc":
                self.settings.compiler = compiler_e.MSVC
            case _ :
                self.settings.compiler = compiler_e.NONE

        self.compiler = name
        self.cxx = None
        self.cc = shutil.which(cc)

        if cxx is not None:
            self.cxx = shutil.which(cxx)

        print("compiler set to [ {} ] build system [ {} ]".format(
            self.cc, self.build_system))

    def compilers(self):
        out = []

        out.extend([f"-DCMAKE_C_COMPILER={self.cc}"])

        if "kefir" in self.compiler:
            out.extend(["-DCOMPILER_KEFIR=true"])

        if self.cxx is not None:
            out.extend([f"-DCMAKE_CXX_COMPILER={self.cxx}"])
        else:
            print("No C++ compiler found skipping...")

        return out

    def display_string(self):
        p = self.platform
        a = self.arch

        if self.arch_target is not None:
            if self.arch_target != self.arch:
                a = self.arch_target
                # config_opt.extend(["-A", self.arch_target])

        if self.platform_target is not None:
            if self.platform_target != self.platform:
                # Todo add cross compiling
                pass

        target = "{}-{}-{}-{}".format(
            self.compiler, self.build_system, p, a
        ).lower().replace(" ", "-")

        return target

    def get_settings(self):
        return self.settings

    def is_ready(self):
        return None not in [
            self.arch,
            self.build_system,
            self.cc,
            self.compiler,
            self.platform
        ]

    def configure(self, path, args, config_opt):
        config = [
            "cmake",
            "-S", f"{self.home}",
            "-B", path,
            "-G", self.build_system,
            "-DGENERATE_REPORT=ON",
            f"-DNO_SDL3={args.no_sdl3}",
            f"-DNO_SDL2={args.no_sdl2}",
        ]

        config.extend(self.compilers())
        config.extend(config_opt)

        subprocess.run(config, check=True)

    def build(self, args):
        config_opt = []
        pa = self.parse_args_build(args)

        if not self.is_ready():
            print("builder_c is not in a ready state!{}".format(
                f"\nName:         {self.compiler}"
                f"\nCC:           {self.cc}"
                f"\nCXX:          {self.cxx}"
                f"\nArch:         {self.arch}"
                f"\nBuild system: {self.build_system}"
                f"\nPlatform:     {self.platform}"
            ))
            return

        p = self.platform
        a = self.arch

        if self.arch_target is not None:
            if self.arch_target != self.arch:
                a = self.arch_target
                config_opt.extend(["-A", self.arch_target])

        if self.platform_target is not None:
            if self.platform_target != self.platform:
                # Todo add cross compiling
                pass

        target = "{}-{}-{}-{}".format(
            self.compiler, self.build_system, p, a
        ).lower().replace(" ", "-")

        path = f"{self.home}/build/{target}"

        print("Setting up temporary enviroment...")
        os.makedirs(path, exist_ok=True)

        print("Configuring cmake...")
        self.configure(path, pa, config_opt)

        print("CMake building...")
        subprocess.run([
                "cmake",
                "--build", f"{path}"
            ],
            check=True
        )

        for e in find_executable(f"{self.home}/build/{target}", ["CMakeFiles"]):
            full_path = e
            link_name = os.path.basename(e)
            link_name = link_name.replace(".EXE", "")
            link_name = f"build/bin/{link_name}-{p}-{self.compiler}-{a}-{self.build_system}"
            link_name = link_name.lower().replace(" ", "_")

            if "nt" != os.name:
                try:
                    os.symlink(full_path, link_name)
                    print(f"Link created: {full_path} --> {link_name}")
                except FileExistsError:
                    print(f"Link exists : {full_path} --> {link_name}")

                try:
                    os.remove(f"{self.home}/compile_commands.json")
                except OSError:
                    pass

                os.symlink(f"{self.home}/build/{target}/compile_commands.json", f"{self.home}/compile_commands.json")
