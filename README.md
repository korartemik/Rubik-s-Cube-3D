# Rubik-s-Cube-3D
Программа по визуализации и сборки кубика рубик. Rubik's cube visualization and assembly program.
# Управление:
Стрелочки "вверх", "вниз", "влево", "вправо" управление камерой

цифры "1-6" поворот грани

"l" изменение направления вращения (по часовой или против часовой)

"s" сохранение положения кубика рубика в файл

"d" вывод положение кубика рубика в консоль

"f" ввод новой расскраски из файла

"g" ввод новой расскраски из коносли

"q" запуск сборки кубика рубика

"t" проверка корректности окраск

"HOME" приближение камеры

"END" отдаление камеры

# Запуск с помощью Visual Studio
Для запуска потребуется библиотека GLUT(OpenGl)
Скачать библиотеку можно скачать по ссылке http://www.opengl.org/resources/libraries/glut/glutdlls37beta.zip

Далее потребуется переместить файлы glut.lib и glut32.lib в папку Microsoft Visual Studio\2019\Community\VC\Tools\MSVC\14.28.29910\lib\x86

Файл glut.h в папку C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Tools\MSVC\14.28.29910\include

Файлы glut.dll и glut32.dll в папку C:\Windows\SysWOW64

Далее в свойствах проекта выбрать выбрать Конфигурация: Активная(debug),  Платформа: Активная(Win32). И добавить в дополнительные зависимости линки : 
opengl32.lib glut32.lib glu32.lib
