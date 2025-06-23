#include "emergencia.h"
#include <math.h>

// ==================== IMPLEMENTAÇÃO - HASH/BAIRROS ====================

// Função hash simples para IDs de bairros
int hash_bairro(int id) {
    return id % TAM_HASH;
}

// Cria uma nova tabela hash para bairros
TabelaHashBairros* criar_tabela_bairros() {
    TabelaHashBairros* tabela = (TabelaHashBairros*)malloc(sizeof(TabelaHashBairros));
    if (!tabela) return NULL;
    
    // Inicializa todas as posições como NULL
    for (int i = 0; i < TAM_HASH; i++) {
        tabela->tabela[i] = NULL;
    }
    
    return tabela;
}

// Insere um bairro na tabela hash
int inserir_bairro(TabelaHashBairros* tabela, int id, const char* nome) {
    if (!tabela || !nome) return 0;
    
    // Verifica se já existe
    if (buscar_bairro(tabela, id)) return 0;
    
    int indice = hash_bairro(id);
    Bairro* novo = (Bairro*)malloc(sizeof(Bairro));
    if (!novo) return 0;
    
    novo->id = id;
    strcpy(novo->nome, nome);
    novo->prox = tabela->tabela[indice];  // Encadeamento para tratar colisões
    tabela->tabela[indice] = novo;
    
    return 1;
}

// Busca um bairro pelo ID
Bairro* buscar_bairro(TabelaHashBairros* tabela, int id) {
    if (!tabela) return NULL;
    
    int indice = hash_bairro(id);
    Bairro* atual = tabela->tabela[indice];
    
    while (atual) {
        if (atual->id == id) return atual;
        atual = atual->prox;
    }
    
    return NULL;
}

// Lista todos os bairros cadastrados
void listar_bairros(TabelaHashBairros* tabela) {
    if (!tabela) return;
    
    printf("\n=== BAIRROS CADASTRADOS ===\n");
    int encontrou = 0;
    for (int i = 0; i < TAM_HASH; i++) {
        Bairro* atual = tabela->tabela[i];
        while (atual) {
            printf("ID: %d - Nome: %s\n", atual->id, atual->nome);
            atual = atual->prox;
            encontrou = 1;
        }
    }
    if (!encontrou) {
        printf("Nenhum bairro cadastrado.\n");
    }
}

// Remove um bairro da tabela hash
int remover_bairro(TabelaHashBairros* tabela, int id) {
    if (!tabela) return 0;
    
    int indice = hash_bairro(id);
    Bairro* atual = tabela->tabela[indice];
    Bairro* anterior = NULL;
    
    while (atual) {
        if (atual->id == id) {
            if (anterior == NULL) {
                tabela->tabela[indice] = atual->prox;
            } else {
                anterior->prox = atual->prox;
            }
            free(atual);
            return 1;
        }
        anterior = atual;
        atual = atual->prox;
    }
    
    return 0;
}

// Libera memória da tabela de bairros
void liberar_tabela_bairros(TabelaHashBairros* tabela) {
    if (!tabela) return;
    
    for (int i = 0; i < TAM_HASH; i++) {
        Bairro* atual = tabela->tabela[i];
        while (atual) {
            Bairro* temp = atual;
            atual = atual->prox;
            free(temp);
        }
    }
    free(tabela);
}

// ==================== IMPLEMENTAÇÃO - HASH/CIDADÃOS ====================

// Função hash para CPF
int hash_cpf(const char* cpf) {
    if (!cpf) return 0;
    int hash = 0;
    for (int i = 0; cpf[i] != '\0'; i++) {
        if (cpf[i] >= '0' && cpf[i] <= '9') {
            hash = (hash * 10 + (cpf[i] - '0')) % TAM_HASH;
        }
    }
    return hash;
}

// Cria uma nova tabela hash para cidadãos
TabelaHashCidadaos* criar_tabela_cidadaos() {
    TabelaHashCidadaos* tabela = (TabelaHashCidadaos*)malloc(sizeof(TabelaHashCidadaos));
    if (!tabela) return NULL;
    
    for (int i = 0; i < TAM_HASH; i++) {
        tabela->tabela[i] = NULL;
    }
    
    return tabela;
}

// Insere um cidadão na tabela hash
int inserir_cidadao(TabelaHashCidadaos* tabela, const char* cpf, const char* nome, 
                   const char* email, const char* endereco, int bairro_id) {
    if (!tabela || !cpf || !nome || !email || !endereco) return 0;
    
    // Verifica se já existe
    if (buscar_cidadao(tabela, cpf)) return 0;
    
    int indice = hash_cpf(cpf);
    Cidadao* novo = (Cidadao*)malloc(sizeof(Cidadao));
    if (!novo) return 0;
    
    strcpy(novo->cpf, cpf);
    strcpy(novo->nome, nome);
    strcpy(novo->email, email);
    strcpy(novo->endereco, endereco);
    novo->bairro_id = bairro_id;
    novo->prox = tabela->tabela[indice];
    tabela->tabela[indice] = novo;
    
    return 1;
}

// Busca um cidadão pelo CPF
Cidadao* buscar_cidadao(TabelaHashCidadaos* tabela, const char* cpf) {
    if (!tabela || !cpf) return NULL;
    
    int indice = hash_cpf(cpf);
    Cidadao* atual = tabela->tabela[indice];
    
    while (atual) {
        if (strcmp(atual->cpf, cpf) == 0) return atual;
        atual = atual->prox;
    }
    
    return NULL;
}

// Lista todos os cidadãos cadastrados
void listar_cidadaos(TabelaHashCidadaos* tabela) {
    if (!tabela) return;
    
    printf("\n=== CIDADÃOS CADASTRADOS ===\n");
    int encontrou = 0;
    for (int i = 0; i < TAM_HASH; i++) {
        Cidadao* atual = tabela->tabela[i];
        while (atual) {
            printf("CPF: %s - Nome: %s - Email: %s\n", atual->cpf, atual->nome, atual->email);
            printf("  Endereco: %s - Bairro ID: %d\n", atual->endereco, atual->bairro_id);
            atual = atual->prox;
            encontrou = 1;
        }
    }
    if (!encontrou) {
        printf("Nenhum cidadão cadastrado.\n");
    }
}

// Remove um cidadão da tabela hash
int remover_cidadao(TabelaHashCidadaos* tabela, const char* cpf) {
    if (!tabela || !cpf) return 0;
    
    int indice = hash_cpf(cpf);
    Cidadao* atual = tabela->tabela[indice];
    Cidadao* anterior = NULL;
    
    while (atual) {
        if (strcmp(atual->cpf, cpf) == 0) {
            if (anterior == NULL) {
                tabela->tabela[indice] = atual->prox;
            } else {
                anterior->prox = atual->prox;
            }
            free(atual);
            return 1;
        }
        anterior = atual;
        atual = atual->prox;
    }
    
    return 0;
}

// Libera memória da tabela de cidadãos
void liberar_tabela_cidadaos(TabelaHashCidadaos* tabela) {
    if (!tabela) return;
    
    for (int i = 0; i < TAM_HASH; i++) {
        Cidadao* atual = tabela->tabela[i];
        while (atual) {
            Cidadao* temp = atual;
            atual = atual->prox;
            free(temp);
        }
    }
    free(tabela);
}

// ==================== IMPLEMENTAÇÃO - PILHAS DE HISTÓRICO ====================

// Cria uma nova pilha de histórico
PilhaHistorico* criar_pilha_historico() {
    PilhaHistorico* pilha = (PilhaHistorico*)malloc(sizeof(PilhaHistorico));
    if (!pilha) return NULL;
    
    pilha->topo = NULL;
    pilha->tamanho = 0;
    
    return pilha;
}

// Verifica se a pilha está vazia
int pilha_vazia(PilhaHistorico* pilha) {
    return pilha == NULL || pilha->topo == NULL;
}

// Empilha um novo histórico de atendimento
void empilhar_historico(PilhaHistorico* pilha, int ocorrencia_id, int bairro_id, 
                       TipoServico tipo, int gravidade, int tempo_inicio, 
                       int tempo_fim, const char* observacoes) {
    if (!pilha) return;
    
    HistoricoAtendimento* novo = (HistoricoAtendimento*)malloc(sizeof(HistoricoAtendimento));
    if (!novo) return;
    
    novo->ocorrencia_id = ocorrencia_id;
    novo->bairro_id = bairro_id;
    novo->tipo_servico = tipo;
    novo->gravidade = gravidade;
    novo->tempo_inicio = tempo_inicio;
    novo->tempo_fim = tempo_fim;
    strcpy(novo->observacoes, observacoes ? observacoes : "Atendimento concluido");
    novo->prox = pilha->topo;
    
    pilha->topo = novo;
    pilha->tamanho++;
}

// Desempilha um histórico de atendimento
HistoricoAtendimento* desempilhar_historico(PilhaHistorico* pilha) {
    if (pilha_vazia(pilha)) return NULL;
    
    HistoricoAtendimento* temp = pilha->topo;
    pilha->topo = pilha->topo->prox;
    pilha->tamanho--;
    
    return temp;
}

// Mostra o histórico completo (sem remover)
void mostrar_historico(PilhaHistorico* pilha) {
    if (pilha_vazia(pilha)) {
        printf("Histórico vazio\n");
        return;
    }
    
    printf("Histórico (%d atendimentos):\n", pilha->tamanho);
    HistoricoAtendimento* atual = pilha->topo;
    int contador = 1;
    
    while (atual) {
        printf("  %d. Ocorrência #%d - %s - Bairro %d - Gravidade %d\n", 
               contador++, atual->ocorrencia_id, tipo_servico_string(atual->tipo_servico),
               atual->bairro_id, atual->gravidade);
        printf("     Tempo: %d a %d - %s\n", 
               atual->tempo_inicio, atual->tempo_fim, atual->observacoes);
        atual = atual->prox;
    }
}

// Libera memória da pilha de histórico
void liberar_pilha_historico(PilhaHistorico* pilha) {
    if (!pilha) return;
    
    while (!pilha_vazia(pilha)) {
        HistoricoAtendimento* temp = desempilhar_historico(pilha);
        free(temp);
    }
    free(pilha);
}

