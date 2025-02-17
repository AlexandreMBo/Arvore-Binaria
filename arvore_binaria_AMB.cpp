#include <iostream>
#include <cstdlib>
#include <stack>
using namespace std;

 typedef struct no {
 int chave ;
 int contador ; // frequencia observada da chave
 struct no * esq ; // ponteiro para subarvore esquerda
 struct no * dir ; // ponteiro para subarvore direita
 }NO , * PONT ;

 void inicializar(PONT* raiz){
    *raiz=NULL;
 }

 PONT criarNo (int valor){
    PONT novo = (PONT) malloc(sizeof(NO)); //alocar memória para novo nó

    // confere se a aloção funcionou corretamente
    if (novo){
    novo->chave = valor;
    novo->contador = 1;
    novo->esq = NULL;
    novo->dir = NULL;
    }
    return novo;
 }

 // funcao de busca na arvore
 PONT buscar (PONT raiz, int valor) {
    if (raiz == NULL) {   //verificar se a raiz está vazia
        return raiz;
    }
    else if (valor < raiz->chave) {   // menor desce o ramo esquerdo
        return buscar (raiz->esq, valor);
    }
    else if (valor > raiz->chave) {    // maior desce o ramo direito
        return buscar (raiz->dir, valor);
    }
    else {      // se for igual retorna o valor da raiz
        return raiz;
    }
    return NULL;
 }

 // Inserir na arvore
 PONT inserir (PONT raiz, int valor) {
    if (raiz == NULL){
        return criarNo (valor);  // Se estiver a posicao vazia (NULL) insere
    }
    else if (valor < raiz->chave){    // se for menor esquerda
        raiz->esq = inserir (raiz->esq, valor);
    }
    else if (valor > raiz->chave){    // se for maior direita
        raiz->dir = inserir (raiz->dir, valor);
    }
    else {     // se for igual soma 1 ao contador
        raiz->contador = raiz->contador + 1;
    }
    return raiz;
 }

 //Remover 1 ocorrencia
PONT removerUmaOcorrencia (PONT raiz, int valor) {
    if (raiz == NULL){  //arvore vazia
        return raiz;
    }
    else if (valor == raiz->chave){
        if (raiz->contador > 1){    //Se o contador esta maior que 1, apenas reduz a contagem, pois continua existindo outro valor equivalente
            raiz->contador = raiz->contador -1;
            }
        else {  // aqui o contador é igual a 1, ou seja, quando removermos, iremos remover o no
            if (raiz->esq == NULL && raiz->dir == NULL) {   //se o no nao tem filhos, elimina e limpa
                free(raiz);
                return NULL;
        }
            else if (raiz->esq != NULL && raiz->dir==NULL){ //apenas filho da esquerda
                PONT temporario = raiz->esq;  //variavel temporaria recebe o valor do filho a esquerda que sera o novo no
                free(raiz);
                return temporario;
            }
            else if (raiz->esq==NULL && raiz->dir!=NULL){   //apenas filho da direita
                PONT temporario = raiz->dir;    //variavel temporaria recebe o valor do filho a direita que sera o novo no
                free(raiz);
                return temporario;
            }
            else{
                PONT temporario = raiz->dir; //vamos substituir pelo ponto mais a esquerda da subarvore direita do no que estamos removendo
                while (temporario->esq != NULL){
                    temporario = temporario->esq;
                }
                raiz->chave = temporario->chave;
                raiz->contador = temporario->contador;
                raiz->dir = removerUmaOcorrencia (raiz->dir, temporario->chave);     // Apos transformar o ponto mais a esquerda da direita no no, temos que remover ele da posicao atual
            }
        }
    }
    else if (valor<raiz->chave){
        raiz->esq = removerUmaOcorrencia (raiz->esq, valor);
    }
    else if (valor>raiz->chave){
        raiz->dir = removerUmaOcorrencia (raiz->dir, valor);
    }
    return raiz;
}

