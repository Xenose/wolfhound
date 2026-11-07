from builder2 import builder_c
from fastapi import FastAPI


app = FastAPI()


@app.get("/test")
def get_root(payload: dict):
    # Session Builder
    sb = builder_c(".")
    sb.build_remote_recive(payload)
    return "Hello, world!"


@app.put("/build")
def put_build():
    return "Building!"

@app.put("/sync")
def put_sync():
    return "Syncing!"

@app.put("/compiler")
def put_compiler():
    return "compiler is ..."

@app.put("/build/system")
def put_build_system():
    return "build system is ..."
