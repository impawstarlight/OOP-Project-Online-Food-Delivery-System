// MUST COMPILE WITH C++17
// Fix for CodeBlocks C++17 Bug
#define _GLIBCXX_FILESYSTEM
#include <bits/stdc++.h>
using namespace std;

#include "helper.cpp"
#include "user.cpp"


void show_main_menu() {
	Menu menu("Main Menu", {
		"Login",
		"Register",
		"Exit"
	}, 1);

	while (true) {
		menu.display();
		switch (menu.get_choice()) {
			case 1: User::login(); break;
			case 2: User::signup(); break;
			case 3: return;
		}
	}
}

void load_data() {
	User::load_data();
}


int main() {
	load_data();
	show_main_menu();


	return 0;
}
