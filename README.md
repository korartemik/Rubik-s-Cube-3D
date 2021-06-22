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

ПКМ случайный поворот граней

# Запуск с помощью Visual Studio
Для запуска потребуется библиотека GLUT(OpenGl)
Скачать библиотеку можно скачать по ссылке http://www.opengl.org/resources/libraries/glut/glutdlls37beta.zip

Далее потребуется переместить файлы glut.lib и glut32.lib в папку Microsoft Visual Studio\2019\Community\VC\Tools\MSVC\14.28.29910\lib\x86

Файл glut.h в папку C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Tools\MSVC\14.28.29910\include

Файлы glut.dll и glut32.dll в папку C:\Windows\SysWOW64

Далее в свойствах проекта выбрать выбрать Конфигурация: Активная(debug),  Платформа: Активная(Win32). И добавить в дополнительные зависимости линки : 
opengl32.lib glut32.lib glu32.lib

# Код

Программа состоит из 3 заголовочных и 2 cpp. В SmallCube.h создаётся структура, отвечающий за кубик размером 1х1х1 из которого потом создаётся кубик 3х3х3 и обладающий свойствами изменения цвета и положения в пространстве. В Cube.h создайтся класс, отвечающий за куб размером 3х3х3, у которого можно поворачивать грани и по параметрам, которого создаётся кубик в окне приложения. В CubeRubic.h создаётся класс, отвечающий за объявление функций программы, такие как сброка, ввод и вывод кубика. В CubeRubic.cpp реализация всех функций. В main.cpp создаётся окно приложения, задаётся цвет граней кубика, его расположение в пространстве, освещение, а также назначаются для кнопок их значение.
# Литература
http://www.opita.net/node/896

http://is.ifmo.ru/download/brick.pdf
