cmake_minimum_required(VERSION 3.12)
project(GraphEditor)

# Устанавливаем стандарт C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_BUILD_TYPE Debug)

# Включаем текущую директорию для поиска заголовочных файлов
set(CMAKE_INCLUDE_CURRENT_DIR ON)



# Указываем путь для поиска Qt6
set(CMAKE_PREFIX_PATH "/opt/homebrew/Cellar/qt/6.7.3/lib/cmake")

# Ищем Qt6 с компонентом Widgets
find_package(Qt6 REQUIRED COMPONENTS Widgets)

# Включаем автоматическую обработку moc для файлов, содержащих Q_OBJECT
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Добавляем исходные файлы проекта
set(SOURCES
    main.cpp
    HelpfulFunc.cpp
)

# Добавляем заголовочные файлы
set(HEADERS
    Graph.hpp
    GraphParts.hpp
    DynamicArray.hpp
    GraphScene.hpp
    MainWindow.hpp
    HelpfulFunc.hpp
)

# Добавляем исполняемый файл
add_executable(GraphEditor ${SOURCES} ${HEADERS})

# Линкуем с библиотеками Qt6
target_link_libraries(GraphEditor Qt6::Widgets)

# Устанавливаем поддержку C++17 для проекта
target_compile_features(GraphEditor PUBLIC cxx_std_17)


