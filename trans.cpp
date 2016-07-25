#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

#define Spring 1
#define Summer 2
#define Fall 3
#define Winter 4

int get_season(int day)
{
	if((day>=32)&&(day<=120))
    {
		return Spring;
    }
	else if((day>=121)&&(day<=212))
    {
		return Summer;
    }
	else if((day>=213)&&(day<=304))
    {
		return Fall;
    }
	else if(((day>=1)&&(day<=31))||((day>=305)&&(day<=366)))
    {
		return Winter;
    }
	else
    {
		return -1;
    }
}

int main()
{
    string year[11]={"2000", "2001","2002", "2003", "2004", "2005", "2006", "2007", "2008", "2009", "2010"};
    string zone_name[11] = {"11","10","9","8","7","6","5","4","1","2","3"};
    for(int year_num=0; year_num<11; year_num++)
    {
    	vector<int> day[11];
	    vector<float> wi[11];
	    vector<int> grade[11];

	    string str;

    	string filename="data/"+year[year_num]+".txt";
		ifstream file(filename);

	    int zones=11;
	    int entries_num[11] = { 0 };

	    getline(file, str);
	    istringstream entries_in(str);
	    for(int i=0; i<zones; i++)
	    {
	        entries_in>>entries_num[i];
	    }

	    int line=1;
	    while (getline(file, str))
	    {
	        istringstream in(str);
	        for(int i=0; i<zones; i++)
	        {
	            int temp_day;
	            float temp_wi;
	            string temp;
	            if(line<=entries_num[i])
	            {
	                in>>temp_day>>temp>>temp_wi;
	                day[i].push_back(temp_day);
	                wi[i].push_back(temp_wi);
	            }
	        }
	        line++;
	    }
	    string grade_filename="data/"+year[year_num]+"-grade.txt";
	    ifstream grade_file(grade_filename);
	    line=1;
	    while (getline(grade_file, str))
	    {
	        istringstream grade_in(str);
	        for(int i=0; i<zones; i++)
	        {
	            int temp_grade, temp_grade_0, temp_grade_1, temp_grade_2;
	            grade_in>>temp_grade>>temp_grade_0>>temp_grade_1>>temp_grade_2;
	            if(line<=entries_num[i])
	            {
	                if(temp_grade==0)
	                {
	                    grade[i].push_back(1);
	                }
	                else if(temp_grade==6)
	                {
	                    grade[i].push_back(2);
	                }
	                else if(temp_grade==43)
	                {
	                    grade[i].push_back(3);
	                }
	                else if(temp_grade==10)
	                {
	                    grade[i].push_back(4);
	                }
	                else if(temp_grade==33)
	                {
	                    grade[i].push_back(5);
	                }
	                else if(temp_grade==44)
	                {
	                    grade[i].push_back(6);
	                }
	                else if(temp_grade==3)
	                {
	                    grade[i].push_back(7);
	                }
	                else
	                {
	                    grade[i].push_back(-1);
	                }
	            }
	        }
	        line++;
	    }
	    for(int i=0; i<zones; i++)
	    {
	        string out_filename="data/"+year[year_num]+"-"+zone_name[i]+".txt";
	        ofstream outfile(out_filename);
	        for(int j=0; j<day[i].size(); j++)
	        {
	            outfile<<grade[i][j]<<'\t'<<day[i][j]<<'\t'<<wi[i][j]<<endl;
	        }
	        outfile.close();
	    }
    }
	return 0;
}