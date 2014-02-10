#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>

using namespace std;

int longestindex = 0;

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
		// string intersection(Outline a) {
		// 	string response;

		// 	if(intersects(a)) {
		// 		if(x1() > a.x1()) { //if x of the called outline is greater than the passed outline
		// 			if(height() < a.height()) {
		// 				response = "("+to_string(a.x2()) + "," + to_string(height())+")";
		// 			} else {
		// 				response = "("+to_string(x1()) + "," + to_string(a.height())+")";
		// 			}
		// 		} else {
		// 			if(height() < a.height()) {
		// 				response = "("+to_string(a.x1()) + "," + to_string(a.height())+")";
		// 			} else {
		// 				response = "("+to_string(x2()) + "," + to_string(a.height())+")";
		// 			}
		// 		}

		// 	} else {
		// 		response = "";
		// 	}

		// 	//returns intersection at height change
		// 	return response;
		// }
		string intersection(Outline a) { ////--
			string response = "";

			if(intersects(a)) {

				if(height() < a.height()) {
					response = "("+to_string(a.x1()) + "," + to_string(a.height())+")";
				} else {
					response = "("+to_string(x2()) + "," + to_string(a.height())+")";
				}
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
	//delete sortoutlines;
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
		vector<Outline> temp;
		for(int i=0;i<sortedoutlines.size();i++) {
			temp.push_back(sortedoutlines[i]);
		}

		sortedoutlines.clear();
		return temp;
	}
}

vector<string> comparediff(vector<Outline> voutline) {
	vector<string> res;

	res.push_back("("+to_string(voutline[0].x1())+","+to_string(voutline[0].height())+")");
	for(int i=0;i<voutline.size()-1;i++) {
		voutline[i].index(i);
		voutline[i+1].index(i+1);

		if(voutline[i].intersects(voutline[i+1])) {
			string out = voutline[i].intersection(voutline[i+1]);

			res.push_back(out);
		} else {
			res.push_back("("+to_string(voutline[i].x2())+",0)");
			res.push_back("("+to_string(voutline[i+1].x1()) + "," + to_string(voutline[i+1].height())+")");
		}
	}

	res.push_back("("+to_string(voutline[voutline.size()-1].x2()) + ",0)");

	// vector<string>* response = &res;

	return res;
}

//vector<string> *response;
vector<string>* getOutline(vector<string>& input) {
	vector<Outline> outlines;

	for(int i=0;i<input.size();i++) {
		vector<string> numbers = split(input[i]," ");
		outlines.push_back(numbers);
	}

	outlines = sortoutlines(outlines); ////--

	vector<string> comparedoutlines = comparediff(outlines);

	vector<string>* holder = new vector<string>();

	for (int i = 0; i < comparedoutlines.size(); i++) {
		string str_hold = comparedoutlines[i];
		holder->push_back(str_hold);
	}

	return holder;
}

void assertingEquals(int number, vector<string>& actual, vector<string>& expected) {
	bool failed = false;
	cout << "case " << setw(2) << number << ": ";
	for (int i = 0; i < expected.size(); i++) {
		if (i < actual.size()) {
			if (actual[i] != expected[i]) {
				failed = true;
				cout << "fail: expected " << expected[i] << " but was " << actual[i];
				break;
			}
		}
		else {
			failed = true;
			cout << "fail: expected " << expected[i] << " but results ended prematurely.";
			break;
		}
	}
	if (!failed) {
		if (actual.size() != expected.size()) {
			cout << "fail: actual has more data than needed";
		}
		else {
			cout << "ok";
		}
	}
	cout << endl;
}

int main (int argc, char * const argv[]) {
	vector<string> input;
	vector<string> expected;
	for (int i = 0; i < 10; i++) {
		input   .clear();
		expected.clear();
		switch (i) {
			case 0:
				input   .push_back( "0 42 6" );

				expected.push_back( "(0,42)" );
				expected.push_back( "(6,0)" );
				break;
			case 1:
				input   .push_back( "5 4 10" );
				input   .push_back( "15 3 20" );

				expected.push_back( "(5,4)" );
				expected.push_back( "(10,0)" );
				expected.push_back( "(15,3)" );
				expected.push_back( "(20,0)" );
				break;
			 case 2:
				input   .push_back( "180 1 359" );
				input   .push_back( "90 3 180" );
				input   .push_back( "0 2 90" );
        
				expected.push_back( "(0,2)" );
				expected.push_back( "(90,3)" );
				expected.push_back( "(180,1)" );
				expected.push_back( "(359,0)" ); 
				break;
 			case 3:
				input   .push_back( "140 4 240" );
				input   .push_back( "90 9 190" );

				expected.push_back( "(90,9)" );
				expected.push_back( "(190,4)" );
				expected.push_back( "(240,0)" );
				break;
			case 4:
				input   .push_back( "200 9 300" );
				input   .push_back( "30 4 230" );

				expected.push_back( "(30,4)" );
				expected.push_back( "(200,9)" );
				expected.push_back( "(300,0)" );
				break;
			case 5:
				input   .push_back( "1 5 4" );
				input   .push_back( "2 8 6" );
				input   .push_back( "4 6 7" );

				expected.push_back( "(1,5)" );
				expected.push_back( "(2,8)" );
				expected.push_back( "(6,6)" );
				expected.push_back( "(7,0)" );
				break;
			case 6:
				input   .push_back( "14 8 17" );
				input   .push_back( "12 7 16" );
				input   .push_back( "11 6 14" );

				expected.push_back( "(11,6)" );
				expected.push_back( "(12,7)" );
				expected.push_back( "(14,8)" );
				expected.push_back( "(17,0)" );
				break;
			case 7:
				input   .push_back( "14 8 17" );
				input   .push_back( "12 7 16" );
				input   .push_back( "11 6 14" );
				input   .push_back( "1 5 4" );
				input   .push_back( "2 8 6" );
				input   .push_back( "4 6 7" );

				expected.push_back( "(1,5)" );
				expected.push_back( "(2,8)" );
				expected.push_back( "(6,6)" );
				expected.push_back( "(7,0)" );
				expected.push_back( "(11,6)" );
				expected.push_back( "(12,7)" );
				expected.push_back( "(14,8)" );
				expected.push_back( "(17,0)" );
				break;
			case 8:
				input   .push_back( "5 2 7" );
				input   .push_back( "3 5 8" );
				input   .push_back( "1 8 9" );

				expected.push_back( "(1,8)" );
				expected.push_back( "(9,0)" );
				break;
			case 9:
				input   .push_back( "1 11 5" );
				input   .push_back( "2 6 7" );
				input   .push_back( "3 13 9" );
				input   .push_back( "12 7 16" );
				input   .push_back( "14 3 25" );
				input   .push_back( "19 18 22" );
				input   .push_back( "23 13 29" );
				input   .push_back( "24 4 28" );

				expected.push_back( "(1,11)" );
				expected.push_back( "(3,13)" );
				expected.push_back( "(9,0)" );
				expected.push_back( "(12,7)" );
				expected.push_back( "(16,3)" );
				expected.push_back( "(19,18)" );
				expected.push_back( "(22,3)" );
				expected.push_back( "(23,13)" );
				expected.push_back( "(29,0)" );
				break;
			default:
				break;
		}
		vector<string>* actual = getOutline( input );
		assertingEquals( i, *actual, expected );
		delete actual;
	}
    return 0;
}