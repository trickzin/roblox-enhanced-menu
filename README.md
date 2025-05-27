#  Roblox Enhanced Menu

Um menu completo de mod/cheat para Roblox desenvolvido com ImGui, oferecendo funcionalidades avançadas de ESP, movimento, combate e otimização de performance.

###  ESP (Visão Melhorada)
- **Player ESP**: Contornos e informações dos jogadores
- **Item ESP**: Destaque de itens importantes
- **Distance ESP**: Mostrar distância para jogadores/itens

###  Movimento
- **Speed Boost**: Aumentar velocidade de movimento
- **Jump Boost**: Pulos mais altos
- **No Clip**: Atravessar paredes
- **Fly Mode**: Capacidade de voar

###  Combate
- **Aimbot**: Assistência automática de mira
- **Auto Attack**: Ataque automático
- **Damage Boost**: Aumentar dano causado

### Utilidades
- **Auto Farm**: Coleta automática de recursos
- **Teleport**: Mudança instantânea de localização
- **God Mode**: Modo de invencibilidade

### Performance
- **Monitor de FPS**: Acompanhamento em tempo real
- **Otimização de Gráficos**: Melhorar performance
- **Limpeza de Memória**: Liberar recursos não utilizados

### Personalização
- **6 Temas**: Dark Blue, Green Matrix, Purple Cosmic, Orange Fire, Ice Blue, RGB Rainbow
- **Modo RGB**: Animação de cores automática
- **Interface Responsiva**: Compatível com mobile e PC

## Como Compilar

### Dependências
- CMake 3.16+
- C++17 compiler
- OpenGL
- GLFW3
- ImGui (incluído automaticamente)

### Build
```bash
git clone https://github.com/trickzqw/roblox-enhanced-menu
cd roblox-enhanced-menu
mkdir build
cd build
cmake ..
make
./RobloxEnhancedMenu
```

##  Uso no Roblox Mobile (Delta APK)

### Conversão para Lua
O projeto inclui conversores para transformar o menu C++ em scripts Lua compatíveis com executors de Roblox:

```lua
-- Exemplo de conversão automática
local Menu = loadstring(game:HttpGet("https://raw.githubusercontent.com/trickzqw/roblox-enhanced-menu/main/lua/menu.lua"))()
Menu:Initialize()
```

### Compatibilidade
-  Delta Executor
-  Synapse X Mobile
-  KRNL
-  Script-Ware Mobile

## Estrutura do Projeto

```
roblox-enhanced-menu/
├── src/                    # Código fonte C++
│   ├── main.cpp
│   ├── menu.cpp
│   ├── performance_monitor.cpp
│   ├── optimization.cpp
│   └── themes.cpp
├── lua/                    # Scripts Lua convertidos
│   ├── menu.lua
│   ├── esp.lua
│   ├── movement.lua
│   └── combat.lua
├── docs/                   # Documentação
├── examples/              # Exemplos de uso
└── CMakeLists.txt         # Build configuration
```

## Configuração para Executors

### Delta APK
1. Baixe o script Lua do repositório
2. Injete usando o executor do Delta
3. Configure as funcionalidades no menu

### Outros Executors
- Suporte universal para executors que suportam GUI
- Interface adaptável para diferentes resoluções
- Sistema de salvamento de configurações

## </> Desenvolvedor

**Criado por**: trickzqw  
**Email**: sintofaltadela@gmail.com  
**Website**: https://trickzin.github.io/trick-little-man/

##  Licença

MIT License - veja [LICENSE](LICENSE) para detalhes.