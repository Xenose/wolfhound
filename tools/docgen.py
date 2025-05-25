import os
import re

DOCDIR = "docs"
TODO = []

COPY_FILES = [".md"]
C_FILES = [".c", ".h", ".cpp", ".hpp"]
SKIP_DIRS = ["docs", "build"]

FILSUP = C_FILES + COPY_FILES


def create_table(text):
    tp = re.findall(r'@d_param[^\n]*', text)
    to = re.findall(r'@d_opt[^\n]*', text)

    if not tp and not to:
        return text, None
    # end if

    table = []
    table.append("| Parameter | Type | Designation | Optional | Description |")
    table.append("| --------- | ---- | ----------- | -------- | ----------- |")

    for t in tp:
        t = t.replace('\t', ' ')
        m = t[t.find(':') + 1:].strip()
        v = t[:t.find(':')][t.find('(') + 1:t.find(')')].strip()
        n = t[t.find(')') + 1: t.find(':') - 1].strip().replace(' ', '')
        table.append(f"| {n} | {v} | .{n} | NO | {m} |")
    # end for

    for t in to:
        t = t.replace('\t', ' ')
        m = t[t.find(':') + 1:].strip()
        v = t[:t.find(':')][t.find('(') + 1:t.find(')')].strip()
        n = t[t.find(')') + 1: t.find(':') - 1].strip().replace(' ', '')
        table.append(f"| {n} | {v} | .{n} | YES | {m} |")
    # end for

    # Remove all lines with @d_param and @d_opt
    cleaned_text = re.sub(
        r'^.*@d_(param|opt)[^\n]*\n?', '', text, flags=re.MULTILINE)
    # Insert table at first matching position or end
    insertion_point = re.search(r'@d_(param|opt)', text)

    if insertion_point:
        idx = insertion_point.start()
        cleaned_text = text[:idx] + '\n'.join(table) + '\n' + cleaned_text[idx:]
    else:
        cleaned_text = '\n'.join(table) + '\n' + cleaned_text
    # end if

    return cleaned_text, table
# end def


def extract_md_doc(text):
    pattern = re.compile(r"/\*\s*\[MD_DOC\](.*?)\*/", re.DOTALL)
    raw_blocks = pattern.findall(text)
    cleaned_blocks = []

    for block in raw_blocks:
        block, _ = create_table(block)
        lines = block.splitlines()
        cleaned_lines = [re.sub(r'^\s*\* ?', '', line) for line in lines]
        cleaned_blocks.append('\n'.join(cleaned_lines).strip())
    # end for

    return cleaned_blocks
# end def


def copy(text, path):
    with open(path, "w") as out:
        out.write(text)
    # end with
# end copy


def c_file(file, source):
    p = os.path.join(DOCDIR, f"{file}.md")

    with open(os.path.normpath(p), "w") as out:
        results = re.findall(r'#include\<.*>', source)

        for res in results:
            link = res.replace("#include<", "")[:-1]
            _, _, filename = link.rpartition('/')
            out.write(f"[{filename}]({link})\n")
        # end for

        for doc in extract_md_doc(source):
            out.write(f"\n{doc}\n")
        # end for
    # end open
# end def


def main():
    global TODO

    for i in os.walk('.', followlinks=False, topdown=True):
        if any(sd in i[0] for sd in SKIP_DIRS):
            continue
        # end if

        p = os.path.join(i[0])
        d = os.path.normpath(os.path.join(DOCDIR, p))
        os.makedirs(d, exist_ok=True)

        for f in i[2]:
            if not any(f.endswith(ext) for ext in FILSUP):
                continue
            # end if for

            f = os.path.join(p, f)

            with open(f) as fd:
                text = fd.read()

                if any(f.endswith(cf) for cf in COPY_FILES):
                    copy(text, os.path.normpath(os.path.join(DOCDIR, f)))
                    continue
                # end if

                # if "[MD_DOC]" not in text:
                #    continue
                # end if

                if any(f.endswith(cf) for cf in C_FILES):
                    c_file(f, text)
                    todo = re.findall(r"//.*TODO.*", text)

                    if todo:
                        for t in todo:
                            TODO.append(f"{f.replace("./", "")} -> {t.replace("//", "")}")
                        # end for
                    continue
                # end if
            # end open
        # end for
    # end for

    with open(os.path.join(DOCDIR, "todo.md"), "w") as fd:
        fd.write("# TODO LIST")

        for t in TODO:
            fd.write(f"{t}\n")
        # end for
    # end with
# end def


if __name__ == "__main__":
    main()
# end if
