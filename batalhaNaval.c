#include <stdio.h> // Biblioteca para entrada e saída (printf, scanf)

// Define constantes para o tamanho do tabuleiro, navio e os valores das celulas
#define TAM_TABULEIRO 10
#define TAM_NAVIO 3
#define AGUA 0
#define NAVIO 3
#define HABILIDADE 5

// Preenche todo o tabuleiro com o valor de AGUA (0)
void inicializarTabuleiro(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO]) {
    // Percorre linhas
    for (int i = 0; i < TAM_TABULEIRO; i++) {
        // Percorre colunas
        for (int j = 0; j < TAM_TABULEIRO; j++) {
            tabuleiro[i][j] = AGUA; // Define a celula como agua
        }
    }
}

// Verifica se um navio pode ser colocado na posicao dada
// Checa limites do tabuleiro e se as casas estao livres (AGUA)
// Retorna 1 se for possivel, 0 caso contrario
int verificarPosicaoLivre(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int linha, int coluna, int orientacao, int tamanho) {
    // Verifica cada parte do navio
    for (int i = 0; i < tamanho; i++) {
        int l = linha, c = coluna;
        // Calcula a coordenada da parte atual baseado na orientacao
        if (orientacao == 0) { // Horizontal
            c += i;
        } else if (orientacao == 1) { // Vertical
            l += i;
        } else if (orientacao == 2) { // Diagonal Principal
            l += i; c += i;
        } else if (orientacao == 3) { // Diagonal Secundaria
             l += i; c -= i;
        }

        // Verifica se a coordenada esta fora do tabuleiro
         if (l < 0 || l >= TAM_TABULEIRO || c < 0 || c >= TAM_TABULEIRO) {
             return 0; // Fora dos limites
         }
         // Verifica se a coordenada nao e agua (ja esta ocupada)
         if (tabuleiro[l][c] != AGUA) {
            return 0; // Ocupado
         }
    }
    return 1; // Todas as posicoes estao validas e livres
}


// Tenta colocar um navio na horizontal
void posicionarNavioHorizontal(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int linha, int coluna) {
    // Verifica se a posicao e valida e livre
    if (coluna + TAM_NAVIO <= TAM_TABULEIRO && verificarPosicaoLivre(tabuleiro, linha, coluna, 0, TAM_NAVIO)) {
        // Coloca o navio (valor NAVIO)
        for (int i = 0; i < TAM_NAVIO; i++) {
            tabuleiro[linha][coluna + i] = NAVIO;
        }
         printf("Navio horizontal posicionado em (%d, %d)\n", linha, coluna);
    } else {
        // Informa se nao foi possivel
        printf("Posicao horizontal invalida ou ocupada em (%d, %d).\n", linha, coluna);
    }
}

// Tenta colocar um navio na vertical
void posicionarNavioVertical(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int linha, int coluna) {
    // Verifica se a posicao e valida e livre
    if (linha + TAM_NAVIO <= TAM_TABULEIRO && verificarPosicaoLivre(tabuleiro, linha, coluna, 1, TAM_NAVIO)) {
        // Coloca o navio (valor NAVIO)
        for (int i = 0; i < TAM_NAVIO; i++) {
            tabuleiro[linha + i][coluna] = NAVIO;
        }
         printf("Navio vertical posicionado em (%d, %d)\n", linha, coluna);
    } else {
        printf("Posicao vertical invalida ou ocupada em (%d, %d).\n", linha, coluna);
    }
}

// Tenta colocar um navio na diagonal principal (\)
void posicionarNavioDiagonalPrincipal(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int linha, int coluna) {
    // Verifica se a posicao e valida e livre
    if (linha + TAM_NAVIO <= TAM_TABULEIRO && coluna + TAM_NAVIO <= TAM_TABULEIRO && verificarPosicaoLivre(tabuleiro, linha, coluna, 2, TAM_NAVIO)) {
        // Coloca o navio (valor NAVIO)
        for (int i = 0; i < TAM_NAVIO; i++) {
            tabuleiro[linha + i][coluna + i] = NAVIO;
        }
         printf("Navio diag principal posicionado em (%d, %d)\n", linha, coluna);
    } else {
        printf("Posicao diag principal invalida ou ocupada em (%d, %d).\n", linha, coluna);
    }
}

// Tenta colocar um navio na diagonal secundaria (/)
void posicionarNavioDiagonalSecundaria(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int linha, int coluna) {
    // Verifica se a posicao e valida e livre
     if (linha + TAM_NAVIO <= TAM_TABULEIRO && coluna - TAM_NAVIO + 1 >= 0 && verificarPosicaoLivre(tabuleiro, linha, coluna, 3, TAM_NAVIO)) {
        // Coloca o navio (valor NAVIO)
        for (int i = 0; i < TAM_NAVIO; i++) {
            tabuleiro[linha + i][coluna - i] = NAVIO;
        }
         printf("Navio diag secundaria posicionado em (%d, %d)\n", linha, coluna);
    } else {
        printf("Posicao diag secundaria invalida ou ocupada em (%d, %d).\n", linha, coluna);
    }
}


