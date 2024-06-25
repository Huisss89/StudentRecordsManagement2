#include	<iostream>
#include	<fstream>
#include	<cstdlib>
#include	<cstdio>
#include	<ctime>
#include	<string>
#include	<windows.h> //For decoration purpose
#include	"BST.h"
#include    "Student.h"

using namespace std;

bool readFile(const char *, BST *);
bool redundant(int, BTNode*);

int menu();

int main() {
	system("Color 0B");//Change background and font color

	menu();
	
	system("pause");
	return 0;
}

//a) Read Student Info from file
bool readFile(const char* filename, BST* t1) {
	Student stuInfo;
	int count = 0; //number of student stored
	int i = 1;
	char check[30];
	char name[30];
	char address[100];
	ifstream infile(filename);
	if (!infile) {
		cout << "Unable to open " << filename << " file!" << endl;
		return false;
	}

	else {
		while (!infile.eof()) {
			infile >> check;
			if (strcmp(check, "=") == 0 && i == 1) {
				infile >> stuInfo.id;
				i++;
			}
			else if (strcmp(check, "=") == 0 && i == 2) {
				infile >> stuInfo.name;
				infile.getline(name, 30);
				strcat_s(stuInfo.name, name);
				i++;
			}
			else if (strcmp(check, "=") == 0 && i == 3) {
				infile >> stuInfo.address;
				infile.getline(address, 100);
				strcat_s(stuInfo.address, address);
				i++;
			}
			else if (strcmp(check, "=") == 0 && i == 4) {
				infile >> stuInfo.DOB;
				i++;
			}
			else if (strcmp(check, "=") == 0 && i == 5) {
				infile >> stuInfo.phone_no;
				i++;
			}
			else if (strcmp(check, "=") == 0 && i == 6) {
				infile >> stuInfo.course;
				i++;
			}
			else if (strcmp(check, "=") == 0 && i == 7) {
				infile >> stuInfo.cgpa;
				i = 1;
				if (t1->empty()) {
					if (!redundant(stuInfo.id, t1->root)) {
						t1->insert(stuInfo);
						count++;
					}
				}
				else {
					t1->insert(stuInfo);
					count++;
				}
			}
		}
		infile.close();
		cout << "\n\tSuccessfully read student(s) record from student.txt!" << endl;
		cout << "\n\t\tNumber of student(s) record read: " << count << endl;
		cout << "\n\n\t\t";
		return true;
	}
}

bool redundant(int id, BTNode* BTptr) {
	if (BTptr == NULL)
		return false;

	if (id == BTptr->item.id)
		return true;
	else if (id < BTptr->item.id)
		return redundant(id, BTptr->left);
	else
		return redundant(id, BTptr->right);
}


