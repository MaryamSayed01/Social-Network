#pragma once
#include <iostream>
#include<string>
#include<algorithm>
#include<cstdlib>
#include<cmath>
#include<fstream>
#include<exception>
using namespace std;
class User;
class FriendsList;
template <class dataType>
class LinkedList;
template <class dataType>
class Node {
    friend class LinkedList<dataType>;
    //friend class User;
    
public:
    dataType data;
    Node<dataType>* next;
    friend ostream& operator<<(ostream& out, const Node& anotherNode) {
        out << anotherNode.data;
    }
};
template <class dataType>
class LinkedList {
    friend class FriendsList;

public:
    LinkedList() {
        head = tail = new Node<dataType>;
    }
    LinkedList(bool usersList) {
        if (usersList) {
            if (typeid(dataType) == typeid(User)) {
                head = tail = new Node<dataType>;
                string username, name, email;
                fstream usersfile;
                usersfile.open("all-users.txt", ios::in | ios::out | ios::binary);
                while (!usersfile.eof())
                {
                    getline(usersfile, username, ',');
                    getline(usersfile, name, ',');
                    getline(usersfile, email);
                    User user(username, name, email);
                    this->push_back(user);
                }
            }
        }
        
        else {  
        head = tail = new Node<dataType>;
        }
    }
    
    bool isEmpty() {
        return length == 0;
    }
    //add to tail
    void push_back(dataType value) {
        if (this->isEmpty()) {
            head->data = value;
            head->next = NULL;
            tail = head;
        }
        else {
            Node<dataType>* nodeToAdd = new Node<dataType>;
            nodeToAdd->data = value;
            nodeToAdd->next = NULL;
            this->tail->next = nodeToAdd;
            this->tail = nodeToAdd;
        }
        this->length += 1;
    }
    //add to head
    void puch_Front(dataType value)
    {
        if (this->isEmpty()) {
            head->data = value;
            head->next = NULL;
            tail = head;
        }
        else {
            Node* nodeToAdd = new Node;
            nodeToAdd->data = value;
            nodeToAdd->next = this->head;
            head = nodeToAdd;
        }
        this->length += 1;
    }
    void addInPosition(dataType value, int position) {
        if (position > length || position <= 0) {
            cout << "this position not valid\n";
            return;
        }
        else if (position == 0) {
            this->puch_Front(value);
        }
        else if (position == length) {
            this->push_back(value);
        }
        else {
            Node<dataType>* currentNode = this->head;
            for (int pos = 1; pos < position; pos++) {
                currentNode = currentNode->next;

            }
            Node<dataType>* nodeToAdd = new Node<dataType>;
            nodeToAdd->data = value;
            nodeToAdd->next = currentNode->next;
            currentNode->next = nodeToAdd;
            this->length += 1;
        }

    }
    void popHead() {
        if (this->length == 1) {
            delete this->head;
            head = tail = NULL;
            this->length -= 1;
        }
        else if (!this->isEmpty()) {
            Node<dataType>tempNode = new Node<dataType>;
            tempNode = this->head;
            head = head->next;
            delete tempNode;
            this->length -= 1;
        }
        else {
            cout << "Your list is empty!\n";
        }
    }
    void popTail() {
        if (this->length == 1) {
            delete this->head;
            head = tail = NULL;
            this->length -= 1;
        }
        else if (!this->isEmpty()) {
            Node<dataType>currentNode = this->head->next;
            Node<dataType>previousNode = this->head;
            while (currentNode != NULL)
            {
                previousNode = currentNode;
                currentNode = currentNode->next;
            }
            delete currentNode;
            previousNode->next = NULL;
            this->tail = previousNode;
            this->length -= 1;
        }
        else {
            cout << "Your list is empty!\n";
        }
    }
    void popValue(dataType value) {
        if (this->isEmpty()) {
            cout << "Your list is empty!\n";
        }
        else if (this->head->data == value) {
            this->popHead();
        }
        else if (this->tail->data == value) {
            this->popTail();
        }
        else {
            Node<dataType>currentNode = this->head->next;
            Node<dataType>previousNode = this->head;
            while (currentNode != NULL)
            {
                if (currentNode->value == value) {
                    break;
                }
                else {
                    previousNode = currentNode;
                    currentNode = currentNode->next;
                }
            }
            if (currentNode == NULL) {
                cout << "Didn't find match\n";
            }
            else {
                previousNode->next = currentNode->next;
                if (currentNode == tail) {
                    tail = previousNode;

                }
                this->length -= 1;
                delete currentNode;
            }
        }
    }
     /*~LinkedList() {
        while (this->head->next != nullptr) {
            Node<dataType>* temp = head;
            head = head->next;
            delete temp;
        }
        delete head;
    }*/