// ==================== IMPLEMENTAÇÃO - LISTAS CRUZADAS ====================

// Cria uma nova lista cruzada
ListaCruzada* criar_lista_cruzada() {
    ListaCruzada* lista = (ListaCruzada*)malloc(sizeof(ListaCruzada));
    if (!lista) return NULL;
    
    lista->primeiro = NULL;
    return lista;
}

// Insere um bairro na lista cruzada
int inserir_bairro_servico(ListaCruzada* lista, int bairro_id, const char* nome_bairro) {
    if (!lista || !nome_bairro) return 0;
    
    // Verifica se já existe
    NoBairroServico* atual = lista->primeiro;
    while (atual) {
        if (atual->bairro_id == bairro_id) return 0;
        atual = atual->prox_bairro;
    }
    
    NoBairroServico* novo = (NoBairroServico*)malloc(sizeof(NoBairroServico));
    if (!novo) return 0;
    
    novo->bairro_id = bairro_id;
    strcpy(novo->nome_bairro, nome_bairro);
    novo->servicos = NULL;
    novo->prox_bairro = lista->primeiro;
    lista->primeiro = novo;
    
    return 1;
}

// Adiciona um serviço a um bairro
int adicionar_servico_bairro(ListaCruzada* lista, int bairro_id, TipoServico tipo) {
    if (!lista) return 0;
    
    // Busca o bairro
    NoBairroServico* bairro = lista->primeiro;
    while (bairro && bairro->bairro_id != bairro_id) {
        bairro = bairro->prox_bairro;
    }
    
    if (!bairro) return 0;
    
    // Verifica se o serviço já existe
    NoServico* servico = bairro->servicos;
    while (servico) {
        if (servico->tipo == tipo) {
            servico->unidades_disponiveis++;
            return 1;
        }
        servico = servico->prox_servico;
    }
    
    // Cria novo serviço
    NoServico* novo_servico = (NoServico*)malloc(sizeof(NoServico));
    if (!novo_servico) return 0;
    
    novo_servico->tipo = tipo;
    novo_servico->unidades_disponiveis = 1;
    novo_servico->prox_servico = bairro->servicos;
    bairro->servicos = novo_servico;
    
    return 1;
}

// Atualiza número de unidades disponíveis
int atualizar_unidades_disponiveis(ListaCruzada* lista, int bairro_id, TipoServico tipo, int delta) {
    if (!lista) return 0;
    
    NoBairroServico* bairro = lista->primeiro;
    while (bairro && bairro->bairro_id != bairro_id) {
        bairro = bairro->prox_bairro;
    }
    
    if (!bairro) return 0;
    
    NoServico* servico = bairro->servicos;
    while (servico) {
        if (servico->tipo == tipo) {
            servico->unidades_disponiveis += delta;
            if (servico->unidades_disponiveis < 0) {
                servico->unidades_disponiveis = 0;
            }
            return 1;
        }
        servico = servico->prox_servico;
    }
    
    return 0;
}

// Mostra o mapa da cidade com serviços
void mostrar_mapa_cidade(ListaCruzada* lista) {
    if (!lista || !lista->primeiro) {
        printf("Mapa da cidade vazio\n");
        return;
    }
    
    printf("\n=== MAPA DA CIDADE - BAIRROS E SERVIÇOS ===\n");
    NoBairroServico* bairro = lista->primeiro;
    
    while (bairro) {
        printf("🏙️  Bairro: %s (ID: %d)\n", bairro->nome_bairro, bairro->bairro_id);
        
        if (!bairro->servicos) {
            printf("   ❌ Nenhum serviço disponível\n");
        } else {
            NoServico* servico = bairro->servicos;
            while (servico) {
                printf("   ✅ %s: %d unidades disponíveis\n", 
                       tipo_servico_string(servico->tipo), 
                       servico->unidades_disponiveis);
                servico = servico->prox_servico;
            }
        }
        
        bairro = bairro->prox_bairro;
        printf("\n");
    }
}

// Libera memória da lista cruzada
void liberar_lista_cruzada(ListaCruzada* lista) {
    if (!lista) return;
    
    while (lista->primeiro) {
        NoBairroServico* bairro_temp = lista->primeiro;
        lista->primeiro = lista->primeiro->prox_bairro;
        
        // Libera serviços do bairro
        while (bairro_temp->servicos) {
            NoServico* servico_temp = bairro_temp->servicos;
            bairro_temp->servicos = bairro_temp->servicos->prox_servico;
            free(servico_temp);
        }
        
        free(bairro_temp);
    }
    
    free(lista);
}

// ==================== IMPLEMENTAÇÃO - UNIDADES DE SERVIÇO ====================

// Cria uma nova unidade de serviço
UnidadeServico* criar_unidade(int id, TipoServico tipo, const char* identificacao) {
    UnidadeServico* nova = (UnidadeServico*)malloc(sizeof(UnidadeServico));
    if (!nova) return NULL;
    
    nova->id = id;
    nova->tipo = tipo;
    strcpy(nova->identificacao, identificacao);
    nova->disponivel = 1;  // Inicialmente disponível
    nova->prox = NULL;
    
    return nova;
}

// Insere uma unidade na lista de unidades
int inserir_unidade(UnidadeServico** lista, int id, TipoServico tipo, const char* identificacao) {
    UnidadeServico* nova = criar_unidade(id, tipo, identificacao);
    if (!nova) return 0;
    
    nova->prox = *lista;
    *lista = nova;
    
    return 1;
}

// Busca uma unidade disponível do tipo especificado
UnidadeServico* buscar_unidade_disponivel(UnidadeServico* lista, TipoServico tipo) {
    UnidadeServico* atual = lista;
    
    while (atual) {
        if (atual->tipo == tipo && atual->disponivel) {
            return atual;
        }
        atual = atual->prox;
    }
    
    return NULL;
}

// Retorna string do tipo de serviço
const char* tipo_servico_string(TipoServico tipo) {
    switch (tipo) {
        case AMBULANCIA: return "AMBULANCIA";
        case BOMBEIRO: return "BOMBEIRO";
        case POLICIA: return "POLICIA";
        default: return "DESCONHECIDO";
    }
}

// Lista todas as unidades cadastradas
void listar_unidades(UnidadeServico* lista) {
    printf("\n=== UNIDADES DE SERVIÇO ===\n");
    UnidadeServico* atual = lista;
    
    if (!atual) {
        printf("Nenhuma unidade cadastrada.\n");
        return;
    }
    
    while (atual) {
        printf("ID: %d - %s - %s - Status: %s\n", 
               atual->id, 
               atual->identificacao,
               tipo_servico_string(atual->tipo),
               atual->disponivel ? "DISPONÍVEL" : "OCUPADO");
        atual = atual->prox;
    }
}

// Libera memória das unidades
void liberar_unidades(UnidadeServico* lista) {
    while (lista) {
        UnidadeServico* temp = lista;
        lista = lista->prox;
        free(temp);
    }
}

// ==================== IMPLEMENTAÇÃO - FILAS ====================

// Cria uma nova fila
Fila* criar_fila() {
    Fila* fila = (Fila*)malloc(sizeof(Fila));
    if (!fila) return NULL;
    
    fila->inicio = NULL;
    fila->fim = NULL;
    fila->tamanho = 0;
    
    return fila;
}

// Verifica se a fila está vazia
int fila_vazia(Fila* fila) {
    return fila == NULL || fila->inicio == NULL;
}

// Adiciona uma ocorrência na fila
void enfileirar(Fila* fila, Ocorrencia* ocorrencia) {
    if (!fila || !ocorrencia) return;
    
    NoFila* novo = (NoFila*)malloc(sizeof(NoFila));
    if (!novo) return;
    
    novo->ocorrencia = ocorrencia;
    novo->prox = NULL;
    
    if (fila_vazia(fila)) {
        fila->inicio = fila->fim = novo;
    } else {
        fila->fim->prox = novo;
        fila->fim = novo;
    }
    
    fila->tamanho++;
}

// Remove e retorna a primeira ocorrência da fila
Ocorrencia* desenfileirar(Fila* fila) {
    if (fila_vazia(fila)) return NULL;
    
    NoFila* temp = fila->inicio;
    Ocorrencia* ocorrencia = temp->ocorrencia;
    
    fila->inicio = fila->inicio->prox;
    if (fila->inicio == NULL) {
        fila->fim = NULL;
    }
    
    free(temp);
    fila->tamanho--;
    
    return ocorrencia;
}

// Mostra o conteúdo da fila
void mostrar_fila(Fila* fila) {
    if (fila_vazia(fila)) {
        printf("Fila vazia\n");
        return;
    }
    
    NoFila* atual = fila->inicio;
    printf("Fila (%d ocorrencias): ", fila->tamanho);
    
    while (atual) {
        printf("[ID:%d Bairro:%d Grav:%d] ", 
               atual->ocorrencia->id, 
               atual->ocorrencia->bairro_id,
               atual->ocorrencia->gravidade);
        atual = atual->prox;
    }
    printf("\n");
}

// Libera memória da fila
void liberar_fila(Fila* fila) {
    if (!fila) return;
    
    while (!fila_vazia(fila)) {
        Ocorrencia* ocorrencia = desenfileirar(fila);
        free(ocorrencia);
    }
    free(fila);
}

// ==================== IMPLEMENTAÇÃO - OCORRÊNCIAS ====================

// Cria uma nova ocorrência
Ocorrencia* criar_ocorrencia(int id, int bairro_id, TipoServico tipo, int gravidade, int tempo) {
    Ocorrencia* nova = (Ocorrencia*)malloc(sizeof(Ocorrencia));
    if (!nova) return NULL;
    
    nova->id = id;
    nova->bairro_id = bairro_id;
    nova->tipo_servico = tipo;
    nova->gravidade = gravidade;
    nova->tempo_chegada = tempo;
    nova->prox = NULL;
    
    return nova;
}

// ==================== IMPLEMENTAÇÃO - ÁRVORE BST (NOVA - FASE 3) ====================

// Cria uma nova árvore BST
ArvoreBST* criar_arvore_bst() {
    ArvoreBST* arvore = (ArvoreBST*)malloc(sizeof(ArvoreBST));
    if (!arvore) return NULL;
    
    arvore->raiz = NULL;
    arvore->tamanho = 0;
    
    return arvore;
}

