#include <bits/stdc++.h>

using namespace std;


class Tabuleiro {
    public:
        int **mapa;
        int tam;

        void setTam(int N) {
            tam = N;
        }

        void iniciaMapa() {
            mapa = new int *[tam];

            for (int i = 0; i < tam; ++i) {
                mapa[i] = new int[tam];
            }
        }

        void printMapa() {
            for (int i = 0; i < tam; ++i) {
                for (int j = 0; j < tam; ++j) {
                    cout << mapa[i][j] << " ";
                }
                //cout << "\n";
            }
        }
};

class Personagem {
    public:
        bool intangivel;
        int i, j, distMax;

        void traduzMovimento(char c) {
            if(c == 'U')
                cima();
            else if(c == 'D')
                baixo();
            else if(c == 'R')
                direita();
            else if(c == 'L')
                esquerda();
        }

        void cima() {
            i = i - 1;
        }

        void baixo() {
            i = i + 1;
        }

        void direita() {
            j = j + 1;
        }

        void esquerda() {
            j = j - 1;
        }
};

char movimento_pacman(int i, int j, int x, int y){
    //cima
    if(i - 1 == x && j == y){
        return 'U';
    
    }//baixo
    if(i + 1 == x && j == y){
        return 'D';
    }
    //direita
    if(i == x && j + 1 == y){
        return 'R';
    }
    //esquerda
    if(i == x && j - 1== y){
        return'L';
    }

    return 'i'; //invalido

}


class ContadorPassos {
    public:
        int cima = 0, baixo = 0, direita = 0, esquerda = 0;

        void contaPasso(char c) {
            if(c == 'U')
                cima = cima + 1;
            else if(c == 'D')
                baixo = baixo + 1;
            else if(c == 'R')
                direita = direita + 1;
            else if(c == 'L')
                esquerda = esquerda + 1;
        }
};

bool movimentoFantasma(vector<char> &movimentos, Personagem &fantasma) {
    if(movimentos.size() == 0) return false;

    char movimento = movimentos[0];

    fantasma.traduzMovimento(movimento);

    movimentos.erase(movimentos.begin());

    return true;
}

void movimentoPacman(vector<char> &melhorCaminho, Personagem &pacman, ContadorPassos &contadorPasso) {
    if(melhorCaminho.size() == 0) return;

    char movimento = melhorCaminho[0];

    pacman.traduzMovimento(movimento);
    contadorPasso.contaPasso(movimento);

    melhorCaminho.erase(melhorCaminho.begin());

    return;
}

struct No {
    int linha;
    int coluna;
    int distancia;
};

bool e_celula_valida(int linha, int coluna, int numLinha, int numcolunas) {
    return (linha >= 0 && linha < numLinha && coluna >= 0 && coluna < numcolunas);
}

vector<No> menor_caminho_encontrado(vector<vector<int>>& grafo, int inicio_linha, int inicio_coluna, int objetivo_lin, int objetivo_coluna) {
    int numLinha = grafo.size();
    int numcolunas = grafo[0].size();

    int dr[] = {0, -1, 1, 0}; // Vetor de deslocamento para linhas (cima, baixo, direita, esquerda)
    int dc[] = {1, 0, 0, -1}; // Vetor de deslocamento para colunas (cima, baixo, direita, esquerda)

    vector<vector<bool>> no_visitado(numLinha, vector<bool>(numcolunas, false));
    vector<vector<No>> no_pai(numLinha, vector<No>(numcolunas, { -1, -1, -1 }));

    queue<No> q;
    q.push({inicio_linha, inicio_coluna, 0});
    no_visitado[inicio_linha][inicio_coluna] = true;

    //logica da BFS adaptada
    while (!q.empty()) {
        No curr = q.front();
        q.pop();

        int linha_atual = curr.linha;
        int colunauna_atual = curr.coluna;
        int distancia_atual = curr.distancia;

        if (linha_atual == objetivo_lin && colunauna_atual == objetivo_coluna) {
            vector<No> caminho;
            while (linha_atual != -1 && colunauna_atual != -1) {
                caminho.push_back({ linha_atual, colunauna_atual, distancia_atual });
                int newlinha = no_pai[linha_atual][colunauna_atual].linha;
                int newcoluna = no_pai[linha_atual][colunauna_atual].coluna;
                linha_atual = newlinha;
                colunauna_atual = newcoluna;
                distancia_atual--;
            }

            // Inverter o caminho para obter a ordem correta
            reverse(caminho.begin(), caminho.end());
            return caminho;
        }

        for (int i = 0; i < 4; i++) {
            int newlinha = linha_atual + dr[i];
            int newcoluna = colunauna_atual + dc[i];

            // Verificar se a célula vizinha é válida (dentro dos limites do grafo)
            // e se não foi visitada anteriormente e se é uma célula livre (valor 0 no grafo)
            if (e_celula_valida(newlinha, newcoluna, numLinha, numcolunas) && !no_visitado[newlinha][newcoluna] && grafo[newlinha][newcoluna] == 0) {
                q.push({ newlinha, newcoluna, distancia_atual + 1 });
                no_visitado[newlinha][newcoluna] = true;
                no_pai[newlinha][newcoluna] = { linha_atual, colunauna_atual, distancia_atual };
            }
        }
    }

    return {};  // Retornar um vetor vazio caso não seja possível encontrar um caminho
}

