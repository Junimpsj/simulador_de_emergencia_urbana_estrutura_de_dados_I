# 🚨 Simulador de Atendimento Inteligente em Situações de Emergência Urbana

Um sistema de simulação completo para gerenciamento de emergências urbanas, desenvolvido como projeto da disciplina **Estruturas de Dados I - 2025**.

## 📋 Descrição

Este projeto simula um sistema de atendimento de emergência urbana em uma cidade inteligente, onde diferentes serviços (ambulâncias, bombeiros e polícia) respondem a ocorrências em diversos bairros com base em prioridades, gravidade e disponibilidade de recursos.

O sistema foi projetado para demonstrar a aplicação prática de estruturas de dados fundamentais em um contexto realista e socialmente relevante, implementando **7 estruturas de dados diferentes** em um sistema coeso e funcional.

## 🎯 Objetivos Alcançados

- ✅ **Aplicação prática** de estruturas de dados em um cenário real
- ✅ **Desenvolvimento incremental** com 3 fases progressivas
- ✅ **Simulação inteligente** de atendimentos de emergência
- ✅ **Otimização de respostas** baseada em prioridade e localização
- ✅ **Consultas avançadas** com árvores balanceadas
- ✅ **Interface completa** com 5 menus especializados

## 🏗️ Arquitetura do Sistema

### Estruturas de Dados Implementadas

| Estrutura | Status | Aplicação no Sistema | Complexidade |
|-----------|--------|---------------------|--------------|
| **Tabela Hash** | ✅ **Concluída** | Acesso rápido a bairros por ID e cidadãos por CPF | O(1) |
| **Filas (FIFO)** | ✅ **Concluída** | Organização de atendimentos por tipo de serviço | O(1) |
| **Listas Encadeadas** | ✅ **Concluída** | Gerenciamento de unidades de serviço | O(n) |
| **Pilhas (LIFO)** | ✅ **Fase 2** | Histórico individual de atendimentos | O(1) |
| **Listas Cruzadas** | ✅ **Fase 2** | Associação bairros ↔ serviços disponíveis | O(n×m) |
| **Árvore BST** | ✅ **Fase 3** | Consultas ordenadas por ID de ocorrência | O(log n) |
| **Árvore AVL** | ✅ **Fase 3** | Priorização automática por gravidade | O(log n) |

## 🚀 Funcionalidades Implementadas

### ✅ Fase 1 - Simulação Básica (Concluída)
- **Cadastro de Bairros** usando tabela hash para acesso O(1)
- **Gerenciamento de Unidades** (ambulâncias, bombeiros, polícia)
- **Sistema de Filas** separadas por tipo de serviço
- **Simulação Temporal** com controle de disponibilidade
- **Interface Interativa** com menus intuitivos

### ✅ Fase 2 - Histórico e Busca Rápida (Concluída)
- **Histórico de Atendimentos** com pilhas (último atendimento no topo)
- **Sistema de Busca Rápida** de cidadãos por CPF usando hashing
- **Mapa da Cidade** com listas cruzadas conectando bairros e serviços
- **Cadastro de Cidadãos** com informações completas
- **Consultas Avançadas** e estatísticas em tempo real
- **Interface Expandida** com menu de consultas e históricos

### ✅ Fase 3 - Busca e Priorização Inteligente (Concluída)
- **Consultas inteligentes** com árvores BST para busca por ID
- **Priorização automática** com árvores AVL balanceadas por gravidade
- **Menu especializado** para demonstração das árvores
- **Testes de performance** comparando algoritmos
- **Demonstração de balanceamento** automático da AVL
- **Simulação completa** com todas as funcionalidades integradas

## 🛠️ Tecnologias

- **Linguagem:** C (ISO C99)
- **Paradigma:** Programação estruturada
- **Estruturas:** Implementadas do zero, sem bibliotecas externas
- **Gerenciamento:** Controle manual de memória com liberação completa
- **Arquitetura:** Modular (header/implementação/interface)
- **Bibliotecas:** `stdio.h`, `stdlib.h`, `string.h`, `math.h`

## 📁 Estrutura do Projeto
```
📦 emergency-simulator/
├── 📄 main.c           # Interface principal e fluxo do programa (100 linhas)
├── 📄 emergencia.h     # Definições de estruturas e protótipos (180 linhas)
├── 📄 emergencia.c     # Implementação completa (1400+ linhas)
├── 📄 README.md        # Documentação atualizada do projeto
└── 📊 Estatísticas     # Total: ~1700 linhas de código
```

