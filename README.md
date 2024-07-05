# Computer Graphics Sessional

## Video Tutorial : 
- <a href="https://www.youtube.com/watch?v=btTLvK-zokU">How to install glut 3.7.6 OpenGL and graphics.h Library on Codeblocks 20.03 in Windows</a>

## Instruction for adding graphics and OpenGL file in CodeBlocks
- Install '<a href="https://sourceforge.net/projects/codeblocks/files/Binaries/20.03/Windows/codeblocks-20.03mingw-setup.exe">codeblocks-20.03mingw-setup.exe</a>'

- Replace the files in 'C:\Program Files\CodeBlocks\MinGW' with files from "<a href="https://github.com/mdarikrayhan/Computer-Graphics-Sessional/blob/main/Graphics_h_and_OpenGL/MinGW.zip">MinGW.zip</a>"

- add the flowing path in Environment Variables
```
C:\Program Files\CodeBlocks\MinGW\bin
```

- Copy the "<a href="https://github.com/mdarikrayhan/Computer-Graphics-Sessional/blob/main/Graphics_h_and_OpenGL/glut32.dll">glut32.dll</a>" to the flowing path
```
C:\Windows\System
```

- Open CodeBlocks and go to (Settings > Compiler > Linker Settings)

- Link Libraries (left), Click on "Add" button, then click "Browse" and select the "libbbgi.a" and then click "Open" . File path
```
C:\Program Files\CodeBlocks\MinGW\lib\libbgi.a
```

- Other linker option (right), copy the text below and paste there
```
-lbgi -lgdi32 -lcomdlg32 -luuid -loleaut32 -lole32
```

- Click "OK"


## NOTE:
- The graphics.h will work only in the program saved in ".cpp" format.

- To check the graphics.h is working or not Create a new consol application in ".cpp" format and copy the codes given below, paste it in the file you created and click "Build and Run" button or click "F9" key from your keyboard.

```
#include<graphics.h>
int main()
{
    int gd=DETECT,gm;
    initgraph(&gd,&gm,"");
    circle(200,200,100);
    getch();
}
```

- If you see a circle in a new window then the graphics.h is working properly.

- To check the OpenGL is working or not Create a new GLUT project and give the project name "OpenGl" and click "Next" button

- It will show you to select GLUT library, select the below path and click "Next" button
```
C:\Program Files\CodeBlocks\MinGW
```

- Click next and then finish

- You will get a main.cpp file, on that file on line no 14 you need to add the below code
```
#include <windows.h>
```

- Now press "F9" key from your keyboard or click "Build and Run" button
