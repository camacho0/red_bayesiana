#include "Prueba.hpp"

struct Vertice{
	string nombre;
	Vertice* sig;
	Arista* ari;
	double pro[2][2];
	double lambda[2]={1,1};
	double pi[2]={0,0};
	double p[2]={0,0};
	double ml[2]={0,0};
	double mp[2]={1,1};
	Vertice(string nom, double m[2][2]){
		nombre=nom;
		sig=NULL;
		ari=NULL;
		for(int i=0; i<2;i++){
			for(int j=0; j<2;j++){
				pro[i][j]=m[i][j];
			}
		}
		//pro=p[][c];
	}
};

struct Arista{
	Arista* sig;
	Vertice* dest;
	Arista(Vertice* d){
		dest=d;
		sig=NULL;
	}
};


Grafo::Grafo(){
	primero = NULL;
	tamano = 0;
}

bool Grafo:: EstaVacio(){
	return tamano==0;
}

int Grafo::ObtenerTamano(){
	return tamano;
}

Vertice* Grafo::ObtenerVertice(string nom){
	Vertice* i=primero;
	while(i != NULL){
		if(i->nombre == nom){
			return i;
		}
		i=i->sig;

	}
	return NULL;
}

void Grafo::InsertarVertice(string nom, double ma[2][2]){
	if(ObtenerVertice(nom)==NULL){
		Vertice* nuevo = new Vertice(nom,ma);
		if(EstaVacio()){
			primero=nuevo;
		}
		else{
			Vertice* i=primero;
			while(i->sig != NULL){
				i=i->sig;
			}
			i->sig=nuevo;
		}
		tamano++;
	}
	else{
		cout<<"Este vertice ya existe en el grafo"<<endl;
	}
}

void Grafo::InsertarArista(string ori,string dest){
	Vertice* vori=ObtenerVertice(ori);
	Vertice* vdest= ObtenerVertice(dest);
	if (vori==NULL){
		cout<<"El vertice origen no existe"<<endl;
	}
	if(vdest==NULL){
		cout<<"El vertice destino no existe"<<endl;
	}
	if(vori != NULL && vdest != NULL){
		Arista* nueva=new Arista(vdest);
		if(vori->ari == NULL){
			vori->ari=nueva;
		}
		else{
			Arista* j= vori->ari;
			while(j->sig != NULL){
				j=j->sig;
			}
			j->sig=nueva;
		}
	}
}

void Grafo::MostrarLista(){
	Vertice* i=primero;
	while(i != NULL){
		Arista* j = i->ari;
		cout<<i->nombre<<"=";
		while(j != NULL){
			cout<<i->nombre<<"->"<<j->dest->nombre<<",";
			j=j->sig;
		}
		cout<<endl;
		i=i->sig;
	}
}

void Grafo::MostrarProbabilidad(string nombre){
	Vertice* ve=ObtenerVertice(nombre);
	cout<<"La matriz de probabilidad de:"<<ve->nombre<<endl;
	for(int i=0; i<2; i++){
		for(int j=0; j<2; j++){
			cout<<ve->pro[i][j]<<" ";
		}
		cout<<endl;
	}
}

void Grafo::MostrarLambda(string nombre){
	Vertice* ve=ObtenerVertice(nombre);
	cout<<"La lambda de:"<<ve->nombre<<endl;
	cout<<ve->lambda[0]<<", "<<ve->lambda[1]<<endl;
}


vector<Vertice*> Grafo::EncontrarHojas(){
	vector<Vertice*> hojas;
	Vertice* i = primero;
	while(i !=NULL){
		if(i->ari==NULL){
			hojas.push_back(i);
		}
		i=i->sig;
	}
	//cout<<hojas.size()<<endl;
	return hojas;
}

vector<Vertice*> Grafo::Hijos(Vertice* p){
	vector<Vertice*> hijos;
	Arista* i=p->ari;
	while(i != NULL){
		hijos.push_back(i->dest);
		i=i->sig;
	}
	return hijos;
}

Vertice* Grafo::Padres(Vertice* h){
	Vertice* i= primero;
	Arista* j;
	while(i != NULL){
		j=i->ari;
		while(j != NULL){
			if(j->dest==h){
				return i;
			}
			j=j->sig;
		}
		i=i->sig;
	}
}

