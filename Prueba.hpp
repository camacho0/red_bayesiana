#ifndef GRAFO_HPP
#define GRAFO_HPP
#include <iostream>
//#include "Arista.hpp"
//#include "Vertice.hpp"
#include <string>
#include <list>
#include <stack>
#include <queue>
#include <algorithm>
#include <vector>
//#include <map>
//#include <unordered_set>

using namespace std;
struct Vertice;
struct Arista;


class Grafo{
	private:
		Vertice* primero;
		int tamano;
	
	public:
		Grafo();
		bool EstaVacio();
		int ObtenerTamano();
		Vertice* ObtenerVertice(string nombre);
		void InsertarVertice(string nombre, double ma[2][2]);
		void InsertarArista(string ori, string dest);
		void MostrarLista();
		void MostrarProbabilidad(string nombre);
		void RecorridoAnchura(string origen);
		void RecorridoProfundidad(string origen);
	//	void Hojas(vector<Vertice*> V);
		vector<Vertice*> EncontrarHojas();
		vector<Vertice*> Hijos(Vertice* p);
		Vertice* Padres(Vertice* h);
		vector<Vertice*> Hermanos(Vertice* e);
		void MensajeLambda(Vertice* h);
		void Lambda(Vertice* v);
		void PropagacionLambda();
		void MensajePi(Vertice* v);
		void Pi(Vertice* v);
		void PropagacionPi();
		void MostrarLambda(string nom);
		void Mostrar();
		void MostrarPi();
		void Probabilidades();
		void MostrarPro();
};

#endif