void convertTabuleiroTografo(const Tabuleiro& tabuleiro, vector<vector<int>>& grafo) {
    int tam = tabuleiro.tam;
    grafo.clear();
    grafo.resize(tam, vector<int>(tam));

    for (int i = 0; i < tam; i++) {
        for (int j = 0; j < tam; j++) {
            grafo[i][j] = tabuleiro.mapa[i][j];
        }
    }
}


int main()
{	 
    //recebe a entrada
	int N, M;
    ContadorPassos contadorPasso;
    vector<char> movimentos;

    cin >> N;
    Tabuleiro tabuleiro;
    tabuleiro.setTam(N);
    tabuleiro.iniciaMapa();

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cin >> tabuleiro.mapa[i][j];
        }
    }

    Personagem pacman;
    cin >> pacman.i;
    cin >> pacman.j;
    pacman.intangivel = false;

    Personagem fantasma;
    cin >> fantasma.i;
    cin >> fantasma.j;
    fantasma.intangivel = true;

    cin >> M;
    char aux;
    for (int i = 0; i < M; ++i) {
        cin >> aux;
        movimentos.push_back(aux);
    }

    int inicio_linha = pacman.i;
    int inicio_coluna = pacman.j;
    int objetivo_lin;
    int objetivo_coluna;
    
    vector<vector<int>> grafo;
    convertTabuleiroTografo(tabuleiro,grafo);


    vector<char>melhorCaminho;
    
    int cont = M;
    vector<No> caminho_mais_curto;

    int ultimoNolinha, ultimoNocoluna;    

    do { 
        objetivo_lin = fantasma.i;
        objetivo_coluna = fantasma.j;

        // Atualizar a posição do Pacman com o último nó do caminho mais curto encontrado
        caminho_mais_curto = menor_caminho_encontrado(grafo, pacman.i, pacman.j, objetivo_lin, objetivo_coluna);
        if(!caminho_mais_curto.empty()) {
            for (const No& No : caminho_mais_curto) {
                ultimoNolinha = No.linha;
                ultimoNocoluna = No.coluna;
            }

            // Verificar se o caminho mais curto possui pelo menos dois nós
            if (caminho_mais_curto.size() >= 2) {
                const No& secondNo = caminho_mais_curto[1];
                ultimoNolinha = secondNo.linha;
                ultimoNocoluna = secondNo.coluna;
            }

            pacman.i = ultimoNolinha;
            pacman.j = ultimoNocoluna;

        }
        
        movimentoFantasma(movimentos, fantasma);
        cont--;
    }while(cont >= 0);


    ultimoNolinha = inicio_linha;
    ultimoNocoluna = inicio_coluna; 

    // Percorrer o caminho mais curto encontrado e adicionar os movimentos correspondentes ao melhor caminho
    for (const No& No : caminho_mais_curto) {
        char auxxx = movimento_pacman(ultimoNolinha, ultimoNocoluna, No.linha, No.coluna);
        if(auxxx != 'i') melhorCaminho.push_back(auxxx);

        ultimoNolinha = No.linha;
        ultimoNocoluna = No.coluna;
        
        movimentoPacman(melhorCaminho, pacman, contadorPasso);
    }

    if(!caminho_mais_curto.empty() || (ultimoNolinha = fantasma.i && ultimoNocoluna == fantasma.j)){
        cout << "Número de passos: " << contadorPasso.cima + contadorPasso.baixo + contadorPasso.direita + contadorPasso.esquerda << "\n";
        cout << "Movimentos para cima: " << contadorPasso.cima << "\n";
        cout << "Movimentos para baixo: " << contadorPasso.baixo << "\n";
        cout << "Movimentos para esquerda: " << contadorPasso.esquerda << "\n";
        cout << "Movimentos para direita: " << contadorPasso.direita << "\n";
    } else {
        cout << "Não foi possível achar um caminho";
    }

	return 0;
}