# 🚨 Simulador de Atendimento Inteligente em Situações de Emergência Urbana

Um sistema de simulação completo para gerenciamento de emergências urbanas, desenvolvido como projeto da disciplina **Estruturas de Dados I - 2025**.

## 📋 Descrição

Este projeto simula um sistema de atendimento de emergência urbana em uma cidade inteligente, onde diferentes serviços (ambulâncias, bombeiros e polícia) respondem a ocorrências em diversos bairros com base em prioridades, gravidade e disponibilidade de recursos.

O sistema foi projetado para demonstrar a aplicação prática de estruturas de dados fundamentais em um contexto realista e socialmente relevante.

## 🎯 Objetivos

- **Aplicação prática** de estruturas de dados em um cenário real
- **Desenvolvimento incremental** com refatoração progressiva
- **Simulação inteligente** de atendimentos de emergência
- **Otimização de respostas** baseada em prioridade e localização

## 🏗️ Arquitetura do Sistema

### Estruturas de Dados Implementadas

| Estrutura | Aplicação no Sistema |
|-----------|---------------------|
| **Tabela Hash** | Acesso rápido a bairros por ID |
| **Filas (FIFO)** | Organização de atendimentos por tipo de serviço |
| **Listas Encadeadas** | Gerenciamento de unidades de serviço |
| **Pilhas** *(em desenvolvimento)* | Histórico individual de atendimentos |
| **Listas Cruzadas** *(em desenvolvimento)* | Associação bairros ↔ serviços |
| **Árvore BST** *(planejado)* | Consultas ordenadas por ID/horário |
| **Árvore AVL** *(planejado)* | Priorização inteligente por gravidade |

## 🚀 Funcionalidades

### ✅ Fase 1 - Simulação Básica (Concluída)
- **Cadastro de Bairros** usando tabela hash para acesso O(1)
- **Gerenciamento de Unidades** (ambulâncias, bombeiros, polícia)
- **Sistema de Filas** separadas por tipo de serviço
- **Simulação Temporal** com controle de disponibilidade
- **Interface Interativa** com menus intuitivos

### 🔄 Fase 2 - Em Desenvolvimento
- Histórico de atendimentos com pilhas
- Sistema de busca rápida expandido
- Representação cidade-serviços com listas cruzadas

### 📋 Fase 3 - Planejado
- Consultas inteligentes com árvores BST
- Priorização automática com árvores AVL balanceadas

## 🛠️ Tecnologias

- **Linguagem:** C (ISO C99)
- **Paradigma:** Programação estruturada
- **Estruturas:** Implementadas do zero, sem bibliotecas externas
- **Gerenciamento:** Controle manual de memória
- **Arquitetura:** Modular (header/implementação/interface)

## 📁 Estrutura do Projeto

📦 emergency-simulator/
├── 📄 main.c           # Interface principal e fluxo do programa
├── 📄 emergencia.h     # Definições de estruturas e protótipos
├── 📄 emergencia.c     # Implementação de todas as funcionalidades
├── 📄 README.md        # Documentação do projeto

## 🎮 Como Usar

### Compilação
```bash
gcc -o simulador main.c emergencia.c -std=c99 -Wall

./simulador