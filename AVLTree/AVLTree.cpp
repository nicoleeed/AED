#include <iostream>
#include <queue>
#include<iomanip>
#include <stack>
#include <vector>
#include<cmath>
using namespace std;
template<class T>
class Node {
	public:
		T value;
		Node* next;
		int status;

		Node(T v, Node* n) {
			value = v;
			next = n;
			status = 0;
		}
};

template<class T>
class Pila {
	public:
		Node<T>* head;
	
		Pila() {
			head = nullptr;
		}

		bool Push(T x) {
			if (!head) {
				head = new Node<T>(x, head);
				return 1;
			}
			if (x == head->value) {
				head->status++;
				return 1;
			}
			head = new Node<T>(x, head);
			return 1;
		}
	
		int headStatus() {
			return head->status;
		}
	
		T Pop() {
			if (!head) {
				cout << "Empty Pila" << endl;
				return 0;
			}
			if (head->status != 3) return 0;
			Node<T>* temp = head;
			T r = head->value;
			head = head->next;
			delete temp;
			return r;
		}
	
		~Pila() {
			Node<T>** p;
			for (p = &head; *p; ) {
				Node<T>* t = *p;
				*p = (*p)->next;
				delete(t);
			}
		}
	
		void Print() {
			if (head->status == 1)
				cout << head->status << "  ";

		}
};

template<class T>
class BNode {
public:
	T value;
	BNode* next;
	BNode* prev;
	int pos;
	int nivel;
	bool empty;
	BNode(T v, int pos_, int niv, bool emp, BNode* n = nullptr, BNode* p = nullptr) {
		value = v;
		next = n;
		prev = p;
		pos = pos_;
		nivel = niv;
		empty = emp;
	}
};

template<class T>
class Cola {
	public:
		BNode<T>* head;
		BNode<T>* tail;

		Cola() {
			head = nullptr;
			tail = nullptr;
		}
	
		int Size() {
			int cont = 0;
			for (BNode<T>* p = head; p; p = p->next) {
				cont++;
			}
			return cont;
		}
	
		bool Push(T x, int p, int n, bool em) {
			if (!head) {
				head = new BNode<T>(x, p, n, em, head, nullptr);
				tail = head;
				return 1;
			}
			tail->next = new BNode<T>(x, p, n, em, tail->next, tail);
			tail = tail->next;
			return 1;
		}
	
		T Pop() {
			if (!head) {
				cout << "Empty Cola" << endl;
				return 0;
			}
			BNode<T>* temp = head;
			T r = head->value;
			head = head->next;
			if (head)  head->prev = NULL;
			delete temp;
			return r;
		}
	
		~Cola() {
			BNode<T>** p;
			for (p = &head; *p; ) {
				BNode<T>* t = *p;
				*p = (*p)->next;
				delete(t);
			}
		}
	
		void Print() {
			if (!head) {
				cout << "Empty Cola" << endl;
			}
			else {
				cout << "||<-";
				BNode<T>* i = head;
				for (; i && i->next; i = i->next) {
					cout << i->value->value << "<=>";
				}
				cout << i->value->value << "->";
				cout << "|| " << endl;
			}

		}
};

template<class T>
class asc {
	public:
		bool operator()(T a, T b) {
			return a < b;
		}
};

template<class T>
class desc {
	public:
		bool operator()(T a, T b) {
			return a > b;
		}
}; 

template<class T>
class BinaryNode {
	public:
		T value;
		BinaryNode* nodes[2];
		int alt;

		BinaryNode(T v) {
			value = v;
			nodes[0] = NULL;
			nodes[1] = NULL;
			alt = 0;
		}
};

template<class T, class R>
class AVLTree {
	private:
		bool rand = 0;
		R r;
	
		BinaryNode<T>** Replace(BinaryNode<T>** p) {
			for (p = &(*p)->nodes[rand]; (*p)->nodes[!rand]; p = &((*p)->nodes[!rand]));
			rand = (!rand);
			return p;
		}
	