//Remover todas as ocorrencias
PONT removerTodasOcorrencias(PONT raiz, int valor) {
    if (raiz == NULL) {  // arvore vazia
        return raiz;
    }

    // Caso o valor seja igual ao valor do no atual
    if (valor == raiz->chave) {
        if (raiz->esq == NULL && raiz->dir == NULL) {   // no sem filhos, limpa
            free(raiz);
            return NULL;
        }

        else if (raiz->esq != NULL && raiz->dir == NULL) {  //se o tem apenas o filho da esquerda, esse vira o no
            PONT temporario = raiz->esq;    // variavel temporaria para auxiiliar
            free(raiz);
            return temporario;
        }

        else if (raiz->esq == NULL && raiz->dir != NULL) {   //se o no tem apenas o filho da direita esse vira o no
            PONT temporario = raiz->dir;    //variavel temporaria para auxiliar
            free(raiz);
            return temporario;
        }

        else {
            PONT temporario = raiz->dir;  //se o no tem dois filhos, substituiremos pelo ponto mais a esquerda da subarvore direita
            while (temporario->esq != NULL) {
                temporario = temporario->esq;
            }
            raiz->chave = temporario->chave;
            raiz->contador = temporario->contador;
            raiz->dir = removerTodasOcorrencias(raiz->dir, temporario->chave);  // Remover o no que foi transferido para o no removido
        }
    }

    else if (valor < raiz->chave) {
        raiz->esq = removerTodasOcorrencias(raiz->esq, valor);  //se menor busca na esquerda
    }
    else {
        raiz->dir = removerTodasOcorrencias(raiz->dir, valor);  //se maior, busca na direita
    }

    return raiz;
}

//Exibir na ordem

void exibirInOrder(PONT raiz) { //vai ate o valor mais a esquerda e começa a imprimir (esquerda, no, direita, sobe...)
    if (raiz == NULL) {
        return;  //se for NULL a arvore eta vazia
    }
    
    exibirInOrder(raiz->esq);

    for (int i = 0; i < raiz->contador; i++) {
        cout << raiz->chave << ", ";
    }

    exibirInOrder(raiz->dir);
}

// Contador de nos

int contarNos (PONT raiz){  //tem uma ideia semelhante a da função de exibir nos, vai ate a esquerda e volta contando (esquerda, no, direita, sobe...)
    int contnos = 0;
    
    if (raiz == NULL){
        return 0;
    }
    contnos = contnos + contarNos(raiz->esq);
    
    contnos = contnos + 1;
    
    contnos = contnos + contarNos(raiz->dir);

    
    return contnos;
}

//Contador de elementos (inclusive as repetiçoes de um mesmo valor)

int contarTotalElementos(PONT raiz){
    int total_elementos = 0;
    
    if (raiz == NULL){
        return 0;
    }
    total_elementos = total_elementos + contarTotalElementos (raiz->esq);
    
    for (int i = 0; i<raiz->contador; i++){
        total_elementos = total_elementos + 1;
    }
    total_elementos = total_elementos + contarTotalElementos(raiz->dir);
    
    return total_elementos;
}

// encontrar k-esimo menor valor
int kEsimoMenor(PONT raiz, int k) {
    if (raiz == NULL) {
        return -1;  // no caso da arvore vazia nao retornamos nada
    }

    stack<PONT> pilha;  // criamos uma pilha temporaria para controle do percurso
    PONT atual = raiz;
    

    while (atual != NULL || !pilha.empty()) {       //empilhando os elementos a partir da subarvore esquerda
        while (atual != NULL) {
            pilha.push(atual);
            atual = atual->esq;
        }
        
        atual = pilha.top();
        pilha.pop();

        for (int i = 0; i < atual->contador; i++) {
            k = k-1;  // subtraimos de  k, pois encontramos um novo valor
            if (k == 0) {
                return atual->chave;  // quando k chega a zero, retorna o valor que representa o k-esimo menor valor
            }
        }


        atual = atual->dir; // se a pilha atual nao satisfaz o valor de k, vai pela subarvore da direita
    }

    return -1;  // quando k e maior que o numero de elementos na arvore ele deve retornar -1, pois o k-esimo valor nao existira
}

// Imprimir dentro de um intervalo de valores (min - max)

void imprimirIntervalo (PONT raiz, int min, int max){
    if (raiz==NULL){    //quando a arvore esta vazia nao ha o que imprimir
        return;
    }
    if (raiz->chave >=min && raiz->chave <=max){    //quando o valor do no esta entre o minimo e o maximo, imprime o valor
        cout<<raiz->chave<<", ";
        
        imprimirIntervalo(raiz->esq, min, max);  // continua buscando na subarvore esquerda
        imprimirIntervalo(raiz->dir, min, max);  // continua buscando na subarvore direita
    }
    if (raiz->chave <min){                     //se o valor do no e menor que o minimo busca na subarvore direita, pois na subarvore esquerda so tem valores menores
        imprimirIntervalo(raiz->dir, min, max);
    }
    if (raiz->chave >max){
        imprimirIntervalo(raiz->esq, min, max);     //se o valor do no e maior que o maximo busca na subarvore esquerda, pois na subarvore direita so tem valores maiores
    }
}

