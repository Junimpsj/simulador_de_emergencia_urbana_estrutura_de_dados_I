#ifndef EMERGENCIA_H
#define EMERGENCIA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// ==================== CONSTANTES ====================
#define TAM_HASH 101 //Tamanho da tabela Hash
#define MAX_NOME 100 //Tamanho máximo para nomes
#define MAX_ENDERECO 200 //Tamanho máximo para endereços
#define MAX_CPF 15 //Tamanho máximo para CPF
#define MAX_EMAIL 100 //Tamanho máximo para email

// ==================== STRUCTS BAIRROS ====================
typedef struct Bairro {
    int id;
    char nome[MAX_NOME];
    struct Bairro* prox; //Para tratamento de colisões
} Bairro;

typedef struct {
    Bairro* tabela[TAM_HASH];
} TabelaHashBairros;

// ==================== STRUCTS CIDADÃOS ====================
typedef struct Cidadao {
    char cpf[MAX_CPF];
    char nome[MAX_NOME];
    char email[MAX_EMAIL];
    char endereco[MAX_ENDERECO];
    int bairro_id;
    struct Cidadao* prox; //Para tratamento de colisões
} Cidadao;

typedef struct {
    Cidadao* tabela[TAM_HASH];
} TabelaHashCidadaos;

// ==================== STRUCTS UNIDADES DE SERVIÇO ====================
typedef enum {
    AMBULANCIA,
    BOMBEIRO,
    POLICIA
} TipoServico;

typedef struct UnidadeServico {
    int id;
    TipoServico tipo;
    char identificacao[MAX_NOME];
    int disponivel; //Booleano, 1 é disponível e 0 é ocupado
    struct UnidadeServico* prox;
} UnidadeServico;

// ==================== STRUCTS HISTÓRICO ====================
typedef struct HistoricoAtendimento {
    int ocorrencia_id;
    int bairro_id;
    TipoServico tipo_servico;
    int gravidade;
    int tempo_inicio;
    int tempo_fim;
    char observacoes[MAX_NOME];
    struct HistoricoAtendimento* prox;
} HistoricoAtendimento;

typedef struct {
    HistoricoAtendimento* topo;
    int tamanho;
} PilhaHistorico;

// ==================== STRUCTS OCORRÊNCIAS ====================
typedef struct Ocorrencia {
    int id;
    int bairro_id;
    TipoServico tipo_servico;
    int gravidade; //1 para baixa, 2 para média, 3 para alta
    int tempo_chegada; //Unidade de tempo
    struct Ocorrencia* prox;
} Ocorrencia;

// ==================== STRUCTS FILAS ====================
typedef struct NoFila {
    Ocorrencia* ocorrencia;
    struct NoFila* prox;
} NoFila;

typedef struct {
    NoFila* inicio;
    NoFila* fim;
    int tamanho;
} Fila;

// ==================== STRUCTS LISTAS CRUZADAS ====================
typedef struct NoServico {
    TipoServico tipo;
    int unidades_disponiveis;
    struct NoServico* prox_servico;
} NoServico;

typedef struct NoBairroServico {
    int bairro_id;
    char nome_bairro[MAX_NOME];
    NoServico* servicos;
    struct NoBairroServico* prox_bairro;
} NoBairroServico;

typedef struct {
    NoBairroServico* primeiro;
} ListaCruzada;

// ==================== STRUCTS ÁRVORE BST ====================
typedef struct NoArvoreBST {
    Ocorrencia* ocorrencia;
    struct NoArvoreBST* esquerda;
    struct NoArvoreBST* direita;
} NoArvoreBST;

typedef struct {
    NoArvoreBST* raiz;
    int tamanho;
} ArvoreBST;

// ==================== STRUCTS ÁRVORE AVL ====================
typedef struct NoArvoreAVL {
    Ocorrencia* ocorrencia;
    int altura;
    int fator_balanceamento;
    struct NoArvoreAVL* esquerda;
    struct NoArvoreAVL* direita;
} NoArvoreAVL;

typedef struct {
    NoArvoreAVL* raiz;
    int tamanho;
} ArvoreAVL;

