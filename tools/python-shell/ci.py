import os
from fastapi import FastAPI
from builder2 import builder_c


app = FastAPI()


@app.get("/build")
def get_root(payload: dict):
    # Session Builder
    sb = builder_c(os.getcwd())

    sb.build_remote_recive(payload)
    return "Hello, world!"

@app.put("/sync")
def put_sync():
    return "Syncing!"

@app.put("/compiler")
def put_compiler():
    return "compiler is ..."

@app.put("/build/system")
def put_build_system():
    return "build system is ..."
