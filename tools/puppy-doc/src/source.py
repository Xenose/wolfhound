import os
import re

# from includes
from pathlib import Path


class style_c:
    def __init__(self):
        self.name = None

    def extract_include(self, js, file, text):
        # C/C++ files
        for s in [ "c", "cpp", "h", "hpp" ]:
            if file.endswith(f".{s}"):
                results = re.findall(r'#include.*?\<.*>', text)

                for res in results:
                    link = re.sub(r"#include.*?<", "", res)[:-1]
                    _, _, filename = link.rpartition('/')
                    js["links"].append(f"[{filename}]({link}) ")
                return

    def extract_keywords(self, js, file, text):
        # kp : keyword pattern
        kp = re.search(rf"\[.*?{self.name}.*?:.*?\]", text)

        if kp is not None:
            # ckp : clean keyword pattern
            ckp = re.sub(r"\[.*?:", "", kp.group())
            ckp = re.sub(r"\]$", "", ckp)
            js[file]["keywords"] = ckp.split(",")

    # Clean up the markers for C comments,
    # TODO other languages needs a switch.
    def clean_markers(self, blocks):
        out = []

        for b in blocks:
            lines = b.splitlines()

            for l in lines:
                cl = re.sub(r'^\s*\* ?', '', l)
                out.append(''.join(cl).strip())

        return out

    def parse(self, js, filepath, file, text):
        out = None

        if self.name is None:
            return out

        # tp : text pattern
        tp = re.compile(rf"/\*\s*\[{self.name}.*?\](.*?)\*/", re.DOTALL)
        blocks = self.clean_markers(tp.findall(text))

        if 0 != len(blocks):
            out = blocks

            if filepath not in js:
                js[filepath] = {}
                
            if "text" not in js:
                js[filepath]["text"] = []

            if "links" not in js:
                js[filepath]["links"] = []

            self.extract_include(js[filepath], file, text)

            # TODO prevent self including
            self.extract_keywords(js, filepath, text)

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
        self.output_folder = "./docs"
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

            filepath = Path(directory, file)

            for st in self.styles:
                if not self.is_supported(file, self.styles[st]):
                    continue

                t = self.styles[st]["style"].parse(self.js, filepath, file, text)

                if t is not None:
                    self.js[filepath]["text"].append(t)

    def link(self):
        pass

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
            
            for f in files:
                self.link();

    def insert_keywords(self, text):
        for file in self.js:
            for keyword in self.js[file]["keywords"]:
                text = text.replace(f" {keyword}(", f" [{keyword}]({file}) ")
                text = text.replace(f" {keyword} ", f" [{keyword}]({file}) ")
        
        return text

    def output(self):
        for file in self.js:
            out = ""
            f = Path(self.output_folder, f"{file}.md")
            f.parent.mkdir(parents=True, exist_ok=True)

            with open(f, "w") as fd:
                out = str(file)

                for text_array in self.js[file]["text"]:
                    for text in text_array:
                        out += f"{self.insert_keywords(text)}\n"
                    
                    out += "SEE ALSO\n"

                    for link in self.js[file]["links"]:
                        out += link

                # Dumping time...
                print(out)
                fd.write(out)




def main():
    puppy = puppy_c()

    kernel = doc_kernel_c();
    md = doc_md_c()

    c_family_files = [ "c", "cpp", "h", "hpp" ]

    puppy.add_style("kernel_doc", kernel, c_family_files)
    puppy.add_style("puppy", md, c_family_files)

    # Legacy support for the old style
    puppy.add_style("md_doc", md, c_family_files)

    puppy.scan()
    puppy.output()


if "__main__" == __name__:
    main()
