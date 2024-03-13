Технологии программирования, Ким Б05-327, весна 2024

Как запустить проект, находясь в его корневой директории:
cd ..
mkdir -p build
cd build
cmake -DCMAKE_BUILD_TYPE=Release /path/to/project/directory
cmake --build .

Исполняемый файл будет лежать в директории bin проекта

[Class diagram](./class_uml.jpg?raw=true)

[Use case diagram](./use_case_uml.jpg?raw=true)
