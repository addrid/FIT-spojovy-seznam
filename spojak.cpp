// CREATED BY Daniel Navratil
#include <stdio.h>
#include <stdlib.h>
 
/* Nase oblibena struktura */
typedef struct TNode
{
    int            m_Val;
    struct TNode * m_Next;
 
} TNODE;
/*--------------------------------------------------------------------*/
/* Funkce insertStart vlozi prvek na zacatek spojoveho seznamu.
 * Podrobneji popsano v clanku.
 */
TNODE * insertStart ( int val, TNODE * start )
{
    TNODE * tmp = start;
    start = ( TNODE * ) malloc ( sizeof ( *start ) );
 
    start -> m_Val = val;
    start -> m_Next = tmp;
 
    return start; /*Vracime novy zacatek*/
}
/*--------------------------------------------------------------------*/
/* Funkce insertEnd vklada prvek na konec seznamu. Vzhledem k tomu,
 * ze seznam je jednosmerny, tak musime od zacatku projit cely seznam,
 * dokud nenarazime na strukturu, ktera ma v m_Next NULL a teprve tam
 * muzeme pridavat.
 *
 * Nedeste se dvojhvezdickoveho ukazatele, je to v podstate ukazatel
 * na ukazatel. Pokud nam prijde prazdny seznam, potrebujeme modifikovat
 * zacatek, to nam ale obycejny ukazatel neumozni.
 * Muzeme zacatek vracet jako ve funkci insertStart a vyhnout se tak uplne
 * dvojhvezdickovym ukazatelum, ale je dost na hlavu, aby funkce pridavajici
 * prvky na konec vracela zacatek, ne?
 */
void insertEnd ( int val, TNODE ** start )
{
    /* temp je pouze pomocna promenna, abychom nepracovali s neoblibenym
     * dvouhvezdickovym ukazatelem
     */
    TNODE * temp = *start;
    /* Musime osetrit stav, kdy se funkce zavola na prazdny seznam,
     * pokud bychom to neudelali, program by pri pristupu do temp->m_Next
     * havaroval
     */
 
     if ( !*start )
     {
        *start = insertStart( val, *start ); /*vyuzijeme funkci, kterou uz mame*/
        return;
     }
 
    /* Proc nepouzivame pouze temp, ale temp -> m_Next? Jednoduse proto,
     * ze kdyz dojdeme na konec, tak mame akorat ukazatel na NULL a s tim
     * se muzeme jit klouzat. Potrebujeme novemu predposlenimu prvku
     * nastavit m_Next na novy posledni prvek.
     */
 
    while ( temp -> m_Next )
    {
        temp = temp -> m_Next; /*Dokud muzu, prelezu na dalsi polozku*/
    }
 
    /*Vytvarime a inicializujeme novy posledni prvek*/
    temp -> m_Next = ( TNODE * ) malloc ( sizeof ( *temp ) );
    temp -> m_Next -> m_Val = val;
    temp -> m_Next -> m_Next = NULL;
 
    /* Pokud mate problem vyznat se v sipkach, zkuste si to udelat takto:
       TNODE * NovyPosledni = ( TNODE * ) malloc ( sizeof ( *start ) );
       NovyPosledni -> m_Val = val;
       NovyPosledni -> m_Next = NULL;
       temp -> m_Next = NovyPosledni;
     * Dela to uplne to same, jen je tam tech sipek mene a lepe se to
     * predstavuje.
     */
}
/*--------------------------------------------------------------------*/
/* Funkce insertAfter vlozi prvek do seznamu za polozku, ktera ma val rovnu
 * parametru position. Slouzi jen k ucelu, jak vlozit neco doprostred seznamu.
 */
int insertAfter ( TNODE * list, int position, int val )
{
    TNODE * temp, *next;
    /* Polezeme seznamem, dokud nenarazime na polozku, ktera ma
     * m_Val rovnu position. Ve chvili, kdy ji najdeme, ji mame
     * v promenne list a muzeme s ni dale pracovat.*/
    while ( list )
    {
        if ( list -> m_Val == position )
            break;
        list = list -> m_Next;
    }
    /*Pokud takova polozka neni, list ukazuje na NULL a hlasime chybu.*/
    if ( !list )
    {
        printf( "Polozka s hodnotou %d nenalezena!", position );
        return 1;
    }
    /* Zazalohujeme si ukazatel na nasledujici polozku listu, abychom
     * pak pripojili konec seznamu.*/
    temp = list -> m_Next;
 
    /*Vytvorime novou polozku a inicializujeme ji.*/
    next = ( TNODE * ) malloc ( sizeof ( *next ) );
    next -> m_Val = val;
    /*Pripojime ji za list*/
    list -> m_Next = next;
    /*K next pripojime zazalohovany konec seznamu*/
    next -> m_Next = temp;
 
    return 0;
}
/*--------------------------------------------------------------------*/
void deleteListRec ( TNODE * list )
{
 
 
}
/*--------------------------------------------------------------------*/
void deleteList ( TNODE * list )
{
    /*Iterativni verze*/
    TNODE * tmp;
    while ( list )
    {
        tmp = list -> m_Next;
        free ( list );
        list = tmp;
    }
 
    /*Rekurzivni verze, nepoustejte obe naraz*/
    /*
    if ( !list ) return;
    if( list -> m_Next )
        deleteList ( list -> m_Next );
    free ( list );
    */
}
/*--------------------------------------------------------------------*/
void printListIter ( TNODE * list )
{
 
    while ( list )
    {
        printf("%d ", list -> m_Val );
        list = list -> m_Next;
    }
    printf("\n");
}
/*--------------------------------------------------------------------*/
void printListRec ( TNODE * list )
{
    if ( list )
    {
        /* printListRec ( list -> m_Next ); tiskne v opacnem poradi*/
        printf( "%d ", list -> m_Val );
        printListRec ( list -> m_Next ); /*tiskne stejne jako printListIter*/
    }
}
/*--------------------------------------------------------------------*/
 
int main ( int argc, char * argv [] )
{
    TNODE * list = NULL;
 
    list = insertStart( -1, list ); /*-1*/
    list = insertStart( -2, list ); /*-2 -1*/
    list = insertStart( -3, list ); /*-3 -2 -1*/
 
    printListIter ( list );
 
    insertEnd ( 0, & list ); /*-3 -2 -1 0*/
    insertEnd ( 1, & list ); /*-3 -2 -1 0 1*/
    insertEnd ( 3, & list ); /*-3 -2 -1 0 1 3*/
 
    printListIter ( list );
 
    /*pridame dvojku za jednicku*/
    insertAfter ( list, 1, 2 );
 
    printf("\nRekurzivni vypis:\n");
    printListRec ( list );
 
    printf("\n\nIteracni vypis:\n");
    printListIter ( list );
 
    deleteList ( list );
 
    return 0;
}
