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
    //1. Инициализация
    Node* init() {
        return nullptr;
    }

    //2. Освобождение памяти
    void dispose(Node*& head) {
        Node* current = head;
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
        head = nullptr;
    }

    //3. Добавление элемента (упорядоченный по возрастанию)
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

    //4. Удаление всех вхождений заданного по значению элемента
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

    //5. Удаление (после каждого вхождения заданного)
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

    //6. Поиск заданного элемента по значению
    bool find(Node* head, int value) {
        Node* current = head;
        while (current) {
            if (current->data == value)
                return true;
            current = current->next;
        }
        return false;
    }

    //7. Печать
    void print(Node* head) {
        Node* current = head;
        while (current) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    //8. Операция работы с двумя списками (симметрическая разность)
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
    //Для корректного отображения кириллицы
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    List list;
    Node* head = list.init();
    int choice, value;

    //Для симметрической разности
    Node* result = list.init();
    Node* scnd_head = list.init();

    do {
        cout << "Меню:\n";
        cout << "1. Инициализация списка\n";
        cout << "2. Освобождение памяти\n";
        cout << "3. Добавление элемента\n";
        cout << "4. Удаление всех вхождений элемента\n";
        cout << "5. Удаление после каждого вхождения\n";
        cout << "6. Поиск элемента\n";
        cout << "7. Печать списка\n";
        cout << "8. Симметрическая разность двух списков\n";
        cout << "0. Выход\n";
        cout << "Выберите действие: ";
        cin >> choice;

        switch (choice) {
        case 1: //+1. Инициализация
            head = list.init();
            cout << "Список инициализирован.\n";
            break;
        case 2: //+2. Освобождение памяти
            list.dispose(head);
            cout << "Память освобождена.\n";
            break;
        case 3: //+3. Добавление элемента (упорядоченный по возрастанию)
            cout << "Введите значение для добавления: ";
            cin >> value;
            list.addSorted(head, value);
            cout << "Элемент добавлен.\n";
            break;
        case 4: //+4. Удаление всех вхождений заданного по значению элемента
            cout << "Введите значение для удаления: ";
            cin >> value;
            list.removeAll(head, value);
            cout << "Вхождения удалены.\n";
            break;
        case 5: //+5. Удаление (после каждого вхождения заданного)
            cout << "Введите значение, после каждого вхождения которого необходимо производить удаление: ";
            cin >> value;
            list.removeAfter(head, value);
            break;
        case 6: //+6. Поиск заданного элемента по значению
            cout << "Введите значение для поиска: ";
            cin >> value;
            if (list.find(head, value)) {
                cout << "Элемент найден.\n";
            }
            else cout << "Элемент не найден.\n";
            break;
        case 7: //+7. Печать
            cout << "Список: ";
            list.print(head);
            break;
        case 8: //+8. Операция работы с двумя списками (симметрическая разность)
            while (true) {
                string input;
                cout << "Введите очередной элемент второго списка либо введите латинскую 'e', чтобы завершить ввод: ";
                cin >> input;

                if (input == "e") {
                    cout << "Ввод второго списка завершен.\n";
                    break;
                }

                try {
                    value = stoi(input);
                    list.addSorted(scnd_head, value);
                }
                catch (invalid_argument& e) {
                    cout << "Некорректный ввод, попробуйте снова.\n";
                }
            };
            cout << "Первый список: ";
            list.print(head);
            cout << "Второй список: ";
            list.print(scnd_head);

            result = list.symmetricDifference(head, scnd_head);
            cout << "Результат: ";
            list.print(result);
            break;
        case 0:
            cout << "Выход из программы.\n";
            break;
        default:
            cout << "Некорректный выбор.\n";
        }
    } while (choice != 0);

    list.dispose(head);
    return 0;
}