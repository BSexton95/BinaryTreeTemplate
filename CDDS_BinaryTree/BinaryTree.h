#ifndef _BINARYTREE_H_
#define _BINARYTREE_H_

#pragma once
template<typename T>
class TreeNode;

template<typename T>
class BinaryTree
{
public:

	BinaryTree() {};
	~BinaryTree() {};

	/// <summary>
	/// Returns whether or not there are any nodes in the list
	/// </summary>
	bool isEmpty() const;
	/// <summary>
	/// Creates a new node that stores the given value and places it into the tree
	/// </summary>
	/// <param name="value">The new value to add to the tree</param>
	void insert(T value);
	/// <summary>
	/// Finds the node with the given value and removes it from the tree
	/// </summary>
	/// <param name="value">The value of the node to search for in the tree</param>
	void remove(T value);
	/// <summary>
	/// Finds and returns a node with the given value in the tree
	/// </summary>
	/// <param name="value">The value of the node to search for</param>
	TreeNode<T>* find(T value) {return nullptr;}

	void draw(TreeNode<T>* selected = nullptr);

private:
	/// <summary>
	/// Finds the node that matches the value in the list
	/// </summary>
	/// <param name="searchValue">The value of the node to search for</param>
	/// <param name="nodeFound">A pointer that will store the address of the node that was found</param>
	/// <param name="nodeParent">A pointer that will store the address of the parent of the node that was found</param>
	/// <returns>Whether or not a node matching the value could be found</returns>
	bool findNode(T searchValue, TreeNode<T>*& nodeFound, TreeNode<T>*& nodeParent) {}

	void draw(TreeNode<T>* currentNode, int x, int y, int horizontalSpacing, TreeNode<T>* selected = nullptr);

	TreeNode<T>* m_root = nullptr;
};

#endif

template<typename T>
inline bool BinaryTree<T>::isEmpty() const
{
	if (m_root->getLeft() == nullptr && m_root->getRight() == nullptr)
		return true;
	else
		return false;
}

template<typename T>
void BinaryTree<T>::insert(T value)
{
	bool nodeInserted = false;
	//Create a new node
	TreeNode<T>* newNode = new TreeNode<T>(value);
	//Create a temporary node that is set to be the root
	TreeNode<T>* tempNode = m_root;
	
	//If the root is null...
	if (m_root == nullptr)
	{
		//...set the root to be the new node
		m_root = newNode;
		//set node inserted to be true
		nodeInserted = true;
	}

	//Loops while the node inserted is false
	while (nodeInserted != true)
	{
		//If the value of the new node is less than the value of the temporary node...
		if (newNode->getData() < tempNode->getData())
		{
			//...Check to see if the left node is null or not
			//If the left of the temperary node is not null...
			if (tempNode->getLeft() != nullptr)
			{
				//...go to the next left
				tempNode = tempNode->getLeft();

			}
			//Otherwise insert the new node in the empty spot
			//and set node inserted to be true
			else
			{
				tempNode->setLeft(newNode);
				nodeInserted = true;
			}
		}
		//Otherwise if the value of the new node is greater than the value of the temporary node...
		else if (newNode->getData() > tempNode->getData())
		{
			//...Check to see if the right node is null or not
			//If the right of the temporary node is not null...
			if (tempNode->getRight() != nullptr)
			{
				//...go to the next right
				tempNode = tempNode->getRight();
			}
			//Otherwise insert the new node in the empty spot
			//and set node inserted to be true
			else
			{
				tempNode->setRight(newNode);
				nodeInserted = true;
			}
		}
	}
}

template<typename T>
inline void BinaryTree<T>::remove(T value)
{
	
}

template<typename T>
inline void BinaryTree<T>::draw(TreeNode<T>* selected)
{
	draw(m_root, 400, 40, 400, selected);
}

template<typename T>
inline void BinaryTree<T>::draw(TreeNode<T>* currentNode, int x, int y, int horizontalSpacing, TreeNode<T>* selected)
{
	//Decrese the horizontal space as the nodes draw
	horizontalSpacing /= 2;

	//Check if the current node is null
	if (currentNode)
	{
		//Draws the left child if this node has one
		if (currentNode->hasLeft())
		{
			//Draws a line between the left child and the current node
			DrawLine(x, y, x - horizontalSpacing, y + 80, RED);
			//Draws the left child
			draw(currentNode->getLeft(), x - horizontalSpacing, y + 80, horizontalSpacing, selected);
		}

		//Draws the right child if this node has one
		if (currentNode->hasRight())
		{
			//Draws a line between this child and the current node
			DrawLine(x, y, x + horizontalSpacing, y + 80, RED);
			//Draws the right child
			draw(currentNode->getRight(), x + horizontalSpacing, y + 80, horizontalSpacing, selected);
		}

		//Draws the current node
		currentNode->draw(x, y, (selected == currentNode));
	}
}
