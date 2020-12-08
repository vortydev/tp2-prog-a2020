/*
 * Auteur:		Étienne Ménard
 * Date:		11/11/2020 (Joyeuse journée du souvenir)
 * Fichier:		list.hpp
 * Description:	Structure de données dynamique que l'on peut manipuler à l'aider d'un itérateur explicite.
 */

#pragma once
#include <cassert>

template <typename TYPE> class list;
//CLASSE CELLULE
template <typename TYPE>
class cellule
{
	friend class list<TYPE>;	//la seule classe ayant accès à la 
								//représentation de la cellule
	TYPE element;				//Contenu de la cellule
	cellule <TYPE>* next;		//Pointeur vers la cellule suivante 
	cellule <TYPE>* previous;	//Pointeur vers la cellule precedente

	cellule(const TYPE& e, cellule<TYPE>* n = nullptr, cellule<TYPE>* p = nullptr)
	{
		element = e;
		next = n;
		previous = p;
	}
};

template <typename TYPE>
class list
{
private:
	cellule <TYPE>* _first;			//Adresse du premier élément 

	list(const list<TYPE>& l);		//Copieur désactivé
public:
	class iterator
	{
		friend class list<TYPE>;
	private:
		cellule<TYPE>* _current;		//adresse de la cellule
		const list<TYPE>* _list;		//adresse de la liste
	public:
		iterator();					//constructeur
		~iterator();				//destructeur

		const iterator& operator=(const iterator& it); //pour j=i

		bool operator==(const iterator& it)const; //pour if(j==i)
		bool operator!=(const iterator& it)const; //pour if(j!=i)

		iterator operator++(int i);			//i++
		const iterator& operator++();		//++i

		iterator operator--(int i);			//i--
		const iterator& operator--();		//--i

		iterator operator+(int i);	// surcharge (optionelle) de l'opérateur +

		TYPE& operator*();				//accès à un élément
		const TYPE& operator*()const;		//idem, en mode const

	};

	list(void);	// constructeur
	~list(void); // destructeur

	void clear();
	bool empty()const;

	iterator begin()const;			//return premier
	iterator end()const;			//return nullptr

	iterator insert(iterator it, const TYPE& element);
	iterator erase(iterator it);
	iterator erase(iterator first, iterator last);

	TYPE& operator[](iterator it);		//pas ds la STL
	const TYPE& operator[](iterator it)const;

	//chercher dans la liste l’élément reçu en paramètre
	//et à partir de l’itérateur reçu pour la version 2
	//la méthode  retourne un iterator sur l’element trouvé
	//s’il est innexistant, l’iterator est à la fin 
	iterator operator()(const TYPE& ele)const; 
	iterator operator()(const TYPE& ele, iterator it)const;

	const list<TYPE>& operator=(const list<TYPE>& l);
};

/* 
 * MÉTHODES DE L'ITÉRATEUR 
 */

// Constructeur d'itérateur
template <typename TYPE>
list<TYPE>::iterator::iterator() {
	_current = nullptr;
	_list = nullptr;
}

// Destructeur d'itérateur
template <typename TYPE>
list<TYPE>::iterator::~iterator() {
	_current = nullptr;
	_list = nullptr;
}

// affectateur d'itérateur =
template <typename TYPE>
typename const list<TYPE>::iterator& list<TYPE>::iterator::operator=(const iterator& it) {
	assert(_list == it._list);
	assert(_list != nullptr);

	_current = it._current;

	return *this;
}

// Surcharge de l'opérateur ==
template <typename TYPE>
bool list<TYPE>::iterator::operator==(const iterator& it)const {
	assert(_list != nullptr);	// si positionné
	assert(_list == it._list); // s'assure que l'itérateur est dans la bonne liste

	return _current == it._current;
}

// Surcharge de l'opérateur !=
template <typename TYPE>
bool list<TYPE>::iterator::operator!=(const iterator& it)const {
	assert(_list != nullptr);	// si positionné
	assert(_list == it._list); // s'assure que l'itérateur est dans la bonne liste

	return _current != it._current;
}

// Surcharge de l'opérateur ++ (i++)
template <typename TYPE>
typename list<TYPE>::iterator list<TYPE>::iterator::operator++(int i) {
	iterator it(*this);
	operator++();
	return it;
}

// Surcharge de l'opérateur ++ (++i)
template <typename TYPE>
const typename list<TYPE>::iterator& list<TYPE>::iterator::operator++() {
	assert(_list != nullptr); // it positionné
	assert(_current != nullptr); //it pas à la fin de la liste
	assert(!_list->empty()); // la liste n'est pas vide

	if (_current == _list->_first->previous)
		_current = nullptr;
	else
		_current = _current->next;

	return *this;
}

// Surcharge de l'opérateur -- (i--)
template <typename TYPE>
typename list<TYPE>::iterator list<TYPE>::iterator::operator--(int i) {
	iterator it(*this);
	operator--();
	return it;
}

// Surcharge de l'opérateur -- (--i)
template <typename TYPE>
const typename list<TYPE>::iterator& list<TYPE>::iterator::operator--() {
	assert(_list != nullptr); // it positionné
	assert(_current != _list->_first); // it pointe sur quelque chose
	assert(!_list->empty());

	if (_current == nullptr)
		_current = _list->_first->previous;
	else
		_current = _current->previous;

	return *this;
}

