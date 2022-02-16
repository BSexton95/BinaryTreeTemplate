#ifndef _BINARYTREE_H_
#define _BINARYTREE_H_

#pragma once
template<typename T>
class TreeNode;

template<typename T>
class BinaryTree
{
public:
	/// <summary>
	/// Constructor for the binary tree
	/// </summary>
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
	TreeNode<T>* find(T value);

	void draw(TreeNode<T>* selected = nullptr);

private:
	/// <summary>
	/// Finds the node that matches the value in the list
	/// </summary>
	/// <param name="searchValue">The value of the node to search for</param>
	/// <param name="nodeFound">A pointer that will store the address of the node that was found</param>
	/// <param name="nodeParent">A pointer that will store the address of the parent of the node that was found</param>
	/// <returns>Whether or not a node matching the value could be found</returns>
	bool findNode(T searchValue, TreeNode<T>*& nodeFound, TreeNode<T>*& nodeParent);

	void draw(TreeNode<T>* currentNode, int x, int y, int horizontalSpacing, TreeNode<T>* selected = nullptr);

	TreeNode<T>* m_root = nullptr;
};

#endif

template<typename T>
bool BinaryTree<T>::isEmpty() const
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
		else if (value == tempNode->getData())
			return;
	}
}

template<typename T>
void BinaryTree<T>::remove(T value)
{
	//Create a node that will be the node to remove
	TreeNode<T>* nodeToRemove = new TreeNode<T>(value);
	//Create a node that keeps track of the parent node
	TreeNode<T>* parentNode = new TreeNode<T>();

	//Finds the node to removes parent node
	//If the value can't be find it will break return
	if (!findNode(value, nodeToRemove, parentNode))
		return;

	

	//If the node to remove doesn't have a left or a right node...
	if (!nodeToRemove->hasLeft() && !nodeToRemove->getRight())
	{
		if (m_root->getData() == value)
		{
			delete m_root;
			m_root = nullptr;
			return;
		}

		//...delete the node
		delete nodeToRemove;
		//If the node to removes parent left is the node to remove...
		if (parentNode->getLeft() == nodeToRemove)
			//...set the parents left to be null
			parentNode->setLeft(nullptr);
		//Otherwise set the parents right to be null
		else
			parentNode->setRight(nullptr);

		
	}
	//If the node to remove has a left and doesn't have a right...
	else if (nodeToRemove->hasLeft() && !nodeToRemove->hasRight())
	{
		if (m_root->getData() == value)
		{
			m_root = m_root->getLeft();
			m_root->setLeft(nullptr);
			return;
		}
		//If the node to removes parents left node is the node to remove...
		if (parentNode->getLeft() != nodeToRemove)
			//...set the parents right node to be the node to removes left node
			parentNode->setRight(nodeToRemove->getLeft());
		//Otherwise set the parents left node to be the node to removes left node
		else
			parentNode->setLeft(nodeToRemove->getLeft());
		
		//Delete the node to be removed
		delete nodeToRemove;
	}
	//If the node to be removed doesn't have a left and has a right
	else if (!nodeToRemove->hasLeft() && nodeToRemove->hasRight())
	{
		if (m_root->getData() == value)
		{
			m_root = m_root->getRight();
			m_root->setRight(nullptr);
			return;
		}
		//If the parent node of the node to be removed right is the node to be removed...
		if (parentNode->getRight() != nodeToRemove)
			//...set the parent nodes left to be the node to removes right
			parentNode->setLeft(nodeToRemove->getRight());
		//Otherwise set the parent nodes right to be the node to be removeds right
		else
			parentNode->setRight(nodeToRemove->getRight());

		//Delete the node to be removed
		delete nodeToRemove;
	}
	//If the node to be removed has a left and a right...
	else if (nodeToRemove->hasLeft() && nodeToRemove->hasRight())
	{
		//Create a current node that is se to be the node to be removeds right node
		TreeNode<T>* currentNode = nodeToRemove->getRight();
		//Set the parent node to be the current node
		parentNode = currentNode;
		//Create a boolean that will be true when you reach the furthes right nodes left
		bool furthestRightsLeft = false;

		//If the current node has a left...
		if (currentNode->hasLeft())
		{
			//Loop until the furthest rights left is reached
			while (!furthestRightsLeft)
			{
				//IF the parents left node has a left...
				if (parentNode->getLeft()->hasLeft())
				{
					//...set the parent node to be it's left
					parentNode = parentNode->getLeft();
				}
				//Otherwise....
				else
				{
					//...set the current node to be the parent nodes left
					currentNode = parentNode->getLeft();

					//set the boolean to be true
					furthestRightsLeft = true;
				}
			}
			//set the data of the node to be removed to be the data of the current node
			nodeToRemove->setData(currentNode->getData());
			//set the left of the parents node to be the current nodes right
			parentNode->setLeft(currentNode->getRight());
			//Delete the current node
			delete currentNode;
		}
		//Otherwise...
		else
		{
			//...set the node to be removeds data to be the current nodes data
			nodeToRemove->setData(currentNode->getData());

			//If the node to be removeds right node has a right node...
			if (nodeToRemove->getRight()->hasRight())
			{
				//...set the node to be reomveds right to be the current nodes right
				nodeToRemove->setRight(currentNode->getRight());
			}
			//Otherwise set the node to be removeds right to be null
			else
			{
				nodeToRemove->setRight(nullptr);
			}
			//Delete the current node
			delete currentNode;
		}
	}
}


template<typename T>
TreeNode<T>* BinaryTree<T>::find(T value)
{
	bool nodeFound = false;
	//Create a new node to keep track of the current node
	//set it to be the root
	TreeNode<T>* currentNode = m_root;

	//Loops while node hasn't been found
	while (nodeFound != true)
	{
		//If the current nodes value is less than the value to be found...
		if (currentNode->getData() < value)
		{
			//...set the current node to be the node to it's right if it has a right
			if (currentNode->hasRight())
				currentNode = currentNode->getRight();
		}
		//else if the current nodes value is greater than the value to be found...
		else if (currentNode->getData() > value)
		{
			//...set the current node to be the node to it's left if it has a left
			if (currentNode->hasLeft())
				currentNode = currentNode->getLeft();
		}
		//Otherwise if the current nodes value is equal to the value to be found...
		else if (currentNode->getData() == value)
		{
			//return the current node
			return currentNode;
		}
	}

	return currentNode;
}

template<typename T>
void BinaryTree<T>::draw(TreeNode<T>* selected)
{
	draw(m_root, 400, 40, 400, selected);
}

template<typename T>
bool BinaryTree<T>::findNode(T searchValue, TreeNode<T>*& nodeFound, TreeNode<T>*& nodeParent)
{
	bool foundNode = false;
	nodeFound = m_root;
	nodeParent = m_root;

	while (foundNode != true)
	{
		if (nodeFound->getData() < searchValue)
		{
			if (nodeFound->hasRight())
			{
				nodeParent = nodeFound;
				nodeFound = nodeFound->getRight();
				
			}
		}
		else if (nodeFound->getData() > searchValue)
		{
			if (nodeFound->hasLeft())
			{
				nodeParent = nodeFound;
				nodeFound = nodeFound->getLeft();
				
			}
		}
		else if (nodeFound->getData() == searchValue)
		{
			
			return true;
		}
		
	}

	
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
