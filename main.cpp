#include "Invertida.hpp"


using namespace std;

int main(){
	vector<Vertice*> lista;
	double m1[2][2]={{0.992,0.99},{0.008,0.01}};
	double m2[2][2]={{0.2,0.003},{0.8,0.997}};
	double m3[2][2]={{0.003,0.5},{0.997,0.5}};
	double m4[2][2]={{0.22,0.3},{0.78,0.7}};
	double m5[2][2]={{0.83,0.52},{0.17,0.48}};
	double m6[2][2]={{0.73,0.98},{0.27,0.02}};
	double m7[2][2]={{0.63,0.52},{0.37,0.48}};
	double m8[2][2]={{0.0036,0.12},{0.9964,0.88}};
	double m9[2][2]={{0.45,0.12},{0.55,0.88}};
	double m10[2][2]={{0.32,0.21},{0.68,0.79}};
	double m11[2][2]={{0.66,0.1},{0.34,0.9}};
	double m12[2][2]={{0.6,0.4},{0.4,0.6}};
	double m13[2][2]={{0.69,0.79},{0.31,0.21}};
	double m14[2][2]={{0.22,0.87},{0.78,0.13}};
	double m15[2][2]={{0.92,0.97},{0.08,0.03}};
	double p1[2]={0.005,0.995};
	double p2[2]={0.03,0.97};
	double p3[2]={0.04,0.96};
	double p4[2]={0.3,0.7};
	double p5[2]={0.9,0.1};
	double p6[2]={0.12,0.88};
	double p7[2]={0.36,0.64};
	double p8[2]={0.82,0.18};
	Grafo* grafo =  new Grafo();
	grafo->InsertarVertice("C",m1);
	grafo->InsertarVertice("SP",m2);
	grafo->InsertarVertice("SS",m3);
	grafo->InsertarVertice("R",m4);
	grafo->InsertarVertice("Sc1",m5);
	grafo->InsertarVertice("Sv",m6);
	grafo->InsertarVertice("Sc2",m7);
	grafo->InsertarVertice("Bc",m8,p1);
	grafo->InsertarVertice("Cm",m9,p2);
	grafo->InsertarVertice("Bo1",m10,p3);
	grafo->InsertarVertice("Re",m11,p4);
	grafo->InsertarVertice("It",m12,p5);
  grafo->InsertarVertice("Tu",m13,p6);
	grafo->InsertarVertice("Cd",m14,p7);
	grafo->InsertarVertice("Bo2",m15,p8);

	
	grafo->InsertarArista("C","SP");
	grafo->InsertarArista("C","SS");
	grafo->InsertarArista("SP","R");
	grafo->InsertarArista("SP","Sc1");
	grafo->InsertarArista("SS","Sv");
	grafo->InsertarArista("SS","Sc2");
	grafo->InsertarArista("R","Bc");
	grafo->InsertarArista("R","Cm");
	grafo->InsertarArista("Sc1","Bo1");
	grafo->InsertarArista("Sc1","Re");
	grafo->InsertarArista("Sv","Tu");
	grafo->InsertarArista("Sv","Cd");
	grafo->InsertarArista("Sc2","It");
	grafo->InsertarArista("Sc2","Bo2");
	grafo->MostrarLista();
	grafo->PropagacionPi();
  grafo->MostrarPi();

	return 0;
}
