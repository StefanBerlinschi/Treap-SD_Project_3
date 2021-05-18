#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

class Treap {
    private:
        int priority, data;
        Treap *left, *right, *parent;

    public:
        Treap(): priority(0), data(0), left(NULL), right(NULL), parent(NULL) {};
        Treap(int x): data(x), left(NULL), right(NULL), parent(NULL) {
            priority = rand() % 3000 + 1;
        };
        ~Treap() {
            free_space(get_root());
        };

        void free_space (Treap* root) {
            if (root == NULL) return;
            if (root->left != NULL)
                free_space(root->left);
            if (root->right != NULL) 
                 free_space(root->right);
            
            delete root;
        };

        friend ostream& operator << (ostream& out, Treap &nod) {
            out << nod.data << " ";
            return out;
        }
        

        void rotate_with_parent (Treap *B) {              // "this" este nodul B, pe care vrem sa il swap-am cu parintele sau A
            if (B->parent == NULL) return;

            Treap *A = B->parent;            // adresa lui A

            if (A->parent != NULL) {
                Treap *P = A->parent;           // adresa parintelui lui A
                
                B->parent = P;               // parintele lui B devine fostul parinte al lui A

                if (P->left == A) {             // il punem pe B in pozitia de fiu al fostului parinte
                    P->left = B;             // al lui A
                } else if (P->right == A) {
                    P->right = B;
                }
            } else B->parent = NULL;

            A->parent = B;               // parintele lui A devine B

            if (A->right == B) {
                A->right = B->left;

                if (B->left != NULL)
                    B->left->parent = A;

                B->left = A;
            } else if (A->left == B) {
                A->left = B->right;

                if (B->right != NULL)
                    B->right->parent = A;

                B->right = A;
            }
        }
        Treap* get_root() {
            if (this->parent == NULL) return this;
                else {
                    Treap* p = this;
                    while (p->parent != NULL)
                        p = p->parent;
                    return p;
                }
        }
        void insert(int x) {
            if (priority == 0) {                // daca nu exista noduri
                priority = rand() % 3000 + 1;
                data = x;
            } else {
                Treap *cob = get_root();

                while (cob != NULL) {
                    if (x < cob->data && cob->left == NULL) {
                        cob->left = new Treap(x);
                        cob->left->parent = cob;
                        cob = cob->left;
                        break;
                    }

                    if (x >= cob->data && cob->right == NULL) {
                        cob->right = new Treap(x);
                        cob->right->parent = cob;
                        cob = cob->right;
                        break;
                    }

                    if (x < cob->data) cob = cob->left;
                        else cob = cob->right;
                }

                while (cob->parent != NULL) {
                    if (cob->priority > cob->parent->priority)
                        rotate_with_parent(cob);
                    else break;
                }
            }
        }

        Treap* search(int x) {
            if (priority == 0) {
                // cout << "Treap-ul este gol!";
                return NULL;
            }

            Treap* ptr = get_root();
            while (ptr->data != x) {
                if (ptr->data > x) {
                    if (ptr->left == NULL) {
                        // cout << "Nu exista\n";
                        return NULL;
                    }
                    ptr = ptr->left;
                } else {
                    if (ptr->right == NULL) {
                        // cout << "Nu exista\n";
                        return NULL;
                    }
                    ptr = ptr->right;
                }
            }
            // cout << "S-a gasit la adresa " << ptr << '\n';
            return ptr;
        }
        void delete_node(int x) {
            if (priority == 0) {
                // cout << "Treap-ul este gol!";
                return;
            }

            Treap* ptr = get_root();
            while (ptr->data != x) {
                if (ptr->data > x) {
                    if (ptr->left == NULL) {
                        // cout << "Nu exista\n";
                        return;
                    }
                    ptr = ptr->left;
                } else {
                    if (ptr->right == NULL) {
                        // cout << "Nu exista\n";
                        return;
                    }
                    ptr = ptr->right;
                }
            }

            while (ptr->left != NULL || ptr->right != NULL) {

                if (ptr->left == NULL) {
                    rotate_with_parent(ptr->right);
                } else 

                if (ptr->right == NULL) {
                    rotate_with_parent(ptr->left);
                } else

                if (ptr->right->priority > ptr->left->priority) {
                    rotate_with_parent(ptr->right);     
                } else 
                
                {rotate_with_parent(ptr->left);
                }
            }

            if (ptr->parent->left = ptr) ptr->parent->left = NULL;
                else ptr->parent->right = NULL;
            delete ptr;
        }
        Treap* succesor(int x) {
            Treap *ptr = search(x);
            if (ptr == NULL) {
                // cout << "Nodul nu exista\n";
                return NULL;
            }

            if (ptr->left != NULL) {
                // cout << "Fiu stang: ";
                cout << ptr->left->data; 
                cout << " ";
            }
            if (ptr->right != NULL) {
                // cout << "Fiu drept: ";
                cout << ptr->right->data;
                cout << "\n";
            }
            if (ptr->left == NULL && ptr->right == NULL) {
                // cout << "Nodul nu are fii\n";
            }
            return ptr->left;
        } 
        Treap* predecesor(int x) {
            Treap *ptr = search(x);
            if (ptr->parent == NULL) {
                // cout << "Nodul este radacina\n";
                return NULL;
            }

            // cout << "Tatal nodului este " << ptr->parent->data << "\n";
            return ptr->parent;
        }
        void afisare_sortat(Treap* root) {
            if (root == NULL) return;
            afisare_sortat(root->left);
            cout << *root;
            afisare_sortat(root->right);
        }


};

int main() {
    srand(time(NULL));
    Treap x;
    Treap *p = &x;
    x.insert(7);
    x.insert(4);
    x.insert(6);
    x.search(10);
    x.search(7);
    x.succesor(4);
    x.predecesor(7);
    x.afisare_sortat(x.get_root());
    return 0;
}