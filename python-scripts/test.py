import sys
import clang.cindex

target = "main.cpp"

index = clang.cindex.Index.create()
tree = index.parse(target)

for value in tree.get_includes():
    print value.source.name
