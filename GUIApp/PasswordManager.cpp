#include <iostream>
#include <string>
#include <fstream>
#include <cstdio>

#include "PasswordManager.h"

using namespace std;

string Encrypt(const string& password)
{
	string encrypted = password;
	char key = 42;
	for (char& c : encrypted)
	{
		c ^= key; //Use of the Xor operator to encrypt the password
	}
	return encrypted;
}

string Decrypt(const string& encrypted)
{
	return Encrypt(encrypted);

}


void AddPassword(const string &password, const string &username)
{
	string password_encrypted = Encrypt(password);
	ofstream PasswordFile("Password.txt", ios::app); //Don't erase the file each time he is open
	if (PasswordFile)
	{
		PasswordFile << username << ":" << password_encrypted << endl;
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
		size_t pos = ligne.find(":");
		string username_find = ligne.substr(0, pos);
		if (username_find == username)
		{
			found = true;
			break;
		}
	}

	PasswordFile2.close();

	if (found)
	{
		string password = ligne.substr(ligne.find(":") + 1);
		cout << "Username Found !" << endl;
		cout << "Password : " << password << endl;
	}
	else
	{
		cout << "No username found" << endl;
	}
}

void ShowAllPassword()
{
	string ligne;
	ifstream PasswordFile2("Password.txt");
	if (!PasswordFile2)
	{
		cout << "Error opening the file. \n" << endl;
	}
	bool foundsomething = false;
	while (getline(PasswordFile2, ligne))
	{
		if (ligne.empty()) continue;
		size_t pos = ligne.find(":");
		string username = ligne.substr(0, pos);
		string password = ligne.substr(ligne.find(":") + 1);
		string decrypted_password = Decrypt(password);
		cout << username << ":" << decrypted_password << endl;
		foundsomething = true;
	}

	if (!foundsomething)
	{
		cout << "No account find" << endl;

	}
}


bool DeleteAccount(const std::string& account)
{
	string ligne;
	bool found = false;
	cout << "Which account do you want to delete ? (Enter the username of the account) : \n" << endl;
	ifstream AccountFile_read("Password.txt");
	ofstream AccountFile_write("temp.txt");
	while (getline(AccountFile_read, ligne))
	{
		size_t pos = ligne.find(":");
		string username = ligne.substr(0, pos);
		string password = ligne.substr(ligne.find(":") + 1);
        if (account != username)
		{
			AccountFile_write << username << ":" << password << endl;
		}
		else
		{
			found = true;
		}
	}
	AccountFile_read.close();
	AccountFile_write.close();
		if (remove("Password.txt") != 0)
		{
			cout << "Error deleting the file" << endl;
		}
		else if (rename("temp.txt", "Password.txt") != 0)
		{
			cout << "Error renaming the file" << endl;
		}
		else
		{
			if (found)
			{	
                cout << "Account deleted successfully" << endl;
                return true;
			}
			else
			{
                    cout << "Account not found." << endl;
                return false;
			}
		}
} 

bool ModifyPassword(const std::string& account,const std::string& new_password)
{
	string ligne;
	ifstream File_read("Password.txt");
	ofstream File_write("temp.txt");
	bool found = false;
	while (getline(File_read, ligne))
	{
		size_t pos = ligne.find(":");
		string username = ligne.substr(0, pos);
		string password = ligne.substr(ligne.find(":") + 1);
		

		if (account == username)
		{
			File_write << username << ":" << Encrypt(new_password) << endl;
			found = true;
		}
		else
		{
			File_write << ligne << endl;
		}
	}
	File_read.close();
	File_write.close();
	if (found)
	{
		if (remove("Password.txt") != 0)
		{
			cout << "Error removing the file." << endl;
		}
		else if (rename("temp.txt", "Password.txt") != 0)
		{
			cout << "Error renaming the file." << endl;
		}	cout << "Password modified !" << endl;
        return true;

	}
	else
	{
		cout << "Account not found" << endl;
        return false;
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
        string account;
		cout << "1) Add a Password \n 2) retrieve a password \n 3) show all saved account \n 4) Delete a password \n 5) Modify a password \n 6) Quit \n" << endl;
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

			string adminPassword = "Admin1234"; //You can change the password to a custom one.
			string passwordInput;
			cout << "Enter the password to get the list of all the account" << endl;
			cin >> passwordInput;
			if (passwordInput == adminPassword)
			{
				ShowAllPassword();
			}
			else
			{
				cout << "Wrong password, command denied" << endl;
				DisplayMenu();

			}

		}

		else if (choice == 4)
		{
            DeleteAccount(account);
		}
		else if (choice == 5)
		{
            ModifyPassword(username,password);
		}

		else if (choice == 6)
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
