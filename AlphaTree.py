# scapegoat tree
# BuildTree, insert, search, delete, print operations

import math

check_invariants = True
use_flatten = True

# ******************************** DATA STRUCTURES ***********************************


class SgNode:
    def __init__(self, key):
        self.key = key
        self.left, self.right = None, None

    def __lt__(self, other):
        return self.key < other.key

    def __gt__(self, other):
        return self.key > other.key

    def __str__(self):
        return str(self.key)


class Sgt:
    def __init__(self, alpha):
        self.root = None
        self.alpha = alpha
        self.size = 0
        self.max_size = 0

    # wrapper for search(tree, key) in helpers
    # other fn need parent, but people querying the tree don't care
    def search(self, key):
        node, _ = tree_search(self, key)
        return node

    def insert(self, key):

        node = SgNode(key)

        self.size += 1
        self.max_size = max(self.max_size, self.size)

        if self.root is None:
            self.root = node
        else:
            depth = insert_node(self.root, node)
            if depth > alpha_height(self):
                sg, parent = find_scapegoat(self, node)
                sz = subtree_size(sg)
                if use_flatten:
                    subtree = rebuild_with_flatten(sz, sg)
                else:
                    subtree = rebuild(sg)

                if sg is parent.left:
                    parent.left = subtree
                else:
                    parent.right = subtree

                if check_invariants:
                    assert_scapegoat_invariants(self, subtree)

    def delete(self, key):
        if self.root is None:
            return
        else:
            node, parent = tree_search(self, key)
            delete_node(self, node, parent)

        self.size -= 1
        if self.size < self.alpha * self.max_size:

            if use_flatten:
                subtree = rebuild_with_flatten(self.size, self.root)
            else:
                subtree = rebuild(self.root)
            self.root = subtree
            self.max_size = self.size

            if check_invariants:
                assert_scapegoat_invariants(self, self.root)

    def print_tree(self):
        def in_order_traverse(node, level):
            if node is None: return
            in_order_traverse(node.right, level + 1)
            indent = ""
            for i in range(level): indent += "     "
            print()
            print(indent + str(node))
            in_order_traverse(node.left, level + 1)

        in_order_traverse(self.root, 0)


# ***************************** HELPERS ********************************************


def rebuild_with_flatten(sz, node):
    def flatten(scapegoat, y=None):
        if scapegoat is None:
            return y

        scapegoat.right = flatten(scapegoat.right, y)
        return flatten(scapegoat.left, scapegoat)

    def build(n, scapegoat):
        if n == 0:
            scapegoat.left = None
            return scapegoat

        r = build(math.ceil((n-1)/2), scapegoat)
        scapegoat = r.right
        s = build(math.floor((n-1)/2), r.right)

        r.right = s.left
        s.left = r

        return s

    # flatten the subtree
    lst = flatten(node)

    z = build(sz - 1, lst)

    # move the return node to the rightmost position of subtree
    ret_node = z.left
    tmp = ret_node
    while tmp.right is not None:
        tmp = tmp.right
    tmp.right = z
    tmp.right.left = None

    return ret_node


def rebuild(node):
    def in_order_traverse(root, aux):
        if root is None: return
        in_order_traverse(root.left, aux)
        copy = root
        aux.append(copy)
        in_order_traverse(root.right, aux)

    def rebuild_tree(nodes, l, r):

        if l == r: return None
        if r - l == 1:
            nodes[l].left = None
            nodes[l].right = None
            return nodes[l]

        mid = int( (l + r) / 2)

        lnode = rebuild_tree(nodes, l, mid)
        rnode = rebuild_tree(nodes, mid + 1, r)

        nodes[mid].left = lnode
        nodes[mid].right = rnode

        return nodes[mid]

    nodes = []
    in_order_traverse(node, nodes)
    ret_node = rebuild_tree(nodes, 0, len(nodes))
    return ret_node


def alpha_height(tree):
        return math.floor(math.log(tree.size, 1.0 / tree.alpha))


def subtree_size(node):
    def in_order_traverse(root, countarr):
        if root is None: return
        in_order_traverse(root.left, countarr)
        countarr[0] += 1
        in_order_traverse(root.right, countarr)

    counter = [0]
    in_order_traverse(node, counter)
    return counter[0]


def is_weight_balanced_at(tree, node):
    sl = subtree_size(node.left)
    sr = subtree_size(node.right)
    sm = sl + sr + 1
    target = tree.alpha * sm
    return sl <= target and sr <= target


