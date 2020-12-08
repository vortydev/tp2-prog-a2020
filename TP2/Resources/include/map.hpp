/*
 * Auteur:		�tienne M�nard
 * Date:		09/09/2020
 * Fichier:		map.hpp
 * Description:	D�clare les m�thodes de l'objet map
*/

#pragma once
#include <iostream>
#include <fstream>
#include <cassert>

template <class TYPE>
class mapp {
	private:
		char* _name;	// pointeur sur le nom de la map
		TYPE** _map;	// la map dynamique, en lignes et colonnes
		int _line,		// nombre de lignes
			_col;		// nombre de colonnes

	public:
		mapp();
		mapp(const char* name, int line, int col);
		mapp(const mapp<TYPE>& mapCopy);
		~mapp();

		void clear();						//clear la map et le nom
		void clearMap();					//clear la map et remet les dimensions � 0
		void clearName();					//clear le nom
		
		int nbLine()const;					//retourne le nb de ligne
		int nbCol()const;					//retourne le nb de colonne
		const char* getName()const;			//retourne le nom de la map
		void setName(const char* name);		//modifie le nom de la map
		void resize(int line, int col);		//resize la matrice avec les nouv. dims
		TYPE& at(int posI, int posJ)const;	//retourne une r�f�rence � l��l�ment
											//� la position i,j pour acc�der ou modifier
		void print(ostream& output)const;	//print la matrice (sans le nom)
		void read(istream& input);			//lit la matrice de la map ds le flux

		const mapp<TYPE>& operator=(const mapp<TYPE>& mapCopy);	// surcharge l'op�rateur =
		TYPE* operator[](int pos)const;							// surcharge de l'op�rateur []
};
// surchage de l'op�rateur <<
template <class TYPE>
ostream& operator<<(ostream& output, const mapp<TYPE>& m) {
	m.print(output);
	return output;
}

// surchage de l'op�rateur >>
template <class TYPE>
istream& operator>>(istream& input, mapp<TYPE>& m) {
	m.read(input);
	return input;
}

// constructeur sans param�tres
template <class TYPE>
mapp<TYPE>::mapp() {
	_name = nullptr;
	_map = nullptr;
	_line = _col = 0;
}

// constructeur avec param�tres
template <class TYPE>
mapp<TYPE>::mapp(const char* name, int line, int col) {
	assert((line > 0 && col > 0) || (line == 0 && col == 0));
	
	int nbChar = strlen(name);	// rajoutes un espace pour le \0 dans le nom
	_name = nullptr;
	if (nbChar > 0) {			// cr�ation du nom
		_name = new char[nbChar + 1];
		strcpy_s(_name, nbChar + 1, name);
	}

	_line = line;
	_col = col;
	_map = nullptr;
	
	if (_line > 0 && _col > 0) {
		_map = new TYPE*[_line];	// cr�ation de la matrice
		for (int i = 0; i < _line; i++) {
			*(_map + i) = new TYPE[_col];
		}
	}
}

// copieur
template <class TYPE>
mapp<TYPE>::mapp(const mapp<TYPE>& mapCopy) {
	_line = mapCopy._line;
	_col = mapCopy._col;
	
	int nbChar = strlen(mapCopy._name); // comptes le nombre de caract�res dans la map � copier
	_name = nullptr;
	if (nbChar > 0) {
		_name = new char[nbChar + 1];
		strcpy_s(_name, nbChar + 1, mapCopy._name);
	}

	if (_col == 0) {
		_map = nullptr;
	}
	else {
		_map = new TYPE* [_line];	// cr�ation de la matrice	
		for (int i = 0; i < _line; i++) {	// copies les �l�ments
			*(_map + i) = new TYPE[_col];
			for (int j = 0; j < _col; j++) {
				*(*(_map + i) + j) = *(*(mapCopy._map + i) + j);
			}
		}
	}
}

// destructeur
template <class TYPE>
mapp<TYPE>::~mapp() {
	clear();
}

// big boi m�thode pour clear le nom et le contenu de la map
template <class TYPE>
void mapp<TYPE>::clear() {
	clearMap();
	clearName();
}

