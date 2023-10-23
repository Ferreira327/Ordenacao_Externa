#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <string>
#include <iomanip> // Formatação da saída, uso do setw()

using namespace std;

struct Data {
	char anzsic06[40];
	char Area[40];
	int year;
	int geo_count;
	int ec_count; 
};

void inserirPosicao(int tamanho)
{
	ifstream ler;
   fstream gravar;

   gravar.open("dados.dat",ios::out|ios::in);
   ler.open("dados.dat");
    
   int posicao;
   Data aux;
	Data d;
	
	cout << "Digite o anzsic06: ";
	cin.getline(d.anzsic06,40);

	cout << "Digite a Area: ";
	cin.getline(d.Area,40);
	cout << "Digite o ano: ";
	cin >> d.year;
	cout << "Digite a geo_count: ";
	cin >> d.geo_count;
	cout << "Digite a ec_count: ";
	cin >> d.ec_count;
	
   cout << "Digite a posicao desejada:";
   cin >> posicao;
    
   cout << "\n\nAguarde...\n\n";
    
   if(posicao < 0 or posicao > tamanho){
		throw runtime_error("Posicao invalida");
	}
    
   gravar.seekp((tamanho)*sizeof(Data));
   tamanho--;
   ler.seekg((tamanho)*sizeof(Data));


	while(tamanho >= posicao){
		ler.read(reinterpret_cast<char*>(&aux),sizeof(Data));
		gravar.write(reinterpret_cast<char*>(&aux), sizeof(Data));
		tamanho--;
		ler.seekg((tamanho)*sizeof(Data));
		gravar.seekp((tamanho+1)*sizeof(Data));
	}
	system("clear");

	if(gravar.write(reinterpret_cast<char*>(&d), sizeof(Data))){
      cout << "Posicao inserida com sucesso!\n\n";
   }
	
	gravar.close();
	ler.close();
}

int nPessoasBin()
{
	ifstream calcular("dados.dat", ios::binary);
	calcular.seekg(0, calcular.end);
	int tamanhoArquivo = calcular.tellg(); // calcula tamanho do arquivo binário inteiro
	calcular.close();
	return tamanhoArquivo / sizeof(Data); // divide o tamanho do arquivo inteiro pelo tamanho do struct para saber quantos structs
}

void editar()
{
   int posicao;
   cout << "Posicao a ser editada: " << endl;
   cin >> posicao;
   int tamanho = nPessoasBin();
   if (posicao > tamanho - 1 or posicao < 0){
      cerr << "Posicao inexistente";
	}else{
      fstream atualizar("dados.dat", ios::binary | ios::in | ios::out);

      Data d;
      cin.ignore();
      cout << "anzsic06: " << endl;
      cin.getline(d.anzsic06, 40);
      cout << "Area: " << endl;
      cin.getline(d.Area, 40);
      cout << "year: " << endl;
      cin >> d.year;
      cout << "geo_count: " << endl;
      cin >> d.geo_count;
      cout << "ec_count: " << endl;
      cin >> d.ec_count;

      atualizar.seekp(posicao * sizeof(Data));
      atualizar.write(reinterpret_cast<const char *>(&d), sizeof(Data));
      atualizar.close();

      cout << "Registro editado com sucesso" << endl;
   }
}

void lerCsvEGravarBinario(int tamanho)
{
	ifstream arquivo;
	char pv;
	arquivo.open("original.csv");
	string primeiraLinha;
	getline(arquivo, primeiraLinha);

	ofstream arqBinario("dados.dat", ios::binary);
	for (int i = 0; i < tamanho; i++){

		Data d;
		if(i != 0){
		arquivo.ignore();}
		arquivo.getline(d.anzsic06, 40, ',');
		arquivo.getline(d.Area, 40, ',');
		arquivo >> d.year;
		arquivo >> pv;
		arquivo >> d.geo_count;
		arquivo >> pv;
		arquivo >> d.ec_count;
		arquivo.ignore();
		
		arqBinario.write(reinterpret_cast<const char*>(&d), sizeof(Data));
	}

	arquivo.close();
	arqBinario.close();
}

int nPessoasCsv()
{
	int numero = 0;
	string verifica;
	ifstream arquivo;
	arquivo.open("original.csv");

	while (getline(arquivo, verifica)){
		numero++;
	}

	arquivo.close();
	return numero;
}

void imprimirBusca(int tamanho)
{
	Data func;
	Data guardar;
	ifstream busca("dados.dat", ios::binary);

	cout << "Area a ser buscada:";
	char procura[40];
	cin.getline(procura, 40);
	int pos;
	pos = -1;
	cout << "Buscando...\n\n";
	for (int i = 0; i < tamanho; i++){
		busca.seekg(i * sizeof(Data));							  // posiciona a leitura na posição i
		busca.read(reinterpret_cast<char *>(&func), sizeof(Data)); // lê a posição i e armazena no funcionario func criado
		if (strcmp(func.Area, procura) == 0){
			pos = i;
			guardar = func;
		}
	}
	busca.close();


	if (pos == -1){
		cout << "Usuario nao encontrado" << endl;
	}else{
		cout << "\nPosicao: "<< pos << endl << endl;
		cout << "\n\nanzsic06: " << guardar.anzsic06 << endl << "Area: " << guardar.Area << endl << "year: " << guardar.year << endl << "geo_cont:" <<  guardar.geo_count << endl << "ec_count: "<< guardar.ec_count << endl;

	}


}

