//code for .csv convertor for data point output



#include <fstream>
#include <ctime>
#include <iostream>
#include <istream>
#include <cstdlib>
#include <string>

using namespace std;
void convert(string f);

int main()
{
    string filename;
    cout<<"Enter file name:";
    cin>>filename;
    string output = convert(filename);
}

string convert(string filename)
{
    fstream o;
    int tick=0;
    string output="";
    o.open(filename.c_str());
    string read_in;
    while(!o.eof())
    {
        tick++;
        read_in=getchar();
        if(read_in==' '||read_in=='\t')                 //tab/space delimitation to comma delimitation
        {
            while(read_in==' '||read_in=='\t')
            {
                getchar();
            }
            output=output+',';
        }
        else output=output+read_in;
        if(read_in=='\n')
        {
            tick++;
            if(tick>0&&tick%2=0)                //remove info lines for excel import
            {
                getline(o,read_in);
                read_in='\n';
            }
            output=output+read_in;
        }
    }
}
