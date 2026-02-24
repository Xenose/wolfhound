

def complete():
    return [
        '--arch',
        '--build-system'
    ]


def execute(sh, cmd, args):
    sh.builder.zig(args)