    //this function created specificly to return the data address in memory for the FriendBST
    dataType* findDataAddress(dataType key) {
        if (head != NULL) {
            Node<dataType>* currentNode = this->head;
            while (currentNode != NULL) {
                if (currentNode->data == key) {
                    //cout << "Found\n";
                   // cout<< &(currentNode->data);
                    //cout << currentNode->data;
                    return &(currentNode->data);
                }
                else {

                    currentNode = currentNode->next;
                }
            }
            if (currentNode == NULL) {
                exit(1);
            }
        }
    }
    void displayList() {
        Node<dataType>* currentNode = this->head;
        while (currentNode != NULL) {
            cout << currentNode->data << endl;
            currentNode = currentNode->next;
        }
    }

    Node<dataType>* head, * tail;
    int length;
private:
};
class User {
    string username, name, email;
    bool loggedIn=false;
public:
    FriendsList* userFriendsList;
    //Default Constructor 
    User() {
        loggedIn = false;
    }
    //loginIn while Initializing the the object
    User(string usernameToLogin) {
        this->username = usernameToLogin;
        string username, name, email;
        fstream check;
        check.open("all-users.txt", ios::in | ios::out | ios::binary | ios::app);
        while (!check.eof())
        {

            getline(check, username, ',');
            getline(check, name, ',');
            getline(check, email,'\n');
            if (username.compare(usernameToLogin) == 0)
            {
                this->username = username;
                this->name = (name);
                this->email = (email);
                this->loggedIn = true;
                break;
            }
        }
        if (!(this->loggedIn)) {
            cout << "\nWrong username!\n";
        }
    }
    //Creat new user
    User(string username, string name, string email) {
        this->username = username;
        this->name = name;
        this->email = email;
    }

    //Setters&&Getters
    void setUsername(string username) { this->username = username; }
    void setName(string name) { this->name = name; }
    void setEmail(string email) { this->email = email; }
    string getUsername() {return this->username; }
    string getName() { return this->name; }
    string getEmail() { return this->email;}



    //Login&&Logout Functions
    bool loggedin() {return this->loggedIn; }

    void userLogin()
    {
        string username, name, email;
        fstream check;
        string usernameInput;
        check.open("all-users.txt", ios::in | ios::out | ios::binary);
        cout << "Enter username: ";
        try
        {
            bool found = false;
            cin >> usernameInput;
            while (!check.eof())
            {
                getline(check, username, ',');
                getline(check, name, ',');
                getline(check, email);

                if (username == usernameInput)
                {
                    found = true;
                    this->setUsername(username);
                    this->setName(name);
                    this->setEmail(email);
                    this->loggedIn = true;
                    cout << "Login success\n" << endl;
                }
            }

            if (!found)
            {
                throw 4;
            }
        }
        catch (int x)
        {
            char chose[5];
            cout << "Login faild, Do you want to try again?\n1-Yes\n2-No,Exit\n";
            cin >> chose;
            if (chose[0] == '1' || chose[0] == 'y' || chose[0] == 'Y' || chose[0] == 'O' || chose[0] == 'o')
            {
                return userLogin();
            }
            else
            {
                exit(1);
            }
        }
    }

    void loginOrExit() {
        int choise;
        cout << "1-Login\n2-Exit\n";
        try {
            cin >> choise;
            if (choise == 1 || choise == 2) {
                if (choise == 1) {
                    this->userLogin();
                }
                else {
                    cout << "Thanks for your visit\n";
                }
            }
            else {
                throw 404;
            }
        }
        catch (int num)
        {
            int choise;
            cout << "Ambigous Input choose 1 or 2, Do you want to try again?\n1-Yes\n2-No,Exit\n";
            cin >> choise;
            
            if (choise==1)
            {
                return loginOrExit();
            }
            else
            {
                cout << "Thanks for your visit\n";
                exit(1);
            }
        }

    }

    void logout() {
        return loginOrExit();
    }

