import os
import re


class style_c:
    def __init__(self):
        self.name = None

    def extract_include(self, js, file, text):
        # C/C++ files
        for s in [ "c", "cpp", "h", "hpp" ]:
            if file.endswith(f".{s}"):
                results = re.findall(r'#include\<.*>', text)

                for res in results:
                    link = res.replace("#include<", "")[:-1]
                    _, _, filename = link.rpartition('/')
                    js["links"].append(f"[{filename}]({link})\n")
                return

    def parse(self, js, file, text):
        out = None

        if self.name is None:
            return out

        tp = re.compile(rf"/\*\s*\[{self.name}\](.*?)\*/", re.DOTALL)
        blocks = tp.findall(text)

        if 0 != len(blocks):
            out = blocks

            if file not in js:
                js[file] = {}
                
            if "text" not in js:
                js[file]["text"] = []

            if "links" not in js:
                js[file]["links"] = []

            self.extract_include(js[file], file, text)

        return out


class doc_kernel_c(style_c):
    pass


class doc_md_c(style_c):
    def __init__(self):
        super().__init__()
        self.name = "MD_DOC"


class puppy_c:
    def __init__(self):
        self.styles = {}
        self.js = {}
        self.skip = [
                "./docs",
                "./vendor",
                "./.venv",
                "./build",
                "./.git",
                "./.cache",
                "./.wolfhound",
            ]

    def add_style(self, key : str, style : style_c, file_types):
        self.styles[key] = {
                "file_types": file_types,
                "style": style,
        }


    def is_supported(self, filename, style):
        for s in style["file_types"]:
            if filename.endswith(f".{s}"):
                return True

        return False

    def parse(self, directory, file):
        with open(os.path.join(directory, file), "r") as fd:
            try:
                text = fd.read()
            except UnicodeDecodeError:
                return

            for st in self.styles:
                if not self.is_supported(file, self.styles[st]):
                    continue

                t = self.styles[st]["style"].parse(self.js, file, text)

                if t is not None:
                    self.js[file]["text"].append(t)

    def scan(self):
        for i in os.walk('.', followlinks=False, topdown=True):
            directory = i[0]
            files = i[2]
            skip = False

            for s in self.skip:
                if (directory.startswith(s)):
                    skip = True
                    break

            if skip:
                continue

            for f in files:
                self.parse(directory, f)

        print(self.js)


def main():
    puppy = puppy_c()

    kernel = doc_kernel_c();
    md = doc_md_c()

    c_family_files = [ "c", "cpp", "h", "hpp" ]

    puppy.add_style("kernel_doc", kernel, c_family_files)
    puppy.add_style("puppy", md, c_family_files)

    # Legacy support for the old style
    puppy.add_style("md_doc", md, c_family_files)

    puppy.scan();


if "__main__" == __name__:
    main()
