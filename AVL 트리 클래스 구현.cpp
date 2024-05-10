#include <iostream>
using namespace std;

class AVLNode {
public:
    int key;  // ����� Ű ��
    AVLNode* left;  // ���� �ڽ� ��� ������
    AVLNode* right;  // ������ �ڽ� ��� ������
    int height;  // ����� ����
    AVLNode(int d) : key(d), left(nullptr), right(nullptr), height(1) {}
};

class AVLTree {
public:
    // ��� ���� �Լ�
    AVLNode* insert(AVLNode* node, int key) {
        if (node == nullptr)
            return new AVLNode(key);  // �� ��� ����
        if (key < node->key)
            node->left = insert(node->left, key);  // ���� ����Ʈ���� ����
        else if (key > node->key)
            node->right = insert(node->right, key);  // ������ ����Ʈ���� ����
        else
            return node;  // �ߺ� Ű�� ������� ����

        return updateBalance(node);  // �뷱�� ������Ʈ
    }

    // ��� ���� �Լ�
    void remove(AVLNode*& node, int key) {
        node = removeInternal(node, key);
    }

    // ���������� ��带 �����ϴ� �Լ�
    AVLNode* removeInternal(AVLNode* node, int key) {
        if (node == nullptr)
            return node;

        if (key < node->key) {
            node->left = removeInternal(node->left, key);
        }
        else if (key > node->key) {
            node->right = removeInternal(node->right, key);
        }
        else {
            if (node->left == nullptr || node->right == nullptr) {
                AVLNode* temp = node->left ? node->left : node->right;
                if (temp == nullptr) {
                    delete node;  // �ڽ� ��尡 ������ ����
                    node = nullptr;
                }
                else {
                    *node = *temp; // �ڽ� ��尡 �ϳ� ������, �� �ڽ����� ��ü
                    delete temp;
                }
            }
            else {
                AVLNode* temp = minValueNode(node->right);  // �� �ڽ� ��尡 ������, �ļ� ��带 ã�� ��ü
                node->key = temp->key;
                node->right = removeInternal(node->right, temp->key);
            }
        }

        if (node == nullptr) return node;

        return updateBalance(node);  // �뷱�� ������Ʈ
    }

    // �ּҰ��� ���� ��� ã��
    AVLNode* minValueNode(AVLNode* node) {
        AVLNode* current = node;
        while (current->left != nullptr) {
            current = current->left;
        }
        return current;
    }

    // �뷱�� ������Ʈ �Լ�
    AVLNode* updateBalance(AVLNode* node) {
        node->height = 1 + max(height(node->left), height(node->right));
        int balance = getBalance(node);

        // ȸ���� ���� Ʈ�� ���� ����
        if (balance > 1 && getBalance(node->left) >= 0)
            return rightRotate(node);
        if (balance > 1 && getBalance(node->left) < 0) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        if (balance < -1 && getBalance(node->right) <= 0)
            return leftRotate(node);
        if (balance < -1 && getBalance(node->right) > 0) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
        return node;
    }

    // ������ ȸ��
    AVLNode* rightRotate(AVLNode* y) {
        AVLNode* x = y->left;
        AVLNode* T2 = x->right;
        x->right = y;
        y->left = T2;
        y->height = max(height(y->left), height(y->right)) + 1;
        x->height = max(height(x->left), height(x->right)) + 1;
        return x;
    }

    // ���� ȸ��
    AVLNode* leftRotate(AVLNode* x) {
        AVLNode* y = x->right;
        AVLNode* T2 = y->left;
        y->left = x;
        x->right = T2;
        x->height = max(height(x->left), height(x->right)) + 1;
        y->height = max(height(y->left), height(y->right)) + 1;
        return y;
    }

    // ����� ���̸� ��ȯ�ϴ� �Լ�
    int height(AVLNode* node) {
        if (node == nullptr)
            return 0;
        return node->height;
    }

    // �� ���� �� ū ���� ��ȯ�ϴ� �Լ�
    int max(int a, int b) {
        return (a > b) ? a : b;
    }

    // ����� ���� �μ��� ��ȯ�ϴ� �Լ�
    int getBalance(AVLNode* node) {
        if (node == nullptr)
            return 0;
        return height(node->left) - height(node->right);
    }

    // ���� ��ȸ �Լ�
    void inOrder(AVLNode* node) {
        if (node != nullptr) {
            inOrder(node->left);
            cout << node->key << " ";
            inOrder(node->right);
        }
    }
};
