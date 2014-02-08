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
	int _index;
	bool _sorted;
	vector<Outline> _intersects;
	vector<int> _intersections;
	
	public:
		Outline() {
			_sorted = false;
			_index = 0;
		}
		Outline(int a,int b,int c) {
			_x1 = a;
			_x2 = c;
			_height = b;
			_sorted = false;
			_index = 0;
		}
		Outline(vector<int> a) {
			_x1 = a[0];
			_x2 = a[2];
			_height = a[1];
			_sorted = false;
			_index = 0;
		}
		Outline(vector<string> a) {
			_x1 = makeint(a[0]);
			_x2 = makeint(a[2]);
			_height = makeint(a[1]);
			_sorted = false;
			_index = 0;
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
		int intersection(Outline a) {
			int response;

			if(intersects(a)) {
				if(x1() > a.x1()) {
					if(height() < a.height()) {
						response = a.x2();
					} else {
						response = x1();
					}
				} else {
					if(height() < a.height()) {
						response = a.x1();
					} else {
						response = x2();
					}
				}

			} else {
				response = -1;
			}

			//returns intersection at height change
			return response;
		}
		bool sorted() {
			return _sorted;
		}
		void sorted(bool a) {
			_sorted = a;
		}
		int index() {
			return _index;
		}
		void index(int a) {
			_index = a;
		}
};

vector<Outline> sortedoutlines;
vector<Outline> sortoutlines(vector<Outline>& a) {
	if(a.size() > 0) {
		Outline current;

		for(int i=0;i<a.size();i++) {
			a[i].index(i);
			if(i == 0) {
				current = a[i];
			} else {
				if(a[i].x1() < current.x1()) {
					current = a[i];
				}
			}
		}

		sortedoutlines.push_back(current);
		a.erase(a.begin()+current.index());

		return sortoutlines(a);
	} else {
		return sortedoutlines;
	}
}

vector<string>* comparediff(vector<Outline> voutline) {
	vector<string>* response;

	return response;
}

vector<string>* getOutline(vector<string>& input) {
	vector<string> *response;
	vector<Outline> outlines;

	for(int i=0;i<input.size();i++) {
		vector<string> numbers = split(input[i]," ");
		outlines.push_back(numbers);
	}

	outlines = sortoutlines(outlines);
	response = comparediff(outlines);

	return response;

}

int main() {
	string ainit[] = {"14 8 17", "12 7 16", "11 6 14", "1 5 4", "2 8 6", "4 6 7"};
	vector<string> vinit(ainit,ainit+6);

	getOutline(vinit);

	return 0;
}