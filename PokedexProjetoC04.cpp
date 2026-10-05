//=====================================================
//                Projeto de Pokedex
//=====================================================
// Integrantes:
// Kau� Aparecido Silva Morais       - GES - 756
// Ana Clara Oliveira e Silva        - GES - 867
// T�lio C�sar Alves Junho           - GES - 741
// Jo�o Vitor Lima da Silveira       - GES - 500
// Vitoria C�ssia Bernardo Rodrigues - GEC - 2094
#define INF 99999

#include <iostream> 
#include <locale>
#include <cstdlib>
#include <list>
#include <string>
using namespace std;

struct Cidade
{
	string nome;
	int codigo;
	bool centro;	
};
  
struct Aresta
{
	int origem, destino, peso;
};

void limparCin()
{
    cin.clear();
    cin.ignore(100, '\n');
}

int verificacao(string decisao)
{
	int opcao = 0;
	getline(cin >> ws, decisao);
	
    
    bool valido = true;
    
    if(decisao.empty())
    {
        valido = false;
    }

    for(int i = 0; i < decisao.length(); i++)
    {
        if(decisao[i] < '0' || decisao[i] > '9')
        {
            valido = false;
        }
    }

    if(valido)
    {
        opcao = 0;

        for(int i = 0; i < decisao.length(); i++)
        {
            opcao = opcao * 10 + (decisao[i] - '0');
        }

        if(opcao > 11)
        {
            valido = false;
        }
    }
	
	if(!valido)
		return -1;
	
	return opcao;
	
}
  

int menu(){                 //Exibe o menu da pokedex
    string decisao;

    cout << "  ====================================================================================================================" << endl;
    cout << "                                                     POKEDEX                " << endl;
    cout << "  ====================================================================================================================" << endl;
    cout << "\n# Ol�, Jovem Treinador! Essa � a Pok�dex, sua maior aliada em sua jornada de se tornar o melhor treinador dos Pok�mons!" << endl;
    cout << endl;
    cout << "Fa�a sua escolha: " << endl;
    cout << endl;
    cout << "[1] Cadastrar Cidade. " << endl;
	cout << "[2] Cadastrar Estrada. " << endl;
	cout << "[3] Buscar Centro Pok�mon mais pr�ximo. " << endl;
	cout << "[4] Cadastrar Pok�mon. " << endl;
	cout << "[5] Remover Pok�mon. " << endl;
	cout << "[6] Listar Pok�mons (ordem alfab�tica por nome). " << endl;
	cout << "[7] Listar Pok�mons (ordem alfab�tica por tipo). " << endl;
	cout << "[8] Contar Pok�mons de cada Tipo. " << endl;
	cout << "[9] Encontrar Pok�mons pr�ximos. " << endl;
	cout << "[10] Listar Cidades. " << endl;
	cout << "[11] Listar Estradas. " << endl;
	cout << "[0] Sair do Programa. " << endl;
    cout << endl;

    return verificacao(decisao); 
}

void onConstruct(){
    cout << "Funcionalidade em Constru��o... \n" << endl;
}

void CadastrarCidade(list<Cidade>& cidades, int& vertices)
{
    Cidade nova;

    cout << "Insira o nome da cidade a ser cadastrada: " << endl;
    getline(cin >> ws, nova.nome);

    for(list<Cidade>::iterator it = cidades.begin(); it != cidades.end(); it++)
    {
        while(it->nome == nova.nome)
        {
            cout << "Essa cidade j� foi cadastrada. Insira outro nome: " << endl;
            getline(cin >> ws, nova.nome);

            it = cidades.begin();
        }
    }

    nova.codigo = vertices + 1;


    string respostaCentro;

	cout << "Essa cidade tem um Centro Pok�mon? (1 - Sim / 0 - N�o): " << endl;
	cin >> respostaCentro;

	while(respostaCentro != "0" && respostaCentro != "1")
	{
    	cout << "Digite apenas 1 ou 0: " << endl;
    	cin >> respostaCentro;
	}

	if(respostaCentro == "1")
		nova.centro = true;
	
	else
		nova.centro = false;

    cidades.push_back(nova);

    vertices++;

    cout << "Cidade cadastrada!\n";
    cout << "C�digo da cidade: " << nova.codigo << endl << endl;
}

