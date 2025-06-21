#include "emergencia.h"

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
        printf("Bairro: %s (ID: %d)\n", bairro->nome_bairro, bairro->bairro_id);
        
        if (!bairro->servicos) {
            printf("   [X] Nenhum serviço disponível\n");
        } else {
            NoServico* servico = bairro->servicos;
            while (servico) {
                printf("   [Ok] %s: %d unidades disponíveis\n", 
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

// ==================== IMPLEMENTAÇÃO - SISTEMA PRINCIPAL ====================

// Inicializa o sistema de emergência
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

// Recebe uma nova ocorrência no sistema
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
    
    printf("==========================================\n");
}

// Libera toda a memória do sistema
void liberar_sistema(SistemaEmergencia* sistema) {
    if (!sistema) return;
    
    liberar_tabela_bairros(sistema->bairros);
    liberar_tabela_cidadaos(sistema->cidadaos); // NOVA - FASE 2
    liberar_unidades(sistema->unidades);
    liberar_pilha_historico(sistema->historico_ambulancia); // NOVA - FASE 2
    liberar_pilha_historico(sistema->historico_bombeiro); // NOVA - FASE 2
    liberar_pilha_historico(sistema->historico_policia); // NOVA - FASE 2
    liberar_lista_cruzada(sistema->mapa_cidade); // NOVA - FASE 2
    liberar_fila(sistema->fila_ambulancia);
    liberar_fila(sistema->fila_bombeiro);
    liberar_fila(sistema->fila_policia);
    free(sistema);
}

// ==================== IMPLEMENTAÇÃO - FUNÇÕES DE INTERFACE ====================

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
    printf("4. Consultas e Históricos\n"); // NOVA - FASE 2
    printf("0. Fechar Programa\n");
    printf("Escolha uma opcao: ");
}

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

// Novo menu de consultas e históricos
void menu_consultas(SistemaEmergencia* sistema) {
    int opcao;
    do {
        printf("\n=== CONSULTAS E HISTÓRICOS ===\n");
        printf("1. Buscar Cidadão por CPF\n");
        printf("2. Buscar Bairro por ID\n");
        printf("3. Histórico de Ambulâncias\n");
        printf("4. Histórico de Bombeiros\n");
        printf("5. Histórico da Polícia\n");
        printf("6. Mapa Completo da Cidade\n");
        printf("7. Estatísticas Gerais\n");
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

// Simulação atualizada
void iniciar_simulacao(SistemaEmergencia* sistema) {
    if (!sistema) return;
    
    printf("\n[INICIANDO SIMULAÇÃO AVANÇADA - FASE 2]\n");
    
    // Cadastra dados básicos se não existirem
    if (!buscar_bairro(sistema->bairros, 1)) {
        printf("\nCadastrando dados iniciais...\n");
        cadastrar_bairro_sistema(sistema, 1, "Centro");
        cadastrar_bairro_sistema(sistema, 2, "Jardim Bongiovani");
        cadastrar_bairro_sistema(sistema, 3, "Jardim das Rosas");
        cadastrar_bairro_sistema(sistema, 4, "Ana Jacinta");
        cadastrar_bairro_sistema(sistema, 5, "Alto da Boa Vista");
        
        // Cadastra cidadãos de exemplo
        cadastrar_cidadao_sistema(sistema, "123.456.789-01", "João Silva", "joao@email.com", "Rua A, 123", 1);
        cadastrar_cidadao_sistema(sistema, "987.654.321-01", "Maria Santos", "maria@email.com", "Rua B, 456", 2);
        cadastrar_cidadao_sistema(sistema, "456.789.123-01", "Carlos Oliveira", "carlos@email.com", "Rua C, 789", 3);
        
        cadastrar_unidade_sistema(sistema, 101, AMBULANCIA, "AMB-01");
        cadastrar_unidade_sistema(sistema, 102, AMBULANCIA, "AMB-02");
        cadastrar_unidade_sistema(sistema, 201, BOMBEIRO, "BOMB-01");
        cadastrar_unidade_sistema(sistema, 202, BOMBEIRO, "BOMB-02");
        cadastrar_unidade_sistema(sistema, 301, POLICIA, "POL-01");
        cadastrar_unidade_sistema(sistema, 302, POLICIA, "POL-02");
        
        // Inicializa serviços nos bairros na lista cruzada
        for (int i = 1; i <= 5; i++) {
            adicionar_servico_bairro(sistema->mapa_cidade, i, AMBULANCIA);
            adicionar_servico_bairro(sistema->mapa_cidade, i, BOMBEIRO);
            adicionar_servico_bairro(sistema->mapa_cidade, i, POLICIA);
        }
    }
    
    printf("\nGerando ocorrências...\n");
    receber_ocorrencia(sistema, 1, AMBULANCIA, 3);  // Emergência médica grave no Centro
    receber_ocorrencia(sistema, 2, BOMBEIRO, 2);    // Incêndio médio no Jardim Bongiovani
    receber_ocorrencia(sistema, 3, POLICIA, 1);     // Ocorrência policial leve no Jardim das Rosas
    receber_ocorrencia(sistema, 1, AMBULANCIA, 2);  // Outra emergência médica no Centro
    receber_ocorrencia(sistema, 4, BOMBEIRO, 3);    // Incêndio grave na Ana Jacinta
    
    printf("\nProcessando atendimentos...\n");
    processar_atendimentos(sistema);
    
    printf("\nSimulando passagem do tempo (3 unidades)...\n");
    simular_tempo(sistema, 3);
    
    printf("\nMais ocorrências chegando...\n");
    receber_ocorrencia(sistema, 5, POLICIA, 3);     // Emergência policial grave no Alto da Boa Vista
    receber_ocorrencia(sistema, 2, AMBULANCIA, 1);  // Emergência médica leve no Jardim Bongiovani
    
    printf("\nSimulação final (5 unidades de tempo)...\n");
    simular_tempo(sistema, 5);
    
    printf("\n=== DEMONSTRAÇÃO DAS NOVAS FUNCIONALIDADES ===\n");
    
    // Mostra históricos
    printf("\n Últimos atendimentos de ambulâncias:\n");
    mostrar_historico(sistema->historico_ambulancia);
    
    printf("\n Últimos atendimentos de bombeiros:\n");
    mostrar_historico(sistema->historico_bombeiro);
    
    printf("\n Últimos atendimentos da polícia:\n");
    mostrar_historico(sistema->historico_policia);
    
    // Mostra mapa da cidade
    printf("\n Mapa atual da cidade:\n");
    mostrar_mapa_cidade(sistema->mapa_cidade);
    
    // Demonstra busca rápida de cidadão
    printf("\n Demonstração de busca rápida:\n");
    Cidadao* cidadao = buscar_cidadao(sistema->cidadaos, "123.456.789-01");
    if (cidadao) {
        printf("Cidadão encontrado: %s - Bairro %d\n", cidadao->nome, cidadao->bairro_id);
    }
    
    printf("\n=== SIMULAÇÃO FASE 2 CONCLUÍDA ===\n");
    status_sistema(sistema);
    pausar_sistema();
}

void verificar_dados(SistemaEmergencia* sistema) {
    printf("\n[VERIFICANDO DADOS DO SISTEMA]\n");
    
    if (!sistema) {
        printf("Sistema não inicializado!\n");
        return;
    }
    
    int opcao;
    do {
        printf("\n=== VERIFICAR DADOS ===\n");
        printf("1. Ver status completo do sistema\n");
        printf("2. Listar apenas bairros\n");
        printf("3. Listar apenas cidadaos\n");
        printf("4. Listar apenas unidades\n");
        printf("5. Ver filas de atendimento\n");
        printf("6. Ver historicos de atendimento\n");
        printf("7. Ver mapa da cidade\n");
        printf("0. Voltar ao menu principal\n");
        printf("Escolha uma opção: ");
        
        while (scanf("%d", &opcao) != 1) {
            printf("Entrada inválida! Digite um número: ");
            limpar_buffer();
        }
        limpar_buffer();
        
        switch (opcao) {
            case 1:
                status_sistema(sistema);
                break;
            case 2:
                listar_bairros(sistema->bairros);
                break;
            case 3:
                listar_cidadaos(sistema->cidadaos);
                break;
            case 4:
                listar_unidades(sistema->unidades);
                break;
            case 5:
                printf("\n=== FILAS DE ATENDIMENTO ===\n");
                printf("Ambulância: ");
                mostrar_fila(sistema->fila_ambulancia);
                printf("Bombeiro: ");
                mostrar_fila(sistema->fila_bombeiro);
                printf("Polícia: ");
                mostrar_fila(sistema->fila_policia);
                break;
            case 6:
                printf("\n=== HISTÓRICOS DE ATENDIMENTO ===\n");
                printf("Ambulâncias:\n");
                mostrar_historico(sistema->historico_ambulancia);
                printf("\nBombeiros:\n");
                mostrar_historico(sistema->historico_bombeiro);
                printf("\nPolícia:\n");
                mostrar_historico(sistema->historico_policia);
                break;
            case 7:
                mostrar_mapa_cidade(sistema->mapa_cidade);
                break;
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