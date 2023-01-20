#include <iostream>
#include<string>
#include<algorithm>
#include<cstdlib>
#include<cmath>
#include<fstream>
#include<exception>
#include<iterator>
#include "LinkedList.h"
int displayLoggedInUserList();
void homePage(LinkedList<User>allUsers);
using namespace std;
int main()
{
	LinkedList<User>allUsers(true);
	homePage(allUsers);
}
int displayLoggedInUserList() {
	int choise;
	cout << "\n1-List all friends\n"
		"2-Search by username\n"
		"3- Add friend\n"
		"4- Remove friend\n"
		"5- People you may know\n"
		"6-logout\n";
	cin >> choise;
	while (choise >= 1 && choise <= 6)
	{
		return choise;
	}
	char c[5];
	cout << "Your input is ambigous, Do you want to try again? just enter the number of any choise you want\n" << "2-Yes    2-No,exit\n";
	cin >> c;
	if (c[0] == '1' || c[0] == 'o' || c[0] == 'O' || c[0] == 'Y' || c[0] == 'y')
	{
		return displayLoggedInUserList();
	}
	else
	{
		exit(1);
	}

}
void homePage(LinkedList<User>allUsers) {
	User user;
	//FriendsList userFriendsList();
	FriendsList friendsList;
	user.loginOrExit();
	if (user.loggedin()) {
		//Prepare the user Friend List 
		friendsList.creatFriendsListForThisUser(user, allUsers);
		user.userFriendsList = &friendsList;
		int userChoice;
		//Display the logged in user List to choose operation
		while (true)
		{
			 userChoice = displayLoggedInUserList();
			//1-List all friends✔✔
			if (userChoice == 1)
			{
				user.userFriendsList->inOrder(user.userFriendsList->userRoot);
			}
			
			//2- Search by username✔✔
			//it dispaly the info of username user (Only if) they are friends✔✔
			else if (userChoice == 2) {
				string usernameToSearch;
				cout << "enter the user name you're looking for:";
				cin >> usernameToSearch;
				NodeFriend* searchFriend = NULL;
				searchFriend = user.userFriendsList->foundMatch(user.userFriendsList->userRoot, usernameToSearch);
				if (searchFriend != NULL) {
					cout << "You and this account are Friends!\n" << *(searchFriend->refernceToUserInLinkedList) << endl;
				}
			}

			//3-Add friend\n"✔✔
			else if (userChoice == 3) {
				string usernameToAddToFriendList;
				cout << "enter the username  you want to add to your friendList: ";
				cin >> usernameToAddToFriendList;

				//First make sure that the username is valid
				User userToFind(usernameToAddToFriendList);
				Node<User>* currentNode = allUsers.head;
				while (currentNode != NULL) {
					if (currentNode->data == userToFind) {
						//So the username is valid in the system 
						//Make sure first if they are friends
						NodeFriend* findMatch=NULL;
						findMatch = user.userFriendsList->foundMatch(user.userFriendsList->userRoot, usernameToAddToFriendList);
						if (findMatch != NULL) {
							cout << "your're already friends!\n";
							break;
						}
						NodeFriend* searchFriend = NULL;
						searchFriend = user.userFriendsList->insertNodefriend(user.userFriendsList->userRoot, userToFind, allUsers);
						cout << "\nDone\n";
						string newRelation = userToFind.getUsername() + "," + user.getUsername();

						//Update user file relation
						fstream usersRelation;
						usersRelation.open("all-users-relations.txt", ios::app);
						usersRelation << newRelation << endl;
						usersRelation.close();
						break;
					}
					else {
						currentNode = currentNode->next;
					}
				}
				if (currentNode == NULL) {
					cout << "\nInvalid username!\n";
				}
			}

			//4- Remove friend❌❌
			else if (userChoice == 4) {
				string usernametoRemove;
				cout << "Enter the username friend you want to remove: ";
				cin >> usernametoRemove;

				NodeFriend* searchFriend = NULL;
				searchFriend = user.userFriendsList->foundMatch(user.userFriendsList->userRoot, usernametoRemove);
				//user.userFriendsList->userRoot = user.userFriendsList->removeFriend(user.userFriendsList->userRoot, searchFriend);
				if (searchFriend == NULL) {
					cout << "you're already not friends\n";

				}
				else {
					searchFriend == user.userFriendsList->removeFriend(user.userFriendsList->userRoot, searchFriend);
					//user.userFriendsList->userRoot = searchFriend;
				}

			}
			//5-People you may know✔✔
			else if (userChoice == 5) {
			user.userFriendsList->getPeopleUsermayKnow(user, allUsers);
				string* userFriendsUsername;
				Node<User>* notUserFriends;
			}

			//6-logout✔✔
			else if (userChoice == 6) {
			break;
			}
		}
		if (userChoice == 6) {
			return homePage(allUsers);
		}
	}
}