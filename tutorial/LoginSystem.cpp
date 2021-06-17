#include <iostream>
#include <fstream> //contains both ofstream & ifstream operations
#include <string>
#include <cstdio>
using namespace std;
class UserLogin{
    private:
    string username;
    string password;
    string userAttempted;
    string passwordAttempted;
    bool access = false;
    public:
    UserLogin(){
        // constructor for creating objects
    }
    void check_file(){
        string uline,pline;
        fstream file;
        file.open("user.txt",ios::in);
        if(file.is_open()){
            getline(file,uline);
            username=uline;
        }
        file.close();
        file.open("password.txt",ios::in);
        if(file.is_open()){
            getline(file,pline);
            password=pline;
        }
        file.close();
    }
    // displays file content
    void show_file()
    {

        string line;
        fstream showfile;
        showfile.open("target.txt",ios::in);
        if(!showfile)
        {
                cout<<"\nError in opening file..!!\n";

                exit(0);
        }

        cout<<"\n";
        while(getline(showfile,line))
    {
        cout<<line<<"\n";
    }
        cout<<"\n";
        showfile.close();
    }
    void login(){
        cout<<" Please enter the following details to get access to the files :\n";
        cout<<"username : \n";
        cin>>userAttempted;
        // before moving ahead with password lets check if the email exists in the database
        if(userAttempted == username)
        {
            // move ahead , does nothing for now
            while(!access)
            {
            cout<<"password : \n";
            cin>>passwordAttempted;
                if(passwordAttempted == password)
                {
                    char file_name[20];
                    cout<<"\nBingo ! You now have access to the files\n";
                    cout<<"Enter the file name you want to look at : \n";
                    cin>>file_name;
                    //return the file content
                    show_file();
                    access=true;
                    // does smtg like opens a file
                }
                else
                {
                   cout<<"\nOops! Incorrect password\n"; 
                }
            }
        }
        else{
            cout<<"\nOops! Invalid user id\n"<<"Your id is not registered in our Database"; 
            login();
        } 
    }
};
int main(){
    UserLogin app;
    app.check_file();
    app.login();
    return 0;  
}