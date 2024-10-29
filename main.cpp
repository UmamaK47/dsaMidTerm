#include<iostream>
using namespace std;
typedef int itemType;
struct Node{
	itemType score;
	Node* next;
	Node* previous;
};

class List {
private:
	Node* head = nullptr;
	Node* tail = nullptr;
public:
	void insertAtHead(itemType value);
	void insertAtTail(itemType value);
	void remove(itemType value);
	void display();
	void displayReverse();
	bool isEmpty();
	itemType highestScore();
	itemType lowestScore();
};

void List::insertAtHead(itemType value) {
	Node *newNode = new Node();
	newNode->score = value;
	if (head == nullptr) {
		head = newNode;
		tail = newNode;
		return;
	}
	else {
		newNode->next = head;
		head->previous = newNode;
		head = newNode;
		head->previous = nullptr;
	}
	if (newNode->next == nullptr) {
		tail = newNode;
	}
	cout << "\nScore Inserted Sucessfully.";
}
void List::insertAtTail(itemType value) {
	Node* newNode = new Node();
	newNode->score = value;
	newNode->next = nullptr;
	if (tail == nullptr) {
		head = newNode;
		tail = newNode;
		return;
	}
	else {
		tail->next = newNode;
		newNode->previous = tail;
		tail = newNode;
	}
	cout << "\nScore Inserted Sucessfully.";
}
void List::remove(itemType value) {
	if (isEmpty()) {
		cout << "No matches recorded yet.\n";
		return;
	}
	//delete all occurances of value
	Node* current = head;
	bool found = false;

	while (current != nullptr) {
		if (current->score == value) {
			found = true;
			Node* temp = current;
			//if the node we are removing is the head
			//first we update the new head
			//then we set its previous pointer to nullptr
			if (temp == head) {
				head = head->next;
				if (head != nullptr) {
					head->previous = nullptr;
				}
				else {
					tail = nullptr;
				}
			}
			//if node we're deleting is tail
			//update new tail and set its next pointer to nullptr
			else if (temp == tail) {
				tail = tail->previous;
				if (tail != nullptr) {
					tail->next = nullptr;
				}
				else {
					head = nullptr;
				}
			}
			//if node we're deleting is in the middle
			//set the pointer of the previous and next nodes
			// of the current node to point to each other
			else {
				temp->previous->next = temp->next;
				temp->next->previous = temp->previous;
			}

			current = current->next; 
			delete temp; 
		}
		else {
			current = current->next;
		}
	}

	if (!found) {
		cout << "\nScore " << value << " not found in any match.\n";
	}
	else {
		cout << "\nAll occurrences of score " << value << " removed successfully.\n";
	}
	
		
		
}
void List::display() {
	if (isEmpty()) {
		cout << "No matches recorded yet.\n";
		return;
	}

	Node* current = head;
	while (current != nullptr) {
		cout << "\n" << current->score;
		current = current->next;
	}
}
void List::displayReverse() {
	if (isEmpty()) {
		cout << "No matches recorded yet.\n";
		return;
	}
	else {
		Node* current = tail;
		do {
			cout << "\n" << current->score;
			current = current->previous;
		} while (current != nullptr);
	}
}
bool List::isEmpty() {
	return head == nullptr && tail==nullptr;
}

itemType List::highestScore() {
	if (isEmpty()) {
		cout << "No matches recorded yet.\n";
		return -1;
	}

	itemType maxScore = head->score;
	Node* current = head->next;
	while (current != nullptr) {
		if (current->score > maxScore) {
			maxScore = current->score;
		}
		current = current->next;
	}
	cout << "\nHighest Score: " << maxScore << endl;
	return maxScore;
}

itemType List::lowestScore() {
	if (isEmpty()) {
		cout << "No matches recorded yet.\n";
		return -1;
	}

	itemType minScore = head->score;
	Node* current = head->next;
	while (current != nullptr) {
		if (current->score < minScore) {
			minScore = current->score;
		}
		current = current->next;
	}
	cout << "\nLowest Score: " << minScore << endl;
	return minScore;
}

int main() {
	List matchScores;
	itemType value;
	string choice;
	char con = 'y';

	do {
		cout << "----MENU----\n";
		cout << "1. Add Runs at Start\n2. Add Runs at End\n3. Delete All Occurrences of a Score\n4. Display Scores in Sequence \n5. Display Scores in Reverse\n6. Find Highest Score\n7. Find Lowest Score";
		cout << "\nEnter your choice: ";
		cin >> choice;

		if (choice == "1") {
			cout << "Enter score to insert at start: ";
			while (!(cin >> value)) {
				cout << "Invalid input. Please enter an integer: ";
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
			matchScores.insertAtHead(value);
		}
		else if (choice == "2") {
			cout << "Enter score to insert at end: ";
			while (!(cin >> value)) {
				cout << "Invalid input. Please enter an integer: ";
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
			matchScores.insertAtTail(value);

		}
		else if (choice == "3") {

			cout << "Enter score to delete: ";
			while (!(cin >> value)) {
				cout << "Invalid input. Please enter an integer: ";
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
			matchScores.remove(value);
		}
		else if (choice == "4") {
			matchScores.display();
		}
		else if (choice == "5") {
			matchScores.displayReverse();
		}
		else if (choice == "6") {
			matchScores.highestScore();
		}
		else if (choice == "7") {
			matchScores.lowestScore();
		}
		else {
			cout << "Invalid choice. Try again.";
		}
		do {
			cout << "\nWould you like to continue? (Y:to continue/N:to exit program): ";
			cin >> con;
			if (con != 'y' && con != 'Y' && con != 'n' && con != 'N') {
				cout << "Invalid input: please enter Y or N." << endl;
			}

		} while (con != 'y' && con != 'Y' && con != 'n' && con != 'N');
	} while (con == 'y' || con == 'Y');
	cout << "Exiting Program..." << endl;
	return 0;
}

