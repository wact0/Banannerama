#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

vector<string>* getOutline(vector<string>& input) {
	vector<string>* result = new vector<string>();
	return result;
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

