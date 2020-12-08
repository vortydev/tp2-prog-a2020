/*
 * Auteur:		Étienne Ménard
 * Date:		21/10/2020
 * Fichier:		queue.hpp
 * Description:	Structure dynamique de type FIFO. 
 */

#pragma once
#include <cassert>

template <class TYPE>
class queue {
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

	cellule* _queue; // pointe sur la dernière cellule
	
	cellule*& FRONT()const { // retourne la prochaine cellule de la queue, donc la première
		assert(!empty());
		return _queue->next;
	}

	queue(const queue& q); // disable le copieur

public:
	queue();	// Constructeur
	~queue();	// Destructeur

	void clear();				// Vide la file
	bool empty()const;			// Retourne si la file est vide

	const TYPE& front()const;	// Retourne la tête de la file
	void push(const TYPE& e);	// Ajoutes à la queue
	TYPE pop();					// Enlève la tête
	int size()const;			// Retourne la grosseur de la file
	
	const queue<TYPE>& operator=(const queue<TYPE>& q); // Affectateur
};

// Constructeur
template <class TYPE>
queue<TYPE>::queue() {
	_queue = nullptr;
}

// Destructeur
template <class TYPE>
queue<TYPE>::~queue() {
	clear();
}

// Vide la file
template <class TYPE>
void queue<TYPE>::clear() {
	while (!empty()) {
		pop();
	}
}

// Retourne si la pile est vide
template <class TYPE>
bool queue<TYPE>::empty() const {
	return _queue == nullptr;
}

// Retourne la tête
template <class TYPE>
const TYPE& queue<TYPE>::front()const {
	assert(!empty());
	return FRONT()->element;
}

// Ajoutes à la queue
template <class TYPE>
void queue<TYPE>::push(const TYPE& e) {
	if (empty()) // créé la 1ere cellule
		FRONT() = _queue = new cellule(e, nullptr);
	else
		_queue = _queue->next = new cellule(e, FRONT());
}

// Enlève la tête
template <class TYPE>
TYPE queue<TYPE>::pop() {
	assert(!empty());

	TYPE element = FRONT()->element;
	cellule* trash = FRONT();

	if (_queue == FRONT())
		_queue = nullptr;
	else
		_queue->next = _queue->next->next;

	delete trash;
	
	return element;
}

// Retourne la grosseur de la queue
template <class TYPE>
int queue<TYPE>::size()const {
	if (empty()) // cas limite
		return 0;

	cellule* it = _queue;
	int size = 0;
	do {
		size++;
		it = it->next;
	} while (it != _queue);

	return size;
}

// Affectateur
template <class TYPE>
const queue<TYPE>& queue<TYPE>::operator=(const queue<TYPE>& q) {
	if (this == &q)
		return *this;

	clear();
	if (!q.empty()) {
		cellule* itExp = q.FRONT();
		do {
			push(itExp->element);
			itExp = itExp->next;
		} while (itExp != q.FRONT());
	}

	return *this;
}