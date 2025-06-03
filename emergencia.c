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
    sistema->unidades = NULL;
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
        printf("Bairro cadastrado: ID %d - %s\n", id, nome);
    } else {
        printf("Erro ao cadastrar bairro! (Pode já existir)\n");
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
    printf("==========================================\n");
}

// Libera toda a memória do sistema
void liberar_sistema(SistemaEmergencia* sistema) {
    if (!sistema) return;
    
    liberar_tabela_bairros(sistema->bairros);
    liberar_unidades(sistema->unidades);
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
    printf("0. Fechar Programa\n");
    printf("Escolha uma opcao: ");
}

void menu_configuracao(SistemaEmergencia* sistema) {
    int opcaoConfig;
    do {
        printf("\n=== MENU CONFIGURAÇÃO ===\n");
        printf("1. Adicionar Bairro\n");
        printf("2. Remover Bairro\n");
        printf("3. Listar Bairros\n");
        printf("4. Adicionar Unidade de Serviço\n");
        printf("5. Listar Unidades\n");
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
                int id = ler_inteiro("Digite o ID da unidade: ");
                char identificacao[MAX_NOME];
                ler_string("Digite a identificação (ex: AMB-01): ", identificacao, sizeof(identificacao));
                TipoServico tipo = escolher_tipo_servico();
                cadastrar_unidade_sistema(sistema, id, tipo, identificacao);
                break;
            }
            case 5:
                listar_unidades(sistema->unidades);
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

void iniciar_simulacao(SistemaEmergencia* sistema) {
    if (!sistema) return;
    
    printf("\n[INICIANDO SIMULAÇÃO BÁSICA]\n");
    
    // Cadastra dados básicos se não existirem
    if (!buscar_bairro(sistema->bairros, 1)) {
        printf("\nCadastrando dados iniciais...\n");
        cadastrar_bairro_sistema(sistema, 1, "Centro");
        cadastrar_bairro_sistema(sistema, 2, "Jardim Bongiovani");
        cadastrar_bairro_sistema(sistema, 3, "Jardim das Rosas");
        cadastrar_bairro_sistema(sistema, 4, "Ana Jacinta");
        cadastrar_bairro_sistema(sistema, 5, "Alto da Boa Vista");
        
        cadastrar_unidade_sistema(sistema, 101, AMBULANCIA, "AMB-01");
        cadastrar_unidade_sistema(sistema, 102, AMBULANCIA, "AMB-02");
        cadastrar_unidade_sistema(sistema, 201, BOMBEIRO, "BOMB-01");
        cadastrar_unidade_sistema(sistema, 202, BOMBEIRO, "BOMB-02");
        cadastrar_unidade_sistema(sistema, 301, POLICIA, "POL-01");
        cadastrar_unidade_sistema(sistema, 302, POLICIA, "POL-02");
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
    
    printf("\n=== SIMULAÇÃO CONCLUÍDA ===\n");
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
        printf("3. Listar apenas unidades\n");
        printf("4. Ver filas de atendimento\n");
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
                listar_unidades(sistema->unidades);
                break;
            case 4:
                printf("\n=== FILAS DE ATENDIMENTO ===\n");
                printf("Ambulância: ");
                mostrar_fila(sistema->fila_ambulancia);
                printf("Bombeiro: ");
                mostrar_fila(sistema->fila_bombeiro);
                printf("Polícia: ");
                mostrar_fila(sistema->fila_policia);
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