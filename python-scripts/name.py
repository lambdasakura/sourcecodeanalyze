import sys
import clang.cindex

def find_typerefs(node, typename):
    """ Find all references to the type named 'typename'
    """
    if node.kind.is_declaration():
       ref_node = clang.cindex.Cursor_ref(node)
       print ref_node.displayname
       print ref_node.type.get_declaration()
       return

    if node.kind.is_reference():
        ref_node = clang.cindex.Cursor_ref(node)
        if ref_node.spelling == typename:
            print "EntityID:%s" % (node.get_definition().get_usr())
            print 'using %s @ [file=%s, line=%s, col=%s,def=%s]' % (
                typename, node.location.file,node.location.line, node.location.column,node.get_definition().location.file)
    # Recurse for children of this node
    for c in node.get_children():
        find_typerefs(c, typename)

def callexpr_visitor(node, parent, userdata):
    if node.kind == clang.cindex.CursorKind.CALL_EXPR:
        # ref_node = clang.cindex.Cursor_ref(node)
        print 'Found %s [line=%s, col=%s]' % (
                node.displayname, node.location.line, node.location.column)
    return 2 # means continue visiting recursively

index = clang.cindex.Index.create()

index.parse("test.h")
index.parse("test.c")
tu = index.parse("main.cpp")

print 'Translation unit:', tu.spelling
find_typerefs(tu.cursor, "hoge")
clang.cindex.Cursor_visit(
        tu.cursor,
        clang.cindex.Cursor_visit_callback(callexpr_visitor),
        None)
