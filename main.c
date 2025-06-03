#include "emergencia.h"

int main() {
    // Aqui inicializamos o sistema, caso não incialize temos um erro crítico
    SistemaEmergencia* sistema = inicializar_sistema();
    if (!sistema) {
        printf("Erro na inicialização do sistema\n");
        return 1;
    }
    
    printf("=== SIMULADOR DE EMERGENCIA URBANA ===\n");
    printf("Sistema inicializado com sucesso!\n");
    
    int opcao;
    do {
        exibir_menu_principal();
        
        //Lê a opção do usuário para utilização do sistema
        //Temos um while que permite realizar várias consultas diferentes enquanto quisermos
        //E um switch com as opções existentes
        while (scanf("%d", &opcao) != 1) {
            printf("Entrada inválida! Digite um número: ");
            limpar_buffer();
        }
        limpar_buffer();
        
        switch(opcao) {
            case 1:
                iniciar_simulacao(sistema);
                break;
                
            case 2:
                verificar_dados(sistema);
                break;
                
            case 3:
                menu_configuracao(sistema);
                break;
                
            case 0:
                printf("\n=== ENCERRANDO O SISTEMA ===\n");
                printf("Liberando memória...\n");
                break;
                
            default:
                printf("\nOpção inválida! Tente novamente.\n");
                pausar_sistema();
        }
        
    } while(opcao != 0);
    
    //Função para liberar toda a memória alocada no sistema
    liberar_sistema(sistema);
    
    printf("\nSistema finalizado com sucesso!\n");
    printf("Obrigado por usar o Simulador de Emergência Urbana!\n");
    
    return 0;
}