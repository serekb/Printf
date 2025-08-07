// Printf.cpp : Defines the entry point for the console application.
//

#include <stdio.h>
#include <stdarg.h>

int Printf( const char* sFormat, ...); 
int PrintfV( const char* sFormat, va_list args);

void outDec( int );       // znakowo wypisuje liczbe calk
void outChar( char );     // wypisuje znak  // putchar()
void outStr( char* );     // wypisuje zanakowo string
void outDouble( double ); // wypisuje znakowow liczbe double    0.  (do 8 po kropce)
void outNum( int x );     // wypisuje znakowo liczbe int >0     rekurencyjnie

//----------------------------------
int main(/*int argc, char* argv[]*/)
{
    int n = -0;
    char c = '$';
    double x = 12000000.34500000012;   // nie wiecej jak 8 po pkropce  // .0000012 <=1e-6
    double y = -.12;
    double z = -1.5;
    char* str = (char*)"to jest string";

    n = Printf("%s\n%f%c  *%a*  n=%%d \\ \% /\ny=%f ` ` z=%%f\n%", str, x, c, n, y, z);  // ` -> '
    Printf("\nilosc formatow=%d\n", n);
    return 0;

}
// implementacja uproszczonej funkcji "Printf": %c %d %f %s oraz 
// zamienia `(klawisz ~) na '( klawisz ")
// do wypisywania mozna uzyc JEDYNIE putchar() (raz) (poprzez outChar())


//-----------------------------------------------
int Printf( const char* sFormat, ...)
{

    va_list args; //pointer to the list of arguments //!!!!
    va_start(args, sFormat);// initialize args pointer //!!!!

    int res = PrintfV( sFormat, args ); //!!!!

    va_end(args); //reset variable arguments //!!!!

    return res;
}
//-----------------------------------------------
int PrintfV( const char* sFormat, va_list args )/*sFormat*/
{
    char c;
    int ilosc = 0;

    while( c = *sFormat++ )
    {
        switch(c)
        {
        case '%':
            switch( c = *sFormat++ )
            {
            case 'd': ilosc++; outDec( va_arg( args, int) ); break;
            case 'f': ilosc++; outDouble( va_arg( args, double) ); break;
            case 's': ilosc++; outStr( va_arg( args, char*) ); break;
            case 'c': ilosc++; outChar( va_arg( args, char) ); break;
            default: outChar( '%' ); sFormat--; break;
            }
            break;
        case '`': c = '\''; // to bez break-a
        default: 
            outChar( c );
        }
    }
    return ilosc;
}

//-----------------------------------------------
void outChar( char c)
{
    putchar( c );
}
//-----------------------------------------------
void outStr( char* pStr )
{
    while( *pStr )
        outChar( *pStr++ );
}
//-----------------------------------------------
void outDec( int x)
{
    if(!x)
    {   outChar( '0' ); return; }
    if(x < 0) // ¿eby x zawsze >0
    {
        outChar( '-' );
        x = -x;
    }
    outNum( x );// wypisac znak jesli trzeba i wykorzystac outNum()
}

//-----------------------------------------------
void outDouble( double x )
{
    if(x <-1e-6)
    {
        x=-x;
        outChar('-');
    }
    outDec( int(x) );
    int n=0;
    x = x - (int)x;
    if ((x - (int)x) > 1e-6)
        outChar( '.' );
    while((x - (int)x) > 1e-6 && n < 8)
    {
        outChar( (int)(x *= 10) % 10 + '0' );
        n++;
    }
    // wykorzystac outDec()
   // przerwac drukowanie jesli reszta <=1e-6  ewentualnie do  8-miu cyfr po kropce
}
//-----------------------------------------------
void outNum( int x ) //rekurencyjny  //x>0
{
    if( !x )
        return;
    outNum( x/10 );
    outChar( x%10 + '0' );
}
