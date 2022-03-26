#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "node.hpp"
#include <fstream>
#include <vector>


using namespace std;

BSTNode* root = NULL; // this is the root of BST

// You have to define the functions below

//Approach:
// Since we needed to read data from txt file, so i extracted data from input.txt in loadTrucks(), 
// and instead of changing node.hpp I created an array of size 5 to hold info of each truck then passed that array to insertBST()
// for populating our BST. Then i created a void helper function journey() to call inside makeJourny() for doing petrol 
// calculations and updating info. And at last i printed all the updated info in "result.txt" as output in unloadTruck()
// which had traverse() as its helper function. The traverse() actually traverses the BST in ascending order i.e first left nodes then right nodes.


ofstream outfile ("result.txt");  // This opens the text file where we will write our final output


// This function is a helper function for loadTrucks() function basically it creates the BST
BSTNode* insertBST(BSTNode* root, string* lst) {
    if (root == NULL) {
        root = new BSTNode();
        root->val.driver = *(lst);
        root->val.petrol = stod(*(lst+1));
        root->val.regNo = *(lst+2);
        root->val.fullMileage = stoi(*(lst+3));
        root->val.emptyMileage = stoi(*(lst+4));
        root->left = NULL;
        root->right = NULL;
        return root;
    }

    if (root->val.regNo > *(lst+2)) {
        root->left = insertBST(root->left, lst);
    }
    else {
        root->right = insertBST(root->right, lst);
    }
    return root;
}

// This is helper function for makeJourney(). It does the calculation and update petrol info.
// This function works in the similar way to traverse() for traversing the tree.
void journey(BSTNode* root) {
    if (root == NULL) {
        return;
    }

    double empty = root->val.emptyMileage, full = root->val.fullMileage;
    double cost = (60/(empty) + 60/(full));
    //cout<< root->val.driver<< " "<< cost<< endl;

    journey(root->left);
    journey(root->right);
    if (cost > root->val.petrol) {
        return;
    }
    else {
        root->val.petrol = (root->val.petrol)-(cost);
    }
}


// This function is a helper function for unloadTruck(). 
//It traverse BST in ascending order ny first visiting left child notes and outputs in result.txt file
void traverse(BSTNode* root) {
        if (root == NULL) {
        return;
    }
    traverse(root->left);
    // here i am writing the output to the result.txt file
    outfile<<root->val.driver<<endl;
    outfile<<root->val.petrol<<endl;
    outfile<<root->val.regNo<<endl;
    outfile<<root->val.fullMileage<<endl;
    outfile<<root->val.emptyMileage<<endl;
    traverse(root->right);
}


// In this function i am reading the file and giving input to insertBST(). 
void loadTrucks() {
    string filename("input.txt");
    vector<string> lines;
    string line;

    ifstream input_file(filename);

    while (getline(input_file, line)){
        lines.push_back(line);
    }
    lines.push_back("last line"); // I added this extra line because of running the loop till m=5

    // I didn't changed the original file of node.hpp to make constructor. Instead i used a different approach.
    // instead of creating a constructor, i created an array of size for storing info of each truck then passed the array to insertBST()
    
    string arr [5];
    int m = 0;
    for (const auto &i : lines) {
        if (m==5) {
            root = insertBST(root, arr);
            m = 0;
        }
        *(arr+m) = i;
        ++m;
    }
    
}

// This is the main function, in here the helper function journey() is called.
void makeJourney() {
    journey(root);
}

// This is the main function, in here the helper function traverse() is called.
void unloadTrucks() {
    traverse(root);
    outfile.close();      
}

int main()
{
    
    loadTrucks();
    makeJourney();
    unloadTrucks();
    return 0;
}