		bool Find(T x, BinaryNode<T>**& p, stack<BinaryNode<T>*>& nodos) {
			for (p = &Root; *p && (*p)->value != x; p = &(*p)->nodes[!r(x, (*p)->value)]) {
					nodos.push(*p);
			}
			if (*p == nullptr) {
				nodos.push(Root);
			}
			return *p && (*p)->value == x;
		}
		bool Find1(T val, BinaryNode<T>**& p, stack<BinaryNode<T>**>& s) {
			for (p = &Root; *p && (*p)->value != val; p = &((*p)->nodes[val > (*p)->value])) s.push(p);
			return *p;
		}
	
	public:
		BinaryNode<T>* Root;

		AVLTree() {
			Root = nullptr;
		}

		int tam(BinaryNode<T>* nodo) const {
			return (nodo == NULL) ? 0 : tam(nodo->nodes[0]) + tam(nodo->nodes[1]) + 1;
		}
	
		int H(BinaryNode<T>* u) { return u ? u->alt : 0; }

		int value(BinaryNode<T>* u) { return H(u->nodes[0]) - H(u->nodes[1]); }

		void update(BinaryNode<T>* u) { u->alt = 1 + max(H(u->nodes[0]), H(u->nodes[1])); }

		void move(BinaryNode<T>** u, int w) {
			BinaryNode<T>* a = *u, * b;
			*u = (*u)->nodes[w];
			b = (*u)->nodes[!w];
			(*u)->nodes[!w] = a;
			a->nodes[w] = b;
			update((*u)->nodes[!w]);
			update(*u);
		}

		void balance(BinaryNode<T>** u, T val) {
			update(*u);
			int b = value(*u);
			if (b > 1) {
				if (value((*u)->nodes[0]) < 0) move(&((*u)->nodes[0]), 1);
				return move(u, 0);
			}
			if (b < -1) {
				if (value((*u)->nodes[1]) > 0) move(&((*u)->nodes[1]), 0);
				return move(u, 1);
			}
		}

		void Insert(T val) {
			BinaryNode<T>** p;
			stack<BinaryNode<T>**> path;
			if (!Find1(val, p, path)) {
				*p = new BinaryNode<T>  (val);
				while (!path.empty()) {
					balance(path.top(), val);
					path.pop();
				}
			}
		}

		void Remove(T val) {
			BinaryNode<T>** p;
			stack<BinaryNode<T>**> path;
			if (Find1(val, p, path)) {
				BinaryNode<T>** q = p;
				if ((*p)->nodes[0] && (*p)->nodes[1]) {
					int w = 0;
					path.push(p);
					for (q = &((*p)->nodes[w]); (*q)->nodes[!w]; q = &((*q)->nodes[!w])) path.push(q);
					(*p)->value = (*q)->value;
				}
				BinaryNode<T>* tmp = *q;
				*q = (*q)->nodes[!(*q)->nodes[0]];
				delete tmp;
				while (!path.empty()) {
					balance(path.top(), val);
					path.pop();
				}
			}
		}

		void Inorder(BinaryNode<T>* p) {
			if (!p) return;
			Inorder(p->nodes[0]);
			cout << p->value << "  ";
			Inorder(p->nodes[1]);
		}
	
		void Preorder(BinaryNode<T>* p) {
			if (!p) return;
			cout << p->value << "  ";
			Preorder(p->nodes[0]);
			Preorder(p->nodes[1]);
		}
	
		void Postorder(BinaryNode<T>* p) {
			if (!p) return;
			Postorder(p->nodes[0]);
			Postorder(p->nodes[1]);
			cout << p->value << "  ";
		}
	
		void Reverse(BinaryNode<T>* p) {
			if (!p) return;
			Reverse(p->nodes[1]);
			cout << p->value << "  ";
			Reverse(p->nodes[0]);
		}

