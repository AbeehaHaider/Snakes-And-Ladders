#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;

// Node structure for the linked list representation of the board
struct Node {
		int position;   // Tile number
		Node* next;     // Pointer to next tile
		Node* special;  // Pointer for snakes/ladders (NULL if none)

		Node(int pos) {  // Constructor
				position = pos;
				next = nullptr;
				special = nullptr;
		}
};

// Function to create the game board (linked list of 100 tiles)
Node* createBoard(int size) {
		Node* head = new Node(1); // First tile
		Node* temp = head;

		for (int i = 2; i <= size; i++) {
				temp->next = new Node(i);
				temp = temp->next;
		}
		return head;
}

// Function to find a node at a specific position
Node* findNode(Node* head, int pos) {
		Node* temp = head;
		while (temp && temp->position != pos) 
				temp = temp->next;
		return temp;
}

// Function to add snakes and ladders to the board
void addSnakesAndLadders(Node* head) {
		Node* temp = head;

		while (temp) {
				if (temp->position == 3) temp->special = findNode(head, 22);  // Ladder from 3 to 22
				if (temp->position == 5) temp->special = findNode(head, 8);   // Ladder from 5 to 8
				if (temp->position == 17) temp->special = findNode(head, 4);  // Snake from 17 to 4
				if (temp->position == 19) temp->special = findNode(head, 7);  // Snake from 19 to 7
				if (temp->position == 21) temp->special = findNode(head, 82); // Ladder from 21 to 82
				if (temp->position == 27) temp->special = findNode(head, 1);  // Snake from 27 to 1
				if (temp->position == 34) temp->special = findNode(head, 91); // Ladder from 34 to 91
				if (temp->position == 40) temp->special = findNode(head, 59); // Ladder from 40 to 59
				if (temp->position == 48) temp->special = findNode(head, 26); // Snake from 48 to 26
				if (temp->position == 56) temp->special = findNode(head, 53); // Snake from 56 to 53
				if (temp->position == 61) temp->special = findNode(head, 18); // Snake from 61 to 18
				if (temp->position == 73) temp->special = findNode(head, 94); // Ladder from 73 to 94
				if (temp->position == 84) temp->special = findNode(head, 98); // Ladder from 84 to 98
				if (temp->position == 89) temp->special = findNode(head, 68); // Snake from 89 to 68
				if (temp->position == 99) temp->special = findNode(head, 78); // Snake from 99 to 78
				temp = temp->next;
		}
}


struct Player {
		int position;      // Current position on the board
		int turns;         // Number of turns taken
		int snakeCount;    // Number of snakes encountered
		int ladderCount;   // Number of ladders encountered

		Player() {
				position = 1;
				turns = 0;
				snakeCount = 0;
				ladderCount = 0;
		}
};

// Function to simulate the game
void playGame(Node* head, int numPlayers) {
		vector<Player> players(numPlayers);  // Create players
		bool gameOver = false;

		cout << "\n🔹 Starting Snakes & Ladders Game 🔹\n";

		while (!gameOver) {
				for (int i = 0; i < numPlayers; i++) {
						if (players[i].position >= 100) continue; // Skip if already won

						int diceRoll = (rand() % 6) + 1;  // Rolling a dice (1-6)
						players[i].position += diceRoll;
						players[i].turns++;

						cout << "🎲 Player " << i + 1 << " rolled a " << diceRoll << ", moved to " << players[i].position;

						// Navigate to new position in linked list
						Node* temp = findNode(head, players[i].position);

						if (temp && temp->special) { // Check for snake or ladder
								if (temp->special->position > temp->position) {
										players[i].ladderCount++; // Ladder
										cout << " 🪜 Ladder! Moved up to " << temp->special->position;
								} else {
										players[i].snakeCount++; // Snake
										cout << " 🐍 Snake! Slid down to " << temp->special->position;
								}
								players[i].position = temp->special->position;
						}

						cout << endl;

						// Check for win condition
						if (players[i].position >= 100) {
								cout << "\n🎉 Player " << i + 1 << " wins after " << players[i].turns << " turns! 🎉\n";
								gameOver = true;
								break;
						}
				}
		}

		
		cout << "\n📊 Game Over! Here are the stats:\n";
		for (int i = 0; i < numPlayers; i++) {
				cout << "🔹 Player " << i + 1 << " took " << players[i].turns << " turns, hit " 
						 << players[i].snakeCount << " snakes, and climbed " 
						 << players[i].ladderCount << " ladders.\n";
		}
}

int main() {
		srand(time(0)); 

		int numPlayers;
		cout << "Enter the number of players: ";
		cin >> numPlayers;

		Node* board = createBoard(100);
		addSnakesAndLadders(board);

		playGame(board, numPlayers);

		return 0;
}
