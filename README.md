# CSE-4206-Computer-Graphics-Sessional

## Instruction for adding graphics file in Code::Blocks
- Install '<a href="https://sourceforge.net/projects/codeblocks/files/Binaries/20.03/Windows/codeblocks-20.03mingw-setup.exe">codeblocks-20.03mingw-setup.exe</a>'

- Replace the files in 'C:\Program Files\CodeBlocks\MinGW' with files from "MinGW.zip"

- Copy the "glut32.dll" to 'C:\Windows\System'

- Open CodeBlocks and go to (Settings > Compiler > Linker Settings)

- Link Libraries (left), Click on "Add" button, then click "Browse" and select the "libbbgi.a"
   file that you have copied in CodeBlocks directory..
   Default location is (C:\Program Files\CodeBlocks\MinGW\lib\libbgi.a)
   and then click "Open" button.

- Other linker option (right), copy the text below and paste there
   -lbgi -lgdi32 -lcomdlg32 -luuid -loleaut32 -lole32

```
-lbgi -lgdi32 -lcomdlg32 -luuid -loleaut32 -lole32
```


7) Click "OK"


Done...

NOTE:
1) The graphics.h will work only in the program saved in ".cpp" format.

To check the graphics.h is working or not
*****************************************************************************************************
Create a new consol application in ".cpp" format and copy the codes given below, paste it in the
file you created and click "Build and Run" button or click "F9" key from your keyboard..

#include<graphics.h>
int main()
{
    int gd=DETECT,gm;
    initgraph(&gd,&gm,"");
    circle(200,200,100);
    getch();
}