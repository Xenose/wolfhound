import argparse
import os
import platform
import requests
import shutil
import subprocess

from common.server import server_c

from enum import Enum
from dataclasses import dataclass, field
from pathlib import Path
from typing import Any


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

    # MS : build systems
    VS17_2022   = 1000

class compiler_e(Enum):
    NONE    = 0
    GCC     = 1
    CLANG   = 2
    TCC     = 3 # TinyCC
    KEFIR   = 4
    IFX     = 5 # Intel's compiler LLVM based
    ZIG     = 6
    MSVC    = 7
    MINGW   = 8

class platform_e(Enum):
    NONE    = 0
    LINUX   = 1
    BSD     = 2
    SOLARIS = 3
    BEOS    = 4
    WINDOWS = 5
    MACOS   = 6
    AROS    = 7

class mode_e(Enum):
    LOCAL   = 0
    REMOTE  = 1
    NODE    = 2

@dataclass
class arch_c:
    current : arch_e = arch_e.X64
    target  : arch_e = arch_e.X64

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
    mode :          mode_e          = mode_e.LOCAL

    arch :          arch_c          = field(default_factory = arch_c)
    platform :      platform_c      = field(default_factory = platform_c)
    flags :         build_flags_c   = field(default_factory = build_flags_c)


def parse_args_build(args):
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


def get_name_build_system(bs):
    match bs:
        case build_system_e.NINJA:
            return "Ninja"
        case build_system_e.NMAKE:
            return "NMake Makefiles"
        case build_system_e.UNIX_MAKE:
            return "Unix Makefiles"
        case build_system_e.VS17_2022:
            return "Visual Studio 17 2022"

