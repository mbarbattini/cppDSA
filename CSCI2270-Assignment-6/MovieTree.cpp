#include "MovieTree.hpp"
#include <cstdio>
#include <iostream>

using namespace std;


MovieTree::MovieTree() {
	root = nullptr;
}

MovieTree::~MovieTree() {
	MovieNode* node = root;
	while (node != nullptr) {
		if (node->right != nullptr) {
			delete node->right;	
		}
		node = node->left;
	}
}

void addNode(MovieNode* child, MovieNode* parent) {
	if (child->title <= parent->title && parent->left != nullptr) {
		// recursive to the left 
		addNode(child, parent->left);
	} else if (child->title <= parent->title && parent->left == nullptr) {
		// add to the left
		parent->left = child;
	} else if (child->title >= parent->title && parent->right != nullptr) {
		// recursive to the right
		addNode(child, parent->right);
	} else if (child->title >= parent->title && parent->right == nullptr) {
		// add to the right
		parent->right = child;
	}   	
}


void MovieTree::addMovieNode(int ranking, string title, int year, float rating) {
	MovieNode* newNode = new MovieNode(ranking, title, year, rating);
	// if the tree is empty, make the new node the root
	if (root == nullptr) {
		root = newNode;
	} else {
		addNode(newNode, root);	
	}	
}


void printBST(MovieNode* node) {
	if (node->left != nullptr) {
		printBST(node->left);
	}
	cout << "Movie: " << node->title << " " << node->rating << endl;
	if (node->right != nullptr) {
		printBST(node->right);
	}
}


void MovieTree::printMovieInventory() {
	if (root == nullptr) {
		cout << "Tree is empty. Cannot print" << endl;
	} else {
		printBST(root);
	}
}

//MovieNode* findNode(MovieNode* node, string title) {
	//// base case
	//if (node->title == title) {
		//return node;
	//}
	//if (title <= node->title && node->left != nullptr) {
		//findNode(node->left, title);
	//} else if (title >= node->title && node->right != nullptr) {
	////} else {
		//findNode(node->right, title);
	//}
	//// if it didn't find any, reutrn a nullptr
	//return nullptr;
//}

MovieNode* findNode(MovieNode* node, string title) {
	bool found = false;
	  while (!found) {
		if (title == node->title) {
		  found = true;
		  return node;
		}
		if (node->left == NULL && node->right == NULL) {
		  found = true;
		  return NULL;
		}
		if (node->title >= title) {
		  node = node->left;
		} else if (node->title <= title) {
		  node = node->right;
		}
	  }
	  return NULL;
}


void MovieTree::findMovie(string title) {
	MovieNode* node = nullptr;
	node = findNode(root, title);		
	if (node == nullptr) {
		cout << "That movie is not in the database." << endl;
		return;
	}
	cout << "Movie Info:" << endl;
	cout << "==================" << endl;
	cout << "Ranking:" << node->ranking << endl;
	cout << "Title  :" << node->title << endl;
	cout << "Year   :" << node->year << endl;
	cout << "rating :" << node->rating << endl;	
}

void queryBST(MovieNode* parent, float rating, int year) {
	if (parent->rating >= rating && parent->year >= year) {
		cout << parent->title << "(" << parent->year << ") " << parent->rating << endl;
	}
	if (parent->left != nullptr) {
		queryBST(parent->left, rating, year);
	}
	if (parent->right != nullptr) {
		queryBST(parent->right, rating, year);
	}
}


void MovieTree::queryMovies(float rating, int year) {
	cout << "Movies that came out after year " << year << " with a rating of at least " << rating << ":" << endl;
	queryBST(root, rating, year);
}

void avgRating(MovieNode* parent, MovieNode* avg) {
	// somehow need to track data through multiple recursive calls, and then return two variables
	// can't return more than one value in c++, so need to create an object for it.
	// In this case, just use the already created MovieNode struct and use the year and rating
	// as the places to store the total number of movies and the total rating, respectively
	// Don't need to return anything because we are just modifying the avg object's data
	avg->year++;
	avg->rating += parent->rating;
	if (parent->left != nullptr) {
		avgRating(parent->left, avg);
	} else if (parent->right != nullptr) {
		avgRating(parent->right, avg);
	}
}

void MovieTree::averageRating() {
	if (root == nullptr) {
		cout << "Average Rating: 0.0" << endl;
	} else {
		MovieNode* avg = new MovieNode(0, "", 0, 0.0);
		avgRating(root, avg);
		float answer = avg->rating / avg->year;
		cout << "Average Rating: " << answer << endl;	
	}

}