// Funcao do Lowest Commom Ancestor (LCA)

PONT lowestCommonAncestor(PONT raiz, int val1, int val2){
    if (raiz == NULL){
        return NULL;        //quando a arvore esta vazia retorna NULL apenas
    }
    if (val1 < raiz->chave && val2 < raiz->chave) {     //caso ambos valores sejam menores que a no, buscamos o LCA na subarvore esquerda
        return lowestCommonAncestor(raiz->esq, val1, val2);
    }
    else if (val1 > raiz->chave && val2 > raiz->chave){
        return lowestCommonAncestor(raiz->dir, val1, val2); //por outro lado se ambos os valores sao maiores que o no, buscamos o LCA na subarvore direita
    }
    else{
        return raiz;        //se cada um dos valores esta para um lado, encontramos aqui o no LCA de ambos valores
    }
}


// main() para testes com expectativas de resultado
int main() {
    // PONT raiz;                    // ponteiro para a raiz da BST
    // inicializar(&raiz);           // deixa a árvore vazia
    // 
    // As funções a serem implementadas:
    //   - criarNo
    //   - inserir
    //   - removerUmaOcorrencia
    //   - removerTodasOcorrencias
    //   - buscar
    //   - exibirInOrder
    //   - contarNos
    //   - contarTotalElementos
    //   - kEsimoMenor
    //   - imprimirIntervalo
    //   - lowestCommonAncestor

    PONT raiz;
    inicializar(&raiz);

    // -------------------------------------------------------
    // 1) Inserção com valores repetidos
    //    Esperado que:
    //      - nó 10 tenha contador=2
    //      - nó 5  tenha contador=3
    //      - nó 15 tenha contador=1
    //      - nó 18 tenha contador=1
    //
    // InOrder final esperado (antes de quaisquer remoções):
    //     "5 5 5 10 10 15 18"
    //
    raiz = inserir(raiz, 10);
    raiz = inserir(raiz, 5);
    raiz = inserir(raiz, 15);
    raiz = inserir(raiz, 10); // Repetido: incrementa o contador
    raiz = inserir(raiz, 5);  // Repetido: incrementa o contador
    raiz = inserir(raiz, 5);  // Repetido: incrementa o contador
    raiz = inserir(raiz, 18);
    
    printf("\n--- APÓS INSERIR (10,5,15,10,5,5,18) ---\n");
    printf("InOrder esperado: 5 5 5 10 10 15 18\n");
    printf("InOrder obtido:   ");
    exibirInOrder(raiz); 
    printf("\n");

    // -------------------------------------------------------
       // -------------------------------------------------------
    // 2) Busca por valores
    PONT node5 = buscar(raiz, 5);
    if(node5) {
        printf("\nBuscar(5): encontrado com contador=%d (esperado=3)\n", node5->contador);
    } else {
        printf("\nBuscar(5): não encontrado (inesperado)\n");
    }

    PONT nodeX = buscar(raiz, 999); // valor não existente
    if(!nodeX) {
        printf("Buscar(999): não encontrado (esperado)\n");
    } else {
        printf("Buscar(999): encontrado??? (inesperado)\n");
    }

    // -------------------------------------------------------
    // 3) Remover UMA ocorrência 
    //    removerUmaOcorrencia(5) => contador(5) deve passar de 3 para 2
    removerUmaOcorrencia(raiz, 5);

    printf("\n--- APÓS removerUmaOcorrencia(5) ---\n");
    printf("Esperado InOrder: 5 5 10 10 15 18\n");
    printf("InOrder obtido:   ");
    exibirInOrder(raiz);
    printf("\n");

    node5 = buscar(raiz, 5);
    if(node5) {
        printf("Agora contador(5)=%d (esperado=2)\n", node5->contador);
    }

    // -------------------------------------------------------
    // 4) Remover TODAS ocorrências
    //    removerTodasOcorrencias(10) => remove nó com chave=10 por completo
    removerTodasOcorrencias(raiz, 10);

    printf("\n--- APÓS removerTodasOcorrencias(10) ---\n");
    printf("Esperado InOrder: 5 5 15 18\n");
    printf("InOrder obtido:   ");
    exibirInOrder(raiz);
    printf("\n");

    // -------------------------------------------------------
    // 5) Contagem de nós e total de elementos
    //    Árvores resultante: {5(cont=2), 15(cont=1), 18(cont=1)}
    //      => contarNos=3   (chaves distintas: 5,15,18)
    //      => contarTotalElementos=4   (5,5,15,18)
    int qtdNos = contarNos(raiz);
    int totalElem = contarTotalElementos(raiz);
    printf("\ncontarNos => %d (esperado=3)\n", qtdNos);
    printf("contarTotalElementos => %d (esperado=4)\n", totalElem);

    // -------------------------------------------------------
    // 6) k-ésimo menor (considerando contadores)
    //    InOrder real: [5,5,15,18]
    //       k=1 => 5
    //       k=2 => 5
    //       k=3 => 15
    //       k=4 => 18
    //       k=5 => -1 (não existe)
    printf("\n--- Teste k-ésimo menor ---\n");
    printf("k=1 => %d (esperado=5)\n", kEsimoMenor(raiz,1));
    printf("k=2 => %d (esperado=5)\n", kEsimoMenor(raiz,2));
    printf("k=3 => %d (esperado=15)\n", kEsimoMenor(raiz,3));
    printf("k=4 => %d (esperado=18)\n", kEsimoMenor(raiz,4));
    printf("k=5 => %d (esperado=-1)\n", kEsimoMenor(raiz,5));

    // -------------------------------------------------------
    // 7) imprimirIntervalo [6..18]
    //    InOrder da árvore: 5,5,15,18
    //    Filtrando [6..18], esperamos: 15 18
    printf("\n--- Teste imprimirIntervalo [6..18] ---\n");
    printf("Esperado: 15 18\nObtido:   ");
    imprimirIntervalo(raiz, 6, 18);
    printf("\n");

    // -------------------------------------------------------
    // 8) Testar LCA (lowestCommonAncestor) - não é opcional
    //    Vamos inserir mais alguns valores para teste de LCA
    //    Situação final da árvore atual: 5(cont=2),15(cont=1),18(cont=1)
    //    Inserir(12), Inserir(16), Inserir(3)
    //    Nova BST (com contadores):
    //       5 (cont=2)
    //           /    \
    //         3(1)   15(1)
    //                /  \
    //              12(1) 18(1)
    //                  \
    //                  16(1)           (16 NA VERDADE E FILHA DO 18)
    raiz = inserir(raiz, 12);
    raiz = inserir(raiz, 16);
    raiz = inserir(raiz, 3);

    printf("\n--- Árvore após inserir(12,16,3) ---\n");
    printf("InOrder esperado: 3 5 5 12 15 16 18\n");
    printf("Obtido:          ");
    exibirInOrder(raiz);
    printf("\n");

    // LCA tests:
    //  LCA(3,5) -> 5 ou 3? 
    //     - 3 e 5 estão ambos na subárvore da raiz=5? 
    //     - Se a raiz é 5, e 3<5 => esq 
    //       => LCA(3,5) deve ser 5, mas depende da estrutura exata
    //  LCA(3,12) -> 5
    //  LCA(16,18) -> 16 ou 15? 
    //     => Analisando: 16 < 18 => 16 deve estar na subárvore direita(15)
    //        -> 15 < 16 => goes right => 18
    //        => 16 < 18 => subárvore esquerda de 18
    //        => LCA deve ser 15 ou 18? Precisamos verificar a implementação.
    //  LCA(5,18) -> 5 (pois 5 é raiz, e 18 está à direita)

    PONT nLCA;

    nLCA = lowestCommonAncestor(raiz, 3, 5);
    if(nLCA) {
        printf("\nLCA(3,5) => chave=%d (esperado=5)\n", nLCA->chave);
    }

    nLCA = lowestCommonAncestor(raiz, 3, 12);
    if(nLCA) {
        printf("LCA(3,12) => chave=%d (esperado=5)\n", nLCA->chave);
    }

    nLCA = lowestCommonAncestor(raiz, 16, 18);
    if(nLCA) {
        printf("LCA(16,18) => chave=%d (esperado=18)\n", nLCA->chave); //O NO COM VALOR 16 NA VERDADE E FILHO DO 18, LOGO A CHAVE ESPERADA DIFERE DA ENCONTRADA
    }

    nLCA = lowestCommonAncestor(raiz, 5, 18);
    if(nLCA) {
        printf("LCA(5,18) => chave=%d (esperado=5)\n", nLCA->chave);
        cout<<endl<<"Neste ultimo ha uma divergencia, pela escolha do metodo de remocao do no"<<endl;
    }

    // Por fim, buscar um LCA com valor inexistente
    nLCA = lowestCommonAncestor(raiz, 100, 3);
    if(!nLCA) {
        printf("LCA(100,3) => NULL (esperado=chave nao existe)\n");
    }

    printf("\n--- FIM DOS TESTES ---\n");

    return 0;
}