/*
 * Auteur:		Étienne Ménard
 * Date:		02/09/2020
 * Fichier:		vecteur.h
 * Description:	Déclare les méthodes de l'objet vecteur
 */
#pragma once
#include <iostream>
#include <cassert>

using namespace std;

template <class TYPE>
class vecteur
{
	private:
		TYPE* _tab; // addresse du vecteur
		int _size; // dimension du vecteur

	public:
		// constructeurs, copeiur et destructeur
		vecteur();
		vecteur(int size);
		vecteur(const vecteur<TYPE>& v);
		~vecteur();

		// méthodes du vecteur
		void push_back(const TYPE& value);					// ajoutes une valeur à la fin du vecteur
		void print(ostream& output)const;					// print le contenu du vecteur
		int size()const;									// retourne la grosseur du vecteur
		void resize(int newSize);							// redimensionne le vecteur
		void clear();										// delete le vecteur et set le pointer a null
		TYPE& at(int pos)const;									// return la valeur à la position en paramètre
		void inverse();										// inverse le contenu du vecteur
		void inverseRecursive(int pos = 0);						// inverse récursivement le contenu du vecteur
		
		// surcharges d'opérateurs
		TYPE& operator[](int pos)const;
		const vecteur<TYPE>& operator=(const vecteur<TYPE>& v);
		bool operator==(const vecteur<TYPE>& v)const;
		vecteur<TYPE> operator+(const vecteur<TYPE>& v)const;
		const vecteur<TYPE>& operator+=(const vecteur<TYPE>& v);

		template <class TYPE>
		friend void swap(vecteur<TYPE>& v1, vecteur<TYPE>& v2);
};
// surcharge de l'opérateur <<
template <class TYPE>
ostream& operator<<(ostream& output, const vecteur<TYPE>& v) {
	v.print(output);
	return output;
}

// constructeur sans paramètres
template <class TYPE>
vecteur<TYPE>::vecteur() {
	_tab = nullptr;
	_size = 0;
}

// constructeur avec paramètres
template <class TYPE>
vecteur<TYPE>::vecteur(int size) {
	assert(size >= 0);
	_tab = nullptr;
	_size = size;

	if (_size > 0) _tab = new TYPE[_size];
}

// copieur
template <class TYPE>
vecteur<TYPE>::vecteur(const vecteur<TYPE>& v) {
	_size = v._size;
	_tab = nullptr;

	if (_size > 0) {
		_tab = new TYPE[_size];
		for (int i = 0; i < v._size; i++) {
			*(_tab + i) = *(v._tab + i);
		}
	}
}

// destructeur
template <class TYPE>
vecteur<TYPE>::~vecteur() {
	clear();
}

// rajoutes une valeur à la fin du vecteur
template <class TYPE>
void vecteur<TYPE>::push_back(const TYPE& value) {
	TYPE* newTab = new TYPE[_size + 1];
	for (int i = 0; i < _size; i++) {
		*(newTab + i) = *(_tab + i);
	}
	*(newTab + _size) = value;
	delete[] _tab;
	_size++;
	_tab = newTab;
}

// print le contenu du vecteur
template <class TYPE>
void vecteur<TYPE>::print(ostream& output)const {
	for (int i = 0; i < _size; i++) {
		cout << *(_tab + i) << " ";
	}
}

// retourne la grosseur du vecteur
template <class TYPE>
int vecteur<TYPE>::size()const {
	return _size;
}

// resize le vecteur
template <class TYPE>
void vecteur<TYPE>::resize(int newSize) {
	assert(newSize >= 0);

	if (newSize == _size) return;
	if (newSize == 0) {
		clear();
		return;
	}

	TYPE* newTab = new TYPE[newSize];
	for (int i = 0; i < _size && i < newSize; i++) { // remplis le nouveau tableau et drop les valeurs de trop
		*(newTab + i) = *(_tab + i);
	}
	delete[] _tab;
	_tab = newTab;
	_size = newSize;
}

// clear le vecteur
template <class TYPE>
void vecteur<TYPE>::clear() {
	delete[] _tab;
	_tab = nullptr;
	_size = 0;
}

// retourne la valeur du vecteur à la position entrée en paramètre
template <class TYPE>
TYPE& vecteur<TYPE>::at(int pos)const {
	assert(pos >= 0 && pos < _size);
	return *(_tab + pos);
}

// surcharge de l'opérateur []
template <class TYPE>
TYPE& vecteur<TYPE>::operator[](int pos)const {
	return at(pos);
}

// surcharge de l'opérateur =
template <class TYPE>
const vecteur<TYPE>& vecteur<TYPE>::operator=(const vecteur<TYPE>& v) {
	if (this == &v) return *this;
	clear();
	_size = v._size;

	if (v._size > 0) {
		_tab = new TYPE[_size];
		for (int i = 0; i < v._size; i++) {
			*(_tab + i) = *(v._tab + i);
		}
	}	
	return *this;
}

// surcharge de l'opérateur ==
template <class TYPE>
bool vecteur<TYPE>::operator==(const vecteur<TYPE>& v)const {
	if (_size != v._size) return false;

	for (int i = 0; i < _size; i++) {
		if (*(_tab + i) != *(v._tab + i)) return false;
	}
	return true;
}

// surcharge de l'opérateur +
template <class TYPE>
vecteur<TYPE> vecteur<TYPE>::operator+(const vecteur<TYPE>& v)const {
	vecteur newV(_size + v._size);

	for (int i = 0; i < _size; i++) {
		*(newV._tab + i) = *(_tab + i);
	}
	
	for (int i = 0; i < v._size; i++) {
		*(newV._tab + i + _size) = *(v._tab + i);
	}

	return newV;
}

//surcharge de l'opérateur +=
template <class TYPE>
const vecteur<TYPE>& vecteur<TYPE>::operator+=(const vecteur<TYPE>& v) {
	int oldSize = _size;
	int tempVsize = v._size;
	resize(_size + v._size);
	for (int i = 0; i < tempVsize; i++) {
		*(_tab + i + oldSize) = *(v._tab + i);
	}
	
	return *this;
}

// swap les deux vecteurs en paramètres
template <class TYPE>
void swap(vecteur<TYPE>& v1, vecteur<TYPE>& v2) {
	TYPE* tempV;
	int tempSize;

	tempV = v1._tab;
	tempSize = v1._size;

	v1._tab = v2._tab;
	v1._size = v2._size;

	v2._tab = tempV;
	v2._size = tempSize;
}

// inverse le contenu du vecteur
template <class TYPE>
void vecteur<TYPE>::inverse() {
	for (int i = 0; i < _size / 2; i++) {
		*(_tab + (_size - i - 1)) = *(_tab + i);
	}
}

// inverse le contenu du vecteur, mais récursivement!
template <class TYPE>
void vecteur<TYPE>::inverseRecursive(int pos) {
	assert(pos == 0);
	if (pos < _size / 2) {
		TYPE temp = *(_tab + pos);
		*(_tab + pos) = *(_tab + (_size - pos - 1));
		*(_tab + (_size - pos - 1)) = temp;
		inverseRecursive(pos + 1);
	}
}
