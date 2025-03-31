#pragma once
#ifndef PASSWORD_MANAGER_H
#define PASSWORD_MANAGER_H

#include <string>


void AddPassword(std::string& password, std::string& username); //Function to add a password.

void SearchPassword(std::string& username); //Function to search a password.

void DisplayMenu(); //Function to display the menu of the tool.

void ShowAllPassword(); //Function to show all the account saved (Need the Password's Admin to run it)

void DeleteAccount(); //Function to delete an account (username + password) in the file.

std::string encrypt(const std::string& password);

std::string decrypt(const std::string& encrypted);


#endif 