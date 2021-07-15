#include <ios>
#include <iostream>
#include <string.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    char *str = new char[101];
    cin >> str;
    char *token = strtok(str, "-");
    while(token != NULL){
        cout << *token;
        token = strtok(NULL, "-");
    }
//    cout << "\n";
    return 0;
}