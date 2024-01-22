# Desafio Pacman - Trabalho de Grafos
Código feito em colaboração com https://github.com/Gustavo-de-Oliveira

## Obs:
Para melhores detalhes verifique o PDF com a descrição do projeto.

## Introdução

Pacman é um jogo clássico lançado em 1980, onde o jogador controla um personagem em um labirinto, tentando evitar fantasmas. Neste desafio, você assume o papel do Pacman após adquirir poderes especiais e seu objetivo é alcançar um fantasma em um tabuleiro, fazendo o menor número de movimentos possível.

# Abordagem do Código

Este programa implementa uma solução para o desafio do Pacman, onde o objetivo é fazer com que o Pacman alcance um fantasma em um tabuleiro, evitando obstáculos. Aqui está uma breve explicação da abordagem utilizada:

1. **Estruturas de Dados:**
   - Foram definidas classes para representar o tabuleiro (`Tabuleiro`), os personagens (`Personagem`), e um contador de passos (`ContadorPassos`).
   - Utilização de estruturas como a fila e matriz para representar o grafo do tabuleiro.

2. **Movimentação do Pacman e Fantasma:**
   - Cada personagem possui métodos para traduzir os movimentos (cima, baixo, direita, esquerda).
   - As movimentações são feitas baseadas em listas de caracteres, sendo removido o primeiro caractere após cada movimento.

3. **Busca do Menor Caminho:**
   - Utilização da BFS (Busca em Largura) para encontrar o menor caminho entre o Pacman e o Fantasma no tabuleiro.
   - O caminho é armazenado em uma lista de estruturas `No` representando cada posição.

4. **Conversão de Tabuleiro para Grafo:**
   - Função para converter o tabuleiro em uma representação de grafo, facilitando a aplicação da BFS.

5. **Execução do Jogo:**
   - O jogo é simulado movendo o Pacman em direção ao Fantasma com base no menor caminho encontrado.
   - O Fantasma realiza seus movimentos conforme uma lista pré-definida.

6. **Saída:**
   - Ao final, são exibidos o número total de passos realizados pelo Pacman e a contagem de movimentos em cada direção.
   - Se não for possível alcançar o Fantasma, uma mensagem indicando a impossibilidade é exibida

## Como Compilar

Certifique-se de ter um compilador C++ instalado. Para compilar o arquivo `main.cpp`, utilize o seguinte comando no terminal:

```bash
g++ main.cpp -o teste

./teste