		void InorderPila(BinaryNode<T>* p) {
			Pila<T> pila;
			pila.Push(p->value);
			p = p->nodes[0];
			while (pila.head && p) {
				pila.Push(p->value);
				int status = pila.headStatus();
				if (status == 0) {
					if (p->nodes[0] == nullptr) continue;
					p = p->nodes[0];
				}
				else if (status == 1) {
					cout << p->value << "  ";
					if (p->nodes[0] == nullptr) continue;
				}
				else if (status == 2) {
					if (p->nodes[1] == nullptr) continue;
					p = p->nodes[1];
				}
				else {
					pila.Pop();
					if (pila.head) {
						BinaryNode<T>** q;
						stack<BinaryNode<T>*> nodos;
						Find(pila.head->value, q,  nodos);
						p = *q;
					}

				}
			}
			cout << endl;
		}
	
		void PreorderPila(BinaryNode<T>* p) {
			Pila<T> pila;
			pila.Push(p->value);
			cout << p->value << "  ";
			while (pila.head && p) {
				pila.Push(p->value);
				int status = pila.headStatus();
				if (status == 0) {
					cout << p->value << "  ";
					if (p->nodes[0] == nullptr) continue;
				}
				else if (status == 1) {
					if (p->nodes[0] == nullptr) continue;
					p = p->nodes[0];
				}
				else if (status == 2) {
					if (p->nodes[1] == nullptr) continue;
					p = p->nodes[1];
				}
				else if (status == 3) {
					pila.Pop();
					if (pila.head) {
						BinaryNode<T>** q;
						stack<BinaryNode<T>*> nodos;
						Find(pila.head->value, q, nodos);
						p = *q;
					}
				}
			}
			cout << endl;
		}

		void PostorderPila(BinaryNode<T>* p) {
			Pila<T> pila;
			pila.Push(p->value);
			p = p->nodes[0];
			while (pila.head && p) {
				pila.Push(p->value);
				int status = pila.headStatus();
				if (status == 0) {
					if (p->nodes[0] == nullptr) continue;
					p = p->nodes[0];
				}
				else if (status == 1) {
					if (p->nodes[1] == nullptr) continue;
					p = p->nodes[1];
				}
				else if (status == 2) {
					cout << p->value << "  ";
					if (p->nodes[0] == nullptr) continue;
				}
				else {
					pila.Pop();
					if (pila.head) {
						BinaryNode<T>** q;
						stack<BinaryNode<T>*> nodos;
						Find(pila.head->value, q, nodos);
						p = *q;
					}

				}
			}
			cout << endl;
		}
	
		void ReversePila(BinaryNode<T>* p) {
			Pila<T> pila;
			pila.Push(p->value);
			p = p->nodes[1];
			while (pila.head && p) {
				pila.Push(p->value);
				int status = pila.headStatus();
				if (status == 0) {
					if (p->nodes[1] == nullptr) continue;
					p = p->nodes[1];
				}
				else if (status == 1) {
					cout << p->value << "  ";
					if (p->nodes[1] == nullptr) continue;
				}
				else if (status == 2) {
					if (p->nodes[0] == nullptr) continue;
					p = p->nodes[0];
				}
				else {
					pila.Pop();
					if (pila.head) {
						BinaryNode<T>** q;
						stack<BinaryNode<T>*> nodos;
						Find(pila.head->value, q, nodos);
						p = *q;
					}
				}
			}
			cout << endl;
		}

