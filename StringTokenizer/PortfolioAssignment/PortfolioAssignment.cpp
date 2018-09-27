#include "stdafx.h"
#include "StringTokenizer.h"

int main()
{
	StringTokenizer a("Delimiter betyder skilletegn. I en tekststreng adskilles de indgående tokens af delimiters, som har længden én karakter. Der kan godt komme flere delimiters umiddelbart efter hinanden.");
	a.printContents();
	cout << endl;
	a.trim();
	a.printContents();
	system("Pause");
    return 0;
}

