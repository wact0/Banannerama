#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

int makeint(string number) {
	int response;

	istringstream buffer(number);
	buffer >> response;

	return response;
}

bool vcontains(vector<int> vinteger,int integer) {
	return find(vinteger.begin(),vinteger.end(),integer) != vinteger.end();
}

vector<string> split(string sentence,string delimiter) {
	vector<string> cache;
	bool strhasmatch = true;

	string temp = sentence;

	while(strhasmatch) {
		if(temp.find(delimiter) > temp.size()) {
			cache.push_back(temp);
			strhasmatch = false;
		} else {
			if(temp.size() > 0) {
				cache.push_back(temp.substr(0,temp.find(delimiter)));
				temp = temp.substr(temp.find(delimiter)+1,temp.size());
			} else {
				strhasmatch = false;
			}
		}
	}
	
	return cache;
}

class Outline {
	int _x1;
	int _x2;
	int _height;
	vector<Outline> _intersects;
	
	public:
		Outline(int a,int b,int c) {
			_x1 = a;
			_x2 = c;
			_height = b;
		}
		Outline(vector<int> a) {
			_x1 = a[0];
			_x2 = a[2];
			_height = a[1];
		}
		Outline(vector<string> a) {
			_x1 = makeint(a[0]);
			_x2 = makeint(a[2]);
			_height = makeint(a[1]);
		}

		int x1() {
			return _x1;
		}
		int x2() {
			return _x2;
		}
		int height() {
			return _height;
		}
		bool intersects(Outline a) {
			bool response = false;

			if((a.x1() >= x1() && a.x1() <= x2()) || (a.x2() >= x1() && a.x2() <= x2())) {
				response = true;
			}

			return response;
		}
};

vector<string> getOutline(vector<string>& input) {
	vector<string> outline;
	vector<vector<int> > ints;

	for(int i=0;i<input.size();i++) {
		vector<string> values = split(input[i]," ");
		outline.push_back(input[i]);

		vector<int> vint;

		for(int x=0,y=1;x<values.size();x++,y++) {
			vint.push_back(makeint(values[x]));
		}

		ints.push_back(vint);
	}

	//building outline vector manager
	vector<int> _basestructure; //contains 3 integers representing a current structure
	vector<int> _usedindices; //contains used basestructures and valid used matches

	for(int i=0;i<ints.size();i++) {
		int x1 = ints[i][0];
		int height = ints[i][1];
		int x2 = ints[i][2];

		if(!_basestructure.size()) {
			_basestructure.push_back(x1);
			_basestructure.push_back(height);
			_basestructure.push_back(x2);

			_usedindices.push_back(i);
		} else {
			//once a basestructure has been established, use the power of technology to check for intersections
			bool intersectsleft = false;
			bool intersectsright = false;

			//check to see if structure / part of structure is contained within the basestructure
			if(x1 >= _basestructure[0] && x1 <= _basestructure[2]) {
				intersectsleft = true;

				if(!vcontains(_usedindices,i)) {
					_usedindices.push_back(i); //add our intercepting index to the list
				}
			}
			if(x2 >= _basestructure[0] && x2 <= _basestructure[2]) {
				intersectsright = true;
			}
		}
	}

	return outline;

} 

int main() {
	string ainit[] = {"14 8 17", "12 7 16", "11 6 14", "1 5 4", "2 8 6", "4 6 7"};
	vector<string> vinit(ainit,ainit+6);

	// getOutline(vinit);
	vector<string> samplevect;
	samplevect.push_back("3");
	samplevect.push_back("8");
	samplevect.push_back("9");

	vector<Outline> outlines;
	outlines.push_back(Outline(1,2,5));
	outlines.push_back(Outline(4,7,6));
	outlines.push_back(Outline(samplevect));

	if(outlines[0].intersects(outlines[1])) {
		cout << "Outline [1] intersects outline [0]" << endl;
	}

	cout << outlines[2].height() << endl;

	return 0;
}