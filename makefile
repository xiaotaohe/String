Binary:BinarySearchTree.cpp BinarySearchTree.hpp
	g++ $^ -o $@ -g
string:string.cpp
	g++ $^ -o $@ -g
.PHONY:clean
clean:
	rm -rf Binary
	rm -rf string