// Cria um novo nó para a árvore BST
NoArvoreBST* criar_no_bst(Ocorrencia* ocorrencia) {
    if (!ocorrencia) return NULL;
    
    NoArvoreBST* novo = (NoArvoreBST*)malloc(sizeof(NoArvoreBST));
    if (!novo) return NULL;
    
    // Cria uma cópia da ocorrência para evitar problemas de memória
    novo->ocorrencia = (Ocorrencia*)malloc(sizeof(Ocorrencia));
    if (!novo->ocorrencia) {
        free(novo);
        return NULL;
    }
    
    *(novo->ocorrencia) = *ocorrencia; // Copia os dados
    novo->esquerda = NULL;
    novo->direita = NULL;
    
    return novo;
}

// Insere uma ocorrência na árvore BST (ordenada por ID)
int inserir_bst(ArvoreBST* arvore, Ocorrencia* ocorrencia) {
    if (!arvore || !ocorrencia) return 0;
    
    if (arvore->raiz == NULL) {
        arvore->raiz = criar_no_bst(ocorrencia);
        if (arvore->raiz) {
            arvore->tamanho++;
            return 1;
        }
        return 0;
    }
    
    NoArvoreBST* atual = arvore->raiz;
    NoArvoreBST* pai = NULL;
    
    // Busca a posição para inserção
    while (atual != NULL) {
        pai = atual;
        if (ocorrencia->id < atual->ocorrencia->id) {
            atual = atual->esquerda;
        } else if (ocorrencia->id > atual->ocorrencia->id) {
            atual = atual->direita;
        } else {
            // ID já existe, não insere
            return 0;
        }
    }
    
    // Insere o novo nó
    NoArvoreBST* novo = criar_no_bst(ocorrencia);
    if (!novo) return 0;
    
    if (ocorrencia->id < pai->ocorrencia->id) {
        pai->esquerda = novo;
    } else {
        pai->direita = novo;
    }
    
    arvore->tamanho++;
    return 1;
}

// Busca um nó na árvore BST por ID
NoArvoreBST* buscar_bst(ArvoreBST* arvore, int id) {
    if (!arvore) return NULL;
    
    NoArvoreBST* atual = arvore->raiz;
    
    while (atual != NULL) {
        if (id == atual->ocorrencia->id) {
            return atual;
        } else if (id < atual->ocorrencia->id) {
            atual = atual->esquerda;
        } else {
            atual = atual->direita;
        }
    }
    
    return NULL;
}

// Busca uma ocorrência por ID e retorna a ocorrência
Ocorrencia* buscar_ocorrencia_por_id(ArvoreBST* arvore, int id) {
    NoArvoreBST* no = buscar_bst(arvore, id);
    return no ? no->ocorrencia : NULL;
}

// Percorre a árvore em ordem (esquerda, raiz, direita)
void percorrer_em_ordem_bst(NoArvoreBST* no) {
    if (no != NULL) {
        percorrer_em_ordem_bst(no->esquerda);
        printf("ID: %d | Bairro: %d | %s | Gravidade: %d | Tempo: %d\n",
               no->ocorrencia->id, no->ocorrencia->bairro_id,
               tipo_servico_string(no->ocorrencia->tipo_servico),
               no->ocorrencia->gravidade, no->ocorrencia->tempo_chegada);
        percorrer_em_ordem_bst(no->direita);
    }
}

// Percorre a árvore em pré-ordem (raiz, esquerda, direita)
void percorrer_pre_ordem_bst(NoArvoreBST* no) {
    if (no != NULL) {
        printf("ID: %d | Bairro: %d | %s | Gravidade: %d | Tempo: %d\n",
               no->ocorrencia->id, no->ocorrencia->bairro_id,
               tipo_servico_string(no->ocorrencia->tipo_servico),
               no->ocorrencia->gravidade, no->ocorrencia->tempo_chegada);
        percorrer_pre_ordem_bst(no->esquerda);
        percorrer_pre_ordem_bst(no->direita);
    }
}

// Percorre a árvore em pós-ordem (esquerda, direita, raiz)
void percorrer_pos_ordem_bst(NoArvoreBST* no) {
    if (no != NULL) {
        percorrer_pos_ordem_bst(no->esquerda);
        percorrer_pos_ordem_bst(no->direita);
        printf("ID: %d | Bairro: %d | %s | Gravidade: %d | Tempo: %d\n",
               no->ocorrencia->id, no->ocorrencia->bairro_id,
               tipo_servico_string(no->ocorrencia->tipo_servico),
               no->ocorrencia->gravidade, no->ocorrencia->tempo_chegada);
    }
}

// Mostra informações gerais da árvore BST
void mostrar_arvore_bst(ArvoreBST* arvore) {
    if (!arvore || !arvore->raiz) {
        printf("Árvore BST vazia\n");
        return;
    }
    
    printf("\n=== ÁRVORE BST - OCORRÊNCIAS ===\n");
    printf("Total de ocorrências: %d\n", arvore->tamanho);
    printf("Ocorrências ordenadas por ID:\n");
    percorrer_em_ordem_bst(arvore->raiz);
}

// Mostra árvore ordenada por ID (em ordem)
void mostrar_arvore_ordenada_por_id(ArvoreBST* arvore) {
    if (!arvore || !arvore->raiz) {
        printf("Nenhuma ocorrência cadastrada na árvore\n");
        return;
    }
    
    printf("\n=== CONSULTA ORDENADA POR ID ===\n");
    percorrer_em_ordem_bst(arvore->raiz);
}

// Mostra árvore ordenada por tempo (pré-ordem)
void mostrar_arvore_ordenada_por_tempo(ArvoreBST* arvore) {
    if (!arvore || !arvore->raiz) {
        printf("Nenhuma ocorrência cadastrada na árvore\n");
        return;
    }
    
    printf("\n=== CONSULTA ORDENADA POR TEMPO DE CHEGADA ===\n");
    percorrer_pre_ordem_bst(arvore->raiz);
}

// Remove um nó da árvore BST (função auxiliar recursiva)
NoArvoreBST* remover_bst(NoArvoreBST* no, int id) {
    if (no == NULL) return no;
    
    if (id < no->ocorrencia->id) {
        no->esquerda = remover_bst(no->esquerda, id);
    } else if (id > no->ocorrencia->id) {
        no->direita = remover_bst(no->direita, id);
    } else {
        // Nó encontrado para remoção
        if (no->esquerda == NULL) {
            NoArvoreBST* temp = no->direita;
            free(no->ocorrencia);
            free(no);
            return temp;
        } else if (no->direita == NULL) {
            NoArvoreBST* temp = no->esquerda;
            free(no->ocorrencia);
            free(no);
            return temp;
        }
        
        // Nó com dois filhos: encontra o sucessor em ordem
        NoArvoreBST* temp = no->direita;
        while (temp->esquerda != NULL) {
            temp = temp->esquerda;
        }
        
        // Copia os dados do sucessor
        *(no->ocorrencia) = *(temp->ocorrencia);
        
        // Remove o sucessor
        no->direita = remover_bst(no->direita, temp->ocorrencia->id);
    }
    
    return no;
}

// Remove uma ocorrência da árvore BST
int remover_ocorrencia_bst(ArvoreBST* arvore, int id) {
    if (!arvore) return 0;
    
    NoArvoreBST* resultado = remover_bst(arvore->raiz, id);
    if (resultado != arvore->raiz || buscar_bst(arvore, id) == NULL) {
        arvore->raiz = resultado;
        arvore->tamanho--;
        return 1;
    }
    
    return 0;
}

// Libera memória da árvore BST (função auxiliar recursiva)
void liberar_arvore_bst(NoArvoreBST* no) {
    if (no != NULL) {
        liberar_arvore_bst(no->esquerda);
        liberar_arvore_bst(no->direita);
        free(no->ocorrencia);
        free(no);
    }
}

// Libera toda a árvore BST
void liberar_bst_completa(ArvoreBST* arvore) {
    if (!arvore) return;
    
    liberar_arvore_bst(arvore->raiz);
    free(arvore);
}

// ==================== IMPLEMENTAÇÃO - ÁRVORE AVL PARTE 1 (NOVA - FASE 3) ====================

// Cria uma nova árvore AVL
ArvoreAVL* criar_arvore_avl() {
    ArvoreAVL* arvore = (ArvoreAVL*)malloc(sizeof(ArvoreAVL));
    if (!arvore) return NULL;
    
    arvore->raiz = NULL;
    arvore->tamanho = 0;
    
    return arvore;
}

// Cria um novo nó para a árvore AVL
NoArvoreAVL* criar_no_avl(Ocorrencia* ocorrencia) {
    if (!ocorrencia) return NULL;
    
    NoArvoreAVL* novo = (NoArvoreAVL*)malloc(sizeof(NoArvoreAVL));
    if (!novo) return NULL;
    
    // Cria uma cópia da ocorrência
    novo->ocorrencia = (Ocorrencia*)malloc(sizeof(Ocorrencia));
    if (!novo->ocorrencia) {
        free(novo);
        return NULL;
    }
    
    *(novo->ocorrencia) = *ocorrencia; // Copia os dados
    novo->altura = 1;
    novo->fator_balanceamento = 0;
    novo->esquerda = NULL;
    novo->direita = NULL;
    
    return novo;
}

// Retorna a altura de um nó
int altura_avl(NoArvoreAVL* no) {
    return no ? no->altura : 0;
}

// Calcula o fator de balanceamento
int fator_balanceamento_avl(NoArvoreAVL* no) {
    return no ? altura_avl(no->esquerda) - altura_avl(no->direita) : 0;
}

// Retorna o maior entre dois inteiros
int max_int(int a, int b) {
    return (a > b) ? a : b;
}

