#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class myString 
{
    private:
        string m_str;
    public:
        myString(string s){
            m_str=s;
        }
};

class ReadClass
{

public:
    void showClass()
    {
        ifstream in;
        string line;
        int count = 0, count_len = 0;
        string *ans = new string[1000];

        in.open("main.cpp");
        if (in.fail())
        {
            cout << "Error opeing a file" << endl;
            in.close();
        }
        while (getline(in, line))
        {

            if (line[0] == 'c' && line[1] == 'l')
            {

                // cout << line << endl;
                ans[count] = line;
                count++;
            }
        }
        cout << count << " class in main.cpp" << endl;
        for (int i = 0; i < count; i++)
        {
            cout << ans[i] << endl;
        }
        in.close();
    }
};

int main()
{
    ReadClass rfile;
    rfile.showClass();
    return 0;
}

