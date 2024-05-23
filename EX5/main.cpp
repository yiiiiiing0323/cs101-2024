#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class myString {
    private:
        string m_str;
    public:
        myString(string s) {
            m_str = s;
        }
};

class ReadClass {
    private:
        string str[100];
        int number = 0;
    public:
        void readFile(const string& filename) {
            ifstream in(filename);
            if (in.fail()) {
                cout << "Error opening a file" << endl;
                return;
            }

            string line;
            while (getline(in, line)) {
                if (line.find("class") != string::npos) {
                    str[number] = line;
                    number++;
                }
            }
            in.close();
        }

        void showClass() {
            cout << number << " classes in main.cpp" << endl;
            for (int i = 0; i < number; i++) {
                cout << str[i] << endl;
            }
        }
};

int main() {
    ReadClass rfile;
    rfile.readFile("main.cpp");
    rfile.showClass();

    return 0;
}