//Menu
int menu() {
	BST studentRecord1;
	Student student1;
	string select;
	do {
		cout << "       __    __     ______     __   __     __  __    " << endl;
		cout << "      /\\ '-./  \\   /\\  ___\\   /\\ '-.\\ \\   /\\ \\/\\ \\   " << endl;
		cout << "      \\ \\ \\-./\\ \\  \\ \\  __\\   \\ \\ \\-.  \\  \\ \\ \\_\\ \\  " << endl;
		cout << "       \\ \\_\\ \\ \\_\\  \\ \\_____\\  \\ \\_\\\\'\\_\\  \\ \\_____\\" << endl;
		cout << "        \\/_/  \\/_/   \\/_____/   \\/_/ \\/_/   \\/_____/ " << endl << endl;
		cout << string(60, char(175)) << endl << endl;
		cout << "\t\t1. Read Data to BST" << endl;
		cout << "\t\t2. Print Deepest Nodes" << endl;
		cout << "\t\t3. Display Student" << endl;
		cout << "\t\t4. Clone Subtree" << endl;
		cout << "\t\t5. Print Level Nodes" << endl;
		cout << "\t\t6. Print Path" << endl;
		cout << "\t\t7. Exit\n" << endl;
		cout << string(60, char(175)) << endl;
		cout << endl << "  \t\tAnswer: ";
		getline(cin, select);
		system("CLS");

		if (select == "1") {
			cout << "  ___             _     ___       _            _           ___ ___ _____ " << endl;
			cout << " | _ \\___ __ _ __| |   |   \\ __ _| |_ __ _    | |_ ___    | _ ) __|_   _|" << endl;
			cout << " |   / -_) _` / _` |   | |) / _` |  _/ _` |   |  _/ _ \\   | _ \\__ \\ | |  " << endl;
			cout << " |_|_\\___\\__,_\\__,_|   |___/\\__,_|\\__\\__,_|    \\__\\___/   |___/___/ |_|  " << endl;
			cout << "\n" << string(75, char(45)) << endl;
			if (!readFile("student.txt", &studentRecord1))
				cout << "\n\t\t\t\tError!!!" << endl;
			
			system("pause");
			system("CLS");
		}

		else if (select == "2") {
			cout << "  ___     _     _       ___                       _       _  _         _        " << endl;
			cout << " | _ \\_ _(_)_ _| |_    |   \\ ___ ___ _ __  ___ __| |_    | \\| |___  __| |___ ___" << endl;
			cout << " |  _/ '_| | ' \\  _|   | |) / -_) -_) '_ \\/ -_|_-<  _|   | .` / _ \\/ _` / -_|_-<" << endl;
			cout << " |_| |_| |_|_||_\\__|   |___/\\___\\___| .__/\\___/__/\\__|   |_|\\_\\___/\\__,_\\___/__/" << endl;
			cout << "                                    |_|                                         " << endl;
			cout << string(82, char(45)) << endl;
			if (!studentRecord1.deepestNodes())
				cout << "\n\t\t\t     Error!!!" << endl;
			
			cout <<"\n"<< string(82, char(45)) << endl;
			cout << "\n\n\t\t";
			system("pause");
			system("CLS");
		}

		else if (select == "3") {
			int order, source;
			cout << "  ___  _         _               ___ _           _         _       ___       __     " << endl;
			cout << " |   \\(_)____ __| |__ _ _  _    / __| |_ _  _ __| |___ _ _| |_    |_ _|_ _  / _|___ " << endl;
			cout << " | |) | (_-< '_ \\ / _` | || |   \\__ \\  _| || / _` / -_) ' \\  _|    | || ' \\|  _/ _ \\" << endl;
			cout << " |___/|_/__/ .__/_\\__,_|\\_, |   |___/\\__|\\_,_\\__,_\\___|_||_\\__|   |___|_||_|_| \\___/" << endl;
			cout << "           |_|          |__/                                                        " << endl << endl;
			cout << string(85, char(45)) << endl;
			cout << "\nDo you want to print student(s) info in ascending or descending order?" << endl;
			cout << "\n( 1 - ascending order, 2 - desceding order ) : ";
			cin >> order;
			cin.ignore();
			cout << "\nWould you like to print the student(s) info on screen or print to file? " << endl;
			cout << "\n( 1 - Print to Screen, 2 - Print to File ) : ";
			cin >> source;
			cin.ignore();

			cout << "\n" << string(85, char(45)) << endl;
			if (!studentRecord1.display(order, source))
				cout << "\nError!!!" << endl << endl;
			else {
				if (source == 1) {
					cout << "\n" << string(85, char(45)) << endl;
					cout << "\t     ~ Successfully Display Student(s) Information on Screen! ~" << endl;
					cout << string(85, char(45)) << endl << endl;
				}
				else if (source == 2) {
					cout << "\t      ~ Successfully Display Student(s) Information to File! ~" << endl;
					cout << string(85, char(45)) << endl << endl;
				}

			}
			system("pause");
			system("CLS");
		}

		else if (select == "4") {
			BST t2;
			cout << "   ___ _                  ___      _    _               " << endl;
			cout << "  / __| |___ _ _  ___    / __|_  _| |__| |_ _ _ ___ ___ " << endl;
			cout << " | (__| / _ \\ ' \\/ -_)   \\__ \\ || | '_ \\  _| '_/ -_) -_)" << endl;
			cout << "  \\___|_\\___/_||_\\___|   |___/\\_,_|_.__/\\__|_| \\___\\___|" << endl;
			cout << "\n" << string(63, char(45)) << endl << endl;

			cout << "Enter Student ID to be cloned as the root of subtree: ";
			cin >> student1.id;
			cin.ignore();

			if (cin.fail()) {
				cin.clear();
				cin.ignore(100, '\n');
			}
			cout << "\n\n" << string(63, char(45)) << endl;
			if (t2.CloneSubtree(studentRecord1, student1)) {
				cout << "\t      ~ Successfully Cloned Subtree! ~" << endl;
				cout << string(63, char(45)) << endl << endl;
			}
			else {
				cout << "\nThe subtree cannot be cloned." << endl <<endl;
			}

			system("pause");
			system("CLS");
		}

		else if (select == "5") {
			cout << "  ___     _     _       _                _     _  _         _        " << endl;
			cout << " | _ \\_ _(_)_ _| |_    | |   _____ _____| |   | \\| |___  __| |___ ___" << endl;
			cout << " |  _/ '_| | ' \\  _|   | |__/ -_) V / -_) |   | .` / _ \\/ _` / -_|_-<" << endl;
			cout << " |_| |_| |_|_||_\\__|   |____\\___|\\_/\\___|_|   |_|\\_\\___/\\__,_\\___/__/" << endl;
			cout << "\n" << string(70, char(45)) << endl << endl;

			if (studentRecord1.printLevelNodes()) {
				cout << "\n" << string(70, '-') << endl;
				cout << "\t   ~ Successfully Print Nodes of Each Level! ~" << endl;
				cout << string(70, '-') << endl << endl;
			}
			else {
				cout << "The tree is EMPTY!!!" << endl << endl;
			}

			system("pause");
			system("CLS");
		}

		else if (select == "6") {
			cout << "  ___     _     _       ___     _                     _     ___      _   _    " << endl;
			cout << " | _ \\_ _(_)_ _| |_    | __|_ _| |_ ___ _ _ _ _  __ _| |   | _ \\__ _| |_| |_  " << endl;
			cout << " |  _/ '_| | ' \\  _|   | _|\\ \\ /  _/ -_) '_| ' \\/ _` | |   |  _/ _` |  _| ' \\ " << endl;
			cout << " |_| |_| |_|_||_\\__|   |___/_\\_\\\\__\\___|_| |_||_\\__,_|_|   |_| \\__,_|\\__|_||_|" << endl;
			cout << "\n" << string(80, char(45)) << endl << endl;

			if (studentRecord1.printPath()) {
				cout << "\n" << string(80, '-') << endl;
				cout << "\t\t  ~ Successfully Print Each External Path! ~" << endl;
				cout << string(80, '-') << endl << endl;
			}
			else {
				cout << "The tree is EMPTY!!!" << endl << endl;
			}

			system("pause");
			system("CLS");
		}

		else if (select == "7") {
			cout << "\t   ___              _ ___            _   _  " << endl;
			cout << "\t  / __|___  ___  __| | _ )_  _ ___  | | | | " << endl;
			cout << "\t | (_ / _ \\/ _ \\/ _` | _ \\ || / -_) |_| |_| " << endl;
			cout << "\t  \\___\\___/\\___/\\__,_|___/\\_, \\___| (_) (_) " << endl;
			cout << "\t                          |__/              " << endl;
			cout << "\n\n\t\t";
			system("pause");
			system("CLS");
		}

		else {
			cout << "  ___ _                     _____              _             _         _   _   _   " << endl;
			cout << " | _ \\ |___ __ _ ___ ___   |_   _| _ _  _     /_\\  __ _ __ _(_)_ _    | | | | | |  " << endl;
			cout << " |  _/ / -_) _` (_-</ -_)    | || '_| || |   / _ \\/ _` / _` | | ' \\   |_| |_| |_|  " << endl;
			cout << " |_| |_\\___\\__,_/__/\\___|    |_||_|  \\_, |  /_/ \\_\\__, \\__,_|_|_||_|  (_) (_) (_)  " << endl;
			cout << "                                     |__/         |___/                            " << endl;
			cout << "\n\n\t\t";
			system("pause");
			system("CLS");
			return menu();
		}
	} while (select != "7");
}