// ==================== STRUCTS SISTEMA PRINCIPAL ATUALIZADO====================
typedef struct {
    TabelaHashBairros* bairros;
    TabelaHashCidadaos* cidadaos;
    UnidadeServico* unidades;
    PilhaHistorico* historico_ambulancia;
    PilhaHistorico* historico_bombeiro;
    PilhaHistorico* historico_policia;
    ListaCruzada* mapa_cidade;
    Fila* fila_ambulancia;
    Fila* fila_bombeiro;
    Fila* fila_policia;
    ArvoreBST* arvore_ocorrencias; 
    ArvoreAVL* arvore_prioridades;
    int tempo_atual;
    int proximo_id_ocorrencia;
} SistemaEmergencia;

// ==================== FUNÇÕES HASH DOS BAIRROS ====================
int hash_bairro(int id);
TabelaHashBairros* criar_tabela_bairros();
int inserir_bairro(TabelaHashBairros* tabela, int id, const char* nome);
Bairro* buscar_bairro(TabelaHashBairros* tabela, int id);
void listar_bairros(TabelaHashBairros* tabela);
int remover_bairro(TabelaHashBairros* tabela, int id);
void liberar_tabela_bairros(TabelaHashBairros* tabela);

// ==================== FUNÇÕES HASH DOS CIDADÃOS ====================
int hash_cpf(const char* cpf);
TabelaHashCidadaos* criar_tabela_cidadaos();
int inserir_cidadao(TabelaHashCidadaos* tabela, const char* cpf, const char* nome, 
                   const char* email, const char* endereco, int bairro_id);
Cidadao* buscar_cidadao(TabelaHashCidadaos* tabela, const char* cpf);
void listar_cidadaos(TabelaHashCidadaos* tabela);
int remover_cidadao(TabelaHashCidadaos* tabela, const char* cpf);
void liberar_tabela_cidadaos(TabelaHashCidadaos* tabela);

// ==================== FUNÇÕES PILHA DE HISTÓRICO ====================
PilhaHistorico* criar_pilha_historico();
int pilha_vazia(PilhaHistorico* pilha);
void empilhar_historico(PilhaHistorico* pilha, int ocorrencia_id, int bairro_id, 
                       TipoServico tipo, int gravidade, int tempo_inicio, 
                       int tempo_fim, const char* observacoes);
HistoricoAtendimento* desempilhar_historico(PilhaHistorico* pilha);
void mostrar_historico(PilhaHistorico* pilha);
void liberar_pilha_historico(PilhaHistorico* pilha);

// ==================== FUNÇÕES LISTAS CRUZADAS ====================
ListaCruzada* criar_lista_cruzada();
int inserir_bairro_servico(ListaCruzada* lista, int bairro_id, const char* nome_bairro);
int adicionar_servico_bairro(ListaCruzada* lista, int bairro_id, TipoServico tipo);
int atualizar_unidades_disponiveis(ListaCruzada* lista, int bairro_id, TipoServico tipo, int delta);
void mostrar_mapa_cidade(ListaCruzada* lista);
void liberar_lista_cruzada(ListaCruzada* lista);

// ==================== FUNÇÕES ÁRVORE BST ====================
ArvoreBST* criar_arvore_bst();
NoArvoreBST* criar_no_bst(Ocorrencia* ocorrencia);
int inserir_bst(ArvoreBST* arvore, Ocorrencia* ocorrencia);
NoArvoreBST* buscar_bst(ArvoreBST* arvore, int id);
Ocorrencia* buscar_ocorrencia_por_id(ArvoreBST* arvore, int id);
void percorrer_em_ordem_bst(NoArvoreBST* no);
void percorrer_pre_ordem_bst(NoArvoreBST* no);
void percorrer_pos_ordem_bst(NoArvoreBST* no);
void mostrar_arvore_bst(ArvoreBST* arvore);
void mostrar_arvore_ordenada_por_id(ArvoreBST* arvore);
void mostrar_arvore_ordenada_por_tempo(ArvoreBST* arvore);
NoArvoreBST* remover_bst(NoArvoreBST* no, int id);
int remover_ocorrencia_bst(ArvoreBST* arvore, int id);
void liberar_arvore_bst(NoArvoreBST* no);
void liberar_bst_completa(ArvoreBST* arvore);

