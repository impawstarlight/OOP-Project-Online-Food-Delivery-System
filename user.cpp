
class User {
private:
	string username;
	size_t password_hash;

	static const string datafile;

protected:

	virtual void input() {
		cout << "Enter username: ";
		cin >> username;

		while (users[username]) {
			cout << "This username is already taken!"
			     << endl << "Enter another username: ";
			cin >> username;
		}

		users[username] = this;

		cout << "Enter password: ";
		string password;
		cin >> password;
		password_hash = hash<string>{}(password);
	}

	virtual void write(ofstream& fout) {
		fout << username << endl
		     << password_hash << endl;
	}

	virtual void read(ifstream& fin) {
		fin >> username >> password_hash;
		users[username] = this;
	}

	bool match_password(string password) {
		return (password_hash == hash<string>{}(password));
	}

public:
	static map<string, User*> users;
	static User* current_user;


	User() : username(""), password_hash(0) {}
	virtual ~User() {}

	virtual void show_actions_menu() = 0;

	string get_username() {
		return username;
	}

	static void login() {
		string username, password;
		cout << endl << "Enter username: ";
		cin >> username;
		cout << "Enter password: ";
		cin >> password;
		cout << endl;

		current_user = users[username];

		if (current_user == nullptr) {
			cout << "Invalid username!" << endl;
			users.erase(username);
		}
		else if (current_user->match_password(password)) {
			cout << "Logged in successfully!" << endl;
			current_user->show_actions_menu();
		}
		else {
			cout << "Invalid password!" << endl;
			current_user = nullptr;
		}
	}

	static void signup();
	static void save_data();
	static void load_data();

};

map<string, User*> User::users;
User* User::current_user = nullptr;
const string User::datafile = "users.dat";


#include "restaurant.cpp"
#include "customer.cpp"


void User::signup() {
	User* user = nullptr;
	Menu menu("Register New Account", {
		"Customer Account",
		"Restaurant Account"
	}, 1);

	menu.display();
	switch (menu.get_choice()) {
		case 1: user = new Customer; break;
		case 2: user = new Restaurant; break;
	}

	user->input();
	save_data();
	current_user = user;

	cout << "Registered successfully!" << endl;
	current_user->show_actions_menu();

}

void User::save_data() {
	ofstream fout(datafile, ios::trunc);

	for (auto& [username, user] : users) {
		user->write(fout);
		fout << endl;
	}

	fout.close();
}

void User::load_data() {
	ifstream fin(datafile);

	while (fin) {
		string type;
		fin >> type;

		User* u = nullptr;
		if (type == "Customer")
			u = new Customer();
		else if (type == "Restaurant")
			u = new Restaurant();
		else if (type.size())
			cout << "Invalid user type \"" << type
			     << "\" in " << datafile << endl;

		if (u)
			u->read(fin);
	}

	fin.close();
}


