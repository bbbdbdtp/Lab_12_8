#include <iostream>
#include <string>

using namespace std;

// ��������� ����� ������ �����
struct Node {
    string fileName;
    int fileSize;
    string creationDate;
    string accessRights; // ����� �������: "������", "������", "������ �����������"
    Node* next;
};

// ������� ��� ��������� ������ �����
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
        cin.ignore(); // �������� ��������� ������ ������ ����� � ������
        getline(cin, fileName);

        int fileSize;
        cout << "File Size: ";
        cin >> fileSize;

        string creationDate;
        cout << "Creation Date: ";
        cin.ignore(); // �������� ��������� ������ ������ ����� � ������
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

// ������� ��� ���������� ����� � ���������� ������� �������
Node* filterRestrictedAccessFiles(Node* head, int& numRestrictedFiles) {
    Node* filteredHead = nullptr;
    Node* filteredTail = nullptr;

    Node* current = head;
    while (current != nullptr) {
        // �������� �� ����� ������� ���������
        if (current->accessRights == "denied") {
            numRestrictedFiles++; // ��������� ��������� ��������� �����

            // ��������� ������ ����� ��� ����� � ���������� ������� �������
            Node* newNode = new Node();
            newNode->fileName = current->fileName;
            newNode->fileSize = current->fileSize;
            newNode->creationDate = current->creationDate;
            newNode->accessRights = current->accessRights;
            newNode->next = nullptr;

            // ��������� ������ ����� �� ��������������� ������
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

// ������� ��� ����� ������ �����
void printList(Node* head) {
    Node* current = head;
    while (current != nullptr) {
        // �������� ��� ��� �����
        cout << "File Name: " << current->fileName << ", File Size: " << current->fileSize << ", Creation Date: " << current->creationDate << ", Access Rights: " << current->accessRights << endl;
        current = current->next;
    }
}

int main() {
    int numRestrictedFiles = 0; // ˳������� ��������� �����

    // ���������� ������ ����� � ���������
    Node* fileList = createList();

    cout << "\nInput File List:" << endl;
    // ��������� �������� ������ �����
    printList(fileList);

    // Գ�������� ����� � ���������� ������� �������
    Node* restrictedAccessFilesList = filterRestrictedAccessFiles(fileList, numRestrictedFiles);

    cout << "\nRestricted Access Files List:" << endl;
    // ��������� ������ ����� � ���������� ������� �������
    printList(restrictedAccessFilesList);

    // ��������� ������� ����� � ���������� ������� �������
    cout << "\nNumber of Restricted Access Files: " << numRestrictedFiles << endl;

    // ��������� ���'��, �� ��������������� ��������
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