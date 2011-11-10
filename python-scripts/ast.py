# -*- coding: utf-8 -*-
# python dump_tree.py test.m

import sys
import clang.cindex

def visit_node(node, indent=0):
  print '%s%s : %s %s %s' % ('  ' * indent, node.type.get_declaration().data , node.type.kind, node.kind.name, node.spelling)
  for c in node.get_children():
    visit_node(c, indent=indent+1)

index = clang.cindex.Index.create()
tree = index.parse(sys.argv[1])
visit_node(tree.cursor)
