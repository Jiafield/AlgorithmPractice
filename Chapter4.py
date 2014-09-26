import sys
import random

class Node:
    def __init__(self, value):
        self.value = value
        self.edges = []
        self.prev = None

    def addEdge(self, node):
        if node not in self.edges:
            self.edges.append(node)

    def __repr__(self):
        s = "Node" + str(self.value) + ", edges:"
        for edge in self.edges:
            s = s + str(edge.value) + " "
        s = s + "\n"
        return s
        
class TreeNode:
    def __init__(self, v):
        self.value = v
        self.left = None
        self.right = None
        self.parent = None
        self.child = 0

    def __lt__(self, node):
        return self.value < node.value

    def __eq__(self, node):
        return self.value == node.value

    def __repr__(self):
        s = ""
        current = [self]
        nextlevel = []
        while current:
            for n in current:
                s = s + str(n.value) + " " 
                if n.left:
                    nextlevel.append(n.left)
                if n.right:
                    nextlevel.append(n.right)
            current = nextlevel
            nextlevel = []
            s = s + "\n"
        return s

    def addNode(self, node):
        if self < node:
            if self.right is None:
                self.right = node
                node.parent = self
                return
            self.right.addNode(node)
        else:
            if self.left is None:
                self.left = node
                node.parent = self
                return
            self.left.addNode(node)                

def buildTree(n, ran):
    root = TreeNode(random.randint(0, ran))
    for i in range(n - 1):
        node = TreeNode(random.randint(0, ran))
        root.addNode(node)
    return root

def buildDGraph(n):
    Dgraph = []
    for i in range(n):
        Dgraph.append(Node(i))
    for i in range(n):
        for j in range(random.randint(0, 6)):
            edgeEnd = random.randint(0, n - 1)
            if edgeEnd != Dgraph[i].value:
                Dgraph[i].addEdge(Dgraph[edgeEnd])
    return Dgraph

# Answer 4.1 Implement a function to check if a tree is balanced For the purposes of this question, a balanced tree is defined to be a tree such that no two leaf nodes differ in distance from the root by more than one 
def findMax(root):
    if root is None:
        return 0
    return 1 + max(findMax(root.left), findMax(root.right))

def findMin(root):
    if root is None:
        return 0
    return 1 + min(findMin(root.left), findMin(root.right))

def checkBalance(root):
    min = findMin(root);
    max = findMax(root);
    return max - min <= 1

# Answer 4.2 Given a directed graph, design an algorithm to find out whether there is a route between two node.
def findPath(start, end, graph):
    visited = set([start])
    buf = [start]
    while buf:
        nextNode = buf.pop()
        for edge in nextNode.edges:
            if edge not in visited:
                edge.prev = nextNode.value
                buf.append(edge)
                visited.add(edge)
            if edge == end:
                return True
    return False

def printPath(start, end, graph):
    if end.value == start.value:
        print end.value,
        return
    printPath(start, graph[end.prev], graph)
    print end.value,
    
# Answer 4.3 Given a sorted (increasing order) array, write an algorithm to create a binary tree with minimal height 
def minHeightTree(array, start, end):
    if start > end:
        return None
    mid = (start + end) / 2
    node = TreeNode(array[mid])
    node.left = minHeightTree(array, start, mid - 1)
    node.right = minHeightTree(array, mid + 1, end)
    return node

# Answer 4.4 Given a binary search tree, design an algorithm which creates a linked list of all the nodes at each depth.
def DepthLinkList(root):
    result = []
    currentLevel = [root]
    nextLevel = []
    while currentLevel:
        result.append(currentLevel)
        for node in currentLevel:
            if node.left:
                nextLevel.append(node.left)
            if node.right:
                nextLevel.append(node.right)
        currentLevel = nextLevel
        nextLevel = []
    return result
        
# Answer 4.5 Design an algorithm to find the 'next' node (in-order successor) of a given node in a binary search tree where each node also has a link to its parent.
def findSuccessor(node):
    if (node):
        if node.right:
            successor = node.right
            while successor.left:
                successor = successor.left
            return successor
        else:
            successor = node
            while (successor.parent):
                if successor.parent.left == successor:
                    return successor.parent
                successor = successor.parent
    return None
            
# Answer 4.6 Design an algorithm to find the first common ancestor of two nodes in a binary tree. Avoid storing additional nodes in a data structure. Note: This is not necessarily a binary search tree.
def findCommonAncestor(n1, n2, root):
    pass

# Answer 4.7 You have two very large binary trees: T1, with millions of nodes, and T2, with hundreds of nodes. Create an algorithm to decide if T2 is a subtree of T1.
def isSubtree(t1, t2):
    numNodes = countNodes(t2)
    print "T2 is", t2
    print "T2 has", numNodes, "nodes"
    candidates = []
    findCandidates(candidates, t1, numNodes)
    print "Candidates", candidates
    for c in candidates:
        if compareTree(c, t2):
            return True
    return False

def countNodes(t):
    if not t:
        return 0
    return 1 + countNodes(t.left) + countNodes(t.right)

def findCandidates(candidates, root, num):
    if not root:
        return 0
    left = findCandidates(candidates, root.left, num)
    right = findCandidates(candidates, root.right, num)    
    root.child = left + right
    if root.child + 1 == num:
        candidates.append(root)
    return root.child + 1
    
def compareTree(t1, t2):
    if not t1 and not t2:
        return True
    if not t1 or not t2:
        return False
    if t1 == t2:
        return compareTree(t1.left, t2.left) and compareTree(t1.right, t2.right)
    else:
        return False

if __name__ == "__main__":
# Test 4.1
    print "Test 4.1"
    t = buildTree(10, 100)
    print t
    print checkBalance(t)

# Test 4.2
    print "\nTest 4.2"
    Dgraph = buildDGraph(20)
    print Dgraph
    if findPath(Dgraph[3], Dgraph[4], Dgraph):
        printPath(Dgraph[3], Dgraph[4], Dgraph)
    else:
        print "Can not find path"

# Test 4.3
    print "\nTest 4.3"
    t = minHeightTree(range(63), 0, 62)
    print t

# Test 4.4 
    print "\nTest 4.4"
    lists = DepthLinkList(t)
    for i in range(len(lists)):
        print "Levle ", i, ":"
        for node in lists[i]:
            print node.value, 
        print

# Test 4.5
    print "\nTest 4.5"
    t = buildTree(200, 100)
    print t
    # left child case
    val = findSuccessor(t.left.left)
    if val:
        print "Left child", t.left.left.value, "next is", val.value
    # right child case
    val = findSuccessor(t.right.right)
    if val:
        print "Right child", t.right.right.value, "next is", val.value

# Test 4.6

# Test 4.7
    t1 = buildTree(10000, 10000)
    t2 = buildTree(2, 1000)
    
    print isSubtree(t1, t2)