    //Needed Operators
    //Loggedin User function 
    bool operator==(const User& anotherUser) {
        return(this->username == anotherUser.username);
    }
    friend ostream& operator<<(ostream& out, const User& user) {
        out << "\nUsername:" << user.username << "\nUser name:" << user.name << "\nUser email:" << user.email << endl;;
        return out;
    }
};

struct NodeFriend
{
    string username;
    User* refernceToUserInLinkedList;
    NodeFriend* leftFriend, * rightFriend;
    int height;
};
class FriendsList {
    friend class LinkedList<User>;
    friend class User;
public:
    NodeFriend* userRoot;

    FriendsList() {
        this->userRoot= nullptr;
    }
    //Friend List Object that will call this function will be belong to the user parmeter 
    void creatFriendsListForThisUser(User user, LinkedList<User>usersList) {
        //1-first Add To the root the user was passed in the function:
        //create Node friend then insert it to the FriendLsit obj that called the function
        NodeFriend* userroot = NULL;
       // userroot = this->insertNodefriend(userroot, user, usersList);

        //2- Open the file and find the userRoot friends in the file 
        string username1, username2;
        fstream usersRelation;

        usersRelation.open("all-users-relations.txt", ios::in | ios::out | ios::binary);
        //NodeFriend* nodeFriend = NULL;
        while (!usersRelation.eof())
        {
            getline(usersRelation, username1, ',');
            getline(usersRelation, username2, '\n');
            username2.erase(std::prev(username2.end()));

            //cout << "\nUsername2:" << username2 << endl;
            if (username1 == user.getUsername()) {
                // cout << "FoundFriend! In File length of username: " << username2.length() << ", Username:" << username2 << endl;
                User friendUser(username2);
                //cout << "found friend: " << friendUser;
                userroot = this->insertNodefriend(userroot, friendUser, usersList);

            }
            if (username2 == user.getUsername()) {
                //  cout << "FoundFriend! In File length of username: " << username1.length() << ", Username:" << username1 << endl;

                User friendUser(username1);
                userroot = this->insertNodefriend(userroot, friendUser, usersList);
            }
        }
        if (userroot != NULL) {
            this->userRoot = new NodeFriend;
            this->userRoot = userroot;
            //this->userRoot->leftFriend = new NodeFriend;
            this->userRoot->leftFriend = userroot->leftFriend;
            //this->userRoot->rightFriend = new NodeFriend;

            this->userRoot->rightFriend = userroot->rightFriend;
        }
        else {
            cout << "\nNote: you don't have friends!\n";
        }
        
    }
    NodeFriend* insertNodefriend(NodeFriend* root,User user,LinkedList<User>usersList)
    {
        if (root == NULL) {
            NodeFriend* newFriend = new NodeFriend;
            newFriend->username = user.getUsername();
            newFriend->refernceToUserInLinkedList=usersList.findDataAddress(user);
            root = new NodeFriend;
            root = newFriend;
            root->leftFriend = root->rightFriend = NULL;
            root->height = 1;
            return root;
        }
        else {
            char userFirstChar = (user.getUsername())[0],
                rootFirstChar=root->username[0];

            if (int(userFirstChar) < int(rootFirstChar))
                root->leftFriend = insertNodefriend(root->leftFriend, user,usersList);
            else
                root->rightFriend = insertNodefriend(root->rightFriend, user, usersList);
        }
        return root;
    }
    void getPeopleUsermayKnow(User user,LinkedList<User>allUsers) {
        LinkedList<User>peopleUsermayKnow;
        string username, name, email;
        fstream findnonfriends;
        findnonfriends.open("all-users.txt", ios::in | ios::out | ios::binary);
        int countRecommendations = 0;
        while (!findnonfriends.eof())
        {
            getline(findnonfriends, username, ',');
            getline(findnonfriends, name, ',');
            getline(findnonfriends, email);
            if (username == user.getUsername()) {
                continue;
            }
            NodeFriend* findMatch = NULL;
            findMatch = user.userFriendsList->foundMatch(user.userFriendsList->userRoot,username);
            if (findMatch != NULL ) {
                
                continue;
            }
            else {
                if (countRecommendations == 5) {
                    break;
                }
                else {
                     User user(username, name, email);
                     peopleUsermayKnow.push_back(user);
                     countRecommendations += 1;
                }
               
            }
        }
        if (peopleUsermayKnow.isEmpty()) {
            cout << "There is not recmoendation\n";
        }
        else {
             peopleUsermayKnow.displayList();
        }
    }

