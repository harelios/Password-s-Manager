#include <iostream>
#include <string>
#include <fstream>

#include "PasswordManager.h"

using namespace std;



void AddPassword(string& password, string& username)
{
	
	cout << "Enter an username : " << endl;
	cin >> username;
	cout << "Enter a Password you want to add : " << endl;
	cin >> password;
	ofstream PasswordFile("Password.txt", ios::app); //Don't erase the file each time he is open
	if (PasswordFile)
	{
		PasswordFile << username << ":" << password << endl;
		PasswordFile.close();
		cout << "Username + Password Saved !" << endl;
	}
	else
	{
		cout << "Error opening the file" << endl;
	}
}

void SearchPassword(string& username)
{
	cout << "Enter an username you want to search : " << endl;
	cin >> username;
	cout << "Retrieving..." << endl;
	ifstream PasswordFile2("Password.txt");
	if (!PasswordFile2)
	{
		cout << "Error opening the file" << endl;
	}
	string ligne;
	bool found = false;

	while (getline(PasswordFile2, ligne))
	{
		if (ligne == username)
		{
			found = true;
			break;
		}
	}

	PasswordFile2.close();
	size_t pos = ligne.find(":");
	if (found)
	{
		string password = ligne.substr(pos + 1);
		cout << "Username Found !" << endl;
		cout << "Password : " << password << endl;
	}
	else
	{
		cout << "No username found" << endl;

	}


}


void DisplayMenu()
{

	while (true)
	{
		cout << "---------------------------Password's Manager--------------------------------" << endl;
		int choice;
		string password;
		string username;
		cout << "1) Add a Password \n 2) retrieve a password \n 3) Quit \n" << endl;
		cin >> choice;

		if (choice == 1)
		{
			AddPassword(password, username);
		}
		else if (choice == 2)
		{
			SearchPassword(password);
		}

		else if (choice == 3)
		{
			break;
		}
		else if (cin.fail())
		{
			cout << "Enter a number !" << endl;
			cin.clear();
			cin.ignore();
		}
		else
		{
			cout << "Please enter a valid choice." << endl;

		}

	}

}


