#include "stdafx.h"
#include "StringTokenizer.h"

int main()
{
	StringTokenizer a("Delimiter betyder skilletegn. I en tekststreng adskilles de indg�ende tokens af delimiters, som har l�ngden �n karakter. Der kan godt komme flere delimiters umiddelbart efter hinanden.");
	a.printContents();
	cout << endl;
	a.trim();
	a.printContents();
	system("Pause");
    return 0;
}

