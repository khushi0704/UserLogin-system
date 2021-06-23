#include <iostream>
#include <fstream> //contains both ofstream & ifstream operations
#include <string>
#include <cstdio>
#include <vector>
using namespace std;

//Use constants for file names for easy modification later on
const string USER_FILE = "user.txt";
const string PASS_FILE = "password.txt";
const string TARGET_FILE = "target.txt";

class Encryption {
	public:
		Encryption() {};
		~Encryption() {};

		// can be replaced with any encryption algorithm 
		int encrypt(const int ch) {
			return (ch << 4) + 10000;
		}

		int decrypt(const int encryptedChar) {
			return ((encryptedChar - 10000) >> 4);
		}
};

class UserLogin{
    private:
		vector<string> usernames; //list of usernames
		vector<string> passwords; //list of passwords
		string userAttempted;
		string passwordAttempted;
		bool access;
		Encryption encryption;

		int getLastUserID(string file) {
			ifstream fin;

			fin.open(file, ifstream::in);

			if (fin.peek() == EOF) {    // no user available now
				return 0;
			}

			fin.seekg(0, ios_base::end);
			string line = "";

			for (int i = -1; line[0] != '#'; --i) {
				fin.seekg(i, ios_base::end);
				fin >> line;
			}

			fin.close();
			line.erase(0, 4);

			return stoi(line);
		}

    public:
		
		//Default Constructor
		UserLogin(){
			this->access = false;
		}

        //Deconstructor
        ~UserLogin(){
        }

		//Check the file for data and read it
		void check_file(){
			string username,password;
			fstream file;

			file.open(USER_FILE.c_str(),ios::in);

			if(file.is_open()){
				//While not at the end of the file, read the data
				while(!file.eof()){
					getline(file,username);
					this->usernames.push_back(username);
				}
			}

			file.close();

			file.open(PASS_FILE.c_str(),ios::in);

			if(file.is_open()){
				//While not at the end of the file, read the data
				while(!file.eof()){
					getline(file,password);
					this->passwords.push_back(password);
				}
			}

			file.close();
		}

		//Display the contents of the file
		void show_file(const string& FILE) const
		{
			string line;
			fstream showfile;

			showfile.open(FILE.c_str(),ios::in);

			if(!showfile.is_open())
			{
					cout<<"\nError in opening file..!!\n";

					exit(0);
			}

			cout << "\n";

			while(!showfile.eof()){
				getline(showfile,line);
				cout << line << "\n";
			}

			cout << "\n";

			showfile.close();
		}

		void saveFile(string text, string file, int id) {
			ofstream fout;

			fout.open(file, ofstream::app);
			fout.seekp(0, ios::end);

        	if (fout.tellp() != 0) {
				fout << endl;
			}
    

			for (const char ch : text) {
				fout << this->encryption.encrypt(ch);
				fout << endl;
			}

			fout << "#ID:" << id;

			fout.close();
		}

		int authenticateUsername(string attempt, string file) {
			ifstream fin;

			fin.open(file, ifstream::in);

			string line = "";
			string username = "";
			int encryptedChar = 0;

			while (fin.peek() != EOF) {
				fin >> line;

				if (line.find("#ID:") != string::npos) {
					if (attempt == username) {
						fin.close();
						
						line.erase(0, 4);
						
						return stoi(line);      // return id

					} else {
						username.clear();
					}

				} else {
					char decrypteChar = this->encryption.decrypt(stoi(line));
					username.push_back(decrypteChar);
				}

				line.clear();
			}

			fin.close();
			return 0;
		}

		bool authenticatePassword(string attempt, string file, int id) {
			ifstream fin;

			fin.open(file, ifstream::in);

			string line = "";
			string password = "";

			while (fin.peek() != EOF) {
				fin >> line;

				if (line.find("#ID:" + to_string(id)) != string::npos) {
					if (attempt == password) {
						fin.close();
						
						return true;      // return userID

					} else {
						return false;
					}

				} else {
					if (line.find("#ID:") != string::npos) {
						password.clear();

					} else {
						char decrypteChar = this->encryption.decrypt(stoi(line));
						password.push_back(decrypteChar);
					}		
				}

				line.clear();
			}
		}

		void registerUser(string username, string password) {
			if (this->authenticateUsername(username, USER_FILE)) {   // duplicated username
				cout << "This username is used." << endl;
				return;
			}

			int id = this->getLastUserID(USER_FILE) + 1;

			this->saveFile(username, USER_FILE, id);
			this->saveFile(password, PASS_FILE, id);
		}

		//Allow the user to login by asking for username and password
		void login(){

			cout << "Please enter the following details to get access to the files :\n";

			cout<<"Username : ";
			getline(cin, this->userAttempted);

			// before moving ahead with password lets check if the email exists in the database
			//If the user is found in the database, proceed
			int id = this->authenticateUsername(this->userAttempted, USER_FILE);

			if(id != 0)
			{
				int user_attempts=5;

				// move ahead , does nothing for now
				while(user_attempts != 0)
				{
					cout<<"Password : ";
					getline(cin, this->passwordAttempted);

					if(this->authenticatePassword(this->passwordAttempted, PASS_FILE, id))
					{
						string file_name;

						cout<<"\nBingo ! You now have access to the files\n";

						cout<<"\nEnter the file name you want to look at: ";
						getline(cin, file_name);

						//return the file content
						this->show_file(file_name);
						user_attempts = 0;
					   // access=true;
						// does smtg like opens a file
					}
					else
					{
					   cout<<"\nOops! Incorrect password\n";
						--user_attempts;
						if(user_attempts == 0){
							cout << "Sorry you've reached the maximum limit for attempting password!" << endl;
							break;
						}
					}
				}
			}

			else{
				cout << "\nOops! Invalid user id\n\n"
					 <<"Your id is not registered in our Database\n\n";
				this->login();
			}
		}

		bool search(const string& KEY, const vector<string> LIST) const{
			unsigned int index = 0;
			bool found = false;

			while(index < LIST.size() && !found){
				if(KEY == LIST[index]){
					found = true;
					return found;
				}
				else{
					++index;
				}
			}

			//If it was not found, return false
			return found;
		}
};

int main(){
    UserLogin app;

    app.check_file();

	// app.registerUser("khushi.jain0704@gmail.com", "glowy@3");

    app.login();
	
    string freezing_terminal;

    cout<<"Enter any key to exit: " << endl;

    getline(cin, freezing_terminal);

    return 0;
}
