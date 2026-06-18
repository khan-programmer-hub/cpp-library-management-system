
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

// ================= LOGIN SYSTEM =================
bool login() {
    string user, pass;

    cout << "===== ADMIN LOGIN =====\n";
    cout << "Username: ";
    cin >> user;
    cout << "Password: ";
    cin >> pass;

    if (user == "admin" && pass == "1234") {
        cout << "\nLogin Successful!\n";
        return true;
    } else {
        cout << "\nInvalid Credentials!\n";
        return false;
    }
}

// ================= BOOK CLASS =================
class Book {
private:
    int id;
    string title;
    string author;
    string category;
    bool issued;
    string dueDate;
    int fine;

public:
    Book() {
        id = 0;
        issued = false;
        fine = 0;
        dueDate = "";
    }

    int getId() { return id; }
    string getTitle() { return title; }
    string getCategory() { return category; }

    void input() {
        cout << "Enter Book ID: ";
        cin >> id;
        cin.ignore();

        cout << "Enter Title: ";
        getline(cin, title);

        cout << "Enter Author: ";
        getline(cin, author);

        cout << "Enter Category: ";
        getline(cin, category);

        issued = false;
        fine = 0;
        dueDate = "";
    }

    void display() {
        cout << "\n-----------------------------\n";
        cout << "ID       : " << id << endl;
        cout << "Title    : " << title << endl;
        cout << "Author   : " << author << endl;
        cout << "Category : " << category << endl;
        cout << "Status   : " << (issued ? "Issued" : "Available") << endl;
        if (issued) {
            cout << "Due Date : " << dueDate << endl;
            cout << "Fine     : " << fine << endl;
        }
        cout << "-----------------------------\n";
    }

    void issueBook() {
        if (issued) {
            cout << "Already issued!\n";
        } else {
            issued = true;
            cout << "Enter Due Date: ";
            cin >> dueDate;
            cout << "Issued successfully!\n";
        }
    }

    void returnBook() {
        if (!issued) {
            cout << "Already available!\n";
        } else {
            int days;
            cout << "Enter days late: ";
            cin >> days;

            fine = days * 10;
            issued = false;

            cout << "Returned successfully! Fine: " << fine << endl;
        }
    }

    void update() {
        cin.ignore();
        cout << "Update Title: ";
        getline(cin, title);

        cout << "Update Author: ";
        getline(cin, author);

        cout << "Update Category: ";
        getline(cin, category);

        cout << "Updated successfully!\n";
    }

    void save(ofstream &f) {
        f << id << endl;
        f << title << endl;
        f << author << endl;
        f << category << endl;
        f << issued << endl;
        f << dueDate << endl;
        f << fine << endl;
    }

    void load(ifstream &f) {
        f >> id;
        f.ignore();

        getline(f, title);
        getline(f, author);
        getline(f, category);

        f >> issued;
        f.ignore();

        getline(f, dueDate);
        f >> fine;
        f.ignore();
    }
};

// ================= SAFE LOAD =================
int load(Book b[]) {
    ifstream f("books.txt");
    int count = 0;

    if (!f) return 0;

    while (true) {
        b[count].load(f);
        if (!f.good()) break;
        count++;
    }
    return count;
}

// ================= SAFE SAVE =================
void save(Book b[], int count) {
    ofstream f("books.txt", ios::out | ios::trunc);

    for (int i = 0; i < count; i++) {
        b[i].save(f);
    }
}

// ================= MAIN SYSTEM =================
int main() {

    if (!login()) return 0;

    Book b[100];
    int count = load(b);
    int choice;

    while (true) {

        cout << "\n\n===== ADMIN PANEL =====\n";
        cout << "1. Add Book\n";
        cout << "2. Show Books\n";
        cout << "3. Search (ID)\n";
        cout << "4. Search (Name)\n";
        cout << "5. Search (Category)\n";
        cout << "6. Issue Book\n";
        cout << "7. Return Book\n";
        cout << "8. Update Book\n";
        cout << "9. Delete Book\n";
        cout << "10. Exit\n";
        cout << "=======================\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {

        // ADD
        case 1: {
            b[count].input();
            count++;
            save(b, count);
            break;
        }

        // SHOW
        case 2:
            for (int i = 0; i < count; i++)
                b[i].display();
            break;

        // SEARCH BY ID
        case 3: {
            int id;
            cout << "Enter ID: ";
            cin >> id;

            for (int i = 0; i < count; i++)
                if (b[i].getId() == id)
                    b[i].display();
            break;
        }

        // SEARCH BY NAME
        case 4: {
            string name;
            cin.ignore();
            cout << "Enter Title: ";
            getline(cin, name);

            for (int i = 0; i < count; i++)
                if (b[i].getTitle() == name)
                    b[i].display();
            break;
        }

        // SEARCH BY CATEGORY
        case 5: {
            string cat;
            cin.ignore();
            cout << "Enter Category: ";
            getline(cin, cat);

            for (int i = 0; i < count; i++)
                if (b[i].getCategory() == cat)
                    b[i].display();
            break;
        }

        // ISSUE
        case 6: {
            int id;
            cout << "Enter ID: ";
            cin >> id;

            for (int i = 0; i < count; i++)
                if (b[i].getId() == id)
                    b[i].issueBook();

            save(b, count);
            break;
        }

        // RETURN
        case 7: {
            int id;
            cout << "Enter ID: ";
            cin >> id;

            for (int i = 0; i < count; i++)
                if (b[i].getId() == id)
                    b[i].returnBook();

            save(b, count);
            break;
        }

        // UPDATE
        case 8: {
            int id;
            cout << "Enter ID: ";
            cin >> id;

            for (int i = 0; i < count; i++)
                if (b[i].getId() == id)
                    b[i].update();

            save(b, count);
            break;
        }

        // DELETE
        case 9: {
            int id;
            cout << "Enter ID: ";
            cin >> id;

            for (int i = 0; i < count; i++) {
                if (b[i].getId() == id) {
                    for (int j = i; j < count - 1; j++)
                        b[j] = b[j + 1];

                    count--;
                    save(b, count);
                    cout << "Deleted successfully!\n";
                    break;
                }
            }
            break;
        }

        case 10:
            save(b, count);
            cout << "System Closed!\n";
            return 0;
        }
    }
}