vector<Vertice*> Grafo::Hermanos(Vertice* e){
	vector<Vertice*> hermanos;
	Vertice* p=Padres(e);
	Arista* i=p->ari;
	while(i!= NULL){
		if(i->dest != e){
			hermanos.push_back(i->dest);
		}
		i=i->sig;
	}
	return hermanos;
}

void Grafo::MensajeLambda(Vertice* h){
	double m=0;
	for(int i=0; i<2;i++){
		m=0;
		for(int j=0; j<2;j++){
			m+= h->lambda[i]*h->pro[j][i];
		}
		h->ml[i]=m;
	}
}

void Grafo::Lambda(Vertice* v){
	vector<Vertice*> hijos= Hijos(v);
	//MostrarLambda(v->nombre);
	if(hijos.size()==1){
		for(int i=0; i<2; i++){
			v->lambda[i]=hijos[0]->ml[i];
		}
	}
	else{
		for(int i=0;i<hijos.size();i++){
			for(int j=0; j<2;j++){
				v->lambda[j]*=hijos[i]->ml[j];
			}
		//	cout<< v->lambda[j];
		}
	}
}

void Grafo::PropagacionLambda(){
	vector<Vertice*> hojas=EncontrarHojas();
	Vertice* hijo=NULL;
	Vertice* padre=NULL;
	int h=0;
	for(int i=0; i<hojas.size();i++){
		padre=Padres(hojas[i]);
		MensajeLambda(hojas[i]);
	}

	while(h!=hojas.size()){
		Lambda(Padres(hojas[h]));
		hijo=Padres(hojas[h]);
		padre=Padres(hijo);
		while(padre!=primero ){
			MensajeLambda(hijo);
			Lambda(padre);
			hijo=padre;
			padre=Padres(padre);
		}
		if(padre==primero){
			MensajeLambda(hijo);
			Lambda(padre);
		}
		h++;
	}
}

void Grafo::MensajePi(Vertice* v){
	Vertice* padre=Padres(v);
	double a=1;
	vector<Vertice*> hermanos=Hermanos(v);
	if( hermanos.size()==0){
		v->mp[0]=padre->pi[0];
		v->mp[1]=padre->pi[1];
	}
	else{
		for(int i=0; i<hermanos.size();i++){
			a=1;
			for(int j=0; j<2; j++){
				a*=hermanos[i]->lambda[j];
			}
			v->mp[i]=a;
		}
		v->mp[0]*=padre->pi[0];
		v->mp[1]*=padre->pi[1];
	}
}

void Grafo::Pi(Vertice* v){
	if(v==primero){
		v->pi[0]=v->pro[0][0];
		v->pi[1]=v->pro[0][1];
	}
	else{
		Vertice* padre= Padres(v);
		for(int i=0; i<2; i++){
			for(int j=0; j<2; j++){
				v->pi[i]+=v->mp[j]*v->pro[i][j];
			}
		}
	}
}

void Grafo::PropagacionPi(){
	Vertice* v=primero;
	if(v==primero){
		Pi(v);
		v=v->sig;
	}
	while(v != NULL){
		MensajePi(v);
		Pi(v);
		v=v->sig;
	}
}

void Grafo::Probabilidades(){
Vertice* v=primero;
double c=0;
while(v != NULL){
	v->p[0]=(v->pi[0]*v->lambda[0]);
	v->p[1]=v->pi[1]*v->lambda[1];
	c=v->p[0]+v->p[1];
	v->p[0]/=c;
	v->p[1]/=c;
	v=v->sig;
}
}
void Grafo::Mostrar(){
	Vertice* p=primero;
	while(p!=NULL){
		cout<<p->nombre<<": ";
		cout<<p->lambda[0]<<","<<p->lambda[1]<<endl;
		p=p->sig;
	}
}

void Grafo::MostrarPi(){
	Vertice* p=primero;
	while(p!=NULL){
		cout<<p->nombre<<": ";
		cout<<p->pi[0]<<","<<p->pi[1]<<endl;
		p=p->sig;
	}
}


void Grafo::MostrarPro(){
	Vertice* v=primero;
	while(v!=NULL){
		cout<<v->nombre<<": ";
		cout<<v->p[0]<<","<<v->p[1]<<endl;
		v=v->sig;
	}
}
