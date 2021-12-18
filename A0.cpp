#include <iostream>
#include <string>
using namespace std;

int main(int argc, char* argv[])
{
	string s, word = "";
	getline(cin, s);
	s += ' ';

	int res = 0;
	for (auto c : s) {
		if (((c == ' ') or (c == '	') or (c == '\n')) and (word != "")) {
			res++;
			word = "";
		}
		else {
			word += c;
		}
	}

	cout << "Number of words in line: " << res;
	return 0;
}
