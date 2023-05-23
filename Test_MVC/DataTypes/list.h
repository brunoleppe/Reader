//
// Created by bruno on 20/05/23.
//

#ifndef LCDTEST_LIST_H
#define LCDTEST_LIST_H


namespace bru {
template<typename T>
class list {
private:
    struct Node {
        T data;
        Node *next;

        explicit Node(const T &value) : data(value), next(nullptr) {}
    };

    Node *head;
    int count;

    class Iterator {
    private:
        Node* current;

    public:
        Iterator(Node* node) : current(node) {}

        T& operator*() const {
            return current->data;
        }

        Iterator& operator++() {
            if (current != nullptr) {
                current = current->next;
            }
            return *this;
        }

        bool operator!=(const Iterator& other) const {
            return current != other.current;
        }
    };

public:
    list() : head(nullptr), count(0) {}

    ~list() {
        clear();
    }

    void push_back(const T &value) {
        Node *newNode = new Node(value);

        if (head == nullptr) {
            head = newNode;
        } else {
            Node *current = head;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newNode;
        }

        count++;
    }

    const T &front() const {
        return head->data;
    }

    void clear() {
        Node *current = head;
        while (current != nullptr) {
            Node *next = current->next;
            delete current;
            current = next;
        }
        head = nullptr;
        count = 0;
    }

    int size() const {
        return count;
    }

    void remove(const T &value) {
        if (head == nullptr) {
            return; // List is empty, nothing to remove
        }

        // Check if the head node matches the value
        if (head->data == value) {
            Node *nodeToDelete = head;
            head = head->next;
            delete nodeToDelete;
            count--;
        } else {
            Node *current = head;
            while (current->next != nullptr) {
                if (current->next->data == value) {
                    Node *nodeToDelete = current->next;
                    current->next = current->next->next;
                    delete nodeToDelete;
                    count--;
                    return; // Found and removed the value, exit the function
                }
                current = current->next;
            }
        }
    }

    Iterator begin() const {
        return Iterator(head);
    }

    Iterator end() const {
        return Iterator(nullptr);
    }

};
}

#endif //LCDTEST_LIST_H
