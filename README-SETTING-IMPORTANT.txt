To install properly:
Make sure you have VS 2019 or VS 2017?

Rename the "samprak-hook-base.sln" to what the project name will be e.g:
my-samp-hack.sln

and then open it with any text editor, I used notepad++.

Edit wherever you see samprak-hook-base to your project name, and rename folders aswell.
So samprak-hook-base folder will become my-samp-hack.
Set the values for the project files and folders correctly in the .sln file.
e.g.:  (DONT COPY THIS, THIS IS EXAMPLE)
Project("x") = "my-samp-hack", "my-samp-hack\my-samp-hack.vcxproj", "x"

Make sure folder is renamed, then go in folder and rename samprak-hook-base project
filters files etc like .vcxproj and rename every samprak-hook-base to my-samp-hack
and make sure you rename the file names in the end to match aswell.
Lastly open the .sln and boom.

When you open the project, set the settings:
Conformance mode off, if you have it as permissive it will give errors.
Make sure toolset is fine and windows SDK version is available and set properly
(e.g. using windows 7 sdk on a windows 10 toolset aka 141 instead of 141_xp)


MAKE SURE YOU ARE NOT BUILDING ON X64 MODE E.G. BUILD ON RELEASE X86 OR DEBUG X86.
X64 IS NOT SUPPORTED