// Rotação simples à direita
NoArvoreAVL* rotacao_direita(NoArvoreAVL* y) {
    NoArvoreAVL* x = y->esquerda;
    NoArvoreAVL* T2 = x->direita;
    
    // Executa a rotação
    x->direita = y;
    y->esquerda = T2;
    
    // Atualiza as alturas
    y->altura = max_int(altura_avl(y->esquerda), altura_avl(y->direita)) + 1;
    x->altura = max_int(altura_avl(x->esquerda), altura_avl(x->direita)) + 1;
    
    // Atualiza fatores de balanceamento
    y->fator_balanceamento = fator_balanceamento_avl(y);
    x->fator_balanceamento = fator_balanceamento_avl(x);
    
    return x;
}

// Rotação simples à esquerda
NoArvoreAVL* rotacao_esquerda(NoArvoreAVL* x) {
    NoArvoreAVL* y = x->direita;
    NoArvoreAVL* T2 = y->esquerda;
    
    // Executa a rotação
    y->esquerda = x;
    x->direita = T2;
    
    // Atualiza as alturas
    x->altura = max_int(altura_avl(x->esquerda), altura_avl(x->direita)) + 1;
    y->altura = max_int(altura_avl(y->esquerda), altura_avl(y->direita)) + 1;
    
    // Atualiza fatores de balanceamento
    x->fator_balanceamento = fator_balanceamento_avl(x);
    y->fator_balanceamento = fator_balanceamento_avl(y);
    
    return y;
}

// Insere uma ocorrência na árvore AVL (ordenada por gravidade, depois por ID)
NoArvoreAVL* inserir_avl(NoArvoreAVL* no, Ocorrencia* ocorrencia) {
    // 1. Inserção normal da BST
    if (no == NULL) {
        return criar_no_avl(ocorrencia);
    }
    
    // Compara primeiro por gravidade (maior gravidade = maior prioridade)
    // Em caso de empate, compara por ID
    if (ocorrencia->gravidade > no->ocorrencia->gravidade || 
        (ocorrencia->gravidade == no->ocorrencia->gravidade && ocorrencia->id < no->ocorrencia->id)) {
        no->esquerda = inserir_avl(no->esquerda, ocorrencia);
    } else if (ocorrencia->gravidade < no->ocorrencia->gravidade || 
               (ocorrencia->gravidade == no->ocorrencia->gravidade && ocorrencia->id > no->ocorrencia->id)) {
        no->direita = inserir_avl(no->direita, ocorrencia);
    } else {
        // Ocorrência duplicada, não insere
        return no;
    }
    
    // 2. Atualiza altura do nó atual
    no->altura = 1 + max_int(altura_avl(no->esquerda), altura_avl(no->direita));
    
    // 3. Calcula o fator de balanceamento
    int balanceamento = fator_balanceamento_avl(no);
    no->fator_balanceamento = balanceamento;
    
    // 4. Se o nó ficou desbalanceado, executa as rotações necessárias
    
    // Caso Esquerda-Esquerda
    if (balanceamento > 1 && (ocorrencia->gravidade > no->esquerda->ocorrencia->gravidade || 
        (ocorrencia->gravidade == no->esquerda->ocorrencia->gravidade && ocorrencia->id < no->esquerda->ocorrencia->id))) {
        return rotacao_direita(no);
    }
    
    // Caso Direita-Direita
    if (balanceamento < -1 && (ocorrencia->gravidade < no->direita->ocorrencia->gravidade || 
        (ocorrencia->gravidade == no->direita->ocorrencia->gravidade && ocorrencia->id > no->direita->ocorrencia->id))) {
        return rotacao_esquerda(no);
    }
    
    // Caso Esquerda-Direita
    if (balanceamento > 1 && (ocorrencia->gravidade < no->esquerda->ocorrencia->gravidade || 
        (ocorrencia->gravidade == no->esquerda->ocorrencia->gravidade && ocorrencia->id > no->esquerda->ocorrencia->id))) {
        no->esquerda = rotacao_esquerda(no->esquerda);
        return rotacao_direita(no);
    }
    
    // Caso Direita-Esquerda
    if (balanceamento < -1 && (ocorrencia->gravidade > no->direita->ocorrencia->gravidade || 
        (ocorrencia->gravidade == no->direita->ocorrencia->gravidade && ocorrencia->id < no->direita->ocorrencia->id))) {
        no->direita = rotacao_direita(no->direita);
        return rotacao_esquerda(no);
    }
    
    // Retorna o nó (inalterado)
    return no;
}

// Insere uma ocorrência na árvore AVL
int inserir_avl_arvore(ArvoreAVL* arvore, Ocorrencia* ocorrencia) {
    if (!arvore || !ocorrencia) return 0;
    
    arvore->raiz = inserir_avl(arvore->raiz, ocorrencia);
    
    // Verifica se a inserção foi bem-sucedida
    if (arvore->raiz) {
        arvore->tamanho++;
        return 1;
    }
    
    return 0;
}

// Busca um nó na árvore AVL por gravidade
NoArvoreAVL* buscar_avl(NoArvoreAVL* no, int gravidade) {
    if (no == NULL || no->ocorrencia->gravidade == gravidade) {
        return no;
    }
    
    if (gravidade > no->ocorrencia->gravidade) {
        return buscar_avl(no->esquerda, gravidade);
    }
    
    return buscar_avl(no->direita, gravidade);
}

// Busca uma ocorrência por gravidade
Ocorrencia* buscar_por_gravidade(ArvoreAVL* arvore, int gravidade) {
    if (!arvore) return NULL;
    
    NoArvoreAVL* no = buscar_avl(arvore->raiz, gravidade);
    return no ? no->ocorrencia : NULL;
}

// ==================== IMPLEMENTAÇÃO - ÁRVORE AVL PARTE 2 (NOVA - FASE 3) ====================

// Percorre a árvore AVL por prioridade (em ordem decrescente de gravidade)
void percorrer_por_prioridade(NoArvoreAVL* no) {
    if (no != NULL) {
        percorrer_por_prioridade(no->esquerda);
        printf("🚨 PRIORIDADE %d | ID: %d | Bairro: %d | %s | Tempo: %d | FB: %d\n",
               no->ocorrencia->gravidade, no->ocorrencia->id, no->ocorrencia->bairro_id,
               tipo_servico_string(no->ocorrencia->tipo_servico),
               no->ocorrencia->tempo_chegada, no->fator_balanceamento);
        percorrer_por_prioridade(no->direita);
    }
}

// Mostra informações gerais da árvore AVL
void mostrar_arvore_avl(ArvoreAVL* arvore) {
    if (!arvore || !arvore->raiz) {
        printf("Árvore AVL vazia\n");
        return;
    }
    
    printf("\n=== ÁRVORE AVL - PRIORIDADES ===\n");
    printf("Total de ocorrências: %d\n", arvore->tamanho);
    printf("Árvore balanceada automaticamente\n");
    printf("Ocorrências ordenadas por prioridade (gravidade):\n");
    percorrer_por_prioridade(arvore->raiz);
}

// Mostra ocorrências ordenadas por prioridade
void mostrar_ocorrencias_por_prioridade(ArvoreAVL* arvore) {
    if (!arvore || !arvore->raiz) {
        printf("Nenhuma ocorrência cadastrada na árvore de prioridades\n");
        return;
    }
    
    printf("\n=== CONSULTA POR PRIORIDADE ===\n");
    printf("(Maior gravidade = Maior prioridade)\n");
    percorrer_por_prioridade(arvore->raiz);
}

// Remove um nó da árvore AVL (função auxiliar recursiva)
NoArvoreAVL* remover_avl(NoArvoreAVL* no, int gravidade, int id) {
    // 1. Remoção normal da BST
    if (no == NULL) return no;
    
    if (gravidade > no->ocorrencia->gravidade || 
        (gravidade == no->ocorrencia->gravidade && id < no->ocorrencia->id)) {
        no->esquerda = remover_avl(no->esquerda, gravidade, id);
    } else if (gravidade < no->ocorrencia->gravidade || 
               (gravidade == no->ocorrencia->gravidade && id > no->ocorrencia->id)) {
        no->direita = remover_avl(no->direita, gravidade, id);
    } else {
        // Nó encontrado para remoção
        if ((no->esquerda == NULL) || (no->direita == NULL)) {
            NoArvoreAVL* temp = no->esquerda ? no->esquerda : no->direita;
            
            if (temp == NULL) {
                temp = no;
                no = NULL;
            } else {
                *(no->ocorrencia) = *(temp->ocorrencia);
                no->esquerda = temp->esquerda;
                no->direita = temp->direita;
                no->altura = temp->altura;
            }
            
            free(temp->ocorrencia);
            free(temp);
        } else {
            // Nó com dois filhos: encontra o sucessor em ordem
            NoArvoreAVL* temp = no->direita;
            while (temp->esquerda != NULL) {
                temp = temp->esquerda;
            }
            
            // Copia os dados do sucessor
            *(no->ocorrencia) = *(temp->ocorrencia);
            
            // Remove o sucessor
            no->direita = remover_avl(no->direita, temp->ocorrencia->gravidade, temp->ocorrencia->id);
        }
    }
    
    if (no == NULL) return no;
    
    // 2. Atualiza altura do nó atual
    no->altura = 1 + max_int(altura_avl(no->esquerda), altura_avl(no->direita));
    
    // 3. Calcula o fator de balanceamento
    int balanceamento = fator_balanceamento_avl(no);
    no->fator_balanceamento = balanceamento;
    
    // 4. Se o nó ficou desbalanceado, executa as rotações necessárias
    
    // Caso Esquerda-Esquerda
    if (balanceamento > 1 && fator_balanceamento_avl(no->esquerda) >= 0) {
        return rotacao_direita(no);
    }
    
    // Caso Esquerda-Direita
    if (balanceamento > 1 && fator_balanceamento_avl(no->esquerda) < 0) {
        no->esquerda = rotacao_esquerda(no->esquerda);
        return rotacao_direita(no);
    }
    
    // Caso Direita-Direita
    if (balanceamento < -1 && fator_balanceamento_avl(no->direita) <= 0) {
        return rotacao_esquerda(no);
    }
    
    // Caso Direita-Esquerda
    if (balanceamento < -1 && fator_balanceamento_avl(no->direita) > 0) {
        no->direita = rotacao_direita(no->direita);
        return rotacao_esquerda(no);
    }
    
    return no;
}

