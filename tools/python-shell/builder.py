import os
import subprocess
import shutil
import platform


class builder_c:
    def __init__(self, state: None):
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
        if "nt" == os.name():
            print("gcc is unsupported on windows!")
            return

        self.set_build_system()
        self.set_compilers("gcc", "gcc", "g++")

    def icx(self):
        self.set_build_system()
        self.set_compilers("icx", "icx")

    def msvc(self):
        if "nt" != os.name():
            print("Sorry MSVC is windows only...")
            return

        self.set_build_system()
        self.set_compilers("msvc", "cl", "cl")

    def tcc(self):
        if "nt" == os.name():
            print("TinyCC is unsupported on windows!")
            return

        self.set_build_system()
        self.set_compilers("tcc", "tcc")

    def zig(self):
        self.set_build_system()
        self.set_compilers("zig", "zig cc", "zig c++")

    def set_build_system(self):
        self.build_system = "Ninja"

    def set_compilers(self, name: str, cc: str, cxx: str = None):
        if shutil.which(cc) is None:
            print(f"Compiler [ {name} ] not installed")
            return

        self.compiler = name
        self.cxx = None

        # Zig is special for C
        if "zig" == name:
            self.cc = cc
            self.cxx = cxx
        else:
            self.cc = shutil.which(cc)

            if cxx is not None:
                self.cxx = shutil.which(cxx)

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
        ).lower()

        path = f"build/{target}"

        print("Setting up temporary enviroment...")
        os.makedirs(path, exist_ok=True)
        env = os.environ.copy()
        env["CC"] = self.cc

        if self.cxx is not None:
            env["CXX"] = self.cxx
        else:
            env.pop("CXX", None)

        print("Configuring cmake...")
        subprocess.run([
                "cmake",
                "-S", ".",
                "-B", path,
                "-G", self.build_system,
            ],
            env=env,
            check=True
        )

        print("CMake building...")
        subprocess.run([
                "cmake",
                "--build", f"{path}"
            ],
            env=env,
            check=True
        )
