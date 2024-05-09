#include <iostream>
#include <string>

using namespace std;

// Структура вузла списку файлів
struct Node {
    string fileName;
    int fileSize;
    string creationDate;
    string accessRights; // Права доступу: "читати", "писати", "доступ заборонений"
    Node* next;
};

// Функція для створення списку файлів
Node* createList() {
    Node* head = nullptr;
    Node* tail = nullptr;

    int numFiles;
    cout << "Enter the number of files: ";
    cin >> numFiles;

    for (int i = 0; i < numFiles; ++i) {
        cout << "Enter details for file " << i + 1 << ":" << endl;

        string fileName;
        cout << "File Name: ";
        cin.ignore(); // Ігноруємо попередній символ нового рядка з буфера
        getline(cin, fileName);

        int fileSize;
        cout << "File Size: ";
        cin >> fileSize;

        string creationDate;
        cout << "Creation Date: ";
        cin.ignore(); // Ігноруємо попередній символ нового рядка з буфера
        getline(cin, creationDate);

        string accessRights;
        cout << "Access Rights (read/write/denied): ";
        getline(cin, accessRights);

        Node* newNode = new Node();
        newNode->fileName = fileName;
        newNode->fileSize = fileSize;
        newNode->creationDate = creationDate;
        newNode->accessRights = accessRights;
        newNode->next = nullptr;

        if (head == nullptr) {
            head = newNode;
            tail = newNode;
        }
        else {
            tail->next = newNode;
            tail = newNode;
        }
    }

    return head;
}

// Функція для фільтрації файлів з обмеженими правами доступу
Node* filterRestrictedAccessFiles(Node* head, int& numRestrictedFiles) {
    Node* filteredHead = nullptr;
    Node* filteredTail = nullptr;

    Node* current = head;
    while (current != nullptr) {
        // Перевірка чи права доступу заборонені
        if (current->accessRights == "denied") {
            numRestrictedFiles++; // Збільшення лічильника обмежених файлів

            // Створення нового вузла для файлу з обмеженими правами доступу
            Node* newNode = new Node();
            newNode->fileName = current->fileName;
            newNode->fileSize = current->fileSize;
            newNode->creationDate = current->creationDate;
            newNode->accessRights = current->accessRights;
            newNode->next = nullptr;

            // Додавання нового вузла до відфільтрованого списку
            if (filteredHead == nullptr) {
                filteredHead = newNode;
                filteredTail = newNode;
            }
            else {
                filteredTail->next = newNode;
                filteredTail = newNode;
            }
        }
        current = current->next;
    }

    return filteredHead;
}

// Функція для друку списку файлів
void printList(Node* head) {
    Node* current = head;
    while (current != nullptr) {
        // Виводимо дані про файли
        cout << "File Name: " << current->fileName << ", File Size: " << current->fileSize << ", Creation Date: " << current->creationDate << ", Access Rights: " << current->accessRights << endl;
        current = current->next;
    }
}

int main() {
    int numRestrictedFiles = 0; // Лічильник обмежених файлів

    // Зчитування списку файлів з клавіатури
    Node* fileList = createList();

    cout << "\nInput File List:" << endl;
    // Виведення вхідного списку файлів
    printList(fileList);

    // Фільтрація файлів з обмеженими правами доступу
    Node* restrictedAccessFilesList = filterRestrictedAccessFiles(fileList, numRestrictedFiles);

    cout << "\nRestricted Access Files List:" << endl;
    // Виведення списку файлів з обмеженими правами доступу
    printList(restrictedAccessFilesList);

    // Виведення кількості файлів з обмеженими правами доступу
    cout << "\nNumber of Restricted Access Files: " << numRestrictedFiles << endl;

    // Звільнення пам'яті, що використовується списками
    Node* current = fileList;
    while (current != nullptr) {
        Node* temp = current;
        current = current->next;
        delete temp;
    }

    current = restrictedAccessFilesList;
    while (current != nullptr) {
        Node* temp = current;
        current = current->next;
        delete temp;
    }

    return 0;
}