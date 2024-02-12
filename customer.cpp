
class Customer : public User {
private:
	string full_name;

protected:

	void input() override {
		User::input();
		cout << "Enter full name: ";
		getline(cin >> ws, full_name);
	}

	void write(ofstream& fout) override {
		fout << "Customer" << endl;
		User::write(fout);
		fout << full_name << endl;
	}

	void read(ifstream& fin) override {
		User::read(fin);
		getline(fin >> ws, full_name);
	}

	void show_actions_menu() override {
		Menu menu("Welcome back " + full_name + "!", {
			"Show restaurants",
			"Order history",
			"Log out"
		}, 1);

		while (true) {
			menu.display();
			switch (menu.get_choice()) {
				case 1: Restaurant::show_restaurants(); break;
				case 2: break;
				case 3: return;
			}
		}
	}

public:

	Customer() : full_name("") {}
};
