# -*- coding: utf-8 -*-

import sys
import clang.cindex

def visit_node(node, indent=0):
  if node.kind.name == 'VAR_DECL':
    print '%s (line:%s column:%s)' % (node.spelling, node.location.line, node.location.column)
  for c in node.get_children():
    visit_node(c)
    
index = clang.cindex.Index.create()
tree = index.parse(sys.argv[1])
visit_node(tree.cursor)
