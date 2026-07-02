
from common.params import params_c


def execute(params: params_c):
    params.sh.builder.build(params.args)