// m�thode pour clearer le contenu de la map
template <class TYPE>
void mapp<TYPE>::clearMap() {
	for (int i = 0; i < _line; i++) {	// delete les colonnes
		delete[] * (_map + i);
	}
	delete[] _map;
	_map = nullptr;
	_line = _col = 0;
}

// m�thode pour clearer le nom de la map
template <class TYPE>
void mapp<TYPE>::clearName() {
	delete[] _name;
	_name = nullptr;
}

// m�thode pour retourner le nombre de lignes dans la map
template <class TYPE>
int mapp<TYPE>::nbLine()const {
	return _line;
}

// m�thode pour retourner le nombre de colonnes dans la map
template <class TYPE>
int mapp<TYPE>::nbCol()const {
	return _col;
}

// m�thode pour retourner le nom de la map
template <class TYPE>
const char* mapp<TYPE>::getName()const {
	if (_name == nullptr) 
		return "\0";
	return _name;
}

// m�thode pour renommer la map
template <class TYPE>
void mapp<TYPE>::setName(const char* name) {
	clearName();
	int nbChar = strlen(name);
	_name = nullptr;
	if (nbChar > 0) {
		_name = new char[nbChar + 1];
		strcpy_s(_name, nbChar + 1, name);
	}
}

// m�thode de redimensionnement de la map
template <class TYPE>
void mapp<TYPE>::resize(int line, int col) {
	assert((line > 0 && col > 0) || (line == 0 && col == 0));

	if (line == _line && col == _col) return;	// si le resize est de la m�me dimension que la map
	if (line == 0 && col == 0) {				// si les param�tres sont � 0
		clearMap();
		return;
	}

	TYPE** newMap = new TYPE*[line];				// cr�� la ouvelle map
	for (int i = 0; i < line; i++) {
		*(newMap + i) = new TYPE[col];
	}

	for (int i = 0; i < _line && i < line; i++) {	// dump l'ancienne map dans la nouvelle
		for (int j = 0; j < _col && j < col; j++) {
			*(*(newMap + i) + j) = *(*(_map + i) + j);
		}
	}

	clearMap();
	_map = newMap;	// switcheroo d'addresse de la map
	_line = line;
	_col = col;
}

// m�thode d'acc�s � la donn�e � l'intersection de posI et posJ
template <class TYPE>
TYPE& mapp<TYPE>::at(int posI, int posJ)const {
	assert(posI >= 0 && posI < _line);	// v�rifies que le chiffres est pas n�gatif et dans la matrice
	assert(posJ >= 0 && posJ < _col);
	return *(*(_map + posI) + posJ);
}

// surcharge de l'op�rateur []
template <class TYPE>
TYPE* mapp<TYPE>::operator[](int pos) const {
	assert(pos >= 0 && pos < _line);
	return *(_map + pos);
}

// m�thode d'affichage de l'objet map
template <class TYPE>
void mapp<TYPE>::print(ostream& output)const {
	for (int i = 0; i < _line; i++) {
		for (int j = 0; j < _col; j++) {
			output << *(*(_map + i) + j) << " ";
		}
		output << endl;
	}
}

// m�thode de lecture de l'objet map
template <class TYPE>
void mapp<TYPE>::read(istream& input) {
	for (int i = 0; i < _line; i++) {
		for (int j = 0; j < _col; j++) {
			input >> *(*(_map + i) + j);
		}
	}
}

// surcharge de l'op�rateur =
template <class TYPE>
const mapp<TYPE>& mapp<TYPE>::operator=(const mapp<TYPE>& mapCopy) {
	if (this == &mapCopy) return this;

	clear();	// on supprime tout, donc si les param�tres copi�s sont nuls on peut juste les ignorer
	_line = mapCopy._line;
	_col = mapCopy._col;

	if (_name != nullptr) {
		int nbChar = strlen(mapCopy._name); // comptes le nombre de caract�res dans la map � copier
		if (nbChar > 0) {
			_name = new char[nbChar + 1];
			strcpy_s(_name, nbChar + 1, mapCopy._name);
		}
	}

	if (_col > 0) {
		_map = new TYPE * [_line];
		for (int i = 0; i < _line; i++) {
			*(_map + i) = new TYPE[_col];
			for (int j = 0; j < _col; j++) {
				*(*(_map + i) + j) = *(*(mapCopy._map + i) + j);
			}
		}
	}

	return *this;
}