void mostrarEntrePosicoes()
{
    int inicio, fim;
    cout << "Posicao inicial: ";
    cin >> inicio;
    cout << endl;

    cout << "Posicao final: ";
    cin >> fim;
    cout << endl;

    int tamanho = nPessoasBin();
    if (inicio < 0 or fim < 0 or fim < inicio or inicio > tamanho - 1 or fim > tamanho - 1){
        cerr << "Posicao inexistente";
    }else{
        ifstream busca("dados.dat", ios::binary);
        Data d;
		cout << setw(20)<< left << "anzsic06" << setw(20) <<"Area" << setw(15) << "year" << setw(10) << "geo_cont" << right <<setw(10) << "ec_count"<< endl;
        for (int i = inicio; i <= fim; i++){
            busca.seekg(i * sizeof(d));
            busca.read(reinterpret_cast<char *>(&d), sizeof(Data));
        	cout << setw(20) << left << d.anzsic06 << setw(20) << d.Area << setw(15)<< d.year << setw(10) << d.geo_count << right <<setw(10) << d.ec_count << endl;
        }
    }
}

void trocarPosicoes()
{	
	int pos1;
	int pos2;

	cout << "Digite a posicao 1: " << endl;
	cin >> pos1;
	if(pos1 < 0){
		throw runtime_error("Posicao Invalida");
	}

	cout << "Digite a posicao 2: " << endl;
	cin >> pos2;
	if(pos2 < 0){
		throw runtime_error("Posicao Invalida");
	}

	if(pos1 == pos2){
		throw runtime_error("Posicao Invalida");
	}

	fstream arquivo;
	arquivo.open("dados.dat", ios::out|ios::in);

	Data aux1;
	Data aux2;

	arquivo.seekg((pos1)*sizeof(Data));
	arquivo.read(reinterpret_cast<char*>(&aux1),sizeof(Data));
	arquivo.seekg((pos2)*sizeof(Data));
	arquivo.read(reinterpret_cast<char*>(&aux2),sizeof(Data));

	arquivo.seekp((pos1)*sizeof(Data));
	arquivo.write(reinterpret_cast<char*>(&aux2), sizeof(Data));
	arquivo.seekp((pos2)*sizeof(Data));
	arquivo.write(reinterpret_cast<char*>(&aux1), sizeof(Data));

}

void mostrarTodos(){

	ifstream busca;
	busca.open("dados.dat");
	Data d;

	int tam = nPessoasBin();

	cout << setw(20)<< left << "anzsic06" << setw(20) <<"Area" << setw(15) << "year" << setw(10) << "geo_cont" << right <<setw(10) << "ec_count"<< endl;

	for(int i = 0; i < tam; i++){
      busca.seekg(i * sizeof(d));
      busca.read(reinterpret_cast<char *>(&d), sizeof(Data));
	  cout << setw(20) << left << d.anzsic06 << setw(20) << d.Area << setw(15)<< d.year << setw(10) << d.geo_count << right <<setw(10) << d.ec_count << endl;
      
   }

}

int main () {
	int tamanho = nPessoasCsv();
	tamanho--; //desconsiderar primeira linha do csv
	
	cout << "Aguarde... Lendo o arquivo CSV\n\n";

	lerCsvEGravarBinario(tamanho);
	system("clear");

	cout << "Csv gravado em arquivo binario com sucesso!" << endl;
	cout << "qtd linhas binario: " << nPessoasBin() << endl;
	
	cout << "\nPressione Enter para continuar...\n";
    cin.get();
	
	char a;

	while(a != 'f'){
			
		system("clear");

		cout << "-----------------PROJETO ESTRUTURA DE DADOS ETAPA1-----------------\n\n";
		
		cout << "[1]Mostrar Valores Entre Intervalos\n[2]Imprimir Busca\n[3]Inserir na Posicao\n[4]Numero de Cadastros\n[5]Editar\n[6]Trocar 2 posicoes\n[7]Mostrar todos os dados\n[f]Fechar o programa\n";
		
		cin >> a;
		cin.ignore();
		
		system("clear");
		
		switch(a){
			
			case '1':
			mostrarEntrePosicoes();
			cin.ignore();
			break;
			
			case '2':
			imprimirBusca(tamanho);
			break;
			
			case '3':
			inserirPosicao(tamanho);
			tamanho++;
			cin.ignore();
			break;

			case '4':
			cout << "Numero de Cadastros: " << nPessoasBin() << endl;
			break; 
					
			case '5':
			editar();
			break;

			case '6':
			trocarPosicoes();
			break;

			case '7':
			mostrarTodos();
			break;
		}
		
		cout << "\nPressione Enter para continuar...\n\n";
		cin.get();
		
	}
	
	return 0;	
}