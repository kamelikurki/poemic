Poemic - revealing the music hidden in letters

This is a software to transfer a .txt file to a melody. The source material can be a poem, lyrics of a song, a recipe or anything you can think of. The result depends on the content of the file so it's also possible to make your own .txt file thats sole purpose is to make the software to play a melody that's as nice as possible. 

You need to have portaudio installed in your computer before you can run the program. Download it from: http://www.portaudio.com . The project contains executable file called poem which contains a compiled program that can be run on OSX. If you want to compile the code yourselves you have to include the portaudio library. For example with gcc compiling is done with following command: gcc -o programname poemic.c oscillator.c sine.c audiostream.c -lportaudio -I.

Program takes one command line parameter which is the name of the .txt file that contains the source material. For example if your source material is in a file called mypoem.txt and the executable file is called poem the program is run with following command: .\poem mypoem.txt

This is the first version of the program that includes only very basic functionalities. Future enhancements will include alternative instruments and reading the distribution of note lengths from the source file.

-Ville Saari
