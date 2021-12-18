#include <iostream>
#include <string>
using namespace std;

// A program for counting words in a line. Any sequence of characters without 
// separators is considered a word.Separators are spaces, tabs, newlines.
// 
// The input string is passed to the program through the terminal as the argv[1]
// parameter.The program should display the number of words on the screen

int main(int argc, char* argv[])
{
    string const separators{ " \t\n" };
    string input_string = argv[1];
    cout << "\ninput string: " << input_string << endl;

    size_t begin, pos = 0;
    int res = 0;

    while ((begin = input_string.find_first_not_of(separators, pos)) != std::string::npos)
    {
        pos = input_string.find_first_of(separators, begin + 1);
        res++;
    }

    cout << "the number of words on the screen: " << res << endl;
    return 0;
}
