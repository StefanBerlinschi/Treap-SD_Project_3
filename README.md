# Treap-SD_Project_3
This is my C++ implementation of the treap data structure.

A treap is a data structure that combines the properties of a Binary Search Tree
and a Heap. Each node has a key value and a priority value. 

The key vales are such that all key values in the left subtree of a node are smaller than the key of that node 
and all the values in the right subtree are greater than that of our node.

The priority values are chosen at random and the treap is constructed such that both the left and right
child nodes have smaller priority numbers than their parent node (a maxHeap). The root of the treap will
have the highest priority.