// Remove uma ocorrência da árvore AVL
int remover_ocorrencia_avl(ArvoreAVL* arvore, int gravidade, int id) {
    if (!arvore) return 0;
    
    NoArvoreAVL* resultado = remover_avl(arvore->raiz, gravidade, id);
    arvore->raiz = resultado;
    arvore->tamanho--;
    return 1;
}

// Libera memória da árvore AVL (função auxiliar recursiva)
void liberar_arvore_avl(NoArvoreAVL* no) {
    if (no != NULL) {
        liberar_arvore_avl(no->esquerda);
        liberar_arvore_avl(no->direita);
        free(no->ocorrencia);
        free(no);
    }
}

// Libera toda a árvore AVL
void liberar_avl_completa(ArvoreAVL* arvore) {
    if (!arvore) return;
    
    liberar_arvore_avl(arvore->raiz);
    free(arvore);
}

// ==================== IMPLEMENTAÇÃO - SISTEMA PRINCIPAL ====================

// Inicializa o sistema de emergência (MODIFICADO - FASE 3)
SistemaEmergencia* inicializar_sistema() {
    SistemaEmergencia* sistema = (SistemaEmergencia*)malloc(sizeof(SistemaEmergencia));
    if (!sistema) return NULL;
    
    sistema->bairros = criar_tabela_bairros();
    sistema->cidadaos = criar_tabela_cidadaos();
    sistema->unidades = NULL;
    sistema->historico_ambulancia = criar_pilha_historico();
    sistema->historico_bombeiro = criar_pilha_historico();
    sistema->historico_policia = criar_pilha_historico();
    sistema->mapa_cidade = criar_lista_cruzada();
    sistema->fila_ambulancia = criar_fila();
    sistema->fila_bombeiro = criar_fila();
    sistema->fila_policia = criar_fila();
    sistema->arvore_ocorrencias = criar_arvore_bst(); // NOVA - FASE 3
    sistema->arvore_prioridades = criar_arvore_avl(); // NOVA - FASE 3
    sistema->tempo_atual = 0;
    sistema->proximo_id_ocorrencia = 1;
    
    return sistema;
}

// Cadastra um bairro no sistema
void cadastrar_bairro_sistema(SistemaEmergencia* sistema, int id, const char* nome) {
    if (!sistema) return;
    
    if (inserir_bairro(sistema->bairros, id, nome)) {
        // Também adiciona na lista cruzada
        inserir_bairro_servico(sistema->mapa_cidade, id, nome);
        printf("Bairro cadastrado: ID %d - %s\n", id, nome);
    } else {
        printf("Erro ao cadastrar bairro! (Pode já existir)\n");
    }
}

// Cadastra um cidadão no sistema
void cadastrar_cidadao_sistema(SistemaEmergencia* sistema, const char* cpf, const char* nome,
                              const char* email, const char* endereco, int bairro_id) {
    if (!sistema) return;
    
    // Verifica se o bairro existe
    if (!buscar_bairro(sistema->bairros, bairro_id)) {
        printf("Erro: Bairro ID %d não encontrado!\n", bairro_id);
        return;
    }
    
    if (inserir_cidadao(sistema->cidadaos, cpf, nome, email, endereco, bairro_id)) {
        printf("Cidadão cadastrado: %s - CPF: %s\n", nome, cpf);
    } else {
        printf("Erro ao cadastrar cidadão! (CPF pode já existir)\n");
    }
}

// Cadastra uma unidade no sistema
void cadastrar_unidade_sistema(SistemaEmergencia* sistema, int id, TipoServico tipo, const char* identificacao) {
    if (!sistema) return;
    
    if (inserir_unidade(&sistema->unidades, id, tipo, identificacao)) {
        printf("Unidade cadastrada: %s - %s\n", identificacao, tipo_servico_string(tipo));
    } else {
        printf("Erro ao cadastrar unidade!\n");
    }
}

// Recebe uma nova ocorrência no sistema (MODIFICADO - FASE 3)
void receber_ocorrencia(SistemaEmergencia* sistema, int bairro_id, TipoServico tipo, int gravidade) {
    if (!sistema) return;
    
    // Verifica se o bairro existe
    if (!buscar_bairro(sistema->bairros, bairro_id)) {
        printf("Erro: Bairro ID %d não encontrado!\n", bairro_id);
        return;
    }
    
    Ocorrencia* nova = criar_ocorrencia(sistema->proximo_id_ocorrencia++, 
                                       bairro_id, tipo, gravidade, 
                                       sistema->tempo_atual);
    
    // Adiciona na fila correspondente
    switch (tipo) {
        case AMBULANCIA:
            enfileirar(sistema->fila_ambulancia, nova);
            printf("Ocorrencia #%d adicionada na fila de AMBULANCIA\n", nova->id);
            break;
        case BOMBEIRO:
            enfileirar(sistema->fila_bombeiro, nova);
            printf("Ocorrencia #%d adicionada na fila de BOMBEIRO\n", nova->id);
            break;
        case POLICIA:
            enfileirar(sistema->fila_policia, nova);
            printf("Ocorrencia #%d adicionada na fila de POLICIA\n", nova->id);
            break;
    }
    
    // NOVA FUNCIONALIDADE - FASE 3: Adiciona nas árvores para consultas inteligentes
    if (inserir_bst(sistema->arvore_ocorrencias, nova)) {
        printf("✅ Ocorrencia #%d indexada na arvore BST\n", nova->id);
    }
    
    if (inserir_avl_arvore(sistema->arvore_prioridades, nova)) {
        printf("🚨 Ocorrencia #%d priorizada na arvore AVL (gravidade %d)\n", nova->id, gravidade);
    }
}

// Processa atendimentos das filas
void processar_atendimentos(SistemaEmergencia* sistema) {
    if (!sistema) return;
    
    printf("\n=== PROCESSANDO ATENDIMENTOS - Tempo %d ===\n", sistema->tempo_atual);
    
    // Processa fila de ambulâncias
    if (!fila_vazia(sistema->fila_ambulancia)) {
        UnidadeServico* ambulancia = buscar_unidade_disponivel(sistema->unidades, AMBULANCIA);
        if (ambulancia) {
            Ocorrencia* ocorrencia = desenfileirar(sistema->fila_ambulancia);
            ambulancia->disponivel = 0;  // Marca como ocupado
            
            // Adiciona ao histórico
            empilhar_historico(sistema->historico_ambulancia, ocorrencia->id, 
                             ocorrencia->bairro_id, ocorrencia->tipo_servico, 
                             ocorrencia->gravidade, sistema->tempo_atual, 
                             sistema->tempo_atual + 2, "Atendimento médico");
            
            // Atualiza mapa da cidade
            atualizar_unidades_disponiveis(sistema->mapa_cidade, ocorrencia->bairro_id, AMBULANCIA, -1);
            
            printf("Ambulancia %s atendendo ocorrencia #%d no bairro %d\n", 
                   ambulancia->identificacao, ocorrencia->id, ocorrencia->bairro_id);
            free(ocorrencia);
        }
    }
    
    // Processa fila de bombeiros
    if (!fila_vazia(sistema->fila_bombeiro)) {
        UnidadeServico* bombeiro = buscar_unidade_disponivel(sistema->unidades, BOMBEIRO);
        if (bombeiro) {
            Ocorrencia* ocorrencia = desenfileirar(sistema->fila_bombeiro);
            bombeiro->disponivel = 0;
            
            // Adiciona ao histórico
            empilhar_historico(sistema->historico_bombeiro, ocorrencia->id, 
                             ocorrencia->bairro_id, ocorrencia->tipo_servico, 
                             ocorrencia->gravidade, sistema->tempo_atual, 
                             sistema->tempo_atual + 3, "Combate a incendio");
            
            // Atualiza mapa da cidade
            atualizar_unidades_disponiveis(sistema->mapa_cidade, ocorrencia->bairro_id, BOMBEIRO, -1);
            
            printf("Bombeiro %s atendendo ocorrencia #%d no bairro %d\n", 
                   bombeiro->identificacao, ocorrencia->id, ocorrencia->bairro_id);
            free(ocorrencia);
        }
    }
    
    // Processa fila de polícia
    if (!fila_vazia(sistema->fila_policia)) {
        UnidadeServico* policia = buscar_unidade_disponivel(sistema->unidades, POLICIA);
        if (policia) {
            Ocorrencia* ocorrencia = desenfileirar(sistema->fila_policia);
            policia->disponivel = 0;
            
            // Adiciona ao histórico
            empilhar_historico(sistema->historico_policia, ocorrencia->id, 
                             ocorrencia->bairro_id, ocorrencia->tipo_servico, 
                             ocorrencia->gravidade, sistema->tempo_atual, 
                             sistema->tempo_atual + 1, "Atendimento policial");
            
            // Atualiza mapa da cidade
            atualizar_unidades_disponiveis(sistema->mapa_cidade, ocorrencia->bairro_id, POLICIA, -1);
            
            printf("Policia %s atendendo ocorrencia #%d no bairro %d\n", 
                   policia->identificacao, ocorrencia->id, ocorrencia->bairro_id);
            free(ocorrencia);
        }
    }
}

// Simula passagem do tempo
void simular_tempo(SistemaEmergencia* sistema, int unidades_tempo) {
    if (!sistema) return;
    
    for (int i = 0; i < unidades_tempo; i++) {
        sistema->tempo_atual++;
        
        // Libera algumas unidades aleatoriamente (simulação simples)
        UnidadeServico* atual = sistema->unidades;
        while (atual) {
            if (!atual->disponivel && (sistema->tempo_atual % 3 == 0)) {
                atual->disponivel = 1;
                // Atualiza mapa da cidade
                adicionar_servico_bairro(sistema->mapa_cidade, 1, atual->tipo); // Simula retorno ao centro
                printf("Unidade %s ficou disponivel\n", atual->identificacao);
            }
            atual = atual->prox;
        }
        
        processar_atendimentos(sistema);
    }
}

