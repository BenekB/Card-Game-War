/*  author: Benedykt Bela
 *  author: Justyna Jeliñska
 *  Code Blocks 17.12
 */


#include <iostream>
#include <time.h>
#include <vector>
#include <queue>
#include <cstdlib>
#include <string>
#include <iomanip>

using namespace std;


struct karta
{
    string znak;
    int wartosc;
    string kolor;
};


struct obszar_gry
{
    queue <karta> gracz_1;
    queue <karta> gracz_2;
    queue <karta> stos;
};


obszar_gry stolik;

void tasuj_talie ();
void wojna ();


int main()
{
    tasuj_talie();                  //  tworzenie tali kart, tasowanie oraz rozdzielanie miêdzy dwóch graczy
    wojna();                        //  wlasciwa czesc rozgrywki

    system("PAUSE");

    return 0;
}



void tasuj_talie ()
{
    karta *talia = new karta[52];                       //  tworze talie kart

    for (int j = 0; j < 4; j++)                         //  definiuje talie kart - nadaje im wartosci, znaki i kolory
        for (int i = 0; i < 13; i++)
        {
            talia[i + 13*j].wartosc = i;

            switch ((i + 13*j)%13 + 1)
            {
                case 1: talia[i + 13*j].znak = '2'; break;
                case 2: talia[i + 13*j].znak = '3'; break;
                case 3: talia[i + 13*j].znak = '4'; break;
                case 4: talia[i + 13*j].znak = '5'; break;
                case 5: talia[i + 13*j].znak = '6'; break;
                case 6: talia[i + 13*j].znak = '7'; break;
                case 7: talia[i + 13*j].znak = '8'; break;
                case 8: talia[i + 13*j].znak = '9'; break;
                case 9: talia[i + 13*j].znak = "10"; break;
                case 10: talia[i + 13*j].znak = 'J'; break;
                case 11: talia[i + 13*j].znak = 'D'; break;
                case 12: talia[i + 13*j].znak = 'K'; break;
                case 13: talia[i + 13*j].znak = 'A'; break;
            }

            switch (j)
            {
                case 0: talia[i + 13*j].kolor = "KIER"; break;
                case 1: talia[i + 13*j].kolor = "KARO"; break;
                case 2: talia[i + 13*j].kolor = "PIK"; break;
                case 3: talia[i + 13*j].kolor = "TREFL"; break;
            }
        }


    vector <karta> potasowane;                          //  miejsce na potasowan¹ talie kart
    potasowane.push_back(talia[0]);

    srand( time( NULL ) );

    int gdzie;

    for( int i = 0; i < 52; i++)                    //  tasowanie tali kart
    {
        gdzie = rand() % potasowane.size();
        potasowane.insert( potasowane.begin() + gdzie, talia[i] );
    }


    for (int i = 0; i < 52; i = i + 2)                  //  rozdawanie tali miedzy dwoch graczy
    {
        stolik.gracz_1.push(potasowane[i]);
        stolik.gracz_2.push(potasowane[i+1]);
    }

    delete[] talia;
}



void wojna ()
{
    string a;                           //  zabieg czysto kosmetyczny, zeby moc uzyc setw dla slowa "VS"
    a = "VS";

    while (stolik.gracz_1.size() > 0  and  stolik.gracz_2.size() > 0)                    // sprawdzam, czy gracze maj¹ jeszcze karty
    {
        if (stolik.gracz_1.front().wartosc == stolik.gracz_2.front().wartosc)
            cout<<"WOJNA:      ";
        else
            cout<<"            ";

        cout<<setw(2)<<stolik.gracz_1.front().znak<<" "<<stolik.gracz_1.front().kolor                   //  wypisywanie kart poszczegolnych graczy
            <<setw(15 - stolik.gracz_1.front().kolor.size())<<a
            <<setw(11)<<stolik.gracz_2.front().znak<<" "<<stolik.gracz_2.front().kolor
            <<endl;

        if (stolik.gracz_1.front().wartosc > stolik.gracz_2.front().wartosc)                //  jezeli gracz 1 polozyl wyzsza karte
        {
            while (stolik.stos.size() > 0)                        //    oproznianie stosu po wojnie i przypisywanie tych kart wygranemu graczowi
            {
                stolik.gracz_1.push(stolik.stos.front());
                stolik.stos.pop();
            }

            stolik.gracz_1.push(stolik.gracz_2.front());                    //  wygrany zabiera karte swoja i przeciwnika
            stolik.gracz_1.push(stolik.gracz_1.front());
            stolik.gracz_1.pop();
            stolik.gracz_2.pop();

            if (stolik.gracz_2.size() == 0)
                cout<<endl<<"WYGRYWA GRACZ NUMER 1"<<endl<<endl;
        }
        else if (stolik.gracz_1.front().wartosc < stolik.gracz_2.front().wartosc)           //  jezeli gracz 2 polozyl wyzsza karte
        {
            while (stolik.stos.size() > 0)
            {
                stolik.gracz_2.push(stolik.stos.front());
                stolik.stos.pop();
            }

            stolik.gracz_2.push(stolik.gracz_1.front());
            stolik.gracz_2.push(stolik.gracz_2.front());
            stolik.gracz_1.pop();
            stolik.gracz_2.pop();

            if (stolik.gracz_1.size() == 0)
                cout<<endl<<"WYGRYWA GRACZ NUMER 2"<<endl<<endl;
        }
        else                                                                            //  jezeli dwaj gracze polozyli rownowarte karty
        {
            stolik.stos.push(stolik.gracz_1.front());
            stolik.stos.push(stolik.gracz_2.front());
            stolik.gracz_1.pop();
            stolik.gracz_2.pop();

            if (stolik.gracz_1.size() > 0  and  stolik.gracz_2.size() > 0)                      //  sprawdzam, czy gracze maja jeszcze karty
            {
                cout<<"ZAKRYTE:       KARTA                      KARTA"<<endl;

                stolik.stos.push(stolik.gracz_1.front());
                stolik.stos.push(stolik.gracz_2.front());
                stolik.gracz_1.pop();
                stolik.gracz_2.pop();
            }

            if (stolik.gracz_1.size() == 0)                                     //  sytuacja w ktorej jeden z graczy nie ma juz kart,
                                                                                //  drugi ma 50 kart, a na stole sa dwie rownowartosciowe
                cout<<endl<<"WYGRYWA GRACZ NUMER 2"<<endl<<endl;                //  wygrywa ten, ktory ma wiecej kart
            else if (stolik.gracz_2.size() == 0)
                cout<<endl<<"WYGRYWA GRACZ NUMER 1"<<endl<<endl;
        }
    }
}

