CFLAGS=/nologo /W4 /EHsc /Za

build: list.obj main.obj hash.obj hashset.obj
	cl $(CFLAGS) list.obj main.obj hash.obj hashset.obj /o tema1.exe

list.obj: list.c
	cl /c list.c
main.obj: main.c
	cl /c main.c
hash.obj: hash.c
	cl /c hash.c
hashset.obj: hashset.c
	cl /c hashset.c
	
clean:
	del /Q /F *.obj tema1.exe
