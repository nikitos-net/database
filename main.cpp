#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>

using namespace std;

class Table
{
    protected:
    string name;
    vector <int> size;
    int columns;
    int lines;
    public:
    Table(vector <int> a = {20,20,20,20,20,20}){size = a;}
    void newTable(string newname);
    void addLine();
    void deleteLine(int id);
    void addcolumn();
    void deletecolumn(int id);
    void editdata();
};

void Table::editdata()
{
    int x, y;
    cout<<"Введите номер ряда: ";
    cin>>x;
    cout<<"Введите номер столбца: ";
    cin>>y;
    ifstream file(name);
    string copy[lines][columns];
    for(int i=0; i<lines; i++)
    {
        for(int j=0; j<columns; j++)
        {
            file >> copy[i][j];
        }
    }
    cout<<"Введите содержимое ячейки: ";
    cin>>copy[x-1][y-1];
    
    ofstream newfile(name);
    for(int i=0; i<lines; i++)
    {
        for(int j=0; j<columns; j++)
        {
            newfile << setw(size.at(j)) << left << copy[i][j];
        }
        newfile << endl;
    }
}

void Table::deletecolumn(int id)
{
    int start=0;
    int length=size.at(id-1);
    for(int i=0; i<id-1; i++) start+=size.at(i);
    ifstream file(name);
    string copy[lines+1];
    string s;
    int ls=0;
    while(!file.eof())
    {
    	getline(file,s);
    	if(ls<lines)
    	{
    	    s.erase(start, length);
    	    copy[ls]=s;
    	    ls++;
    	}
	}
	ofstream newfile(name);
	for(int i=0; i<lines; i++)
	{
	    newfile << copy[i] << endl;
	}
}

void Table::addcolumn()
{
    cout<<"Введите ширину колонки: ";
    int width;
    cin>>width;
    ifstream file(name);
    string copy[lines+1];
    int ls=0;
    while(!file.eof())
    {
    	getline(file,copy[ls]);
    	ls++;
	}
	string input;
	ofstream newfile(name);
	for(int i=0; i<lines; i++)
	{
	    cout<<"Введите значение "<<i+1<<"-ой ячейки: ";
	    cin>>input;
	    newfile << copy[i] << setw(width) << left << input << endl;
	}
	size.push_back(width);
}

void Table::deleteLine(int id)
{
    string copy[lines+1];
    ifstream file(name);
    int ls=0;
    string s;
    while(!file.eof())
    {
    	getline(file,s);
    	s.erase(0,size.at(0));
    	copy[ls]=s;
    	ls++;
	}
	int newid=1;
	ofstream newfile(name);
	for(int i=0; i<lines; i++)
	{
	    if(i+1!=id)
	    {
	        newfile << setw(size.at(0)) << left << newid << copy[i] << endl;
	        newid++;
	    }
	}
}

void Table::newTable(string newname)
{
    name = newname + ".txt";
    ifstream file(name);
    string s;
    int ls=0, ws=0;
    while(!file.eof())
    {
    	getline(file,s);
    	ls++;
	}
	file.clear();
	file.seekg(0);
	while(!file.eof())
    {
    	file >> s;
    	ws++;
	}
	ls--;
	lines=ls;
	columns=ws/ls;
	cout<<lines;
}

void Table::addLine()
{
     ofstream file(name, ios::app);
     cout<<"Введите данные каждого столбца через пробел: ";
     string input;
     file << setw(size.at(0)) << left << (lines+1);
     for(int i=1; i<columns; i++)
     {
        cin>>input;
        file << setw(size.at(i)) << left << input;
     }
     file << endl;
     lines++;
}

int main()
{
    vector <int> x = {5,20,20,20,5,5};
    vector <int> y = {5,20};
    vector <int> z = {5,5,5};
	Table students(x);
	Table subjects(y);
	Table grades(z);
	students.newTable("ученики");
	subjects.newTable("предметы");
	grades.newTable("оценки");
	subjects.addLine();
}