// Mostra status geral do sistema
void status_sistema(SistemaEmergencia* sistema) {
    if (!sistema) return;
    
    printf("\n============ STATUS DO SISTEMA ============\n");
    printf("Tempo atual: %d\n", sistema->tempo_atual);
    printf("Próximo ID de ocorrência: %d\n", sistema->proximo_id_ocorrencia);
    
    listar_bairros(sistema->bairros);
    listar_unidades(sistema->unidades);
    
    printf("\n=== FILAS DE ATENDIMENTO ===\n");
    printf("Ambulância: ");
    mostrar_fila(sistema->fila_ambulancia);
    printf("Bombeiro: ");
    mostrar_fila(sistema->fila_bombeiro);
    printf("Polícia: ");
    mostrar_fila(sistema->fila_policia);
    
    // Mostra estatísticas dos históricos
    printf("\n=== ESTATÍSTICAS DE ATENDIMENTO ===\n");
    printf("Ambulâncias - Atendimentos realizados: %d\n", sistema->historico_ambulancia->tamanho);
    printf("Bombeiros - Atendimentos realizados: %d\n", sistema->historico_bombeiro->tamanho);
    printf("Polícia - Atendimentos realizados: %d\n", sistema->historico_policia->tamanho);
    
    // NOVA - FASE 3: Mostra estatísticas das árvores
    printf("\n=== ESTRUTURAS INTELIGENTES (FASE 3) ===\n");
    printf("🌳 BST - Ocorrências indexadas: %d\n", sistema->arvore_ocorrencias->tamanho);
    printf("🌲 AVL - Ocorrências priorizadas: %d\n", sistema->arvore_prioridades->tamanho);
    
    printf("==========================================\n");
}

// Libera toda a memória do sistema (MODIFICADO - FASE 3)
void liberar_sistema(SistemaEmergencia* sistema) {
    if (!sistema) return;
    
    liberar_tabela_bairros(sistema->bairros);
    liberar_tabela_cidadaos(sistema->cidadaos);
    liberar_unidades(sistema->unidades);
    liberar_pilha_historico(sistema->historico_ambulancia);
    liberar_pilha_historico(sistema->historico_bombeiro);
    liberar_pilha_historico(sistema->historico_policia);
    liberar_lista_cruzada(sistema->mapa_cidade);
    liberar_fila(sistema->fila_ambulancia);
    liberar_fila(sistema->fila_bombeiro);
    liberar_fila(sistema->fila_policia);
    liberar_bst_completa(sistema->arvore_ocorrencias); // NOVA - FASE 3
    liberar_avl_completa(sistema->arvore_prioridades); // NOVA - FASE 3
    free(sistema);
}

// ==================== IMPLEMENTAÇÃO - FUNÇÕES AUXILIARES DE INTERFACE ====================

void limpar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int ler_inteiro(const char* mensagem) {
    int valor;
    printf("%s", mensagem);
    while (scanf("%d", &valor) != 1) {
        printf("Entrada inválida! %s", mensagem);
        limpar_buffer();
    }
    limpar_buffer();
    return valor;
}

void ler_string(const char* mensagem, char* destino, int tamanho) {
    printf("%s", mensagem);
    fgets(destino, tamanho, stdin);
    // Remove \n do final se existir
    destino[strcspn(destino, "\n")] = '\0';
}

TipoServico escolher_tipo_servico() {
    int opcao;
    printf("\nEscolha o tipo de serviço:\n");
    printf("1. Ambulância\n");
    printf("2. Bombeiro\n");
    printf("3. Polícia\n");
    printf("Opção: ");
    
    while (scanf("%d", &opcao) != 1 || opcao < 1 || opcao > 3) {
        printf("Opção inválida! Digite 1, 2 ou 3: ");
        limpar_buffer();
    }
    limpar_buffer();
    
    switch (opcao) {
        case 1: return AMBULANCIA;
        case 2: return BOMBEIRO;
        case 3: return POLICIA;
        default: return AMBULANCIA;
    }
}

void pausar_sistema() {
    printf("\nPressione Enter para continuar...");
    getchar();
}

void exibir_menu_principal() {
    printf("\n===== SIMULADOR DE EMERGENCIA URBANA =====\n");
    printf("1. Iniciar Simulacao\n");
    printf("2. Verificar Dados\n");
    printf("3. Configurar Sistema\n");
    printf("4. Consultas e Históricos\n");
    printf("5. Consultas com Árvores\n"); // NOVA - FASE 3
    printf("0. Fechar Programa\n");
    printf("Escolha uma opcao: ");
}

// ==================== IMPLEMENTAÇÃO - MENUS DE CONFIGURAÇÃO ====================

// Menu de configuração expandido
void menu_configuracao(SistemaEmergencia* sistema) {
    int opcaoConfig;
    do {
        printf("\n=== MENU CONFIGURAÇÃO ===\n");
        printf("1. Adicionar Bairro\n");
        printf("2. Remover Bairro\n");
        printf("3. Listar Bairros\n");
        printf("4. Adicionar Cidadão\n");
        printf("5. Remover Cidadão\n");
        printf("6. Listar Cidadãos\n");
        printf("7. Adicionar Unidade de Serviço\n");
        printf("8. Listar Unidades\n");
        printf("9. Ver Mapa da Cidade\n");
        printf("0. Voltar ao menu principal\n");
        printf("Escolha uma opcao: ");
        
        while (scanf("%d", &opcaoConfig) != 1) {
            printf("Entrada inválida! Digite um número: ");
            limpar_buffer();
        }
        limpar_buffer();

        switch (opcaoConfig) {
            case 1: {
                int id = ler_inteiro("Digite o ID do bairro: ");
                char nome[MAX_NOME];
                ler_string("Digite o nome do bairro: ", nome, sizeof(nome));
                cadastrar_bairro_sistema(sistema, id, nome);
                break;
            }
            case 2: {
                int idRemover = ler_inteiro("Digite o ID do bairro para remover: ");
                if (remover_bairro(sistema->bairros, idRemover)) {
                    printf("Bairro removido com sucesso.\n");
                } else {
                    printf("Bairro não encontrado.\n");
                }
                break;
            }
            case 3:
                listar_bairros(sistema->bairros);
                break;
            case 4: {
                char cpf[MAX_CPF], nome[MAX_NOME], email[MAX_EMAIL], endereco[MAX_ENDERECO];
                int bairro_id;
                
                ler_string("Digite o CPF: ", cpf, sizeof(cpf));
                ler_string("Digite o nome: ", nome, sizeof(nome));
                ler_string("Digite o email: ", email, sizeof(email));
                ler_string("Digite o endereço: ", endereco, sizeof(endereco));
                bairro_id = ler_inteiro("Digite o ID do bairro: ");
                
                cadastrar_cidadao_sistema(sistema, cpf, nome, email, endereco, bairro_id);
                break;
            }
            case 5: {
                char cpf[MAX_CPF];
                ler_string("Digite o CPF do cidadão para remover: ", cpf, sizeof(cpf));
                if (remover_cidadao(sistema->cidadaos, cpf)) {
                    printf("Cidadão removido com sucesso.\n");
                } else {
                    printf("Cidadão não encontrado.\n");
                }
                break;
            }
            case 6:
                listar_cidadaos(sistema->cidadaos);
                break;
            case 7: {
                int id = ler_inteiro("Digite o ID da unidade: ");
                char identificacao[MAX_NOME];
                ler_string("Digite a identificação (ex: AMB-01): ", identificacao, sizeof(identificacao));
                TipoServico tipo = escolher_tipo_servico();
                cadastrar_unidade_sistema(sistema, id, tipo, identificacao);
                break;
            }
            case 8:
                listar_unidades(sistema->unidades);
                break;
            case 9:
                mostrar_mapa_cidade(sistema->mapa_cidade);
                break;
            case 0:
                printf("Voltando ao menu principal...\n");
                break;
            default:
                printf("Opcao invalida.\n");
        }
        
        if (opcaoConfig != 0) {
            pausar_sistema();
        }
    } while (opcaoConfig != 0);
}

