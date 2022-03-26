#include<iostream>
#include<vector>

using namespace std;

class Distance{
	int feet, inches;
	public:
	Distance(int ft, int inch): feet(ft), inches(inch){}
	void show(){
		cout<<feet<<"'"<<inches<<"\""<<endl;
	}
};

int main(){
	vector<Distance*> dst; // It's a vector that can store Distance type objects
	dst.push_back(new Distance(3, 4)); // create an object, and push it in vector
	dst.push_back(new Distance(5, 2));
	dst.push_back(new Distance(2, 7));
	dst.push_back(new Distance(7, 8));
	dst.push_back(new Distance(13, 1));
	
	for(int i=0;i<dst.size();i++)
		dst[i]->show(); // call show method of dst[i] object
		
	// deleting the objects, need to delete every single object created dynamically
	for(int i=0;i<dst.size(); i++)
		delete dst[i];
	
	dst.clear(); //clears all the items from vector
	
}