// Mostra o estado atual do tabuleiro no console
void exibirTabuleiro(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO]) {
    printf("\n   "); // Espaco para alinhar indices das colunas
    // Imprime indices das colunas
    for(int j = 0; j < TAM_TABULEIRO; j++){
        printf("%d ", j);
    }
    printf("\n");
    // Percorre linhas
    for (int i = 0; i < TAM_TABULEIRO; i++) {
         printf("%d  ", i); // Imprime indice da linha
         // Percorre colunas
        for (int j = 0; j < TAM_TABULEIRO; j++) {
            printf("%d ", tabuleiro[i][j]); // Imprime valor da celula
        }
        printf("\n"); // Pula linha no final de cada linha do tabuleiro
    }
     printf("\nLegenda: %d=Agua, %d=Navio, %d=Habilidade\n", AGUA, NAVIO, HABILIDADE); // Explica os numeros
}

// Aplica o efeito de uma habilidade no tabuleiro
// Usa uma matriz pequena (habilidade) para marcar o tabuleiro principal
void aplicarHabilidadeGenerica(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int habilidade[5][5], int dim_habilidade, int origemX, int origemY) {
    // Acha o centro da matriz de habilidade para alinhar
    int offset = dim_habilidade / 2;

    // Percorre a matriz da habilidade (linhas e colunas)
    for (int i = 0; i < dim_habilidade; i++) {
        for (int j = 0; j < dim_habilidade; j++) {
            // Se essa parte da habilidade deve ter efeito (valor 1)
            if (habilidade[i][j] == 1) {
                // Calcula a coordenada correspondente no tabuleiro principal
                int x = origemX + i - offset;
                int y = origemY + j - offset;

                // Verifica se a coordenada calculada esta dentro do tabuleiro
                if (x >= 0 && x < TAM_TABULEIRO && y >= 0 && y < TAM_TABULEIRO) {
                    // Marca com HABILIDADE (5) apenas se for AGUA (0)
                    if (tabuleiro[x][y] == AGUA) {
                         tabuleiro[x][y] = HABILIDADE;
                    }
                }
            }
        }
    }
}

// Usa a habilidade Cone
void aplicarCone(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int origemX, int origemY) {
    // Matriz que representa o formato do cone
    int cone[5][5] = {
        {0, 0, 1, 0, 0},
        {0, 1, 1, 1, 0},
        {1, 1, 1, 1, 1},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0}
    };
     printf("Aplicando Cone em (%d, %d)\n", origemX, origemY);
     // Chama a funcao generica para aplicar o formato
    aplicarHabilidadeGenerica(tabuleiro, cone, 5, origemX, origemY);
}

// Usa a habilidade Cruz
void aplicarCruz(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int origemX, int origemY) {
    // Matriz que representa o formato da cruz
    int cruz[5][5] = {
        {0, 0, 1, 0, 0},
        {0, 0, 1, 0, 0},
        {1, 1, 1, 1, 1},
        {0, 0, 1, 0, 0},
        {0, 0, 1, 0, 0}
    };
     printf("Aplicando Cruz em (%d, %d)\n", origemX, origemY);
     // Chama a funcao generica para aplicar o formato
    aplicarHabilidadeGenerica(tabuleiro, cruz, 5, origemX, origemY);
}

// Usa a habilidade Octaedro
void aplicarOctaedro(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int origemX, int origemY) {
    // Matriz que representa o formato do octaedro
    int octaedro[5][5] = {
        {0, 0, 1, 0, 0},
        {0, 1, 1, 1, 0},
        {1, 1, 1, 1, 1},
        {0, 1, 1, 1, 0},
        {0, 0, 1, 0, 0}
    };
     printf("Aplicando Octaedro em (%d, %d)\n", origemX, origemY);
     // Chama a funcao generica para aplicar o formato
    aplicarHabilidadeGenerica(tabuleiro, octaedro, 5, origemX, origemY);
}

// Funcao principal onde o programa executa
int main() {

    // Declara a matriz do tabuleiro
    int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO];
    // Preenche o tabuleiro com agua
    inicializarTabuleiro(tabuleiro);
    printf("Tabuleiro Inicial:\n");
    // Mostra o tabuleiro vazio
    exibirTabuleiro(tabuleiro);

    // Posiciona os 4 tipos de navios
    printf("\n--- Posicionando Navios ---\n");
    posicionarNavioHorizontal(tabuleiro, 0, 0);
    posicionarNavioVertical(tabuleiro, 2, 8);
    posicionarNavioDiagonalPrincipal(tabuleiro, 4, 1);
    posicionarNavioDiagonalSecundaria(tabuleiro, 7, 6);

    printf("\nTabuleiro apos posicionar navios:\n");
    // Mostra o tabuleiro com os navios
    exibirTabuleiro(tabuleiro);

    // Aplica as 3 habilidades em posicoes diferentes
     printf("\n--- Aplicando Habilidades ---\n");
    aplicarCone(tabuleiro, 2, 3);
    aplicarCruz(tabuleiro, 5, 5);
    aplicarOctaedro(tabuleiro, 8, 8);

    printf("\nTabuleiro Final com Habilidades:\n");
    // Mostra o tabuleiro final
    exibirTabuleiro(tabuleiro);

    return 0; // Indica que o programa terminou sem erros
}
