#include <iostream>
using namespace std;

int main()
{
    char s[80];
    int slovo, count = 0;
    system("chcp 1251");
    system("cls");
    cout << "enter your string here: " << endl;
    cin.get(s, 80);
    int i = 0;
    while (s[i] == ' ' && s[i] != '\0')
        i++;
    slovo = 0;
    while (s[i] != '\0') {
        if (s[i] != ' ' && slovo == 0)
        {
            slovo = 1;
            count++;
        }
        else if (s[i] == ' ')
            slovo = 0;
        i++;
    }
    cout << "Number of words per line: " << count;
    cin.get(); cin.get();
    return 0;
}