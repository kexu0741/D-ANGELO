#include <iostream>
#include <string>
#include "BST.hpp"
using namespace std;

PlayerTree::PlayerTree()
{
  root = nullptr;
}
PlayerTree::~PlayerTree()
{

}

void print(PlayerNode *root)
{
    if(root==NULL)
    {
        return;
    }
    if (root->left != NULL)
	{
		print(root->left);
	}
		cout << "Player: " << root->name << endl;

	if (root->right != NULL)
	{
		print(root->right);
	}
}
void PlayerTree::printMovieInventory()
{
    print(root);
}
PlayerNode *spot(PlayerNode *temp, string title)
{

    if(title > temp->name)
    {
        if(temp->right!=NULL)
        {
            temp=spot(temp->right, title);
        }

            return temp;

    }
    else if(title < temp->name)
    {
        if(temp->left!=NULL)
        {
            temp=spot(temp->left, title);
        }

            return temp;

    }
}
void PlayerTree::addMovieNode(string name)
{
  PlayerNode *add = new PlayerNode(name);
  if(root==NULL)
  {
    root = add;
    return;
  }

  PlayerNode *temp = root;
  PlayerNode *a = spot(temp, name);

  if(name > a->name)
  {
      a->right = add;
  }
  else
  {
      a->left = add;
  }

}

void PlayerTree::findMovie(string title)
{
  if(root==NULL)
  {
    cout << "Player not found." << endl;
      return;
  }
  if(root->name == title)
  {
      cout << "Player Info:" << endl;
      cout << "==================" << endl;
      cout << "Name:" << root->name << endl;
      // cout << "Title  :" << root->title << endl;
      // cout << "Year   :" << root->year << endl;
      // cout << "rating :" << root->rating << endl;
  }
  else if(root->name.compare(title) > 0)
  {
    root = root->left;
    findMovie(title);
  }
  else
  {
    root = root->right;
    findMovie(title);
  }
}
PlayerNode* getMinValueNode(PlayerNode* currNode){

    if(currNode->left == NULL){
      return currNode;
    }
    return getMinValueNode(currNode->left);
}
PlayerNode* PlayerTree::deleteNodeHelper(PlayerNode *currNode, string value)
{

    if(currNode == NULL)
    {
      return NULL;
    }
    else if(value < currNode->name)
    {
      currNode->left = deleteNodeHelper(currNode->left, value);
    }
    else if(value > currNode->name)
    {
      currNode->right = deleteNodeHelper(currNode->right, value);
    }
   // We found the node with the value
    else
    {
      //TODO Case : No child
      if(currNode->left == NULL && currNode->right == NULL)
      {
        delete currNode;
        currNode = NULL;
      }
      //TODO Case : Only right child
      else if(currNode->left == NULL)
      {
        PlayerNode *delNode = currNode;
        currNode = currNode->right;
        delete delNode;
      }
      //TODO Case : Only left child
      else if(currNode->right == NULL)
      {
         PlayerNode *delNode = currNode;
        currNode = currNode->left;
        delete delNode;
      }
  //     //TODO Case: Both left and right child
      else
      {
        ///Replace with Minimum from right subtree
        string min = (getMinValueNode(currNode->right))->name;
        currNode->name = min;
        currNode->right = deleteNodeHelper(currNode->right, min);
      }
  //
     }
   return currNode;
}
void PlayerTree::deleteNode(string v)
{
  deleteNodeHelper(root, v);
}
int main()
{
  PlayerTree();
  PlayerTree p;
  p.addMovieNode("Zion Williamson");
  p.addMovieNode("Peter Parker");
  p.addMovieNode("Adam's APple");
  p.addMovieNode("Captain India");
  p.addMovieNode("Wonder Woman");
  p.addMovieNode("Chris Pratt");
  p.addMovieNode("Batman");
  p.addMovieNode("Loser");
  p.printMovieInventory();
  cout << "----------------------" << endl;
  p.deleteNode("Zion Williamson");
  p.printMovieInventory();
}