		void ImpresionGrafica(BinaryNode<T>* p) {
			Cola<BinaryNode<T>*> colaNodos;
			int nivel = 0;
			int cont = tam(Root);
			int techo = log2(cont + 1);
			colaNodos.Push(p, techo * techo, nivel, 1);

			BNode< BinaryNode<T>*>* pp = colaNodos.head;
			BinaryNode<T> emp(0);
			BinaryNode<T>* e = &emp;
			Cola<char> colaFlechas;
			colaFlechas.Push(' ', techo * techo, nivel, 1);
			BNode<char>* qq = colaFlechas.head;
			while (cont > 1) {
				BinaryNode<T>* aux = pp->value;
				int a = 0;
				if (aux->nodes[0]) {
					colaNodos.Push(aux->nodes[0], pow(2, log2(tam(aux->nodes[0]) + 1)), pp->nivel + 1, 1);
					cont--;
					colaFlechas.Push('/', colaNodos.tail->pos, pp->nivel + 1, 1);
				}
				if (!aux->nodes[0]) {
					colaNodos.Push(e, pow(2, log2(tam(aux->nodes[0]) + 1)), pp->nivel + 1, 0);
					colaFlechas.Push(' ', colaNodos.tail->pos, pp->nivel + 1, 0);
				}
				if (aux->nodes[1]) {
					colaNodos.Push(aux->nodes[1], pow(2, log2(tam(aux->nodes[1]) + 1)), pp->nivel + 1, 1);
					cont--;
					colaFlechas.Push('\\', colaNodos.tail->pos, pp->nivel + 1, 1);
				}
				if (!aux->nodes[1]) {
					colaNodos.Push(e, pow(2, log2(tam(aux->nodes[1]) + 1)), pp->nivel + 1, 0);
					colaFlechas.Push(' ', colaNodos.tail->pos, pp->nivel + 1, 0);
				}
				pp = pp->next;
				qq = qq->next;
			}
			BNode<char>* r = colaFlechas.head;
			r = r->next;
			int max = 2;
			for (BNode< BinaryNode<T>*>* i = colaNodos.head; i; i = i->next) {
				BinaryNode<T>* aux = i->value;
				int a = i->pos;
				while (a > 0) {
					cout << " ";
					a--;
				}
				if (i->empty == 0) { cout << " "; }
				else { cout << aux->value; }
				if (i->next && i->next->nivel != i->nivel) {
					cout << endl;
					for (; r->nivel == i->nivel + 1 && r->next; r = r->next) {
						int a = r->pos;
						while (a > 0) {
							cout << " ";
							a--;
						}
						cout << r->value;
					}
					if (r && !r->next) {
						int a = r->pos;
						while (a > 0) {
							cout << " ";
							a--;
						}
						cout << r->value;
					}
					cout << endl;
				}
			}
		}
	
		int PrintHojas(BinaryNode<T>* p) {
			int cont = 0;
			Pila<T> pila;
			pila.Push(p->value);
			p = p->nodes[0];
			cout << " Las hojas de este arbol son { ";
			while (pila.head && p) {
				pila.Push(p->value);
				int status = pila.headStatus();
				if (status == 0) {
					if (p->nodes[0] == nullptr) continue;
					p = p->nodes[0];
				}
				else if (status == 1) {
					if ((!p->nodes[0] && !p->nodes[1])) {
						cout << p->value << " , ";
						cont++;
					}
					if (p->nodes[0] == nullptr) continue;
				}
				else if (status == 2) {
					if (p->nodes[1] == nullptr) continue;
					p = p->nodes[1];
				}
				else {
					pila.Pop();
					if (pila.head) {
						BinaryNode<T>** q;
						stack<BinaryNode<T>*> nodos;
						Find(pila.head->value, q, nodos);
						p = *q;
					}
				}
			}
			cout << " }" << endl;
			return cont;
		}

