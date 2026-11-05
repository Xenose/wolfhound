from fastapi import FastAPI

app = FastAPI()

@app.get("/")
def get_root():
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
    return "build system is ...")
