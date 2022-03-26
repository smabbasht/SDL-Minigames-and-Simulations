#include<iostream>
#include<vector>

using namespace std;

struct Distance{
	int feet, inches;
};

int main(){
	vector<Distance> dst; // It's a vector that can store Distance type objects
	dst.push_back(Distance{3, 4}); // create an object, and push it in vector
	dst.push_back(Distance{5, 2});
	dst.push_back(Distance{2, 7});
	dst.push_back(Distance{7, 8});
	dst.push_back(Distance{13, 1});

    Distance d1 = {5, 12}; 
    dst.push_back(d1);
	
	for(int i=0;i<dst.size();i++)
		cout<<dst[i].feet<<"'"<<dst[i].inches<<'"'<<endl; // call show method of dst[i] object
}