// ==================== FUNÇÕES ÁRVORE AVL ====================
ArvoreAVL* criar_arvore_avl();
NoArvoreAVL* criar_no_avl(Ocorrencia* ocorrencia);
int altura_avl(NoArvoreAVL* no);
int fator_balanceamento_avl(NoArvoreAVL* no);
int max_int(int a, int b);
NoArvoreAVL* rotacao_direita(NoArvoreAVL* y);
NoArvoreAVL* rotacao_esquerda(NoArvoreAVL* x);
NoArvoreAVL* inserir_avl(NoArvoreAVL* no, Ocorrencia* ocorrencia);
int inserir_avl_arvore(ArvoreAVL* arvore, Ocorrencia* ocorrencia);
NoArvoreAVL* buscar_avl(NoArvoreAVL* no, int gravidade);
Ocorrencia* buscar_por_gravidade(ArvoreAVL* arvore, int gravidade);
void percorrer_por_prioridade(NoArvoreAVL* no);
void mostrar_arvore_avl(ArvoreAVL* arvore);
void mostrar_ocorrencias_por_prioridade(ArvoreAVL* arvore);
NoArvoreAVL* remover_avl(NoArvoreAVL* no, int gravidade, int id);
int remover_ocorrencia_avl(ArvoreAVL* arvore, int gravidade, int id);
void liberar_arvore_avl(NoArvoreAVL* no);
void liberar_avl_completa(ArvoreAVL* arvore);

// ==================== FUNÇÕES UNIDADES DE SERVIÇO ====================
UnidadeServico* criar_unidade(int id, TipoServico tipo, const char* identificacao);
int inserir_unidade(UnidadeServico** lista, int id, TipoServico tipo, const char* identificacao);
UnidadeServico* buscar_unidade_disponivel(UnidadeServico* lista, TipoServico tipo);
void listar_unidades(UnidadeServico* lista);
const char* tipo_servico_string(TipoServico tipo);
void liberar_unidades(UnidadeServico* lista);

// ==================== FUNÇÕES FILAS ====================
Fila* criar_fila();
int fila_vazia(Fila* fila);
void enfileirar(Fila* fila, Ocorrencia* ocorrencia);
Ocorrencia* desenfileirar(Fila* fila);
void mostrar_fila(Fila* fila);
void liberar_fila(Fila* fila);

// ==================== FUNÇÕES OCORRÊNCIAS ====================
Ocorrencia* criar_ocorrencia(int id, int bairro_id, TipoServico tipo, int gravidade, int tempo);

// ==================== FUNÇÕES SISTEMA PRINCIPAL ====================
SistemaEmergencia* inicializar_sistema();
void cadastrar_bairro_sistema(SistemaEmergencia* sistema, int id, const char* nome);
void cadastrar_cidadao_sistema(SistemaEmergencia* sistema, const char* cpf, const char* nome,
                              const char* email, const char* endereco, int bairro_id);
void cadastrar_unidade_sistema(SistemaEmergencia* sistema, int id, TipoServico tipo, const char* identificacao);
void receber_ocorrencia(SistemaEmergencia* sistema, int bairro_id, TipoServico tipo, int gravidade);
void processar_atendimentos(SistemaEmergencia* sistema);
void simular_tempo(SistemaEmergencia* sistema, int unidades_tempo);
void status_sistema(SistemaEmergencia* sistema);
void liberar_sistema(SistemaEmergencia* sistema);

// ==================== FUNÇÕES INTERFACE ====================
void exibir_menu_principal();
void menu_configuracao(SistemaEmergencia* sistema);
void menu_consultas(SistemaEmergencia* sistema);
void menu_arvores(SistemaEmergencia* sistema);
void iniciar_simulacao(SistemaEmergencia* sistema);
void verificar_dados(SistemaEmergencia* sistema);

// ==================== FUNÇÕES AUXILIARES INTERFACE ====================
void limpar_buffer();
int ler_inteiro(const char* mensagem);
void ler_string(const char* mensagem, char* destino, int tamanho);
TipoServico escolher_tipo_servico();
void pausar_sistema();

#endif