def find_scapegoat(tree, node):
    scapegoat = tree.root
    parent = None

    while scapegoat is not None:
        if not is_weight_balanced_at(tree, scapegoat) and scapegoat is not tree.root:
            return scapegoat, parent

        parent = scapegoat
        if node < scapegoat:
            scapegoat = scapegoat.left
        else:
            scapegoat = scapegoat.right

    assert(not is_weight_balanced_at(tree, tree.root))
    return tree.root, None


def tree_search(tree, key):
    node = tree.root
    parent = None

    while node is not None:
        if key == node.key: return node, parent
        parent = node
        if key < node.key:
            node = node.left
        else:
            node = node.right

    return None, None


def delete_node(tree, node, parent):

    if node.left is not None and node.right is not None:
        succ, par = find_min(node.right)

        # node.right is the successor
        if par is None: par = node

        replacement = succ
        delete_node(tree, succ, par)

        replacement.right = node.right
        replacement.left = node.left

    else:

        if node.left is None:
            replacement = node.right
        else:
            replacement = node.left

    if parent is None:
        tree.root = replacement
    elif node is parent.left:
        parent.left = replacement
    else:
        parent.right = replacement


def find_min(node):
    parent = None
    min = node
    while node.left is not None:
        parent = node
        node = node.left
        min = node
    return min, parent


def insert_node(root, node, depth=0):
    parent = None
    braflag = 0

    while root is not None:
        parent = root

        if node < root:
            root = root.left
            braflag = 0
        else:
            root = root.right
            braflag = 1

        depth += 1

    if braflag:
        parent.right = node
    else:
        parent.left = node

    return depth


def build_tree(alpha, key):
    tree = Sgt(alpha)
    tree.insert(key)
    return tree


# ********************************** SAMPLE USER PROGRAM ***********************************
# Could lift this out into another file, but... this is okay for now

def process_command(tree, command):
    cmd_toks = command.strip('\n').split()

    if cmd_toks == []:
        return

    instr = cmd_toks[0].lower()

    if instr == 'insert':
        tree.insert(int(cmd_toks[1]))
        return 0

    elif instr == 'search':
        node = tree.search(int(cmd_toks[1]))

        if node is None:
            print("Node %s not found" % (cmd_toks[1]))
        else:
            print("Node %d found" % node.key)

        return 0

    elif instr == 'delete':
        tree.delete(int(cmd_toks[1]))
        return 0

    elif instr == 'print':
        tree.print_tree()
        print()
        print("*************************")
        return 0

    elif instr == 'done':
        "Done... exiting"
        return 1

    else:
        print("Invalid instruction")
        print("Continuing...")
        return 0


def main():
    with open('tree.txt') as f:
        command_list = f.readlines()

    init_cmd = command_list[0].split()
    assert(init_cmd[0].lower() == 'buildtree')

    if not 0.5 <= float(init_cmd[1]) < 1:
        print("Expecting alpha value between 0.5 and 1")
        exit(1)

    tree = build_tree(float(init_cmd[1]), int(init_cmd[2]))

    for command in command_list[1:]:
        ret = process_command(tree, command)

        if ret is 1:
            print("Completing....")
            exit(0)

        elif ret is -1:
            print("Error!")
            exit(0)

    print()
    print("Out of commands")
    print("Completing...")

    exit(0)

# *********************************** TESTS *****************************************


# checks to see that the scapegoat invariants hold
# parent is larger than left child and greater than right child
# after rebalance of a subtree, every node is alpha-weight balanced
def assert_scapegoat_invariants(tree, node):
    def assert_node_invariants(node):
        assert(node.left is None or node.left < node)
        assert(node.right is None or node.right > node)

    def assert_subtree_invariants(node):
        assert(is_weight_balanced_at(tree, node))

    def pre_order_traverse(root):
        if root is None: return
        assert_node_invariants(root)
        assert_subtree_invariants(root)
        pre_order_traverse(root.left)
        pre_order_traverse(root.right)

    assert(tree.max_size / 2 <= tree.size <= tree.max_size)
    pre_order_traverse(node)


