
from common.params import params_c


def complete(text=None):
    return [
        '--arch',
        '--build-system'
    ]


def execute(params: params_c):
    params.sh.builder.kefir(params.args)
