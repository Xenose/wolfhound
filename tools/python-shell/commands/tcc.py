

def complete(text=None):
    return [
        '--arch',
        '--build-system'
    ]


def execute(sh, cmd, args):
    sh.builder.tcc(args)