void CadastrarEstrada(list<Aresta> grafo[], int vertices)
{
	if(vertices <= 1)
	{
		cout << "N�o h� cidades o suficiente para uma estrada ser criada!" << endl;
		return;
	}
	
    int origem, destino, peso;

    cout << "Insira o c�digo da cidade de origem: ";
    cin >> origem;

    while(cin.fail() || origem < 1 || origem > vertices)
    {
        limparCin();
        cout << "C�digo de cidade inexistente. Tente novamente: " << endl;
        cin >> origem;
    }

    cout << "Insira o c�digo da cidade de destino: ";
    cin >> destino;

    while(cin.fail() || destino < 1 || destino > vertices || destino == origem)
    {
        limparCin();

        if(destino == origem)
        {
            cout << "A cidade de destino deve ser diferente da origem. Tente novamente: ";
        }
        else
        {
            cout << "C�digo de cidade inexistente. Tente novamente: ";
        }

        cin >> destino;
    }

    cout << "Dist�ncia da estrada: ";
    cin >> peso;

    while(cin.fail() || peso <= 0)
    {
        limparCin();
        cout << "Insira a dist�ncia correta da estrada: ";
        cin >> peso;
    }

    origem--;
    destino--;

    grafo[origem].push_back({origem, destino, peso});
    grafo[destino].push_back({destino, origem, peso});

    cout << "Estrada cadastrada!\n" << endl;
}

void ListarCidades(list<Cidade> cidades)
{
    // pra percorrer a lista de cidades no for
    list<Cidade>::iterator cidade;

    cout << "\n========== CIDADES ==========\n";

    for(cidade = cidades.begin(); cidade != cidades.end(); cidade++)
    {
	
		cout << "Nome:" << cidade -> nome << " | C�digo:" << cidade -> codigo; 
		cout << " | Centro Pok�mon:";

        if(cidade -> centro)
            cout << "Sim";
        else
            cout << "N�o";

        cout << endl;
    }

    cout << endl;
}

void ListarEstradas(list<Cidade> cidades, list<Aresta> grafo[])
{
    list<Cidade>::iterator cidade; // pra percorrer a lista de cidades no primeiro for
    
    list<Aresta>::iterator it; // pra percorrer a lista de estradas da cidade atual no segundo for 

    cout << "\n========== ESTRADAS ==========\n";

    // percorre todas as cidades
    for(cidade = cidades.begin(); cidade != cidades.end(); cidade++)
    {
        // pega o c�digo da cidade e diminui 1 pra usar como �ndice do grafo (j� que vetor come�a em 0)
        int i = cidade -> codigo - 1;

        // percorre as estradas que saem da cidade atual
        for(it = grafo[i].begin(); it != grafo[i].end(); it++)
        {
            // pra percorrer a lista de cidades e ver qual � o destino
            list<Cidade>::iterator destino;

            // percorre todas as cidades procurando o destino da estrada
            for(destino = cidades.begin(); destino != cidades.end(); destino++)
            {
                // ve se o c�digo da cidade de destino � igual ao destino da estrada
                if(destino -> codigo == it -> destino + 1)
                    cout << cidade -> nome << " -> " << destino -> nome << " | Dist�ncia: " << it -> peso << endl;
            }
        }
    }

    cout << endl;
}

