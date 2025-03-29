#include <iostream>
#include <string>
#include <fstream>

#include "PasswordManager.h"

using namespace std;


int main()
{	
	string owner_password = "Admin100"; //Password of the owner to prevent anybody who are not allowed to access the menu (you can personalize it).
	string user_input;
	cout << "Enter the password to access the menu :" << endl;
	cin >> user_input;
	
	if (user_input == owner_password)
	{      
		cout << "Access allowed." << endl;
		DisplayMenu();
	}
	else
	{
		cout << "Access denied" << endl;
	}

}