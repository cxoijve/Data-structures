#include <iostream>
using namespace std;

class AVLNode {
public:
    int key;  // 노드의 키 값
    AVLNode* left;  // 왼쪽 자식 노드 포인터
    AVLNode* right;  // 오른쪽 자식 노드 포인터
    int height;  // 노드의 높이
    AVLNode(int d) : key(d), left(nullptr), right(nullptr), height(1) {}
};

class AVLTree {
public:
    // 노드 삽입 함수
    AVLNode* insert(AVLNode* node, int key) {
        if (node == nullptr)
            return new AVLNode(key);  // 새 노드 생성
        if (key < node->key)
            node->left = insert(node->left, key);  // 왼쪽 서브트리에 삽입
        else if (key > node->key)
            node->right = insert(node->right, key);  // 오른쪽 서브트리에 삽입
        else
            return node;  // 중복 키는 허용하지 않음

        return updateBalance(node);  // 밸런스 업데이트
    }

    // 노드 삭제 함수
    void remove(AVLNode*& node, int key) {
        node = removeInternal(node, key);
    }

    // 내부적으로 노드를 삭제하는 함수
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
                    delete node;  // 자식 노드가 없으면 삭제
                    node = nullptr;
                }
                else {
                    *node = *temp; // 자식 노드가 하나 있으면, 그 자식으로 대체
                    delete temp;
                }
            }
            else {
                AVLNode* temp = minValueNode(node->right);  // 두 자식 노드가 있으면, 후속 노드를 찾아 대체
                node->key = temp->key;
                node->right = removeInternal(node->right, temp->key);
            }
        }

        if (node == nullptr) return node;

        return updateBalance(node);  // 밸런스 업데이트
    }

    // 최소값을 가진 노드 찾기
    AVLNode* minValueNode(AVLNode* node) {
        AVLNode* current = node;
        while (current->left != nullptr) {
            current = current->left;
        }
        return current;
    }

    // 밸런스 업데이트 함수
    AVLNode* updateBalance(AVLNode* node) {
        node->height = 1 + max(height(node->left), height(node->right));
        int balance = getBalance(node);

        // 회전을 통해 트리 균형 유지
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

    // 오른쪽 회전
    AVLNode* rightRotate(AVLNode* y) {
        AVLNode* x = y->left;
        AVLNode* T2 = x->right;
        x->right = y;
        y->left = T2;
        y->height = max(height(y->left), height(y->right)) + 1;
        x->height = max(height(x->left), height(x->right)) + 1;
        return x;
    }

    // 왼쪽 회전
    AVLNode* leftRotate(AVLNode* x) {
        AVLNode* y = x->right;
        AVLNode* T2 = y->left;
        y->left = x;
        x->right = T2;
        x->height = max(height(x->left), height(x->right)) + 1;
        y->height = max(height(y->left), height(y->right)) + 1;
        return y;
    }

    // 노드의 높이를 반환하는 함수
    int height(AVLNode* node) {
        if (node == nullptr)
            return 0;
        return node->height;
    }

    // 두 정수 중 큰 값을 반환하는 함수
    int max(int a, int b) {
        return (a > b) ? a : b;
    }

    // 노드의 균형 인수를 반환하는 함수
    int getBalance(AVLNode* node) {
        if (node == nullptr)
            return 0;
        return height(node->left) - height(node->right);
    }

    // 중위 순회 함수
    void inOrder(AVLNode* node) {
        if (node != nullptr) {
            inOrder(node->left);
            cout << node->key << " ";
            inOrder(node->right);
        }
    }
};
