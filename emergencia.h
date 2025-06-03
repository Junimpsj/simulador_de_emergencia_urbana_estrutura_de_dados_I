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

// ==================== STRUCTS BAIRROS ====================
typedef struct Bairro {
    int id;
    char nome[MAX_NOME];
    struct Bairro* prox; //Para tratamento de colisões
} Bairro;

typedef struct {
    Bairro* tabela[TAM_HASH];
} TabelaHashBairros;

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

// ==================== STRUCTS OCORRÊNCIAS ====================
typedef struct Ocorrencia {
    int id;
    int bairro_id;
    TipoServico tipo_servico;
    int gravidade; // 1 para baixa, 2 para média, 3 para alta
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

// ==================== STRUCTS SISTEMA PRINCIPAL ====================
typedef struct {
    TabelaHashBairros* bairros;
    UnidadeServico* unidades;
    Fila* fila_ambulancia;
    Fila* fila_bombeiro;
    Fila* fila_policia;
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
void cadastrar_unidade_sistema(SistemaEmergencia* sistema, int id, TipoServico tipo, const char* identificacao);
void receber_ocorrencia(SistemaEmergencia* sistema, int bairro_id, TipoServico tipo, int gravidade);
void processar_atendimentos(SistemaEmergencia* sistema);
void simular_tempo(SistemaEmergencia* sistema, int unidades_tempo);
void status_sistema(SistemaEmergencia* sistema);
void liberar_sistema(SistemaEmergencia* sistema);

// ==================== FUNÇÕES INTERFACE ====================
void exibir_menu_principal();
void menu_configuracao(SistemaEmergencia* sistema);
void iniciar_simulacao(SistemaEmergencia* sistema);
void verificar_dados(SistemaEmergencia* sistema);

// ==================== FUNÇÕES AUXILIARES INTERFACE ====================
void limpar_buffer();
int ler_inteiro(const char* mensagem);
void ler_string(const char* mensagem, char* destino, int tamanho);
TipoServico escolher_tipo_servico();
void pausar_sistema();

#endif