## 🎮 Como Usar

### Compilação
```bash
gcc -o simulador main.c emergencia.c -std=c99 -Wall -lm
./simulador
```
> **Nota:** O `-lm` é necessário para linkar a biblioteca matemática (função `log2`)

### 📋 Menus Disponíveis

1. **🚀 Iniciar Simulação** - Executa simulação automática completa com 5 fases
2. **🔍 Verificar Dados** - Visualiza estado atual do sistema e estruturas
3. **⚙️ Configurar Sistema** - Cadastra bairros, cidadãos e unidades
4. **📊 Consultas e Históricos** - Busca por CPF, históricos e estatísticas
5. **🌳 Consultas com Árvores** - Menu especializado para demonstração das árvores

### 🎯 Fluxo de Uso Recomendado

1. **Primeira execução**: Escolha opção 1 (Simulação Completa)
2. **Exploração**: Use opção 5 para testar as árvores BST e AVL
3. **Configuração**: Opção 3 para adicionar seus próprios dados
4. **Análise**: Opção 2 para verificar o estado do sistema

## 📈 Progresso do Desenvolvimento

### ✅ Todas as Fases Concluídas

| Fase | Prazo | Status | Estruturas Implementadas | Linhas de Código |
|------|-------|--------|-------------------------|------------------|
| **Fase 1** | 02/06/2025 | ✅ **Concluída** | Hash Tables, Filas, Listas | ~600 linhas |
| **Fase 2** | 16/06/2025 | ✅ **Concluída** | Pilhas, Listas Cruzadas | +400 linhas |
| **Fase 3** | 23/06/2025 | ✅ **Concluída** | Árvore BST, Árvore AVL | +700 linhas |

## 🔬 Demonstração das Estruturas

### 📊 **Tabelas Hash (Fase 1)**
```
Bairros: ID → hash(ID) % 101 → O(1) → {id, nome}
Cidadãos: CPF → hash(CPF) % 101 → O(1) → {cpf, nome, email, endereço, bairro}
```

### 📋 **Pilhas de Histórico (Fase 2)**
```
Ambulâncias: [Último] → [Penúltimo] → [Anterior] → ...
Bombeiros:   [Último] → [Penúltimo] → [Anterior] → ...
Polícia:     [Último] → [Penúltimo] → [Anterior] → ...
```

### 🗺️ **Listas Cruzadas (Fase 2)**
```
Bairro Centro → [Ambulância: 2] → [Bombeiro: 1] → [Polícia: 2]
Bairro Jardim → [Ambulância: 1] → [Bombeiro: 2] → [Polícia: 1]
```

### 🌳 **Árvore BST (Fase 3) - Busca por ID**
```
        [ID: 4]
       /       \
   [ID: 2]   [ID: 6]
   /    \     /    \
[ID: 1][ID: 3][ID: 5][ID: 7]
```

### 🌲 **Árvore AVL (Fase 3) - Priorização por Gravidade**
```
      [Grav: 2, FB: 0]
     /               \
[Grav: 3, FB: 0] [Grav: 1, FB: 0]
```
> **FB = Fator de Balanceamento** (sempre entre -1, 0, 1)

## 🎪 Simulação Completa - 5 Fases

A simulação automática (Menu 1) demonstra todo o sistema:

1. **📋 Configuração Inicial**: Cadastra 5 bairros, 4 cidadãos e 6 unidades
2. **🚨 Ocorrências de Emergência**: Gera 8 ocorrências com prioridades variadas
3. **⚡ Processamento Inteligente**: Simula 5 unidades de tempo com atendimentos
4. **🌳 Demonstração das Árvores**: Mostra BST e AVL em funcionamento
5. **📈 Relatórios Finais**: Estatísticas completas e mapa da cidade

---

## 🏆 Conclusão

Este projeto representa uma implementação completa e funcional de um sistema de emergência urbana, demonstrando com excelência a aplicação prática de estruturas de dados fundamentais. 

**Desenvolvido como projeto acadêmico para Estruturas de Dados I - 2025**  
*Demonstrando excelência técnica na aplicação de conceitos fundamentais em contexto socialmente relevante*

---

**Status do Projeto**: ✅ **COMPLETO E FUNCIONAL** ✅