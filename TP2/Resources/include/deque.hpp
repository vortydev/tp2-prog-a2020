/*
 * Auteur:		�tienne M�nard
 * Date:		05/11/2020
 * Fichier:		deque.hpp
 * Description:	Structure dynamique de type FIFO et LIFO o� l'on a acc�s qu'au premier et dernier �l�ments.
 */

#pragma once
#include <cassert>

template <class TYPE>
class deque {
private:
	struct cellule {
		TYPE element;
		cellule* next,
				prev;
		
		cellule(const TYPE& e, cellule* n = nullptr, cellule* p = nullptr) {
			element = e;
			next = n;
			prev = p;
		}
	};

	cellule* _deque;

	cellule*& FRONT() {
		assert(!empty());
		return _queue->next;
	}

	deque(const deque& dq); // disable le copieur

public:
	deque();	// constructeur sans param�tres
	~deque();	// destructeur

	bool empty()const;			// return si la deque est vide
	void clear();				// vide la deque
	const TYPE& front()const;	// retournes la t�te de la file
	const TYPE& back()const;	// retournes la fin de la file

	TYPE pop_front();						// delete la premi�re valeur de la deque
	TYPE pop_back();						// delete la derni�re valeur de la deque
	void push_front(const TYPE& element);	// push une valeur au d�but de la deque
	void push_back(const TYPE& element);	// push une valeur � la fin de la deque

	int size()const;										// retourne la grosseur de la file
	const deque<TYPE>& operator=(const deque<TYPE>& dq);	// affectateur
	
};

// Constructeur
template <class TYPE>
deque<TYPE>::deque() {
	_deque = nullptr;
}

// Destructeur
template <class TYPE>
deque<TYPE>::~deque() {
	clear();
}

// Return si la deque est vide
template <class TYPE>
bool deque<TYPE>::empty()const {
	return _deque == nullptr;
}

// Vide la deque
template <class TYPE>
void deque<TYPE>::clear() {
	while (!empty()) {
		pop_back();// todo
	}
}

// Retournes la t�te
template <class TYPE>
const TYPE& deque<TYPE>::front()const {
	assert(!empty());
	return FRONT()->element;
}

// Retournes la fin
template <class TYPE>
const TYPE& deque<TYPE>::back()const {
	assert(!empty());
	return _deque->element;
}

// Delete la premi�re valeur de la deque
template <class TYPE>
TYPE deque<TYPE>::pop_front() {
	assert(!empty());

	TYPE element = FRONT()->element;
	cellule* trash = FRONT();

	if (_deque == FRONT())
		_deque = nullptr;
	else {
		FRONT()->next->prev = _deque;
		_deque->next = FRONT()->next;
	}

	delete trash;
	return element;
}

// Delete la derni�re valeur de la deque
template <class TYPE>
TYPE deque<TYPE>::pop_back() {
	assert(!empty());

	TYPE element = _deque->element;
	cellule* trash = _deque;

	if (_deque == FRONT())
		_deque = nullptr;
	else {
		_deque->prev->next = FRONT();
		_deque = _deque->next->prev = _deque->prev;
	}

	delete trash;
	return element;
}

// Push une valeur � la fin de la deque
template <class TYPE>
void deque<TYPE>::push_back(const TYPE& e) {
	if (empty())
		_deque->prev = FRONT() = _deque = new cellule(e);
	else
		_deque = FRONT() = FRONT()->prev = new cellule(e, FRONT(), _deque);
}

// Push une valeur au devant de la deque
template <class TYPE>
void deque<TYPE>::push_front(const TYPE& e) {
	if (empty())
		_deque->prev = FRONT() = _deque = new cellule(e);
	else
		FRONT() = FRONT()->prev = new cellule(e, FRONT(), _deque);
}

// Retourne la grosseur de la queue
template <class TYPE>
int deque<TYPE>::size()const {
	if (empty()) // cas limite
		return 0;

	cellule* it = _deque;
	int size = 0;
	do {
		size++;
		it = it->next;
	} while (it != _deque);

	return size;
}

// Affectateur
template <class TYPE>
const deque<TYPE>& deque<TYPE>::operator=(const deque<TYPE>& dq) {
	if (this == &dq)
		return *this;

	clear();
	if (!dq.empty()) {
		cellule* itExp = dq.FRONT();
		do {
			push_back(itExp->element);
			itExp = itExp->next;
		} while (itExp != dq.FRONT());
	}

	return *this;
}