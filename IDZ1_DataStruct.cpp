#include <iostream>
#include <string>
#include <windows.h>
using namespace std;

struct Node {
    int data;
    Node* next;
};

class List {
private:
    Node* head;
public:
    //1. �������������
    Node* init() {
        return nullptr;
    }

    //2. ������������ ������
    void dispose(Node*& head) {
        Node* current = head;
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
        head = nullptr;
    }

    //3. ���������� �������� (������������� �� �����������)
    void addSorted(Node*& head, int value) {
        Node* newNode = new Node{ value, nullptr };

        if (!head || value < head->data) {
            newNode->next = head;
            head = newNode;
            return;
        }

        Node* current = head;
        while (current->next && current->next->data < value) {
            current = current->next;
        }

        newNode->next = current->next;
        current->next = newNode;
    }

    //4. �������� ���� ��������� ��������� �� �������� ��������
    void removeAll(Node*& head, int value) {
        while (head && head->data == value) {
            Node* temp = head;
            head = temp->next;
            delete temp;
            temp = nullptr;
        }

        Node* current = head;
        while (current && current->next) {
            if (current->next->data == value) {
                Node* temp = current->next;
                current->next = temp->next;
                delete temp;
                temp = nullptr;
            }
            else {
                current = current->next;
            }
        }
    }

    //5. �������� (����� ������� ��������� ���������)
    void removeAfter(Node*& head, int value) {
        Node* current = head;
        while (current && current->next) {
            if (current->data == value) {
                Node* temp = current->next;
                current->next = temp->next;
                delete temp;
                temp = nullptr;
            }
            current = current->next;
        }
    }

    //6. ����� ��������� �������� �� ��������
    bool find(Node* head, int value) {
        Node* current = head;
        while (current) {
            if (current->data == value)
                return true;
            current = current->next;
        }
        return false;
    }

    //7. ������
    void print(Node* head) {
        Node* current = head;
        while (current) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    //8. �������� ������ � ����� �������� (�������������� ��������)
    Node* symmetricDifference(Node* fst_head, Node* scnd_head) {
        Node* result = nullptr;
        Node* current;

        current = fst_head;
        while (current) {
            if (!find(scnd_head, current->data)) {
                addSorted(result, current->data);
            }
            current = current->next;
        }

        current = scnd_head;
        while (current) {
            if (!find(fst_head, current->data)) {
                addSorted(result, current->data);
            }
            current = current->next;
        }

        return result;
    }
};

int main()
{
    //��� ����������� ����������� ���������
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    List list;
    Node* head = list.init();
    int choice, value;

    //��� �������������� ��������
    Node* result = list.init();
    Node* scnd_head = list.init();

    do {
        cout << "����:\n";
        cout << "1. ������������� ������\n";
        cout << "2. ������������ ������\n";
        cout << "3. ���������� ��������\n";
        cout << "4. �������� ���� ��������� ��������\n";
        cout << "5. �������� ����� ������� ���������\n";
        cout << "6. ����� ��������\n";
        cout << "7. ������ ������\n";
        cout << "8. �������������� �������� ���� �������\n";
        cout << "0. �����\n";
        cout << "�������� ��������: ";
        cin >> choice;

        switch (choice) {
        case 1: //+1. �������������
            head = list.init();
            cout << "������ ���������������.\n";
            break;
        case 2: //+2. ������������ ������
            list.dispose(head);
            cout << "������ �����������.\n";
            break;
        case 3: //+3. ���������� �������� (������������� �� �����������)
            cout << "������� �������� ��� ����������: ";
            cin >> value;
            list.addSorted(head, value);
            cout << "������� ��������.\n";
            break;
        case 4: //+4. �������� ���� ��������� ��������� �� �������� ��������
            cout << "������� �������� ��� ��������: ";
            cin >> value;
            list.removeAll(head, value);
            cout << "��������� �������.\n";
            break;
        case 5: //+5. �������� (����� ������� ��������� ���������)
            cout << "������� ��������, ����� ������� ��������� �������� ���������� ����������� ��������: ";
            cin >> value;
            list.removeAfter(head, value);
            break;
        case 6: //+6. ����� ��������� �������� �� ��������
            cout << "������� �������� ��� ������: ";
            cin >> value;
            if (list.find(head, value)) {
                cout << "������� ������.\n";
            }
            else cout << "������� �� ������.\n";
            break;
        case 7: //+7. ������
            cout << "������: ";
            list.print(head);
            break;
        case 8: //+8. �������� ������ � ����� �������� (�������������� ��������)
            while (true) {
                string input;
                cout << "������� ��������� ������� ������� ������ ���� ������� ��������� 'e', ����� ��������� ����: ";
                cin >> input;

                if (input == "e") {
                    cout << "���� ������� ������ ��������.\n";
                    break;
                }

                try {
                    value = stoi(input);
                    list.addSorted(scnd_head, value);
                }
                catch (invalid_argument& e) {
                    cout << "������������ ����, ���������� �����.\n";
                }
            };
            cout << "������ ������: ";
            list.print(head);
            cout << "������ ������: ";
            list.print(scnd_head);

            result = list.symmetricDifference(head, scnd_head);
            cout << "���������: ";
            list.print(result);
            break;
        case 0:
            cout << "����� �� ���������.\n";
            break;
        default:
            cout << "������������ �����.\n";
        }
    } while (choice != 0);

    list.dispose(head);
    return 0;
}