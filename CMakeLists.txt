# Defina a versão mínima do CMake necessária
cmake_minimum_required(VERSION 3.18)

# Nome do projeto e linguagem
project(Snake LANGUAGES CXX)

# Define o padrão do C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Adicionar os arquivos-fonte ao executável
add_executable(${PROJECT_NAME}
    main.cpp
    Cobrinha.cpp
    No.cpp
)

# Incluir diretórios de cabeçalhos
target_include_directories(${PROJECT_NAME} PRIVATE .)
