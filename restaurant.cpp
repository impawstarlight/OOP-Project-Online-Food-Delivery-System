#include "food.cpp"

class Restaurant : public User {
private:
	string restaurant_name;
	string location;
	FoodMenu food_menu;

	static vector<Restaurant*> restaurants;

protected:

	void input() override {
	    restaurants.push_back(this);
		User::input();

		cout << "Restaurant name: ";
		getline(cin >> ws, restaurant_name);

		cout << "Location:" << endl;
		location = choice_based_input({
			"Savar",
			"Nabinagar",
			"Hemayetpur"
		});
	}

	void write(ofstream& fout) override {
		fout << "Restaurant" << endl;
		User::write(fout);
		fout << restaurant_name << endl << location << endl;
		food_menu.write(fout);
	}

	void read(ifstream& fin) override {
        restaurants.push_back(this);
		User::read(fin);
		getline(fin >> ws, restaurant_name);
		getline(fin >> ws, location);
		food_menu.read(fin);
	}

	void show_actions_menu() override {
		Menu menu("Welcome back " + restaurant_name + "!", {
			"Manage food menu",
			"Create offer",
			"Log out"
		}, 1);

		while (true) {
			menu.display();
			switch (menu.get_choice()) {
				case 1: food_menu.show_actions_menu(); break;
				case 2: create_offer(); break;
				case 3: return;
			}
		}
	}

	void create_offer() {
		Menu menu("Type of offer", {
			"Discount offer",
			"Bundle offer",
			"Free offer"
		}, 1);

		menu.display();
		menu.get_choice();
		cout << "Demo only!" << endl;
	}

public:

	Restaurant() : restaurant_name(""), location("") {}

	string to_string() {
		ostringstream sout;
		sout << left << setw(30) << restaurant_name << setw(20) << right
		     << location;
		return sout.str();

	}

	static void show_restaurants() {
	    vector<string> options;
	    for (auto& restaurant : restaurants)
            options.push_back(restaurant->to_string());

	    options.push_back("Return");
	    Menu menu("Restaurants", options, 1);

        while (true) {
            menu.display();
            int choice = menu.get_choice();
            if (choice > restaurants.size())
                break;
            else {
                Restaurant* restaurant = restaurants[choice - 1];
                cout << endl << "Showing food menu of " << restaurant->restaurant_name << endl << endl;
                restaurant->food_menu.show_foods();
            }
        }

	}
};

vector<Restaurant*> Restaurant::restaurants;

