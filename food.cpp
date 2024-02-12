
class FoodItem {
private:
	string name;
	string category;
	string serving_amount;
	double price;

public:
	friend class FoodMenu;

	void input() {
		cout << "Food name: ";
		getline(cin >> ws, name);

		cout << "Category:" << endl;
		category = choice_based_input({
			"Fast food",
			"Appetizer",
			"Lunch/Dinner",
			"Dessert",
			"Drink",
			"Other"
		});

		cout << "Serving amount: ";
		getline(cin >> ws, serving_amount);

		cout << "Price: ";
		cin >> price;
	}

//	void edit_price() {
//		cout << "New price: ";
//		cin >> price;
//	}
//
//	bool show_actions_menu() {
//		Menu menu("", {
//			"Edit price",
//			"Delete this item"
//		}, 1);
//
//		menu.display();
//		switch (menu.get_choice()) {
//			case 1: edit_price(); break;
//			case 2: return true;
//		}
//
//		return false;
//	}

	string to_string() {
		ostringstream sout;
		sout << left << setw(30) << name << setw(20) << right
		     << serving_amount << setw(10) << price << " Taka";
		return sout.str();
	}

	void write(ofstream& fout) {
		fout << name << endl
		     << serving_amount << endl
		     << price << endl;
	}

	void read(ifstream& fin, string category) {
		this->category = category;
		getline(fin >> ws, name);
		getline(fin >> ws, serving_amount);
		fin >> price;
	}

	friend bool operator<(const FoodItem& a, const FoodItem& b);
};

bool operator<(const FoodItem& a, const FoodItem& b) {
	return a.name < b.name;
}


class FoodMenu {
private:
	map<string, set<FoodItem>> foods;

	void show_actions_menu() {
		Menu menu("Manage Food Menu", {
			"Show foods",
			"Add food",
			"Remove food",
			"Go back"
		}, 1);

		while (true) {
			menu.display();
			switch (menu.get_choice()) {
				case 1: show_foods(); break;
				case 2: add_food(); break;
				case 3: break;
				case 4: return;
			}
		}
	}

	void add_food() {
		FoodItem food;
		food.input();
		foods[food.category].insert(food);
		User::save_data();
	}

	void write(ofstream& fout) {
		fout << foods.size() << endl;

		for (auto& [category, food_set] : foods) {
            fout << category << endl
                 << food_set.size() << endl;
			for (FoodItem food : food_set)
				food.write(fout);
        }
	}

	void read(ifstream& fin) {
		int n_categories;
		fin >> n_categories;

		while (n_categories--) {
			string category;
			int n_items;
			getline(fin >> ws, category);
			fin >> n_items;

			while (n_items--) {
				FoodItem food;
				food.read(fin, category);
				foods[category].insert(food);
			}
		}
	}



public:
	friend class Restaurant;


	void show_foods() {
		cout << "   #  " << setw(30) << left << "Name" << setw(20) << right
		     << "Serving amount" << setw(15) << right << "Price" << endl;

		for (auto& [category, food_set] : foods) {
			vector<string> options;
			for (FoodItem food : food_set)
				options.push_back(food.to_string());

			Menu menu(category, options, 1);
			menu.display();
			//menu.get_choice();
		}
	}

};