    NodeFriend* foundMatch(NodeFriend*nodeFriend,string username) {
        if (nodeFriend != NULL) {
            if (username == nodeFriend->username) {
                return nodeFriend;
            }
            else 
            {
                char userFirstChar = username[0], nodeFriendFirstChar = nodeFriend->username[0];
                if (int(userFirstChar) < int(nodeFriendFirstChar)) {
                    return foundMatch(nodeFriend->leftFriend, username);
                }
                else {
                    return foundMatch(nodeFriend->rightFriend, username);
                }
            }
        }
        else {
            return NULL;
        }
        return nodeFriend;
    }
    
    NodeFriend* digToLeaf(NodeFriend* nodeFriend) {
        NodeFriend* current = nodeFriend;
        while (current->leftFriend != NULL) {
            current = current->leftFriend;
        }
        return current;
    }
   
    NodeFriend* removeFriend(NodeFriend* root, string username) {
        if (root == NULL)
        {
            return root;
        }
            // If the key to be deleted is smaller
            // than the root's key, then it lies
            // in left subtree
            char userFirstChar = username[0], nodeFriendFirstChar = root->username[0];

            if (int(userFirstChar) < int(nodeFriendFirstChar)) {
                cout << "found in <\n";
                return removeFriend(root->leftFriend, username);
            }
            else if (int(userFirstChar) > int(nodeFriendFirstChar)) {
                cout << "found in >\n";
                return removeFriend(root->rightFriend, username);
            }
            // if key is same as root's key, then
            // This is the node to be deleted
            else if(root->username==username)
            {
                cout << "found in ==/n";
                // node with only one child or no child
                if ((root->leftFriend == NULL) ||
                    (root->rightFriend == NULL))
                {
                    NodeFriend* temp = root->leftFriend ?
                        root->leftFriend :
                        root->rightFriend;

                    // No child case
                    if (temp == NULL)
                    {
                        cout << "No childes\n";
                        temp = root;
                        root = NULL;
                    }
                    else // One child case
                    {
                        cout << "one chiled: " << temp->username;
                        *root = *temp;
                    }
                        // Copy the contents of
                                       // the non-empty child
                    free(temp);
                }
                else
                {
                    cout << "\nTwo childs\n";
                    NodeFriend* temp = digToLeaf(root->rightFriend);
                    cout << "succecor: " << temp->username;
                    root->username = temp->username;
                    root->refernceToUserInLinkedList = temp->refernceToUserInLinkedList;
                    root->rightFriend = removeFriend(root->rightFriend,temp->username);
                }
            }

            // If the tree had only one node
            // then return
            if (root == NULL) {
                cout << "Only one node\n";
                 return root;
            }
            return root;
       
    }

    //To print User friends
    void inOrder(NodeFriend* userfriends)
    {
        if (userfriends != NULL)
        {
            inOrder(userfriends->leftFriend);
            cout <<"\nfriend:\n"<< *(userfriends->refernceToUserInLinkedList);
            inOrder(userfriends->rightFriend);
        }
    }
    void printUserRoot() {
        cout << this->userRoot->username << endl;
    }
};
/* NodeFriend* removeFriend(NodeFriend* root, NodeFriend* searchFriend) {
        if (root == NULL)
        {
            return root;
        }
        char userFirstChar = searchFriend->username[0], nodeFriendFirstChar = root->username[0];
        if (int(userFirstChar) < int(nodeFriendFirstChar)) {
            //cout << "found in <\n";
            return removeFriend(root->leftFriend, searchFriend);
        }
        else if (int(userFirstChar) > int(nodeFriendFirstChar)) {
           // cout << "found in >\n";
            return removeFriend(root->rightFriend, searchFriend);
        }
        else if (root->username == searchFriend->username)
        {
            //cout << "found in ==/n";
            // node with only one child or no child
            if ((root->leftFriend == NULL) ||
                (root->rightFriend == NULL))
            {
                NodeFriend* temp = NULL;
                temp= root->leftFriend ? root->leftFriend : root->rightFriend;

                if (temp == NULL)
                {
                    temp = root;
                    root = NULL;
                }
                else
                {
                    *root = *temp;
                }
                free(temp);
            }
            else
            {
                NodeFriend* temp = digToLeaf(root->rightFriend);

                root->username = temp->username;
                root->refernceToUserInLinkedList = temp->refernceToUserInLinkedList;
                root->rightFriend = removeFriend(root->rightFriend, temp->username);
            }
        }

    }*/