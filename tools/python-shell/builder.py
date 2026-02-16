import os
import subprocess
import shutil
import platform
import argparse


class builder_c:
    def __init__(self, state=None):
        self.arch = platform.machine()
        self.build_system = None
        self.compiler = None
        self.platform = platform.system()

        self.arch_target = None
        self.platform_target = None

        if not os.path.exists("build"):
            os.mkdir("build")
        pass

    def clang(self):
        self.set_build_system()
        self.set_compilers("clang", "clang", "clang++")

    def gcc(self):
        if "nt" == os.name:
            print("gcc is unsupported on windows!")
            return

        self.set_build_system()
        self.set_compilers("gcc", "gcc", "g++")

    def icx(self):
        self.set_build_system()
        self.set_compilers("icx", "icx")

    def msvc(self, args):
        if "nt" != os.name:
            print("Sorry MSVC is windows only...")
            return

        a = self.parse_args(args)

        self.set_build_system(a)
        self.set_compilers("msvc", "cl", "cl")

    def tcc(self):
        if "nt" == os.name:
            print("TinyCC is unsupported on windows!")
            return

        self.set_build_system()
        self.set_compilers("tcc", "tcc")

    def zig(self):
        self.set_build_system()
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
            default="ninja",
            help="Set the build system to use"
        )

        return parser.parse_args(args)

    def set_build_system(self, args=None):
        print(args)

        if args is None:
            self.build_system = "Ninja"
        else:
            match args.build_system.lower():
                case "ninja":
                    self.build_system = "Ninja"
                case "make":
                    if "nt" == os.name:
                        self.build_system = "NMake Makefiles"
                    else:
                        self.build_system = "Unix Makefiles"
                case "visual":
                    if "nt" != os.name:
                        print("Visual is for windows ONLY!")
                        return
                    self.build_system = "Visual Studio 17 2022"
                case _:
                    self.build_system = "Ninja"

    def set_compilers(self, name: str, cc: str, cxx: str = None):
        if shutil.which(cc) is None:
            print(f"Compiler [ {name} ] not installed")
            return

        self.compiler = name
        self.cxx = None
        self.cc = shutil.which(cc)

        if self.cxx is not None:
            self.cxx = shutil.which(cxx)

        print(f"compiler set to [ {self.cc} ] build system [ {self.build_system} ]")

    def compilers(self):
        out = []

        out.extend([f"-DCMAKE_C_COMPILER={self.cc}"])

        if self.cxx is not None:
            print("No C++ compiler found skipping...")
            out.extend([f"-DCMAKE_CXX_COMPILER={self.cxx}"])

        return out

    def is_ready(self):
        return None not in [
            self.arch,
            self.build_system,
            self.cc,
            self.compiler,
            self.platform
        ]

    def build(self):
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
                # Todo add cross compiling
                pass

        if self.platform_target is not None:
            if self.platform_target != self.platform:
                # Todo add cross compiling
                pass

        target = "{}-{}-{}-{}".format(
            self.compiler, self.build_system, p, a
        ).lower().replace(" ", "-")

        path = f"build/{target}"

        print("Setting up temporary enviroment...")
        os.makedirs(path, exist_ok=True)

        print("Configuring cmake...")
        config = [
            "cmake",
            "-S", ".",
            "-B", path,
            "-G", self.build_system,
        ]

        config.extend(self.compilers())
        subprocess.run(config, check=True)

        print("CMake building...")
        subprocess.run([
                "cmake",
                "--build", f"{path}"
            ],
            check=True
        )
