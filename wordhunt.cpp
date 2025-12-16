#include <iostream>
#include <fstream>
#include <cstring>
#include <cctype>
#include <cstdlib>
#include <ctime> // all libraries mentioned in the assigment question 

using namespace std;

// ========== FUNCTION DECLARATIONS ==========
char** create_board(int size);
void free_board(char** board, int size);
void initialize_board(char** board, int size);
void display_board(char** board, int size);  // board manangment functions 

char** load_dictionary(const char* filename, int* word_count);
void free_dictionary(char** dictionary, int word_count);
bool is_valid_word(char** dictionary, int word_count, const char* word);
void to_uppercase(char* str); // dictionary management functions /helper funtions

bool** create_visited(int size);
void free_visited(bool** visited, int size); // word search functions 

bool find_word_from(char** board, int size, const char* word,
                    int row, int col, bool** visited, int index);
bool search_word(char** board, int size, const char* word);

int calculate_score(const char* word);// all the functions provided in the assignment question

// ========== MAIN FUNCTION ==========
int main() {
    
    cout << "WORD HUNT - Boggle Word Game\n"; // display game title (ASCII art too complicated looking)
    

    int word_count = 0;
    char** dictionary = load_dictionary("dictionary.txt", &word_count); // load dictionary 

    if (dictionary == NULL) {
        cout << "Dictionary file not found.\n";
        return 0;//Check if dictionary is nullptr (file not found)
    }

    cout << "Dictionary loaded: " << word_count << " words.\n"; // Print number of words loaded

    int size;
    cout << "Enter board size (3-6, default 4): "; //  Get board size from user
    cin >> size;

    if (size < 3 || size > 6) {
        size = 4;
    }

    char** board = create_board(size);
    initialize_board(board, size);
    display_board(board, size); // create and initialize board

    int score = 0;
    bool playing = true; // initialise game variabkles 

    while (playing) {
        cout << "MENU:\n";
        cout << "1. Find a word\n";
        cout << "2. Generate new board\n";
        cout << "3. Quit\n";
        cout << "Your score: " << score << "\n";
        cout << "Enter choice: ";

        int choice;
        cin >> choice;

        if (choice == 1) { // find a word
            char word[100];
            cout << "Enter word to find: ";
            cin >> word;

            to_uppercase(word);

            if (strlen(word) < 3) {
                cout << "Word too short.\n";
            } else if (!is_valid_word(dictionary, word_count, word)) {
                cout << "'" << word << "' is not in the dictionary.\n";
            } else {
                cout << "Searching for '" << word << "'...\n";
                if (search_word(board, size, word)) {
                    int pts = calculate_score(word);
                    score = score + pts;
                    cout << "Word found! +" << pts << " points\n";
                } else {
                    cout << "Word not found on board.\n";
                }
            }
        }
        else if (choice == 2) { // generate new board
            free_board(board, size);
            board = create_board(size);
            initialize_board(board, size);
            display_board(board, size);
            score = 0;
            cout << "Score reset to 0.\n";
        }
        else if (choice == 3) { // quit
            playing = false;
        }
        else {
            cout << "Invalid choice.\n";
        }
    }

    free_board(board, size);
    free_dictionary(dictionary, word_count);

    cout << "Goodbye!\n";
    return 0;
}

// ========== FUNCTION IMPLEMENTATIONS ==========
// todo- implement all functions as per the assignment requirements
char** create_board(int size) {
    char** board = new char*[size];
    for (int i = 0; i < size; i++) {
        board[i] = new char[size];
    }
    return board;
}

void free_board(char** board, int size) {
    for (int i = 0; i < size; i++) {
        delete[] board[i];
    }
    delete[] board;
}

void initialize_board(char** board, int size) {
    srand(time(0));
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            board[i][j] = 'A' + rand() % 26;
        }
    }
}

void display_board(char** board, int size) {
    cout << "\n";
    cout << "  ";
    for (int i = 0; i < size; i++) {
        cout << i << " ";
    }
    cout << "\n";

    for (int i = 0; i < size; i++) {
        cout << "+";
        for (int j = 0; j < size; j++) {
            cout << "---+";
        }
        cout << "\n";

        cout << i << "|";
        for (int j = 0; j < size; j++) {
            cout << " " << board[i][j] << " |";
        }
        cout << "\n";
    }

    cout << "+";
    for (int j = 0; j < size; j++) {
        cout << "---+";
    }
    cout << "\n\n";
}

char** load_dictionary(const char* filename, int* word_count) {
    ifstream file(filename);
    if (!file.is_open()) {
        return NULL;
    }

    char temp[100];
    int count = 0;

    while (file >> temp) {
        if (strlen(temp) >= 3) {
            count++;
        }
    }

    *word_count = count;
    char** dict = new char*[count];

    file.clear();
    file.seekg(0);

    int index = 0;
    while (file >> temp) {
        if (strlen(temp) >= 3) {
            dict[index] = new char[strlen(temp) + 1];
            strcpy(dict[index], temp);
            to_uppercase(dict[index]);
            index++;
        }
    }

    file.close();
    return dict;
}

void free_dictionary(char** dictionary, int word_count) {
    for (int i = 0; i < word_count; i++) {
        delete[] dictionary[i];
    }
    delete[] dictionary;
}

bool is_valid_word(char** dictionary, int word_count, const char* word) {
    for (int i = 0; i < word_count; i++) {
        if (strcmp(dictionary[i], word) == 0) {
            return true;
        }
    }
    return false;
}

void to_uppercase(char* str) {
    for (int i = 0; str[i] != '\0'; i++) {
        str[i] = toupper(str[i]);
    }
}

bool** create_visited(int size) {
    bool** visited = new bool*[size];
    for (int i = 0; i < size; i++) {
        visited[i] = new bool[size];
        for (int j = 0; j < size; j++) {
            visited[i][j] = false;
        }
    }
    return visited;
}

void free_visited(bool** visited, int size) {
    for (int i = 0; i < size; i++) {
        delete[] visited[i];
    }
    delete[] visited;
}

bool find_word_from(char** board, int size, const char* word,
                    int row, int col, bool** visited, int index) {

               // tried checking bounds first but it broke recursion
    // base case when full word is matched         
    if (word[index] == '\0') {
        return true;
    }

    if (row < 0 || col < 0 || row >= size || col >= size) {
        return false;
    }

    if (visited[row][col]) { //backtracking check
        return false;
    }

    if (board[row][col] != word[index]) {
        return false;
    }

    visited[row][col] = true;

    int dr[8] = {-1,-1,-1,0,0,1,1,1};
    int dc[8] = {-1,0,1,-1,1,-1,0,1}; //define direction arrays for 8 possible moves

    for (int i = 0; i < 8; i++) {
        if (find_word_from(board, size, word,
                           row + dr[i], col + dc[i],
                           visited, index + 1)) {
            visited[row][col] = false;
            return true;
        }
    }

    visited[row][col] = false;
    return false;
}

bool search_word(char** board, int size, const char* word) { // tried using one visited array for all searches but words were failing randomly, so recreating each time
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            bool** visited = create_visited(size);
            if (find_word_from(board, size, word, i, j, visited, 0)) {
                free_visited(visited, size);
                return true;
            }
            free_visited(visited, size);
        }
    }
    return false;
}

int calculate_score(const char* word) {
    int len = strlen(word);

    if (len == 3 || len == 4) return 1;
    if (len == 5) return 2;
    if (len == 6) return 3;
    if (len == 7) return 5;
    if (len >= 8) return 11;

    return 0;
}