// Surcharge de l'opérateur +
template <typename TYPE>
typename list<TYPE>::iterator list<TYPE>::iterator::operator+(int i) {
	while (_current != _list->end() && i > 0) {
		operator++();
		i--;
	}

	return *this;
}

// setteur
template <typename TYPE>
TYPE& list<TYPE>::iterator::operator*() {
	assert(_list != nullptr); // it positionné
	assert(_current != nullptr);
	assert(_list->_first != nullptr);

	return _current->element;
}

// Retourne l'élément où est l'itérateur en constante référence
template <typename TYPE>
const TYPE& list<TYPE>::iterator::operator*()const {
	assert(_list != nullptr && _current != nullptr); //Itérateur positionné
	assert(_list->_first != nullptr); 			  //liste non vide

	return _current->element;
}

/* 
 * MÉTHODES DE LA LISTE 
 */

// Constructeur de la liste
template <class TYPE>
list<TYPE>::list(void) {
	_first = nullptr;
}

// Destructeur de la liste
template <class TYPE>
list<TYPE>::~list(void) {
	clear();
}

// Retourne si la liste est vide
template <class TYPE>
bool list<TYPE>::empty()const {
	return _first == nullptr;
}

// Vide la liste
template <class TYPE>
void list<TYPE>::clear() {
	while (!empty())
		erase(begin());
}

// place l'itérateur au début de la liste
template <typename TYPE>
typename list<TYPE>::iterator list<TYPE>::begin()const {
	iterator it;

	it._current = _first;
	it._list = this;

	return it;
}

// place l'itérateur à la fin de la liste
template <typename TYPE>
typename list<TYPE>::iterator list<TYPE>::end()const {
	iterator it;

	it._current = nullptr;
	it._list = this;

	return it;
}

// Insère une valeur dans la liste
template <typename TYPE>
typename list<TYPE>::iterator list<TYPE>::insert(typename list<TYPE>::iterator it, const TYPE& element) {
	assert(it._list == this); // est-ce que l'addresse de la liste est la même que moi-même?

	if (empty()) // si la liste est vide
		it._current = _first->previous = _first = new cellule<TYPE>(element);
	else if (it._current == nullptr) // itérateur à la fin (push_back)
		it._current = _first->previous = _first->previous->next = new cellule<TYPE>(element, nullptr, _first->previous);
	else if (it._current == _first)	// itérateur au début (push_front)
		it._current = _first = _first->previous = new cellule<TYPE>(element, _first, _first->previous);
	else // itérateur au milieu
		it._current = it._current->previous = it._current->previous->next = new cellule<TYPE>(element, it._current, it._current->previous);

	return it;
}

// Efface une cellule dans la liste et modifie les cellules pour maintenir le chainage
template <typename TYPE>
typename list<TYPE>::iterator list<TYPE>::erase(typename list<TYPE>::iterator it) {
	assert(it._list == this);
	assert(it._current != nullptr);
	assert(!empty());
	
	cellule<TYPE>* trash = it._current;

	if (_first->previous == _first) // _first->next == nullptr // dernière cellule
		it._current = _first = nullptr;
	else if (it._current == _first) { // erase la première cellule
		_first->next->previous = _first->previous;
		it._current = _first = _first->next;
	}
	else if (it._current == _first->previous) { // erase la dernière cellule
		_first->previous->previous->next = nullptr;
		it._current = _first->previous = _first->previous->previous;
	}
	else {
		it._current->next->previous = it._current->previous;
		it._current = it._current->previous->next = it._current->next;
	}

	delete trash;
	return it;
}

// Efface les éléments du premier au deuxième itérateur
template <typename TYPE>
typename list<TYPE>::iterator list<TYPE>::erase(typename list<TYPE>::iterator first, typename list<TYPE>::iterator last) {
	assert(last._list != nullptr); // last pointe sur une liste
	assert(last._list == first._list); // même liste que first

	while (first != end() && first != last) 
		first = erase(first);
	if (first != end())
		first = erase(first);

	return first;
}

// surcharge de l'opérateur []
template <class TYPE>
TYPE& list<TYPE>::operator[](iterator it) {
	assert(it._list == this);

	return *it;
}

// surcharge de l'opérateur  [] const
template <class TYPE>
const TYPE& list<TYPE>::operator[](iterator it)const {
	assert(it._list == this);

	return *it;
}

// surcharge de l'opérateur ()
template <typename TYPE>
typename list<TYPE>::iterator list<TYPE>::operator()(const TYPE& ele, iterator it)const {
	assert(it._list == this);

	while (it != end()) {
		if (*it == ele)
			return it;
		it++;
	}
	
	return it;
}

// surcharge de l'opérateur () const
template <typename TYPE>
typename list<TYPE>::iterator list<TYPE>::operator()(const TYPE& ele)const {
	return operator()(ele, begin());
}

// affectateur de liste
template <class TYPE>
const list<TYPE>& list<TYPE>::operator=(const list<TYPE>& l) {
	if (this == &l)
		return *this;

	clear();

	iterator itExp = l.begin();
	while (!l.empty()) {
		insert(end(), *itExp);
		itExp++;
	}

	return *this;
}