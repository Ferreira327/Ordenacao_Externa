
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <string>

struct Data {
	char anzsic06[40];
	char Area[40];
	int year;
	int geo_count;
	int ec_count; 
};

using namespace std;


void inserirPosicao(int tamanho){
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
	
	if(gravar.write(reinterpret_cast<char*>(&d), sizeof(Data)))
		cout << "Posicao inserida com sucesso!\n\n";
	
	gravar.close();
	ler.close();
	
}


void lerCsvEGravarBinario(int tamanho)
{
	ifstream arquivo;
	char pv;
	arquivo.open("original.csv");
	string primeiraLinha;
	getline(arquivo, primeiraLinha);

	 ofstream arqBinario("dados.dat", ios::binary);
	 for (int i = 0; i < tamanho; i++)
	{
		Data d;
		arquivo.getline(d.anzsic06, 40, ',');
		arquivo.getline(d.Area, 40, ',');
		arquivo >> d.year;
		arquivo >> pv;
		arquivo >> d.geo_count;
		arquivo >> pv;
		arquivo >> d.ec_count;
		arquivo.ignore();
		
		arqBinario.seekp(0, ios::end);
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
	while (getline(arquivo, verifica))
	{
		numero++;
	}
	arquivo.close();
	return numero;
}

int nPessoasBin()
{
	ifstream calcular("dados.dat", ios::binary);
	calcular.seekg(0, calcular.end);
	int tamanhoArquivo = calcular.tellg(); // calcula tamanho do arquivo binário inteiro
	calcular.close();
	return tamanhoArquivo / sizeof(Data); // divide o tamanho do arquivo inteiro pelo tamanho do struct para saber quantos structs
}

void imprimirBusca(int tamanho)
{
	Data func;
	ifstream busca("dados.dat", ios::binary);

	cout << "Area a ser buscada:";
	char procura[40];
	cin.getline(procura, 40);
	int pos;
	pos = -1;
	for (int i = 0; i < tamanho; i++)
		{
		busca.seekg(i * sizeof(Data));							  // posiciona a leitura na posição i
		busca.read(reinterpret_cast<char *>(&func), sizeof(Data)); // lê a posição i e armazena no funcionario func criado
		if (strcmp(func.Area, procura) == 0)
		{
			//busca.close();
			pos = i;
		}
	}
	busca.close();

	if (pos == -1)
	{
		cout << "Usuario nao encontrado" << endl;
	}
	else
	{
		cout << "\nPosicao: "<< pos << endl << endl;
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
    if (inicio < 0 or fim < 0 or fim < inicio or inicio > tamanho - 1 or fim > tamanho - 1)
    {
        cerr << "Posicao inexistente";
    }
    else
    {
        ifstream busca("dados.dat", ios::binary);
        Data d;
        for (int i = inicio; i <= fim; i++)
        {
            busca.seekg(i * sizeof(d));
            busca.read(reinterpret_cast<char *>(&d), sizeof(Data));
            cout << d.anzsic06 << ";";
            cout << d.Area << ";";
            cout << d.year << ";";
            cout << d.geo_count << ";";
            cout << d.ec_count << ";";
            cout << endl;
        }
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
	
	cout << "[1]Mostrar Valores Entre Intervalos\n[2]Imprimir Busca\n[3]Inserir na Posicao\n[4]Numero de Cadastros\n\n";
	
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
		cout << "Numero de Cadastros: "<< nPessoasBin() << endl;
		break; 
				
	}
	
	cout << "\nPressione Enter para continuar...\n\n";
    cin.get();
	
	
	}
	
	return 0;
	
	
}
