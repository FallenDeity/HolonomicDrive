import os
import pathlib

DIRS = ["src", "test", "include"]
CLANG_COMMAND = "clang-format -i {file}"
EXTENSIONS = (".cpp", ".cxx", ".c++", ".cc", ".cp", ".c", ".i", ".ii", ".h", ".h++", ".hpp", ".hxx", ".hh", ".inl", ".inc", ".ipp", ".ixx", ".txx", ".tpp", ".tcc", ".tpl")

for dir in DIRS:
    for file in pathlib.Path(dir).rglob("*"):
        if file.suffix in EXTENSIONS:
            command = CLANG_COMMAND.format(file=file)
            print(command)
            os.system(command)