# using the example given in the slides
# expecting scapegoat to be 6.  Also another experiment.
# Still no balancing done here
def find_scapegoat_unit_tests():
    tree = build_tree(0.57, 2)
    tree.insert(1)
    tree.insert(6)
    tree.insert(5)
    tree.insert(4)
    tree.insert(3)
    tree.insert(15)
    tree.insert(12)
    tree.insert(9)
    tree.insert(7)
    tree.insert(16)
    tree.insert(13)
    tree.insert(11)
    tree.insert(17)
    tree.insert(14)
    tree.insert(10)
    tree.insert(18)
    tree.insert(8)

    node = tree.search(8)
    sg, _ = find_scapegoat(tree, node)
    assert(sg.key is 6)

    # tree2 with a modification on the first
    # add a 1 or 2 before some numbers to allow more nodes
    # now 6 (16) is balanced with 13 nodes on left, 13 on right
    tree2 = build_tree(0.57, 2)
    tree2.insert(1)
    tree2.insert(16)
    tree2.insert(15)
    tree2.insert(14)
    tree2.insert(13)
    tree2.insert(12)
    tree2.insert(11)
    tree2.insert(10)
    tree2.insert(9)
    tree2.insert(8)
    tree2.insert(7)
    tree2.insert(6)
    tree2.insert(5)
    tree2.insert(4)
    tree2.insert(3)

    # and 15 (215) is unbalanced with 10 nodes on left, 3 on right
    # this is after the insertion of 8 (18)
    tree2.insert(215)
    tree2.insert(112)
    tree2.insert(19)
    tree2.insert(17)
    tree2.insert(216)
    tree2.insert(113)
    tree2.insert(111)
    tree2.insert(217)
    tree2.insert(114)
    tree2.insert(110)
    tree2.insert(218)
    tree2.insert(115)
    tree2.insert(116)
    tree2.insert(18)

    node = tree2.search(18)
    sg2, _ = find_scapegoat(tree2, node)

    # expect 15 (215) to be scapegoat
    assert(sg2.key is 215)
    
    print("success")


# progress check
# the tree was still only a binary search tree when this was written
# that is, this assumes no balancing is done
# test cases verified with online BST visualisation:
# https://visualgo.net/bst
def bst_unit_tests():
    tree = build_tree(0.5, 33)
    tree.insert(35)
    tree.delete(35)

    node = tree.search(35)
    assert(node is None)

    tree.insert(35)
    tree.insert(25)

    assert(tree.root.key is 33)
    assert(tree.root.right.key is 35)
    assert(tree.root.left.key is 25)

    # delete root
    tree.delete(33)

    node = tree.search(33)
    assert(node is None)

    assert(tree.root.key is 35)
    assert(tree.root.left.key is 25)
    assert(tree.root.right is None)

    tree.insert(45)
    tree.insert(12)
    tree.insert(32)
    tree.insert(42)
    tree.insert(52)
    tree.insert(55)
    tree.insert(99)
    tree.insert(48)
    tree.insert(59)
    tree.insert(63)
    tree.insert(64)
    tree.insert(13)
    tree.insert(5)
    tree.insert(6)
    tree.insert(31)
    tree.insert(33)

    assert(tree.size is 18)

    # delete n where n has no children
    tree.delete(6)
    node = tree.search(6)
    assert(node is None)
    node = tree.search(5)
    assert(node is not None)
    assert(node.left is None)
    assert(node.right is None)

    # delete n where n has 1 child and n is left child of parent
    tree.delete(59)
    node = tree.search(59)
    assert(node is None)
    node = tree.search(99)
    assert(node is not None)
    assert(node.left.key is 63)
    assert(node.right is None)

    # delete n where n has 1 child and n is right child of parent
    tree.delete(55)
    node = tree.search(55)
    assert(node is None)
    node = tree.search(52)
    assert(node is not None)
    assert(node.left.key is 48)
    assert(node.right.key is 99)

    # delete n where n has 2 children and n is left child of parent
    tree.delete(25)
    node = tree.search(25)
    assert(node is None)
    node = tree.search(35)
    assert(node is not None)
    assert(node.left.key is 31)
    assert(node.right.key is 45)

    # delete n where n has 2 children and n is right child of parent
    tree.delete(45)
    node = tree.search(45)
    assert(node is None)
    node = tree.search(35)
    assert(node is not None)
    assert(node.left.key is 31)
    assert(node.right.key is 48)

    assert(tree.root.key is 35)

    assert(tree.size is 13)
    print("success")


# progress check ; no balancing
def subtree_size_unit_tests():
    tree = build_tree(0.5, 33)
    assert(subtree_size(tree.root) is 1)
    assert(is_weight_balanced_at(tree, tree.root))

    tree.insert(45)
    tree.insert(43)
    tree.insert(47)

    tree.insert(25)
    tree.insert(23)
    tree.insert(27)

    node = tree.search(33)
    assert(subtree_size(node) is 7)

    node = tree.search(45)
    assert(subtree_size(node) is 3)

    node = tree.search(25)
    assert(subtree_size(node) is 3)

    assert(is_weight_balanced_at(tree, tree.root))
    assert(is_weight_balanced_at(tree, tree.root.left))
    assert(is_weight_balanced_at(tree, tree.root.right))

    tree.insert(65)
    tree.insert(63)
    tree.insert(67)

    assert(not is_weight_balanced_at(tree, tree.root))
    print("success")


if __name__ == "__main__":
    main()