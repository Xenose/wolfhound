
from common.params import params_c


def complete(text=None):
    return [
        "--no-sdl3",
        "--no-sdl2",
        "--no-glfw3",
        "--no-vulkan",
        "--no-opengl",
    ]

def execute(params: params_c):
    params.sh.builder.build(params.args)
