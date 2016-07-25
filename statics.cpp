#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

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
    string str;

    string year[11]={"2000", "2001","2002", "2003", "2004", "2005", "2006", "2007", "2008", "2009", "2010"};
    string zone_name[11] = {"11","10","9","8","7","6","5","4","1","2","3"};
    string seasons[4]={"Spring", "Summer", "Fall", "Winter"};
    for(int zone_num=0; zone_num<11; zone_num++)
    {
    	vector<float> zone_bar[4];
        for(int year_num=0; year_num<11; year_num++)
        {
            vector<float> spring_vec, summer_vec, fall_vec, winter_vec;
            string str;

            string filename="data/"+year[year_num]+"-"+zone_name[zone_num]+".txt";
            ifstream file(filename);

            while (getline(file, str))
            {
                istringstream in(str);
                int temp_grade, temp_day;
                float temp_wi;
                in>>temp_grade>>temp_day>>temp_wi;
                if(get_season(temp_day)==Spring)
                {
                    spring_vec.push_back(temp_wi);
                }
                else if(get_season(temp_day)==Summer)
                {
                    summer_vec.push_back(temp_wi);
                }
                else if(get_season(temp_day)==Fall)
                {
                    fall_vec.push_back(temp_wi);
                }
                else if(get_season(temp_day)==Winter)
                {
                    winter_vec.push_back(temp_wi);
                }
            }
            sort(spring_vec.begin(), spring_vec.end());
            sort(summer_vec.begin(), summer_vec.end());
            sort(fall_vec.begin(), fall_vec.end());
            sort(winter_vec.begin(), winter_vec.end());
            zone_bar[0].push_back((spring_vec[0]+spring_vec[1]+spring_vec[2]+spring_vec[3]+spring_vec[4])/5.0);
            zone_bar[1].push_back((summer_vec[0]+summer_vec[1]+summer_vec[2]+summer_vec[3]+summer_vec[4])/5.0);
            zone_bar[2].push_back((fall_vec[0]+fall_vec[1]+fall_vec[2]+fall_vec[3]+fall_vec[4])/5.0);
            zone_bar[3].push_back((winter_vec[0]+winter_vec[1]+winter_vec[2]+winter_vec[3]+winter_vec[4])/5.0);
        }
        for(int i=0; i<4; i++)
        {
            string out_filename="result/zone-"+zone_name[zone_num]+"-"+seasons[i]+".txt";
            ofstream outfile(out_filename);
            for(int j=0; j<zone_bar[i].size(); j++)
            {
                outfile<<year[j]<<'\t'<<zone_bar[i][j]<<endl;
            }
            outfile.close();
        }
    }
	return 0;
}