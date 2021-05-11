mkdir Debug
ECHO Докачиваю SFML библиотеку...
cd sfml/tomove
ECHO Перенос openal32.dll
move openal32.dll ../../Debug
ECHO Перенос sfml-graphics-2.dll
move sfml-graphics-2.dll ../../Debug
ECHO Перенос sfml-graphics-d-2.dll
move sfml-graphics-d-2.dll ../../Debug
ECHO Перенос sfml-system-2.dll
move sfml-system-2.dll ../../Debug
ECHO Перенос sfml-system-d-2.dll
move sfml-system-d-2.dll ../../Debug
ECHO Перенос sfml-window-2.dll
move sfml-window-2.dll ../../Debug
ECHO Перенос sfml-window-d-2.dll
move sfml-window-d-2.dll ../../Debug
cd ..
rmdir tomove
ECHO Готово!