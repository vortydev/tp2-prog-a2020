/*
 * Auteur:		Étienne Ménard
 * Date:		05/10/2020
 * Fichier:		stack.hpp
 * Description:	Déclare les méthodes du stack
 */

#pragma once
#include <cassert>
using namespace std;

template <class TYPE>
class stack {
	private:
		struct cellule
		{
			TYPE element;	// élément de la cellule
			cellule* next;	// pointeur vers la prochaine cellule

			cellule(const TYPE& e, cellule* n = nullptr) 
			{
				element = e;
				next = n;
			}
		};
		cellule* _top;
		stack(const stack& s);				// désactiver le copieur
		cellule* copyCell(cellule* cell) {	// affectateur récursif
			if (cell == nullptr)
				return nullptr;
			return new cellule(cell->element, copyCell(cell->next));
		}
	public:
		stack();
		~stack();

		void push(const TYPE& e);	// ajoute un nouveau dessus
		void pop();					// enlève le dessus

		const TYPE& top() const;	// retourne le dessus, mais dépile pas
		TYPE& top();				// retourne le dessus, mais en setteur
		int size()const;			// retourne le nb d’élément

		bool empty() const;			// si la pile est vide
		void clear();				// vide la pile

		const stack& operator=(const stack& s);	// affectateur
		bool operator==(const stack& s)const;	// comparaison de 2 piles
};

// constructeur sans paramètres
template <class TYPE>
stack<TYPE>::stack() {
	_top = nullptr;
}

// destructeur
template <class TYPE>
stack<TYPE>::~stack() {
	clear();
}

// ajoutes un nouveau dessus
template <class TYPE>
void stack<TYPE>::push(const TYPE& e) {
	_top = new cellule(e, _top);
}

// enlève la cellule du dessus
template <class TYPE>
void stack<TYPE>::pop() {
	assert(!empty());
	cellule* newTop = _top->next; // store le pointeur de la prochaine cellule
	delete _top;
	_top = newTop;
}

// retourne l'élément de la cellule du dessus
template <class TYPE>
const TYPE& stack<TYPE>::top() const {
	assert(!empty());
	return _top->element;
}

// retourne l'élément de la cellule du dessus en setteur
template <class TYPE>
TYPE& stack<TYPE>::top() {
	assert(!empty());
	return _top->element;
}

// retourne la grosseur de la pile
template <class TYPE>
int stack<TYPE>::size() const {
	int size = 0;
	cellule* it = _top;
	while (it != nullptr) {
		size++;
		it = it->next;
	}
	return size;
}

// si la pile est vide
template <class TYPE>
bool stack<TYPE>::empty() const {
	return _top == nullptr;
}

// vide la pile
template <class TYPE>
void stack<TYPE>::clear() {
	while (!empty())
		pop();
}

// affectateur
template <class TYPE>
const stack<TYPE>& stack<TYPE>::operator=(const stack& s) {
	if (this == &s) 
		return *this; // cas limite
	
	clear();

	// _top = copyCell(s._top); affectateur récursif

	if (!s.empty()) {
		cellule* itImp = nullptr;
		cellule* itExp = s._top;
		itImp = _top = new cellule(itExp->element);

		itExp = itExp->next;
		while (itExp != nullptr) {
			itImp = itImp->next = new cellule(itExp->element);
			itExp = itExp->next;
		}
	}
	return *this;
}

// comparaison de 2 piles
template <class TYPE>
bool stack<TYPE>::operator==(const stack& s)const {
	cellule* itImp = _top;
	cellule* itExp = s._top;

	// boucle pour comparer le contenu
	while (itImp != nullptr && itExp != nullptr) {
		if (itImp->element != itExp->element) // si l'élément est différent dans les deux piles
			return false;
		itImp = itImp->next;
		itExp = itExp->next;
	}

	return itImp == itExp;
}