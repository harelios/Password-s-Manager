#pragma once
#ifndef PASSWORD_MANAGER_H
#define PASSWORD_MANAGER_H

#include <string>


void AddPassword(const std::string& password,const std::string& username); //Function to add a password.

void SearchPassword(std::string& username); //Function to search a password.

void DisplayMenu(); //Function to display the menu of the tool.

void ShowAllPassword(); //Function to show all the account saved. (Need the Password's Admin to run it)

bool DeleteAccount(const std::string& account); //Function to delete an account (username + password) in the file.

std::string Encrypt(const std::string& password); //Function to encrypt the password.

std::string Decrypt(const std::string& encrypted); //Function to decrypt the password.

bool ModifyPassword(const std::string& username,const std::string& new_password);
#endif 
