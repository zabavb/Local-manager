#include<iostream>
#include<fstream>
#include<vector>
#include<map>
#include<algorithm>
using namespace std;

class CITY
{
private:
	string city;
public:
	CITY() : city{ "" }
	{}
	CITY(string city) : city{ city }
	{}

	string GET_city() const
	{
		return this->city;
	}

	void SET_city(string city)
	{
		this->city = city;
	}
	friend ostream& operator<< (ostream& os, const CITY& tmp);
};
ostream& operator<< (ostream& os, const CITY& tmp)
{
	os << "City: " << tmp.city;
	return os;
}

class DATA
{
private:
	map<string, vector<CITY>> mp;
public:
	void ADD_country(string country)
	{
		for (auto it = mp.find(country); it != mp.end(); it++)
		{
			cout << "\tThis country has already added!" << endl;
			return;
		}

		vector<CITY> vec;
		mp.insert({ country, vec });
	}
	void ADD_city(string country, string city)
	{
		bool find_country = false;
		for (auto it = mp.find(country); it != mp.end(); it++)
		{
			find_country = true;

			for (auto it_2 = it->second.begin(); it_2 != it->second.end(); it_2++)
			{
				if (it_2->GET_city() == city)
				{
					cout << "\tThis city has already added!" << endl;
					cout << "Country: " << it->first << ": " << it_2->GET_city() << endl;
				}
			}
			it->second.push_back(city);

			return;
		}
		if (find_country == false)
			cout << "\tCountry wasn't found!" << endl;

		vector<CITY> vec;
		vec.push_back(city);

		mp.insert({ country, vec });
	}
	void FIND_city(string city)
	{
		for (auto it = mp.begin(); it != mp.end(); it++)
		{
			bool find_city = false;

			for (auto it_2 = it->second.begin(); it_2 != it->second.end(); it_2++)
			{
				if (it_2->GET_city() == city)
				{
					find_city = true;
					cout << it->first << ": " << endl << it_2->GET_city() << endl;
					return;
				}
			}
			if (find_city == false)
				cout << "\tCity wasn't found!" << endl;
		}
	}
	void EDIT_city(string country, string city, string new_city)
	{
		bool find_country = false;
		for (auto it = mp.find(country); it != mp.end(); it++)
		{
			find_country = true;
			bool find_city = false;

			for (auto it_2 = it->second.begin(); it_2 != it->second.end(); it_2++)
			{
				if (it_2->GET_city() == city)
				{
					find_city = true;

					it_2->SET_city(new_city);
					cout << it->first << ": " << endl << it_2->GET_city() << endl;
					return;
				}
			}
			if (find_city == false)
				cout << "\tCity wasn't found!" << endl;
		}
		if (find_country == false)
			cout << "\tCountry wasn't found!" << endl;
	}
	void DELETE_country(string country)
	{
		auto it = mp.find(country);
		mp.erase(it);
		cout << "\tDeleted!" << endl;
	}
	void DELETE_city(string country, string city)
	{
		bool find_country = false;
		for (auto it = mp.find(country); it != mp.end(); it++)
		{
			find_country = true;
			bool find_city = false;

			for (auto it_2 = it->second.begin(); it_2 != it->second.end(); it_2++)
			{
				if (it_2->GET_city() == city)
				{
					it->second.erase(it_2);
					return;
				}
			}

			if (find_city == false)
				cout << "\tCity wasn't found!" << endl;
		}
		if (find_country == false)
			cout << "\tCountry wasn't found!" << endl;
	}
	int COUNT_of_cities()
	{
		int count = 0;
		for (auto it = mp.begin(); it != mp.end(); it++)
			for (auto it_2 = it->second.begin(); it_2 != it->second.end(); it_2++)
				count++;
		return count;
	}
	void Print()
	{
		for (auto it = mp.begin(); it != mp.end(); it++)
		{
			cout << it->first << ": " << endl;
			cout << "Count of cities: " << it->second.size() << endl << endl;
			for (auto& elem : it->second)
				cout << elem.GET_city() << endl;
			cout << endl;
		}
	}
	void Save()
	{
		ofstream ofs("File.txt");

		ostream_iterator<CITY> os_it(ofs, "\n");

		for (auto it = mp.begin(); it != mp.end(); it++)
		{
			ofs << it->first << ": " << endl;
			copy(it->second.begin(), it->second.end(), os_it);
		}

		ofs.close();
	}
};


int main()
{
	DATA data;

	int chois;
	while (true)
	{
		cout << endl << "0 - EXIT" << endl << "1 - Add country" << endl << "2 - Add city" << endl;
		cout << "3 - Search city" << endl << "4 - Edit city" << endl << "5 - Delete country" << endl;
		cout << "6 - Delete city" << endl << "7 - Count of cities" << endl << "8 - Print all data" << endl;
		cout << "Enter your chois: ";
		cin >> chois;

		if (chois >= 0 && chois <= 8)
		{
			if (chois == 0)
			{
				cout << endl << endl << "\tEXIT!" << endl;
				break;
			}
			if (chois == 1)
			{
				string country, city;
				cout << "Enter country: ";
				cin >> country;
				cout << endl;
				
				data.ADD_country(country);
				data.Save();
			}
			if (chois == 2)
			{
				string country, city;
				cout << "Enter country: ";
				cin >> country;
				cout << "Enter city: ";
				cin >> city;
				cout << endl;
				
				data.ADD_city(country, city);
				data.Save();
			}
			if (chois == 3)
			{
				string city;
				cout << "Enter city: ";
				cin >> city;
				cout << endl;
				
				data.FIND_city(city);
			}
			if (chois == 4)
			{
				string country, city, new_city;
				cout << "Enter country: ";
				cin >> country;
				cout << "Enter city which you want to rename: ";
				cin >> city;
				cout << "Enter new name of city: ";
				cin >> new_city;
				cout << endl;
				
				data.EDIT_city(country, city, new_city);
				data.Save();
			}
			if (chois == 5)
			{
				string country;
				cout << "Enter country: ";
				cin >> country;
				
				data.DELETE_country(country);
				data.Save();
			}
			if (chois == 6)
			{
				string country, city;
				cout << "Enter country: ";
				cin >> country;
				cout << "Enter city: ";
				cin >> city;
				cout << endl;
				
				data.DELETE_city(country, city);
				data.Save();
			}
			if (chois == 7)
				cout << "Count of cities: " << data.COUNT_of_cities() << endl;

			if (chois == 8)
				data.Print();
		}
		else
			cout << "Something going wrong..." << endl << endl;
	}

	return 0;
}