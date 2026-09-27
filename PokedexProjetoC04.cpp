//=====================================================
//                Projeto de Pokedex
//=====================================================
// Integrantes:
// Kauã Aparecido Silva Morais       - GES - 756
// Ana Clara Oliveira e Silva        - GES - 867
// Túlio César Alves Junho           - GES - 741
// João Vitor Lima da Silveira       - GES - 500
// Vitoria Cássia Bernardo Rodrigues - GEC - 2094
#define INF 99999

#include <iostream> 
#include <locale>
#include <cstdlib>
#include <list>
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
  

int menu(){                 //Exibe o menu da pokedex
    int decisao = -1;

    cout << "  ====================================================================================================================" << endl;
    cout << "                                                     POKEDEX                " << endl;
    cout << "  ====================================================================================================================" << endl;
    cout << "\n# Olá, Jovem Treinador! Essa é a Pokédex, sua maior aliada em sua jornada de se tornar o melhor treinador dos Pokémons!" << endl;
    cout << endl;
    cout << "Faça sua escolha: " << endl;
    cout << endl;
    cout << "[1] Cadastrar Cidade. " << endl;
	cout << "[2] Cadastrar Estrada. " << endl;
	cout << "[3] Buscar Centro Pokémon mais próximo. " << endl;
	cout << "[4] Cadastrar Pokémon. " << endl;
	cout << "[5] Remover Pokémon. " << endl;
	cout << "[6] Listar Pokémons (ordem alfabética por nome). " << endl;
	cout << "[7] Listar Pokemons (ordem alfabética por tipo). " << endl;
	cout << "[8] Contar Pokémons de cada Tipo. " << endl;
	cout << "[9] Encontrar Pokémons próximos. " << endl;
	cout << "[10] Listar Cidades. " << endl;
	cout << "[11] Listar Estradas. " << endl;
	cout << "[0] Sair do Programa. " << endl;
    cout << endl;

    cin >> decisao;

    return decisao;
}

void onConstruct(){
    cout << "Funcionalidade em Construcao... \n" << endl;
}

void CadastrarCidade(list<Cidade>& cidades, int& vertices)
{
	Cidade nova;
	
	cout << "Insira o nome da cidade a ser cadastrada: " << endl;
	getline(cin >> ws, nova.nome);
	
	nova.codigo = vertices + 1;
	
	cout << "Essa cidade tem um Centro Pokémon? (1 - Sim / 0 - Não): " << endl;

    int temCentro;
    cin >> temCentro;

    while(temCentro != 1 && temCentro != 0){
        cout << "Digite um valor válido por favor!" << endl;
        cin >> temCentro;
    }

    nova.centro = temCentro; // int 0/1 -> bool false/true, conversão automática e segura
	
	cidades.push_back(nova);
	
	vertices++;
	
	cout << "Cidade cadastrada!\n"; 
	cout << "Código da cidade: " << nova.codigo << endl << endl;
}

void CadastrarEstrada(list<Aresta> grafo[], int vertices)
{
	int origem, destino, peso;

    cout << "Insira o código da cidade de origem: ";
    cin >> origem;

    cout << "Insira o código da cidade de destino: ";
    cin >> destino;

	if(origem < 1 || origem > vertices || destino < 1 || destino > vertices)
    {
        cout << "Código de cidade inválido!\n" << endl;
        return;
    }
	
    cout << "Distância da estrada: ";
    cin >> peso;

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
	
		cout << "Nome:" << cidade -> nome << " | Código:" << cidade -> codigo; 
		cout << " | Centro Pokémon:";

        if(cidade -> centro)
            cout << "Sim";
        else
            cout << "Não";

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
        // pega o código da cidade e diminui 1 pra usar como índice do grafo (já que vetor começa em 0)
        int i = cidade -> codigo - 1;

        // percorre as estradas que saem da cidade atual
        for(it = grafo[i].begin(); it != grafo[i].end(); it++)
        {
            // pra percorrer a lista de cidades e ver qual é o destino
            list<Cidade>::iterator destino;

            // percorre todas as cidades procurando o destino da estrada
            for(destino = cidades.begin(); destino != cidades.end(); destino++)
            {
                // ve se o código da cidade de destino é igual ao destino da estrada
                if(destino -> codigo == it -> destino + 1)
                    cout << cidade -> nome << " -> " << destino -> nome << " | Distância: " << it -> peso << endl;
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

    int origem = origemCodigo - 1; // converte código digitado -> índice

    if(origem < 0 || origem >= totalcidades)
    {
        cout << "Código de cidade inválido!" << endl;
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
        cout << "Nenhum centro Pokemon encontrado" << endl;
        return -1;
    }

    cout << "Centro Pokemon encontrado na cidade " << nomeCidade[melhorcidade] << endl;
    cout << "Distancia total: " << menordistancia << endl;

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

    //Começo do código
    
    list<Cidade> cidades;
    
    int vertices = 0;

    list<Aresta> grafo[100];
    
    int decisao = -1;

    while(decisao != 0){

        decisao = menu();

            switch (decisao)        //Switch que controla a entrada desejada do usuário.
        {
        case 0:                 //Encerrando o programa
            cout << "\nPokédex desligando... Pika Pika :(\n" << endl;
            return 0;
            
        case 1:                 //Cadastrar cidade
            CadastrarCidade(cidades, vertices);     
            break;
        
        case 2:                 //Cadastrar estradas
            CadastrarEstrada(grafo, vertices);      
            break;
        
        case 3:                 //Buscar centro Pokemon mais proximo
            int localizacao;
            cout << "Qual cidade vc esta no momento?(Digite o codigo por favor" << endl;
            cin >> localizacao;
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
        
		case 9:                 //Encontrar pokes próximos
            onConstruct();
            break;
        
		case 10:
    		ListarCidades(cidades);
    		break;
		
		case 11:
    		ListarEstradas(cidades, grafo);
    		break;
        
		default:     
            cout << "Opção inválida, Jovem Treinador! " << endl;
            break;
        }

    }
    
    

    return 0;
}