# architecture
def get_name_arch(arch):
    match arch:
        case arch_e.X64:
            return "x64"

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

        self.servers = [
            server_c("127.0.0.1")
        ]

        self.home = home
        self.platform = platform.system()

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
        a = None

        if args is not None:
            a = self.parse_args_compiler(args)
        
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

        a = self.parse_args_compiler(args)

        self.set_build_system(a, "make")
        self.set_compilers("gcc", "gcc", "g++")

    def icx(self, args):
        a = self.parse_args_compiler(args)

        self.set_build_system(a, "ninja")
        self.set_compilers("icx", "icx")

    def msvc(self, args):
        if "nt" != os.name:
            print("Sorry MSVC is windows only...")
            return

        a = self.parse_args_compiler(args)

        self.set_build_system(a, "visual")
        self.set_compilers("msvc", "cl", "cl")

    def tcc(self, args):
        if "nt" == os.name:
            print("TinyCC is unsupported on windows!")
            return

        a = self.parse_args_compiler(args)
        self.set_build_system(a, "make")
        self.set_compilers("tcc", "tcc")

    def kefir(self, args):
        a = self.parse_args_compiler(args)

        self.set_build_system(a, "make")
        self.set_compilers("kefir", "kefir")

    def zig(self, args):
        a = self.parse_args_compiler(args)
        self.set_build_system(a, "ninja")
        self.set_compilers("zig", "zig cc", "zig c++")

    def parse_args_compiler(self, args):
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


    def set_build_system(self, args:Any=None, dbs="ninja"):
        if args is not None:
            bs = args.build_system

            if bs is None:
                bs = dbs
        else:
            bs = dbs

        match bs.lower():
            case "ninja":
                self.settings.build_system = build_system_e.NINJA
            case "make":
                if "nt" == os.name:
                    self.settings.build_system = build_system_e.NMAKE
                else:
                    self.settings.build_system = build_system_e.UNIX_MAKE
            case "visual":
                if "nt" != os.name:
                    print("Visual is for windows ONLY!")
                    return
                
                self.settings.build_system = build_system_e.VS17_2022
            case _:
                self.settings.build_system = build_system_e.NINJA

    def set_mode(self, mode: str, servers = None):
        match mode:
            case "local":
                self.settings.mode = mode_e.LOCAL
            case "remote":
                if servers is None:
                    self.servers = [ server_c() ]
                self.settings.mode = mode_e.REMOTE

    def set_compilers(self, name: str, cc: str, cxx: Any = None):
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

        self.cxx = None
        self.cc = shutil.which(cc)

        if cxx is not None:
            self.cxx = shutil.which(cxx)

        print(f"compiler set to [ {self.cc} ] build system [ {get_name_build_system(self.settings.build_system)} ]")

    def compilers(self):
        out = []

        out.extend([f"-DCMAKE_C_COMPILER={self.cc}"])

        if compiler_e.KEFIR == self.settings.compiler:
            out.extend(["-DCOMPILER_KEFIR=true"])

        if self.cxx is not None:
            out.extend([f"-DCMAKE_CXX_COMPILER={self.cxx}"])
        else:
            print("No C++ compiler found skipping...")

        return out

    def display_string(self):
        p = self.platform
        a = get_name_arch(self.settings.arch.target)

        if a != self.settings.arch.current:
            pass
            # a = self.settigns.arch_target.name
            # config_opt.extend(["-A", self.arch_target])

        if self.platform_target != self.platform:
            # Todo add cross compiling
            pass

        target = f"{self.settings.compiler}-{get_name_build_system(self.settings.build_system)}-{p}-{a}".lower().replace(" ", "-")

        return target

    def get_settings(self):
        return self.settings

    def is_ready(self):
        return None not in [
            self.settings.build_system,
            self.cc,
            self.platform
        ]

    def configure(self, path, args, config_opt):
        config = [
            "cmake",
            "-S", f"{self.home}",
            "-B", str(path),
            "-G", get_name_build_system(self.settings.build_system),
            "-DGENERATE_REPORT=ON",
        ]

        if args is not None:
            config.extend([
                f"-DNO_SDL3={args.no_sdl3}",
                f"-DNO_SDL2={args.no_sdl2}"
            ])

        config.extend(self.compilers())

        if config_opt is not None:
            config.extend(config_opt)

        print(f"\n\n---> {config}\n\n")
        subprocess.run(config, check=True)


    def build_local(self, args = None):
        config_opt = []
        pa = None

        if args is not None:
            pa = parse_args_build(args)

        if not self.is_ready():
            return

        print("\n\nbuilder_c is not in a ready state!{}\n\n".format(
            f"\n\tName:         {self.settings.compiler}"
            f"\n\tCC:           {self.cc}"
            f"\n\tCXX:          {self.cxx}"
            f"\n\tArch:         {self.settings.arch}"
            f"\n\tBuild system: {get_name_build_system(self.settings.build_system)}"
            f"\n\tPlatform:     {self.platform}"
        ))

        p = self.platform
        a = get_name_arch(self.settings.arch.target)

        if self.settings.arch.target != self.settings.arch.current:
            config_opt.extend(["-A", a])

        if self.platform_target != self.platform:
            # Todo add cross compiling
            pass

        target = f"{self.settings.compiler}-{get_name_build_system(self.settings.build_system)}-{p}-{a}".lower().replace(" ", "-")

        # p for Path
        p = Path(self.home, "build", target)

        print("Setting up temporary enviroment...")
        os.makedirs(p, exist_ok=True)

        print("Configuring cmake...")
        self.configure(p, pa, config_opt)

        print("CMake building...")
        subprocess.run([
                "cmake",
                "--build", f"{p}"
            ],
            check=True
        )

        # TODO fix linking code...
       #  for e in find_executable(Path(self.home, "build", target), ["CMakeFiles"]):
       #      full_path = str(e)

       #      link_name = os.path.basename(full_path)
       #      link_name = link_name.replace(".EXE", "")
       #      link_name = f"build/bin/{link_name}-{p}-{self.compiler}-{a}-{get_name_build_system(self.settings.build_system)}"
       #      link_name = link_name.lower().replace(" ", "_")

       #      if "nt" != os.name:
       #          try:
       #              os.symlink(full_path, link_name)
       #              print(f"Link created: {full_path} --> {link_name}")
       #          except FileExistsError:
       #              print(f"Link exists : {full_path} --> {link_name}")

       #          try:
       #              os.remove(f"{self.home}/compile_commands.json")
       #          except OSError:
       #              pass

    # TODO : Extend the parameters and test cross
    # machine execution.
    def build_remote_recive(self, data):
        print(data)

        match data["compiler"].lower():
            case "clang":
                self.clang(None)

        self.build_local()


    def build_remote_payload(self):
        out = {}

        out["build_system"] = str(self.settings.compiler.name)
        out["compiler"]     = str(self.settings.compiler.name)

        return out

    def build_remote(self, args):
        payload = self.build_remote_payload()


        for server in self.servers:
            print(f"Sending requests to [ {server} ]")

            r = requests.get(f'http://{server.ip}:{server.port}/test', json=payload)
            print(f"\n{server.name} --> {r.status_code}")

    def build(self, args):
        match self.settings.mode:
            case mode_e.LOCAL:
                self.build_local(args)
            case mode_e.REMOTE:
                self.build_remote(args)

 
