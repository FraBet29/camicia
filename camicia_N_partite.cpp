//CAMICIA - Simulazione di N partite
//Salva in un file il numero di carte giocate e il vincitore per ogni partita

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

#define N 1000 //numero di partite da simulare

int nCarteGiocate; //conta le carte giocate

/*
//Utile per debug
void stampaMazzo(vector<int> G) {
	for(int i=0; i<40; i++)
		cout << G[i] << ' ';
	cout << endl;
}
*/

void mischiaMazzo(vector<int> &m) {
	
	random_shuffle(m.begin(), m.end());
	
}

void inizializzaMazzo(vector<int> &mazzo) {
	
	for(int i=0; i<4; i++)
		mazzo[i] = 1; //asso
	for(int i=4; i<8; i++)
		mazzo[i] = 2; //due
	for(int i=8; i<12; i++)
		mazzo[i] = 3; //tre
	for(int i=12; i<40; i++)
		mazzo[i] = 4; //altre carte
		
}

void distribuisciCarte(vector<int> mazzo, vector<int> &G1, vector<int> &G2) {
	
	int i = 0;
	
	for(int j=0; j<40; j+=2) {
		G1[i] = mazzo[j];
		i++;
	}
	for( ; i<40; i++)
		G1[i] = 0;
	
	i = 0;
	
	for(int j=1; j<40; j+=2) {
		G2[i] = mazzo[j];
		i++;
	}
	for( ; i<40; i++)
		G2[i] = 0;
	
}

bool controllaVuoto(vector<int> G) { //restituisce true se vuoto, false altrimenti
	for(int i=0; i<40; i++)
		if(G[i]!=0)
			return false;
	return true;
}

//CIG � costruito in modo tale che le carte pi� recenti siano in fondo
//Quando CIG viene preso da un giocatore viene correttamente "capovolto"
//(nel gioco reale infatti le carte dei giocatori sono a faccia in gi�, mentre CIG � a faccia in su)
void mettiCarta(vector<int> &G, vector<int> &CIG, int &nCIG) {
	CIG[nCIG] = G[0];
	G.erase(G.begin());
	G.push_back(0);
	nCIG++;
}

void controllaCarteSpeciali(vector<int> &G1, vector<int> &G2, vector<int> &CIG, int &nCIG, bool &turnoG1) {
	
	bool controllaCiclo = true;
	
	int n = CIG[nCIG-1];
	
	for(int i=0; i<n && controllaCiclo && !controllaVuoto(G1) && !controllaVuoto(G2); i++) {
		
		if(turnoG1==true)
			mettiCarta(G1, CIG, nCIG);
		else
			mettiCarta(G2, CIG, nCIG);
			
		nCarteGiocate++;
				
		if(CIG[nCIG-1]!=4) {
			turnoG1 = !turnoG1;
			controllaCiclo = false;
			controllaCarteSpeciali(G1, G2, CIG, nCIG, turnoG1);
		}

	}

}

void prendiCIG(vector<int> &G, vector<int> &CIG, int &nCIG) {
	
	int contG = 0;
	while(G[contG]!=0)
		contG++;
	int contCIG = 0;
	while(CIG[contCIG]!=0) {
		G[contG] = CIG[contCIG];
		CIG[contCIG] = 0;
		contG++;
		contCIG++;
	}
	nCIG = 0;
}

char gioca(vector<int> G1, vector<int> G2) {
	
	vector<int> CIG(40); //carte in gioco
	int nCIG = 0; //indice CIG, conta quante carte sono in gioco
	
	bool turnoG1 = true; //inizia G1
	
	while(!controllaVuoto(G1) && !controllaVuoto(G2)) { //il gioco continua finch� uno dei giocatori ha zero carte in mano
		
		if(turnoG1)
			mettiCarta(G1, CIG, nCIG);
		else
			mettiCarta(G2, CIG, nCIG);
			
		nCarteGiocate++;
					
		turnoG1 = !turnoG1;
		
		if(CIG[nCIG-1]!=4) {
			
			controllaCarteSpeciali(G1, G2, CIG, nCIG, turnoG1);
			
			if(turnoG1)
				prendiCIG(G2, CIG, nCIG);
			else
				prendiCIG(G1, CIG, nCIG);
			
			turnoG1 = !turnoG1;
			
		}
	
	}
	
	if(controllaVuoto(G1))
		return '2';
	else
		return '1';
	
}

int main() {
	
	char Winner;
	
	vector<int> mazzo(40);
	inizializzaMazzo(mazzo);

	vector<int> G1(40);
	vector<int> G2(40);
	
	ofstream fout("output.txt");
	fout << "NCarte Vincitore" << endl;

	for(int i=0; i<N; i++) {
		
		nCarteGiocate = 0;
		
		mischiaMazzo(mazzo);
		distribuisciCarte(mazzo, G1, G2);
		Winner = gioca(G1, G2);
		
		fout << nCarteGiocate << ' ';
		fout << 'G' << Winner << endl;
	
	}
	
	fout.close();
	
	return 0;
	
}
