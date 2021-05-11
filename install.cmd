mkdir Debug
ECHO Докачиваю SFML библиотеку...
curl https://www.sfml-dev.org/files/SFML-2.5.1-windows-vc15-32-bit.zip -o tomove.zip
tar -xf tomove.zip
del tomove.zip
cd SFML-2.5.1/bin
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
cd ../..
ren SFML-2.5.1 sfml-res
ECHO Готово!