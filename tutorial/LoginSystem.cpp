#include <iostream>
#include <fstream> //contains both ofstream & ifstream operations
#include <string>
using namespace std;
class UserLogin{
    private:
    string username="khushijain@gmail.com";
    string password="khushi";
    string userAttempted;
    string passwordAttempted;
    public:
    UserLogin(){
        // constructor for creating objects
    }
    void login(){
        cout<<" Please enter the following details to get access to the files :\n";
        cout<<"username : \n";
        cin>>userAttempted;
    // before moving ahead with password lets check if the email exists in the database
        if(userAttempted == username){
                // move ahead , does nothing for now
            cout<<"password : \n";
            cin>>passwordAttempted;
            if(passwordAttempted == password){
                cout<<"\nBingo ! You now have access to the files\n";
                // does smtg like opens a file
            }
            else{
               cout<<"\nOops! Incorrect password\n"; 
            }
        }
        else{
            cout<<"\nOops! Invalid user id\n"; 
            login();
        }
        
        
    }
};
int main(){
    UserLogin app;
    app.login();
    return 0; 
}