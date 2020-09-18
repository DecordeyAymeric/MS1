
#pragma hdrstop
#pragma argsused

#ifdef _WIN32
#include <tchar.h>
#else
typedef char _TCHAR;
#define _tmain main
#endif
#include <math.h>
#include <iostream>
using namespace std;
#include <stdio.h>
#include <sstream>
#include <time.h>
#include <fstream>
#include "SNAfficheur.h"
#include "SNLigne.h"
#include "PortSerieAfficheur.h"
int SaisirBinaire()
{
		char bin[100];
		int nb=0;
		cin>>bin;
		for (int i=0;i<strlen(bin); i++)
		{
			nb=nb*2+(bin[i]-'0');
		}
		return nb;
}
string EntierVersChaineEnBinaire(int nb)
{
		ostringstream oss;
		bool copie=false;
		for(int i=31;i>=0;i--)
		{
			if (((nb>>i)&1)==1)
			{
				copie=true;
			}
			if (copie==true)
			{
				oss<<((nb>>i)&1);

			}
		}
		return oss.str();
}

int _tmain(int argc, _TCHAR* argv[])
{

		SNAfficheur aff;
		char phrase[500];
		int choix;
		float val1, val2;
		float k;
		char operateur;
		float resultat;
		char fonction[10];
		char unite;
		int nb;
		int base;

    char buffer[256];
    time_t timestamp = time(NULL);

	strftime(buffer, sizeof(buffer), "%A %d %B %Y - %X.", localtime(&timestamp));
	cout << buffer <<endl;
//    printf("%s\n", buffer);


	cout<<"Calcul(1),Trigo(2),Conversion(3):";
	cin>>choix;
	cin.get();

if (choix==1)
{
	cout<<"Saisir Calcul :" ;
	cin >> val1 >> operateur >> val2 ;
	cin.get();
			if (operateur=='+')
			{
				resultat=val1+val2;
			}
			else if (operateur=='-')
			{
				resultat=val1-val2;
			}
			else if (operateur=='*')
			{
				resultat=val1*val2;
			}
			else if (operateur=='/')
			{
				resultat=val1/val2;
			}

	sprintf(phrase,"%.3f %c %.3f = %.3f", val1, operateur, val2, resultat);
	cout<<phrase ;



	cin.get();cin.get();cin.get();cin.get();
}
else if (choix==2)
{
	cout<<"Resultat en radian(1) ou en degre(2)?" ;
	cin>>unite;
		if (unite=='1')
		{
			k=1 ;
		}

		else if (unite=='2')
		{
			k=3.14/180 ;
		}

	cout<<"Saisir Calcul Trigo :";
	cin>>fonction>>val1 ;
	val1=val1*k;
	cin.get();
		 if (strcmp(fonction,"cos")=='0')
		  {
			resultat=cos(val1);
		  }
		 else if (strcmp(fonction,"sin")=='0')
		  {
			resultat=sin(val1);
		  }
		 else if (strcmp(fonction,"tan")=='0')
		  {
			resultat=tan(val1);
		  }

	sprintf(phrase,"%s(%.3f) = %.3f", fonction, val1, resultat);
	cout<<phrase ;
	cin.get();cin.get();cin.get();cin.get();
}
else if (choix==3)
{
	cout<<"Choix de la base de saisie : Decimal(1), Hexa(2), Binaire(3):" ;
	cin>>base;
		if (base==1)
		{
			cout<<"Saisir un  nombre decimal :" ;
			cin>>dec>>nb ;
		}
		else if (base==2)
		{
			cout<<"Saisir un nombre hexadecimal :";
			cin>>hex>>nb ;
		}
		else if (base==3)
		{
			cout<<"Saisir un nombre binaire :";
			nb=SaisirBinaire() ;
		}

	cout<<"Choix de la base d'affichage : Decimal(1), Hexa(2), Binaire(3) :" ;
	cin>>base;
		if (base==1)
		{
			cout<<"Resultat en dec : "<<dec<<nb<<endl;
		}
		else if (base==2)
		{
			cout<<"Resultat en hexa: "<<hex<<nb<<endl;
		}
		else if (base==3)
		{
			cout<<"Resultat en binaire:"<<EntierVersChaineEnBinaire(nb)<<endl ;
		}
 }
	ofstream fichier;
	fichier.open("calculatrice.log");
	fichier << "Historique de calcul :" <<endl;
	fichier << buffer << endl;
	fichier << "" << endl;
	fichier << phrase << endl;
	fichier.close();

    aff.ModifierAdresseIPDuServeurUDP("172.20.182.57");
	aff.ModifierPortDuServeurUDP(4321);
	SNLigne lg;
	lg.ModifierMessage(phrase);
	aff.EnvoyerLigneEnUDP(lg);


//	sprintf(phase,"%d = %d", nb, nb);
//	cout<<phase ;

	cin.get();cin.get();cin.get();cin.get();

return 0;
}