		int PrintRamas(BinaryNode<T>* p) {
			int cont = 0;
			Pila<T> pila;
			pila.Push(p->value);
			p = p->nodes[0];
			cout << " Las ramas de este arbol son { ";
			while (pila.head && p) {
				pila.Push(p->value);
				int status = pila.headStatus();
				if (status == 0) {
					if (p->nodes[0] == nullptr) continue;
					p = p->nodes[0];
				}
				else if (status == 1) {
					if (p != Root) {
						if ((p->nodes[0] && p->nodes[1]) || (!p->nodes[0] && p->nodes[1]) || (p->nodes[0] && !p->nodes[1])) {
							cout << p->value << " , ";
							cont++;
						}
					}
					if (p->nodes[0] == nullptr) continue;
				}
				else if (status == 2) {
					if (p->nodes[1] == nullptr) continue;
					p = p->nodes[1];
				}
				else {
					pila.Pop();
					if (pila.head) {
						BinaryNode<T>** q;
						stack<BinaryNode<T>*> nodos;
						Find(pila.head->value, q, nodos);
						p = *q;
					}
				}
			}
			cout << " }" << endl;
			return cont;
		}

		void del(BinaryNode<T>* p) {
			if (!p) return;
			if (p->nodes[0]) del(p->nodes[0]);
			if (p->nodes[1]) del(p->nodes[1]);
			delete p;
		}

		~AVLTree() {
			del(Root);
			Root = nullptr;
		}
	
}; 
int main() {
	AVLTree<int, asc<int>> a;

	cout << "------ AVL TREE -------" << endl;
	cout << "  1 = Insert" << endl;
	cout << "  2 = Remove" << endl;
	cout << "  3 = PreOrder" << endl;
	cout << "  4 = InOrder" << endl;
	cout << "  5 = PostOrder" << endl;
	cout << "  6 = Reverse" << endl;
	cout << "  7 = Niveles" << endl;
	cout << "  8 = Hojas" << endl;
	cout << "  9 = Ramas" << endl;
	cout << "  10 = Total Nodos" << endl;
	cout << "  11 = Eliminar Arbol" << endl;
	cout << "  0 = Terminar" << endl;
	cout << endl;


	bool code = true;
	int tecla;
	while (code) {
		cout << endl;
		cout << "- Chose an a option: ";
		cin >> tecla;
		cout << endl;

		switch (tecla) {
		case 1:
			int numero;
			cout << "Insert: ";
			cin >> numero;
			a.Insert(numero);
			break;

		case 2:
			int numero2;
			cout << "Remove: ";
			cin >> numero2;
			a.Remove(numero2);
			break;

		case 3:
			cout << "PreOrder" << endl;
			cout << "PreOrder recursivo:  "; a.PreorderPila(a.Root);
			cout << endl;
			cout << "PreOrder pila:  "; a.Preorder(a.Root);
			cout << endl;
			break;

		case 4:
			cout << "InOrder" << endl;
			cout << "InOrder recursivo:  "; a.InorderPila(a.Root);
			cout << endl;
			cout << "InOrder pila:  "; a.Inorder(a.Root);
			cout << endl;
			break;

		case 5:
			cout << "PostOrder" << endl;
			cout << "PostOrder recursivo:  "; a.Postorder(a.Root);
			cout << endl;
			cout << "PostOrder pila:  "; a.Postorder(a.Root);
			cout << endl;
			break;

		case 6:
			cout << "Reverse" << endl;
			cout << "Reverse recursivo:  "; a.ReversePila(a.Root);
			cout << endl;
			cout << "Reverse pila:  ";  a.Reverse(a.Root);
			cout << endl;
			break;

		case 7:
			cout << "Niveles" << endl;
			cout << "Niveles cola:  " << endl; a.ImpresionGrafica(a.Root);
			cout << endl;
			break;

		case 8:
			cout << "El numero de hojas es: " << a.PrintHojas(a.Root) << endl;
			break;

		case 9:
			cout << "El numero de ramas es: " << a.PrintRamas(a.Root) << endl;
			break;

		case 10:
			cout << "El numero de nodos de este arbol es: " << a.tam(a.Root) << endl;
			a.Inorder(a.Root);
			cout << endl;
			break;

		case 11:
			a.~AVLTree();
			cout << "Arbol vacio" << endl;
			break;
		case 0:
			code = false;
			break;
		}
	}
}