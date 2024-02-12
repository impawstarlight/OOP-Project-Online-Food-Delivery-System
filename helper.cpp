
template <typename T>
void show_list(vector<string> items, T first_index, string delimiter = ". ") {
	for (const auto& item : items)
		cout << setw(4) << right << first_index++ << delimiter
		     << item << endl;
}


void invalid() {
	cout << "Invalid input!" << endl;
}


template<class T>
class Menu {
private:
	string title;
	vector<string> options;
	T first_index;
	string delimiter;

public:

	Menu(string tl, vector<string> op, T fi, string dl = ". ") :
		title(tl), options(op),
		first_index(fi), delimiter(dl) {}

	void display() {
		if (title.size())
			cout << endl << "----- " << title
				 << " -----" << endl << endl;

		show_list(options, first_index, delimiter);
	}

	T get_choice() {
		T choice;
		cout << endl << "Select an option: ";
		cin >> choice;

		const T last_index = first_index + options.size() - 1;

		while (choice < first_index || choice > last_index) {
			cout << endl << "Invalid choice!" << endl
			     << "Please select a valid option: ";
			cin >> choice;
		}

		return choice;
	}

};


string choice_based_input(vector<string> options) {
	Menu menu("", options, 1);
	menu.display();
	return options[menu.get_choice() - 1];
}