int CentroProximo(list<Aresta> grafo[], list<Cidade>& cidades, int totalcidades, int origemCodigo)
{
    string nomeCidade[100];
    bool temCentro[100];

    // Monta arrays auxiliares indexados por codigo-1, percorrendo a list uma vez
    list<Cidade>::iterator itc;
    for(itc = cidades.begin(); itc != cidades.end(); itc++)
    {
        int idx = itc->codigo - 1;
        nomeCidade[idx] = itc->nome;
        temCentro[idx] = itc->centro;
    }

    int origem = origemCodigo - 1; // converte c�digo digitado -> �ndice

    if(origem < 0 || origem >= totalcidades)
    {
        cout << "C�digo de cidade inv�lido!" << endl;
        return -1;
    }

    bool visitado[100];
    int pai[100];
    int distancia[100];

    list<Aresta>::iterator it;

    for(int i = 0; i < totalcidades; i++){
        visitado[i] = false;
        pai[i] = -1;
        distancia[i] = INF;
    }
    distancia[origem] = 0;

    while(true){

        int atual = -1;
        int menor = INF;

        for(int i = 0; i < totalcidades; i++){
            if(!visitado[i] && distancia[i] < menor){
                menor = distancia[i];
                atual = i;
            }
        }

        if(atual == -1)
            break;

        visitado[atual] = true;

        for(it = grafo[atual].begin(); it != grafo[atual].end(); ++it)
        {
            int destino = it->destino;
            int peso = it->peso;

            if(distancia[atual] + peso < distancia[destino]){
                distancia[destino] = distancia[atual] + peso;
                pai[destino] = atual;
            }
        }
    }

    int melhorcidade = -1;
    int menordistancia = INF;

    for(int i = 0; i < totalcidades; i++){
        if(temCentro[i] && distancia[i] < menordistancia)
        {
            menordistancia = distancia[i];
            melhorcidade = i;
        }
    }

    if(melhorcidade == -1){
        cout << "Nenhum centro Pok�mon encontrado" << endl;
        return -1;
    }

    cout << "Centro Pok�mon encontrado na cidade " << nomeCidade[melhorcidade] << endl;
    cout << "Dist�ncia total: " << menordistancia << endl;

    int caminho[100];
    int tam = 0;
    for(int v = melhorcidade; v != -1; v = pai[v]){
        caminho[tam++] = v;
    }

    cout << "Rota: ";
    for(int i = tam - 1; i >= 0; i--){
        cout << nomeCidade[caminho[i]];

        if(i > 0)
            cout << " -> ";
    }
    cout << endl;

    return melhorcidade;
}

int main(){

	setlocale(LC_ALL, "Portuguese_Brazil");  
	
    //Imagem pikachu
    
    #ifdef _WIN32
    // Ativa cores ANSI no Windows Terminal
    system("chcp 65001 > nul");
    #endif

    // Pikachu #025 - arte colorida do projeto Pokemon Terminal Art
    const char* comando =
        "curl -s "
        "https://raw.githubusercontent.com/shinya/pokemon-terminal-art/main/"
        "fullcolor/diamond/025.txt";

    system(comando);
    cout << "\033[0m" << endl;

    //Come�o do c�digo
    
    list<Cidade> cidades;
    
    int vertices = 0;

    list<Aresta> grafo[100];
    
    int decisao = -1;

    while(decisao != 0){

        decisao = menu();

            switch (decisao)        //Switch que controla a entrada desejada do usu�rio.
        {
        case 0:                 //Encerrando o programa
            cout << "\nPok�dex desligando... Pika Pika :(\n" << endl;
            return 0;
            
        case 1:                 //Cadastrar cidade
            CadastrarCidade(cidades, vertices);     
            break;
        
        case 2:                 //Cadastrar estradas
            CadastrarEstrada(grafo, vertices);      
            break;
        
        case 3:                 //Buscar centro Pokemon mais proximo
            int localizacao;
            cout << "Qual cidade voc� est� no momento? (Digite o c�digo, por favor): " << endl;
            cin >> localizacao;

            while(cin.fail())
            {
                limparCin();
                cout << "Entrada inv�lida. Digite o c�digo da cidade novamente: " << endl;
                cin >> localizacao;
            }

            CentroProximo(grafo, cidades, vertices,localizacao); //aqui chat
            break;
        
        case 4:                 //Cadastrar pokemon
            onConstruct();
            break;
        
        case 5:                 //Remover pokemon
            onConstruct();
            break;
        
		case 6:                 //Listar pokes por ordem alfabetica do nome
            onConstruct();
            break;
        
		case 7:                 //Listar pokes por ordem alfabetica por tipo
            onConstruct();
            break;
        
		case 8:                 //Contar pokes de cada tipo
            onConstruct();
            break;
        
		case 9:                 //Encontrar pokes pr�ximos
            onConstruct();
            break;
        
		case 10:
    		ListarCidades(cidades);
    		break;
		
		case 11:
    		ListarEstradas(cidades, grafo);
    		break;
        
		default:     
            cout << "Op��o inv�lida, Jovem Treinador! " << endl;
            break;
        }

    }

    return 0;
}