// Menu de consultas expandido (MODIFICADO - FASE 3)
void menu_consultas(SistemaEmergencia* sistema) {
    int opcao;
    do {
        printf("\n=== CONSULTAS E HISTÓRICOS ===\n");
        printf("🔍 Buscas Básicas:\n");
        printf("1. Buscar Cidadão por CPF\n");
        printf("2. Buscar Bairro por ID\n");
        printf("\n📋 Históricos:\n");
        printf("3. Histórico de Ambulâncias\n");
        printf("4. Histórico de Bombeiros\n");
        printf("5. Histórico da Polícia\n");
        printf("\n🗺️ Mapas e Estatísticas:\n");
        printf("6. Mapa Completo da Cidade\n");
        printf("7. Estatísticas Gerais\n");
        printf("\n🆕 Buscas Inteligentes (Fase 3):\n");
        printf("8. Busca Rápida por ID (BST)\n");
        printf("9. Consulta por Prioridade (AVL)\n");
        printf("0. Voltar ao menu principal\n");
        printf("Escolha uma opção: ");
        
        while (scanf("%d", &opcao) != 1) {
            printf("Entrada inválida! Digite um número: ");
            limpar_buffer();
        }
        limpar_buffer();
        
        switch (opcao) {
            case 1: {
                char cpf[MAX_CPF];
                ler_string("Digite o CPF: ", cpf, sizeof(cpf));
                Cidadao* cidadao = buscar_cidadao(sistema->cidadaos, cpf);
                if (cidadao) {
                    printf("\n=== CIDADÃO ENCONTRADO ===\n");
                    printf("Nome: %s\n", cidadao->nome);
                    printf("CPF: %s\n", cidadao->cpf);
                    printf("Email: %s\n", cidadao->email);
                    printf("Endereço: %s\n", cidadao->endereco);
                    printf("Bairro ID: %d\n", cidadao->bairro_id);
                } else {
                    printf("Cidadão não encontrado!\n");
                }
                break;
            }
            case 2: {
                int id = ler_inteiro("Digite o ID do bairro: ");
                Bairro* bairro = buscar_bairro(sistema->bairros, id);
                if (bairro) {
                    printf("\n=== BAIRRO ENCONTRADO ===\n");
                    printf("ID: %d\n", bairro->id);
                    printf("Nome: %s\n", bairro->nome);
                } else {
                    printf("Bairro não encontrado!\n");
                }
                break;
            }
            case 3:
                printf("\n=== HISTÓRICO DE AMBULÂNCIAS ===\n");
                mostrar_historico(sistema->historico_ambulancia);
                break;
            case 4:
                printf("\n=== HISTÓRICO DE BOMBEIROS ===\n");
                mostrar_historico(sistema->historico_bombeiro);
                break;
            case 5:
                printf("\n=== HISTÓRICO DA POLÍCIA ===\n");
                mostrar_historico(sistema->historico_policia);
                break;
            case 6:
                mostrar_mapa_cidade(sistema->mapa_cidade);
                break;
            case 7: {
                printf("\n=== ESTATÍSTICAS GERAIS ===\n");
                printf("Total de atendimentos:\n");
                printf("  Ambulâncias: %d\n", sistema->historico_ambulancia->tamanho);
                printf("  Bombeiros: %d\n", sistema->historico_bombeiro->tamanho);
                printf("  Polícia: %d\n", sistema->historico_policia->tamanho);
                printf("  TOTAL: %d\n", sistema->historico_ambulancia->tamanho + 
                                        sistema->historico_bombeiro->tamanho + 
                                        sistema->historico_policia->tamanho);
                printf("Tempo atual do sistema: %d\n", sistema->tempo_atual);
                printf("🆕 Ocorrências na BST: %d\n", sistema->arvore_ocorrencias->tamanho);
                printf("🆕 Ocorrências na AVL: %d\n", sistema->arvore_prioridades->tamanho);
                break;
            }
            case 8: { // NOVA - FASE 3
                int id = ler_inteiro("Digite o ID da ocorrência: ");
                printf("\n🚀 BUSCA INTELIGENTE (BST):\n");
                Ocorrencia* ocorrencia = buscar_ocorrencia_por_id(sistema->arvore_ocorrencias, id);
                if (ocorrencia) {
                    printf("✅ Encontrada em O(log n)!\n");
                    printf("ID: %d | Bairro: %d | %s | Gravidade: %d\n",
                           ocorrencia->id, ocorrencia->bairro_id,
                           tipo_servico_string(ocorrencia->tipo_servico),
                           ocorrencia->gravidade);
                } else {
                    printf("❌ Ocorrência não encontrada!\n");
                }
                break;
            }
            case 9: { // NOVA - FASE 3
                printf("\n🚨 CONSULTA POR PRIORIDADE (AVL):\n");
                printf("Ocorrências ordenadas por gravidade:\n");
                mostrar_ocorrencias_por_prioridade(sistema->arvore_prioridades);
                break;
            }
            case 0:
                printf("Voltando ao menu principal...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
        
        if (opcao != 0) {
            pausar_sistema();
        }
    } while (opcao != 0);
}

// Adicione este include no topo do arquivo emergencia.c se não estiver presente:
// #include <math.h>

// ==================== IMPLEMENTAÇÃO - MENU ÁRVORES (NOVA - FASE 3) ====================

// Menu específico para consultas com árvores
void menu_arvores(SistemaEmergencia* sistema) {
    int opcao;
    do {
        printf("\n=== 🌳 CONSULTAS COM ÁRVORES (FASE 3) ===\n");
        printf("🔍 Busca Inteligente:\n");
        printf("1. Buscar Ocorrência por ID (BST)\n");
        printf("2. Listar Todas as Ocorrências por ID (BST)\n");
        printf("3. Consultar por Prioridade (AVL)\n");
        printf("4. Mostrar Estrutura da Árvore BST\n");
        printf("5. Mostrar Estrutura da Árvore AVL\n");
        printf("\n📊 Operações Avançadas:\n");
        printf("6. Remover Ocorrência por ID (BST)\n");
        printf("7. Buscar por Gravidade (AVL)\n");
        printf("8. Estatísticas das Árvores\n");
        printf("\n🧪 Testes de Performance:\n");
        printf("9. Teste de Busca Sequencial vs BST\n");
        printf("10. Demonstração de Balanceamento AVL\n");
        printf("0. Voltar ao menu principal\n");
        printf("Escolha uma opção: ");
        
        while (scanf("%d", &opcao) != 1) {
            printf("Entrada inválida! Digite um número: ");
            limpar_buffer();
        }
        limpar_buffer();
        
        switch (opcao) {
            case 1: {
                int id = ler_inteiro("Digite o ID da ocorrência: ");
                printf("\n🚀 BUSCA INTELIGENTE (BST) - Complexidade O(log n):\n");
                Ocorrencia* ocorrencia = buscar_ocorrencia_por_id(sistema->arvore_ocorrencias, id);
                if (ocorrencia) {
                    printf("✅ Ocorrência encontrada rapidamente!\n");
                    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
                    printf("📋 ID: %d\n", ocorrencia->id);
                    printf("🏘️  Bairro: %d\n", ocorrencia->bairro_id);
                    printf("🚨 Serviço: %s\n", tipo_servico_string(ocorrencia->tipo_servico));
                    printf("⚠️  Gravidade: %d\n", ocorrencia->gravidade);
                    printf("⏰ Tempo de Chegada: %d\n", ocorrencia->tempo_chegada);
                    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
                } else {
                    printf("❌ Ocorrência com ID %d não encontrada!\n", id);
                }
                break;
            }
            case 2:
                printf("\n📋 TODAS AS OCORRÊNCIAS ORDENADAS POR ID:\n");
                mostrar_arvore_ordenada_por_id(sistema->arvore_ocorrencias);
                break;
            case 3:
                printf("\n🚨 CONSULTA POR PRIORIDADE (AVL):\n");
                printf("Árvore auto-balanceada para máxima eficiência!\n");
                mostrar_ocorrencias_por_prioridade(sistema->arvore_prioridades);
                break;
            case 4:
                printf("\n🌳 ESTRUTURA COMPLETA DA ÁRVORE BST:\n");
                mostrar_arvore_bst(sistema->arvore_ocorrencias);
                break;
            case 5:
                printf("\n🌲 ESTRUTURA COMPLETA DA ÁRVORE AVL:\n");
                mostrar_arvore_avl(sistema->arvore_prioridades);
                break;
            case 6: {
                int id = ler_inteiro("Digite o ID da ocorrência para remover: ");
                if (remover_ocorrencia_bst(sistema->arvore_ocorrencias, id)) {
                    printf("✅ Ocorrência #%d removida da BST com sucesso!\n", id);
                } else {
                    printf("❌ Ocorrência #%d não encontrada para remoção!\n", id);
                }
                break;
            }
            case 7: {
                int gravidade = ler_inteiro("Digite a gravidade para buscar (1-3): ");
                if (gravidade < 1 || gravidade > 3) {
                    printf("❌ Gravidade deve estar entre 1 e 3!\n");
                    break;
                }
                printf("\n🔍 BUSCA POR GRAVIDADE %d (AVL):\n", gravidade);
                Ocorrencia* ocorrencia = buscar_por_gravidade(sistema->arvore_prioridades, gravidade);
                if (ocorrencia) {
                    printf("✅ Encontrada ocorrência com gravidade %d:\n", gravidade);
                    printf("ID: %d | Bairro: %d | %s\n", 
                           ocorrencia->id, ocorrencia->bairro_id,
                           tipo_servico_string(ocorrencia->tipo_servico));
                } else {
                    printf("❌ Nenhuma ocorrência encontrada com gravidade %d!\n", gravidade);
                }
                break;
            }
            case 8: {
                printf("\n📊 ESTATÍSTICAS DAS ÁRVORES:\n");
                printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
                printf("🌳 BST (Busca por ID):\n");
                printf("   • Ocorrências indexadas: %d\n", sistema->arvore_ocorrencias->tamanho);
                printf("   • Complexidade de busca: O(log n) médio\n");
                printf("   • Uso: Consultas rápidas por ID\n\n");
                printf("🌲 AVL (Priorização):\n");
                printf("   • Ocorrências priorizadas: %d\n", sistema->arvore_prioridades->tamanho);
                printf("   • Complexidade de busca: O(log n) garantido\n");
                printf("   • Uso: Ordenação automática por gravidade\n");
                printf("   • Balanceamento: Automático\n");
                printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
                break;
            }
            case 9: {
                printf("\n⚡ TESTE DE PERFORMANCE: Busca Sequencial vs BST\n");
                printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
                if (sistema->arvore_ocorrencias->tamanho > 0) {
                    printf("🔍 Simulando busca em %d ocorrências...\n", sistema->arvore_ocorrencias->tamanho);
                    printf("📈 Busca Sequencial: O(n) = %d comparações\n", sistema->arvore_ocorrencias->tamanho);
                    printf("🚀 Busca BST: O(log n) ≈ %.1f comparações\n", 
                           sistema->arvore_ocorrencias->tamanho > 1 ? 
                           log2(sistema->arvore_ocorrencias->tamanho) : 1.0);
                    printf("⚡ Melhoria: %.1fx mais rápido!\n", 
                           sistema->arvore_ocorrencias->tamanho > 1 ? 
                           (float)sistema->arvore_ocorrencias->tamanho / log2(sistema->arvore_ocorrencias->tamanho) : 1.0);
                } else {
                    printf("❌ Nenhuma ocorrência cadastrada para teste!\n");
                }
                printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
                break;
            }
            case 10: {
                printf("\n🔄 DEMONSTRAÇÃO DE BALANCEAMENTO AVL:\n");
                printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
                printf("A árvore AVL se rebalanceia automaticamente!\n");
                printf("Cada nó mostra seu Fator de Balanceamento (FB):\n");
                printf("• FB = altura(esquerda) - altura(direita)\n");
                printf("• FB ∈ {-1, 0, 1} garante balanceamento\n");
                printf("• Rotações automáticas mantêm a eficiência\n\n");
                mostrar_arvore_avl(sistema->arvore_prioridades);
                printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
                break;
            }
            case 0:
                printf("Voltando ao menu principal...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
        
        if (opcao != 0) {
            pausar_sistema();
        }
    } while (opcao != 0);
}

// ==================== IMPLEMENTAÇÃO - SIMULAÇÃO PRINCIPAL ====================

// Função principal de simulação com dados de exemplo
void iniciar_simulacao(SistemaEmergencia* sistema) {
    printf("\n🚀 INICIANDO SIMULAÇÃO COMPLETA DO SISTEMA\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    
    // ==================== CONFIGURAÇÃO INICIAL ====================
    printf("\n📋 FASE 1: Configuração Inicial do Sistema\n");
    printf("──────────────────────────────────────────────────────────\n");
    
    // Cadastra bairros
    printf("🏘️  Cadastrando bairros...\n");
    cadastrar_bairro_sistema(sistema, 1, "Centro");
    cadastrar_bairro_sistema(sistema, 2, "Jardim Paulista");
    cadastrar_bairro_sistema(sistema, 3, "Vila Madalena");
    cadastrar_bairro_sistema(sistema, 4, "Ipiranga");
    cadastrar_bairro_sistema(sistema, 5, "Mooca");
    
    // Cadastra cidadãos
    printf("\n👥 Cadastrando cidadãos...\n");
    cadastrar_cidadao_sistema(sistema, "111.111.111-11", "João Silva", 
                             "joao@email.com", "Rua das Flores, 123", 1);
    cadastrar_cidadao_sistema(sistema, "222.222.222-22", "Maria Santos", 
                             "maria@email.com", "Av. Paulista, 456", 2);
    cadastrar_cidadao_sistema(sistema, "333.333.333-33", "Pedro Costa", 
                             "pedro@email.com", "Rua Augusta, 789", 3);
    cadastrar_cidadao_sistema(sistema, "444.444.444-44", "Ana Oliveira", 
                             "ana@email.com", "Rua Independência, 321", 4);
    
    // Cadastra unidades de serviço
    printf("\n🚑 Cadastrando unidades de emergência...\n");
    cadastrar_unidade_sistema(sistema, 1, AMBULANCIA, "AMB-01");
    cadastrar_unidade_sistema(sistema, 2, AMBULANCIA, "AMB-02");
    cadastrar_unidade_sistema(sistema, 3, BOMBEIRO, "BOMB-01");
    cadastrar_unidade_sistema(sistema, 4, BOMBEIRO, "BOMB-02");
    cadastrar_unidade_sistema(sistema, 5, POLICIA, "POL-01");
    cadastrar_unidade_sistema(sistema, 6, POLICIA, "POL-02");
    
    // Configura serviços nos bairros
    printf("\n🗺️  Configurando mapa da cidade...\n");
    for (int i = 1; i <= 5; i++) {
        adicionar_servico_bairro(sistema->mapa_cidade, i, AMBULANCIA);
        adicionar_servico_bairro(sistema->mapa_cidade, i, BOMBEIRO);
        adicionar_servico_bairro(sistema->mapa_cidade, i, POLICIA);
    }
    
    pausar_sistema();
    
    // ==================== SIMULAÇÃO DE OCORRÊNCIAS ====================
    printf("\n🚨 FASE 2: Simulação de Ocorrências de Emergência\n");
    printf("──────────────────────────────────────────────────────────\n");
    
    printf("Gerando ocorrências de emergência...\n\n");
    
    // Simula diversas ocorrências com diferentes prioridades
    receber_ocorrencia(sistema, 1, AMBULANCIA, 3);  // Alta prioridade
    receber_ocorrencia(sistema, 2, BOMBEIRO, 2);    // Média prioridade
    receber_ocorrencia(sistema, 3, POLICIA, 1);     // Baixa prioridade
    receber_ocorrencia(sistema, 4, AMBULANCIA, 2);  // Média prioridade
    receber_ocorrencia(sistema, 5, BOMBEIRO, 3);    // Alta prioridade
    receber_ocorrencia(sistema, 1, POLICIA, 2);     // Média prioridade
    receber_ocorrencia(sistema, 3, AMBULANCIA, 1);  // Baixa prioridade
    receber_ocorrencia(sistema, 2, POLICIA, 3);     // Alta prioridade
    
    printf("\n📊 Status das filas após recebimento:\n");
    status_sistema(sistema);
    
    pausar_sistema();
    
    // ==================== PROCESSAMENTO E ATENDIMENTOS ====================
    printf("\n⚡ FASE 3: Processamento Inteligente de Atendimentos\n");
    printf("──────────────────────────────────────────────────────────\n");
    
    printf("Iniciando processamento automático...\n");
    
    // Simula 5 unidades de tempo
    for (int tempo = 1; tempo <= 5; tempo++) {
        printf("\n🕐 === TEMPO %d ===\n", tempo);
        simular_tempo(sistema, 1);
        
        if (tempo == 3) {
            printf("\n🆘 NOVA EMERGÊNCIA CRÍTICA!\n");
            receber_ocorrencia(sistema, 1, AMBULANCIA, 3);
            receber_ocorrencia(sistema, 4, BOMBEIRO, 3);
        }
        
        printf("\n");
    }
    
    pausar_sistema();
    
    // ==================== DEMONSTRAÇÃO DAS ÁRVORES ====================
    printf("\n🌳 FASE 4: Consultas Inteligentes com Árvores (FASE 3)\n");
    printf("──────────────────────────────────────────────────────────\n");
    
    printf("🔍 Demonstrando busca inteligente por ID:\n");
    mostrar_arvore_bst(sistema->arvore_ocorrencias);
    
    printf("\n🚨 Demonstrando priorização automática:\n");
    mostrar_arvore_avl(sistema->arvore_prioridades);
    
    // Teste de busca específica
    printf("\n🎯 Teste de busca rápida:\n");
    Ocorrencia* teste = buscar_ocorrencia_por_id(sistema->arvore_ocorrencias, 1);
    if (teste) {
        printf("✅ Busca por ID 1: SUCESSO em O(log n)!\n");
    }
    
    pausar_sistema();
    
    // ==================== RELATÓRIOS FINAIS ====================
    printf("\n📈 FASE 5: Relatórios e Estatísticas Finais\n");
    printf("──────────────────────────────────────────────────────────\n");
    
    // Mostra históricos
    printf("📋 Histórico de Ambulâncias:\n");
    mostrar_historico(sistema->historico_ambulancia);
    
    printf("\n🔥 Histórico de Bombeiros:\n");
    mostrar_historico(sistema->historico_bombeiro);
    
    printf("\n👮 Histórico da Polícia:\n");
    mostrar_historico(sistema->historico_policia);
    
    // Estatísticas das estruturas avançadas
    printf("\n🧠 ESTRUTURAS INTELIGENTES:\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    printf("🌳 BST - Ocorrências indexadas: %d\n", sistema->arvore_ocorrencias->tamanho);
    printf("🌲 AVL - Ocorrências priorizadas: %d\n", sistema->arvore_prioridades->tamanho);
    printf("⚡ Eficiência de busca: O(log n) garantida\n");
    printf("🔄 Balanceamento: Automático (AVL)\n");
    
    // Mostra mapa final da cidade
    printf("\n🗺️  MAPA FINAL DA CIDADE:\n");
    mostrar_mapa_cidade(sistema->mapa_cidade);
    
    printf("\n✅ SIMULAÇÃO COMPLETA FINALIZADA COM SUCESSO!\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    printf("📊 Total de atendimentos realizados: %d\n", 
           sistema->historico_ambulancia->tamanho + 
           sistema->historico_bombeiro->tamanho + 
           sistema->historico_policia->tamanho);
    printf("⏰ Tempo total simulado: %d unidades\n", sistema->tempo_atual);
    printf("🏆 Sistema funcionando perfeitamente!\n");
    
    pausar_sistema();
}

// ==================== IMPLEMENTAÇÃO - VERIFICAÇÃO DE DADOS ====================

// Função para verificar dados do sistema
void verificar_dados(SistemaEmergencia* sistema) {
    printf("\n🔍 VERIFICAÇÃO COMPLETA DO SISTEMA\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    
    // Status geral
    status_sistema(sistema);
    
    // Detalhes das estruturas avançadas
    printf("\n🆕 ESTRUTURAS AVANÇADAS (FASE 3):\n");
    printf("──────────────────────────────────────────────────────────\n");
    
    // Verifica árvore BST
    if (sistema->arvore_ocorrencias->tamanho > 0) {
        printf("🌳 ÁRVORE BST - Consulta por ID:\n");
        mostrar_arvore_ordenada_por_id(sistema->arvore_ocorrencias);
    } else {
        printf("🌳 Árvore BST vazia - nenhuma ocorrência cadastrada\n");
    }
    
    printf("\n");
    
    // Verifica árvore AVL
    if (sistema->arvore_prioridades->tamanho > 0) {
        printf("🌲 ÁRVORE AVL - Ordenação por Prioridade:\n");
        mostrar_ocorrencias_por_prioridade(sistema->arvore_prioridades);
    } else {
        printf("🌲 Árvore AVL vazia - nenhuma ocorrência priorizada\n");
    }
    
    // Mostra mapa da cidade
    printf("\n🗺️  MAPA DETALHADO DA CIDADE:\n");
    mostrar_mapa_cidade(sistema->mapa_cidade);
    
    // Análise de performance
    printf("\n⚡ ANÁLISE DE PERFORMANCE:\n");
    printf("──────────────────────────────────────────────────────────\n");
    printf("📊 Complexidades de busca:\n");
    printf("   • Bairros por ID: O(1) - Hash Table\n");
    printf("   • Cidadãos por CPF: O(1) - Hash Table\n");
    printf("   • Ocorrências por ID: O(log n) - BST\n");
    printf("   • Priorização: O(log n) - AVL balanceada\n");
    printf("   • Filas de atendimento: O(1) - FIFO\n");
    printf("   • Histórico: O(1) - Pilhas LIFO\n");
    
    printf("\n🎯 Recomendações:\n");
    if (sistema->arvore_ocorrencias->tamanho == 0) {
        printf("   ⚠️  Execute uma simulação para ver as árvores em ação!\n");
    } else {
        printf("   ✅ Sistema com dados suficientes para análise\n");
    }
    
    if (sistema->historico_ambulancia->tamanho + 
        sistema->historico_bombeiro->tamanho + 
        sistema->historico_policia->tamanho == 0) {
        printf("   ⚠️  Nenhum atendimento realizado ainda\n");
    } else {
        printf("   ✅ Histórico de atendimentos disponível\n");
    }
    
    printf("\n━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    
    pausar_sistema();
}