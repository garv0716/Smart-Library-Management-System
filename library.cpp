// Smart Library Management System using DSA
// Developed with practical features like student info, book inventory, and recommendations

#include <iostream>
#include <unordered_map>
#include <vector>
#include <stack>
#include <queue>
#include <algorithm>
#include <set>
#include <string>

using namespace std;

// Book structure
struct Book {
    int id;
    string title;
    string author;
    string genre;
    float rating;
    int quantity;
};

// Student structure
struct Student {
    int studentId;
    string name;
    vector<int> borrowedBooks;
};

unordered_map<int, Book> bookDatabase;                  // Book ID -> Book
unordered_map<string, vector<int>> authorMap;           // Author -> Book IDs
unordered_map<string, vector<int>> genreMap;            // Genre -> Book IDs
unordered_map<int, vector<int>> recommendationGraph;    // Book ID -> Connected Book IDs
unordered_map<int, Student> studentDatabase;            // Student ID -> Student

stack<int> borrowHistory;                               // Stack for borrow history

// Function declarations
void addBook();
void showAllBooks();
void searchBookByTitle();
void borrowBook();
void returnBook();
void viewBorrowHistory();
void displayBook(const Book& book);
void recommendBooks();
void registerStudent();
string toLower(const string& str);

int main() {
    int choice;

    while (true) {
        cout << "\n===== Library Management System =====" << endl;
        cout << "1. Add Book\n2. Show All Books\n3. Search Book by Title\n4. Register Student\n5. Borrow Book\n6. Return Book\n7. View Borrow History\n8. Recommend Books\n9. Exit\nEnter your choice: ";
        cin >> choice;
        cin.ignore();  // To clear the newline after choice input

        switch (choice) {
            case 1: addBook(); break;
            case 2: showAllBooks(); break;
            case 3: searchBookByTitle(); break;
            case 4: registerStudent(); break;
            case 5: borrowBook(); break;
            case 6: returnBook(); break;
            case 7: viewBorrowHistory(); break;
            case 8: recommendBooks(); break;
            case 9: cout << "Exiting...\n"; return 0;
            default: cout << "Invalid option. Try again.\n";
        }
    }

    return 0;
}

void addBook() {
    Book newBook;
    cout << "\nEnter Book ID: ";
    cin >> newBook.id;
    cin.ignore();
    cout << "Title: "; getline(cin, newBook.title);
    cout << "Author: "; getline(cin, newBook.author);
    cout << "Genre: "; getline(cin, newBook.genre);
    cout << "Rating (out of 5): "; cin >> newBook.rating;
    cout << "Quantity: "; cin >> newBook.quantity;
    cin.ignore();

    bookDatabase[newBook.id] = newBook;
    authorMap[newBook.author].push_back(newBook.id);
    genreMap[newBook.genre].push_back(newBook.id);

    // Update recommendation graph based on genre
    for (int otherId : genreMap[newBook.genre]) {
        if (otherId != newBook.id) {
            recommendationGraph[newBook.id].push_back(otherId);
            recommendationGraph[otherId].push_back(newBook.id);
        }
    }

    cout << "Book added successfully.\n";
}

void showAllBooks() {
    cout << "\n=== Available Books ===" << endl;
    for (const auto& entry : bookDatabase) {
        const Book& book = entry.second;
        if (book.quantity > 0) displayBook(book);
    }
}

void displayBook(const Book& book) {
    cout << "\n[Book ID: " << book.id << "]\nTitle: " << book.title
         << "\nAuthor: " << book.author << "\nGenre: " << book.genre
         << "\nRating: " << book.rating << "/5\nAvailable: " << book.quantity << endl;
}

void registerStudent() {
    Student newStudent;
    cout << "\nEnter Student ID: ";
    cin >> newStudent.studentId;
    cin.ignore();
    cout << "Enter Name: ";
    getline(cin, newStudent.name);
    studentDatabase[newStudent.studentId] = newStudent;
    cout << "Student registered successfully.\n";
}

void searchBookByTitle() {
    string title;
    cout << "\nEnter title to search (case-insensitive substring search): ";
    getline(cin, title);

    string titleLower = toLower(title);
    bool found = false;

    for (const auto& pair : bookDatabase) {
        string bookTitleLower = toLower(pair.second.title);
        if (bookTitleLower.find(titleLower) != string::npos) {
            displayBook(pair.second);
            found = true;
        }
    }

    if (!found) cout << "No books found matching the title.\n";
}

void borrowBook() {
    int studentId, bookId;
    cout << "\nEnter your Student ID: "; cin >> studentId;

    if (studentDatabase.find(studentId) == studentDatabase.end()) {
        cout << "Student not found. Please register first.\n";
        return;
    }

    cout << "Enter Book ID to borrow: "; cin >> bookId;
    if (bookDatabase.find(bookId) != bookDatabase.end()) {
        Book& book = bookDatabase[bookId];
        if (book.quantity > 0) {
            book.quantity--;
            studentDatabase[studentId].borrowedBooks.push_back(bookId);
            borrowHistory.push(bookId);
            cout << "Book borrowed successfully!\n";
        } else {
            cout << "Book not available right now.\n";
        }
    } else {
        cout << "Invalid Book ID.\n";
    }
    cin.ignore();
}

void returnBook() {
    int studentId, bookId;
    cout << "\nEnter your Student ID: "; cin >> studentId;

    if (studentDatabase.find(studentId) == studentDatabase.end()) {
        cout << "Student not found.\n";
        return;
    }

    cout << "Enter Book ID to return: "; cin >> bookId;

    auto& borrowed = studentDatabase[studentId].borrowedBooks;
    auto it = find(borrowed.begin(), borrowed.end(), bookId);
    if (it != borrowed.end()) {
        borrowed.erase(it);
        bookDatabase[bookId].quantity++;
        cout << "Book returned successfully.\n";
    } else {
        cout << "This book wasn't borrowed by you.\n";
    }
    cin.ignore();
}

void viewBorrowHistory() {
    stack<int> temp = borrowHistory;
    if (temp.empty()) {
        cout << "\nNo borrow history available.\n";
        return;
    }

    cout << "\n=== Borrow History (most recent first) ===" << endl;
    while (!temp.empty()) {
        int id = temp.top();
        temp.pop();
        if (bookDatabase.find(id) != bookDatabase.end())
            displayBook(bookDatabase[id]);
    }
}

void recommendBooks() {
    int bookId;
    cout << "\nEnter Book ID to get recommendations: ";
    cin >> bookId;

    if (recommendationGraph.find(bookId) == recommendationGraph.end()) {
        cout << "No recommendations found.\n";
        cin.ignore();
        return;
    }

    cout << "\nBooks similar by genre:\n";
    set<int> visited;
    queue<int> q;

    visited.insert(bookId);
    q.push(bookId);

    while (!q.empty()) {
        int current = q.front();
        q.pop();

        for (int neighbor : recommendationGraph[current]) {
            if (visited.find(neighbor) == visited.end()) {
                if (bookDatabase[neighbor].quantity > 0)
                    displayBook(bookDatabase[neighbor]);
                visited.insert(neighbor);
                q.push(neighbor);
            }
        }
    }
    cin.ignore();
}

// Helper function to convert string to lowercase for case-insensitive search
string toLower(const string& str) {
    string result = str;
    transform(result.begin(), result.end(), result.begin(),
              [](unsigned char c){ return tolower(c); });
    return result;
}
