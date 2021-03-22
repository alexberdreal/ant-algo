# Муравьиный алгоритм :ant:

Инструкция по конфигурации проекта (Visual Studio):
1. Перейти в "Проект -> Свойства -> С/С++ -> Общие" и в "Дополнительные каталоги включаемых файлов" добавить "Полный путь до папки с проектом\sfml\include"
2. Перейти в "Проект -> Свойства -> Компоновщик -> Общие" и в "Дополнительные каталоги библиотек" добавить "Полный путь до папки с проектом\sfml\lib"
3. Перейти в "Проект -> Свойства -> С/С++ -> Ввод" и в "Дополнительные зависимости" добавить следующее (название каждой библиотеки с новой строки):
sfml-graphics-d.lib
sfml-window-d.lib
sfml-system-d.lib
4. Запустить программу ctrl + f5 - для создания папки Debug и exe-файла в ней
5. Перенести файлы из папки "sfml/tomove" в папку "Debug"
6. Раскомментировать весь код в Visualization.cpp
7. Готово!

* В Visualization.cpp в функцию drawWindow() добавлен тестовый код, который должен сработать при вызове в Source.cpp, если все подключено успешно *
