Scarlet Shadow

![C++](https://img.shields.io/badge/C%2B%2B-20-00599C?style=flat-square&logo=cplusplus)
![SDL](https://img.shields.io/badge/SDL-3-173B5F?style=flat-square)
![CMake](https://img.shields.io/badge/CMake-3.20%2B-064F8C?style=flat-square&logo=cmake)
![Status](https://img.shields.io/badge/status-em%20desenvolvimento-C1121F?style=flat-square)

**Scarlet Shadow** (*Sombra Escarlate*) é um jogo de plataforma 2D em desenvolvimento, criado em C++ com SDL3.

Além de construir as mecânicas do jogo, o principal objetivo deste projeto é aprender a estruturar uma aplicação de maior porte e organizar seu crescimento de forma modular e sustentável. Cada novo sistema é uma oportunidade de praticar separação de responsabilidades, gerenciamento de estados, arquitetura de software e manutenção de código.

> O projeto está em fase de protótipo. Sistemas, interfaces e elementos visuais ainda poderão mudar durante o desenvolvimento.

## Funcionalidades atuais

- Menu principal animado, com navegação por teclado;
- Gerenciamento dos estados de menu e partida;
- Movimento horizontal, gravidade e salto;
- Colisão horizontal e vertical com blocos sólidos;
- Plataformas atravessáveis por baixo;
- Obstáculos que devolvem o jogador ao ponto inicial;
- Reinício após queda para fora do mapa;
- Carregamento de fases a partir de arquivos externos;
- Câmera que acompanha o jogador e respeita os limites da fase;
- Loop principal baseado em `deltaTime`;
- Estrutura modular para entidades, física, mundo, renderização e núcleo do jogo.

Atualmente, parte da renderização utiliza formas geométricas provisórias. A prioridade desta etapa é consolidar os sistemas e a arquitetura antes da evolução visual do jogo.

## Controles

### Menu

| Ação | Teclas |
|---|---|
| Mover a seleção | `W`, `S` ou setas direcionais |
| Confirmar | `Espaço` ou `Enter` |
| Sair | `Esc` |

### Partida

| Ação | Teclas |
|---|---|
| Mover para a esquerda | `A` |
| Mover para a direita | `D` |
| Pular | `Espaço` |

## Tecnologias

- **C++20** — linguagem principal;
- **SDL3** — janela, eventos, entrada e renderização;
- **SDL3_image** — carregamento de texturas e imagens;
- **SDL3_ttf** — renderização de fontes e textos;
- **SDL3_mixer** — dependência preparada para o sistema de áudio;
- **CMake** — configuração da compilação e gerenciamento do projeto;
- **Git Submodules** — integração das bibliotecas SDL ao repositório.

## Estrutura do projeto

```text
ScarletShadow/
├── assets/
│   ├── fonts/          # Fontes utilizadas pela interface
│   ├── maps/           # Arquivos que descrevem as fases
│   └── sprites/        # Imagens e animações
├── src/
│   ├── core/           # Loop principal, estados e menu
│   ├── entities/       # Jogador e plataformas
│   ├── physics/        # Detecção e resolução de colisões
│   ├── render/         # Câmera e apoio à renderização
│   ├── world/          # Fases e tiles
│   └── main.cpp        # Ponto de entrada
├── vendor/             # SDL e extensões adicionadas como submódulos
└── CMakeLists.txt      # Configuração de compilação
```

Essa divisão busca impedir que o crescimento do jogo concentre regras diferentes em uma única classe. A intenção é evoluir cada sistema de forma independente e manter claras as responsabilidades dos componentes.

## Sistema de fases

As fases são descritas por arquivos de texto dentro de `assets/maps`. Cada caractere representa um elemento do mundo:

| Símbolo | Elemento |
|:---:|---|
| `.` | Espaço vazio |
| `#` | Bloco sólido |
| `^` | Obstáculo perigoso |
| `S` | Ponto inicial do jogador |
| `=` | Plataforma atravessável por baixo |

Esse formato permite modificar ou criar mapas sem recompilar o código-fonte.

## Como compilar

### Requisitos

- Git;
- CMake 3.20 ou superior;
- Compilador com suporte a C++20;
- Dependências de desenvolvimento exigidas pela SDL na plataforma utilizada.

### 1. Clonar o repositório e seus submódulos

```bash
git clone --recurse-submodules https://github.com/pedrolima2806/ScarletShadow.git
cd ScarletShadow
```

Caso o repositório já tenha sido clonado sem os submódulos:

```bash
git submodule update --init --recursive
```

### 2. Configurar e compilar

```bash
cmake -S . -B build
cmake --build build --parallel
```

### 3. Executar

No Linux, execute a partir da pasta de compilação para que os caminhos dos recursos sejam encontrados corretamente:

```bash
cd build
./SombraEscarlate
```

## Roadmap

As funcionalidades abaixo estão planejadas e **ainda não devem ser consideradas implementadas**.

### Progressão e navegação

- [ ] Save points;
- [ ] Fim de fase;
- [ ] Tela de seleção de fase;
- [ ] Tela de seleção de área.

### Movimento do jogador

- [ ] Inércia;
- [ ] Pulo aprimorado;
- [ ] Dash.

### Combate

- [ ] Inimigos;
- [ ] Sistema de vida;
- [ ] Sistema universal de disparos e morte por disparo;
- [ ] Espada do jogador;
- [ ] Morte por espada;
- [ ] Reflexão de disparos com a espada;
- [ ] Sistema de disparo do jogador aprimorado;
- [ ] Múltiplas armas;
- [ ] Habilidade ultimate;
- [ ] Spawn de armas.

### Inteligência e sistemas do jogo

- [ ] Inteligência artificial dos inimigos aprimorada;
- [ ] Câmera aprimorada;
- [ ] Sistema de pontuação;
- [ ] Multiplayer.

## Princípios de desenvolvimento

Durante a evolução do Scarlet Shadow, o projeto busca priorizar:

- Responsabilidades bem definidas entre classes e sistemas;
- Inclusão gradual de novas mecânicas;
- Código legível e de fácil manutenção;
- Baixo acoplamento entre componentes;
- Possibilidade de expansão sem reescrever toda a base;
- Aprendizado contínuo por meio de decisões reais de arquitetura.

## Autor

Desenvolvido por [Pedro Lima](https://github.com/pedrolima2806).
